/*--------------------------------------------------------------------------*/
/* FTL driver for SLC small block NAND flash                  (C)ChaN, 2013 */
/*--------------------------------------------------------------------------*/
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

#include "LPC2300.h"
#include "diskio.h"

/* Fast memcpy functions (defined in asmfunc.S). These functions are equivalent to generic memcpy() but faster. */
void Copy_al2un (BYTE *dst, const DWORD *src, int count);	/* Copy aligned to unaligned */
void Copy_un2al (DWORD *dst, const BYTE *src, int count);	/* Copy unaligned to aligned */



/* NAND flash and FTL configurations (depends on the memory chip) */

#define	N_TOTAL_BLKS	8192	/* Total number of erase blocks on the memory chip (8MB:1024, 16MB:1024, 32MB:2048, 64MB:4096, 128MB:8192) */
#define	N_SIZE_BLK		32		/* Erase block size (8MB:16, 16MB+:32) */
#define	N_RES_BLKS		1		/* Number of top blocks to be reserved for system (1 or larger) */
#define	P_SPARE_BLKS	3		/* Percentage of spare blocks in total blocks */

#define	N_SPARE_BLKS	(N_TOTAL_BLKS * P_SPARE_BLKS / 100)			/* Number of spare blocks */
#define	N_USER_BLKS		(N_TOTAL_BLKS - N_RES_BLKS - N_SPARE_BLKS)	/* Number of user blocks */
#define MAX_LBA			(N_USER_BLKS * N_SIZE_BLK)					/* Number of user sectors */



/*--------------------------------------------------------------------------*/
/* Module private work area                                                 */
/*--------------------------------------------------------------------------*/

static
WORD BlockStat[N_TOTAL_BLKS] __attribute__ ((section(".etherram")));	/* Physical block status (2 * N_TOTAL_BLKS bytes) */
/* 0xFFFF:Blank, 0xFFFE:Bad, 0 to N_USER_BLKS-1:Live (logical block number) */

static
DWORD BlockBuff[N_SIZE_BLK][132];	/* Block buffer (528 * N_SIZE_BLK bytes) */
/* Physical sector organization */
/*
/ DWORD : Description
/ 0-63  : Sector data 1 (256 bytes)
/ 64-127: Sector data 2 (256 bytes)
/ 128   : b31-16: Logical block number (inverted)
/         b15-0:  Logical block number
/ 129   : b31-0: Bad Block Mark (!=0xFFFFFFFF:Bad)
/ 130   : b31-24: 0xFF=Blank sector, !0xFF=Live sector
/         b21-0:  ECC of sector data 1
/ 131   : b31-24: Not used (Don't care)
/         b21-0:  ECC of sector data 2
*/


static
BYTE PageStat[N_SIZE_BLK];			/* Page status in the block buffer (1:ECC checked) */

static
WORD LogBlock, PhyBlock, BadBlocks;	/* Loaded logical block, Corresponding physical block, Number of bad blocks */
static
BYTE Init, BlockDirty;				/* Initialized, Loaded block needed to be written back */



/*--------------------------------------------------------------------------*/
/* NAND flash media access functions via GPIO (platform dependent)          */
/*--------------------------------------------------------------------------*/

#define NAND_DATA_OUT(d)	FIO3PIN0 = d	/* Set write data on the D0..7 */
#define NAND_DATA_IN()		FIO3PIN0		/* Get value on the  D0..7 */
#define NAND_DIR_IN()		FIO3DIR0=0		/* Set D0..7 direction input */
#define NAND_DIR_OUT()		FIO3DIR0=0xFF	/* Set D0..7 direction output */

#define NAND_READY()		(FIO2PIN0 & 0x80)	/* Check RDY/BSY# signal (True:ready, False:busy) */

#define NAND_CTRL_INIT()	FIO2DIR0 = 0x3F	/* Set CLE/ALE/RE/WE/CE/WP as output */

#define NAND_CLE_H()		FIO2SET0=0x01	/* Set CLE high */
#define NAND_CLE_L()		FIO2CLR0=0x01	/* Set CLE low */
#define NAND_ALE_H()		FIO2SET0=0x02	/* Set ALE high */
#define NAND_ALE_L()		FIO2CLR0=0x02	/* Set ALE low */
#define NAND_RE_H()			FIO2SET0=0x04	/* Set RE# high */
#define NAND_RE_L()			FIO2CLR0=0x04	/* Set RE# low */
#define NAND_WE_H()			FIO2SET0=0x08	/* Set WE# high */
#define NAND_WE_L()			FIO2CLR0=0x08	/* Set WE# low */
#define NAND_CE_H()			FIO2SET0=0x10	/* Set CE# high */
#define NAND_CE_L()			FIO2CLR0=0x10	/* Set CE# low */
#define NAND_WP_H()			FIO2SET0=0x20	/* Set WP# high */
#define NAND_WP_L()			FIO2CLR0=0x20	/* Set WP# low*/


/*-------------------------------------*/
/* Wait until memory chip goes ready   */

static
void nand_wait (void)
{
	while (!NAND_READY()) ;
}


/*-------------------------------------*/
/* Send a command byte to the memory   */

static
void nand_cmd (
	BYTE cmd
)
{
	NAND_DATA_OUT(cmd);
	NAND_DIR_OUT();
	NAND_CLE_H();
	NAND_WE_L(); NAND_WE_L();
	NAND_WE_H(); NAND_WE_H();
	NAND_CLE_L();
}


/*-------------------------------------*/
/* Send an address byte to the memory  */

static
void nand_adr (
	BYTE cmd
)
{
	NAND_DATA_OUT(cmd);
	NAND_DIR_OUT();
	NAND_ALE_H();
	NAND_WE_L(); NAND_WE_L();
	NAND_WE_H(); NAND_WE_H();
	NAND_ALE_L();
}


/*-------------------------------------*/
/* Read a byte from the memory         */

static
BYTE nand_read_byte (void)
{
	BYTE rb;


	NAND_DIR_IN();
	NAND_RE_L(); NAND_RE_L(); NAND_RE_L();
	rb = NAND_DATA_IN();
	NAND_RE_H();

	return rb;
}


/*-------------------------------------*/
/* Read multiple byte from the memory  */

static
void nand_read_multi (
	BYTE* buff,		/* Pointer to the buffer to store the read data */
	UINT bc			/* Number of bytes to read (even number) */
)
{
	NAND_DIR_IN();
	do {
		NAND_RE_L(); NAND_RE_L(); NAND_RE_L();
		*buff++ = NAND_DATA_IN();
		NAND_RE_H();
		NAND_RE_L(); NAND_RE_L(); NAND_RE_L();
		*buff++ = NAND_DATA_IN();
		NAND_RE_H();
	} while (bc -= 2);
}


/*-------------------------------------*/
/* Write multiple byte to the memory   */

static
void nand_write_multi (
	const BYTE* buff,	/* Pointer to the data to be written */
	UINT bc				/* Number of bytes to write (even number) */
)
{
	NAND_DIR_OUT();
	do {
		NAND_DATA_OUT(*buff++);
		NAND_WE_L(); NAND_WE_L();
		NAND_WE_H();
		NAND_DATA_OUT(*buff++);
		NAND_WE_L(); NAND_WE_L();
		NAND_WE_H();
	} while (bc -= 2);
}


/*-------------------------------------*/
/* Initialize memory I/F               */

static
void nand_init (void)
{
	NAND_CE_H();
	NAND_ALE_L();
	NAND_CLE_L();
	NAND_RE_H();
	NAND_WE_H();
	NAND_CTRL_INIT();
	NAND_CE_L();
	NAND_WP_H();

	nand_cmd(0xFF);
}



/*--------------------------------------------------------------------------*/
/* NAND flash control functions                                             */
/*--------------------------------------------------------------------------*/

/*-------------------------------------*/
/* Read page(s)                        */

static
void read_page (
	DWORD* buff,	/* Read data buffer */
	DWORD sa,		/* Physical sector address */
	UINT sc,		/* Number of sectors to read */
	UINT bs			/* Number of bytes per sector (4,8,12,16 or 528) */
)
{
	nand_wait();
	nand_cmd(bs <= 16 ? 0x50 : 0x00);	/* Read mode 1 or 3 */
	nand_adr(0);
	nand_adr((BYTE)(sa));
	nand_adr((BYTE)(sa >> 8));
	nand_adr((BYTE)(sa >> 16));
	do {
		nand_wait();
		nand_read_multi((BYTE*)buff, bs);
		buff += bs / 4;
	} while (--sc);
}



/*-------------------------------------*/
/* Write page(s)                       */

static
int write_page (		/* 0:Failed, 1:Successful */
	const DWORD* buff,	/* 528 byte sectors to be written */
	DWORD sa,			/* Physical sector address */
	UINT sc				/* Number of sectors to write */
)
{
	do {
		nand_wait();
		nand_cmd(0x80);				/* Data load command */
		nand_adr(0);				/* Physical sector address */
		nand_adr((BYTE)(sa));
		nand_adr((BYTE)(sa >> 8));
		nand_adr((BYTE)(sa >> 16));
		nand_write_multi((const BYTE*)buff, 528);	/* Load a sector data */
		nand_cmd(0x10);				/* Initiate to write */
		nand_wait();
		nand_cmd(0x70);				/* Check write result */
		if (nand_read_byte() & 0x01) return 0;
		buff += 132;				/* Next sector data */
		sa++;						/* Next sector address */
	} while (--sc);

	return 1;
}



/*-------------------------------------*/
/* Erase a physical block              */

static
int erase_phy_block (	/* 0:Failed, 1:Successful */
	WORD blk			/* Physical block to be erased */
)
{
	DWORD sa = (DWORD)blk * N_SIZE_BLK;

//	xprintf("[E:%d]", blk);
	nand_wait();
	nand_cmd(0x60);				/* Erase command */
	nand_adr((BYTE)(sa));		/* Physical block address */
	nand_adr((BYTE)(sa >> 8));
	nand_adr((BYTE)(sa >> 16));
	nand_cmd(0xD0);				/* Initiate to erase */
	nand_wait();
	nand_cmd(0x70);				/* Check erase result */

	BlockStat[blk] = 0xFFFF;	/* Mark the block 'blanked' */

	return (nand_read_byte() & 0x01) ? 0 : 1;
}



/*-----------------------------------------------------*/
/* Find and load a logical block into the block buffer */

static
void load_block (
	WORD lb,		/* Logical block number to be loaded */
	int load		/* 1:Load, 0:Do not load because the entire block is to be overwritten */
)
{
	UINT pb, i, j;


	/* Find the logical block */
	for (pb = N_RES_BLKS; pb < N_TOTAL_BLKS && BlockStat[pb] != lb; pb++) ;

	if (pb == N_TOTAL_BLKS) {	/* The logical block is not exist */
		for (i = 0; i < N_SIZE_BLK; i++) {	/* Initialize the block buffer as all blank sector */
			for (j = 0; j < 132; j++)
				BlockBuff[i][j] = 0xFFFFFFFF;
		}
		pb = 0;		/* No physical block */
	//	xprintf("[L:%d,B]", lb);
	} else {	/* Found the logical block */
		if (load)
			read_page(BlockBuff[0], (DWORD)pb * N_SIZE_BLK, N_SIZE_BLK, 528);
	//	xprintf("[L:%d,L]", lb);
	}

	PhyBlock = pb;	/* Current physical block */
	LogBlock = lb;	/* Current logical block */
	BlockDirty = 0;
	for (i = 0; i < N_SIZE_BLK; i++) PageStat[i] = 0;
}



/*------------------------------------*/
/* Mark an erase block as 'bad block' */

static
void bad_block (
	WORD pb			/* Physical block to be marked bad */
)
{
	DWORD sa;
	DWORD buf[4];
	int i;


//	xprintf("[B:%d]", pb);
	buf[0] = 0xFFFFFFFF;
	buf[2] = 0xFFFFFFFF;
	buf[3] = 0xFFFFFFFF;

	for (sa = (DWORD)pb * N_SIZE_BLK; sa / N_SIZE_BLK == pb; sa++) {
		nand_wait();				/* Wait for ready */
		nand_cmd(0x80);				/* Data load command */
		nand_adr(0);				/* Physical sector address */
		nand_adr((BYTE)(sa));
		nand_adr((BYTE)(sa >> 8));
		nand_adr((BYTE)(sa >> 16));
		buf[1] = 0xFFFFFFFF;		/* Load data area (not programmed) */
		for (i = 0; i < 32; i++)
			nand_write_multi((const BYTE*)buf, 16);
		buf[1] = 0;					/* Set bad block mark */
		nand_write_multi((const BYTE*)buf, 16);
		nand_cmd(0x10);				/* Initiate to write */
	}
	nand_wait();

	BlockStat[pb] = 0xFFFE;			/* Mark the block 'bad' */
}



/*----------------------------------------------*/
/* Write-back block buffer into NAND flash      */

static
int flush_block (void)
{
	WORD pb, pbs;
	UINT i;


	if (BlockDirty) {
		for (i = 0; i < N_SIZE_BLK; i++) {				/* Re-initialize block status */
			BlockBuff[i][128] = LogBlock | (~LogBlock << 16);
			BlockBuff[i][129] = 0xFFFFFFFF;
		}
		pb = pbs = PhyBlock ? PhyBlock : N_RES_BLKS;	/* Find a free block */
		for (;;) {
			if (BadBlocks >= N_SPARE_BLKS) return 0;	/* Too many bad blocks */
			while (BlockStat[pb] != 0xFFFF) {			/* Find a free block */
				if (++pb >= N_TOTAL_BLKS) pb = N_RES_BLKS;
				if (pb == pbs) return 0;				/* No free block is available */
			}
		//	xprintf("[W:%d]", pb);
			if (write_page(BlockBuff[0], (DWORD)pb * N_SIZE_BLK, N_SIZE_BLK)) break;	/* Write-back the block */
			bad_block(pb);		/* Mark 'bad-block' if the block goes bad */
			BadBlocks++;
		}
		BlockStat[pb] = LogBlock;

		if (PhyBlock) {	/* Erase old block */
			if (!erase_phy_block(PhyBlock)) {
				bad_block(PhyBlock);
				BadBlocks++;
			}
		}

		PhyBlock = pb;
		BlockDirty = 0;
	}

	return 1;
}



/*----------------------------------------------*/
/* Force blanked logical blocks                 */

static
DRESULT blank_log_blocks (
	LBA_t *region		/* Block of logical sectors to be blanked {start, end} */
)						/* If start sector is not top of a logical block, the block is left not blanked. */
{						/* If end sector is not end of a logical block, the block is left not blanked. */
	WORD stlb, edlb, pb;
	DWORD st = (DWORD)region[0], ed = (DWORD)region[1];


	if (ed >= MAX_LBA || st > ed) return RES_PARERR;
	stlb = (WORD)((st + N_SIZE_BLK - 1) / N_SIZE_BLK);	/* Start LB */
	edlb = (WORD)((ed + 1) / N_SIZE_BLK);				/* End LB + 1 */

	for (pb = N_RES_BLKS; pb < N_TOTAL_BLKS; pb++) {
		if (BlockStat[pb] >= stlb && BlockStat[pb] < edlb) {
			if (!erase_phy_block(pb)) {
				bad_block(pb);	/* Erase the logical block */
				BadBlocks++;
			}
		}
	}

	return RES_OK;
}



/*----------------------------------------------*/
/* Check if the block can be written well       */

static
int chk_block (	/* 0:Failed, 1:Successful */
	WORD blk,	/* Physical block to be checked */
	DWORD pat	/* Test pattern */
)
{
	DWORD *buf = BlockBuff[0];
	int i;


	for (i = 0; i < 132 * N_SIZE_BLK; i++)	/* Create check pattern */
		buf[i] = pat;

	if (!write_page(buf, (DWORD)blk * N_SIZE_BLK, N_SIZE_BLK))	/* Write it to the block */
		return 0;

	read_page(buf, (DWORD)blk * N_SIZE_BLK, N_SIZE_BLK, 528);		/* Read-back the data */

	for (i = 0; i < 132 * N_SIZE_BLK; i++) {						/* Compare check pattern */
		if (buf[i] != pat) return 0;
	}

	return 1;
}



/*----------------------------------------------*/
/* Create physical format on the memory         */

static
DRESULT phy_format (
	int(*func)(UINT,UINT,UINT)	/* Pointer to call-back function for progress report */
)
{
	WORD pb, bb;


	nand_init();
	Init = bb = 0;

	for (pb = N_RES_BLKS; pb < N_TOTAL_BLKS; pb++) {	/* Check all blocks but reserved blocks */
		if (   !erase_phy_block(pb)			/* Check if the block has defect or not */
			|| !chk_block(pb, 0x55AA55AA)
			|| !erase_phy_block(pb)
			|| !chk_block(pb, 0xAA55AA55)
			|| !erase_phy_block(pb)
			) {
			bad_block(pb);	/* Mark 'bad-block' if the block is bad */
			bb++;
		}
		if (func && !func(pb - N_RES_BLKS + 1, N_TOTAL_BLKS - N_RES_BLKS, bb))	/* Report progress in format (processed, total, bad)*/
			return RES_ERROR;
		if (bb > N_SPARE_BLKS / 2) return RES_ERROR;	/* Too many bad blocks */
	}

	return RES_OK;
}



/*--------------------------------------------*/
/* Create ECC value of a 256 byte data block  */

static
DWORD create_ecc (		/* Returns 22 bit parity (b0:P0, b1:P0', b2:P1, b3:P1', b4:P2, ..., b21:P10') */
	const DWORD* blk	/* Pointer to the 256 byte data block to be calcurated */
)
{
	UINT i;
	DWORD d, r, par[22], *pp;

	/* Clear parity accumlator */
	for (i = 0; i < 22; par[i++] = 0) ;

	/* Calcurate parity */
	for (i = 0; i < 64; i++) {
		d = *blk++;		/* Get four bytes */
		pp = par;		/* Parity table */
		*pp++ ^= d & 0x55555555;		/* P0  */
		*pp++ ^= d & 0xAAAAAAAA;		/* P0' */
		*pp++ ^= d & 0x33333333;		/* P1  */
		*pp++ ^= d & 0xCCCCCCCC;		/* P1' */
		*pp++ ^= d & 0x0F0F0F0F;		/* P2  */
		*pp++ ^= d & 0xF0F0F0F0;		/* P2' */
		*pp++ ^= d & 0x00FF00FF;		/* P3  */
		*pp++ ^= d & 0xFF00FF00;		/* P3' */
		*pp++ ^= d & 0x0000FFFF;		/* P4  */
		*pp++ ^= d & 0xFFFF0000;		/* P4' */
		pp[i >> 0 & 1] ^= d; pp += 2;	/* P5, P5' */
		pp[i >> 1 & 1] ^= d; pp += 2;	/* P6, P6' */
		pp[i >> 2 & 1] ^= d; pp += 2;	/* P7, P7' */
		pp[i >> 3 & 1] ^= d; pp += 2;	/* P8, P8' */
		pp[i >> 4 & 1] ^= d; pp += 2;	/* P9, P9' */
		pp[i >> 5 & 1] ^= d;			/* P10, P10' */
	}

	/* Gather parity and pack it into a DWORD */
	for (i = r = 0; i < 22; i++) {
		d = par[i];
		d ^= d >> 16;
		d ^= d >> 8;
		d ^= d >> 4;
		d ^= d >> 2;
		d ^= d >> 1;
		r |= (d & 1) << i;
	}

	return r;
}


/*----------------------------------------------*/
/* Check and correct a 256 byte data block      */

static
UINT check_ecc (	/* ==0:No error, b0:A bit error in data, b1:A bit error in ECC, b2:Unrecoverable (2+ bits error) */
	DWORD* blk,		/* Pointer to the 256 byte data block to be checked */
	DWORD ecc		/* Pre-calcurated 22 bit ECC of the data block */
)
{
	UINT i, bit, ofs;


	ecc = (ecc ^ create_ecc(blk)) & 0x3FFFFF;	/* Compare ECC */

	if (!ecc) return 0;							/* Succeeded(0): No error */
	if (!(ecc & (ecc - 1))) return 1;			/* Succeeded(1): Single-bit error in the ECC */
	if (((ecc ^ (ecc >> 1)) & 0x155555) != 0x155555) return 4;	/* Failed(4): Multiple-bit error */

	/* Correct single-bit error in the data block */
	for (bit = 0, i = 1; i < 32; i <<= 1, ecc >>= 2) {
		if (ecc & 2) bit |= i;
	}
	for (ofs = 0, i = 1; i < 64; i <<= 1, ecc >>= 2) {
		if (ecc & 2) ofs |= i;
	}
	blk[ofs] ^= 1 << bit;

	return 2;	/* Succeeded(2): Single-bit error in the data was corrected */
}



/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS NAND_initialize (void)
{
	DWORD i, j, w, d[2], bb, bf;
	WORD stat;


	nand_init();
	flush_block();

	/* Create physical block status table */
	for (bb = 0, i = N_RES_BLKS; i < N_TOTAL_BLKS; i++) {
		read_page(d, i * N_SIZE_BLK, 1, 8);	/* Read two DWORDs of the spare area of 1st page */
		bf = 0;
		w = ~d[1];	/* Check bad block mark */
		if (w & (w - 1)) {	/* Bad block (2 or more zeros) */
			bb++; bf = 1;
		} else {
			w = d[0];	/* Get block status */
		 	if (w != 0xFFFFFFFF && (WORD)w != (WORD)(~w >> 16)) {	/* Bit error in the status? */
				read_page(d, i * N_SIZE_BLK + 1, 1, 8);	/* Read 2nd page */
				w = d[0];	/* Get block status */
			 	if (w != 0xFFFFFFFF && (WORD)w != (WORD)(~w >> 16)) {
			 		bb++; bf = 1;
				}
			}
		}
		stat = bf ? 0xFFFE : (WORD)w;
		BlockStat[i] = stat;

		/* Check duplicated logical block due to interruption of write sequence */
		if (stat < 0xFFFE) {
			for (j = N_RES_BLKS; BlockStat[j] != stat && j < i; j++) ;
			if (j < i) {
				if (erase_phy_block(j)) {	/* Erase duplicated block */
					BlockStat[j] = 0xFFFF;
				} else {
					bad_block(j);
					bb++;
				}
			}
		}

		if (bb >= N_SPARE_BLKS) break;	/* Too many bad blocks */
	}
	nand_cmd(0x00);		/* Exit read mode 3 */

	Init = (bb < N_SPARE_BLKS) ? 1 : 0;
	BadBlocks = bb;
	LogBlock = 0xFFFF;
	BlockDirty = 0;

	return Init ? 0 : STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS NAND_status (void)
{
	return Init ? 0 : STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT NAND_read (
	BYTE* buff,		/* Data read buffer */
	LBA_t lba,		/* Start sector number (LBA) */
	UINT sc			/* Number of sectors to read */
)
{
	DWORD sect = (DWORD)lba;
	WORD lb;
	UINT s, i, j;


	if (!Init) return RES_NOTRDY;				/* Initialized? */
	if (sect + sc > MAX_LBA) return RES_PARERR;	/* Range check */

	while (sc) {
		lb = sect / N_SIZE_BLK;	/* Block to be read */
		if (lb != LogBlock) {	/* Load the block if it is different with current block */
			if (!flush_block()) return RES_ERROR;
			load_block(lb, 1);
		}
		do {
			i = sect % N_SIZE_BLK;	/* Sector offset in the block */
			s = ~BlockBuff[i][130] >> 24;	/* Check if the sector is blank */
			if (s & (s - 1)) {	/* Live sector (copy data) */
				if (!PageStat[i]) {	/* Check ECC if not checked */
					s = check_ecc(&BlockBuff[i][0], BlockBuff[i][130]);
					if (s & 4) return RES_ERROR;
					if (s & 2) BlockBuff[i][130] = create_ecc(&BlockBuff[i][0]);
					if (s & 3) BlockDirty = 1; 
					s = check_ecc(&BlockBuff[i][64], BlockBuff[i][131]);
					if (s & 4) return RES_ERROR;
					if (s & 2) BlockBuff[i][131] = create_ecc(&BlockBuff[i][64]);
					if (s & 3) BlockDirty = 1; 
					PageStat[i] = 1;
				}
				Copy_al2un(buff, BlockBuff[i], 512);	/* Copy sector data to app buffer */
			} else {	/* Blank sector */
				for (j = 0; j < 512; j++)	/* Fill app buffer with 0xFF */
					buff[j] = 0xFF;
			}
			buff += 512; sect++; sc--;
		} while (sc && (sect % N_SIZE_BLK));	/* Repeat until last sector or end of block */
	}

	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
/* Note: Must be synced after write process to flush the dirty block     */

DRESULT NAND_write (
	const BYTE* buff,	/* Data to be written */
	LBA_t lba,			/* Start sector number (LBA) */
	UINT sc				/* Number of sectors to write */
)
{
	DWORD sect = (DWORD)lba;
	WORD lb;
	UINT i;
	int load;


	if (!Init) return RES_NOTRDY;				/* Initialized? */
	if (sect + sc > MAX_LBA) return RES_PARERR;	/* Range check */

	while (sc) {
		lb = sect / N_SIZE_BLK;	/* Block to be written */
		i = sect % N_SIZE_BLK;	/* Sector offset in the block */
		if (lb != LogBlock) {	/* Load a new block if block is different */
			if (!flush_block()) return RES_ERROR;
			load = (i == 0 && sc >= N_SIZE_BLK) ? 0 : 1;	/* Do not read block if the entire block is to be overwritten */
			load_block(lb, load);
		}
		do {
			Copy_un2al(BlockBuff[i], buff, 512);				/* Copy app data to the sector */
			BlockBuff[i][130] = create_ecc(&BlockBuff[i][0]);	/* Create ECC 1 (the sector goes live) */
			BlockBuff[i][131] = create_ecc(&BlockBuff[i][64]);	/* Create ECC 2 */
			PageStat[i] = 1;
			buff += 512; i++; sect++; sc--;
		} while (sc && (sect % N_SIZE_BLK));	/* Repeat until last sector or end of block */
		BlockDirty = 1;
	}

	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT NAND_ioctl (
	BYTE cmd,
	void* buff
)
{
	switch (cmd) {
	case CTRL_SYNC:			/* Flush dirty block */
		if (!Init) return RES_NOTRDY;
		return flush_block() ? RES_OK : RES_ERROR;

	case GET_SECTOR_COUNT:	/* Get number of user sectors */
		*(LBA_t*)buff = (DWORD)MAX_LBA;
		return RES_OK;

	case GET_BLOCK_SIZE:	/* Get erase block size */
		*(DWORD*)buff = N_SIZE_BLK;
		return RES_OK;

	case CTRL_TRIM:			/* Erase (force blanked) a sector group */
		if (!Init) return RES_NOTRDY;
		return blank_log_blocks(buff);

	case CTRL_FORMAT:		/* Create physical format on the memory */
		return phy_format(buff);
	}

	return RES_PARERR;
}

