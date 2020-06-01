/*------------------------------------------------------------------------/
/  Sound Streaming Driver and RIFF-WAVE file player for MB9BF616/617/618
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2012, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include <string.h>
#include "FM3_type2.h"
#include "sound.h"

#define	LD_WORD(ptr)		(WORD)(*(WORD*)(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(*(DWORD*)(BYTE*)(ptr))

/* BT8,10 are used as PWM output. BT9 is used as sampling interval timer. */

#define F_PCLK		72000000	/* Bus clock supplied to BT module */


static
WAVFIFO *WavFifo;	/* Pointer to sound FIFO control block */


/*-----------------------------------------------------*/
/* Common ISR for BT8-15                               */

void BT8_15_IRQHandler (void)
{

	if (BT9_STC & 0x01) {	/* Catch BT9 underflow (sound sampling interval) */
		WAVFIFO *fcb;
		uint32_t ri, ct, ch_l, ch_r;
		uint8_t *buff;


		BT9_STC = 0x10;	/* Clear BT9 irq */

		fcb = WavFifo;
		if (!fcb) return;
		buff = fcb->buff;
		ct = fcb->ct; ri = fcb->ri;

		switch (fcb->mode) {
		case 0:		/* Mono, 8bit */
			if (ct < 1) return;
			ch_l = ch_r = buff[ri] << 8;
			ct -= 1; ri += 1;
			break;
		case 1:		/* Stereo, 8bit */
			if (ct < 2) return;
			ch_l = buff[ri] << 8;
			ch_r = buff[ri + 1] << 8;
			ct -= 2; ri += 2;
			break;
		case 2:		/* Mono, 16bit */
			if (ct < 2) return;
			ch_l = ch_r = LD_WORD(buff+ri) ^ 0x8000;
			ct -= 2; ri += 2;
			break;
		default:	/* Stereo, 16bit */
			if (ct < 4) return;
			ch_l = LD_WORD(buff+ri) ^ 0x8000;;
			ch_r = LD_WORD(buff+ri+2) ^ 0x8000;;
			ct -= 4; ri += 4;
		}
		fcb->ct = ct;
		fcb->ri = ri & (fcb->sz_buff - 1);

		BT8_PDUT = (uint16_t)(ch_l >>= 7);
		BT10_PDUT = (uint16_t)(ch_r >>= 7);

		return;
	}

	__disable_irqn(BT8_15_IRQn);	/* May be a spurious interrupt (No one caught this interrupt) */
}



/*-----------------------------------------------------*/
/* Enable sound output stream                          */

int sound_start (
	WAVFIFO* fcb,	/* Pointer to the sound FIFO control structure */
	uint32_t fs		/* Sampling frequency [Hz] */
)
{
	if (fs < 8000 || fs > 48000) return 0;	/* Check fs range */

	WavFifo = fcb;			/* Register FIFO control structure */
	fcb->ri = 0; fcb->wi = 0; fcb->ct = 0;	/* Flush FIFO */

	/* Configure BT8 as audio output L */
	BT8_TMCR =  0x0010;		/* Stop BT8 */
	BT8_STC = 0;
	EPFR12 |= 0x00000004;	/* Attach TIOA08 to I/O pad */
	PFRA |= 0x0001;
	BT8_PCSR = 511;			/* 9bit PWM = F_PCLK/512 Hz */
	BT8_PDUT = 256;
	BT8_TMCR =  0x0013;		/* Start BT8 with PWM mode */

	/* Configure BT10 as audio output R */
	BT10_TMCR =  0x0010;	/* Stop BT10 */
	BT10_STC = 0;
	EPFR12 |= 0x00040000;	/* Attach TIOA10 to I/O pad */
	PFRA |= 0x0004;
	BT10_PCSR = 511;		/* 9bit PWM = F_PCLK/512 Hz */
	BT10_PDUT = 256;
	BT10_TMCR =  0x0013;	/* Start BT10 with PWM mode */

	/* Configure BT9 as sampling interval timer */
	BT9_TMCR = 0x0030;		/* Stop BT9 */
	BT9_TMCR2 = 0;
	BT9_PCSR = (uint16_t)(F_PCLK / fs);	/* Audio sampling interval */
	BT9_TMCR = 0x0033;		/* Enable BT9 with IVT mode */
	BT9_STC = 0x10;			/* Enable BT9 underflow irq */
	__enable_irqn(BT8_15_IRQn);				/* Enable interrupt */
	__set_irqn_priority(BT8_15_IRQn, 0);	/* Set interrupt priority, highest */

	return 1;
}



/*-----------------------------------------------------*/
/* Disable sound stream                                */

void sound_stop (void)
{
	BT9_STC = 0;		/* Stop BT9 (sampling interrupt) */
	BT9_TMCR = 0;

	BT8_PDUT = 256;		/* Return audio outputs to center level (PWM is left activated) */
	BT10_PDUT = 256;

	WavFifo = 0;		/* Unregister FIFO control structure */
}



#if USE_WAVPLAYER
/*-----------------------------------------------------*/
/* Simple WAV file player                              */
/*-----------------------------------------------------*/

#include "xprintf.h"
#include "uart_mfs.h"
#define NBSIZE 64			/* Size of name buffer */
#define FCC(c1,c2,c3,c4)	((c4<<24)+(c3<<16)+(c2<<8)+c1)	/* Create FourCC */


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


	xprintf("**** RIFF-WAVE Player ****\nFile=%s\n", title);	/* Put title */

	/* Is this a WAV file? */
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
			if (LD_WORD(&buff[0]) != 0x1) return -1;	/* Check if LPCM or not */
			if (LD_WORD(&buff[2]) == 2) {	/* Check channels (1 or 2) */
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
			szwav = sz;			/* Size of wave data [byte] */
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
					case FCC('I','N','A','M'):		/* INAM (name) field */
						p = nam; break;
					case FCC('I','A','R','T'):		/* IART (artist) field */
						p = art; break;
					}
					if (p && ssz <= NBSIZE) {
						if (f_read(fp, p, ssz, &br) || br != ssz) return -1;
					} else {
						if (f_lseek(fp, f_tell(fp) + ssz)) return -1;
					}
				}
			} else {
				if (f_lseek(fp, sz)) return -1;	/* Skip unknown sub-chunk */
			}
			break;

		default :	/* Unknown chunk */
			return -1;
		}
	}
	if (!szwav || !fsmp) return -1;		/* Check if valid WAV file */
	if (f_lseek(fp, offw)) return -1;	/* Seek to top of wav data */
	tc = szwav / fsmp / wsmp;			/* Length (sec) */

	xprintf("IART=%s\nINAM=%s\n", art, nam);
	xprintf("Sample=%u.%ukHz/%ubit/%s\nLength=%u:%02u\n", fsmp / 1000, (fsmp / 100) % 10, (md & 2) ? 16 : 8, (md & 1) ? "Stereo" : "Mono", tc / 60, tc % 60);

	/* Initialize sound FIFO and start sound streming */
	fcb.mode = md;			/* Sampling: b0=mono(0)/stereo(1), b1=8bit(0)/16bit(1) */
	fcb.buff = buff;		/* Pointer to streaming buffer */
	fcb.sz_buff = sz_work;	/* Size of streaming buffer */
	if (!sound_start(&fcb, fsmp)) return -1;	/* Start sound streaming */

	k = 0; wi = 0;
	while (szwav || fcb.ct >= 4) {	/* Sound streaming loop */
		if (szwav && fcb.ct <= sz_work / 2) {	/* Refill FIFO when it gets half empty */
			btr = (szwav >= sz_work / 2) ? sz_work / 2 : szwav;
			f_read(fp, &buff[wi], btr, &br);
			if (br != btr) break;	/* Exit if wrong file termination or FS error */
			szwav -= br;
			wi = (wi + br) & (sz_work - 1);
			__disable_irq();
			fcb.ct += br;
			__enable_irq();
		}
		if (uart3_test()) {		/* Exit if a user command arrived */
			k = uart3_getc();
			break;
		}
		t = (f_tell(fp) - offw - fcb.ct) / fsmp / wsmp;	/* Refresh time display every 1 sec */
		if (t != tc) {
			tc = t;
			xprintf("\rTime=%u:%02u", tc / 60, tc % 60);
		}
	}

	sound_stop();	/* Stop sound streaming */

	xputc('\n');
	return k;	/* Terminated due to -1:error, 0:eot, >0:key code */
}
#endif /* USE_WAVPLAYER */

