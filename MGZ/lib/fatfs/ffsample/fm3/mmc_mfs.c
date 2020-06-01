/*------------------------------------------------------------------------*/
/* MB9BF616/617/618 MMCv3/SDv1/SDv2 (SPI mode) control module             */
/*------------------------------------------------------------------------*/
/*
/  Copyright (C) 2013, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/------------------------------------------------------------------------*/

/*----- Basic Configurations -----*/

#define MFS_CH		6			/* MFS channel (4-7) to control MMC/SD */
#define MFS_LOC		1			/* MFS pin relocation number (0-2) */
#define SCLK_FAST	7200000		/* SCLK under normal operation [Hz] */
#define	SCLK_SLOW	400000		/* SCLK under initialization [Hz] */
#define APB2CLK		72000000	/* Bus clock [Hz] */

#define	MMC_CD		!(PDIRA & 0x0008)	/* Card detect (yes:true, no:false, default:true) */
#define	MMC_WP		0				 	/* Write protected (yes:true, no:false, default:false) */

#define CTRL_INIT()	{ PDOR3 |= 0x0001; DDR3 |= 0x0001; PCRA |= 0x0008; }	/* Initialize control pins P30(CS)=H, PA3(INS)=pu */
#define CS_LOW()	PDOR3 &= ~0x0001	/* Set P30(CS) low */
#define CS_HIGH()	PDOR3 |= 0x0001		/* Set P30(CS) high */



/*--------------------------------------------------------------------------
   Module Private Functions and Macros
---------------------------------------------------------------------------*/

#include "FM3_type2.h"
#include "diskio.h"


#if   MFS_CH == 4
#define MFS_SMR   MFS4_SMR
#define MFS_SCR   MFS4_SCR
#define MFS_ESCR  MFS4_ESCR
#define MFS_SSR   MFS4_SSR
#define MFS_TDR   MFS4_TDR
#define MFS_RDR   MFS4_RDR
#define MFS_BGR   MFS4_BGR
#define MFS_FCR   MFS4_FCR
#define MFS_FCR0  MFS4_FCR0
#define MFS_FCR1  MFS4_FCR1
#define MFS_FBYTE MFS4_FBYTE
#define MFS_FBYTE1 MFS4_FBYTE1
#define MFS_FBYTE2 MFS4_FBYTE2
#if   MFS_LOC == 0
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 4)) | (20 << 4); PFRD |= 7 << 0; }
#elif MFS_LOC == 1
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 4)) | (42 << 4); PFR1 |= 7 << 10; }
#elif MFS_LOC == 2
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 4)) | (63 << 4); PFR0 |= 7 << 5; }
#endif

#elif MFS_CH == 5
#define MFS_SMR   MFS5_SMR
#define MFS_SCR   MFS5_SCR
#define MFS_ESCR  MFS5_ESCR
#define MFS_SSR   MFS5_SSR
#define MFS_TDR   MFS5_TDR
#define MFS_RDR   MFS5_RDR
#define MFS_BGR   MFS5_BGR
#define MFS_FCR   MFS5_FCR
#define MFS_FCR0  MFS5_FCR0
#define MFS_FCR1  MFS5_FCR1
#define MFS_FBYTE MFS5_FBYTE
#define MFS_FBYTE1 MFS5_FBYTE1
#define MFS_FBYTE2 MFS5_FBYTE2
#if   MFS_LOC == 0
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 10)) | (20 << 10); PFR6 |= 7 << 0; }
#elif MFS_LOC == 1
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 10)) | (42 << 10); PFR9 |= 7 << 2; }
#elif MFS_LOC == 2
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 10)) | (63 << 10); PFR3 |= 7 << 6; }
#endif

#elif MFS_CH == 6
#define MFS_SMR   MFS6_SMR
#define MFS_SCR   MFS6_SCR
#define MFS_ESCR  MFS6_ESCR
#define MFS_SSR   MFS6_SSR
#define MFS_TDR   MFS6_TDR
#define MFS_RDR   MFS6_RDR
#define MFS_BGR   MFS6_BGR
#define MFS_FCR   MFS6_FCR
#define MFS_FCR0  MFS6_FCR0
#define MFS_FCR1  MFS6_FCR1
#define MFS_FBYTE MFS6_FBYTE
#define MFS_FBYTE1 MFS6_FBYTE1
#define MFS_FBYTE2 MFS6_FBYTE2
#if   MFS_LOC == 0
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 16)) | (20 << 16); PFR5 |= 7 << 3; }
#elif MFS_LOC == 1
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 16)) | (42 << 16); PFR3 |= 7 << 1; }
#elif MFS_LOC == 2
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 16)) | (63 << 16); PFRF |= 7 << 3; }
#endif

#elif MFS_CH == 7
#define MFS_SMR   MFS7_SMR
#define MFS_SCR   MFS7_SCR
#define MFS_ESCR  MFS7_ESCR
#define MFS_SSR   MFS7_SSR
#define MFS_TDR   MFS7_TDR
#define MFS_RDR   MFS7_RDR
#define MFS_BGR   MFS7_BGR
#define MFS_FCR   MFS7_FCR
#define MFS_FCR0  MFS7_FCR0
#define MFS_FCR1  MFS7_FCR1
#define MFS_FBYTE MFS7_FBYTE
#define MFS_FBYTE1 MFS7_FBYTE1
#define MFS_FBYTE2 MFS7_FBYTE2
#if   MFS_LOC == 0
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 22)) | (20<< 22); PFR5 |= 7 << 9; }
#elif MFS_LOC == 1
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 22)) | (42 << 22); PFR4 |= 7 << 12; }
#elif MFS_LOC == 2
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(63 << 22)) | (63 << 22); PFRB |= 7 << 0; }
#endif

#else
#error Wrong MFS channel.

#endif

#if APB2CLK / SCLK_FAST - 1 < 3 || APB2CLK / SCLK_SLOW - 1 < 3
#error Wrong SCLK frequency setting.
#endif

#define FCLK_FAST() { MFS_BGR = APB2CLK / SCLK_FAST - 1; }
#define FCLK_SLOW() { MFS_BGR = APB2CLK / SCLK_SLOW - 1; }



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

/* Card type flags (CardType) */
#define CT_MMC		0x01		/* MMC ver 3 */
#define CT_SD1		0x02		/* SD ver 1 */
#define CT_SD2		0x04		/* SD ver 2 */
#define CT_SDC		(CT_SD1|CT_SD2)	/* SD */
#define CT_BLOCK	0x08		/* Block addressing */


static volatile
DSTATUS Stat = STA_NOINIT;	/* Physical drive status */

static volatile
UINT Timer1, Timer2;	/* 1kHz decrement timer stopped at zero (disk_timerproc()) */

static
BYTE CardType;			/* Card type flags */



/*-----------------------------------------------------------------------*/
/* MMC controls                                                          */
/*-----------------------------------------------------------------------*/

/* Exchange a byte */
static
BYTE xchg_spi (
	BYTE dat	/* Data to send */
)
{
	MFS_TDR = dat;
	while (!(MFS_SSR & 0x04)) ;
	return MFS_RDR;
}


/* Receive multiple byte */
static
void rcvr_spi_multi (
	BYTE *buff,		/* Pointer to data buffer */
	UINT btr		/* Number of bytes to receive (16, 64 or 512) */
)
{
	int n;


	for (n = 0; n < 14; n++)
		MFS_TDR = 0xFF;
	btr -= 14;
	while (btr) {
		while (!(MFS_SSR & 0x04)) ;
		*buff++ = MFS_RDR;
		MFS_TDR = 0xFF;
		btr--;
	}
	for (n = 0; n < 14; n++) {
		while (!(MFS_SSR & 0x04)) ;
		*buff++ = MFS_RDR;
	}
}


#if _USE_WRITE
/* Send multiple byte */
static
void xmit_spi_multi (
	const BYTE *buff,	/* Pointer to the data */
	UINT btx			/* Number of bytes to send (512) */
)
{
	int n;


	for (n = 0; n < 14; n++)
		MFS_TDR = *buff++;
	btx -= 14;
	while (btx) {
		while (!(MFS_SSR & 0x04)) ;
		MFS_RDR;
		MFS_TDR = *buff++;
		btx--;
	}
	for (n = 0; n < 14; n++) {
		while (!(MFS_SSR & 0x04)) ;
		MFS_RDR;
	}
}
#endif


/* Initialize MMC controls */
static
void init_spi (void)
{
	/* Initialize extra control ports CS/INS/WP */
	CTRL_INIT();

	/* Initialize MFS as SPI */
	MFS_SCR = 0x80;		/* Disable MFS */
	MFS_FBYTE2 = 0x01;	/* Rx FIFO trigger level = 1 */
	MFS_FCR = 0x000F;	/* Enable Tx/Rx FIFO */
	MFS_ESCR = 0x00;
	MFS_SMR = 0x4F;		/* SPI mode 0, Enable SCK/SO output */
	MFS_SCR = 0x23;		/* Enable MFS with SPI master, Tx/Rx enabled */

	ATTACH_MFS();		/* Attach MFS to the I/O pads */
}



/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/

static
int wait_ready (	/* 1:Ready, 0:Timeout */
	UINT wt			/* Timeout [ms] */
)
{
	BYTE d;


	Timer2 = wt;
	do {
		d = xchg_spi(0xFF);
		/* This loop takes a time. Insert rot_rdq() here for multitask envilonment. */
	} while (d != 0xFF && Timer2);	/* Wait for card goes ready or timeout */

	return (d == 0xFF) ? 1 : 0;
}



/*-----------------------------------------------------------------------*/
/* Deselect card and release SPI                                         */
/*-----------------------------------------------------------------------*/

static
void deselect (void)
{
	CS_HIGH();		/* Set CW# high */
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
	if (wait_ready(500)) return 1;	/* Wait for card ready */

	deselect();
	return 0;		/* Timeout */
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
	if(token != 0xFE) return 0;		/* Function fails if invalid DataStart token or timeout */

	rcvr_spi_multi(buff, btr);		/* Store trailing data to the buffer */
	xchg_spi(0xFF); xchg_spi(0xFF);	/* Discard CRC */

	return 1;						/* Function succeeded */
}



/*-----------------------------------------------------------------------*/
/* Send a data packet to the MMC                                         */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
static
int xmit_datablock (	/* 1:OK, 0:Failed */
	const BYTE *buff,	/* Ponter to 512 byte data to be sent */
	BYTE token			/* Token */
)
{
	BYTE resp;


	if (!wait_ready(500)) return 0;		/* Wait for card ready */

	xchg_spi(token);					/* Send token */
	if (token != 0xFD) {				/* Send data if token is other than StopTran */
		xmit_spi_multi(buff, 512);		/* Data */
		xchg_spi(0xFF); xchg_spi(0xFF);	/* Dummy CRC */

		resp = xchg_spi(0xFF);			/* Receive data resp */
		if ((resp & 0x1F) != 0x05) return 0;	/* Function fails if the data packet was not accepted */
	}
	return 1;
}
#endif


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
	xchg_spi(0x40 | cmd);				/* Start + command index */
	xchg_spi((BYTE)(arg >> 24));		/* Argument[31..24] */
	xchg_spi((BYTE)(arg >> 16));		/* Argument[23..16] */
	xchg_spi((BYTE)(arg >> 8));			/* Argument[15..8] */
	xchg_spi((BYTE)arg);				/* Argument[7..0] */
	n = 0x01;							/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;			/* Valid CRC for CMD0(0) */
	if (cmd == CMD8) n = 0x87;			/* Valid CRC for CMD8(0x1AA) */
	xchg_spi(n);

	/* Receive command resp */
	if (cmd == CMD12) xchg_spi(0xFF);	/* Diacard following one byte when CMD12 */
	n = 10;								/* Wait for response (10 bytes max) */
	do {
		res = xchg_spi(0xFF);
	} while ((res & 0x80) && --n);

	return res;							/* Return received response */
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

	init_spi();							/* Initialize MMC controls */
	FCLK_SLOW();
	for (n = 10; n; n--) xchg_spi(0xFF);	/* Send 80 dummy clocks */

	ty = 0;
	if (send_cmd(CMD0, 0) == 1) {			/* Put the card SPI/Idle state */
		Timer1 = 1000;						/* Initialization timeout = 1 sec */
		if (send_cmd(CMD8, 0x1AA) == 1) {	/* SDv2? */
			for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);	/* Get 32 bit return value of R7 resp */
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				/* Is the card supports vcc of 2.7-3.6V? */
				while (Timer1 && send_cmd(ACMD41, 1UL << 30)) ;	/* Wait for end of initialization with ACMD41(HCS) */
				if (Timer1 && send_cmd(CMD58, 0) == 0) {		/* Check CCS bit in the OCR */
					for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);
					ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* Card id SDv2 */
				}
			}
		} else {	/* Not SDv2 card */
			if (send_cmd(ACMD41, 0) <= 1) 	{	/* SDv1 or MMC? */
				ty = CT_SD1; cmd = ACMD41;	/* SDv1 (ACMD41(0)) */
			} else {
				ty = CT_MMC; cmd = CMD1;	/* MMCv3 (CMD1(0)) */
			}
			while (Timer1 && send_cmd(cmd, 0)) ;		/* Wait for end of initialization */
			if (!Timer1 || send_cmd(CMD16, 512) != 0)	/* Set block length: 512 */
				ty = 0;
		}
	}
	CardType = ty;	/* Card type */
	deselect();

	if (ty) {			/* OK */
		FCLK_FAST();			/* Set fast clock */
		Stat &= ~STA_NOINIT;	/* Clear STA_NOINIT flag */
	} else {			/* Failed */
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
	BYTE cmd;
	DWORD sect = (DWORD)sector;


	if (drv || !count) return RES_PARERR;		/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */
	if (!(CardType & CT_BLOCK)) sect *= 512;	/* LBA ot BA conversion (byte addressing cards) */

	cmd = count > 1 ? CMD18 : CMD17;			/*  READ_MULTIPLE_BLOCK : READ_SINGLE_BLOCK */
	if (send_cmd(cmd, sect) == 0) {
		do {
			if (!rcvr_datablock(buff, 512)) break;
			buff += 512;
		} while (--count);
		if (cmd == CMD18) send_cmd(CMD12, 0);	/* STOP_TRANSMISSION */
	}
	deselect();

	return count ? RES_ERROR : RES_OK;	/* Return result */
}



/*-----------------------------------------------------------------------*/
/* Write sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
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
		if (CardType & CT_SDC) send_cmd(ACMD23, count);	/* Predefine number of sectors */
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

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive number (0) */
	BYTE cmd,		/* Control command code */
	void *buff		/* Pointer to the conrtol data */
)
{
	DRESULT res;
	BYTE n, csd[16], *ptr = buff;
	DWORD st, ed, cs;
	LBA_t *dp;


	if (drv) return RES_PARERR;					/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

	res = RES_ERROR;

	switch (cmd) {
	case CTRL_SYNC :		/* Wait for end of internal write process of the card */
		if (select()) res = RES_OK;
		break;

	case GET_SECTOR_COUNT :	/* Get drive capacity in unit of sector (DWORD) */
		if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
			if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
				cs = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
				*(LBA_t*)buff = cs << 10;
			} else {					/* SDC ver 1.XX or MMC ver 3 */
				n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
				cs = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
				*(LBA_t*)buff = cs << (n - 9);
			}
			res = RES_OK;
		}
		break;

	case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
		if (CardType & CT_SD2) {	/* SDC ver 2.00 */
			if (send_cmd(ACMD13, 0) == 0) {	/* Read SD status */
				xchg_spi(0xFF);
				if (rcvr_datablock(csd, 16)) {				/* Read partial block */
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
			res = RES_OK;	/* FatFs does not check result of this command */
		}
		break;

	/* Following commands are not used by FatFs module */

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
#endif


/*-----------------------------------------------------------------------*/
/* Device Timer Driven Function                                          */
/*-----------------------------------------------------------------------*/
/* This function must be called from timer interrupt routine in period
/  of 1 ms to generate card control timing.
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
	if (MMC_WP) {	/* Write protected */
		s |= STA_PROTECT;
	} else {		/* Write enabled */
		s &= ~STA_PROTECT;
	}
	if (MMC_CD) {	/* Card is in socket */
		s &= ~STA_NODISK;
	} else {		/* Socket empty */
		s |= (STA_NODISK | STA_NOINIT);
	}
	Stat = s;
}

