/*--------------------------------------------------------------------------*/
/* AVI to IMG file converter                                                */
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

#include <stdio.h>
#include <string.h>
#include <process.h>
#include <windows.h>
#include <wingdi.h>
#include <vfw.h>


#define MAX_WIDTH	320	/* Maximum image width for the target system */
#define MAX_HEIGHT	240	/* Maximum image height for the target system */
#define	BIG_ENDIAN	0	/* Pixel byte order for 16bpp(RGB565) image (0:GB-RG, 1:RG-GB) */


/* IMG file header */
typedef struct {
	BYTE Sign[2];		/* Signature word ("IM":Video stream only, "im":Audio/Video mixed sterem */
	WORD Width;			/* Picture width [pixel] */
	WORD Height;		/* Picture height [pixel] */
	WORD Bpp;			/* Picture color depth (16:RGB565, 8:256gray or 4:16gray) */
	DWORD DataOfs;		/* Data start offset from top of the file */
	DWORD Frames;		/* Number of frames */
	DWORD FrmPeriod;	/* Frame period [us] */
	DWORD FrmSize;		/* Number of bytes per frame (incl. audio data) */
	DWORD WavSamples;	/* Number of audio samples */
	WORD WavFormat;		/* LPCM audio format (bit0:mono(0)/stereo(1), bit1:8bit(0)/16bit(1) )  */
	WORD WavFreq;		/* Audio sampling freqency [Hz] */
} IMG_HEADER;


/* Input file, Output file and audio enable flag */
char InFile[256], OutFile[256], Audio;

BYTE *WavData;	/* Pointer to the allocated audio buffer */


/* Handles */
PAVIFILE Avifile;
PAVISTREAM AviVs, AviAs;
PGETFRAME Getfrm;
HANDLE hDst = INVALID_HANDLE_VALUE;



/*------------------------------------*/
/* Abort program with a dying message */

void die (const char *str)
{
	/* Put message */
	puts(str);

	/* Delete aborted output file */
	if (hDst != INVALID_HANDLE_VALUE) {
		CloseHandle(hDst);
		DeleteFile(OutFile);
	}

	/* Discard all resources */
	if (WavData) free(WavData);
	if (Getfrm) AVIStreamGetFrameClose(Getfrm);
	if (AviAs) AVIStreamRelease(AviAs);
	if (AviVs) AVIStreamRelease(AviVs);
	if (Avifile) AVIFileRelease(Avifile);
	if (WavData) free(WavData);
	AVIFileExit();

	exit(1);
}



/*---------------------------------------*/
/* Write a frame data (audio and image)  */

char* write_frame (				/* Returns 0 on succeeded, valid pointer to the message on error */
	HANDLE hdst,				/* Output file */
	const IMG_HEADER* hdr,		/* File header */
	DWORD frm,					/* Frame number (0:first frame) */
	const BITMAPINFOHEADER* bnf,/* Pointer to the source bitmap */
	const BYTE *audio,			/* Pointer to the audio data (0:no audio stream) */
	DWORD naudio				/* Number of audio data bytes */
)
{
	DWORD x, y, bw, slsz, slstp, dlsz, szpic;
	WORD w;
	BYTE *dst, b;
	const BYTE *src, *bitmap;
	static BYTE buff[MAX_WIDTH * MAX_HEIGHT * 2];


	bitmap = (BYTE*)bnf;
	bitmap += bnf->biSize;		/* Pointer to the bitmap data */
	switch (bnf->biBitCount) {	/* Check color format */
	case 24:
		slsz = (hdr->Width * 3 + 3) & ~3;	/* Source line stride [byte] */
		slstp = 3;							/* Source pixel stride [byte] */
		break;
	case 32:
		slsz = hdr->Width * 4;
		slstp = 4;
		break;
	default:
		return "Invalid given color depth.";
	}
	dlsz = hdr->Width * hdr->Bpp / 8;	/* Destination line size [byte] */
	szpic = dlsz * hdr->Height;			/* Destination image size [byte] */

	if (frm == 0) {	/* Put file header before first frame */
		WriteFile(hdst, hdr, sizeof(IMG_HEADER), &bw, NULL);
		if (bw != sizeof(IMG_HEADER) || (LONG)SetFilePointer(hdst, hdr->DataOfs, NULL, FILE_BEGIN) < 0)
			return "Could not write file header.";
	}

	if (audio) {	/* Write audio stream if needed */
		WriteFile(hdst, &naudio, 2, &bw, NULL);			/* Number of audio data bytes follows */
		WriteFile(hdst, audio, naudio, &bw, NULL);		/* Audio data */
		/* Align to 512 byte boundary */
		SetFilePointer(hdst, (SetFilePointer(hdst, 0, 0, FILE_CURRENT) + 511) & ~511, 0, FILE_BEGIN);
	}

	/* Write video stream  */
	for (y = 0; y < hdr->Height; y++) {
		src = &bitmap[slsz * y];
		dst = &buff[dlsz * (hdr->Height - y - 1)];
		for (x = 0; x < hdr->Width; x++) {
			switch (hdr->Bpp) {
			case 16:
				w = ((src[2] & 0xF8) << 8) | ((src[1] & 0xFC) << 3) | (src[0] >> 3);
				if (BIG_ENDIAN) {
					*dst++ = (BYTE)(w >> 8); *dst++ = (BYTE)w;
				} else {
					*dst++ = (BYTE)w; *dst++ = (BYTE)(w >> 8);
				}
				break;
			case 8:
				b = (src[2] * 30 + src[1] * 59 + src[0] * 11) / 100;
				*dst++ = b;
				break;
			case 4:
				b = (src[2] * 30 + src[1] * 59 + src[0] * 11) / 100;
				if (x & 1)
					*dst++ = *dst | (b >> 4);
				else
					*dst = b & 0xF0;
			}
			src += slstp;
		}
	}
	WriteFile(hdst, buff, szpic, &bw, NULL);

	return 0;
}



/*------------------------------------------------*/
/* Convert input audio data to the desired format */

void cv_audio (
	const BYTE *src,	/* Pointer to the input audio data (16bit/stereo) */
	BYTE *dst,			/* Pointer to the output buffer */
	WORD fmt,			/* Audio format: 0=8bit/mo, 1=8bit/st, 2=16bit/mo or 3=16bit/st */
	DWORD len			/* Number of samples to convert */
)
{
	short l, r;
	const short *s = (const short*)src;
	short *d = (short*)src;


	while (len--) {
		l = *s++; r = *s++;	/* Get 16ibt/stereo */
		switch (fmt) {
		case 0:		/* 8bit/mono */
			*dst++ = ((l + r) >> 9) ^ 0x80;
			break;
		case 1:		/* 8bit/stereo */
			*dst++ = (l >> 8) ^ 0x80;
			*dst++ = (r >> 8) ^ 0x80;
			break;
		case 2:		/* 16bit/mono */
			*d++ = (l + r) >> 1;
			break;
		default:	/* 16bit/stereo */
			*d++ = l; *d++ = r;
		}
	}
}



/*------------------------------------------------*/
/* Get command line and initialize parameters     */

int load_commands (int argc, char *argv[], IMG_HEADER* hdr)
{
	char *cp;
	int i, q;


	hdr->Bpp = 16;	/* Color depth (default) */
	hdr->WavFormat = 0;

	/* Analyze command line parameters... */
	for (i = 1; i < argc; i++) {
		cp = argv[i];

		if (*cp == '-') {	/* Command switches... */
			cp++;
			switch (*cp++) {
				case 'c' :	/* -c<n> : Color depth (4, 8, or 16) */
					hdr->Bpp = (WORD)strtoul(cp, &cp, 10);
					if (hdr->Bpp != 4 && hdr->Bpp != 8 && hdr->Bpp != 16) return -1;
					break;
				case 'a' :	/* -a<n> : Output wave stream format */
					hdr->WavFormat = (WORD)strtoul(cp, &cp, 10);
					if (hdr->WavFormat > 3) return -1;
					Audio = 1;
					break;
				default :	/* invalid command */
					return -1;
			}
			if (*cp >= ' ') return -1;	/* option trails garbage */
		}

		else {	/* files */
			if (InFile[0]) {
				strcpy(OutFile, cp);
			} else {
				strcpy(InFile, cp);
				strcpy(OutFile, cp);
				q = strlen(OutFile) - 4;
				if (q <= 0 || OutFile[q] != '.') q += 4;
				strcpy(&OutFile[q], ".img");
			}
		}

	}

	return 0;
}



/*------------------------------------------------*/
/* Program main                                   */

int main (int argc, char *argv[])
{
	AVIFILEINFO avinfo;
	AVISTREAMINFO asnfo;
	WAVEFORMATEX wavfmt;
	BITMAPINFOHEADER *bnf;
	IMG_HEADER hdr;
	char *mes;
	LONG start, sz, rsz;
	DWORD frm, wlen, nwav, outbw = 0;
	double spf = 0, spd;
	BYTE *wp;


	AVIFileInit();	/* Initialize VfW lib */

	if (load_commands(argc, argv, &hdr) || !InFile[0])
		die("AVI to IMG file Converter R1.1 (C)ChaN, 2011\n\n"\
			"Usage: avi2img [<swtches>] <input_avi> [<output_img>]\n"\
			"Switch: -c<n> Color depth: 16=RGB565, 8=256-gray or 4=16-gray\n"\
			"        -a<n> Enable audio stream: 0=8bit/mo, 1=8bit/st, 2=16bit/mo, 3=16bit/st"\
		);

	/* Open the AVI file */
	printf("Input file: %s\n", InFile);
	if (AVIFileOpen(&Avifile, InFile, OF_READ, 0))
		die("Could not open input AVI file.");

	/* Get the AVI file information */
	if (AVIFileInfo(Avifile, &avinfo, sizeof(AVIFILEINFO)))
		die("Could not get file information.");

	/* Determine output file properties by the AVI file information */
	hdr.Width = (WORD)avinfo.dwWidth;
	hdr.Height = (WORD)avinfo.dwHeight;
	hdr.FrmSize = avinfo.dwWidth * avinfo.dwHeight * hdr.Bpp / 8;
	hdr.FrmPeriod = (DWORD)(1000000 / ((double)avinfo.dwRate / avinfo.dwScale));
	hdr.Frames = avinfo.dwLength;
	hdr.DataOfs = 512;
	printf(" Video: %dx%d, %.4gfps, %dframes (output in %dbpp)\n", hdr.Width, hdr.Height, (double)avinfo.dwRate / avinfo.dwScale, hdr.Frames, hdr.Bpp);
	if (avinfo.dwWidth > MAX_WIDTH || avinfo.dwHeight > MAX_HEIGHT)
		die("Too large picture.");
	if (hdr.FrmSize % 512)
		die("Picture size is not aligned to 512 byte boundary.");

	/* Open video stream */
	if (AVIFileGetStream(Avifile, &AviVs, streamtypeVIDEO, 0) || AVIStreamInfo(AviVs, &asnfo, sizeof(asnfo)))
		die("Could not open AVI video stream.");

	/* Open audio stream and load wav data */
	if (!Audio || AVIFileGetStream(Avifile, &AviAs, streamtypeAUDIO, 0) || AVIStreamInfo(AviAs, &asnfo, sizeof(asnfo))) {
		hdr.WavSamples = 0;
		hdr.WavFreq = 0;
		memcpy(hdr.Sign, "IM", 2);	/* Video stream only */
	} else {
		start = AVIStreamStart(AviAs);
		hdr.WavSamples = wlen = AVIStreamLength(AviAs) - start;
		sz = sizeof(WAVEFORMATEX);
		if (AVIStreamReadFormat(AviAs, start, &wavfmt, &sz))
			die("Could not get audio format.");
		if (wavfmt.wFormatTag != 1 || wavfmt.nChannels != 2 || wavfmt.wBitsPerSample != 16)
			die("Supports audio format only LPCM, 16bit/stereo.");
		if (wavfmt.nSamplesPerSec < 8000 || wavfmt.nSamplesPerSec > 48000)
			die("Invalid audio frequency.");
		hdr.WavFreq = (WORD)wavfmt.nSamplesPerSec;
		sz = wavfmt.wBitsPerSample / 8 * wavfmt.nChannels * wlen;
		WavData = malloc(sz);
		if (!WavData) die("Could not allocate memory for audio data.");
		if (AVIStreamRead(AviAs, start, wlen, WavData, sz, 0, &rsz))
			die("Faild to read audio data.");
		AVIStreamRelease(AviAs);
		cv_audio(WavData, WavData, hdr.WavFormat, wlen);	/* Convert audio format */
		outbw = ((hdr.WavFormat & 1) ? 2 : 1) * ((hdr.WavFormat & 2) ? 2 : 1);
		spf = (double)wlen / hdr.Frames;
		hdr.FrmSize += ((DWORD)spf * outbw + 2 + 511) & ~511;	/* Add size of audio stream per frame (512 byte aligned) */
		memcpy(hdr.Sign, "im", 2);	/* Audio/Video mixed stream */
		printf(" Audio: %.4gkHz (output in %dbit/%s)\n", (double)hdr.WavFreq / 1000, (hdr.WavFormat & 2) ? 16 : 8, (hdr.WavFormat & 1) ? "stereo" : "mono");
	}

	/* Start to decode video stream */
	Getfrm = AVIStreamGetFrameOpen(AviVs, (LPBITMAPINFOHEADER)AVIGETFRAMEF_BESTDISPLAYFMT);
	if (!Getfrm) die("Could not open frame.");

	/* Create output file */
	printf("Output file: %s\n", OutFile);
	hDst = CreateFile(OutFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (hDst == INVALID_HANDLE_VALUE)
		 die("Could not create output file.");

	/* Read video frames and output to the destination file */
	wp = WavData; spd = 0;
	for (frm = 0; frm < hdr.Frames; frm++) {
		bnf = AVIStreamGetFrame(Getfrm, frm);
		if (!bnf) die("Could not get a frame.");
		spd += spf;
		nwav = (DWORD)spd * outbw;
		mes = write_frame(hDst, &hdr, frm, bnf, wp, nwav);
		if (mes) die(mes);
		if (wp) wp += nwav;
		spd -= (double)(DWORD)spd;
	}
	printf(" File size: %u\n", GetFileSize(hDst, 0));

	CloseHandle(hDst);
	AVIStreamGetFrameClose(Getfrm);
	AVIStreamRelease(AviVs);
	AVIFileRelease(Avifile);
	AVIFileExit();
	if (WavData) free(WavData);
	printf("\nCompleted.\n");

	return 0;
}
