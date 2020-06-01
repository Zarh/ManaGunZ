/*-----------------------------------------------------------------------*/
/* MMCv3/SDv1/SDv2 (in native mode via MCI) control module (C)ChaN, 2013 */
/*-----------------------------------------------------------------------*/
/* This program is opened under license policy of following trems.
/
/  Copyright (C) 2013, ChaN, all right reserved.
/
/ * This program is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial use UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/---------------------------------------------------------------------------*/

#include <string.h>
#include "LPC2300.h"
#include "interrupt.h"
#include "diskio.h"


/* These functions are defined in asmfunc.S */
void Copy_al2un (BYTE *dst, const DWORD *src, int count);	/* Copy aligned to unaligned. */
void Copy_un2al (DWORD *dst, const BYTE *src, int count);	/* Copy unaligned to aligned. */


/* --- MCI configurations --- */
#define N_BUF		4			/* Block transfer FIFO depth (>= 2) */
#define PCLK		72000000UL	/* PCLK supplied to MCI module */
#define MCLK_ID		400000UL	/* MCICLK for ID state (100k-400k) */
#define MCLK_RW		18000000UL	/* MCICLK for data transfer (PCLK divided by even number) */

/* This MCI driver assumes that MCLK_RW is CCLK/4 or slower. If block buffer underrun/overrun
/  occured due to any interrupt by higher priority process or slow external memory, increasing
/  N_BUF or decreasing MCLK_RW will solve it. */


/* ----- Port definitions ----- */
#define	MMC_CD		!(FIO0PIN2 & 0x20)	/* Card detect (yes:true, no:false, default:true) */
#define	MMC_WP		0				 	/* Write protected (yes:true, no:false, default:false) */


/* ----- MMC/SDC command ----- */
#define CMD0	(0)				/* GO_IDLE_STATE */
#define CMD1	(1)				/* SEND_OP_COND (MMC) */
#define CMD2	(2)				/* ALL_SEND_CID */
#define CMD3	(3)				/* SEND_RELATIVE_ADDR */
#define ACMD6	(6|0x80)		/* SET_BUS_WIDTH (SDC) */
#define CMD7	(7)				/* SELECT_CARD */
#define CMD8	(8)				/* SEND_IF_COND */
#define CMD9	(9)				/* SEND_CSD */
#define CMD10	(10)			/* SEND_CID */
#define CMD12	(12)			/* STOP_TRANSMISSION */
#define CMD13	(13)			/* SEND_STATUS */
#define ACMD13	(13|0x80)		/* SD_STATUS (SDC) */
#define CMD16	(16)			/* SET_BLOCKLEN */
#define CMD17	(17)			/* READ_SINGLE_BLOCK */
#define CMD18	(18)			/* READ_MULTIPLE_BLOCK */
#define	CMD23	(23)			/* SET_BLK_COUNT (MMC) */
#define	ACMD23	(23|0x80)		/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)			/* WRITE_BLOCK */
#define CMD25	(25)			/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)			/* ERASE_ER_BLK_START */
#define CMD33	(33)			/* ERASE_ER_BLK_END */
#define CMD38	(38)			/* ERASE */
#define	ACMD41	(41|0x80)		/* SEND_OP_COND (SDC) */
#define CMD55	(55)			/* APP_CMD */

/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

static volatile
DSTATUS Stat = STA_NOINIT;	/* Disk status */

static volatile
WORD Timer[2];			/* 1000Hz decrement timer for Transaction and Command */

static
WORD CardRCA;			/* Assigned RCA */
static
BYTE CardType,			/* Card type flag */
	 CardInfo[16+16+4];	/* CSD(16), CID(16), OCR(4) */

static volatile
BYTE XferStat, 		 	/* b3:MCI error, b2:Overrun, b1:Write, b0:Read */
	 XferWc,			/* Write block counter */
	 XferWp, XferRp;	/* R/W index of block FIFO */


/* Block transfer buffer (located in USB RAM) */
static
DWORD DmaBuff[N_BUF][128] __attribute__ ((section(".usbram"))), /* Block transfer FIFO */
	  LinkList[N_BUF][4] __attribute__ ((section(".usbram")));	/* DMA link list */




/*-----------------------------------------------------------------------*/
/* Interrupt service routine for data transfer                           */
/*-----------------------------------------------------------------------*/

static
void Isr_MCI (void)
{
	DWORD ms;
	BYTE n, xs;


	ms = MCI_STATUS & 0x073A;	/* Clear MCI interrupt status */
	MCI_CLEAR = ms;

	xs = XferStat;
	if (ms & 0x400) {			/* A block transfer completed (DataBlockEnd) */
		if (xs & 1) {				/* In card read operation */
			if (ms & 0x100) {			/* When last block is received (DataEnd), */
				GPDMA_SOFT_BREQ = 0x10;	/* Pop off remaining data in the MCIFIFO */
			}
			n = (XferWp + 1) % N_BUF;	/* Next write buffer */
			XferWp = n;
			if (n == XferRp) xs |= 4;	/* Check block overrun */
		}
		else {						/* In card write operation */
			n = (XferRp + 1) % N_BUF;	/* Next read buffer */
			XferRp = n;
			if (n == XferWp) xs |= 4;	/* Check block underrun */
		}
	} else {					/* An MCI error occured (not DataBlockEnd) */
		xs |= 8;
	}

	XferStat = xs;
}



static
void Isr_GPDMA (void)
{
	GPDMA_INT_TCCLR = 0x01;				/* Clear GPDMA interrupt flag */

	if (XferStat & 2) {					/* In write operation */
		if (--XferWc == N_BUF) {		/* Terminate LLI */
			LinkList[XferRp % N_BUF][2] = 0;
		}
	}
}




/*-----------------------------------------------------------------------*/
/* Ready for data reception                                              */
/*-----------------------------------------------------------------------*/

static
void ready_reception (
	UINT blks,		/* Number of blocks to receive (1..127) */
	UINT bs			/* Block size (64 or 512) */
)
{
	UINT n;
	DWORD dma_ctrl;


	/* ------ Setting up GPDMA Ch-0 ------ */

	GPDMA_CH0_CFG &= 0xFFF80420;		/* Disable ch-0 */
	GPDMA_INT_TCCLR = 0x01;				/* Clear interrupt flag */
	dma_ctrl = 0x88492000 | (bs / 4);	/* 1_000_1_0_00_010_010_010_010_************ */

	/* Create link list */
	for (n = 0; n < N_BUF; n++) {
		LinkList[n][0] = (DWORD)&MCI_FIFO;
		LinkList[n][1] = (DWORD)DmaBuff[n];
		LinkList[n][2] = (DWORD)LinkList[(n + 1) % N_BUF];
		LinkList[n][3] = dma_ctrl;
	}

	/* Load first LLI */
	GPDMA_CH0_SRC = LinkList[0][0];
	GPDMA_CH0_DEST = LinkList[0][1];
	GPDMA_CH0_LLI = LinkList[0][2];
	GPDMA_CH0_CTRL = LinkList[0][3];

	/* Enable ch-0 */
	GPDMA_CH0_CFG |= 0x19009;			/* *************_0_0_1_1_0_010_*_0000_*_0100_1 */

	/* --------- Setting up MCI ---------- */

	XferRp = 0;	XferWp = 0;					/* Block FIFO R/W index */
	XferStat = 1;							/* Transfer status: MCI --> Memory */

	MCI_DATA_LEN = bs * blks;				/* Set total data length */
	MCI_DATA_TMR = (DWORD)(MCLK_RW * 0.2);	/* Data timer: 0.2sec */
	MCI_CLEAR = 0x72A;						/* Clear status flags */
	MCI_MASK0 = 0x72A;						/* DataBlockEnd StartBitErr DataEnd RxOverrun DataTimeOut DataCrcFail */
	for (n = 0; bs > 1; bs >>= 1, n += 0x10);
	MCI_DATA_CTRL  = n | 0xB;				/* Start to receive data blocks */
}




/*-----------------------------------------------------------------------*/
/* Start to transmit a data block                                        */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
static
void start_transmission (
	UINT blks			/* Number of blocks to be transmitted (1..127) */
)
{
	UINT n;
	DWORD dma_ctrl;


	/* ------ Setting up GPDMA Ch-0 ------ */

	GPDMA_CH0_CFG &= 0xFFF80420;		/* Disable ch-0 */
	GPDMA_INT_TCCLR = 0x01;				/* Clear interrupt flag */
	dma_ctrl = 0x84492080;				/* 1_000_0_1_00_010_010_010_010_000010000000 */

	/* Create link list */
	for (n = 0; n < N_BUF; n++) {
		LinkList[n][0] = (DWORD)DmaBuff[n];
		LinkList[n][1] = (DWORD)&MCI_FIFO;
		LinkList[n][2] = (n == blks - 1) ? 0 : (DWORD)LinkList[(n + 1) % N_BUF];
		LinkList[n][3] = dma_ctrl;
	}

	/* Load first LLI */
	GPDMA_CH0_SRC = LinkList[0][0];
	GPDMA_CH0_DEST = LinkList[0][1];
	GPDMA_CH0_LLI = LinkList[0][2];
	GPDMA_CH0_CTRL = LinkList[0][3];

	/* Enable ch-0 */
	GPDMA_CH0_CFG |= 0x18901;			/* *************_0_0_1_1_0_001_*_0100_*_0000_1 */

	/* --------- Setting up MCI ---------- */

	XferRp = 0;								/* Block FIFO read index */
	XferWc = (BYTE)blks;
	XferStat = 2;							/* Transfer status: Memroy --> MCI */

	MCI_DATA_LEN = 512 * (blks + 1);		/* Set total data length */
	MCI_DATA_TMR = (DWORD)(MCLK_RW * 0.5);	/* Data timer: 0.5sec */
	MCI_CLEAR = 0x51A;						/* Clear status flags */
	MCI_MASK0 = 0x51A;						/* DataBlockEnd DataEnd TxUnderrun DataTimeOut DataCrcFail */
	MCI_DATA_CTRL  = (9 << 4) | 0x9;		/* Start to transmit data blocks */
}
#endif	/* _READONLY */




/*-----------------------------------------------------------------------*/
/* Stop data transfer                                                    */
/*-----------------------------------------------------------------------*/

static
void stop_transfer (void)
{
	MCI_MASK0 = 0;			/* Disable MCI interrupt */
	MCI_DATA_CTRL = 0;		/* Stop MCI data transfer */

	GPDMA_CH0_CFG &= 0xFFF80420;	/* Disable DMA ch-0 */
}




/*-----------------------------------------------------------------------*/
/* Power Control (Device dependent)                                      */
/*-----------------------------------------------------------------------*/

static
void power_on (void)
{
	/* Enable MCI and GPDMA power */
	__set_PCONP(PCSDC|PCGPDMA);

	/* Enable GPDMA controller with little-endian */
	GPDMA_CH0_CFG &= 0xFFF80000;	/* Disable DMA ch-0 */
	GPDMA_CONFIG = 0x01;

	/* Select PCLK for MCI, CCLK/1 = 72MHz */
	__set_PCLKSEL(PCLK_MCI, PCLKDIV_1);

	/* Attach MCI unit to I/O pad */
	__set_PINSEL(0, 19, 2);	/* MCICLK -> P0.19 */
	__set_PINSEL(0, 20, 2);	/* MCICMD -> P0.20 */
	__set_PINSEL(0, 21, 2);	/* MCIPWR -> P0.21 */
	__set_PINSEL(0, 22, 2);	/* MCIDAT0 -> P0.22 */
	__set_PINSEL(2, 11, 2);	/* MCIDAT1 -> P2.11 */
	__set_PINSEL(2, 12, 2);	/* MCIDAT2 -> P2.12 */
	__set_PINSEL(2, 13, 2);	/* MCIDAT3 -> P2.13 */

	MCI_MASK0 = 0;
	MCI_COMMAND = 0;
	MCI_DATA_CTRL = 0;

	/* Register interrupt handlers for MCI,DMA event */
	RegisterIrq(MCI_IRQn, Isr_MCI, PRI_LOWEST-1);
	RegisterIrq(GPDMA_IRQn, Isr_GPDMA, PRI_LOWEST-1);

	/* Power-on (VCC is always tied to the socket on this board) */
	MCI_POWER = 0x01;					/* Socket power on */
	for (Timer[0] = 10; Timer[0]; ) ;	/* 10ms */
	MCI_POWER = 0x03;					/* Enable signals */
}


static
void power_off (void)
{
	MCI_MASK0 = 0;
	MCI_COMMAND = 0;
	MCI_DATA_CTRL = 0;

	MCI_POWER = 0;			/* Power-off */
	MCI_CLOCK = 0;

	Stat |= STA_NOINIT;
}


/*-----------------------------------------------------------------------*/
/* Send a command token to the card and receive a response               */
/*-----------------------------------------------------------------------*/

static
int send_cmd (		/* Returns 1 when function succeeded otherwise returns 0 */
	UINT idx,		/* Command index (bit[5..0]), ACMD flag (bit7) */
	DWORD arg,		/* Command argument */
	UINT rt,		/* Expected response type. None(0), Short(1) or Long(2) */
	DWORD *buff		/* Response return buffer */
)
{
	UINT s, mc;


	if (idx & 0x80) {				/* Send a CMD55 prior to the specified command if it is ACMD class */
		if (!send_cmd(CMD55, (DWORD)CardRCA << 16, 1, buff)	/* When CMD55 is faild, */
			|| !(buff[0] & 0x00000020)) return 0;		/* exit with error */
	}
	idx &= 0x3F;					/* Mask out ACMD flag */

	do {							/* Wait while CmdActive bit is set */
		MCI_COMMAND = 0;			/* Cancel to transmit command */
		MCI_CLEAR = 0x0C5;			/* Clear status flags */
		for (s = 0; s < 10; s++) MCI_STATUS;	/* Skip lock out time of command reg. */
	} while (MCI_STATUS & 0x00800);

	MCI_ARGUMENT = arg;				/* Set the argument into argument register */
	mc = 0x400 | idx;				/* Enable bit + index */
	if (rt == 1) mc |= 0x040;		/* Set Response bit to reveice short resp */
	if (rt > 1) mc |= 0x0C0;		/* Set Response and LongResp bit to receive long resp */
	MCI_COMMAND = mc;				/* Initiate command transaction */

	Timer[1] = 100;
	for (;;) {						/* Wait for end of the cmd/resp transaction */
		if (!Timer[1]) return 0;
		s = MCI_STATUS;				/* Get the transaction status */
		if (rt == 0) {
			if (s & 0x080) return 1;	/* CmdSent */
		} else {
			if (s & 0x040) break;	/* CmdRespEnd */
			if (s & 0x001) { 		/* CmdCrcFail */
				if (idx == 1 || idx == 12 || idx == 41) break;	/* Ignore resp CRC error on CMD1/12/41 */
				return 0;
			}
			if (s & 0x004) return 0;	/* CmdTimeOut */
		}
	}

	buff[0] = MCI_RESP0;			/* Read the response words */
	if (rt == 2) {
		buff[1] = MCI_RESP1;
		buff[2] = MCI_RESP2;
		buff[3] = MCI_RESP3;
	}

	return 1;		/* Return with success */
}




/*-----------------------------------------------------------------------*/
/* Wait card ready                                                       */
/*-----------------------------------------------------------------------*/

static
int wait_ready (	/* Returns 1 when card is tran state, otherwise returns 0 */
	WORD tmr		/* Timeout in unit of 1ms */
)
{
	DWORD rc;


	Timer[0] = tmr;
	while (Timer[0]) {
		if (send_cmd(CMD13, (DWORD)CardRCA << 16, 1, &rc) && ((rc & 0x01E00) == 0x00800)) break;

		/* This loop takes a time. Insert rot_rdq() here for multitask envilonment. */

	}
	return Timer[0] ? 1 : 0;
}




/*-----------------------------------------------------------------------*/
/* Swap byte order                                                       */
/*-----------------------------------------------------------------------*/

static
void bswap_cp (BYTE *dst, const DWORD *src)
{
	DWORD d;


	d = *src;
	*dst++ = (BYTE)(d >> 24);
	*dst++ = (BYTE)(d >> 16);
	*dst++ = (BYTE)(d >> 8);
	*dst++ = (BYTE)(d >> 0);
}




/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS MCI_initialize (void)
{
	UINT cmd, n;
	DWORD resp[4];
	BYTE ty;


	if (Stat & STA_NODISK) return Stat;		/* No card in the socket */

	power_on();								/* Force socket power on */
	MCI_CLOCK = 0x100 | (PCLK/MCLK_ID/2-1);	/* Set MCICLK = MCLK_ID */
	for (Timer[0] = 2; Timer[0]; );

	send_cmd(CMD0, 0, 0, NULL);	 			/* Put the card into idle state */
	CardRCA = 0;

	/*---- Card is 'idle' state ----*/

	Timer[0] = 1000;						/* Initialization timeout of 1000 msec */
	if (send_cmd(CMD8, 0x1AA, 1, resp)		/* Is the card SDv2? */
		&& (resp[0] & 0xFFF) == 0x1AA) {		/* The card can work at vdd range of 2.7-3.6V */
		do {									/* Wait while card is busy state (use ACMD41 with HCS bit) */

			/* This loop takes a time. Insert task rotation here for multitask envilonment. */

			if (!Timer[0]) goto di_fail;
		} while (!send_cmd(ACMD41, 0x40FF8000, 1, resp) || !(resp[0] & 0x80000000));
		ty = (resp[0] & 0x40000000) ? CT_SD2|CT_BLOCK : CT_SD2;	/* Check CCS bit in the OCR */
	}
	else {									/* SDv1 or MMCv3 */
		if (send_cmd(ACMD41, 0x00FF8000, 1, resp)) {
			ty = CT_SD1; cmd = ACMD41;			/* ACMD41 is accepted -> SDC Ver1 */
		} else {
			ty = CT_MMC; cmd = CMD1;			/* ACMD41 is rejected -> MMC */
		}
		do {									/* Wait while card is busy state (use ACMD41 or CMD1) */

			/* This loop will take a time. Insert task rotation here for multitask envilonment. */

			if (!Timer[0]) goto di_fail;
		} while (!send_cmd(cmd, 0x00FF8000, 1, resp) || !(resp[0] & 0x80000000));
	}

	CardType = ty;							/* Save card type */
	bswap_cp(&CardInfo[32], resp);			/* Save OCR */

	/*---- Card is 'ready' state ----*/

	if (!send_cmd(CMD2, 0, 2, resp)) goto di_fail;	/* Enter ident state */
	for (n = 0; n < 4; n++) bswap_cp(&CardInfo[n * 4 + 16], &resp[n]);	/* Save CID */

	/*---- Card is 'ident' state ----*/

	if (ty & CT_SDC) {						/* SDC: Get generated RCA and save it */
		if (!send_cmd(CMD3, 0, 1, resp)) goto di_fail;
		CardRCA = (WORD)(resp[0] >> 16);
	} else {								/* MMC: Assign RCA to the card */
		if (!send_cmd(CMD3, 1 << 16, 1, resp)) goto di_fail;
		CardRCA = 1;
	}

	/*---- Card is 'stby' state ----*/

	if (!send_cmd(CMD9, (DWORD)CardRCA << 16, 2, resp)) goto di_fail;	/* Get CSD and save it */
	for (n = 0; n < 4; n++) bswap_cp(&CardInfo[n * 4], &resp[n]);
	if (!send_cmd(CMD7, (DWORD)CardRCA << 16, 1, resp)) goto di_fail;	/* Select card */

	/*---- Card is 'tran' state ----*/

	if (!(ty & CT_BLOCK)) {		/* Set data block length to 512 (for byte addressing cards) */
		if (!send_cmd(CMD16, 512, 1, resp) || (resp[0] & 0xFDF90000)) goto di_fail;
	}

	if (ty & CT_SDC) {		/* Set wide bus mode (for SDCs) */
		if (!send_cmd(ACMD6, 2, 1, resp) || (resp[0] & 0xFDF90000)) {	/* Set wide bus mode of SDC */
			goto di_fail;
		}
		MCI_CLOCK |= 0x800;					/* Set wide bus mode of MCI */
	}

	MCI_CLOCK = (MCI_CLOCK & 0xF00) | 0x200 | (PCLK/MCLK_RW/2-1);		/* Set MCICLK = MCLK_RW, power-save mode */

	Stat &= ~STA_NOINIT;	/* Clear STA_NOINIT */
	return Stat;

di_fail:
	power_off();
	Stat |= STA_NOINIT;		/* Set STA_NOINIT */
	return Stat;
}




/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS MCI_status (void)
{
	return Stat;
}




/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT MCI_read (
	BYTE *buff,			/* Pointer to the data buffer to store read data */
	LBA_t sector,		/* Start sector number (LBA) */
	UINT count			/* Sector count (1..127) */
)
{
	DWORD resp, sect = (DWORD)sector;
	UINT cmd;
	BYTE rp;


	if (count < 1 || count > 127) return RES_PARERR;	/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check drive status */

	if (!(CardType & CT_BLOCK)) sect *= 512;	/* Convert LBA to byte address if needed */
	if (!wait_ready(500)) return RES_ERROR;		/* Make sure that card is tran state */

	ready_reception(count, 512);			/* Ready to receive data blocks */
	cmd = (count > 1) ? CMD18 : CMD17;		/* Transfer type: Single block or Multiple block */
	if (send_cmd(cmd, sect, 1, &resp)		/* Start to read */
		&& !(resp & 0xC0580000)) {
		rp = 0;
		do {
			while ((rp == XferWp) && !(XferStat & 0xC)) {	/* Wait for block arrival */
				/* This loop will take a time. Replace it with sync process for multitask envilonment. */
			}
			if (XferStat & 0xC) break;			/* Abort if any error has occured */
			Copy_al2un(buff, DmaBuff[rp], 512);	/* Pop an block */
			XferRp = rp = (rp + 1) % N_BUF;		/* Next DMA buffer */
			if (XferStat & 0xC) break;			/* Abort if overrun has occured */
			buff += 512; 						/* Next user buffer address */
		} while (--count);
	}
	stop_transfer();						/* Close data path */
	if (count || cmd == CMD18) {			/* Terminate to read if needed */
		send_cmd(CMD12, 0, 1, &resp);
	}

	return count ? RES_ERROR : RES_OK;
}




/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT MCI_write (
	const BYTE *buff,	/* Pointer to the data to be written */
	LBA_t sector,		/* Start sector number (LBA) */
	UINT count			/* Sector count (1..127) */
)
{
	DWORD resp, sect = (DWORD)sector;
	UINT cmd;
	BYTE wp, xc;

	if (count < 1 || count > 127) return RES_PARERR;	/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check drive status */
	if (Stat & STA_PROTECT) return RES_WRPRT;	/* Check write protection */

	if (!(CardType & CT_BLOCK)) sect *= 512;	/* Convert LBA to byte address if needed */
	if (!wait_ready(500)) return RES_ERROR;		/* Make sure that card is tran state */

	if (count == 1) {	/* Single block write */
		cmd = CMD24;
	} else {			/* Multiple block write */
		cmd = (CardType & CT_SDC) ? ACMD23 : CMD23;
		if (!send_cmd(cmd, count, 1, &resp)		/* Preset number of blocks to write */
			|| (resp & 0xC0580000)) {
			return RES_ERROR;
		}
		cmd = CMD25;
	}

	if (!send_cmd(cmd, sect, 1, &resp)			/* Send a write command */
		|| (resp & 0xC0580000)) {
		return RES_ERROR;
	}

	wp = 0; xc = count;
	do {										/* Fill block FIFO */
		Copy_un2al(DmaBuff[wp], (BYTE*)(UINT)buff, 512);	/* Push a block */
		wp++;										/* Next DMA buffer */
		count--; buff += 512; 			 			/* Next user buffer address */
	} while (count && wp < N_BUF);
	XferWp = wp = wp % N_BUF;
	start_transmission(xc);						/* Start transmission */

	while (count) {
		while((wp == XferRp) && !(XferStat & 0xC)) {	/* Wait for block FIFO not full */
			/* This loop will take a time. Replace it with sync process for multitask envilonment. */
		}
		if (XferStat & 0xC) break;					/* Abort if block underrun or any MCI error has occured */
		Copy_un2al(DmaBuff[wp], (BYTE*)(UINT)buff, 512);	/* Push a block */
		XferWp = wp = (wp + 1) % N_BUF;				/* Next DMA buffer */
		if (XferStat & 0xC) break;					/* Abort if block underrun has occured */
		count--; buff += 512;						/* Next user buffer address */
	}

	while (!(XferStat & 0xC));					/* Wait for all blocks sent (block underrun) */
	if (XferStat & 0x8) count = 1;				/* Abort if any MCI error has occured */

	stop_transfer();							/* Close data path */
	if (count || (cmd == CMD25 && (CardType & CT_SDC))) { /* Terminate to write if needed */
		send_cmd(CMD12, 0, 1, &resp);
	}

	return count ? RES_ERROR : RES_OK;
}




/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT MCI_ioctl (
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive data block */
)
{
	DRESULT res;
	BYTE b, *ptr = buff, sdstat[64];
	DWORD resp[4], d, st, ed;
	LBA_t *dp;
	static const DWORD au_size[] = {1, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 24576, 32768, 49152, 65536, 131072};


	if (Stat & STA_NOINIT) return RES_NOTRDY;

	res = RES_ERROR;

	switch (cmd) {
		case CTRL_SYNC :	/* Make sure that all data has been written on the media */
			if (wait_ready(500)) res = RES_OK;	/* Wait for card enters tarn state */
			break;

		case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
			if ((CardInfo[0] >> 6) == 1) {	/* SDC CSD v2.0 */
				d = CardInfo[9] + ((WORD)CardInfo[8] << 8) + ((DWORD)(CardInfo[7] & 63) << 16) + 1;
				*(LBA_t*)buff = d << 10;
			} else {						/* MMC or SDC CSD v1.0 */
				b = (CardInfo[5] & 15) + ((CardInfo[10] & 128) >> 7) + ((CardInfo[9] & 3) << 1) + 2;
				d = (CardInfo[8] >> 6) + ((WORD)CardInfo[7] << 2) + ((WORD)(CardInfo[6] & 3) << 10) + 1;
				*(LBA_t*)buff = d << (b - 9);
			}
			res = RES_OK;
			break;

		case GET_BLOCK_SIZE :	/* Get erase block size in unit of sectors (DWORD) */
			if (CardType & CT_SD2) {	/* SDC ver 2.00 */
				if (MCI_ioctl(MMC_GET_SDSTAT, sdstat)) break;
				*(DWORD*)buff = au_size[sdstat[10] >> 4];
			} else {					/* SDC ver 1.XX or MMC */
				if (CardType & CT_SD1) {	/* SDC v1 */
					*(DWORD*)buff = (((CardInfo[10] & 63) << 1) + ((WORD)(CardInfo[11] & 128) >> 7) + 1) << ((CardInfo[13] >> 6) - 1);
				} else {					/* MMC */
					*(DWORD*)buff = ((WORD)((CardInfo[10] & 124) >> 2) + 1) * (((CardInfo[11] & 3) << 3) + ((CardInfo[11] & 224) >> 5) + 1);
				}
			}
			res = RES_OK;
			break;

		case CTRL_TRIM :		/* Erase a block of sectors */
			if (!(CardType & CT_SDC) || (!(CardInfo[0] >> 6) && !(CardInfo[10] & 0x40))) break;	/* Check if sector erase can be applied to the card */
			dp = buff; st = (DWORD)dp[0]; ed = (DWORD)dp[1];
			if (!(CardType & CT_BLOCK)) {
				st *= 512; ed *= 512;
			}
			if (send_cmd(CMD32, st, 1, resp) && send_cmd(CMD33, ed, 1, resp) && send_cmd(CMD38, 0, 1, resp) && wait_ready(30000)) {
				res = RES_OK;
			}
			break;

		case CTRL_POWER_OFF :
			power_off();		/* Power off */
			res = RES_OK;
			break;

		case MMC_GET_TYPE :		/* Get card type flags (1 byte) */
			*ptr = CardType;
			res = RES_OK;
			break;

		case MMC_GET_CSD :		/* Get CSD (16 bytes) */
			memcpy(buff, &CardInfo[0], 16);
			res = RES_OK;
			break;

		case MMC_GET_CID :		/* Get CID (16 bytes) */
			memcpy(buff, &CardInfo[16], 16);
			res = RES_OK;
			break;

		case MMC_GET_OCR :		/* Get OCR (4 bytes) */
			memcpy(buff, &CardInfo[32], 4);
			res = RES_OK;
			break;

		case MMC_GET_SDSTAT :	/* Receive SD status as a data block (64 bytes) */
			if (CardType & CT_SDC) {	/* SDC */
				if (wait_ready(500)) {
					ready_reception(1, 64);				/* Ready to receive data blocks */
					if (send_cmd(ACMD13, 0, 1, resp)	/* Start to read */
							&& !(resp[0] & 0xC0580000)) {
						while ((XferWp == 0) && !(XferStat & 0xC));
						if (!(XferStat & 0xC)) {
							Copy_al2un(buff, DmaBuff[0], 64);
							res = RES_OK;
						}
					}
				}
				stop_transfer();					/* Close data path */
			}
			break;

		default:
			res = RES_PARERR;
	}

	return res;
}




/*-----------------------------------------------------------------------*/
/* Device Timer Interrupt Procedure                                      */
/*-----------------------------------------------------------------------*/
/* This function must be called in period of 1ms                         */

void MCI_timerproc (void)
{
	BYTE s;
	WORD n;


	/* 1000Hz decrement timers */
	if ((n = Timer[0]) > 0) Timer[0] = --n;
	if ((n = Timer[1]) > 0) Timer[1] = --n;

	s = Stat;
	if (MMC_WP) {			/* Write protected */
		s |= STA_PROTECT;
	} else {				/* Write enabled */
		s &= ~STA_PROTECT;
	}
	if (MMC_CD) {			/* Card is in socket */
		s &= ~STA_NODISK;
	} else {				/* Socket empty */
		s |= (STA_NODISK | STA_NOINIT);
	}
	Stat = s;
}

