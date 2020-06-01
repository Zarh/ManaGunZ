/*--------------------------------------------------------------------------*/
/* 24-bit BMP to 16-bit bitmap converter                      (C)ChaN, 2011 */
/*--------------------------------------------------------------------------*/
/* This program is opened under license policy of following trems.
/
/  Copyright (C) 2011, ChaN, all right reserved.
/
/ * This program is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial use UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/---------------------------------------------------------------------------*/
/*
The 24-bit BMP to 16-bit raw bitmap converter supports three output formats.

[RGB565 windows bmp]
16bpp windows BMP file with bit field information.

[Raw RGB565 bitmap with heading size information]
uint16_t bitmap[] = { <width>, <height>, <left-top pix>, <next right pix>, ... <right-bottom pix> };

[Raw RGB565 bitmap only]
uint16_t bitmap[] = { <left-top pix>, <next right pix>, ... <right-bottom pix> };

[Big endian]
Endianness of raw bitmap data is little endian in default.
It can also be switched to big-endian.

*/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <wingdi.h>

/* Maximum source image size */
#define MAX_WIDTH	1024
#define MAX_HEIGHT	1024

/* Bit field for output pixel in 16-bit RGB (rrrrrggggggbbbbb) */
#define	R_MSB	15
#define	R_LSB	11
#define	G_MSB	10
#define	G_LSB	5
#define	B_MSB	4
#define	B_LSB	0


BYTE SrcBuff[(MAX_WIDTH * 3 + 3) * MAX_HEIGHT];
WORD DstBuff[(MAX_WIDTH * 2) * MAX_HEIGHT];



WORD cv_2416 (	/* Returns 16-bit packed pixel data */
	BYTE *src24	/* Pointer to the pixel data in 24-bit B-G-R */
)
{
	WORD w, s;


	s = *src24++ >> (8 - B_MSB + B_LSB - 1);
	w = s << B_LSB;
	s = *src24++ >> (8 - G_MSB + G_LSB - 1);
	w |= s << G_LSB;
	s = *src24++ >> (8 - R_MSB + R_LSB - 1);
	w |= s << R_LSB;

	return w;
}




int cv_bmpfile (
	const char *src,	/* Pointer to the source file name */
	int fmt,			/* Output format */
	int endian			/* Endianness of output pixel data */
)
{
	char dst[256];
	BYTE buf[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)];
	BITMAPFILEHEADER *bfh = (BITMAPFILEHEADER*)&buf[0];
	BITMAPINFOHEADER *bih = (BITMAPINFOHEADER*)&buf[sizeof(BITMAPFILEHEADER)];
	DWORD btr, br, btw, bw, bfm[3];
	LONG width, width_b, height, height_b, xc, yc;
	BYTE *sp;
	WORD *dp, w;
	int i;
	HANDLE fh;


	/* Open source file */
	if (strlen(src) >= 250) return 2;
	fh = CreateFile(src, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fh == INVALID_HANDLE_VALUE) return 2;
	printf("%s ==> ", src);

	/* Load file header and check if valid bmp file */
	ReadFile(fh, buf, sizeof(buf), &br, NULL);
	if (br != sizeof(buf)) { CloseHandle(fh); return 3; }
	if (bfh->bfType != 0x4D42) { CloseHandle(fh); return 4; }	/* Check signature "BM" */
	if (bih->biPlanes != 1 || bih->biBitCount != 24 || bih->biCompression != BI_RGB) { CloseHandle(fh); return 5; }	/* Check if 24-bit BMP */
	width = bih->biWidth; height = bih->biHeight;
	height_b = (height > 0) ? height : 0 - height;
	width_b = (width * 3 + 3) & ~3;
	btr = width_b * height_b;
	if (!btr || width > MAX_WIDTH || height_b > MAX_HEIGHT) { CloseHandle(fh); return 6; }	/* Check image size */

	/* Load source bitmap */
	SetFilePointer(fh, bfh->bfOffBits, NULL, FILE_BEGIN);
	ReadFile(fh, SrcBuff, btr, &br, NULL);
	CloseHandle(fh);
	if (btr != br) return 7;

	/* Create destination file */
	strcpy(dst, src);
	i = strlen(dst);
	if (i > 4 && dst[i - 4] == '.') i -= 4;
	strcpy(dst + i, fmt ? ".bin" : "_16.bmp");
	fh = CreateFile(dst, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fh == INVALID_HANDLE_VALUE) return 10;
	printf("%s\n", dst);

	if (fmt == 0) {	/* Output format is windows bmp */
		bih->biBitCount = 16;				/* 16 bits/pixel */
		bih->biCompression = BI_BITFIELDS;	/* Use bit field information */
		if (width & 1) width++;				/* Align bitmap width to 4-byte boundary */
		bih->biSizeImage = width * 2 * height_b;
		bih->biHeight = height_b;
		bfh->bfOffBits = sizeof(buf) + 12;
		bfh->bfSize = bfh->bfOffBits + bih->biSizeImage;
		WriteFile(fh, buf, sizeof(buf), &bw, NULL);
		if (bw != sizeof(buf)) { CloseHandle(fh); return 12; }

		/* Create RGB bit field information and write it */
		bfm[0] = (255 >> (8 - R_MSB + R_LSB - 1)) << R_LSB;
		bfm[1] = (255 >> (8 - G_MSB + G_LSB - 1)) << G_LSB;
		bfm[2] = (255 >> (8 - B_MSB + B_LSB - 1)) << B_LSB;
		WriteFile(fh, bfm, 12, &bw, NULL);
		if (bw != 12) { CloseHandle(fh); return 12; }

		/* Create 16-bit bitmap and write it */
		for (yc = 0; yc < height_b; yc++) {
			sp = &SrcBuff[width_b * (height > 0 ? height_b - yc - 1 : yc)];
			dp = &DstBuff[width * (height_b - yc - 1)];
			for (xc = 0; xc < bih->biWidth; xc++) {
				*dp++ = cv_2416(sp);
				sp += 3;
			}
			if (bih->biWidth & 1) *dp = 0;
		}
		WriteFile(fh, DstBuff, bih->biSizeImage, &bw, NULL);
		if (bw != bih->biSizeImage) { CloseHandle(fh); return 12; }

	} else {	/* Output format is raw bitmap */
		/* Create 16-bit bitmap */
		for (yc = 0; yc < height_b; yc++) {
			sp = &SrcBuff[width_b * (height > 0 ? height_b - yc - 1 : yc)];
			dp = &DstBuff[width * yc];
			for (xc = 0; xc < bih->biWidth; xc++) {
				w = cv_2416(sp);
				if (endian) w = (w << 8) | (w >> 8);
				*dp++ = w;
				sp += 3;
			}
		}
		if (fmt == 1) {	/* Put size information if needed */
			w = width;
			if (endian) w = (w << 8) | (w >> 8);
			dp[0] = w;
			w = height_b;
			if (endian) w = (w << 8) | (w >> 8);
			dp[1] = w;
			WriteFile(fh, dp, 4, &bw, NULL);
			if (bw != 4) { CloseHandle(fh); return 12; }
		}

		/* Write 16-bit bitmap */
		WriteFile(fh, DstBuff, width * height_b * 2, &bw, NULL);
		if (bw != width * height_b * 2) { CloseHandle(fh); return 12; }
	}

	CloseHandle(fh);

	return 0;
}



int main (int argc, char *argv[])
{
	const char *p;
	int i, rv, er, files;
	int fmt = 1;
	int endian = 0;


	rv = -1; er = files = 0;
	for (i = 1; i < argc; i++) {
		p = argv[i];
		if (*p == '-') {
			p++;
			switch (*p++) {
			case 'f':
				switch (*p++) {
				case 'b':
					fmt = 0; break;
				case '1':
					fmt = 1; break;
				case '2':
					fmt = 2; break;
				default:
					er = 1;
				}
				break;
			case 'b':
				endian = 1; break;
			default:
				er = 1;
			}
		} else {
			files++;
			rv = cv_bmpfile(p, fmt, endian);
			if (rv) er = rv;
		}
	}

	if (rv) {
		if (rv < 0) {
			printf( "Usage: bmp2bin <options> <input files> ...\n"
					"options: -fb - Output in RGB565 windows bmp\n"
					"       : -f1 - Output in raw RGB565 with heading size info (default)\n"
					"       : -f2 - Output in raw RGB565\n"
					"       : -b  - Big endian (valid for only -f1 and -f2)\n"
			);
		} else {
			printf("Error. Code = %d\n", rv);
		}
	} else {
		printf("%d file(s) converted.\n", files);
	}

	printf("\nType Enter to exit...");
	getchar();

	return rv;
}

