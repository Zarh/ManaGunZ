#ifndef _RTC_DEFINED
#define _RTC_DEFINED


typedef struct {
	uint16_t	year;	/* 2000..2099 */
	uint8_t		month;	/* 1..12 */
	uint8_t		mday;	/* 1.. 31 */
	uint8_t		wday;	/* 1..7 */
	uint8_t		hour;	/* 0..23 */
	uint8_t		min;	/* 0..59 */
	uint8_t		sec;	/* 0..59 */
} RTC;

int iic_write (uint8_t, uint16_t, uint16_t, const void*);	/* Write to IIC device */
int iic_read (uint8_t, uint16_t, uint16_t, void*);		/* Read from IIC device */

int rtc_init (void);				/* Initialize RTC */
int rtc_gettime (RTC*);				/* Get time */
int rtc_settime (const RTC*);		/* Set time */


#endif
