/*-----------------------------------------------------------------------*/
/* Glue functions for FatFs - MCI/NAND drivers            (C)ChaN, 2010  */
/*-----------------------------------------------------------------------*/

#include "diskio.h"


DSTATUS disk_initialize (
	BYTE drv
)
{
	switch (drv) {
	case DN_NAND:
		return NAND_initialize();
	case DN_MCI:
		return MCI_initialize();
	}
	return RES_PARERR;
}



DSTATUS disk_status (
	BYTE drv
)
{
	switch (drv) {
	case DN_NAND:
		return NAND_status();
	case DN_MCI:
		return MCI_status();
	}
	return RES_PARERR;
}



DRESULT disk_read (
	BYTE drv,
	BYTE* buff,
	LBA_t lba,
	UINT count
)
{
	switch (drv) {
	case DN_NAND:
		return NAND_read(buff, lba, count);
	case DN_MCI:
		return MCI_read(buff, lba, count);
	}
	return RES_PARERR;
}


DRESULT disk_write (
	BYTE drv,
	const BYTE* buff,
	LBA_t lba,
	UINT count
)
{
	switch (drv) {
	case DN_NAND:
		return NAND_write(buff, lba, count);
	case DN_MCI:
		return MCI_write(buff, lba, count);
	}
	return RES_PARERR;
}


DRESULT disk_ioctl (
	BYTE drv,
	BYTE cmd,
	void* buff
)
{
	switch (drv) {
	case DN_NAND:
		return NAND_ioctl(cmd, buff);
	case DN_MCI:
		return MCI_ioctl(cmd, buff);
	}
	return RES_PARERR;
}


