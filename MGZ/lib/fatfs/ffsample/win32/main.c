/*------------------------------------------------------------------------/
/  The Main Development Bench of FatFs Module
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2018, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/


#include <string.h>
#include <stdio.h>
#include <locale.h>
#include "ff.h"
#include "diskio.h"

int assign_drives (void);	/* Initialization of low level I/O module */


#if FF_MULTI_PARTITION

/* This is an example of volume - partition mapping table */
PARTITION VolToPart[FF_VOLUMES] = {
	{0, 1},	/* "0:" ==> 1st partition on PD#0 */
	{0, 2},	/* "1:" ==> 2nd partition on PD#0 */
	{0, 3},	/* "2:" ==> 3rd partition on PD#0 */
	{1, 0},	/* "3:" ==> PD#1 */
	{2, 0},	/* "4:" ==> PD#2 */
	{3, 0},	/* "5:" ==> PD#3 */
	{4, 0},	/* "6:" ==> PD#4 */
	{5, 0}	/* "7:" ==> PD#5 */
};
#endif


#define LINE_LEN 1024


/*---------------------------------------------------------*/
/* Work Area                                               */
/*---------------------------------------------------------*/

LONGLONG AccSize;			/* Work register for scan_files() */
WORD AccFiles, AccDirs;
FILINFO Finfo;

WCHAR Line[LINE_LEN];		/* Console input/output buffer */
HANDLE hConOut, hConIn;
WORD CodePage = FF_CODE_PAGE;

FATFS FatFs[FF_VOLUMES];	/* Filesystem object for logical drive */
BYTE Buff[262144];			/* Working buffer */

#if FF_USE_FASTSEEK
DWORD SeekTbl[16];			/* Link map table for fast seek feature */
#endif



/*-------------------------------------------------------------------*/
/* User Provided RTC Function for FatFs module                       */
/*-------------------------------------------------------------------*/
/* This is a real time clock service to be called from FatFs module. */
/* This function is needed when FF_FS_READONLY == 0 and FF_FS_NORTC == 0 */

DWORD get_fattime (void)
{
	SYSTEMTIME tm;

	/* Get local time */
	GetLocalTime(&tm);

	/* Pack date and time into a DWORD variable */
	return    ((DWORD)(tm.wYear - 1980) << 25)
			| ((DWORD)tm.wMonth << 21)
			| ((DWORD)tm.wDay << 16)
			| (WORD)(tm.wHour << 11)
			| (WORD)(tm.wMinute << 5)
			| (WORD)(tm.wSecond >> 1);
}




/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */


int xatoll (		/* 0:Failed, 1:Successful */
	WCHAR **str,	/* Pointer to pointer to the string */
	QWORD *res		/* Pointer to a valiable to store the value */
)
{
	QWORD val;
	UINT r;
	WCHAR c;


	*res = 0;
	while ((c = **str) == L' ') (*str)++;	/* Skip leading spaces */

	if (c == L'0') {
		c = *(++(*str));
		switch (c) {
		case L'x':		/* hexdecimal */
			r = 16; c = *(++(*str));
			break;
		case L'b':		/* binary */
			r = 2; c = *(++(*str));
			break;
		default:
			if (c <= L' ') return 1;	/* single zero */
			if (c < L'0' || c > L'9') return 0;	/* invalid char */
			r = 8;		/* octal */
		}
	} else {
		if (c < L'0' || c > L'9') return 0;	/* EOL or invalid char */
		r = 10;			/* decimal */
	}

	val = 0;
	while (c > L' ') {
		if (c >= L'a') c -= 0x20;
		c -= L'0';
		if (c >= 17) {
			c -= 7;
			if (c <= 9) return 0;	/* invalid char */
		}
		if (c >= r) return 0;		/* invalid char for current radix */
		val = val * r + c;
		c = *(++(*str));
	}

	*res = val;
	return 1;
}


int xatoi (
	WCHAR **str,	/* Pointer to pointer to the string */
	DWORD *res		/* Pointer to a valiable to store the value */
)
{
	QWORD d;


	*res = 0;
	if (!xatoll(str, &d)) return 0;
	*res = (DWORD)d;
	return 1;
}


void zputc (
	WCHAR c
)
{
	DWORD wc;

	WriteConsoleW(hConOut, &c, 1, &wc, 0);
}


void zprintf (
	const WCHAR *fmt,
	...
)
{
	UINT r, i, j, w, f;
	unsigned __int64 v;
	WCHAR s[32], c, d, *p;
	va_list arp;

	va_start(arp, fmt);

	for (;;) {
		c = *fmt++;					/* Get a char */
		if (!c) break;				/* End of format? */
		if (c != L'%') {			/* Pass through it if not a % sequense */
			zputc(c); continue;
		}
		f = 0;
		c = *fmt++;					/* Get first char of the sequense */
		if (c == L'0') {			/* Flag: '0' padded */
			f = 1; c = *fmt++;
		} else {
			if (c == '-') {			/* Flag: left justified */
				f = 2; c = *fmt++;
			}
		}
		for (w = 0; c >= L'0' && c <= L'9'; c = *fmt++)	/* Minimum width */
			w = w * 10 + c - L'0';
		if (c == L'l' || c == L'L') {	/* Prefix: Size is long int */
			f |= 4; c = *fmt++;
			if (c == L'l' || c == L'L') {	/* Prefix: Size is long long int */
				f |= 8; c = *fmt++;
			}
		}
		if (!c) break;				/* End of format? */
		d = c;
		if (d >= L'a') d -= 0x20;
		switch (d) {				/* Type is... */
		case L'S' :					/* String */
			p = va_arg(arp, WCHAR*);
			for (j = 0; p[j]; j++) ;
			while (!(f & 2) && j++ < w) zputc(L' ');
			while (*p) zputc(*p++);
			while (j++ < w) zputc(L' ');
			continue;
		case L'C' :					/* Character */
			zputc((WCHAR)va_arg(arp, int)); continue;
		case L'B' :					/* Binary */
			r = 2; break;
		case L'O' :					/* Octal */
			r = 8; break;
		case L'D' :					/* Signed decimal */
		case L'U' :					/* Unsigned decimal */
			r = 10; break;
		case L'X' :					/* Hexdecimal */
			r = 16; break;
		default:					/* Unknown type (passthrough) */
			zputc(c); continue;
		}

		/* Get an argument and put it in numeral */
		if (f & 8) {
			v = va_arg(arp, __int64);
		} else {
			if (f & 4) {
				v = va_arg(arp, long);
			} else {
				v = (d == L'D') ? (long)va_arg(arp, int) : (long)va_arg(arp, unsigned int);
			}
		}
		if (d == L'D' && (v & 0x8000000000000000)) {
			v = 0 - v;
			f |= 16;
		}
		i = 0;
		do {
			d = (WCHAR)(v % r); v /= r;
			if (d > 9) d += (c == L'x') ? 0x27 : 0x07;
			s[i++] = d + '0';
		} while (v && i < 32);
		if (f & 16) s[i++] = L'-';
		j = i; d = (f & 1) ? L'0' : L' ';
		while (!(f & 2) && j++ < w) zputc(d);
		do zputc(s[--i]); while(i);
		while (j++ < w) zputc(L' ');
	}

	va_end(arp);

}


void get_line (
	WCHAR* buf,
	UINT len
)
{
	UINT i = 0;
	DWORD n;


	for (;;) {
		ReadConsoleW(hConIn, &buf[i], 1, &n, 0);
		if (buf[i] == L'\b') {
			if (i) i--;
			continue;
		}
		if (buf[i] == L'\r') {
			buf[i] = 0;
			break;
		}
		if ((UINT)buf[i] >= L' ' && i + n < len) i += n;
	}
}


WCHAR* ts2ws (const TCHAR* str)
{
	static WCHAR rstr[2][512];
	static int ri;
#if FF_USE_LFN && FF_LFN_UNICODE == 3
	int di;
	TCHAR dc;
#endif

	ri = (ri + 1) % 2;
	rstr[ri][0] = 0;
#if FF_USE_LFN && FF_LFN_UNICODE == 1	/* UTF16 to UTF16 */
	wcscpy(rstr[ri], str);
#elif FF_USE_LFN && FF_LFN_UNICODE == 2	/* UTF8 to UTF16 */
	MultiByteToWideChar(CP_UTF8, 0, str, -1, rstr[ri], 512);
#elif FF_USE_LFN && FF_LFN_UNICODE == 3	/* UTF32 to UTF16 */
	for (di = 0; *str && di < 512 - 2; ) {
		dc = *str++;
		if (dc >= 0x10000) {
			dc -= 0x10000;
			rstr[ri][di++] = (WCHAR)((dc >> 10) + 0xD800);
			dc = (dc & 0x3FF) + 0xDC00;
		}
		rstr[ri][di++] = (WCHAR)dc;
	}
	rstr[ri][di] = 0;
#else	/* ANSI/OEM to UTF16 */
	MultiByteToWideChar(CodePage, 0, str, -1, rstr[ri], 512);
#endif
	return rstr[ri];
}


TCHAR* ws2ts (const WCHAR* str)
{
	static TCHAR rstr[2][1024];
	static int ri;
#if FF_USE_LFN && FF_LFN_UNICODE == 3
	int di;
	TCHAR dc, ls;
#endif

	ri = (ri + 1) % 2;
	rstr[ri][0] = 0;
#if FF_USE_LFN && FF_LFN_UNICODE == 1	/* UTF16 to UTF16 */
	wcscpy(rstr[ri], str);
#elif FF_USE_LFN && FF_LFN_UNICODE == 2	/* UTF16 to UTF8 */
	WideCharToMultiByte(CP_UTF8, 0, str, -1, rstr[ri], 512, 0, 0);
#elif FF_USE_LFN && FF_LFN_UNICODE == 3	/* UTF16 to UTF32 */
	for (di = 0; *str && di < 512 - 1; ) {
		dc = *str++;
		if (dc >= 0xD800 && dc <= 0xDBFF) {
			ls = *str;
			if (ls >= 0xDC00 && ls <= 0xDFFF) {
				str++;
				dc = ((dc - 0xD800) << 10) + (ls - 0xDC00) + 0x10000;
			} else {
				continue;
			}
		}
		rstr[ri][di++] = dc;
	}
	rstr[ri][di] = 0;
#else	/* UTF16 to ANSI/OEM */
	WideCharToMultiByte(CodePage, WC_NO_BEST_FIT_CHARS, str, -1, rstr[ri], 512, 0, 0);
#endif
	return rstr[ri];
}




/*----------------------------------------------*/
/* Dump a block of byte array                   */

void put_dump (
	const BYTE* buff,	/* Pointer to the byte array to be dumped */
	LBA_t addr,			/* Heading address value */
	int cnt				/* Number of bytes to be dumped */
)
{
	int i;


	zprintf(FF_LBA64 ? L"%08llX:" : L"%08X:", addr);

	for (i = 0; i < cnt; i++) {
		zprintf(L" %02X", buff[i]);
	}

	zputc(L' ');
	for (i = 0; i < cnt; i++) {
		zputc((buff[i] >= ' ' && buff[i] <= '~') ? buff[i] : '.');
	}

	zputc(L'\n');
}



UINT forward (
	const BYTE* buf,
	UINT btf
)
{
	UINT i;


	if (btf) {	/* Transfer call? */
		for (i = 0; i < btf; i++) zputc((TCHAR)buf[i]);
		return btf;
	} else {	/* Sens call */
		return 1;
	}
}




FRESULT scan_files (
	WCHAR* path		/* Pointer to the path name working buffer */
)
{
	DIR dir;
	FRESULT res;
	int i;


	if ((res = f_opendir(&dir, ws2ts(path))) == FR_OK) {
		i = wcslen(path);
		while (((res = f_readdir(&dir, &Finfo)) == FR_OK) && Finfo.fname[0]) {
			if (Finfo.fattrib & AM_DIR) {
				AccDirs++;
				*(path+i) = L'/'; wcscpy(path+i+1, ts2ws(Finfo.fname));
				res = scan_files(path);
				*(path+i) = L'\0';
				if (res != FR_OK) break;
			} else {
				AccFiles++;
				AccSize += Finfo.fsize;
			}
		}
		f_closedir(&dir);
	}

	return res;
}



void put_rc (FRESULT rc)
{
	const WCHAR *p =
		L"OK\0DISK_ERR\0INT_ERR\0NOT_READY\0NO_FILE\0NO_PATH\0INVALID_NAME\0"
		L"DENIED\0EXIST\0INVALID_OBJECT\0WRITE_PROTECTED\0INVALID_DRIVE\0"
		L"NOT_ENABLED\0NO_FILE_SYSTEM\0MKFS_ABORTED\0TIMEOUT\0LOCKED\0"
		L"NOT_ENOUGH_CORE\0TOO_MANY_OPEN_FILES\0INVALID_PARAMETER\0";
	FRESULT i;

	for (i = 0; i != rc && *p; i++) {
		while(*p++) ;
	}
	zprintf(L"rc=%u FR_%s\n", (UINT)rc, p);
}



const WCHAR HelpStr[] = {
		L"[Disk contorls]\n"
		L" di <pd#> - Initialize disk\n"
		L" dd [<pd#> <sect>] - Dump a secrtor\n"
		L" ds <pd#> - Show disk status\n"
		L" dl <file> - Load FAT image into RAM disk (pd#0)\n"
		L"[Buffer contorls]\n"
		L" bd <ofs> - Dump working buffer\n"
		L" be <ofs> [<data>] ... - Edit working buffer\n"
		L" br <pd#> <sect> <count> - Read disk into working buffer\n"
		L" bw <pd#> <sect> <count> - Write working buffer into disk\n"
		L" bf <val> - Fill working buffer\n"
		L"[Filesystem contorls]\n"
		L" fi <ld#> [<opt>] - Force initialized the volume\n"
		L" fs [<path>] - Show volume status\n"
		L" fl [<path>] - Show a directory\n"
		L" fL <path> <pat> - Find a directory\n"
		L" fo <mode> <file> - Open a file\n"
		L" fc - Close the file\n"
		L" fe <ofs> - Move fp in normal seek\n"
		L" fE <ofs> - Move fp in fast seek or Create link table\n"
		L" ff <len> - Forward file data to the console\n"
		L" fh <fsz> <opt> - Allocate a contiguous block to the file\n"
		L" fd <len> - Read and dump the file\n"
		L" fr <len> - Read the file\n"
		L" fw <len> <val> - Write to the file\n"
		L" fn <object name> <new name> - Rename an object\n"
		L" fu <object name> - Unlink an object\n"
		L" fv - Truncate the file at current fp\n"
		L" fk <dir name> - Create a directory\n"
		L" fa <atrr> <mask> <object name> - Change object attribute\n"
		L" ft <year> <month> <day> <hour> <min> <sec> <object name> - Change timestamp of an object\n"
		L" fx <src file> <dst file> - Copy a file\n"
		L" fg <path> - Change current directory\n"
		L" fj <path> - Change current drive\n"
		L" fq - Show current directory path\n"
		L" fb <name> - Set volume label\n"
		L" fm <ld#> [<fs type> [<au size> [<align> [<N fats> [<N root>]]]]] - Create FAT volume\n"
		L" fp <pd#> <p1 size> <p2 size> ... - Divide physical drive\n"
		L" fz [<ld#> <pd#> <pt#>] - Map logical drive to partition\n"
		L" p <cp#> - Set code page\n"
		L"\n"
	};



int set_console_size (
	HANDLE hcon,
	int width,
	int height,
	int bline
)
{
	COORD dim;
	SMALL_RECT rect;


	dim.X = (SHORT)width; dim.Y = (SHORT)bline;
	rect.Top = rect.Left = 0; rect.Right = (SHORT)(width - 1); rect.Bottom = (SHORT)(height - 1);

	if (SetConsoleScreenBufferSize(hcon, dim) && SetConsoleWindowInfo(hcon, TRUE, &rect) ) return 1;

	return 0;
}




/*-----------------------------------------------------------------------*/
/* Main                                                                  */
/*-----------------------------------------------------------------------*/


int main (void)
{
	WCHAR *ptr, *ptr2, pool[64];
	TCHAR tpool[128];
	DWORD p1, p2, p3;
	QWORD px, q1;
	BYTE *buf;
	UINT s1, s2, cnt;
	WORD w;
	DWORD dw, ofs = 0, drv = 0;
	LBA_t ns, sect = 0;
	const WCHAR *ft[] = {L"", L"FAT12", L"FAT16", L"FAT32", L"exFAT"};
	const WCHAR *uni[] = {L"ANSI/OEM", L"UTF-16", L"UTF-8", L"UTF-32"};
	HANDLE h;
	FRESULT fr;
	DRESULT dr;
	FATFS *fs;				/* Pointer to file system object */
	DIR dir;				/* Directory object */
	FIL file[2];			/* File objects */


	hConIn = GetStdHandle(STD_INPUT_HANDLE);
	hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
	set_console_size(hConOut, 100, 35, 500);

#if FF_CODE_PAGE != 0
	if (GetConsoleCP() != FF_CODE_PAGE) {
		if (!SetConsoleCP(FF_CODE_PAGE) || !SetConsoleOutputCP(FF_CODE_PAGE)) {
			zprintf(L"Error: Failed to change the console code page.\n");
		}
	}
#else
	w = GetConsoleCP();
	zprintf(L"f_setcp(%u)\n", w);
	put_rc(f_setcp(w));
#endif

	swprintf(pool, 64, L"FatFs debug console (%s, CP%u, %s)", FF_USE_LFN ? L"LFN" : L"SFN", FF_CODE_PAGE, uni[FF_LFN_UNICODE]);
	SetConsoleTitleW(pool);
	zprintf(L"FatFs module test monitor (%s, CP%u, %s)\n\n", FF_USE_LFN ? L"LFN" : L"SFN", FF_CODE_PAGE, uni[FF_LFN_UNICODE]);

	assign_drives();	/* Find physical drives on the PC */
#if FF_MULTI_PARTITION
	zprintf(L"\nMultiple partition is enabled. Logical drives are associated with the patitions as follows:\n");
	for (cnt = 0; cnt < sizeof VolToPart / sizeof (PARTITION); cnt++) {
		if (VolToPart[cnt].pt == 0) {
			zprintf(L"\"%u:\" ==> PD#%u\n", cnt, VolToPart[cnt].pd);
		} else {
			zprintf(L"\"%u:\" ==> PT#%u in PD#%u\n", cnt, VolToPart[cnt].pt, VolToPart[cnt].pd);
		}
	}
	zprintf(L"\n");
#else
	zprintf(L"\nMultiple partition is disabled.\nEach logical drive is associated with the same physical drive number.\n\n");
#endif


	for (;;) {
		zprintf(L">");
		get_line(Line, LINE_LEN);
		ptr = Line;

		switch (*ptr++) {	/* Branch by primary command character */

		case L'q' :	/* Exit program */
			return 0;

		case L'?':		/* Show usage */
			zprintf(HelpStr);
			break;

		case L'T' :

			/* Quick test space */

			break;

		case L'd' :	/* Disk I/O command */
			switch (*ptr++) {	/* Branch by secondary command character */
			case L'd' :	/* dd [<pd#> <sect>] - Dump a secrtor */
				if (!xatoi(&ptr, &p1)) {
					p1 = drv; q1 = sect;
				} else {
					if (!xatoll(&ptr, &q1)) break;
				}
				dr = disk_read((BYTE)p1, Buff, (LBA_t)q1, 1);
				if (dr) { zprintf(L"rc=%d\n", (WORD)dr); break; }
				zprintf(L"PD#:%u LBA:%llu\n", p1, q1);
				if (disk_ioctl((BYTE)p1, GET_SECTOR_SIZE, &w) != RES_OK) break;
				sect = (LBA_t)q1 + 1; drv = p1;
				for (buf = Buff, ofs = 0; ofs < w; buf += 16, ofs += 16) {
					put_dump(buf, ofs, 16);
				}
				break;

			case L'i' :	/* di <pd#> - Initialize physical drive */
				if (!xatoi(&ptr, &p1)) break;
				dr = disk_initialize((BYTE)p1);
				zprintf(L"rc=%d\n", dr);
				if (disk_ioctl((BYTE)p1, GET_SECTOR_SIZE, &w) == RES_OK) {
					zprintf(L"Sector size = %u\n", w);
				}
				if (disk_ioctl((BYTE)p1, GET_SECTOR_COUNT, &ns) == RES_OK) {
					zprintf(L"Number of sectors = %llu\n", (QWORD)ns);
				}
				break;

			case L'l' :	/* dl <image file> - Load image of a FAT volume into RAM disk */
				while (*ptr == ' ') ptr++;
				if (disk_ioctl(0, 200, ptr) == RES_OK) {
					zprintf(L"Ok\n");
				}
				break;

			}
			break;

		case L'b' :	/* Buffer control command */
			switch (*ptr++) {	/* Branch by secondary command character */
			case L'd' :	/* bd <ofs> - Dump Buff[] */
				if (!xatoi(&ptr, &p1)) break;
				for (buf = &Buff[p1], ofs = p1, cnt = 32; cnt; cnt--, buf += 16, ofs += 16) {
					put_dump(buf, ofs, 16);
				}
				break;

			case L'e' :	/* be <ofs> [<data>] ... - Edit Buff[] */
				if (!xatoi(&ptr, &p1)) break;
				if (xatoi(&ptr, &p2)) {
					do {
						Buff[p1++] = (BYTE)p2;
					} while (xatoi(&ptr, &p2));
					break;
				}
				for (;;) {
					zprintf(L"%04X %02X-", (WORD)(p1), (WORD)Buff[p1]);
					get_line(Line, LINE_LEN);
					ptr = Line;
					if (*ptr == '.') break;
					if (*ptr < ' ') { p1++; continue; }
					if (xatoi(&ptr, &p2)) {
						Buff[p1++] = (BYTE)p2;
					} else {
						zprintf(L"???\n");
					}
				}
				break;

			case L'r' :	/* br <pd#> <sector> <count> - Read disk into Buff[] */
				if (!xatoi(&ptr, &p1) || !xatoll(&ptr, &q1) || !xatoi(&ptr, &p3)) break;
				zprintf(L"rc=%u\n", disk_read((BYTE)p1, Buff, (LBA_t)q1, p3));
				break;

			case L'w' :	/* bw <pd#> <sect> <count> - Write Buff[] into disk */
				if (!xatoi(&ptr, &p1) || !xatoll(&ptr, &q1) || !xatoi(&ptr, &p3)) break;
				zprintf(L"rc=%u\n", disk_write((BYTE)p1, Buff, (LBA_t)q1, p3));
				break;

			case L'f' :	/* bf <n> - Fill Buff[] */
				if (!xatoi(&ptr, &p1)) break;
				memset(Buff, p1, sizeof Buff);
				break;

			case L's' :	/* bs - Save Buff[] */
				while (*ptr == ' ') ptr++;
				h = CreateFileW(L"Buff.bin", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
				if (h != INVALID_HANDLE_VALUE) {
					WriteFile(h, Buff, sizeof Buff, &dw, 0);
					CloseHandle(h);
					zprintf(L"Ok.\n");
				}
				break;

			}
			break;

		case L'f' :	/* FatFs test command */
			switch (*ptr++) {	/* Branch by secondary command character */

			case L'i' :	/* fi <pd#> <opt> <path> - Force initialized the logical drive */
				if (!xatoi(&ptr, &p1) || (UINT)p1 > 9) break;
				if (!xatoi(&ptr, &p2)) p2 = 0;
				swprintf(ptr, LINE_LEN, L"%d:", p1);
				put_rc(f_mount(&FatFs[p1], ws2ts(ptr), (BYTE)p2));
				break;

			case L's' :	/* fs [<path>] - Show logical drive status */
				while (*ptr == ' ') ptr++;
				ptr2 = ptr;
#if FF_FS_READONLY
				fr = f_opendir(&dir, ts2ws(ptr));
				if (fr == FR_OK) {
					fs = dir.obj.fs;
					f_closedir(&dir);
				}
#else
				fr = f_getfree(ws2ts(ptr), (DWORD*)&p1, &fs);
#endif
				if (fr) { put_rc(fr); break; }
				zprintf(L"FAT type = %s\n", ft[fs->fs_type]);
				zprintf(L"Cluster size = %lu bytes\n",
#if FF_MAX_SS != FF_MIN_SS
					(DWORD)fs->csize * fs->ssize);
#else
					(DWORD)fs->csize * FF_MAX_SS);
#endif
				if (fs->fs_type < FS_FAT32) zprintf(L"Root DIR entries = %u\n", fs->n_rootdir);
				zprintf(L"Sectors/FAT = %lu\nNumber of FATs = %u\nNumber of clusters = %lu\nVolume start sector = %llu\nFAT start sector = %llu\nRoot DIR start %s = %llu\nData start sector = %llu\n\n",
					fs->fsize, fs->n_fats, fs->n_fatent - 2, (QWORD)fs->volbase, (QWORD)fs->fatbase, fs->fs_type >= FS_FAT32 ? L"cluster" : L"sector", (QWORD)fs->dirbase, (QWORD)fs->database);
#if FF_USE_LABEL
				fr = f_getlabel(ws2ts(ptr2), tpool, &dw);
				if (fr) { put_rc(fr); break; }
				if (tpool[0]) {
					zprintf(L"Volume name is %s\n", ts2ws(tpool));
				} else {
					zprintf(L"No volume label\n");
				}
				zprintf(L"Volume S/N is %04X-%04X\n", dw >> 16, dw & 0xFFFF);
#endif
				zprintf(L"...");
				AccSize = AccFiles = AccDirs = 0;
				fr = scan_files(ptr);
				if (fr) { put_rc(fr); break; }
				p2 = (fs->n_fatent - 2) * fs->csize;
				p3 = p1 * fs->csize;
#if FF_MAX_SS != FF_MIN_SS
				p2 *= fs->ssize / 512;
				p3 *= fs->ssize / 512;
#endif
				p2 /= 2;
				p3 /= 2;
				zprintf(L"\r%u files, %llu bytes.\n%u folders.\n%lu KiB total disk space.\n",
						AccFiles, AccSize, AccDirs, p2);
#if !FF_FS_READONLY
				zprintf(L"%lu KiB available.\n", p3);
#endif
				break;

			case L'l' :	/* fl [<path>] - Directory listing */
				while (*ptr == L' ') ptr++;
				fr = f_opendir(&dir, ws2ts(ptr));
				if (fr) { put_rc(fr); break; }
				AccSize = s1 = s2 = 0;
				for(;;) {
					fr = f_readdir(&dir, &Finfo);
					if ((fr != FR_OK) || !Finfo.fname[0]) break;
					if (Finfo.fattrib & AM_DIR) {
						s2++;
					} else {
						s1++; AccSize += Finfo.fsize;
					}
					zprintf(L"%c%c%c%c%c %u/%02u/%02u %02u:%02u %10llu  ",
							(Finfo.fattrib & AM_DIR) ? L'D' : L'-',
							(Finfo.fattrib & AM_RDO) ? L'R' : L'-',
							(Finfo.fattrib & AM_HID) ? L'H' : L'-',
							(Finfo.fattrib & AM_SYS) ? L'S' : L'-',
							(Finfo.fattrib & AM_ARC) ? L'A' : L'-',
							(Finfo.fdate >> 9) + 1980, (Finfo.fdate >> 5) & 15, Finfo.fdate & 31,
							(Finfo.ftime >> 11), (Finfo.ftime >> 5) & 63, (QWORD)Finfo.fsize);
#if FF_USE_LFN && FF_USE_FIND == 2
					zprintf(L"%-14s", ts2ws(Finfo.altname));
#endif
					zprintf(L"%s\n", ts2ws(Finfo.fname));
				}
				f_closedir(&dir);
				if (fr == FR_OK) {
					zprintf(L"%4u File(s),%11llu bytes total\n%4u Dir(s)", s1, AccSize, s2);
#if !FF_FS_READONLY
					fr = f_getfree(ws2ts(ptr), (DWORD*)&p1, &fs);
					if (fr == FR_OK) {
						zprintf(L",%12llu bytes free", (QWORD)p1 * fs->csize * 512);
					}
#endif
					zprintf(L"\n");
				} else {
					put_rc(fr);
				}
				break;
#if FF_USE_FIND
			case L'L' :	/* fL <path> <pattern> - Directory search */
				while (*ptr == L' ') ptr++;
				ptr2 = ptr;
				while (*ptr != L' ') ptr++;
				*ptr++ = 0;
				fr = f_findfirst(&dir, &Finfo, ws2ts(ptr2), ws2ts(ptr));
				while (fr == FR_OK && Finfo.fname[0]) {
#if FF_USE_LFN && FF_USE_FIND == 2
					zprintf(L"%-12s  ", ts2ws(Finfo.altname));
#endif
					zprintf(L"%s\n", ts2ws(Finfo.fname));
					fr = f_findnext(&dir, &Finfo);
				}
				if (fr) put_rc(fr);

				f_closedir(&dir);
				break;
#endif
			case L'o' :	/* fo <mode> <file> - Open a file */
				if (!xatoi(&ptr, &p1)) break;
				while (*ptr == L' ') ptr++;
				fr = f_open(&file[0], ws2ts(ptr), (BYTE)p1);
				put_rc(fr);
				break;

			case L'c' :	/* fc - Close a file */
				put_rc(f_close(&file[0]));
				break;

			case L'r' :	/* fr <len> - read file */
				if (!xatoi(&ptr, &p1)) break;
				p2 =0;
				while (p1) {
					if (p1 >= sizeof Buff) {
						cnt = sizeof Buff; p1 -= sizeof Buff;
					} else {
						cnt = p1; p1 = 0;
					}
					fr = f_read(&file[0], Buff, cnt, &s2);
					if (fr != FR_OK) { put_rc(fr); break; }
					p2 += s2;
					if (cnt != s2) break;
				}
				zprintf(L"%lu bytes read.\n", p2);
				break;

			case L'd' :	/* fd <len> - read and dump file from current fp */
				if (!xatoi(&ptr, &p1)) p1 = 128;
				ofs = (DWORD)file[0].fptr;
				while (p1) {
					if (p1 >= 16) { cnt = 16; p1 -= 16; }
					else 		  { cnt = p1; p1 = 0; }
					fr = f_read(&file[0], Buff, cnt, &cnt);
					if (fr != FR_OK) { put_rc(fr); break; }
					if (!cnt) break;
					put_dump(Buff, ofs, cnt);
					ofs += 16;
				}
				break;

			case L'e' :	/* fe <ofs> - Seek file pointer */
				if (!xatoll(&ptr, &px)) break;
				fr = f_lseek(&file[0], (FSIZE_t)px);
				put_rc(fr);
				if (fr == FR_OK) {
					zprintf(L"fptr = %llu(0x%llX)\n", (QWORD)file[0].fptr, (QWORD)file[0].fptr);
				}
				break;
#if FF_USE_FASTSEEK
			case L'E' :	/* fE - Enable fast seek and initialize cluster link map table */
				file[0].cltbl = SeekTbl;			/* Enable fast seek (set address of buffer) */
				SeekTbl[0] = sizeof SeekTbl / sizeof *SeekTbl;	/* Buffer size */
				fr = f_lseek(&file[0], CREATE_LINKMAP);	/* Create link map table */
				put_rc(fr);
				if (fr == FR_OK) {
					zprintf((SeekTbl[0] > 4) ? L"fragmented in %d.\n" : L"contiguous.\n", SeekTbl[0] / 2 - 1);
					zprintf(L"%u items used.\n", SeekTbl[0]);

				}
				if (fr == FR_NOT_ENOUGH_CORE) {
					zprintf(L"%u items required to create the link map table.\n", SeekTbl[0]);
				}
				break;
#endif	/* FF_USE_FASTSEEK */
#if FF_FS_RPATH >= 1
			case L'g' :	/* fg <path> - Change current directory */
				while (*ptr == L' ') ptr++;
				put_rc(f_chdir(ws2ts(ptr)));
				break;
			case L'j' :	/* fj <path> - Change current drive */
				while (*ptr == L' ') ptr++;
				put_rc(f_chdrive(ws2ts(ptr)));
				break;
#if FF_FS_RPATH >= 2
			case L'q' :	/* fq - Show current dir path */
				fr = f_getcwd(tpool, sizeof tpool / sizeof tpool[0]);
				if (fr) {
					put_rc(fr);
				} else {
					zprintf(L"%s\n", ts2ws(tpool));
				}
				break;
#endif
#endif
#if FF_USE_FORWARD
			case L'f' :	/* ff <len> - Forward data */
				if (!xatoi(&ptr, &p1)) break;
				fr = f_forward(&file[0], forward, p1, &s1);
				put_rc(fr);
				if (fr == FR_OK) zprintf(L"\n%u bytes tranferred.\n", s1);
				break;
#endif
#if !FF_FS_READONLY
			case L'w' :	/* fw <len> <val> - Write file */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				memset(Buff, p2, sizeof Buff);
				p2 = 0;
				while (p1) {
					if (p1 >= sizeof Buff) { cnt = sizeof Buff; p1 -= sizeof Buff; }
					else 				  { cnt = p1; p1 = 0; }
					fr = f_write(&file[0], Buff, cnt, &s2);
					if (fr != FR_OK) { put_rc(fr); break; }
					p2 += s2;
					if (cnt != s2) break;
				}
				zprintf(L"%lu bytes written.\n", p2);
				break;

			case L'v' :	/* fv - Truncate file */
				put_rc(f_truncate(&file[0]));
				break;

			case L'n' :	/* fn <name> <new_name> - Change file/dir name */
				while (*ptr == L' ') ptr++;
				ptr2 = wcschr(ptr, L' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				while (*ptr2 == L' ') ptr2++;
				put_rc(f_rename(ws2ts(ptr), ws2ts(ptr2)));
				break;

			case L'u' :	/* fu <name> - Unlink a file/dir */
				while (*ptr == L' ') ptr++;
				put_rc(f_unlink(ws2ts(ptr)));
				break;

			case L'k' :	/* fk <name> - Create a directory */
				while (*ptr == L' ') ptr++;
				put_rc(f_mkdir(ws2ts(ptr)));
				break;

			case L'x' : /* fx <src_name> <dst_name> - Copy a file */
				while (*ptr == L' ') ptr++;
				ptr2 = wcschr(ptr, L' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				while (*ptr2 == L' ') ptr2++;
				zprintf(L"Opening \"%s\"", ptr);
				fr = f_open(&file[0], ws2ts(ptr), FA_OPEN_EXISTING | FA_READ);
				zprintf(L"\n");
				if (fr) {
					put_rc(fr);
					break;
				}
				while (*ptr2 == L' ') ptr2++;
				zprintf(L"Creating \"%s\"", ptr2);
				fr = f_open(&file[1], ws2ts(ptr2), FA_CREATE_ALWAYS | FA_WRITE);
				zprintf(L"\n");
				if (fr) {
					put_rc(fr);
					f_close(&file[0]);
					break;
				}
				zprintf(L"Copying...");
				q1 = 0;
				for (;;) {
					fr = f_read(&file[0], Buff, sizeof Buff, &s1);
					if (fr || s1 == 0) break;   /* error or eof */
					fr = f_write(&file[1], Buff, s1, &s2);
					q1 += s2;
					if (fr || s2 < s1) break;   /* error or disk full */
				}
				zprintf(L"\n");
				if (fr) put_rc(fr);
				f_close(&file[0]);
				f_close(&file[1]);
				zprintf(L"%llu bytes copied.\n", q1);
				break;
#if FF_USE_EXPAND
			case L'h':	/* fh <fsz> <opt> - Allocate contiguous block */
				if (!xatoll(&ptr, &px) || !xatoi(&ptr, &p2)) break;
				fr = f_expand(&file[0], (FSIZE_t)px, (BYTE)p2);
				put_rc(fr);
				break;
#endif
#if FF_USE_CHMOD
			case L'a' :	/* fa <atrr> <mask> <name> - Change file/dir attribute */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				while (*ptr == L' ') ptr++;
				put_rc(f_chmod(ws2ts(ptr), (BYTE)p1, (BYTE)p2));
				break;

			case L't' :	/* ft <year> <month> <day> <hour> <min> <sec> <name> - Change timestamp of a file/dir */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.fdate = (WORD)(((p1 - 1980) << 9) | ((p2 & 15) << 5) | (p3 & 31));
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.ftime = (WORD)(((p1 & 31) << 11) | ((p2 & 63) << 5) | ((p3 >> 1) & 31));
				while (FF_USE_LFN && *ptr == L' ') ptr++;
				put_rc(f_utime(ws2ts(ptr), &Finfo));
				break;
#endif
#if FF_USE_LABEL
			case L'b' :	/* fb <name> - Set volume label */
				while (*ptr == L' ') ptr++;
				put_rc(f_setlabel(ws2ts(ptr)));
				break;
#endif
#if FF_USE_MKFS
			case L'm' :	/* fm <ld#> [<fs type> [<au size> [<align> [<n_fats> [<n_root>]]]]] - Create filesystem */
				{
					MKFS_PARM opt, *popt = 0;

					if (!xatoi(&ptr, &p1)) break;
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
					zprintf(L"The volume will be formatted. Are you sure? (Y/n)=");
					get_line(ptr, 256);
					if (*ptr != L'Y') break;
					swprintf(ptr, LINE_LEN, L"%u:", (UINT)p1);
					put_rc(f_mkfs(ws2ts(ptr), popt, Buff, sizeof Buff));
					break;
				}
#if FF_MULTI_PARTITION
			case L'p' :	/* fp <pd#> <size1> <size2> ... - Create partition table */
				{
					LBA_t pts[10];

					for (cnt = 0; cnt < 9; cnt++) {
						if (!xatoll(&ptr, &q1)) break;
						pts[cnt] = (LBA_t)q1;
					}
					pts[cnt] = 0;
					if (cnt < 2) break;
					zprintf(L"The physical drive %u will be re-partitioned. Are you sure? (Y/n)=", (BYTE)pts[0]);
					get_line(ptr, 256);
					if (*ptr != L'Y') break;
					put_rc(f_fdisk((BYTE)pts[0], &pts[1], Buff));
				}
				break;

			case L'z' : /* fz [<ld#> <pd#> <pt#>] - Map logical drive to partition */
				if (!xatoi(&ptr, &p1)) {
					for (cnt = 0; cnt < sizeof VolToPart / sizeof (PARTITION); cnt++) {
						zprintf((VolToPart[cnt].pt == 0) ? L"\"%u:\" ==> PD#%u\n" : L"\"%u:\" ==> PD#%u/PT#%u\n", cnt, VolToPart[cnt].pd, VolToPart[cnt].pt);
					}
				} else {
					if (xatoi(&ptr, &p2) && xatoi(&ptr, &p3) && (BYTE)p1 < FF_VOLUMES) {
						VolToPart[p1].pd = (BYTE)p2;
						VolToPart[p1].pt = (BYTE)p3;
					}
				}
				break;

#endif	/* FF_MULTI_PARTITION */
#endif	/* FF_USE_MKFS */
#endif	/* !FF_FS_READONLY */
			}
			break;
#if FF_CODE_PAGE == 0
			case L'p' :	/* p <codepage> - Set code page */
			if (!xatoi(&ptr, &p1)) break;
			w = (WORD)p1;
			fr = f_setcp(w);
			put_rc(fr);
			if (fr == FR_OK) {
				CodePage = w;
				if (SetConsoleCP(w) && SetConsoleOutputCP(w)) {
					zprintf(L"Console CP = %u\n", w);
				} else {
					zprintf(L"Failed to change the console CP.\n");
				}
			}
			break;
#endif

		}
	}

}


