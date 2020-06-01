/*------------------------------------------------------------------------*/
/* FRK-RX62N: MMCv3/SDv1/SDv2+ (in SPI mode) Control Module               */
/*------------------------------------------------------------------------*/
/*
/  Copyright (C) 2014, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include <machine.h>	/* Platform dependent include file */
#include "iodefine.h"	/* Platform dependent include file */
#include "diskio.h"		/* Common include file for ff.c and disk layer */


#define RSPI_CH	0	/* RSPI channel: 0:RSPIA-A, 1:RSPIB-A, 10:RSPIA-B, 11:RSPIB-B */

#define	CS_LOW()	PORTC.DR.BIT.B4 = 0		/* Set CS Low */
#define	CS_HIGH()	PORTC.DR.BIT.B4 = 1		/* Set CS High */
#define	MMC_CD		(!PORT0.PORT.BIT.B7)	/* Card status switch (Exist:True, Empty:False) */
#define	MMC_WP		0 						/* Write protect switch (Protected:True, Enabled:False) */
#define CTRL_INIT()	{	/* Initialize CS,CD,WP control port */\
	PORTC.DR.BIT.B4 = 1; /* CS=OUT */	\
	PORTC.DDR.BIT.B4 = 1; /* CS=H */	\
	PORT0.ICR.BIT.B7 = 1; /* CD=IN */	\
}

#define F_PCLK		96000000UL	/* PCLK frequency (configured by SCKCR.PCK) */
#define SCLK_FAST	12000000UL	/* SCLK frequency (R/W) */
#define	SCLK_SLOW	400000UL	/* SCLK frequency (Init) */


#if RSPI_CH == 0	/* RSPIA-A */
#define RSPI	RSPI0
#define	RSPI_ATTACH() {			\
	PORTC.ICR.BIT.B7 = 1;		\
	IOPORT.PFGSPI.BYTE = 0x0E;	\
	MSTP_RSPI0 = 0;				\
}

#elif RSPI_CH == 10	/* RSPIA-B */
#define RSPI	RSPI0
#define	RSPI_ATTACH() {			\
	PORTA.ICR.BIT.B7 = 1;		\
	IOPORT.PFGSPI.BYTE = 0x0F;	\
	MSTP_RSPI0 = 0;				\
}

#elif RSPI_CH == 1	/* RSPIB-A */
#define RSPI	RSPI1
#define	RSPI_ATTACH() {			\
	PORT3.ICR.BIT.B0 = 1;		\
	IOPORT.PFHSPI.BYTE = 0x0E;	\
	MSTP_RSPI1 = 0;				\
}

#elif RSPI_CH == 11	/* RSPIB-B */
#define RSPI	RSPI1
#define	RSPI_ATTACH() {			\
	PORTE.ICR.BIT.B7 = 1;		\
	IOPORT.PFHSPI.BYTE = 0x0F;	\
	MSTP_RSPI1 = 0;				\
}

#endif

#define FCLK_FAST() {					\
	RSPI.SPCR.BIT.SPE = 0;				\
	RSPI.SPBR.BYTE = F_PCLK/2/SCLK_FAST-1;	\
	RSPI.SPCR.BIT.SPE = 1;				\
}

#ifdef __LIT
#define LDDW(x) revl(x)	/* Little endian: swap bytes */
#else
#define LDDW(x) x		/* Big endian: no swap */
#endif



/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

/* MMC/SD command */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */



static volatile
DSTATUS Stat = STA_NOINIT;	/* Physical drive status */

static volatile
WORD Timer1, Timer2;	/* 1000Hz decrement timer stopped at zero (driven by disk_timerproc()) */

static
BYTE CardType;			/* Card type flags */



/*-----------------------------------------------------------------------*/
/* Control SPI module                                                    */
/*-----------------------------------------------------------------------*/
/* Only these five functions are platform dependent. Any other functions */
/* are portable to different system.                                     */

/*---------------------------------*/
/* Enable SPI and MMC/SDC controls */
/*---------------------------------*/
static
void power_on (void)
{
	/* Initialize CS/CD/WP port */
	CTRL_INIT();

	/* Attach RSPI module to I/O pads, disable module stop */
	RSPI_ATTACH();

	/* Initialize RSPI module */
	RSPI.SPCR.BYTE = 0;		/* Stop RSPI module */
	RSPI.SPPCR.BYTE = 0;	/* Fixed idle value, disable loop-back mode */
	RSPI.SPSCR.BYTE = 0;	/* Disable sequence control */
	RSPI.SPDCR.BYTE = 0x20;	/* SPLW=1 */
	RSPI.SPCMD0.WORD = 0x0700;	/* LSBF=0, SPB=7, BRDV=0, CPOL=0, CPHA=0 */
	RSPI.SPBR.BYTE = F_PCLK / 2 / SCLK_SLOW - 1;	/* Bit rate */
	RSPI.SPCR.BYTE = 0x49;	/* Start RSPI in master mode */
}


/*---------------------*/
/*    Disable SPI      */
/*---------------------*/
static
void power_off (void)	/* Disable MMC/SDC interface */
{
	RSPI.SPCR.BYTE = 0;		/* Stop RSPI module */
}


/*---------------------*/
/* Send/Receive a byte */
/*---------------------*/
static
BYTE xchg_spi (
	BYTE dat	/* Data to send */
)
{
	RSPI.SPDR.LONG = dat;			/* Start transmission (lower 8bits) */
	while (!RSPI.SPSR.BIT.SPRF) ;	/* Wait for end of transfer */
	return RSPI.SPDR.LONG;			/* Returen received byte (lower 8bits) */
}


/*---------------------*/
/* Send multiple bytes */
/*---------------------*/
static
void xmit_spi_multi (
	const BYTE *buff,	/* Pointer to the data */
	UINT btx			/* Number of bytes to send (multiple of 4) */
)
{
	const DWORD *lp = (const DWORD*)buff;


	RSPI.SPCMD0.BIT.SPB = 3;	/* Set SPI 32-bit mode */

	do {
		RSPI.SPDR.LONG = LDDW(*lp++);	/* Send four data bytes */
		while (!RSPI.SPSR.BIT.SPRF) ;	/* Wait for end of transfer */
		RSPI.SPDR.LONG;					/* Discard four received bytes */
	} while (btx -= 4);					/* Repeat until all data sent */

	RSPI.SPCMD0.BIT.SPB = 7;	/* Set SPI 8-bit mode */
}


/*------------------------*/
/* Receive multiple bytes */
/*------------------------*/
static
void rcvr_spi_multi (
	BYTE *buff,		/* Pointer to data buffer */
	UINT btr		/* Number of bytes to receive (multiple of 4) */
)
{
	DWORD *lp = (DWORD*)buff;


	RSPI.SPCMD0.BIT.SPB = 3;	/* Set SPI 32-bit mode */

	do {
		RSPI.SPDR.LONG = 0xFFFFFFFF;	/* Send four 0xFFs */
		while (!RSPI.SPSR.BIT.SPRF) ;	/* Wait for end of transfer */
		*lp++ = LDDW(RSPI.SPDR.LONG);	/* Store four received bytes */
	} while (btr -= 4);					/* Repeat until all data received */

	RSPI.SPCMD0.BIT.SPB = 7;	/* Set SPI 8-bit mode */
}




/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/

static
int wait_ready (	/* 1:Ready, 0:Timeout */
	UINT wt			/* Timeout [ms] */
)
{
	Timer2 = (WORD)wt;

	do {
		if (xchg_spi(0xFF) == 0xFF) return 1;	/* Card goes ready */

		/* This loop takes a time. Insert rot_rdq() here for multitask envilonment. */

	} while (Timer2);	/* Wait until card goes ready or timeout */

	return 0;	/* Timeout occured */
}



/*-----------------------------------------------------------------------*/
/* Deselect card and release SPI                                         */
/*-----------------------------------------------------------------------*/

static
void deselect (void)
{
	CS_HIGH();		/* Set CS# high */
	xchg_spi(0xFF);	/* Dummy clock (force DO hi-z for multiple slave SPI) */
}



/*-----------------------------------------------------------------------*/
/* Select card and wait for ready                                        */
/*-----------------------------------------------------------------------*/

static
int select (void)	/* 1:OK, 0:Timeout */
{
	CS_LOW();		/* Set CS# low */
	xchg_spi(0xFF);	/* Dummy clock (force DO enabled) */

	if (wait_ready(500)) return 1;	/* Leading busy check: Wait for card ready */

	deselect();
	return 0;	/* Failed to select the card due to timeout */
}



/*-----------------------------------------------------------------------*/
/* Receive a data packet from the MMC                                    */
/*-----------------------------------------------------------------------*/

static
int rcvr_datablock (	/* 1:OK, 0:Error */
	BYTE *buff,			/* Data buffer */
	UINT btr			/* Data block length (byte) */
)
{
	BYTE token;


	Timer1 = 200;
	do {							/* Wait for DataStart token in timeout of 200ms */
		token = xchg_spi(0xFF);

		/* This loop will take a time. Insert rot_rdq() here for multitask envilonment. */

	} while ((token == 0xFF) && Timer1);
	if (token != 0xFE) return 0;	/* Function fails if invalid DataStart token or timeout */

	rcvr_spi_multi(buff, btr);		/* Store trailing data to the buffer */
	xchg_spi(0xFF); xchg_spi(0xFF);	/* Discard CRC */

	return 1;						/* Function succeeded */
}



/*-----------------------------------------------------------------------*/
/* Send a data packet to the MMC                                         */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0
static
int xmit_datablock (	/* 1:OK, 0:Failed */
	const BYTE *buff,	/* Ponter to 512 byte data to be sent */
	BYTE token			/* Token */
)
{
	BYTE resp;


	if (!wait_ready(500)) return 0;		/* Leading busy check: Wait for card ready to accept data block */

	xchg_spi(token);					/* Send token */
	if (token == 0xFD) return 1;		/* Do not send data if token is StopTran */

	xmit_spi_multi(buff, 512);			/* Data */
	xchg_spi(0xFF); xchg_spi(0xFF);		/* Dummy CRC */

	resp = xchg_spi(0xFF);				/* Receive data resp */

	return (resp & 0x1F) == 0x05 ? 1 : 0;	/* Data was accepted or not */

	/* Busy check is done at next transmission */
}
#endif /* _USE_WRITE */



/*-----------------------------------------------------------------------*/
/* Send a command packet to the MMC                                      */
/*-----------------------------------------------------------------------*/

static
BYTE send_cmd (		/* Return value: R1 resp (bit7==1:Failed to send) */
	BYTE cmd,		/* Command index */
	DWORD arg		/* Argument */
)
{
	BYTE n, res;


	if (cmd & 0x80) {	/* Send a CMD55 prior to ACMD<n> */
		cmd &= 0x7F;
		res = send_cmd(CMD55, 0);
		if (res > 1) return res;
	}

	/* Select the card and wait for ready except to stop multiple block read */
	if (cmd != CMD12) {
		deselect();
		if (!select()) return 0xFF;
	}

	/* Send command packet */
	xchg_spi(0x40 | cmd);			/* Start + command index */
	xchg_spi((BYTE)(arg >> 24));	/* Argument[31..24] */
	xchg_spi((BYTE)(arg >> 16));	/* Argument[23..16] */
	xchg_spi((BYTE)(arg >> 8));		/* Argument[15..8] */
	xchg_spi((BYTE)arg);			/* Argument[7..0] */
	n = 0x01;						/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;		/* Valid CRC for CMD0(0) */
	if (cmd == CMD8) n = 0x87;		/* Valid CRC for CMD8(0x1AA) */
	xchg_spi(n);

	/* Receive command resp */
	if (cmd == CMD12) xchg_spi(0xFF);	/* Diacard stuff byte on CMD12 */
	n = 10;							/* Wait for response (10 bytes max) */
	do
		res = xchg_spi(0xFF);
	while ((res & 0x80) && --n);

	return res;						/* Return received response */
}



/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize disk drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE drv		/* Physical drive number (0) */
)
{
	BYTE n, cmd, ty, ocr[4];


	if (drv) return STA_NOINIT;			/* Supports only drive 0 */

	power_on();							/* Initialize RSPI */
	for (n = 10; n; n--) xchg_spi(0xFF);/* Send 80 dummy clocks */

	ty = 0;
	if (send_cmd(CMD0, 0) == 1) {			/* Put the card SPI state */
		Timer1 = 1000;						/* Initialization timeout = 1 sec */
		if (send_cmd(CMD8, 0x1AA) == 1) {	/* Is the card SDv2? */
			for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);	/* Get 32 bit return value of R7 resp */
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				/* Does the card support 2.7-3.6V? */
				while (Timer1 && send_cmd(ACMD41, 1UL << 30)) ;	/* Wait for end of initialization with ACMD41(HCS) */
				if (Timer1 && send_cmd(CMD58, 0) == 0) {		/* Check CCS bit in the OCR */
					for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);
					ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* Check if the card is SDv2 */
				}
			}
		} else {	/* Not an SDv2 card */
			if (send_cmd(ACMD41, 0) <= 1) 	{	/* SDv1 or MMC? */
				ty = CT_SD1; cmd = ACMD41;	/* SDv1 (ACMD41(0)) */
			} else {
				ty = CT_MMC; cmd = CMD1;	/* MMCv3 (CMD1(0)) */
			}
			while (Timer1 && send_cmd(cmd, 0)) ;		/* Wait for end of initialization */
			if (!Timer1 || send_cmd(CMD16, 512) != 0) ty = 0;	/* Set block length: 512 */
		}
	}
	CardType = ty;	/* Card type */
	deselect();

	if (ty) {			/* OK */
		FCLK_FAST();			/* Set fast clock */
		Stat &= ~STA_NOINIT;	/* Clear STA_NOINIT flag */
	} else {			/* Failed */
		power_off();
		Stat = STA_NOINIT;
	}

	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Get disk status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive number (0) */
)
{
	if (drv) return STA_NOINIT;		/* Supports only drive 0 */

	return Stat;	/* Return disk status */
}



/*-----------------------------------------------------------------------*/
/* Read sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive number (0) */
	BYTE *buff,		/* Pointer to the data buffer to store read data */
	LBA_t sector,	/* Start sector number (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	DWORD sect = (DWORD)sector;


	if (drv || !count) return RES_PARERR;		/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

	if (!(CardType & CT_BLOCK)) sect *= 512;	/* LBA ot BA conversion (byte addressing cards) */

	if (count == 1) {	/* Single sector read */
		if ((send_cmd(CMD17, sect) == 0)	/* READ_SINGLE_BLOCK */
			&& rcvr_datablock(buff, 512)) {
			count = 0;
		}
	}
	else {				/* Multiple sector read */
		if (send_cmd(CMD18, sect) == 0) {	/* READ_MULTIPLE_BLOCK */
			do {
				if (!rcvr_datablock(buff, 512)) break;
				buff += 512;
			} while (--count);
			send_cmd(CMD12, 0);				/* STOP_TRANSMISSION */
		}
	}
	deselect();

	return count ? RES_ERROR : RES_OK;	/* Return result */
}



/*-----------------------------------------------------------------------*/
/* Write sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive number (0) */
	const BYTE *buff,	/* Ponter to the data to write */
	LBA_t sector,		/* Start sector number (LBA) */
	UINT count			/* Number of sectors to write (1..128) */
)
{
	DWORD sect = (DWORD)sector;


	if (drv || !count) return RES_PARERR;		/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check drive status */
	if (Stat & STA_PROTECT) return RES_WRPRT;	/* Check write protect */

	if (!(CardType & CT_BLOCK)) sect *= 512;	/* LBA ==> BA conversion (byte addressing cards) */

	if (count == 1) {	/* Single sector write */
		if ((send_cmd(CMD24, sect) == 0)	/* WRITE_BLOCK */
			&& xmit_datablock(buff, 0xFE)) {
			count = 0;
		}
	}
	else {				/* Multiple sector write */
		if (CardType & CT_SDC) send_cmd(ACMD23, count);
		if (send_cmd(CMD25, sect) == 0) {	/* WRITE_MULTIPLE_BLOCK */
			do {
				if (!xmit_datablock(buff, 0xFC)) break;
				buff += 512;
			} while (--count);
			if (!xmit_datablock(0, 0xFD)) count = 1;	/* STOP_TRAN token */
		}
	}
	deselect();

	return count ? RES_ERROR : RES_OK;	/* Return result */
}
#endif



/*-----------------------------------------------------------------------*/
/* Miscellaneous drive controls other than data read/write               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive number (0) */
	BYTE ctrl,		/* Control command code */
	void *buff		/* Pointer to the conrtol data */
)
{
	DRESULT res;
	BYTE n, csd[16], *ptr = buff;
	DWORD st, ed, csz;
	LBA_t *dp;


	if (drv) return RES_PARERR;					/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

	res = RES_ERROR;

	switch (ctrl) {
	case CTRL_SYNC :		/* Wait for end of internal write process of the drive */
		if (select()) res = RES_OK;
		break;

	case GET_SECTOR_COUNT :	/* Get drive capacity in unit of sector (DWORD) */
		if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
			if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
				csz = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
				*(LBA_t*)buff = csz << 10;
			} else {					/* SDC ver 1.XX or MMC ver 3 */
				n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
				csz = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
				*(LBA_t*)buff = csz << (n - 9);
			}
			res = RES_OK;
		}
		break;

	case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
		if (CardType & CT_SD2) {	/* SDC ver 2.00 */
			if (send_cmd(ACMD13, 0) == 0) {	/* Read SD status */
				xchg_spi(0xFF);	/* Discard 2nd byte of R2 resp. */
				if (rcvr_datablock(csd, 16)) {					/* Read partial block */
					for (n = 64 - 16; n; n--) xchg_spi(0xFF);	/* Purge trailing data */
					*(DWORD*)buff = 16UL << (csd[10] >> 4);
					res = RES_OK;
				}
			}
		} else {					/* SDC ver 1.XX or MMC */
			if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {	/* Read CSD */
				if (CardType & CT_SD1) {	/* SDC ver 1.XX */
					*(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
				} else {					/* MMC */
					*(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
				}
				res = RES_OK;
			}
		}
		break;

	case CTRL_TRIM :	/* Erase a block of sectors (used when _USE_TRIM == 1) */
		if (!(CardType & CT_SDC)) break;				/* Check if the card is SDC */
		if (disk_ioctl(drv, MMC_GET_CSD, csd)) break;	/* Get CSD */
		if (!(csd[0] >> 6) && !(csd[10] & 0x40)) break;	/* Check if sector erase can be applied to the card */
		dp = buff; st = (DWORD)dp[0]; ed = (DWORD)dp[1];	/* Load sector block */
		if (!(CardType & CT_BLOCK)) {
			st *= 512; ed *= 512;
		}
		if (send_cmd(CMD32, st) == 0 && send_cmd(CMD33, ed) == 0 && send_cmd(CMD38, 0) == 0 && wait_ready(30000)) {	/* Erase sector block */
			res = RES_OK;
		}
		break;

	/* Following command are not used by FatFs module */

	case MMC_GET_TYPE :		/* Get MMC/SDC type (BYTE) */
		*ptr = CardType;
		res = RES_OK;
		break;

	case MMC_GET_CSD :		/* Read CSD (16 bytes) */
		if (send_cmd(CMD9, 0) == 0 && rcvr_datablock(ptr, 16)) {	/* READ_CSD */
			res = RES_OK;
		}
		break;

	case MMC_GET_CID :		/* Read CID (16 bytes) */
		if (send_cmd(CMD10, 0) == 0 && rcvr_datablock(ptr, 16)) {	/* READ_CID */
			res = RES_OK;
		}
		break;

	case MMC_GET_OCR :		/* Read OCR (4 bytes) */
		if (send_cmd(CMD58, 0) == 0) {	/* READ_OCR */
			for (n = 4; n; n--) *ptr++ = xchg_spi(0xFF);
			res = RES_OK;
		}
		break;

	case MMC_GET_SDSTAT :	/* Read SD status (64 bytes) */
		if (send_cmd(ACMD13, 0) == 0) {	/* SD_STATUS */
			xchg_spi(0xFF);
			if (rcvr_datablock(ptr, 64)) res = RES_OK;
		}
		break;

	default:
		res = RES_PARERR;
	}

	deselect();

	return res;
}


/*-----------------------------------------------------------------------*/
/* Device timer function                                                 */
/*-----------------------------------------------------------------------*/
/* This function must be called from system timer process
/  in period of 1 ms to generate card control timing.
*/

void disk_timerproc (void)
{
	WORD n;
	BYTE s;


	n = Timer1;						/* 1kHz decrement timer stopped at 0 */
	if (n) Timer1 = --n;
	n = Timer2;
	if (n) Timer2 = --n;

	s = Stat;
	if (MMC_WP) {		/* Write protected */
		s |= STA_PROTECT;
	} else {		/* Write enabled */
		s &= ~STA_PROTECT;
	}
	if (MMC_CD) {		/* Card is in socket */
		s &= ~STA_NODISK;
	} else {		/* Socket empty */
		s |= (STA_NODISK | STA_NOINIT);
	}
	Stat = s;
}

