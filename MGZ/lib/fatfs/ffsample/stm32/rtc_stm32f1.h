#ifndef _RTC_DEFINED
#define _RTC_DEFINED

#define _RTC_TDIF	+9.0	/* JST = UTC+9.0 */

#include "STM32F100.h"

typedef struct {
	uint16_t	year;	/* 1970..2106 */
	uint8_t		month;	/* 1..12 */
	uint8_t		mday;	/* 1..31 */
	uint8_t		hour;	/* 0..23 */
	uint8_t		min;	/* 0..59 */
	uint8_t		sec;	/* 0..59 */
	uint8_t		wday;	/* 0..6 (Sun..Sat) */
} RTCTIME;

int rtc_initialize (void);				/* Initialize RTC */
int rtc_gettime (RTCTIME* rtc);			/* Get time */
int rtc_settime (const RTCTIME* rtc);	/* Set time */
int rtc_getutc (uint32_t* utc);			/* Get time in UTC */
int rtc_setutc (uint32_t utc);			/* Set time in UTC */


#endif
