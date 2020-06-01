#ifndef _RTC_DEFINED
#define _RTC_DEFINE

#include "LPC176x.h"

typedef struct {
	uint16_t	year;	/* 1..4095 */
	uint8_t	month;	/* 1..12 */
	uint8_t	mday;	/* 1.. 31 */
	uint8_t	wday;	/* 1..7 */
	uint8_t	hour;	/* 0..23 */
	uint8_t	min;	/* 0..59 */
	uint8_t	sec;	/* 0..59 */
} RTC;

int rtc_initialize (void);		/* Initialize RTC */
int rtc_gettime (RTC*);			/* Get time */
int rtc_settime (const RTC*);	/* Set time */

#endif
