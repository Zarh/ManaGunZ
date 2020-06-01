(c) 2013 Estwald <www.elotrolado.net>

This library is a port from libntfs for Wii, NTFS-3G and libext2fs, for psl1ght v2

https://github.com/Estwald/PSDK3v2 // psl1ght and environment for  Windows

https://github.com/Estwald/libntfs_ext // this library


See "ps3_example". See below for "Standard I/O C functions"

This library now support NTFS partitions (Read/Write operations) and ext 2/3/4 (Read only operations)

The support for write operations is experimental (use as you own risk)

REMEMBER YOU TO DO UNMOUNT OPERATIONS BEFORE TO UNPLUG THE DEVICES (because surely you can lose information)

Use Windows "chkdsk" command to check the device frequently

/***********************************************************************************************************/
/***********************************************************************************************************/

To access to NTFS device, for file operations you must use this functions:


int ps3ntfs_open(const char *path, int flags, int mode); // flags: O_RDONLY... mode: 0777
int ps3ntfs_close(int fd);
int ps3ntfs_write(int fd, const char *ptr, size_t len);
int ps3ntfs_read(int fd, char *ptr, size_t len);
off_t  ps3ntfs_seek(int fd, off_t pos, int dir);
s64  ps3ntfs_seek64(int fd, s64 pos, int dir);  // 64 bits version for large files
int ps3ntfs_fstat(int fd, struct stat *st);
int ps3ntfs_stat(const char *file, struct stat *st);
int ps3ntfs_link(const char *existing, const char  *newLink);
int ps3ntfs_unlink(const char *name); // for files and folders

int ps3ntfs_rename(const char *oldName, const char *newName);
int ps3ntfs_mkdir(const char *path, int mode);

DIR_ITER*  ps3ntfs_diropen(const char *path);
int ps3ntfs_dirreset(DIR_ITER *dirState);
int ps3ntfs_dirnext(DIR_ITER *dirState, char *filename, struct stat *filestat);
int ps3ntfs_dirclose(DIR_ITER *dirState);

NTFS path must be absolute (with device/unit name). NTFS units can be accessed using "ntfsX:" or "/ntfsX:" (X = is the unit number).

Also i have implemented in this functions support for PS3 internal devices as "/dev_hdd", "/dev_usb000" using
LV2 syscalls

Examples: 

// NTFS operation to write

int fd = ps3ntfs_open("ntfs0:/text.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);

if(fd < 0) error(fd);

-------------------

// FAT operation  to write (from internal device) 

int fd = ps3ntfs_open("/dev_usb000/text.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);

if(fd < 0) error(fd);

-------------------

// NTFS operation to read

int fd = ps3ntfs_open("ntfs0:/text.txt", O_RDONLY, 0);

if(fd < 0) error(fd);

/***********************************************************************************************************/
/***********************************************************************************************************/

Exceptions:


ps3ntfs_chdir() -> is not supported because the paths must be absolute 

ps3ntfs_statvfs() -> is only supported for NTFS devices (for internal devices uses sysFsGetFreeSize() function)

ps3ntfs_dirreset() -> is only supported for NTFS devices


/***********************************************************************************************************/
/***********************************************************************************************************/

Special functions:

bool PS3_NTFS_IsInserted(int fd); // fd -> (0 to 7), return true if usb00X (fd is the number) is plugged

bool PS3_NTFS_Shutdown(int fd);  // fd -> (0 to 7), cause the close of the usb00X device (sector read/write operations fails)


/***********************************************************************************************************/
/***********************************************************************************************************/

Standard I/O C functions
------------------------

Now the library support some standard I/O function. By default PS3_STDIO is defined and ps3_io.c
compiles this support defining libc syscalls function from the __syscalls struct

NOTE: including sys/mutext.h and sys/syscalls.h, it cause an error because sys_mutex_attr is re-defined. For this
reason i define struct __syscalls_t directly and maybe you needs to do soe changes if you are using a different newlib

To initialize the standard function you must call at first function in the main(), NTFS_init_system_io();

Deinit function (NTFS_deinit_system_io()) is called mean atexit function.

Remember you that is possible to use PS3 system devices (as "/dev_usb000"), NTFS (as "/ntfs0:") a EXT2/3/4 (as "/ext0:")
devices with this library.

Standard functions supported:

open_r -> for stdio.h fopen()...
close_r -> for stdio.h fclose()...
read_r -> for stdio.h fread()...
write_r -> for stdio.h fwrite()...
lseek_r -> for stdio.h fseek()...
lseek64_r -> for using with large files (see ps3_example_stdio for this)
fstat_r -> for stat.h fstat()
stat_r -> for stat.h stat()

ftruncate_r -> for unistd.h ftruncate()
truncate_r -> for unistd.h truncate()
fsync_r -> for stdio.h fflush()
link_r -> for unistd.h link()
unlink_r -> for unistd.h unlink()
rename_r -> for stdio.h rename()
mkdir_r -> for stat.h mkdir()
rmdir_r -> for unistd.h rmdir()

closedir_r -> for dirent.h closedir()
opendir_r -> for dirent.h opendir()
readdir_r -> for dirent.h readdir()
readdir_r_r -> for dirent.h readdir_r()


