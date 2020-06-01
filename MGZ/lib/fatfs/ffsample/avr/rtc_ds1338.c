/*--------------------------------------------------------------------------*/
/*  DS1338 RTC controls via AVR GPIO                                        */
/*--------------------------------------------------------------------------*/

#include <avr/io.h>
#include <string.h>
#include "rtc.h"


#define	IIC_INIT()	{ DDRB &= ~(_BV(1)|_BV(0)); PORTB &= ~(_BV(1)|_BV(0)); }	/* Set SCL/SDA as hi-z */
#define SCL_LOW()	DDRB |=	_BV(1)				/* SCL = LOW */
#define SCL_HIGH()	DDRB &=	~_BV(1)				/* SCL = High-Z */
#define	SCL_VAL()	((PINB & _BV(1)) ? 1 : 0)	/* SCL level */
#define SDA_LOW()	DDRB |=	_BV(0)				/* SDA = LOW */
#define SDA_HIGH()	DDRB &=	~_BV(0)				/* SDA = High-Z */
#define	SDA_VAL()	((PINB & _BV(0)) ? 1 : 0)	/* SDA level */



/*-------------------------------------------------*/
/* I2C bus protocol                                */


static
void iic_delay (void)
{
	int n;

	for (n = 4; n; n--) PINB;
}


/* Generate start condition on the IIC bus */
static
void iic_start (void)
{
	SDA_HIGH();
	iic_delay();
	SCL_HIGH();
	iic_delay();
	SDA_LOW();
	iic_delay();
	SCL_LOW();
	iic_delay();
}


/* Generate stop condition on the IIC bus */
static
void iic_stop (void)
{
	SDA_LOW();
	iic_delay();
	SCL_HIGH();
	iic_delay();
	SDA_HIGH();
	iic_delay();
}


/* Send a byte to the IIC bus */
static
int iic_send (uint8_t dat)
{
	uint8_t b = 0x80;
	int ack;


	do {
		if (dat & b)	 {	/* SDA = Z/L */
			SDA_HIGH();
		} else {
			SDA_LOW();
		}
		iic_delay();
		SCL_HIGH();
		iic_delay();
		SCL_LOW();
		iic_delay();
	} while (b >>= 1);
	SDA_HIGH();
	iic_delay();
	SCL_HIGH();
	ack = SDA_VAL() ? 0 : 1;	/* Sample ACK */
	iic_delay();
	SCL_LOW();
	iic_delay();
	return ack;
}


/* Receive a byte from the IIC bus */
static
uint8_t iic_rcvr (int ack)
{
	uint16_t d = 1;


	do {
		d <<= 1;
		SCL_HIGH();
		if (SDA_VAL()) d++;
		iic_delay();
		SCL_LOW();
		iic_delay();
	} while (d < 0x100);
	if (ack) {		/* SDA = ACK */
		SDA_LOW();
	} else {
		SDA_HIGH();
	}
	iic_delay();
	SCL_HIGH();
	iic_delay();
	SCL_LOW();
	SDA_HIGH();
	iic_delay();

	return (uint8_t)d;
}



/*-------------------------------------------------*/
/* I2C block read/write controls                   */


int iic_read (
	uint8_t dev,		/* Device address */
	uint16_t adr,		/* Read start address */
	uint16_t cnt,		/* Read byte count */
	void* buff		/* Read data buffer */
)
{
	uint8_t *rbuff = buff;
	int n;


	if (!cnt) return 0;

	n = 10;
	do {							/* Select device */
		iic_start();
	} while (!iic_send(dev) && --n);
	if (n) {
		if (iic_send((uint8_t)adr)) {		/* Set start address */
			iic_start();				/* Reselect device in read mode */
			if (iic_send(dev | 1)) {
				do {					/* Receive data */
					cnt--;
					*rbuff++ = iic_rcvr(cnt ? 1 : 0);
				} while (cnt);
			}
		}
	}

	iic_stop();						/* Deselect device */

	return cnt ? 0 : 1;
}



int iic_write (
	uint8_t dev,			/* Device address */
	uint16_t adr,			/* Write start address */
	uint16_t cnt,			/* Write byte count */
	const void* buff	/* Data to be written */
)
{
	const uint8_t *wbuff = buff;
	int n;


	if (!cnt) return 0;

	n = 10;
	do {							/* Select device */
		iic_start();
	} while (!iic_send(dev) && --n);
	if (n) {
		if (iic_send((uint8_t)adr)) {		/* Set start address */
			do {						/* Send data */
				if (!iic_send(*wbuff++)) break;
			} while (--cnt);
		}
	}

	iic_stop();						/* Deselect device */

	return cnt ? 0 : 1;
}



/*-------------------------------------------------*/
/* RTC functions                                   */


int rtc_gettime (RTC *rtc)
{
	uint8_t buf[8];


	if (!iic_read(0xD0, 0, 7, buf)) return 0;

	rtc->sec = (buf[0] & 0x0F) + ((buf[0] >> 4) & 7) * 10;
	rtc->min = (buf[1] & 0x0F) + (buf[1] >> 4) * 10;
	rtc->hour = (buf[2] & 0x0F) + ((buf[2] >> 4) & 3) * 10;
	rtc->wday = (buf[2] & 0x07);
	rtc->mday = (buf[4] & 0x0F) + ((buf[4] >> 4) & 3) * 10;
	rtc->month = (buf[5] & 0x0F) + ((buf[5] >> 4) & 1) * 10;
	rtc->year = 2000 + (buf[6] & 0x0F) + (buf[6] >> 4) * 10;

	return 1;
}




int rtc_settime (const RTC *rtc)
{

	uint8_t buf[8];


	buf[0] = rtc->sec / 10 * 16 + rtc->sec % 10;
	buf[1] = rtc->min / 10 * 16 + rtc->min % 10;
	buf[2] = rtc->hour / 10 * 16 + rtc->hour % 10;
	buf[3] = rtc->wday & 7;
	buf[4] = rtc->mday / 10 * 16 + rtc->mday % 10;
	buf[5] = rtc->month / 10 * 16 + rtc->month % 10;
	buf[6] = (rtc->year - 2000) / 10 * 16 + (rtc->year - 2000) % 10;
	return iic_write(0xD0, 0, 7, buf);
}




int rtc_init (void)
{
	uint8_t buf[8];	/* RTC R/W buffer */
	uint16_t adr;


	IIC_INIT();		/* Initialize IIC function */

	/* Read RTC registers */
	if (!iic_read(0xD0, 0, 8, buf)) return 0;	/* IIC error */

	if (buf[7] & 0x20) {	/* When data has been volatiled, set default time */
		/* Clear nv-ram. Reg[8..63] */
		memset(buf, 0, 8);
		for (adr = 8; adr < 64; adr += 8) {
			iic_write(0x0D, adr, 8, buf);
		}
		/* Reset time to Jan 1, '08. Reg[0..7] */
		buf[4] = 1; buf[5] = 1; buf[6] = 8;
		iic_write(0x0D, 0, 8, buf);
	}
	return 1;
}

