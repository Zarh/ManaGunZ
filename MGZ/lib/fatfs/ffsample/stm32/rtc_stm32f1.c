/*------------------------------------------------------------------------/
/  STM32F100 RTC control module
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2013, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include "rtc_stm32f1.h"

#define F_LSE	32768	/* LSE oscillator frequency */


static
const uint8_t samurai[] = {31,28,31,30,31,30,31,31,30,31,30,31};

static
uint8_t rtcok;


/*------------------------------------------*/
/* Initialize RTC                           */
/*------------------------------------------*/

int rtc_initialize (void)	/* 1:RTC is available, 0:RTC is not available */
{
	uint32_t n;

	/* Enable BKP and PWR module */
	__enable_peripheral(BKPEN);
	__enable_peripheral(PWREN);

	PWR_CR |= _BV(8);	/* Enable write access to backup domain */

	RCC_BDCR = 0x00008101;	/* Enable LSE oscillator */
	for (n = 8000000; n && !(RCC_BDCR & _BV(1)); n--) ;	/* Wait for LSE start and stable */
	if (n) {
		for (n = 100000; n && !(RTC_CRL & _BV(5)); n--) ;
		if (n) {
			RTC_CRL = _BV(4);					/* Enter RTC configuration mode */
			RTC_PRLH = 0; RTC_PRLL = F_LSE - 1;	/* Set RTC clock divider for 1 sec tick */
			RTC_CRL = 0;						/* Exit RTC configuration mode */
			for ( ; n && !(RTC_CRL & _BV(5)); n--) ;	/* Wait for RTC internal process */
			for ( ; n && !(RTC_CRL & _BV(3)); n--) ;	/* Wait for RTC is in sync */
		}
	}

	if (n) {
		rtcok = 1;		/* RTC is available */
	} else {
		rtcok = 0;		/* RTC is not available */
		RCC_BDCR = 0;	/* Stop LSE oscillator */
	}

	PWR_CR &= ~_BV(8);	/* Inhibit write access to backup domain */

	return rtcok;
}



/*------------------------------------------*/
/* Set time in UTC                          */
/*------------------------------------------*/

int rtc_setutc (uint32_t tmr)
{
	uint32_t n = 0;


	if (rtcok) {
		PWR_CR |= _BV(8);		/* Enable write access to backup domain */
		for (n = 100000; n && !(RTC_CRL & _BV(5)); n--) ;	/* Wait for end of RTC internal process */
		if (n) {
			RTC_CRL = _BV(4);		/* Enter RTC configuration mode */
			RTC_CNTL = tmr; RTC_CNTH = tmr >> 16;	/* Set time counter */
			RTC_PRLL = F_LSE - 1; RTC_PRLH = 0; 	/* Set RTC clock divider for 1 sec tick */
			RTC_CRL = 0;			/* Exit RTC configuration mode */
			for ( ; n && !(RTC_CRL & _BV(5)); n--) ;	/* Wait for end of RTC internal process */
		}
		PWR_CR &= ~_BV(8);		/* Inhibit write access to backup domain */
	}

	return n ? 1 : 0;
}



/*------------------------------------------*/
/* Get time in UTC                          */
/*------------------------------------------*/

int rtc_getutc (uint32_t* tmr)
{
	uint32_t t1, t2;


	if (rtcok) {
		/* Read RTC counter */
		t1 = RTC_CNTH << 16 | RTC_CNTL;
		do {
			t2 = t1;
			t1 = RTC_CNTH << 16 | RTC_CNTL;	
		} while (t1 != t2);
		*tmr = t1;
		return 1;
	}
	return 0;
}



/*------------------------------------------*/
/* Get time in calendar form                */
/*------------------------------------------*/

int rtc_gettime (RTCTIME* rtc)
{
	uint32_t utc, n, i, d;

	if (!rtc_getutc(&utc)) return 0;

	utc += (long)(_RTC_TDIF * 3600);

	rtc->sec = (uint8_t)(utc % 60); utc /= 60;
	rtc->min = (uint8_t)(utc % 60); utc /= 60;
	rtc->hour = (uint8_t)(utc % 24); utc /= 24;
	rtc->wday = (uint8_t)((utc + 4) % 7);
	rtc->year = (uint16_t)(1970 + utc / 1461 * 4); utc %= 1461;
	n = ((utc >= 1096) ? utc - 1 : utc) / 365;
	rtc->year += n;
	utc -= n * 365 + (n > 2 ? 1 : 0);
	for (i = 0; i < 12; i++) {
		d = samurai[i];
		if (i == 1 && n == 2) d++;
		if (utc < d) break;
		utc -= d;
	}
	rtc->month = (uint8_t)(1 + i);
	rtc->mday = (uint8_t)(1 + utc);

	return 1;
}



/*------------------------------------------*/
/* Set time in calendar form                */
/*------------------------------------------*/

int rtc_settime (const RTCTIME* rtc)
{
	uint32_t utc, i, y;


	y = rtc->year - 1970;
	if (y > 2106 || !rtc->month || !rtc->mday) return 0;

	utc = y / 4 * 1461; y %= 4;
	utc += y * 365 + (y > 2 ? 1 : 0);
	for (i = 0; i < 12 && i + 1 < rtc->month; i++) {
		utc += samurai[i];
		if (i == 1 && y == 2) utc++;
	}
	utc += rtc->mday - 1;
	utc *= 86400;
	utc += rtc->hour * 3600 + rtc->min * 60 + rtc->sec;

	utc -= (long)(_RTC_TDIF * 3600);

	return rtc_setutc(utc);
}


