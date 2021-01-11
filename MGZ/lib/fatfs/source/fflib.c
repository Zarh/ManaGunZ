//fflib.c

#include <ppu-types.h>
#include "storage.h"
#include <malloc.h>
#include <sys/file.h>
#include <lv2/mutex.h> 
#include <sys/errno.h>
#include <stdio.h>

#include "ff.h"
#include "fflib.h"

#define VER "v0.4.0"

/*
you'll need these in the Makefile of your app in order to have actual access to raw devices
# aditional scetool flags (--self-ctrl-flags, --self-cap-flags...)
SCETOOL_FLAGS	+=	--self-ctrl-flags 4000000000000000000000000000000000000000000000000000000000000002
SCETOOL_FLAGS	+=	--self-cap-flags 00000000000000000000000000000000000000000000007B0000000100000000

**file_to_sectors**
@Zar, thanks!
"file_to_sectors is a function to get the sectors offsets of the iso from the usb device raw data (offset used by storage functions)

int parts = file_to_sectors( char *GamePath, u32 *sections, u32 *sections_size, u32 MAX_SECTIONS);

input : GamePath : the path of the file. For example, "/dev_usb000/GAMES/mygame.iso"
input : MAX_SECTIONS : number max of sections (allocated in memory). For example, MAX_SECTIONS = "((0x10000-sizeof(rawseciso_args))/8)"

output : parts : number of sections. For example, parts = 2
output : sections : offset of section used by the file . For example, sections[0] = 0x00223344, sections[1]=0x11223344
output : sections_size : size of each sections. For example, sections[0] = 0x800, sections[1]=0x800 
"

@aldostools, thanks!
"
That is the function used by prepNTFS to allow backup managers see the ISOs as native files.

prepNTFS or IRISMAN call that function for every ISO scanned or processed by selection in the case of IRISMAN.
The function file_to_sectors generate 2 lists: one is the list with the address of the initial raw sectors for each segment of the ISO file passed as parameter, the other is a list with the size of each segment (consecutive raw sectors).
If the ISO is multi-part, the lists of each multi-part file are appended to the initial lists.

Then the application creates a config file with a header containing the parameters needed by "rawseciso" plugin to access the storage in raw mode and the list of raw sectors and size of segments file needed to read the whole ISO file. The config file is stored in a native file system for later use.

For these ISO stored in non-standard file systems (ntfs, ext3) the backup manager read these config files and list them as "ISO files" stored in ntfs/ext3. For instance: /dev_hdd0/tmp/wmtmp/My Game.iso.ntfs[PS3ISO] is displayed as /ntfs0:/PS3ISO/My Game.iso

When the user mounts one of these ISO files, the backup manager starts the rawseciso plugin and passes the data of config file as parameter. The rawseciso plugin acts as intermediary between Cobra and the storage device. It starts the discfile_proxy in Cobra and rawseciso plugin emulates the physical disc serving the sectors requested by the SCSI driver via Cobra's proxy.

A retail game is accessed from disc (more or less) like this:
Game <=> GameOS <=> SCSI <=> bluray driver <=> raw sectors

An ISO file stored in a standard file system (hdd0/fat32) is accessed like this:
Game <=> GameOS <=> SCSI <=> Cobra <=> cell file system <=> file data

An ISO file stored in a non-standard file system (ntfs/ext3) is accessed like this:
Game <=> GameOS <=> SCSI <=> Cobra <=> discfile_proxy <=> rawseciso plugin <=> storage device <=> raw sectors

A remote ISO is accessed like this:
Game <=> GameOS <=> SCSI <=> Cobra <=> discfile_proxy <=> netiso plugin <=> net <=> ps3netsrv <=> file system <=> file data
"
*/

//extern void NPrintf (const char* fmt, ...);
#define NPrintf(fmt, ...)

static u64 ffdev_id[MAXFDS];
static int ffdev_fd[MAXFDS];
static int ffdev_ss[MAXFDS];

static char _fflib_init = 0;

int fflib_init()
{
    int k;
    if (_fflib_init == 1)
        return FR_EXIST;
    for (k = 0; k < MAXFDS; k++)
    {
        ffdev_id[k] = 0;
        ffdev_fd[k] = -1;
        ffdev_ss[k] = -1;
    }
    _fflib_init = 1;
    return FR_OK;
}

int fflib_is_fatfs (char *path)
{
    FDIR dir;
    FATFS fs;       /* Work area (filesystem object) for logical drive */
    if (f_mount (&fs, path, 0) == FR_OK)
    {
        if (f_opendir (&dir, path) == FR_OK)
        {
            f_closedir (&dir);
            f_mount (0, path, 0);
            return FR_OK;
        }
        f_mount (0, path, 0);
    }
    //
    return FR_NO_FILESYSTEM;
}

int fflib_attach(int idx, u64 id, int now)
{
    if (idx < 0 || idx > MAXFDS)
    {
        NPrintf ("!fflib_attach: invalid drive index %d for 0x%llx %d\n", idx, id, now);
        return FR_INVALID_DRIVE;
    }
    if (ffdev_id[idx] > 0)
    {
        NPrintf ("!fflib_attach: drive already attached as 0x%llx on index %d for 0x%llx %d\n", ffdev_id[idx], idx, id, now);
        return FR_EXIST;
    }
    fflib_init ();
    //
    ffdev_id[idx] = id;
    //
    if (now)
    {
        //mount fs and check access
        FDIR dir;
        FATFS fs;       /* Work area (filesystem object) for logical drive */
        char drv[7];    //MAXFDS MUST not be more than 3 digits
        snprintf (drv, 7, "%d:/", idx);
        if(f_mount (&fs, drv, 0) != FR_OK)
        {
            NPrintf ("!fflib_attach: mount failed for 0x%llx on index %d\n", ffdev_id[idx], idx);
            return FR_NOT_ENABLED;
        }
        /* Open the directory */
        int res = f_opendir (&dir, drv);
        if (res != FR_OK)
        {
            f_mount (0, drv, 0);
            NPrintf ("!fflib_attach: can't open drive for 0x%llx on index %d res %d\n", ffdev_id[idx], idx, res);
            return FR_NO_FILESYSTEM;
        }
        f_closedir (&dir);
        f_mount (0, drv, 0);
    }
    return FR_OK;
}

int fflib_detach(int idx)
{
    if (idx < 0 || idx > MAXFDS)
    {
        NPrintf ("!fflib_detach: invalid drive index %d for 0x%llx %d\n", idx);
        return FR_INVALID_DRIVE;
    }
    fflib_init ();
    if(ffdev_id[idx] < 0)
    {
        NPrintf ("!fflib_detach: can't detach 0x%llx on index %d\n", ffdev_id[idx], idx);
        return FR_NOT_READY;
    }
    if(ffdev_fd[idx] > 0)
        sys_storage_close (ffdev_fd[idx]);
    ffdev_id[idx] = 0;
    ffdev_fd[idx] = -1;
    ffdev_ss[idx] = -1;

    return FR_OK;
}

u64 fflib_id_get(int idx)
{
    fflib_init ();
    return ffdev_id[idx];
}

int fflib_fd_get(int idx)
{
    fflib_init ();
    return ffdev_fd[idx];
}

int fflib_ss_get(int idx)
{
    fflib_init ();
    return ffdev_ss[idx];
}

int fflib_fd_set(int idx, int fd)
{
    fflib_init ();
    ffdev_fd[idx] = fd;

    return fd;
}

int fflib_ss_set(int idx, int ss)
{
    fflib_init ();
    ffdev_ss[idx] = ss;

    return ss;
}

// maps a file to a list of sectors and its sizes, based on a maximum buffer provided by caller
/* usage example from IRISMAN:
    // use plugin
    plugin_args = malloc(0x20000);

    psxseciso_args *p_args;

    memset(plugin_args, 0, 0x10000);

    p_args = (psxseciso_args *)plugin_args;
    p_args->device = 0ULL;
    p_args->emu_mode = EMU_PSX_MULTI;

    int max_parts = (0x10000 - sizeof(psxseciso_args)) / 8;

    uint32_t *sections = malloc(max_parts * sizeof(uint32_t));
    uint32_t *sections_size = malloc(max_parts * sizeof(uint32_t));

    u32 offset = 0;

    for(n = 0; n < nfiles; n++)
    {
        if(stat(files[n], &s)) s.st_size = 0x40000000;
        if(!strncmp(files[n], "/ntfs", 5) || !strncmp(files[n], "/ext", 4))
        {
            if(p_args->device == 0) p_args->device = USB_MASS_STORAGE(NTFS_Test_Device(((char *) files[n])+1));

            memset(sections, 0, max_parts * sizeof(uint32_t));
            memset(sections_size, 0, max_parts * sizeof(uint32_t));
            int parts = ps3ntfs_file_to_sectors(files[n], sections, sections_size, max_parts, 1);
            if(parts <=0 || parts >= max_parts)
            {
                if(sections) free(sections);
                if(sections_size) free(sections_size);
                if(plugin_args) free(plugin_args); plugin_args = NULL;

                sprintf(temp_buffer, "Too much parts in PSX iso:\n%s", files[n]);
                ..
            }
*/

static uint32_t *sects;
static uint32_t *nsect;
static int pidx = 0;
static int max_parts = 0;
int sector_record_add (unsigned int sect, unsigned int nsec)
{
    if (pidx == -1)
    {
        //can't record any more
        return -1;
    }
    //safety
    if (max_parts <= 0)
        return -1;
    //NPrintf ("reading from sector %u for %u sectors\n", sect, nsec);
    if (nsect[pidx] == 0)
    {
        sects[pidx] = sect;    //set start sector
        nsect[pidx] = nsec;
    }
    else
    {
        //do we need to add to the same?
        if (sects[pidx] + nsect[pidx] == sect)
        {
            nsect[pidx] += nsec;
        }
        else
        {
            //register new section
            pidx++;
            //overflow?
            if (pidx >= max_parts)
                pidx = -1;
            else
            {
                sects[pidx] = sect;    //set start section sector
                nsect[pidx] = nsec;
            }
        }
    }
    return 0;
}

#define MSZ (1024*1024) //1MB slice
#define FWR (MSZ*1024)  //1GB as slices of 1MB
#define BSZ (3*MSZ)     //3MB slice

//!!USE THESE WITH CARE!
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

int fflib_file_to_sectors(const char *path, uint32_t *sec_out, uint32_t *size_out, int max, int phys)
{
    sects = sec_out;
    nsect = size_out;
    pidx = 0;   //current part index reset
    max_parts = max;
    
    //FATFS fs;     /* Ponter to the filesystem object */
    //int ret = f_mount (&fs, path, 0);                    /* Mount the default drive */
    //if (ret != FR_OK) return -1;
    
    FRESULT fr;         /* FatFs function common result code */
    UINT bw;
    FIL fdst;           /* File objects */
    fr = f_open_sectors (&fdst, path, FA_READ, &sector_record_add);
    if (fr != FR_OK)
        return -1;
    while (1)
    {
        //simulate reading 300MB at a time to pick up the sections accessed by driver
        //might require tuning but it seems we cannot read ALL file at once.. I tried ;-)=
        fr = f_read_sectors (&fdst, NULL, MSZ * 300, &bw, &sector_record_add);  /* Read a chunk of source file */
        //error reading
        if (fr != FR_OK)
        {
            pidx = -1;
            break;
        }
        //are we done reading? EOF
        if (bw == 0)
        {
            pidx++; //we may end up with only one entry in best case
            break;
        }
    }
    f_close(&fdst);
    //
    //f_mount (NULL, path, 0);                    /* UnMount the default drive */
    //
    return pidx;
}
