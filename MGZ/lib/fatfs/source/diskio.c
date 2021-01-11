/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

/* PS3 I/O support */
#define SYSIO_RETRY	10

#include <ppu-types.h>
#include <malloc.h>
#include <sys/file.h>
#include <lv2/mutex.h> 
#include <sys/errno.h>
#include "storage.h"

#include "fflib.h"

# if 0
DWORD get_fattime (void)
{
	return ((DWORD)(FF_NORTC_YEAR - 1980) << 25 | (DWORD)FF_NORTC_MON << 21 | (DWORD)FF_NORTC_MDAY << 16);
}
#endif
static DSTATUS fatfs_dev_init(int idx)
{
    int rr;
	static device_info_t disc_info;
	u64 id = fflib_id_get (idx);
	if (id == 0)
		return RES_PARERR;
	rr = sys_storage_get_device_info (id, &disc_info);
	if(rr != 0)  
	{
		disc_info.sector_size = 512; 
	}

	if(fflib_fd_get (idx) >= 0)
		return RES_OK;
	int fd;
	if(sys_storage_open (id, &fd) < 0) 
	{
		return RES_NOTRDY;
	}
	fflib_fd_set (idx, fd);
	fflib_ss_set (idx, disc_info.sector_size);

	return RES_OK;
}

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	if (fflib_fd_get (pdrv) > 0)
		return RES_OK;
	//
	return RES_ERROR;
}


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	return fatfs_dev_init (pdrv);
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_PARERR;
	int fd = fflib_fd_get (pdrv);
	int ss = fflib_ss_get (pdrv);
    int flag = ((int) (s64) buff) & 31;

    if (fd < 0 || !buff || ss < 0)
		return RES_PARERR;

    void *my_buff;
    
    if(flag) 
		my_buff = memalign (16, ss * count); 
	else 
		my_buff = buff;

    if(!my_buff)
		return RES_ERROR;

	u64 storage_flag = 0;
    u32 sectors_read;
    int r, k;
	res = RES_OK;
	for (k = 0; k < SYSIO_RETRY; k++)
	{
		r = sys_storage_read (fd, sector, count, (u8 *) my_buff, &sectors_read, storage_flag); 
		if (r == 0x80010002 ) {
			if(storage_flag == 0x22) break;
			if(storage_flag == 1) storage_flag = 0x22;
			if(storage_flag == 0) storage_flag = 1;
		}
		if(r == 0)
		{
			break;
		}

		usleep (62500);
	}
	if(r == 0x80010002) //sys error
	{
		if(flag) 
		{
			free(my_buff);
		}
		//drive unplugged? detach?
		return RES_NOTRDY;
	}
	
    if(flag) 
	{
		if(r>=0)
			memcpy (buff, my_buff, ss * count);
        free (my_buff);
    }

    if(r < 0) 
		return RES_ERROR;

    if(sectors_read != count) 
	{
		return RES_ERROR;
	}

	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_PARERR;
    int flag = ((int) (s64) buff) & 31;
	int fd = fflib_fd_get (pdrv);
	int ss = fflib_ss_get (pdrv);

    if (fd < 0  || !buff || ss < 0)
	{
		return RES_PARERR;
	}
    void *my_buff;
    
    if (flag) 
		my_buff = memalign (32, ss * count);
	else
		my_buff = (void *) buff;

    uint32_t sectors_wrote;

    if (!my_buff)
	{
		return RES_ERROR;
	}
    if (flag)
		memcpy (my_buff, buff, ss * count);

	u64 storage_flag = 0;
	
    int r, k;
	res = RES_OK;
	for (k = 0; k < SYSIO_RETRY; k++)
	{
		r = sys_storage_write (fd, (uint32_t) sector, (uint32_t) count, (uint8_t *) my_buff, &sectors_wrote, storage_flag);
		
		if (r == 0x80010002 ) {
			if(storage_flag == 0x22) break;
			if(storage_flag == 1) storage_flag = 0x22;
			if(storage_flag == 0) storage_flag = 1;
		}
		
		if (r ==0)
		{
			break;
		}

		usleep (62500);
	}
    if (flag)
		free (my_buff);
	
	if (r == 0x80010002) //sys error
	{
		return RES_NOTRDY;//drive unplugged? detach from FS?
	}

    if (r < 0)
	{
		return RES_ERROR;
	}

    if (sectors_wrote != count)
	{
		return RES_ERROR;
	}

	return res;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_PARERR;
	int fd = fflib_fd_get (pdrv);
	u64 id = fflib_id_get (pdrv);
	if (fd < 0 || id == 0)
	{
		return RES_NOTRDY;
	}
	res = RES_PARERR;
	switch (cmd) 
	{
		case CTRL_SYNC:			/* Nothing to do */
			res = RES_OK;
			break;

		case GET_SECTOR_COUNT:	/* Get number of sectors on the drive */
		{
			static device_info_t disc_info;
			disc_info.sector_count = 0;
			int rr = sys_storage_get_device_info (id, &disc_info);
			if (rr != 0)
			{
				return RES_ERROR;
			}
			*(LBA_t*)buff = (LBA_t) disc_info.sector_count;
			res = RES_OK;
		}
			break;

		case GET_SECTOR_SIZE:	/* Get size of sector for generic read/write */
		{
			static device_info_t disc_info;
			disc_info.sector_size = 0;
			int rr = sys_storage_get_device_info (id, &disc_info);
			if (rr != 0)
			{
				return RES_ERROR;
			}
			*(WORD*)buff = disc_info.sector_size;
			res = RES_OK;
		}
			break;

		case GET_BLOCK_SIZE:	/* Get internal block size in unit of sector */
			//*(DWORD*)buff = SZ_BLOCK;
			res = RES_PARERR;
			break;
	}
	return res;
}

//#endif
