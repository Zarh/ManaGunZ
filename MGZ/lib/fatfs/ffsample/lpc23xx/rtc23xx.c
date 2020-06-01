/*--------------------------------------------------------------------------*/
/*  RTC controls                                                            */

#include "rtc23xx.h"


int rtc_initialize (void)
{
	/* Enable PCLK to the RTC */
	__set_PCONP(PCRTC);

	/* Start RTC with external XTAL */
	RTC_CCR = 0x11;

	/* Stop PCLK to the RTC to reduce battery power consumption */
	__clr_PCONP(PCRTC);

	return 1;
}



int rtc_gettime (RTC *rtc)
{
	uint32_t d, t;


	do {
		t = RTC_CTIME0;
		d = RTC_CTIME1;
	} while (t != RTC_CTIME0 || d != RTC_CTIME1);

	rtc->sec = t & 63;
	rtc->min = (t >> 8) & 63;
	rtc->hour = (t >> 16) & 31;
	rtc->wday = (t >> 24) & 7;
	rtc->mday = d & 31;
	rtc->month = (d >> 8) & 15;
	rtc->year = (d >> 16) & 4095;

	return 1;
}




int rtc_settime (const RTC *rtc)
{
	/* Enable PCLK to the RTC */
	__set_PCONP(PCRTC);

	/* Stop RTC */
	RTC_CCR = 0x12;

	/* Update RTC registers */
	RTC_SEC = rtc->sec;
	RTC_MIN = rtc->min;
	RTC_HOUR = rtc->hour;
	RTC_DOW = rtc->wday;
	RTC_DOM = rtc->mday;
	RTC_MONTH = rtc->month;
	RTC_YEAR = rtc->year;

	/* Restart RTC with external XTAL */
	RTC_CCR = 0x11;

	/* Stop PCLK to the RTC to reduce battery power consumption */
	__clr_PCONP(PCRTC);

	return 1;
}


