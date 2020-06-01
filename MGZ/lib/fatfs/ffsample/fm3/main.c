/*----------------------------------------------------------------------*/
/* FAT file system sample project for FatFs            (C)ChaN, 2019    */
/*----------------------------------------------------------------------*/
/* Ev.Board: FRK-FM3 from CQ Publishing                                 */
/* Console: N81 115200bps (port is defined in uart.c)                   */
/* MMC/SDC: SPI mode (port is defined in mmc.c)                         */
/*----------------------------------------------------------------------*/

#include <string.h>
#include "FM3_type2.h"
#include "uart_mfs.h"
#include "xprintf.h"
#include "ff.h"
#include "diskio.h"
#include "iic.h"
#include "sound.h"

extern void disk_timerproc (void);


/* Control onboard LED */
#define LED_ON()	DDRF |= 0x0008	/* PF3 Low */
#define LED_OFF()	DDRF &= ~0x0008	/* PF3 Hi-Z */


DWORD AccSize;				/* Work register for fs command */
WORD AccFiles, AccDirs;
FILINFO Finfo;

char Line[256];				/* Console input buffer */
BYTE Buff[32768] __attribute__ ((aligned (4))) ;	/* Working buffer */

FATFS FatFs;				/* File system object for each logical drive */
FIL File[2];				/* File objects */
DIR Dir;					/* Directory object */

volatile UINT Timer;		/* Performance counter (1kHz increment) */


/*---------------------------------------------*/
/* 1kHz timer process                          */
/*---------------------------------------------*/

void SysTick_Handler (void)
{
	static UINT led;


	Timer++;	/* Increment performance counter */

	led++;		/* LED blinking timer */
	if ((led & 0x40) && (led & 0x680) == 0) {
		LED_ON();
	} else {
		LED_OFF();
	}

	disk_timerproc();	/* Disk timer process (mmc.c) */
}


/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called back     */
/* from FatFs module.                                      */

#if !_FS_NORTC && !_FS_READONLY
DWORD get_fattime (void)
{
	return	  ((DWORD)(2012 - 1980) << 25)	/* Return fixed value 2012/4/1 0:0:0 */
			| ((DWORD)4 << 21)
			| ((DWORD)1 << 16)
			| ((DWORD)0 << 11)
			| ((DWORD)0 << 5)
			| ((DWORD)0 >> 1);
}
#endif


/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */
/*--------------------------------------------------------------------------*/

static
FRESULT scan_files (
	char* path		/* Pointer to the path name working buffer */
)
{
	DIR dir;
	FRESULT res;
	BYTE i;


	if ((res = f_opendir(&dir, path)) == FR_OK) {
		while (((res = f_readdir(&dir, &Finfo)) == FR_OK) && Finfo.fname[0]) {
			if (Finfo.fattrib & AM_DIR) {
				AccDirs++;
				i = strlen(path);
				*(path+i) = '/'; strcpy(path+i+1, Finfo.fname);
				res = scan_files(path);
				*(path+i) = '\0';
				if (res != FR_OK) break;
			} else {
			//	xprintf("%s/%s\n", path, fn);
				AccFiles++;
				AccSize += Finfo.fsize;
			}
		}
	}

	return res;
}



static
void put_rc (FRESULT rc)
{
	const char *str =
		"OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
		"INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
		"INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
		"LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0" "INVALID_PARAMETER\0";
	FRESULT i;

	for (i = 0; i != rc && *str; i++) {
		while (*str++) ;
	}
	xprintf("rc=%u FR_%s\n", (UINT)rc, str);
}



static
const char HelpMsg[] =
	"[Disk contorls]\n"
	" di - Initialize disk\n"
	" dd [<pd#> <lba>] - Dump a secrtor\n"
	" ds - Show disk status\n"
	"[Buffer controls]\n"
	" bd <ofs> - Dump working buffer\n"
	" be <ofs> [<data>] ... - Edit working buffer\n"
	" br <pd#> <lba> [<count>] - Read disk into working buffer\n"
	" bw <pd#> <lba> [<count>] - Write working buffer into disk\n"
	" bf <val> - Fill working buffer\n"
	"[File system controls]\n"
	" fi [<opt>] - Force initialized the volume\n"
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
	" fa <atrr> <mask> <name> - Change attribute of an object\n"
	" ft <year> <month> <day> <hour> <min> <sec> <name> - Change timestamp of an object\n"
	" fx <src.file> <dst.file> - Copy a file\n"
	" fg <path> - Change current directory\n"
	" fq - Show current directory\n"
	" fb <name> - Set volume label\n"
	" fm <type> <csize> - Create file system\n"
	" fz [<len>] - Change/Show R/W length for fr/fw/fx command\n"
	"[Misc commands]\n"
	" p <wavfile> - Play RIFF-WAVE file\n"
	" md[b|h|w] <addr> [<count>] - Dump memory\n"
	" mf <addr> <value> <count> - Fill memory\n"
	" me[b|h|w] <addr> [<value> ...] - Edit memory\n"
	" ir <f.addr> <count> - Read FRAM\n"
	" iw <f.addr> <count> - Write FRAM\n"
	"\n";




int main (void)
{
	char *ptr, *ptr2;
	long p1, p2, p3;
	BYTE res, b, drv = 0;
	UINT s1, s2, cnt, blen = sizeof Buff;
	static const BYTE ft[] = {0, 12, 16, 32};
	DWORD ofs = 0, sect = 0, blk[2];
	FATFS *fs;


	/* Configure WDT (disable) */
	WDG_LCK = 0; WDG_LCK = 0x1ACCE551; WDG_LCK = ~0x1ACCE551;
	WDG_CTL = 0;

	/* Configure I/O port */
	ADE = 0;	/* Disable all analog inputs */

	/* Enable SysTick timer in interval of 1 ms */
	SYST_RVR = 144000000 / 1000 - 1;
	SYST_CSR = 0x07;

#ifdef I2C_DEFINED
	/* Initialize I2C bus */
	i2c_init();
#endif

	/* Enable UART and attach it to xprintf module for console */
	uart3_init();
	xdev_out(uart3_putc);
	xdev_in(uart3_getc);

	/* Start Debug Monitor */
	xputs("\nFatFs test monitor for FRK-FM3 evaluation board (?:help)\n");
	xprintf("LFN=%s, CP=%u\n", FF_USE_LFN ? "Enabled" : "Disabled", FF_CODE_PAGE);

	for (;;) {
		xputc('>');
		xgets(Line, sizeof Line);

		ptr = Line;
		switch (*ptr++) {
		case '?' :	/* Show Command List */
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
			case 'd' :	/* dd [<pd#> <lba>] - Dump secrtor */
				if (!xatoi(&ptr, &p1)) {
					p1 = drv; p2 = sect;
				} else {
					if (!xatoi(&ptr, &p2)) break;
				}
				drv = (BYTE)p1; sect = p2;
				res = disk_read(drv, Buff, sect, 1);
				if (res) { xprintf("rc=%d\n", (WORD)res); break; }
				xprintf("PD#:&u LBA:%lu\n", drv, sect++);
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
				if (disk_ioctl((BYTE)p1, MMC_GET_TYPE, &b) == RES_OK)
					{ xprintf("Media type: %u\n", b); }
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

			case 'c' :	/* Disk ioctl */
				switch (*ptr++) {
				case 's' :	/* dcs <pd#> - CTRL_SYNC */
					if (!xatoi(&ptr, &p1)) break;
					xprintf("rc=%d\n", disk_ioctl((BYTE)p1, CTRL_SYNC, 0));
					break;
				case 'e' :	/* dce <pd#> <s.lba> <e.lba> - CTRL_ERASE_SECTOR */
					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, (long*)&blk[0]) || !xatoi(&ptr, (long*)&blk[1])) break;
					xprintf("rc=%d\n", disk_ioctl((BYTE)p1, CTRL_TRIM, blk));
					break;
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

			case 'r' :	/* br <pd#> <lba> [<count>] - Read disk into R/W buffer */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				if (!xatoi(&ptr, &p3)) p3 = 1;
				xprintf("rc=%u\n", (WORD)disk_read((BYTE)p1, Buff, p2, p3));
				break;

			case 'w' :	/* bw <pd#> <lba> [<count>] - Write R/W buffer into disk */
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

			case 'i' :	/* fi [<opt>]- Initialize logical drive */
				if (!xatoi(&ptr, &p2)) p2 = 0;
				put_rc(f_mount(&FatFs, "", (BYTE)p2));
				break;

			case 's' :	/* fs [<path>] - Show volume status */
				while (*ptr == ' ') ptr++;
				res = f_getfree(ptr, (DWORD*)&p1, &fs);
				if (res) { put_rc(res); break; }
				xprintf("FAT type = FAT%u\nBytes/Cluster = %lu\nNumber of FATs = %u\n"
						"Root DIR entries = %u\nSectors/FAT = %lu\nNumber of clusters = %lu\n"
						"Volume start (lba) = %lu\nFAT start (lba) = %lu\nDIR start (lba,clustor) = %lu\nData start (lba) = %lu\n",
						ft[fs->fs_type & 3], (DWORD)fs->csize * 512, fs->n_fats,
						fs->n_rootdir, fs->fsize, (DWORD)fs->n_fatent - 2,
						fs->volbase, fs->fatbase, fs->dirbase, fs->database
				);
#if FF_USE_LABEL
		if (f_getlabel(ptr, (char*)Buff, (DWORD*)&p2) == FR_OK) {
			xprintf(Buff[0] ? "Volume name is %s\n" : "No volume label\n", (char*)Buff);
			xprintf("Volume S/N is %04X-%04X\n", (DWORD)p2 >> 16, (DWORD)p2 & 0xFFFF);
		}
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
					xprintf("fptr=%lu(0x%lX)\n", f_tell(&File[0]), f_tell(&File[0]));
				break;

			case 'd' :	/* fd <len> - read and dump file from current fp */
				if (!xatoi(&ptr, &p1)) break;
				ofs = f_tell(&File[0]);
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

			case 'n' :	/* fn <org.name> <new.name> - Change file/dir name */
				while (*ptr == ' ') ptr++;
				ptr2 = strchr(ptr, ' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				while (*ptr2 == ' ') ptr2++;
				put_rc(f_rename(ptr, ptr2));
				break;

			case 'u' :	/* fu <name> - Unlink a file or dir */
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

			case 'a' :	/* fa <atrr> <mask> <name> - Change file/dir attribute */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				while (*ptr == ' ') ptr++;
				put_rc(f_chmod(ptr, p1, p2));
				break;

			case 't' :	/* ft <year> <month> <day> <hour> <min> <sec> <name> - Change timestamp */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.fdate = ((p1 - 1980) << 9) | ((p2 & 15) << 5) | (p3 & 31);
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.ftime = ((p1 & 31) << 11) | ((p2 & 63) << 5) | ((p3 >> 1) & 31);
				put_rc(f_utime(ptr, &Finfo));
				break;

			case 'x' : /* fx <src.name> <dst.name> - Copy file */
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
#endif
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
#endif
			case 'z' :	/* fz [<size>] - Change/Show R/W length for fr/fw/fx command */
				if (xatoi(&ptr, &p1) && p1 >= 1 && p1 <= (long)sizeof Buff)
					blen = p1;
				xprintf("blen=%u\n", blen);
				break;
			}
			break;
#ifdef SOUND_DEFINED
		case 'p' :	/* p <wavfile> - Play RIFF-WAV file */
			while (*ptr == ' ') ptr++;
			res = f_open(&File[0], ptr, FA_READ);
			if (res) {
				put_rc(res);
			} else {
				load_wav(&File[0], ptr, Buff, sizeof Buff);
				f_close(&File[0]);
			}
			break;
#endif
#ifdef I2C_DEFINED
		case 'i' :	/* Read/Write FRAM */
			switch (*ptr++) {
				volatile I2CCTRL i2c;
			case 'r' :	/* ir <f.addr> <count> - Read FRAM */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;	/* Get FRAM start address and byte count */
				i2c.sla = (0xA << 3) | ((p1 >> 8) & 7);	/* 7-bit slave address */
				i2c.cmd[0] = (uint8_t)p1; i2c.ncmd = 1; /* Command bytes following SLA+W */
				i2c.data = Buff; i2c.ndata = p2 % 2048;	/* Data read buffer and count */
				i2c.dir = I2C_READ; i2c.eotfunc = 0;	/* Data direction and call-back function */
				i2c_start(&i2c);						/* Start the I2C transaction */
				while (i2c.status == I2C_BUSY) ;		/* Wait for end of I2C transaction */
				xprintf("status=%u\n", i2c.status);		/* Put result */
				break;
			case 'w' :	/* iw <f.addr> <count> - Write FRAM */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;	/* Get FRAM start address and byte count */
				i2c.sla = (0xA << 3) | ((p1 >> 8) & 7);	/* 7-bit slave address */
				i2c.cmd[0] = (uint8_t)p1; i2c.ncmd = 1; /* Command bytes following SLA+W */
				i2c.data = Buff; i2c.ndata = p2 % 2048;	/* Data to write and count */
				i2c.dir = I2C_WRITE; i2c.eotfunc = 0;	/* Data direction and call-back function */
				i2c_start(&i2c);						/* Start the I2C transaction */
				while (i2c.status == I2C_BUSY) ;		/* Wait for end of I2C transaction */
				xprintf("status=%u\n", i2c.status);		/* Put result */
				break;
			}
			break;
#endif

		}
	}
}
