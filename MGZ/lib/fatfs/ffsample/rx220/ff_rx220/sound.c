/*------------------------------------------------------------------------/
/  Sound Streaming Driver and RIFF-WAVE file player for RX220
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2017, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/
/* Note: MTU3/4 are used as sound output. CMT1 is used as sampling interval timer. */


#include <string.h>
#include "iodefine.h"
#include "sound.h"
#include "vect.h"


#define F_PCLK		32000000	/* PCLK freqency (configured by SCKCR.PCKB) */

#define	LD_WORD(ptr)		(WORD)(*(WORD*)(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(*(DWORD*)(BYTE*)(ptr))


static
WAVFIFO *SoundFifo;	/* Pointer to sound FIFO control block */


/*-----------------------------------------------------*/
/* Audio sampling interval ISR (CMT1)                  */

void Excep_CMT1_CMI1 (void)
{

	WAVFIFO *fcb;
	uint32_t ri, ct, ch_l, ch_r;
	uint8_t *buff;


	fcb = SoundFifo;
	if (!fcb) return;	/* Spurious interrupt? */

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

	MTU4.TGRC = ch_l >> 8;
	MTU3.TGRC = ch_r >> 8;
}



/*-----------------------------------------------------*/
/* Enable sound output stream                          */

int sound_start (
	WAVFIFO* fcb,	/* Pointer to the sound FIFO control structure */
	uint32_t fs		/* Sampling frequency [Hz] */
)
{
	if (fs < 8000 || fs > 48000) return 0;	/* Check fs range */

	SoundFifo = fcb;			/* Register FIFO control structure */
	fcb->ri = 0; fcb->wi = 0; fcb->ct = 0;	/* Flush FIFO */

	/* Enable MTU and CMT1 */
	SYSTEM.PRCR.WORD = 0xA502;		/* Unlock module stop registers */
	MSTP_MTU = 0;					/* Enable MTU module */
	MSTP_CMT1 = 0;					/* Enable CMT0/1 module */
	SYSTEM.PRCR.WORD = 0xA500;		/* Lock module stop registers */

	/* Attach MTIOC4A/MTIOC3A to I/O pad */
	MPC.PWPR.BYTE = 0x40; MPC.PWPR.BYTE = 0x40;		/* Unlock MPC */
	MPC.PA0PFS.BYTE = 0x01; PORTA.PMR.BIT.B0 = 1;	/* MTIOC4A -> PA0 */
	MPC.P14PFS.BYTE = 0x01; PORT1.PMR.BIT.B4 = 1;	/* MTIOC3A -> P14 */
	MPC.PWPR.BYTE = 0x80;							/* Lock MPC */

	/* Configure MTU4 as PWM out */
	MTU.TSTR.BIT.CST4 = 0;		/* Stop MTU4 */
	MTU.TOER.BIT.OE4A = 1;		/* Enable MTIOC4A output */
	MTU4.TCR.BYTE = 0x40;		/* CCLR=2, CKEG=0, TPSC=0 */
	MTU4.TMDR.BYTE = 0x12;		/* MD=2, BFA=1 */
	MTU4.TBTM.BYTE = 0x01;		/* TTSA=1 */
	MTU4.TIORH.BYTE = 0x65;		/* Clear output on c/m, set on interval */
	MTU4.TCNT = 0; MTU4.TGRB = 256 - 1;	/* PWM interval = 256 */
	MTU4.TGRA = 0x0080; MTU4.TGRC = 0x0080;	/* PWM initial value */
	MTU.TSTR.BIT.CST4 = 1;		/* Start MTU4 (MTIOC4A as L-ch) */

	/* Configure MTU3 as PWM out */
	MTU.TSTR.BIT.CST3 = 0;		/* Stop MTU3 */
	MTU3.TCR.BYTE = 0x40;		/* CCLR=2, CKEG=0, TPSC=0 */
	MTU3.TMDR.BYTE = 0x12;		/* MD=2, BFA=1 */
	MTU3.TBTM.BYTE = 0x01;		/* TTSA=1 */
	MTU3.TIORH.BYTE = 0x65;		/* Clear output on c/m, set on interval */
	MTU3.TCNT = 0; MTU3.TGRB = 256 - 1;	/* PWM interval = 256 */
	MTU3.TGRA = 0x0080; MTU3.TGRC = 0x0080;	/* PWM initial value */
	MTU.TSTR.BIT.CST3 = 1;		/* Start MTU3 (MTIOC3A as R-ch) */

	/* Configure CMT1 as sampling interval timer */
	CMT1.CMCOR = (uint16_t)(F_PCLK / 8 / fs - 1);	/* Audio sampling interval */
	CMT1.CMCNT = 0;
	IPR(CMT1, CMI1) = 9;		/* Interrupt priority = 9 */
	IEN(CMT1, CMI1) = 1;		/* Enable CMT1 compare match irq */
	CMT1.CMCR.BIT.CMIE = 1;
	CMT.CMSTR0.BIT.STR1 = 1;	/* Start CMT1 */

	return 1;
}



/*-----------------------------------------------------*/
/* Disable sound stream                                */

void sound_stop (void)
{
	CMT.CMSTR0.BIT.STR1 = 0;	/* Stop CMT1 */

	MTU4.TGRC = 0x0080;	/* Return audio outputs to center level (PWM is left activated) */
	MTU3.TGRC = 0x0080;

	SoundFifo = 0;		/* Unregister FIFO control structure */
}



#if USE_WAVPLAYER
/*-----------------------------------------------------*/
/* Simple WAV file player                              */
/*-----------------------------------------------------*/

#include "xprintf.h"
#include "uart_sci.h"
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
	while (szwav || fcb.ct >= 4) {	/* Sount streaming loop */
		if (szwav && fcb.ct <= sz_work / 2) {	/* Refill FIFO when it gets half empty */
			btr = (szwav >= sz_work / 2) ? sz_work / 2 : szwav;
			f_read(fp, &buff[wi], btr, &br);
			if (br != btr) break;	/* Exit if illigal file termination or FS error */
			szwav -= br;
			wi = (wi + br) & (sz_work - 1);
			IEN(CMT1, CMI1) = 0;	/* Disable CMT1 compare match irq */
			fcb.ct += br;
			IEN(CMT1, CMI1) = 1;	/* Enable CMT1 compare match irq */
		}
		if (uart1_test()) {		/* Exit if a user command arrived */
			k = uart1_getc();
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

