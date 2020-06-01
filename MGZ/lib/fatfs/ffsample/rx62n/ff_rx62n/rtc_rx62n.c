/*--------------------------------------------------------------------------*/
/*  RX62N RTC control module                             (C)ChaN, 2016      */
/*--------------------------------------------------------------------------*/

#include "iodefine.h"
#include "rtc_rx62n.h"

extern
volatile uint32_t Timer;	/* 1kHz increment timer (defined in main.c) */

static
int RtcOk;

static
uint16_t bcd2bin (uint16_t bcd)
{
	return (bcd >> 12) * 1000 + (bcd >> 8 & 15) * 100 + (bcd >> 4 & 15) * 10 + (bcd & 15);
}

static
uint16_t bin2bcd (uint16_t bin)
{
	return bin / 1000 * 4096 | bin / 100 % 10 * 256 | bin / 10 % 10 * 16 | bin % 10;
}





int rtc_initialize (void)
{
	RTC.RCR2.BYTE = 3;	/* Reset RTC */
	for (Timer = 0; Timer < 2000 && (RTC.RCR2.BYTE & 2); ) ;	/* Wait while reset is in progress */

	if (RTC.RCR2.BYTE & 2) {	/* Was reset finished within 2s? */
		RTC.RCR2.BYTE = 0;		/* No. Stop RTC. */
	} else {
		RtcOk = 1;				/* Yes. RTC function is available. */
	}

	return RtcOk;
}



int rtc_gettime (RTC_t *rtc)
{
	if (RtcOk) {	/* Get current time */
		RTC.RCR1.BIT.CIE = 1;
		do {
			/* Read date/time registers */
			ICU.IR[IR_RTC_CUP].BIT.IR = 0;
			rtc->sec = bcd2bin(RTC.RSECCNT.BYTE);
			rtc->min = bcd2bin(RTC.RMINCNT.BYTE);
			rtc->hour = bcd2bin(RTC.RHRCNT.BYTE);
			rtc->wday = RTC.RWKCNT.BYTE;
			rtc->mday = bcd2bin(RTC.RDAYCNT.BYTE);
			rtc->month = bcd2bin(RTC.RMONCNT.BYTE);
			rtc->year = bcd2bin(RTC.RYRCNT.WORD);
		} while (ICU.IR[IR_RTC_CUP].BIT.IR);	/* Retry if register changed in the read process */
		RTC.RCR1.BIT.CIE = 0;
	} else {	/* Return default time if RTC is not available (Jan. 1st, 2016) */
		rtc->sec = 0; rtc->min = 0; rtc->hour = 0;
		rtc->mday = 1; rtc->month = 1; rtc->year = 2016;
	}

	return RtcOk;
}



int rtc_settime (const RTC_t *rtc)
{
	if (RtcOk) {
		RTC.RCR2.BYTE = 0; while (RTC.RCR2.BYTE & 1) ;	/* Stop RTC */
		RTC.RCR2.BYTE = 2; while (RTC.RCR2.BYTE & 2) ;	/* Reset RTC */

		/* Set date/time counters */
		RTC.RSECCNT.BYTE = bin2bcd(rtc->sec);
		RTC.RMINCNT.BYTE = bin2bcd(rtc->min);
		RTC.RHRCNT.BYTE = bin2bcd(rtc->hour);
		RTC.RWKCNT.BYTE = rtc->wday;
		RTC.RDAYCNT.BYTE = bin2bcd(rtc->mday);
		RTC.RMONCNT.BYTE = bin2bcd(rtc->month);
		RTC.RYRCNT.WORD = bin2bcd(rtc->year);

		RTC.RCR2.BYTE = 1; while (!(RTC.RCR2.BYTE & 1)) ;	/* Start RTC */
	}

	return RtcOk;
}


