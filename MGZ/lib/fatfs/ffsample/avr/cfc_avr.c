/*-----------------------------------------------------------------------*/
/* CF Card control module                                                */
/*-----------------------------------------------------------------------*/
/*
/  Copyright (C) 2016, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ff.h"
#include "diskio.h"
#include "cfc_avr.h"


/* Contorl ports */
#define	CTRL_PORT		PORTC
#define	CTRL_DDR		DDRC
#define	DAT_PORT		PORTA
#define	DAT_DDR			DDRA
#define	DAT_PIN			PINA

/* Bit definitions for control port */
#define	REG_DATA		0b11110000	/* Select Data register */
#define	REG_ERROR		0b11110001	/* Select Error register */
#define	REG_FEATURES	0b11110001	/* Select Features register */
#define	REG_COUNT		0b11110010	/* Select Count register */
#define	REG_SECTOR		0b11110011	/* Select Sector register */
#define	REG_CYLL		0b11110100	/* Select Cylinder low register */
#define	REG_CYLH		0b11110101	/* Select Cylinder high regitser */
#define	REG_DEV			0b11110110	/* Select Device register */
#define	REG_COMMAND		0b11110111	/* Select Command register */
#define	REG_STATUS		0b11110111	/* Select Status register */
#define	REG_DEVCTRL		0b11101110	/* Select Device control register */
#define	REG_ALTSTAT		0b11101110	/* Select Alternative Setatus register */
#define	IORD			0b00100000	/* IORD# bit in the control port */
#define	IOWR			0b01000000	/* IOWR# bit in the control port */
#define	RESET			0b10000000	/* RESE# bit in the control port */
#define CF_EXIST		1			/* True if both CD1 and CD2 are low. (no catd detect function) */

/* ATA command */
#define CMD_READ		0x20	/* READ SECTOR(S) */
#define CMD_WRITE		0x30	/* WRITE SECTOR(S) */
#define CMD_ERASE		0xC0	/* ERASE SECTOR(S) */
#define CMD_IDENTIFY	0xEC	/* DEVICE IDENTIFY */
#define CMD_SETFEATURES	0xEF	/* SET FEATURES */

/* ATA register bit definitions */
#define	LBA				0x40	/* REG_DEV */
#define	BSY				0x80	/* REG_STATUS */
#define	DRDY			0x40	/* REG_STATUS */
#define	DRQ				0x08	/* REG_STATUS */
#define	ERR				0x01	/* REG_STATUS */
#define	SRST			0x04	/* REG_DEVCTRL */
#define	NIEN			0x02	/* REG_DEVCTRL */


/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

static volatile DSTATUS Stat = STA_NOINIT;	/* Disk status */

static volatile UINT Timer;		/* 100Hz decrement timer */



static void delay_ms (
	UINT ms
)
{
	ms /= 10;
	cli(); Timer = ms; sei();
	do {
		cli(); ms = Timer; sei();
	} while (ms);
}



/*-----------------------------------------------------------------------*/
/* Socket Power Controls  (Platform dependent)                           */
/*-----------------------------------------------------------------------*/

static void power_on (void)
{
	/* Socket power on */
	{
		/* Nothing to do */
	}

	/* Enable control signals, RESET# = L */
	CTRL_PORT = IORD | IOWR;
	CTRL_DDR = 0xFF;

	DAT_DDR = 0; DAT_PORT = 0xFF;	/* Pull-up D7..D0 */

	delay_ms(10);			/* 10ms */
	CTRL_PORT |= RESET;		/* RESET# = H */
	delay_ms(20);			/* 20ms */
}


static void power_off (void)
{
	Stat |= STA_NOINIT;
#if 0
	DAT_DDR = 0; DAT_PORT = 0; 		/* Set D7..D0 hi-z */
	CTRL_DDR = 0; CTRL_PORT = 0;	/* Set controls hi-z */

	/* Socket power off */
#endif
}



/*-----------------------------------------------------------------------*/
/* Read ATA register (Platform dependent)                                */
/*-----------------------------------------------------------------------*/

static BYTE read_ata (
	BYTE reg			/* Register to be read */
)
{
	BYTE rd;


	CTRL_PORT = reg;		/* Set address [CS1#,CS0#,A2..A0] */
	CTRL_PORT &= ~IORD;		/* IORD# = L */
	CTRL_PORT; CTRL_PORT; CTRL_PORT;	/* Delay */
	rd = DAT_PIN;			/* Get data */
	CTRL_PORT |= IORD;		/* IORD# = H */

	return rd;
}


static void read_ata_block (
	BYTE *buff		/* Buffer to store read data (512 bytes) */
)
{
	BYTE d, c, iord_l, iord_h;


	CTRL_PORT = REG_DATA;		/* Select data register */
	iord_h = REG_DATA;
	iord_l = iord_h & ~IORD;
	c = 255;
	CTRL_PORT = iord_l;		/* IORD# = L */
	CTRL_PORT; CTRL_PORT;	/* delay */
	d = DAT_PIN;			/* Get even data */
	CTRL_PORT = iord_h;		/* IORD# = H */
	do {	/* Receive 2 bytes/loop */
		CTRL_PORT = iord_l;		/* IORD# = L */
		*buff++ = d;			/* Store even data (delayed) */
		d = DAT_PIN;			/* Get odd data */
		CTRL_PORT = iord_h;		/* IORD# = H */
		CTRL_PORT = iord_l;		/* IORD# = L */
		*buff++ = d;			/* Store odd data (delayed) */
		d = DAT_PIN;			/* Get even data */
		CTRL_PORT = iord_h;		/* IORD# = H */
	} while (--c);	/* Repeat 255 times */
	CTRL_PORT = iord_l;		/* IORD# = L */
	*buff++ = d;			/* Store even data (delayed) */
	d = DAT_PIN;			/* Get odd data */
	CTRL_PORT = iord_h;		/* IORD# = H */
	*buff++ = d;			/* Store odd data (delayed) */
}


static void read_ata_part (
	BYTE *buf,
	BYTE ofs,
	BYTE nw
)
{
	BYTE c, dl, dh;


	CTRL_PORT = REG_DATA;		/* Select Data register */
	c = 0;
	do {
		CTRL_PORT &= ~IORD;		/* IORD# = L */
		CTRL_PORT; CTRL_PORT;	/* Delay */
		dl = DAT_PIN;			/* Read even byte */
		CTRL_PORT |= IORD;		/* IORD# = H */
		CTRL_PORT &= ~IORD;		/* IORD# = L */
		CTRL_PORT; CTRL_PORT;	/* Delay */
		dh = DAT_PIN;			/* Read odd byte */
		CTRL_PORT |= IORD;		/* IORD# = H */
		if (nw && (c >= ofs)) {	/* Pick up a part of block */
			*buf++ = dl; *buf++ = dh;
			nw--;
		}
	} while (++c);
}



/*-----------------------------------------------------------------------*/
/* Write data to ATA register (Platform dependent)                       */
/*-----------------------------------------------------------------------*/

static void write_ata (
	BYTE reg,		/* Register to be written */
	BYTE dat		/* Data to be written */
)
{
	CTRL_PORT = reg;		/* Set address [CS1#,CS0#,A2..A0] */
	DAT_DDR = 0xFF;			/* Set D7..D0 as output */
	DAT_PORT = dat;			/* Set data on the D7..D0 */
	CTRL_PORT &= ~IOWR;		/* IOWR# = L */
	CTRL_PORT; CTRL_PORT;	/* Delay */
	CTRL_PORT |= IOWR;		/* IOWR# = H */
	DAT_PORT = 0xFF;		/* Set D7..D0 as input (pull-up) */
	DAT_DDR = 0;
}


#if !FF_FS_READONLY
static void write_ata_block (
	const BYTE *buff	/* Data to write (512 bytes) */
)
{
	BYTE c, iowr_l, iowr_h;


	CTRL_PORT = REG_DATA;	/* Select data register */
	iowr_h = REG_DATA;
	iowr_l = iowr_h & ~IOWR;
	DAT_DDR = 0xFF;			/* Set D0..D7 as output */
	c = 0;
	do {	/* Write 2 bytes/loop */
		DAT_PORT = *buff++;		/* Set even data */
		CTRL_PORT = iowr_l;		/* IOWR# = L */
		CTRL_PORT;				/* Delay */
		CTRL_PORT = iowr_h;		/* IOWR# = H */
		DAT_PORT = *buff++;		/* Set odd data */
		CTRL_PORT = iowr_l;		/* IOWR# = L */
		CTRL_PORT;				/* Delay */
		CTRL_PORT = iowr_h;		/* IOWR# = H */
	} while (--c);	/* Repeat 256 times */
	DAT_PORT = 0xFF;		/* Set D0..D7 as input (pull-up) */
	DAT_DDR = 0;
}
#endif


/*-----------------------------------------------------------------------*/
/* Wait for BSY goes 0 and the bit goes 1                                */
/*-----------------------------------------------------------------------*/

static int wait_stat (	/* 0:Timeout or ERR bit goes 1 */
	UINT ms,	/* Timeout in unit of ms */
	BYTE bit	/* Bit mask to wait for */
)
{
	BYTE s;

	ms /= 10;
	cli(); Timer = ms; sei();
	do {
		s = read_ata(REG_STATUS);				/* Get status */
		cli(); ms = Timer; sei();
		if (ms == 0 || (s & ERR)) return 0;		/* Abort when timeout or error occured */
	} while ((s & BSY) || (bit && !(bit & s)));	/* Wait for BSY goes 0 and the specified bit goes 1 */

	read_ata(REG_ALTSTAT);
	return 1;
}



/*-----------------------------------------------------------------------*/
/* Issue Read/Write command to the drive                                 */
/*-----------------------------------------------------------------------*/

static int issue_rwcmd (
	BYTE cmd,		/* CMD_READ or CMD_WRITE */
	DWORD sector,	/* Start sector (28-bit LBA) */
	BYTE count		/* 1..255, 0:256 */
)
{

	if (!wait_stat(1000, DRDY)) return 0;

	write_ata(REG_DEV, ((BYTE)(sector >> 24) & 0x0F) | LBA);
	write_ata(REG_CYLH, (BYTE)(sector >> 16));
	write_ata(REG_CYLL, (BYTE)(sector >> 8));
	write_ata(REG_SECTOR, (BYTE)sector);
	write_ata(REG_COUNT, (BYTE)count);
	write_ata(REG_COMMAND, cmd);

	return 1;
}



/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS cf_disk_initialize (void)
{
	power_off();							/* Power off */
	delay_ms(200);							/* 100ms */
	if (Stat & STA_NODISK) return Stat;		/* Exit if socket is empty */

	power_on();								/* Initialize control port and socket power on */

	write_ata(REG_DEVCTRL, SRST);			/* Set software reset */
	delay_ms(20);
	write_ata(REG_DEVCTRL, 0);				/* Release software reset */
	delay_ms(20);

	if (!wait_stat(3000, 0)) return Stat;	/* Select device 0 */
	write_ata(REG_DEV, 0);
	if (!wait_stat(3000, DRDY)) return Stat;

	write_ata(REG_FEATURES, 0x03);			/* Set default PIO mode w/o IORDY */
	write_ata(REG_COUNT, 0x01);
	write_ata(REG_COMMAND, CMD_SETFEATURES);
	if (!wait_stat(3000, DRDY)) return Stat;

	write_ata(REG_FEATURES, 0x01);			/* Select 8-bit PIO transfer mode */
	write_ata(REG_COMMAND, CMD_SETFEATURES);
	if (!wait_stat(1000, DRDY)) return Stat;

	Stat &= ~STA_NOINIT;					/* Initialization succeeded */

	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS cf_disk_status (void)
{
	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT cf_disk_read (
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Sector number (LBA) */
	UINT count		/* Sector count (1..256) */
)
{
	DWORD sector32 = (DWORD)sector;


	if (count == 0 || count > 256 || sector32 >= 0x10000000) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;

	/* Issue Read Setor(s) command */
	if (!issue_rwcmd(CMD_READ, sector32, (BYTE)count)) return RES_ERROR;

	/* Receive data blocks */
	do {
		if (!wait_stat(2500, DRQ)) return RES_ERROR;
		read_ata_block(buff);
		buff += 512;
	} while (--count);
	read_ata(REG_ALTSTAT);
	read_ata(REG_STATUS);

	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if !FF_FS_READONLY
DRESULT cf_disk_write (
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Sector number (LBA) */
	UINT count			/* Sector count (1..256) */
)
{
	DWORD sector32 = (DWORD)sector;

	if (count == 0 || count > 256 || sector32 >= 0x10000000) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;

	/* Issue Write Setor(s) command */
	if (!issue_rwcmd(CMD_WRITE, sector32, (BYTE)count)) return RES_ERROR;

	/* Send data blocks */
	do {
		if (!wait_stat(2500, DRQ)) return RES_ERROR;
		write_ata_block(buff);
		buff += 512;
	} while (--count);

	/* Wait for end of write process */
	if (!wait_stat(1000, 0)) return RES_ERROR;
	read_ata(REG_ALTSTAT);
	read_ata(REG_STATUS);

	return RES_OK;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT cf_disk_ioctl (
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive data block */
)
{
	BYTE n, w, ofs, dl, dh, *ptr = (BYTE*)buff;


	if (Stat & STA_NOINIT) return RES_NOTRDY;

	switch (cmd) {
	case CTRL_SYNC :		/* Nothing to do */
		return RES_OK;

	case GET_BLOCK_SIZE :	/* Get erase block size in sectors (DWORD) */
		*(DWORD*)buff = 256;	/* Fixed to 256 */
		return RES_OK;

	case CTRL_POWER_OFF :	/* Power off */
		power_off();
		return RES_OK;

	case GET_SECTOR_COUNT :
		for (n = 0; n < sizeof (LBA_t); ptr[n++] = 0) ;
		ofs = 60; w = 2; n = 0;
		break;

	case ATA_GET_REV :		/* Get firmware revision (8 chars) */
		ofs = 23; w = 4; n = 4;
		break;

	case ATA_GET_MODEL :	/* Get model name (40 chars) */
		ofs = 27; w = 20; n = 20;
		break;

	case ATA_GET_SN :		/* Get serial number (20 chars) */
		ofs = 10; w = 10; n = 10;
		break;

	default:
		return RES_PARERR;
	}

	if (!wait_stat(1000, DRDY)) return RES_ERROR;
	write_ata(REG_COMMAND, CMD_IDENTIFY);	/* Get device ID data block */
	if (!wait_stat(1000, DRQ)) return RES_ERROR;	/* Wait for data ready */
	read_ata_part(ptr, ofs, w);					/* Get a part of data block */
	while (n--) {				/* Swap byte order */
		dl = *ptr++; dh = *ptr--;
		*ptr++ = dh; *ptr++ = dl; 
	}
	read_ata(REG_ALTSTAT);
	read_ata(REG_STATUS);

	return RES_OK;
}
#endif


/*-----------------------------------------------------------------------*/
/* Device timer interrupt procedure                                      */
/*-----------------------------------------------------------------------*/
/* This function must be called in interval of 10ms */


void cf_disk_timerproc (void)
{
	UINT t;


	t = Timer;					/* 100Hz decrement timer */
	if (t) Timer = --t;

	if (CF_EXIST) {	/* Card inserted */
		Stat &= ~STA_NODISK;
	} else {		/* Socket empty */
		Stat |= STA_NODISK | STA_NOINIT;
	}
}

