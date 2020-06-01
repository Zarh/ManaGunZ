/* 
   TINY3D sample / (c) 2010 Hermes  <www.elotrolado.net>

*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

#include <io/pad.h>

#include <tiny3d.h>
#include <libfont.h>

// font 0: 224 chr from 32 to 255, 16 x 32 pix 2 bit depth
#include "font.h"

// font 1: 224 chr from 32 to 255, 16 x 32 pix 2 bit depth
#include "font_b.h"

// font 2: 255 chr from 0 to 254, 8 x 8 pix 1 bit depth
extern unsigned char msx[];

#include "console.h"

#include "ff.h"
#include "fflib.h"

#define SDTEST
#ifdef SDTEST
#include "types.h"

typedef struct {
    int device;
    void *dirStruct;
} DIR_ITER;

#include "iosupport.h"
#include "storage.h"
#include <malloc.h>
#include <sys/file.h>
#include <lv2/mutex.h> 
#include <sys/errno.h>

#include <sys/file.h>
#include <ppu-lv2.h>
#include <sys/stat.h>
#include <lv2/sysfs.h>

#include <sysutil/disc.h>

#include <sysmodule/sysmodule.h>
//app
int app_init (int dt);      //1
int app_input (int dt);     //2
int app_update (int dt);    //3
int app_render (int dt);    //4
int app_cleanup (int dt);   //5
//
//pad buttons mask - for use in app
#define PAD_R1_MASK         0x0001
#define PAD_L1_MASK         0x0002
#define PAD_R2_MASK         0x0004
#define PAD_L2_MASK         0x0008
#define PAD_CR_MASK         0x0010
#define PAD_SQ_MASK         0x0020
#define PAD_CI_MASK         0x0040
#define PAD_TR_MASK         0x0080
#define PAD_SE_MASK         0x0100
#define PAD_ST_MASK         0x0200
#define PAD_R3_MASK         0x0400
#define PAD_L3_MASK         0x0800
#define PAD_UP_MASK         0x1000
#define PAD_DN_MASK         0x2000
#define PAD_LT_MASK         0x4000
#define PAD_RT_MASK         0x8000
//

int fddr[8] = {0};
char fdld[8][256];
char fn[256] = {0};
char wn[256] = {0};
char dn[256] = {0};
int ffd = -1;
static u64 ff_ps3id[8] = {
	0x010300000000000AULL, 0x010300000000000BULL, 0x010300000000000CULL, 0x010300000000000DULL,
	0x010300000000000EULL, 0x010300000000000FULL, 0x010300000000001FULL, 0x0103000000000020ULL 
	};
#if 0
static int dev_fd[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
#include "storage.h"
int sdopen (int fd)
{
	static device_info_t disc_info;
	disc_info.unknown03 = 0x12345678; // hack for Iris Manager Disc Less
	disc_info.sector_size = 0;
	//int ret = sys_storage_get_device_info(ff_ps3id[fd], &disc_info);
    int ret = sys_storage_open(ff_ps3id[fd], &dev_fd[fd]);
    if (0 == ret)
        sys_storage_close(dev_fd[fd]);
    return ret;
}
#else

//tools
FRESULT scan_files2 (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    FDIR dir;
    UINT i = 0;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) 
    {
        for (;;) 
        {
            FRESULT res1 = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res1 != FR_OK || fno.fname[0] == 0) 
                break;  /* Break on error or end of dir */
            i++;
            if (i > 7)
                break;
            if (fno.fattrib & AM_DIR) 
            {                    /* It is a directory */
                snprintf (fdld[i], 255, "/%s", fno.fname);
                //sprintf(&path[i], "/%s", fno.fname);
                //res = scan_files(path);                    /* Enter the directory */
                //if (res != FR_OK) break;
                //path[i] = 0;
            } 
            else 
            {                                       /* It is a file. */
                snprintf (fdld[i], 255, "%s", fno.fname);
                //printf("%s/%s\n", path, fno.fname);
            }
        }
        f_closedir(&dir);
    }
    return res;
}

FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    FDIR dir;
    static FILINFO fno;

    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK)
    {
        DPrintf("Listing path contents for '%s'\n", path);
        for (;;)
        {
            FRESULT res1 = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res1 != FR_OK || fno.fname[0] == 0) 
            {
                f_closedir(&dir);
                return res;  /* Break on error or end of dir */
            }
            if (fno.fattrib & AM_DIR) 
            {                    /* It is a directory */
                DPrintf("/%s\n", fno.fname);
                snprintf (dn, 255, "%s%s", path, fno.fname);
                snprintf (wn, 255, "%s%s/fatfs.tst", path, fno.fname);
            } 
            else 
            {                                       /* It is a file. */
                DPrintf("%s\n", fno.fname);
                snprintf (fn, 255, "%s%s", path, fno.fname);
            }
        }
        f_closedir(&dir);
    }
    else
    {
        ;//DPrintf("!unable to open path '%s' result %d\n", path, res);
    }
    return res;
}
#if 0
fdisk -l /dev/sdb1
Disk /dev/sdb1: 223.6 GiB, 240055746560 bytes, 468858880 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0xf4f4f4f4

Device      Boot      Start        End    Sectors  Size Id Type
/dev/sdb1p1      4109694196 8219388391 4109694196  1.9T f4 SpeedStor
/dev/sdb1p2      4109694196 8219388391 4109694196  1.9T f4 SpeedStor
/dev/sdb1p3      4109694196 8219388391 4109694196  1.9T f4 SpeedStor
/dev/sdb1p4      4109694196 8219388391 4109694196  1.9T f4 SpeedStor
fsck.exfat /dev/sdb1
exfatfsck 1.2.5
Checking file system on /dev/sdb1.
File system version           1.0
Sector size                 512 bytes
Cluster size                128 KB
Volume size                 224 GB
Used space                   21 MB
Available space             224 GB
#endif
#define MSZ (1024*1024)
#define FWR (MSZ*1024)/* 1GB as slices of 1MB */
#define BSZ (3*MSZ)
static LBA_t clst2sect (	/* !=0:Sector number, 0:Failed (invalid cluster#) */
	FATFS* fs,		/* Filesystem object */
	DWORD clst		/* Cluster# to be converted */
)
{
	clst -= 2;		/* Cluster number is origin from 2 */
	if (clst >= fs->n_fatent - 2) return 0;		/* Is it invalid cluster number? */
	return fs->database + (LBA_t)fs->csize * clst;	/* Start sector number of the cluster */
}

FRESULT f_open_sectors (
	FIL* fp,			/* Pointer to the blank file object */
	const TCHAR* path,	/* Pointer to the file name */
	BYTE mode,			/* Access mode and file open mode flags */
	int (*record_cbk)(unsigned int sect, unsigned int nsect)	//callback to run on disk access call
);
FRESULT f_read_sectors (
	FIL* fp, 	/* Pointer to the file object */
	void* buff,	/* Pointer to data buffer */
	UINT btr,	/* Number of bytes to read */
	UINT* br,	/* Pointer to number of bytes read */
	int (*record_cbk)(unsigned int sect, unsigned int nsect)	//callback to run on disk access call
);

#define MAX_SECTS   1000
unsigned int sects[MAX_SECTS];
unsigned int nsect[MAX_SECTS];
int sidx = 0;
int record_add(unsigned int sect, unsigned int nsec)
{
    if (sidx == -1)
    {
        //can't record any more
        return -1;
    }
    //NPrintf ("reading from sector %u for %u sectors\n", sect, nsec);
    if (nsect[sidx] == 0)
    {
        sects[sidx] = sect;    //set start sector
        nsect[sidx] = nsec;
    }
    else
    {
        //do we need to add to the same?
        if (sects[sidx] + nsect[sidx] == sect)
        {
            nsect[sidx] += nsec;
        }
        else
        {
            //register new section
            sidx++;
            if (sidx >= MAX_SECTS)
                sidx = -1;
            else
            {
                sects[sidx] = sect;    //set start section sector
                nsect[sidx] = nsec;
            }
        }
    }
    
    return 0;
}

#include "cobra.h"

#define MAX_SECTIONS	((0x10000-sizeof(rawseciso_args))/8)
typedef struct
{
	uint64_t device;
	uint32_t emu_mode;
	uint32_t num_sections;
	uint32_t num_tracks;
} __attribute__((packed)) rawseciso_args;

void cobra_MountISO()
{
	int i;

    uint8_t *plugin_args = malloc(0x20000);
    uint32_t *sections = malloc(MAX_SECTIONS * sizeof(uint32_t));
    uint32_t *sections_size = malloc(MAX_SECTIONS * sizeof(uint32_t));
    rawseciso_args *p_args;  
    memset(sections, 0, MAX_SECTIONS * sizeof(uint32_t));
    memset(sections_size, 0, MAX_SECTIONS * sizeof(uint32_t));
    memset(plugin_args, 0, 0x10000);

    int parts = sidx;
    //int parts = ps3ntfs_file_to_sectors(GamPath, sections, sections_size, MAX_SECTIONS, 1);
    memcpy (sections, sects, sizeof(uint32_t) * parts);
    memcpy (sections_size, nsect, sizeof(uint32_t) * parts);

    if (parts > 0 && parts < MAX_SECTIONS) 
    {
        p_args = (rawseciso_args *)plugin_args;
        p_args->device = 0x10300000000000a;//USB_MASS_STORAGE(NTFS_Test_Device(&GamPath[1]));
        p_args->emu_mode = EMU_PS3;
        p_args->num_sections = parts;
        p_args->num_tracks = 0;
        memcpy (plugin_args + sizeof(rawseciso_args), sections, parts * sizeof (uint32_t));
        memcpy (plugin_args + sizeof(rawseciso_args) + (parts * sizeof (uint32_t)), sections_size, parts * sizeof(uint32_t)); 
        cobra_unload_vsh_plugin(0);
        if (cobra_load_vsh_plugin (0, "/dev_hdd0/game/MANAGUNZ0/USRDIR/sys/sprx_iso", plugin_args, 0x10000) == 0) return;
    }
}

int file_scan_sectors (int i)
{
    char lbuf[10];
    FATFS fs;     /* Ponter to the filesystem object */
    FDIR fdir;
    snprintf(lbuf, 10, "%d:/", i);
    int ret = f_mount(&fs, lbuf, 0);                    /* Mount the default drive */
    if (ret != FR_OK)
        return ret;
    ret = f_opendir (&fdir, lbuf);
    if (ret == FR_OK)
    {
        FATFS *fsp = fdir.obj.fs;
        DPrintf("fs on '%s' drive: %d, type: %d\n", lbuf, i, fsp->fs_type);
        DPrintf("sector size: %d, cluster size [sectors]: %d, size of an FAT [sectors]: %d\n", fsp->ssize, fsp->csize, fsp->fsize);
        DPrintf("number of FAT entries (number of clusters + 2): %d, number of FATs (1 or 2): %d\n", fsp->n_fatent, fsp->n_fats);
        DPrintf("last cluster: %d, free clusters: %d\n", fsp->last_clst, fsp->free_clst);
        unsigned long capa = fsp->n_fatent / 1024;
        capa *= fsp->ssize;
        capa /= 1024;
        capa *= fsp->csize;
        capa /= 1024;
        DPrintf("capacity: %luGB\n", capa);
        f_closedir (&fdir);
    }
    //emulate file_to_sectors
    BYTE *buffer = malloc (BSZ);
    if (buffer == NULL)
    {
        DPrintf ("!failed to allocate buffer of %dbytes\n", BSZ);
        return FR_INT_ERR;
    }

    /* Open source file on the drive 1 */
    FRESULT fr;         /* FatFs function common result code */
    FIL fdst;           /* File objects */
    char *lfn = "0:/BIA HH.iso"; //"0:/BLES00986 Rock Band 3.iso"; "0:/file_write.bin";
    FILINFO fno;
    if (f_stat (lfn, &fno) == FR_OK)
        DPrintf ("FS: '%s' size: %luMB, %luB\n", lfn, fno.fsize/MSZ, fno.fsize);
    
    #if 0
    UINT csect, lsect, sktr = 0, sk = 0, k, bw = 0;
    fr = f_open_sectors (&fdst, lfn, FA_READ, &record_add);
    if (fr == FR_OK)
    {
        DPrintf ("reading %luB from file '%s'.. please wait\n", fno.fsize, lfn);
        DPrintf ("current sector: %u, dirsect %u\n", fdst.sect, fdst.dir_sect);
    #if 1
        csect = fdst.clust;//clst2sect(&fs, fdst.clust);
        lsect = csect;
        UINT lbsz = fs.ssize + fs.csize;    //force reading a cluster at a time: csize number of sectors
        //
        for (k=0; ;k++)
        {
            fr = f_read_sectors (&fdst, NULL, BSZ * 100, &bw, &record_add);  /* Read a chunk of source file */
            #if 0
            //fr = f_lseek (&fdst, sktr);  /* Read a chunk of source file */
            csect = fdst.clust;//clst2sect(&fs, fdst.clust);
            //DPrintf ("%d.. ", k);
            //DPrintf ("current sector/cluster %u/%u, pos %lu ret %d", csect, fdst.clust, sktr, fr);
            if (csect != lsect)
            {
                lsect = csect;
                DPrintf ("current sector: %u cluster %u, ssect %u\n", lsect, csect, clst2sect(&fs, fdst.clust));
                sk++;
            }
            #endif
            //if (fr != FR_OK || bw == 0)
            //if (fr != FR_OK || bw == 0)
            //if (bw == fno.fsize)
            if (bw == 0)
            {
                sidx++; //we may end up with only one entry in best case
                unsigned int fas = clst2sect(&fs, fdst.clust) + fs.csize;
                DPrintf ("finished recording %d sector entries from sector %u (0x%x) to sector %u (0x%x)\n", sidx, sects[0], sects[0], fas, fas);
                break; /* error or eof */
            }
            //sktr += fs.csize/2;//add sector size
            if (app_input(0) & PAD_CI_MASK)
                break;
            DbgDraw ();
            tiny3d_Flip ();
        }
    #endif
        //
        f_close(&fdst);
    }
    free(buffer);
    //
    f_mount(NULL, lbuf, 0);                    /* UnMount the default drive */
    #endif
    sidx = fflib_file_to_sectors (lfn, sects, nsect, MAX_SECTS, 1);
    //
    DPrintf ("found %u sections\n", sidx);
    unsigned long rfsz = 0;
    int k;
    for (k = 0; k < sidx; k++)
    {
        DPrintf ("section[%d]=0x%x size[%d]=0x%x\n", k, sects[k], k, nsect[k]);
        rfsz += nsect[k];
    }
    DPrintf ("last sector is at %u (0x%x)\n", sects[k-1] + nsect[k-1], sects[k-1] + nsect[k-1]);
    DPrintf ("file size is %u sectors total, %luB on disk vs %luB actual\n", rfsz, rfsz * fs.ssize, fno.fsize);
    //try to mount it
    if (sidx)
        cobra_MountISO ();
    //
    return FR_OK;
}

int fs_info(int i)
{
    char lbuf[10];
    FATFS fs;     /* Ponter to the filesystem object */
    FDIR fdir;
    snprintf(lbuf, 10, "%d:/", i);
    int ret = f_mount(&fs, lbuf, 0);                    /* Mount the default drive */
    if (ret != FR_OK)
        return ret;
    ret = f_opendir (&fdir, lbuf);
    if (ret == FR_OK)
    {
        FATFS *fsp = fdir.obj.fs;
        DPrintf("fs on '%s' drive: %d, type: %d\n", lbuf, i, fsp->fs_type);
        DPrintf("sector size: %d, cluster size [sectors]: %d, size of an FAT [sectors]: %d\n", fsp->ssize, fsp->csize, fsp->fsize);
        DPrintf("number of FAT entries (number of clusters + 2): %d, number of FATs (1 or 2): %d\n", fsp->n_fatent, fsp->n_fats);
        DPrintf("last cluster: %d, free clusters: %d\n", fsp->last_clst, fsp->free_clst);
        unsigned long capa = fsp->n_fatent / 1024;
        capa *= fsp->ssize;
        capa /= 1024;
        capa *= fsp->csize;
        capa /= 1024;
        DPrintf("capacity: %luGB\n", capa);
        f_closedir (&fdir);
    }
    //
    f_mount(NULL, lbuf, 0);                    /* UnMount the default drive */
    //
    return FR_OK;
}

int sdopen (int i)
{
    //FDIR fdir;
    char lbuf[10];
    FATFS fs;     /* Ponter to the filesystem object */
    snprintf(lbuf, 10, "%d:/", i);
    int ret = f_mount(&fs, lbuf, 0);                    /* Mount the default drive */
    if (ret != FR_OK)
        return ret;
    if (ffd == -1)
        ffd = i;
    ret = scan_files(lbuf); //f_opendir (&fdir, lbuf);
    f_mount(NULL, lbuf, 0);                    /* UnMount the default drive */
    //
    if (ret == FR_OK)
        fs_info(i);
    //
    return ret;
}

int sdopen2 (int i)
{
    FDIR fdir;
    char lbuf[10];
    FATFS fs;     /* Ponter to the filesystem object */
    snprintf(lbuf, 10, "%d:/", i);
    int ret = f_mount(&fs, lbuf, 0);                    /* Mount the default drive */
    if (ret != FR_OK)
    {
        return ret;
    }
    ret = f_opendir (&fdir, lbuf);
    DPrintf("%d f_opendir %s drive %d ssize %d csize %d\n", ret, lbuf, i, fs.ssize, fs.csize);
    if (ret == FR_OK)
        f_closedir (&fdir);
    f_mount(0, lbuf, 0);                    /* Mount the default drive */
    //
    return ret;
}
#endif
//

int fatfs_init()
{
    fflib_init();
    //
    int k; for (k = 0; k < 8; k++)
    {
        fdld[k][0] = '\0';
        fddr[k] = fflib_attach (k, ff_ps3id[k], 1);
        DPrintf("open drive %d result %d for 0x%llx\n", k, fddr[k], (long long unsigned int)ff_ps3id[k]);
        if (fddr[k] == FR_OK)
            sdopen (k);
        else
            fflib_detach (k);
    }
    //
    return 0;
}
#endif

void LoadTexture()
{
    u32 * texture_mem = tiny3d_AllocTexture(64*1024*1024); // alloc 64MB of space for textures (this pointer can be global)    

    u32 * texture_pointer; // use to asign texture space without changes texture_mem

    if(!texture_mem) return; // fail!

    texture_pointer = texture_mem;

    ResetFont();
    texture_pointer = (u32 *) AddFontFromBitmapArray((u8 *) font  , (u8 *) texture_pointer, 32, 255, 16, 32, 2, BIT0_FIRST_PIXEL);
    texture_pointer = (u32 *) AddFontFromBitmapArray((u8 *) font_b, (u8 *) texture_pointer, 32, 255, 16, 32, 2, BIT0_FIRST_PIXEL);
    texture_pointer = (u32 *) AddFontFromBitmapArray((u8 *) msx   , (u8 *) texture_pointer,  0, 254,  8,  8, 1, BIT7_FIRST_PIXEL);

    // here you can add more textures using 'texture_pointer'. It is returned aligned to 16 bytes
}
//file write perf
int file_write_perf (int idx)
{
    time_t timer, timere;
    struct tm * timed;
    FATFS fs0;          /* Work area (filesystem object) for logical drives */
    FIL fdst;           /* File objects */
    BYTE *buffer = NULL;//[BSZ];   /* File copy buffer */
    FRESULT fr;         /* FatFs function common result code */
    UINT bw;            /* File read/write count */
    char fn[25];
    snprintf (fn, 25, "%d:/file_write.bin", idx);
    /* Register work area for each logical drive */
    f_mount (&fs0, fn, 0);
    //test writing 1G
    /* Create destination file on the drive 0 */
    fr = f_open (&fdst, fn, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr)
    {
        DPrintf ("!failed to create file '%s'\n", fn);
        return (int)fr;
    }
    /* Copy buffer to destination */
    buffer = malloc (BSZ);
    if (buffer == NULL)
    {
        DPrintf ("!failed to allocate buffer of %dbytes\n", BSZ);
        return FR_INT_ERR;
    }
    //
    DPrintf ("writing %dMB to file '%s'.. please wait\n", FWR/MSZ, fn);
    //
    time (&timer);
    timed = localtime (&timer);
    DPrintf ("writing %d blocks of %dMB: ", FWR/BSZ, BSZ/MSZ);
    time (&timer);
    int k; for (k = 0; k < FWR/BSZ; k++)
    {
        fr = f_write (&fdst, buffer, BSZ, &bw);            /* Write it to the destination file */
        if (fr || bw < BSZ)
            break; /* error or disk full */
        //usleep (100000);
        DPrintf ("..%d ", k + 1);
        if (app_input(0) & PAD_CI_MASK)
            break;
        DbgDraw ();
        tiny3d_Flip ();
    }
    time (&timere);
    /* Close open files */
    f_close (&fdst);
    DPrintf ("done.\n");
    int mbps = (k*BSZ)/(timere - timer);
    if (mbps > MSZ)
        DPrintf ("wrote %dMB to file '%s' in %dsec (%dMBps) bs %dbytes\n", (k*BSZ)/MSZ, fn, (timere - timer), mbps/MSZ, BSZ);
    else if (mbps > 1024)
        DPrintf ("wrote %dKB to file '%s' in %dsec (%dKBps) bs %dbytes\n", k*BSZ/1024, fn, (timere - timer), mbps/1024, BSZ);
    //
    FILINFO fno;
    if (f_stat (fn, &fno) == FR_OK)
        DPrintf ("FS: '%s' size: %luMB\n", fn, fno.fsize/MSZ);
    else
        DPrintf ("FS: '%s' size check failed!\n", fn);
    //test reading
    /* Open source file on the drive 1 */
    fr = f_open (&fdst, fn, FA_READ);
    if (fr == FR_OK)
    {
        DPrintf ("reading from file '%s'.. please wait\n", fn);
        //
        time (&timer);
        DPrintf ("reading blocks of %dMB: ", BSZ/MSZ);
        /* Copy source to destination */
        for (k = 0;;k++)
        {
            fr = f_read (&fdst, buffer, BSZ, &bw);  /* Read a chunk of source file */
            if (fr || bw == 0)
                break; /* error or eof */
            DPrintf ("..%d ", k + 1);
            if (app_input(0) & PAD_CI_MASK)
                break;
            DbgDraw ();
            tiny3d_Flip ();
        }
        time (&timere);
        /* Close open files */
        f_close (&fdst);
        DPrintf ("done.\n");
        mbps = (k*BSZ)/(timere - timer);
        if (mbps > MSZ)
            DPrintf ("read %dMB from file '%s' in %dsec (%dMBps) bs %dbytes\n", (k*BSZ)/MSZ, fn, (timere - timer), mbps/MSZ, BSZ);
        else if (mbps > 1024)
            DPrintf ("read %dKB to file '%s' in %dsec (%dKBps) bs %dbytes\n", k*BSZ/1024, fn, (timere - timer), mbps/1024, BSZ);
    }
    //
    free (buffer);
    /* Unregister work area prior to discard it */
    f_mount (NULL, fn, 0);
    return (int)fr;
}
//create file
//f_write > create_chain > find_bitmap
int file_read(char *fname);
int file_create (char *fname)
{
    FATFS fs;      /* Work area (filesystem object) for logical drives */
    FIL fdst;      /* File objects */
    BYTE buffer[] = "ThiS is A TeSt FiLe FoR wRiTiNg.\n\0";   /* File copy buffer */
    FRESULT fr;    /* FatFs function common result code */
    UINT bw;       /* File read/write count */

    /* Register work area for each logical drive */
    char dn[5];
    snprintf(dn, 4, "%.3s", fname);
    DPrintf("mounting drive '%s'\n", dn);
    DPrintf("writing to file '%s':\n", fname);
    f_mount(&fs, dn, 0);

    /* Create destination file on the drive 0 */
    fr = f_open(&fdst, fname, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr)
    {
        DPrintf("!failed creating the file '%s' result %d\n", fname, fr);
        /* Unregister work area prior to discard it */
        f_mount(0, dn, 0);
        return (int)fr;
    }
    /* Copy source to destination */
    fr = f_write(&fdst, buffer, sizeof(buffer), &bw);            /* Write it to the destination file */
    if (fr != FR_OK || bw != sizeof(buffer))
        DPrintf("!failed writing to file '%s' result %d wrote %d bytes vs %d\n", fname, fr, bw, sizeof(buffer));
    /* Close open files */
    f_close(&fdst);

    /* Unregister work area prior to discard it */
    f_mount(0, dn, 0);
    //read test
    file_read (fname);
    //
    return (int)fr;
}
//
int file_new(char *fname)
{
    if(!fname || !*fname)
        return 0;
    //debug console
    initConsole ();
    DbgHeader("File create test");
    DbgMess("Press o/circle to return");
    //
    file_create (fname);
    //
    int btn = 0;
    //
    while(1)
    {
        //2 input
        btn = app_input(0);
        if (btn & PAD_CI_MASK)
            break;
        //3
		//4
        DbgDraw();
        tiny3d_Flip();
    }
    return 0;
}

//dir contents
int dir_read (char *dname)
{
    FRESULT res;
    FDIR dir;
    static FILINFO fno;
    /* Register work area to the default drive */
    FATFS fs;   /* Work area (filesystem object) for logical drive */
    char drn[5];
    snprintf(drn, 4, "%.3s", dname);
    DPrintf("mounting drive '%s'\n", drn);
    DPrintf("listing directory '%s':\n", dname);
    f_mount(&fs, drn, 0);

    res = f_opendir(&dir, dname);                       /* Open the directory */
    if (res == FR_OK)
    {
        for (;;)
        {
            FRESULT res1 = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res1 != FR_OK || fno.fname[0] == 0) 
            {
                f_closedir(&dir);
                return res;  /* Break on error or end of dir */
            }
            if (fno.fattrib & AM_DIR) 
            {                    /* It is a directory */
                DPrintf("/%s\n", fno.fname);
                snprintf (dn, 255, "%s%s/", dname, fno.fname);
            } 
            else 
            {                                       /* It is a file. */
                DPrintf("%s\n", fno.fname);
                snprintf (fn, 255, "%s%s", dname, fno.fname);
            }
        }
        f_closedir(&dir);
    }
    else
    {
        DPrintf("!unable to open path '%s' result %d\n", dname, res);
    }
    //
    f_mount(0, drn, 0);
    //
    return res;
}

int dir_run(char *dname)
{
    if(!dname || !*dname)
        return 0;
    //debug console
    initConsole ();
    DbgHeader("DIR contents");
    DbgMess("Press o/circle to return");
    //
    dir_read (dname);
    //
    int btn = 0;
    //
    while(1)
    {
        //2 input
        btn = app_input(0);
        if (btn & PAD_CI_MASK)
            break;
        //3
		//4
        DbgDraw();
        tiny3d_Flip();
    }
    return 0;
}

//file contents
int file_read(char *fname)
{
    FIL fil;        /* File object */
    char line[100]; /* Line buffer */
    FRESULT fr;     /* FatFs return code */
    FATFS fs;   /* Work area (filesystem object) for logical drive */

    /* Register work area to the default drive */
    char dn[5];
    snprintf(dn, 4, "%.3s", fname);
    DPrintf("mounting drive '%s'\n", dn);
    DPrintf("reading file '%s':\n", fname);
    f_mount(&fs, dn, 0);

    /* Open a text file */
    fr = f_open(&fil, fname, FA_READ);
    if (fr)
    {
        DPrintf("!failed opening the file '%s' result %d\n", fname, fr);
        //
        f_mount(0, dn, 0);
        return (int)fr;
    }

    /* Read every line and display it */
    while (f_gets(line, sizeof (line), &fil)) 
    {
        DPrintf(line);
    }

    /* Close the file */
    f_close(&fil);
    //
    f_mount(0, dn, 0);
    //
    return 0;
}

int file_run(char *fname)
{
    if(!fname || !*fname)
        return 0;
    //debug console
    initConsole ();
    DbgHeader("File contents");
    DbgMess("Press o/circle to return");
    //
    file_read (fname);
    //
    int btn = 0;
    //
    while(1)
    {
        //2 input
        btn = app_input(0);
        if (btn & PAD_CI_MASK)
            break;
        //3
		//4
        DbgDraw();
        tiny3d_Flip();
    }
    return 0;
}
//app
//1st
int app_init (int dt)
{
    //debug console
    initConsole ();
    //fatfs test
    fatfs_init ();

    tiny3d_Init (1024*1024);

	ioPadInit (7);

	// Load texture
    LoadTexture ();
    //
    DbgHeader("FATFS EXFAT Example");
    DbgMess("Press x/cross to exit");
    //
    return 1;
}
//2nd
#if 0
from
unsigned int BTN_LEFT : 1;      /*!< \brief left button */
unsigned int BTN_DOWN : 1;      /*!< \brief down button */
unsigned int BTN_RIGHT : 1;     /*!< \brief right button */
unsigned int BTN_UP : 1;        /*!< \brief up button */
unsigned int BTN_START : 1;     /*!< \brief start button */
unsigned int BTN_R3 : 1;        /*!< \brief R3 button */
unsigned int BTN_L3 : 1;        /*!< \brief L3 button */
unsigned int BTN_SELECT : 1;    /*!< \brief select button */
unsigned int BTN_SQUARE : 1;    /*!< \brief square button */
unsigned int BTN_CROSS : 1;     /*!< \brief cross button */
unsigned int BTN_CIRCLE : 1;    /*!< \brief circle button */
unsigned int BTN_TRIANGLE : 1;  /*!< \brief triangle button */
unsigned int BTN_R1 : 1;        /*!< \brief R1 button */
unsigned int BTN_L1 : 1;        /*!< \brief L1 button */
unsigned int BTN_R2 : 1;        /*!< \brief R2 button */
unsigned int BTN_L2 : 1;        /*!< \brief L2 button */ 
to 
#define PAD_R1_MASK         0x0001
#define PAD_L1_MASK         0x0002
#define PAD_R2_MASK         0x0004
#define PAD_L2_MASK         0x0008
#define PAD_CR_MASK         0x0010
#define PAD_SQ_MASK         0x0020
#define PAD_CI_MASK         0x0040
#define PAD_TR_MASK         0x0080
#define PAD_SE_MASK         0x0100
#define PAD_ST_MASK         0x0200
#define PAD_R3_MASK         0x0400
#define PAD_L3_MASK         0x0800
#define PAD_UP_MASK         0x1000
#define PAD_DN_MASK         0x2000
#define PAD_LT_MASK         0x4000
#define PAD_RT_MASK         0x8000
#endif
int app_input(int dat)
{
	padInfo padinfo;
	padData paddata;
    int i;
    int ret = 0;
    // Check the pads.
    ioPadGetInfo(&padinfo);

    for(i = 0; i < MAX_PADS; i++)
    {
        if(padinfo.status[i])
        {
            ioPadGetData(i, &paddata);
            //map buttons
            if(paddata.BTN_UP)
                ret |= PAD_UP_MASK;
            if(paddata.BTN_DOWN)
                ret |= PAD_DN_MASK;
            if(paddata.BTN_LEFT)
                ret |= PAD_LT_MASK;
            if(paddata.BTN_RIGHT)
                ret |= PAD_RT_MASK;
            if(paddata.BTN_CROSS)
                ret |= PAD_CR_MASK;
            if(paddata.BTN_CIRCLE)
                ret |= PAD_CI_MASK;
            if(paddata.BTN_TRIANGLE)
                ret |= PAD_TR_MASK;
            if(paddata.BTN_SQUARE)
                ret |= PAD_SQ_MASK;
            if(paddata.BTN_START)
                ret |= PAD_ST_MASK;
            if(paddata.BTN_SELECT)
                ret |= PAD_SE_MASK;
        }
    }
    return ret;
}
//3rd
int app_update(int dat)
{
    return 1;
}
//4th
int app_render(int dat)
{
    /* DRAWING STARTS HERE */
    DbgDraw();
    //
    tiny3d_Flip();

    return 1;
}
//5th
int app_cleanup(int dat)
{
    ioPadEnd();

    return 1;
}
//restore app state after other module was executed
int _app_restore (char init)
{
    if (init)
        initConsole ();
    DbgHeader("FATFS EXFAT Example");
    DbgMess("Press o/circle to exit");
    DPrintf("\n");
    if (*fn)
        DPrintf("press triangle to list contents of file '%s'\n", fn);
    if (*wn)
        DPrintf("press cross to create a test file '%s'\n", wn);
    if (*dn)
        DPrintf("press rectangle to list contents of dir '%s'\n", dn);
    if (ffd != -1)
        DPrintf("press start for write/read test on drive '%d:/'\n", ffd);
    return 0;
}
//
s32 main(s32 argc, const char* argv[])
{
    //1 init
	app_init (0);
    _app_restore (0);
    int btn = app_input (0);
	// Ok, everything is setup. Now for the main loop.
	while(1) 
    {
        //2 input
        btn = app_input (0);
        if (btn & PAD_CI_MASK)
            break;
        //file create
        else if(btn & PAD_CR_MASK)
        {
            file_new (wn);
            //
            _app_restore (1);
        }
        //file contents
        else if(btn & PAD_TR_MASK)
        {
            file_run (fn);
            //
            _app_restore (1);
        }
        //dir listing
        else if(btn & PAD_SQ_MASK)
        {
            dir_run (dn);
            //
            _app_restore (1);
        }
        //file write
        else if(btn & PAD_ST_MASK)
        {
            if (ffd != -1)
                file_write_perf (ffd);
            _app_restore (0);
        }
        //file scan
        else if(btn & PAD_DN_MASK)
        {
            if (ffd != -1)
                file_scan_sectors (ffd);
            _app_restore (0);
        }
        //3
        app_update(0);
		//4
        app_render(0);
	}
    //5
    app_cleanup(0);
    //
	return 0;
}

