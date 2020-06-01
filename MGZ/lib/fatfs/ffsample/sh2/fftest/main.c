/*----------------------------------------------------------------------*/
/* FatFs Module Sample Program / Renesas SH7262        (C)ChaN, 2019    */
/*----------------------------------------------------------------------*/
/* Ev.Board: FRK-SH2A from CQ Publishing                                */
/* Console: SCI2 (N81 38400bps)                                         */
/* MMC/SDC: RSPI0 (SPI mode)                                            */
/*----------------------------------------------------------------------*/


#include <machine.h>
#include <string.h>
#include "iodefine.h"
#include "vect.h"
#include "scif.h"
#include "xprintf.h"
#include "ff.h"
#include "diskio.h"

#define	F_PCLK	24000000UL



/*---------------------------------------------------------*/
/* Work Area                                               */
/*---------------------------------------------------------*/

FATFS FatFs[FF_VOLUMES];	/* File system object */
FIL File[2];				/* File objects */
DIR Dir;					/* Directory object */

DWORD AccSize;				/* Working variables (fs command) */
WORD AccFiles, AccDirs;

FILINFO Finfo;				/* Working variables (fs/fl command) */

char Line[256];				/* Console input buffer */
BYTE Buff[32768];			/* Disk I/O working buffer */

volatile UINT Timer;		/* Performance timer (1kHz) */




/*---------------------------------------------------------*/
/* 1000Hz interval timer (CMT0)                            */
/*---------------------------------------------------------*/

void INT_CMT_CMI0 (void)	/* ISR: Requires vect.h */
{
	static int div10, b;


	CMT.CMCSR0.BIT.CMF = 0;		/* Clear CMT0 interrupt flag */

	Timer++;

	if (++div10 >= 10) {
		div10 = 0;
		disk_timerproc();		/* Disk timer function (100Hz) */
	}
}


static
void delay_ms (					/* Delay in unit of ms */
	UINT ms
)
{
	for (Timer = 0; Timer < ms; ) ;
}



/*---------------------------------------------------------*/
/* Initialize peripherals                                  */
/*---------------------------------------------------------*/


#define SetCCR1(x) ((void(*)(DWORD))((DWORD)SetCCR1_proc + 0x20000000))(x)	/* Write data to CCR1 (Executed at non-cacheable area) */
void SetCCR1_proc (DWORD val)	/* Write a value to CCR1 */
{
	CCNT.CCR1.LONG;
	CCNT.CCR1.LONG;
	CCNT.CCR1.LONG = val;
	CCNT.CCR1.LONG;
	CCNT.CCR1.LONG;
}


static
void IoInit (void)
{
	CPG.FRQCR.WORD = 0x0104;		/* Clock configuration: ICLK=144M, BCLK=48M, PCLK=24M */
	SetCCR1(0x0000090B);			/* Enable instruction/data cache */

	CPG.STBCR3.BYTE = 0;			/* Enable all peripherals */
	CPG.STBCR4.BYTE = 0;
	CPG.STBCR5.BYTE = 0;
	CPG.STBCR6.BYTE = 0;
	CPG.STBCR7.BYTE = 0;
	CPG.STBCR8.BYTE = 0;

	scif2_init(38400);				/* Initialize SCI2: N81,38400bps */

	/* Initialize CMT0 (1kHz interval timer) */
	CMT.CMCNT0.WORD = 0;			/* Clear counter */
	CMT.CMCOR0.WORD = F_PCLK / 8 / 1000 - 1;	/* Set clock divider */
	CMT.CMCSR0.WORD = 0x0040;		/* Enable interrupt, Clock source = PCLK/8 */
	CMT.CMSTR.BIT.STR0 = 1;			/* Start CMT0 */
	INTC.IPR10.BIT._CMT0 = 2;		/* Set interrupt level 2 */


	INTC.IBNR.WORD = 0;				/* Disable register bank feature */
	set_imask(0);					/* Enable interrrupt */
}



/*---------------------------------------------------------*/
/* User Provided Timer Function for FatFs module           */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support a real time clock.          */
/* This is not required in read-only configuration.        */

#if !FF_FS_NORTC
DWORD get_fattime (void)
{
	/* Return a fixed value 2010/4/26 0:00:00 */
	return	  ((DWORD)(2010 - 1980) << 25)	/* Y */
			| ((DWORD)4  << 21)				/* M */
			| ((DWORD)26 << 16)				/* D */
			| ((DWORD)0  << 11)				/* H */
			| ((DWORD)0  << 5)				/* M */
			| ((DWORD)0  >> 1);				/* S */
}
#endif



/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */
/*--------------------------------------------------------------------------*/


static
FRESULT scan_files (	/* Scan directory in recursive */
	char* path			/* Pointer to the path name working buffer */
)
{
	DIR dirs;
	FRESULT res;
	int i;


	res = f_opendir(&dirs, path);	/* Open the directory */
	if (res == FR_OK) {
		i = strlen(path);
		while (((res = f_readdir(&dirs, &Finfo)) == FR_OK) && Finfo.fname[0]) {	/* Get an entry from the dir */
			if (Finfo.fattrib & AM_DIR) {	/* It is a directory */
				AccDirs++;
				path[i] = '/'; strcpy(path+i+1, Finfo.fname);	/* Scan the directory */
				res = scan_files(path);
				path[i] = '\0';
				if (res != FR_OK) break;
			} else {						/* It is a file  */
				AccFiles++;
				AccSize += Finfo.fsize;				/* Accumulate the file size in unit of byte */
			}
		}
	}

	return res;
}



static
void put_rc (		/* Put FatFs result code with defined symbol */
	FRESULT rc
)
{
	const char *str =
		"OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
		"INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
		"INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
		"LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0" "INVALID_NAME\0";
	FRESULT i;

	for (i = FR_OK; i != rc && *str; i++) {
		while (*str++) ;
	}
	xprintf("rc=%u FR_%s\n", (UINT)rc, str);
}



static
const char HelpMsg[] =
	"[Disk contorls]\n"
	" di <pd#> - Initialize disk\n"
	" dd [<pd#> <lba>] - Dump a secrtor\n"
	" ds <pd#> - Show disk status\n"
	"[Buffer controls]\n"
	" bd <ofs> - Dump working buffer\n"
	" be <ofs> [<data>] ... - Edit working buffer\n"
	" br <pd#> <lba> [<count>] - Read disk into working buffer\n"
	" bw <pd#> <lba> [<count>] - Write working buffer into disk\n"
	" bf <val> - Fill working buffer\n"
	"[File system controls]\n"
	" fi - Force initialized the volume\n"
	" fs [<path>] - Show volume status\n"
	" fl [<path>] - Show a directory\n"
	" fo <mode> <file> - Open a file\n"
	" fc - Close the file\n"
	" fe <ofs> - Move fp in normal seek\n"
	" fd <len> - Read and dump the file\n"
	" fr <len> - Read the file\n"
	" fw <len> <val> - Write to the file\n"
	" fn <org.name> <new.name> - Rename an object\n"
	" fu <name> - Unlink an object\n"
	" fv - Truncate the file at current fp\n"
	" fk <name> - Create a directory\n"
	" fa <atrr> <mask> <object name> - Change attribute of an object\n"
	" ft <year> <month> <day> <hour> <min> <sec> <name> - Change timestamp of an object\n"
	" fx <src.file> <dst.file> - Copy a file\n"
	" fg <path> - Change current directory\n"
	" fq - Show current directory\n"
	" fb <name> - Set volume label\n"
	" fm [<fs type> [<au size> [<align> [<n_fats> [<n_root>]]]]] - Create filesystem\n"
	" fz [<len>] - Change/Show R/W length for fr/fw/fx command\n"
	"[Misc commands]\n"
	" md[b|h|w] <addr> [<count>] - Dump memory\n"
	" mf <addr> <value> <count> - Fill memory\n"
	" me[b|h|w] <addr> [<value> ...] - Edit memory\n"
	"\n";



/*--------------------------------------------------------------------------*/
/* Main                                                                     */
/*--------------------------------------------------------------------------*/

int main (void)
{
	char *ptr, *ptr2;
	long p1, p2, p3;
	BYTE dr, b1, drv = 0;
	FRESULT res;
	UINT s1, s2, cnt, blen = sizeof Buff;
	DWORD ofs = 0, sect = 0;
	FATFS *fs;
	static const BYTE ft[] = {0,12,16,32};


	IoInit();

	xdev_in(scif2_getc);		/* Join scif.c and monitor.c */
	xdev_out(scif2_putc);

	delay_ms(10);
	xputs("\nFatFs module test monitor for FRK-RN62N evaluation board\n");
	xprintf("LFN=%s, CP=%u\n", FF_USE_LFN ? "Enabled" : "Disabled", FF_CODE_PAGE);

	for (;;) {
		xputc('>');
		xgets(Line, sizeof Line);

		ptr = Line;
		switch (*ptr++) {
		case '?' :		/* ? - Show usage */
			xputs(HelpMsg);
			break;

		case 'm' :	/* Memory dump/fill/edit */
			switch (*ptr++) {
			case 'd' :	/* md[b|h|w] <address> [<count>] - Dump memory */
				switch (*ptr++) {
				case 'w': p3 = DW_LONG; break;
				case 'h': p3 = DW_SHORT; break;
				default: p3 = DW_CHAR;
				}
				if (!xatoi(&ptr, &p1)) break;
				if (!xatoi(&ptr, &p2)) p2 = 128 / p3;
				for (ptr = (char*)p1; p2 >= 16 / p3; ptr += 16, p2 -= 16 / p3)
					put_dump(ptr, (DWORD)ptr, 16 / p3, p3);
				if (p2) put_dump((BYTE*)ptr, (UINT)ptr, p2, p3);
				break;
			case 'f' :	/* mf <address> <value> <count> - Fill memory */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				while (p3--) {
					*(BYTE*)p1 = (BYTE)p2;
					p1++;
				}
				break;
			case 'e' :	/* me[b|h|w] <address> [<value> ...] - Edit memory */
				switch (*ptr++) {	/* Get data width */
				case 'w': p3 = DW_LONG; break;
				case 'h': p3 = DW_SHORT; break;
				default: p3 = DW_CHAR;
				}
				if (!xatoi(&ptr, &p1)) break;	/* Get start address */
				if (xatoi(&ptr, &p2)) {	/* 2nd parameter is given (direct mode) */
					do {
						switch (p3) {
						case DW_LONG: *(DWORD*)p1 = (DWORD)p2; break;
						case DW_SHORT: *(WORD*)p1 = (WORD)p2; break;
						default: *(BYTE*)p1 = (BYTE)p2;
						}
						p1 += p3;
					} while (xatoi(&ptr, &p2));	/* Get next value */
					break;
				}
				for (;;) {				/* 2nd parameter is not given (interactive mode) */
					switch (p3) {
					case DW_LONG: xprintf("%08X 0x%08X-", p1, *(DWORD*)p1); break;
					case DW_SHORT: xprintf("%08X 0x%04X-", p1, *(WORD*)p1); break;
					default: xprintf("%08X 0x%02X-", p1, *(BYTE*)p1);
					}
					ptr = Line; xgets(ptr, sizeof Line);
					if (*ptr == '.') break;
					if ((BYTE)*ptr >= ' ') {
						if (!xatoi(&ptr, &p2)) continue;
						switch (p3) {
						case DW_LONG: *(DWORD*)p1 = (DWORD)p2; break;
						case DW_SHORT: *(WORD*)p1 = (WORD)p2; break;
						default: *(BYTE*)p1 = (BYTE)p2;
						}
					}
					p1 += p3;
				}
				break;
			}
			break;

		case 'd' :	/* Disk I/O layer controls */
			switch (*ptr++) {
			case 'd' :	/* dd [<pd#> <sect>] - Dump secrtor */
				if (!xatoi(&ptr, &p1)) {
					p1 = drv; p2 = sect;
				} else {
					if (!xatoi(&ptr, &p2)) break;
				}
				drv = (BYTE)p1; sect = p2;
				dr = disk_read(drv, Buff, sect, 1);
				if (dr) { xprintf("rc=%d\n", (WORD)dr); break; }
				xprintf("PD#:%u LBA:%lu\n", drv, sect++);
				for (ptr=(char*)Buff, ofs = 0; ofs < 0x200; ptr += 16, ofs += 16)
					put_dump((BYTE*)ptr, ofs, 16, DW_CHAR);
				break;

			case 'i' :	/* di <pd#> - Initialize disk */
				if (!xatoi(&ptr, &p1)) break;
				xprintf("rc=%d\n", (WORD)disk_initialize((BYTE)p1));
				break;

			case 's' :	/* ds <pd#> - Show disk status */
				if (!xatoi(&ptr, &p1)) break;
				if (disk_ioctl((BYTE)p1, GET_SECTOR_COUNT, &p2) == RES_OK)
					{ xprintf("Drive size: %lu sectors\n", p2); }
				if (disk_ioctl((BYTE)p1, GET_BLOCK_SIZE, &p2) == RES_OK)
					{ xprintf("Block size: %lu sectors\n", p2); }
				if (disk_ioctl((BYTE)p1, MMC_GET_TYPE, &b1) == RES_OK)
					{ xprintf("Media type: %u\n", b1); }
				if (disk_ioctl((BYTE)p1, MMC_GET_CSD, Buff) == RES_OK)
					{ xputs("CSD:\n"); put_dump(Buff, 0, 16, DW_CHAR); }
				if (disk_ioctl((BYTE)p1, MMC_GET_CID, Buff) == RES_OK)
					{ xputs("CID:\n"); put_dump(Buff, 0, 16, DW_CHAR); }
				if (disk_ioctl((BYTE)p1, MMC_GET_OCR, Buff) == RES_OK)
					{ xputs("OCR:\n"); put_dump(Buff, 0, 4, DW_CHAR); }
				if (disk_ioctl((BYTE)p1, MMC_GET_SDSTAT, Buff) == RES_OK) {
					xputs("SD Status:\n");
					for (s1 = 0; s1 < 64; s1 += 16) put_dump(Buff+s1, s1, 16, DW_CHAR);
				}
				break;

			}
			break;

		case 'b' :	/* Buffer controls */
			switch (*ptr++) {
			case 'd' :	/* bd <ofs> - Dump R/W buffer */
				if (!xatoi(&ptr, &p1)) break;
				for (ptr=(char*)&Buff[p1], ofs = p1, cnt = 32; cnt; cnt--, ptr+=16, ofs+=16)
					put_dump((BYTE*)ptr, ofs, 16, DW_CHAR);
				break;

			case 'e' :	/* be <ofs> [<data>] ... - Edit R/W buffer */
				if (!xatoi(&ptr, &p1)) break;
				if (xatoi(&ptr, &p2)) {
					do {
						Buff[p1++] = (BYTE)p2;
					} while (xatoi(&ptr, &p2));
					break;
				}
				for (;;) {
					xprintf("%04X %02X-", (WORD)(p1), (WORD)Buff[p1]);
					xgets(Line, sizeof Line);
					ptr = Line;
					if (*ptr == '.') break;
					if (*ptr < ' ') { p1++; continue; }
					if (xatoi(&ptr, &p2))
						Buff[p1++] = (BYTE)p2;
					else
						xputs("???\n");
				}
				break;

			case 'r' :	/* br <pd#> <lba> [<num>] - Read disk into R/W buffer */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				if (!xatoi(&ptr, &p3)) p3 = 1;
				xprintf("rc=%u\n", (WORD)disk_read((BYTE)p1, Buff, p2, p3));
				break;

			case 'w' :	/* bw <pd#> <lba> [<num>] - Write R/W buffer into disk */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				if (!xatoi(&ptr, &p3)) p3 = 1;
				xprintf("rc=%u\n", (WORD)disk_write((BYTE)p1, Buff, p2, p3));
				break;

			case 'f' :	/* bf <val> - Fill working buffer */
				if (!xatoi(&ptr, &p1)) break;
				memset(Buff, (BYTE)p1, sizeof Buff);
				break;

			}
			break;

		case 'f' :	/* FatFS API controls */
			switch (*ptr++) {

			case 'i' :	/* fi - Force initialized the logical drive */
				put_rc(f_mount(&FatFs[0], "", 0);
				break;

			case 's' :	/* fs [<path>] - Show volume status */
				while (*ptr == ' ') ptr++;
				res = f_getfree(ptr, (DWORD*)&p1, &fs);
				if (res) { put_rc(res); break; }
				xprintf("FAT type = %s\n", ft[fs->fs_type]);
				xprintf("Bytes/Cluster = %lu\n", (DWORD)fs->csize * 512);
				xprintf("Number of FATs = %u\n", fs->n_fats);
				if (fs->fs_type < FS_FAT32) xprintf("Root DIR entries = %u\n", fs->n_rootdir);
				xprintf("Sectors/FAT = %lu\n", fs->fsize);
				xprintf("Number of clusters = %lu\n", (DWORD)fs->n_fatent - 2);
				xprintf("Volume start (lba) = %lu\n", fs->volbase);
				xprintf("FAT start (lba) = %lu\n", fs->fatbase);
				xprintf("FDIR start (lba,clustor) = %lu\n", fs->dirbase);
				xprintf("Data start (lba) = %lu\n\n", fs->database);
#if FF_USE_LABEL
				res = f_getlabel(ptr, (char*)Buff, (DWORD*)&p2);
				if (res) { put_rc(res); break; }
				xprintf(Buff[0] ? "Volume name is %s\n" : "No volume label\n", (char*)Buff);
				xprintf("Volume S/N is %04X-%04X\n", (DWORD)p2 >> 16, (DWORD)p2 & 0xFFFF);
#endif
				AccSize = AccFiles = AccDirs = 0;
				xprintf("...");
				res = scan_files(ptr);
				if (res) { put_rc(res); break; }
				xprintf("\r%u files, %lu bytes.\n%u folders.\n"
						"%lu KiB total disk space.\n%lu KiB available.\n",
						AccFiles, AccSize, AccDirs,
						(fs->n_fatent - 2) * (fs->csize / 2), (DWORD)p1 * (fs->csize / 2)
				);
				break;

			case 'l' :	/* fl [<path>] - Directory listing */
				while (*ptr == ' ') ptr++;
				res = f_opendir(&Dir, ptr);
				if (res) { put_rc(res); break; }
				p1 = s1 = s2 = 0;
				for(;;) {
					res = f_readdir(&Dir, &Finfo);
					if ((res != FR_OK) || !Finfo.fname[0]) break;
					if (Finfo.fattrib & AM_DIR) {
						s2++;
					} else {
						s1++; p1 += Finfo.fsize;
					}
					xprintf("%c%c%c%c%c %u/%02u/%02u %02u:%02u %9lu  %s\n",
							(Finfo.fattrib & AM_DIR) ? 'D' : '-',
							(Finfo.fattrib & AM_RDO) ? 'R' : '-',
							(Finfo.fattrib & AM_HID) ? 'H' : '-',
							(Finfo.fattrib & AM_SYS) ? 'S' : '-',
							(Finfo.fattrib & AM_ARC) ? 'A' : '-',
							(Finfo.fdate >> 9) + 1980, (Finfo.fdate >> 5) & 15, Finfo.fdate & 31,
							(Finfo.ftime >> 11), (Finfo.ftime >> 5) & 63,
							Finfo.fsize, Finfo.fname);
				}
				xprintf("%4u File(s),%10lu bytes total\n%4u Dir(s)", s1, p1, s2);
				res = f_getfree(ptr, (DWORD*)&p1, &fs);
				if (res == FR_OK)
					xprintf(", %10lu bytes free\n", p1 * fs->csize * 512);
				else
					put_rc(res);
				break;

			case 'o' :	/* fo <mode> <file> - Open a file */
				if (!xatoi(&ptr, &p1)) break;
				while (*ptr == ' ') ptr++;
				put_rc(f_open(&File[0], ptr, (BYTE)p1));
				break;

			case 'c' :	/* fc - Close a file */
				put_rc(f_close(&File[0]));
				break;

			case 'e' :	/* fe - Seek file pointer */
				if (!xatoi(&ptr, &p1)) break;
				res = f_lseek(&File[0], p1);
				put_rc(res);
				if (res == FR_OK)
					xprintf("fptr=%lu(0x%lX)\n", File[0].fptr, File[0].fptr);
				break;

			case 'd' :	/* fd <len> - read and dump file from current fp */
				if (!xatoi(&ptr, &p1)) break;
				ofs = File[0].fptr;
				while (p1) {
					if ((UINT)p1 >= 16) { cnt = 16; p1 -= 16; }
					else 				{ cnt = p1; p1 = 0; }
					res = f_read(&File[0], Buff, cnt, &cnt);
					if (res != FR_OK) { put_rc(res); break; }
					if (!cnt) break;
					put_dump(Buff, ofs, cnt, DW_CHAR);
					ofs += 16;
				}
				break;

			case 'r' :	/* fr <len> - read file */
				if (!xatoi(&ptr, &p1)) break;
				p2 = 0;
				Timer = 0;
				while (p1) {
					if ((UINT)p1 >= blen) {
						cnt = blen; p1 -= blen;
					} else {
						cnt = p1; p1 = 0;
					}
					res = f_read(&File[0], Buff, cnt, &s2);
					if (res != FR_OK) { put_rc(res); break; }
					p2 += s2;
					if (cnt != s2) break;
				}
				xprintf("%lu bytes read with %lu kB/sec.\n", p2, Timer ? (p2 / Timer) : 0);
				break;

			case 'w' :	/* fw <len> <val> - write file */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				memset(Buff, (BYTE)p2, blen);
				p2 = 0;
				Timer = 0;
				while (p1) {
					if ((UINT)p1 >= blen) {
						cnt = blen; p1 -= blen;
					} else {
						cnt = p1; p1 = 0;
					}
					res = f_write(&File[0], Buff, cnt, &s2);
					if (res != FR_OK) { put_rc(res); break; }
					p2 += s2;
					if (cnt != s2) break;
				}
				xprintf("%lu bytes written with %lu kB/sec.\n", p2, Timer ? (p2 / Timer) : 0);
				break;

			case 'n' :	/* fn <org.name> <new.name> - Change name of an object */
				while (*ptr == ' ') ptr++;
				ptr2 = strchr(ptr, ' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				while (*ptr2 == ' ') ptr2++;
				put_rc(f_rename(ptr, ptr2));
				break;

			case 'u' :	/* fu <name> - Unlink an object */
				while (*ptr == ' ') ptr++;
				put_rc(f_unlink(ptr));
				break;

			case 'v' :	/* fv - Truncate file */
				put_rc(f_truncate(&File[0]));
				break;

			case 'k' :	/* fk <name> - Create a directory */
				while (*ptr == ' ') ptr++;
				put_rc(f_mkdir(ptr));
				break;
#if FF_USE_CHMOD
			case 'a' :	/* fa <atrr> <mask> <name> - Change attribute of an object */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				while (*ptr == ' ') ptr++;
				put_rc(f_chmod(ptr, p1, p2));
				break;

			case 't' :	/* ft <year> <month> <day> <hour> <min> <sec> <name> - Change timestamp of an object */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.fdate = ((p1 - 1980) << 9) | ((p2 & 15) << 5) | (p3 & 31);
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.ftime = ((p1 & 31) << 11) | ((p2 & 63) << 5) | ((p3 >> 1) & 31);
				put_rc(f_utime(ptr, &Finfo));
				break;
#endif
			case 'x' : /* fx <src.name> <dst.name> - Copy a file */
				while (*ptr == ' ') ptr++;
				ptr2 = strchr(ptr, ' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				while (*ptr2 == ' ') ptr2++;
				xprintf("Opening \"%s\"", ptr);
				res = f_open(&File[0], ptr, FA_OPEN_EXISTING | FA_READ);
				xputc('\n');
				if (res) {
					put_rc(res);
					break;
				}
				xprintf("Creating \"%s\"", ptr2);
				res = f_open(&File[1], ptr2, FA_CREATE_ALWAYS | FA_WRITE);
				xputc('\n');
				if (res) {
					put_rc(res);
					f_close(&File[0]);
					break;
				}
				xprintf("Copying file...");
				Timer = 0;
				p1 = 0;
				for (;;) {
					res = f_read(&File[0], Buff, blen, &s1);
					if (res || s1 == 0) break;   /* error or eof */
					res = f_write(&File[1], Buff, s1, &s2);
					p1 += s2;
					if (res || s2 < s1) break;   /* error or disk full */
				}
				xprintf("\n%lu bytes copied with %lu kB/sec.\n", p1, p1 / Timer);
				f_close(&File[0]);
				f_close(&File[1]);
				break;
#if FF_FS_RPATH
			case 'g' :	/* fg <path> - Change current directory */
				while (*ptr == ' ') ptr++;
				put_rc(f_chdir(ptr));
				break;
#if FF_FS_RPATH >= 2
			case 'q' :	/* fq - Show current dir path */
				res = f_getcwd(Line, sizeof Line);
				if (res)
					put_rc(res);
				else
					xprintf("%s\n", Line);
				break;
#endif
#endif
#if FF_USE_LABEL
			case 'b' :	/* fb <name> - Set volume label */
				while (*ptr == ' ') ptr++;
				put_rc(f_setlabel(ptr));
				break;
#endif	/* FF_USE_LABEL */
#if FF_USE_MKFS
			case 'm' :	/* fm [<fs type> [<au size> [<align> [<n_fats> [<n_root>]]]]] - Create filesystem */
				{
					MKFS_PARM opt, *popt = 0;

					if (xatoi(&ptr, &p2)) {
						memset(&opt, 0, sizeof opt);
						popt = &opt;
						popt->fmt = (BYTE)p2;
						if (xatoi(&ptr, &p2)) {
							popt->au_size = p2;
							if (xatoi(&ptr, &p2)) {
								popt->align = p2;
								if (xatoi(&ptr, &p2)) {
									popt->n_fat = (BYTE)p2;
									if (xatoi(&ptr, &p2)) {
										popt->n_root = p2;
									}
								}
							}
						}
					}
					xprintf("The volume will be formatted. Are you sure? (Y/n)=");
					xgets(Line, sizeof Line);
					if (Line[0] == 'Y') put_rc(f_mkfs("", popt, Buff, sizeof Buff));
					break;
				}
#endif	/* FF_USE_MKFS */
			case 'z' :	/* fz [<size>] - Change/Show R/W length for fr/fw/fx command */
				if (xatoi(&ptr, &p1) && p1 >= 1 && p1 <= (long)sizeof Buff)
					blen = p1;
				xprintf("blen=%u\n", blen);
				break;
			}
			break;
		}
	}
}
