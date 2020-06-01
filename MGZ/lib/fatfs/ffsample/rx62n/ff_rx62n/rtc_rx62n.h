/*--------------------------------------------------------------------------*/
/*  RX62N RTC control module                             (C)ChaN, 2016      */
/*--------------------------------------------------------------------------*/

#include "stdint.h"

typedef struct {
	uint16_t	year;	/* 1970.. */
	uint8_t		month;	/* 1..12 */
	uint8_t		mday;	/* 1..31 */
	uint8_t		wday;	/* 0..6 */
	uint8_t		hour;	/* 0..23 */
	uint8_t		min;	/* 0..59 */
	uint8_t		sec;	/* 0..59 */
} RTC_t;

int rtc_initialize (void);			/* Initialize RTC */
int rtc_gettime (RTC_t*);			/* Get time */
int rtc_settime (const RTC_t*);		/* Set time */

