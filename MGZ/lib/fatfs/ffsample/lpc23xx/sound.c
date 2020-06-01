/*------------------------------------------------------------------------/
/  Sound Streamer and RIFF-WAVE file player
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2011, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include <string.h>
#include "sound.h"
#include "interrupt.h"
#include "xprintf.h"
#include "disp.h"
#include "uart23xx.h"


#define	F_CCLK		72000000	/* CCLK frequency */
#define F_PCLK_T3	18000000	/* PCLK frequency to be supplied to TIMER3 module */

#define NBSIZE 64
#define FCC(c1,c2,c3,c4)	(((DWORD)c4<<24)+((DWORD)c3<<16)+(c2<<8)+c1)	/* FourCC */
#define	LD_WORD(ptr)		(WORD)(*(WORD*)(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(*(DWORD*)(BYTE*)(ptr))

#if F_PCLK_T3 * 1 == F_CCLK
#define PCLKDIV_T3	PCLKDIV_1
#elif F_PCLK_T3 * 2 == F_CCLK
#define PCLKDIV_T3	PCLKDIV_2
#elif F_PCLK_T3 * 4 == F_CCLK
#define PCLKDIV_T3	PCLKDIV_4
#elif F_PCLK_T3 * 8 == F_CCLK
#define PCLKDIV_T3	PCLKDIV_8
#else
#error Invalid frequency combination
#endif


static
WAVFIFO *WavFifo;	/* Pointer to sound FIFO control block */


/*-----------------------------------------------------*/
/* Sound sampling ISR                                  */

void Isr_TIMER3 (void)
{
	WAVFIFO *fcb = WavFifo;	/* Pointer to FIFO controls */
	uint8_t *buff;
	uint32_t ri, ct, dac;


	T3IR = T3IR;	/* Clear irq flag */

	if (!fcb) return;
	buff = fcb->buff;
	ct = fcb->ct; ri = fcb->ri;

	switch (fcb->mode) {
	case 0:		/* Mono, 8bit */
		if (ct < 1) return;
		dac = buff[ri] << 8;
		ct -= 1; ri += 1;
		break;
	case 1:		/* Stereo, 8bit */
		if (ct < 2) return;
		dac = (buff[ri] + buff[ri + 1]) << 7;
		ct -= 2; ri += 2;
		break;
	case 2:		/* Mono, 16bit */
		if (ct < 2) return;
		dac = LD_WORD(buff+ri) ^ 0x8000;
		ct -= 2; ri += 2;
		break;
	default:	/* Stereo, 16bit */
		if (ct < 4) return;
		dac = LD_WORD(buff+ri) ^ 0x8000;
		dac += LD_WORD(buff+ri+2) ^ 0x8000;
		dac >>= 1;
		ct -= 4; ri += 4;
	}

	DACR = dac;

	fcb->ct = ct;
	fcb->ri = ri & (fcb->sz_buff - 1);
}



/*-----------------------------------------------------*/
/* Enable sound output stream                          */

int sound_start (
	WAVFIFO* fcb,	/* Pointer to the sound FIFO control structure */
	uint32_t fs		/* Sampling frequency [Hz] (8000-48000) */
)
{
	if (fs < 8000 || fs > 48000) return 0;	/* Check fs range */

	fcb->ri = 0; fcb->wi = 0; fcb->ct = 0;	/* Flush FIFO */
	WavFifo = fcb;			/* Register FIFO control structure */

	/* Enable DAC */
	__set_PINMODE(0, 26, PINMODE_HIZ);
	__set_PINSEL(0, 26, 2);	/* AOUT -> P0.26 */
	DACR = 0x8000;

	/* Configure TIMER3 as sampling interval timer */
	__set_PCONP(PCTIM3);		/* Enable TIMER3 module */
	__set_PCLKSEL(PCLK_TIMER3, PCLKDIV_T3);
	RegisterIrq(TIMER3_IRQn, Isr_TIMER3, PRI_HIGHEST);
	T3TCR = _BV(1);
	T3MR0 = F_PCLK_T3 / fs - 1;
	T3MCR = _BV(1)|_BV(0);
	T3TCR = _BV(0);

	return 1;
}



/*-----------------------------------------------------*/
/* Disable sound output                                */

void sound_stop (void)
{
	DACR = 0x8000;		/* Return center */

	T3TCR = 0;					/* Stop sampling interrupt (TIMER3) */
	__clr_PCONP(PCTIM3);		/* Disable TIMER3 module */

	WavFifo = 0;		/* Unregister FIFO control structure */
}



/*-----------------------------------------------------*/
/* WAV file loader                                     */

int load_wav (
	FIL *fp,			/* Pointer to the open file object to play */
	const char *title,	/* Title (file name, etc...) */
	void *work,			/* Pointer to working buffer (must be-4 byte aligned) */
	uint32_t sz_work	/* Size of working buffer (must be power of 2) */
)
{
	UINT md, wi, br, tc, t, btr;
	DWORD sz, ssz, offw, szwav, wsmp, fsmp, eof;
	WAVFIFO fcb;
	BYTE k, *buff = work;
	char *p, nam[NBSIZE], art[NBSIZE];


	disp_font_color(C_WHITE);
	xfprintf(disp_putc, "\f%s\n", title);	/* Put title */

	/* Is it a WAV file? */
	if (f_read(fp, buff, 12, &br) || br != 12) return -1;
	if (LD_DWORD(&buff[0]) != FCC('R','I','F','F')) return -1;
	if (LD_DWORD(&buff[8]) != FCC('W','A','V','E')) return -1;
	eof = LD_DWORD(&buff[4]) + 8;

	/* Analyze the RIFF-WAVE header and get properties */
	nam[0] = art[0] = 0;
	md = fsmp = wsmp = offw = szwav = 0;
	while (f_tell(fp) < eof) {
		if (f_read(fp, buff, 8, &br) || br != 8) return -1;
		sz = (LD_DWORD(&buff[4]) + 1) & ~1;
		switch (LD_DWORD(&buff[0])) {
		case FCC('f','m','t',' ') :	/* fmt chunk */
			if (sz > 1000 || sz < 16 || f_read(fp, buff, sz, &br) || sz != br) return -1;
			if (LD_WORD(&buff[0]) != 0x1) return -1;	/* Check if LPCM */
			if (LD_WORD(&buff[2]) == 2) {	/* Channels (1 or 2) */
				md = 1; wsmp = 2;
			} else {
				md = 0; wsmp = 1;
			}
			if (LD_WORD(&buff[14]) == 16) {	/* Resolution (8 or 16) */
				md |= 2; wsmp *= 2;
			}
			fsmp = LD_DWORD(&buff[4]);		/* Sampling rate */
			break;

		case FCC('f','a','c','t') :	/* fact chunk */
			f_lseek(fp, f_tell(fp) + sz);
			break;

		case FCC('d','a','t','a') :	/* data chunk */
			offw = f_tell(fp);	/* Wave data start offset */
			szwav = sz;			/* Wave data length [byte] */
			f_lseek(fp, f_tell(fp) + sz);
			break;

		case FCC('L','I','S','T'):	/* LIST chunk */
			sz += f_tell(fp);
			if (f_read(fp, buff, 4, &br) || br != 4) return -1;
			if (LD_DWORD(buff) == FCC('I','N','F','O')) {	/* LIST/INFO sub-chunk */
				while (f_tell(fp) < sz) {
					if (f_read(fp, buff, 8, &br) || br != 8) return -1;
					ssz = (LD_DWORD(&buff[4]) + 1) & ~1;
					p = 0;
					switch (LD_DWORD(buff)) {
					case FCC('I','N','A','M'):		/* INAM field */
						p = nam; break;
					case FCC('I','A','R','T'):		/* IART field */
						p = art; break;
					}
					if (p && ssz <= NBSIZE) {
						if (f_read(fp, p, ssz, &br) || br != ssz) return -1;
					} else {
						if (f_lseek(fp, f_tell(fp) + ssz)) return -1;
					}
				}
			} else {
				if (f_lseek(fp, sz)) return -1;	/* Skip unknown sub-chunk type */
			}
			break;

		default :	/* Unknown chunk */
			return -1;
		}
	}
	if (!szwav || !fsmp) return -1;		/* Check if valid WAV file */
	if (f_lseek(fp, offw)) return -1;	/* Seek to top of wav data */
	tc = szwav / fsmp / wsmp;			/* Length (sec) */

	xfprintf(disp_putc, "IART=%s\nINAM=%s\n", art, nam);	/* Put IART and INAM field */
	xfprintf(disp_putc, "Sample=%u.%ukHz/%ubit/%s\nLength=%u:%02u\n", fsmp / 1000, (fsmp / 100) % 10, (md & 2) ? 16 : 8, (md & 1) ? "st" : "mo", tc / 60, tc % 60);

	/* Initialize stream parameters and start sound streming */
	fcb.mode = md;			/* Sampling: b0=mono(0)/stereo(1), b1=8bit(0)/16bit(1) */
	fcb.buff = buff;		/* Pointer to streaming buffer */
	fcb.sz_buff = sz_work;	/* Size of streaming buffer */
	if (!sound_start(&fcb, fsmp)) return -1;	/* Start sound streaming */

	disp_font_face(FontH24);	/* Select font for time display */

	k = 0; wi = 0;
	while (szwav || fcb.ct >= 4) {
		if (szwav && fcb.ct <= sz_work / 2) {	/* Refill FIFO when it gets half empty */
			btr = (szwav >= sz_work / 2) ? sz_work / 2 : szwav;
			f_read(fp, &buff[wi], btr, &br);
			if (br != btr) break;
			szwav -= br;
			wi = (wi + br) & (sz_work - 1);
			IrqDisable();
			fcb.ct += br;
			IrqEnable();
		}
		if (uart0_test()) {		/* Exit if a command arrived */
			k = uart0_getc();
			break;
		}
		t = (f_tell(fp) - offw - fcb.ct) / fsmp / wsmp;	/* Refresh time display every 1 sec */
		if (t != tc) {
			tc = t;
			xfprintf(disp_putc, "\rTime=%u:%02u", tc / 60, tc % 60);
		}
	}

	sound_stop();	/* Stop sound output */

	disp_font_face(FontH10);	/* Restore font */

	return k;	/* Terminated due to -1:error, 0:eot, >0:key code */
}



/*-----------------------------------------------------*/
/* M3U file loader                                     */

void load_m3u (
	FIL fp[],	/* 1st item is open file object of m3u file. 2nd item is used for playback */
	void* work,
	UINT sz_work
)
{
	char *line = work;
	int rc, n, trk, trks;
	FRESULT res;


	trks = 0;
	while (f_gets(line, 100, &fp[0])) {
		if (line[0] != '#' && (uint8_t)line[0] > ' ') trks++;
	}
	if (!trks) return;

	rc = 0; trk = 1;
	for (;;) {
		res = f_lseek(&fp[0], 0);
		if (res) break;
		n = 0;
		while (f_gets(line, 100, &fp[0])) {
			if (line[0] != '#' && (uint8_t)line[0] > ' ') {
				if (++n == trk) break;
			}
		}
		if (n != trk) return;
		res = f_open(&fp[1], line, FA_READ);
		if (res == FR_OK) {
			rc = load_wav(&fp[1], line, work, sz_work);
			f_close(&fp[1]);
		}
		if (res || rc == -1 || rc == BTN_CAN) return;
		if (!rc || rc == BTN_RIGHT) {
			if (++trk > trks) trk = 1;
			continue;
		}
		if (rc == BTN_LEFT) {
			if (--trk == 0) trk = trks;
		}
	}

}

