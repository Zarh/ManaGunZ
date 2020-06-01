/*----------------------------------------------------------------------*/
/* FatFs Module Sample Program / Renesas H8/300H       (C)ChaN, 2018    */
/*----------------------------------------------------------------------*/
/* Ev.Board: AKI-H8/3694F from Akizuki Denshi Tsusho Co.,Ltd            */
/* Console: SCI3 (N81 38400bps)                                         */
/* MMC/SDC: P5.0->CLK, P5.1->DI, P5.2->DO, P5.3->CS, P5.4->WP, P5.5->INS*/
/*----------------------------------------------------------------------*/


#include <string.h>
#include <machine.h>
#include "iodefine.h"
#include "sci.h"
#include "xprintf.h"
#include "ff.h"
#include "diskio.h"



DWORD AccSize;				/* Work register for fs command */
WORD AccFiles, AccDirs;
FILINFO Finfo;

char Line[80];				/* Console input buffer */
BYTE Buff[512];				/* Working buffer */

FATFS FatFs;		/* File system object */
FIL File[2];		/* File object */
DIR Dir;



/* 100Hz increment timer */
extern volatile WORD Timer;



/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */



static
void put_rc (FRESULT rc)
{
	const char *str =
		"OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
		"INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
		"INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
		"LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0" "INVALID_NAME\n";
	FRESULT i;

	for (i = 0; i != rc && *str; i++) {
		while (*str++) ;
	}
	xprintf("rc=%u FR_%s\n", (UINT)rc, str);
}


static
FRESULT scan_files (char* path)
{
	DIR dirs;
	FRESULT res;
	BYTE i;


	if ((res = f_opendir(&dirs, path)) == FR_OK) {
		i = strlen(path);
		while (((res = f_readdir(&dirs, &Finfo)) == FR_OK) && Finfo.fname[0]) {
			if (Finfo.fname[0] == '.') continue;
			if (Finfo.fattrib & AM_DIR) {
				AccDirs++;
				*(path+i) = '/'; strcpy(path+i+1, &Finfo.fname[0]);
				res = scan_files(path);
				*(path+i) = '\0';
				if (res != FR_OK) break;
			} else {
				AccFiles++;
				AccSize += Finfo.fsize;
			}
		}
	}

	return res;
}



/*-----------------------------------------------------------------------*/
/* Main                                                                  */


int main (void)
{
	BYTE res, drv = 0, b;
	const BYTE ft[] = {0,12,16,32};
	char *ptr, *ptr2;
	long p1, p2, p3;
	DWORD dw, ofs, sect = 0;
	WORD w1;
	UINT s1, s2, cnt;
	FATFS *fs;


	sci3_init();
	xdev_in(sci3_get);
	xdev_out(sci3_put);
	xputs("\nFatFs module test monitor for H8\n");

	for (;;) {
		xputc('>');
		xgets(Line, sizeof Line);

		ptr = Line;
		switch (*ptr++) {

		case 'd' :
			switch (*ptr++) {
			case 'd' :	/* dd [<pd#> <sector>] - Dump secrtor */
				if (xatoi(&ptr, &p1)) {
					if (!xatoi(&ptr, &p2)) break;
				} else {
					p1 = drv; p2 = sect;
				}
				res = disk_read((BYTE)p1, Buff, p2, 1);
				if (res) { xprintf("rc=%u\n", res); break; }
				xprintf("Drv:%u, Sector:%lu\n", (BYTE)p1, p2);
				sect = p1 + 1;
				for (ptr = (char*)Buff, ofs = 0; ofs < 0x200; ptr+=16, ofs+=16)
					put_dump((BYTE*)ptr, ofs, 16, DW_CHAR);
				break;

			case 'i' :	/* di <pd#> - Initialize disk */
				if (xatoi(&ptr, &p1))
					xprintf("rc=%u\n", disk_initialize((BYTE)p1));
				break;

			case 's' :	/* ds - Show disk status */
				if (!xatoi(&ptr, &p1)) break;
				if (disk_ioctl((BYTE)p1, GET_SECTOR_COUNT, &p2) == RES_OK)
					{ xprintf("Drive size: %lu sectors\n", p2); }
				if (disk_ioctl((BYTE)p1, GET_BLOCK_SIZE, &p2) == RES_OK)
					{ xprintf("Erase block size: %lu sectors\n", p2); }
				if (disk_ioctl((BYTE)p1, MMC_GET_TYPE, &b) == RES_OK)
					{ xprintf("MMC/SDC type: %u\n", b); }
				if (disk_ioctl((BYTE)p1, MMC_GET_CSD, Buff) == RES_OK)
					{ xputs("CSD:"); put_dump(Buff, 0, 16, DW_CHAR); }
				if (disk_ioctl((BYTE)p1, MMC_GET_CID, Buff) == RES_OK)
					{ xputs("CID:"); put_dump(Buff, 0, 16, DW_CHAR); }
				if (disk_ioctl((BYTE)p1, MMC_GET_OCR, Buff) == RES_OK)
					{ xputs("OCR:"); put_dump(Buff, 0, 4, DW_CHAR); }
				if (disk_ioctl((BYTE)p1, MMC_GET_SDSTAT, Buff) == RES_OK) {
					xputs("SD Status:");
					for (s1 = 0; s1 < 64; s1 += 16) put_dump(Buff+s1, s1, 16, DW_CHAR);
				}
				break;
			}
			break;

		case 'b' :
			switch (*ptr++) {
			case 'd' :	/* bd <addr> - Dump R/W buffer */
				if (!xatoi(&ptr, &p1)) break;
				for (ptr=(char*)(&Buff[p1]), ofs = p1, cnt = 32; cnt; cnt--, ptr+=16, ofs+=16)
					put_dump((BYTE*)ptr, ofs, 16, DW_CHAR);
				break;

			case 'e' :	/* be <addr> [<data>] ... - Edit R/W buffer */
				if (!xatoi(&ptr, &p1)) break;
				if (xatoi(&ptr, &p2)) {
					do {
						Buff[p1++] = (BYTE)p2;
					} while (xatoi(&ptr, &p2));
					break;
				}
				for (;;) {
					xprintf("%04X %02X-", (WORD)p1, Buff[p1]);
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

			case 'r' :	/* br <pd#> <sector> <n> - Read disk into R/W buffer */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				xprintf("rc=%u\n", disk_read((BYTE)p1, Buff, p2, (BYTE)p3));
				break;

			case 'w' :	/* bw <pd#> <sector> <n> - Write R/W buffer into disk */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				xprintf("rc=%u\n", disk_write((BYTE)p1, Buff, p2, (BYTE)p3));
				break;

			case 'f' :	/* bf <n> - Fill R/W buffer */
				if (!xatoi(&ptr, &p1)) break;
				memset(Buff, (BYTE)p1, sizeof Buff);
				break;

			}
			break;

		case 'f' :
			switch (*ptr++) {

			case 'i' :	/* fi [<mount>] - Force initialized the logical drive */
				if (!xatoi(&ptr, &p2)) p2 = 0;
				put_rc(f_mount(&FatFs, "", (BYTE)p2));
				break;

			case 's' :	/* fs [<path>] - Show file system status */
				while (*ptr == ' ') ptr++;
				res = f_getfree(ptr, (DWORD*)&p2, &fs);
				if (res) { put_rc(res); break; }
				xprintf("FAT type = FAT%u\nBytes/Cluster = %lu\nNumber of FATs = %u\n"
						"Root DIR entries = %u\nSectors/FAT = %lu\nNumber of clusters = %lu\n"
						"FAT start (lba) = %lu\nDIR start (lba,clustor) = %lu\nData start (lba) = %lu\n\n",
						ft[fs->fs_type & 3], fs->csize * 512UL, fs->n_fats,
						fs->n_rootdir, fs->fsize, fs->n_fatent - 2,
						fs->fatbase, fs->dirbase, fs->database
				);
#if FF_USE_LABEL
				res = f_getlabel(ptr, (char*)Buff, (DWORD*)&p1);
				if (res) { put_rc(res); break; }
				xprintf("Volume S/N is %04X-%04X\n", (WORD)((DWORD)p1 >> 16), (WORD)(p1 & 0xFFFF));
				xprintf(Buff[0] ? "Volume name is %s\n" : "No volume label\n", Buff);
#endif
				xputs("...");
				AccSize = AccFiles = AccDirs = 0;
				res = scan_files(ptr);
				if (res) { put_rc(res); break; }
				xprintf("\r%u files, %lu bytes.\n%u folders.\n"
						"%luKiB total disk space.\n%luKiB available.\n",
						AccFiles, AccSize, AccDirs,
						(fs->n_fatent - 2) * fs->csize / 2, p2 * fs->csize / 2
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
							Finfo.fsize, &(Finfo.fname[0]));
				}
				xprintf("%4u File(s),%10lu bytes\n%4u Dir(s)", s1, p1, s2);
				if (f_getfree(ptr, (DWORD*)&p1, &fs) == FR_OK)
					xprintf(", %10luKiB free\n", p1 * fs->csize / 2);
				break;

			case 'o' :	/* fo <mode> <file> - Open a file */
				if (!xatoi(&ptr, &p1)) break;
				while (*ptr == ' ') ptr++;
				res = f_open(&File[0], ptr, (BYTE)p1);
				put_rc(res);
				break;

			case 'c' :	/* fc - Close a file */
				res = f_close(&File[0]);
				put_rc(res);
				break;

			case 'e' :	/* fe - Seek file pointer */
				if (!xatoi(&ptr, &p1)) break;
				res = f_lseek(&File[0], p1);
				put_rc(res);
				if (res == FR_OK)
					xprintf("fptr = %lu(0x%lX)\n", f_tell(&File[0]), f_tell(&File[0]));
				break;

			case 'r' :	/* fr <len> - read file */
				if (!xatoi(&ptr, &p1)) break;
				p2 = 0;
				Timer = 0;
				while (p1) {
					if (p1 >= sizeof Buff)	{ cnt = sizeof Buff; p1 -= sizeof Buff; }
					else 			{ cnt = (WORD)p1; p1 = 0; }
					res = f_read(&File[0], Buff, cnt, &s2);
					if (res != FR_OK) { put_rc(res); break; }
					p2 += s2;
					if (cnt != s2) break;
				}
				s2 = Timer;
				xprintf("%lu bytes read with %lu bytes/sec.\n", p2, p2 * 100 / s2);
				break;

			case 'd' :	/* fd <len> - read and dump file from current fp */
				if (!xatoi(&ptr, &p1)) break;
				ofs = File[0].fptr;
				while (p1) {
					if (p1 >= 16)	{ cnt = 16; p1 -= 16; }
					else 			{ cnt = (WORD)p1; p1 = 0; }
					res = f_read(&File[0], Buff, cnt, &cnt);
					if (res != FR_OK) { put_rc(res); break; }
					if (!cnt) break;
					put_dump(Buff, ofs, cnt, DW_CHAR);
					ofs += 16;
				}
				break;

			case 'w' :	/* fw <len> <val> - write file */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				memset(Buff, (int)p2, sizeof Buff);
				p2 = 0;
				Timer = 0;
				while (p1) {
					if (p1 >= sizeof Buff)	{ cnt = sizeof Buff; p1 -= sizeof Buff; }
					else 			{ cnt = (WORD)p1; p1 = 0; }
					res = f_write(&File[0], Buff, cnt, &s2);
					if (res != FR_OK) { put_rc(res); break; }
					p2 += s2;
					if (cnt != s2) break;
				}
				s2 = Timer;
				xprintf("%lu bytes written with %lu bytes/sec.\n", p2, p2 * 100 / s2);
				break;

			case 'v' :	/* fv - Truncate file */
				put_rc(f_truncate(&File[0]));
				break;

			case 'n' :	/* fn <old_name> <new_name> - Change file/dir name */
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

			case 'k' :	/* fk <name> - Create a directory */
				while (*ptr == ' ') ptr++;
				put_rc(f_mkdir(ptr));
				break;
#if FF_USE_CHMOD
			case 'a' :	/* fa <atrr> <mask> <name> - Change file/dir attribute */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				while (*ptr == ' ') ptr++;
				put_rc(f_chmod(ptr, p1, p2));
				break;

			case 't' :	/* ft <year> <month> <day> <hour> <min> <sec> <name> */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.fdate = ((p1 - 1980) << 9) | ((p2 & 15) << 5) | (p3 & 31);
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.ftime = ((p1 & 31) << 11) | ((p2 & 63) << 5) | ((p3 >> 1) & 31);
				put_rc(f_utime(ptr, &Finfo));
				break;
#endif
			case 'x' : /* fx <src_name> <dst_name> - Copy file */
				while (*ptr == ' ') ptr++;
				ptr2 = strchr(ptr, ' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				if (!*ptr2) break;
				xprintf("Opening \"%s\"", ptr);
				res = f_open(&File[0], ptr, FA_OPEN_EXISTING | FA_READ);
				if (res) {
					put_rc(res);
					break;
				}
				xprintf("\nCreating \"%s\"", ptr2);
				res = f_open(&File[1], ptr2, FA_CREATE_ALWAYS | FA_WRITE);
				if (res) {
					put_rc(res);
					f_close(&File[0]);
					break;
				}
				xprintf("\nCopying...");
				p1 = 0;
				for (;;) {
					res = f_read(&File[0], Buff, sizeof Buff, &s1);
					if (res || s1 == 0) break;   /* error or eof */
					res = f_write(&File[1], Buff, s1, &s2);
					p1 += s2;
					if (res || s2 < s1) break;   /* error or disk full */
				}
				xprintf("\n%lu bytes copied.\n", p1);
				f_close(&File[0]);
				f_close(&File[1]);
				break;
#if FF_FS_RPATH >= 1
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
			}
			break;

		case '?' :	/* Show Command List */
			xputs(
				"[Disk contorls]\n"
				" di <pd#> - Initialize disk\n"
				" dd [<pd#> <sect>] - Dump a secrtor\n"
				" ds <pd#> - Show disk status\n"
				"[Buffer controls]\n"
				" bd <ofs> - Dump working buffer\n"
				" be <ofs> [<data>] ... - Edit working buffer\n"
				" br <pd#> <sect> [<num>] - Read disk into working buffer\n"
				" bw <pd#> <sect> [<num>] - Write working buffer into disk\n"
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
				" fn <org name> <new name> - Rename an object\n"
				" fu <obj name> - Unlink an object\n"
				" fv - Truncate the file at current fp\n"
				" fk <dir name> - Create a directory\n"
				" fa <atrr> <mask> <object name> - Change object attribute\n"
				" ft <year> <month> <day> <hour> <min> <sec> <object name> - Change timestamp of an object\n"
				" fx <src file> <dst file> - Copy a file\n"
				" fg <path> - Change current directory\n"
				" fq - Show current directory\n"
				" fm [<fs type> [<au size> [<align> [<n_fats> [<n_root>]]]]] - Create filesystem\n"
				"\n"
			);
		}
	}

}


