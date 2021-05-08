#include <sys/stat.h>
#include <dirent.h>

#include "mgz_io.h"
#include "ff.h"

#define FREE(x) if(x!=NULL) {free(x);x=NULL;}

#define YES 1
#define NO  0
	
#define TYPE_NTFS	0 // ntfs lib support file system
#define TYPE_EXFAT	1

//extern u8 SetFilePerms(char *path);

int MGZ_truncate(char *path, u64 len)
{
    int ret;
    int fd;

	if( is_exFAT(path) ) {
		
		FIL fp;
		FRESULT res;    

		res = f_open(&fp, path, FA_CREATE_NEW | FA_WRITE | FA_READ); 
		if(res != FR_OK) {
			return -1;
		}
		res = f_lseek(&fp, f_size(&fp) - len);
		if(res != FR_OK) {
			f_close(&fp);
			return -1;
		}
		
		res = f_truncate(&fp);
		if(res != FR_OK) {
			f_close(&fp);
			return -1;
		}
		
		res = f_close(&fp);
		if( res != FR_OK) return -1;
		
		return res;
	}
	
    fd = ret = ps3ntfs_open(path, O_RDWR, 0666);

    if(ret < 0) return ret;

    ret = ps3ntfs_ftruncate(fd, len);
	
    ps3ntfs_close(fd);
	
    return ret;
}

MGZ_FILE* MGZ_fopen(char *filepath, const char *mode)
{	
	u8 exfat = is_exFAT(filepath); 	
	
	int oflags;
	int m, o;
	switch (*mode++) {
		case 'r':	/* open for reading */
			m = exfat? FA_READ : O_RDONLY;
			o = 0;
			break;
		case 'w':	/* open for writing */
			m = exfat? FA_WRITE : O_WRONLY;
			o = exfat? FA_CREATE_ALWAYS : O_CREAT | O_TRUNC;
			break;
		case 'a':	/* open for appending */
			m = exfat? FA_WRITE : O_WRONLY;
			o = exfat? FA_CREATE_ALWAYS | FA_OPEN_APPEND : O_CREAT | O_APPEND;
			break;
		default:	/* illegal mode */
			return (0);
		}
		/* [rwa]\+ or [rwa]b\+ means read and write */
		if (*mode == '+' || (*mode == 'b' && mode[1] == '+')) {
			m = exfat? FA_READ | FA_WRITE : O_RDWR;
	}
	
	oflags = m | o;
	
	MGZ_FILE *mgz_file = (MGZ_FILE *) malloc(sizeof(MGZ_FILE));
	if(mgz_file == NULL) return NULL;
	
	mgz_file->type = exfat;
	
	if(exfat) {
		int res = f_open(&mgz_file->fp, filepath, oflags);
		if( res != FR_OK) {
			FREE(mgz_file); 
			return NULL;
		}
	} 
	else {
		mgz_file->fd = ps3ntfs_open(filepath, oflags, 0777);
		
		if(mgz_file->fd<0) {
			//SetFilePerms(filepath);
			mgz_file->fd = ps3ntfs_open(filepath, oflags, 0777);
			if(mgz_file->fd<0) {
				FREE(mgz_file);
				return NULL;
			}
		}
	}
	
	return mgz_file;
}

s64 MGZ_fseek(MGZ_FILE* mgz_file, s64 pos, int whence)
{
	if(mgz_file->type==TYPE_NTFS) return ps3ntfs_seek64(mgz_file->fd, (s64) pos, whence);
		
	FRESULT res = -1;
	
	if(whence == SEEK_SET ) res = f_lseek(&mgz_file->fp, pos);
	if(whence == SEEK_CUR ) res = f_lseek(&mgz_file->fp, f_tell(&mgz_file->fp) + pos);
	if(whence == SEEK_END ) res = f_lseek(&mgz_file->fp, f_size(&mgz_file->fp));
	
	if( res == FR_OK ) return 0;
	
	return -1;
	
}

size_t MGZ_fread(void *ptr, size_t size, size_t count, MGZ_FILE* mgz_file)
{
	if(mgz_file->type==TYPE_NTFS) return ps3ntfs_read(mgz_file->fd, (char*)ptr, size*count);
	
	u32 br=0;
	
	if(f_read(&mgz_file->fp, ptr, (u32) size*count, &br)==FR_OK) return (size_t) br;
	
	return -1;
}

size_t MGZ_fwrite(void *ptr, size_t size, size_t count, MGZ_FILE* mgz_file)
{
	if(mgz_file->type==TYPE_NTFS) return ps3ntfs_write(mgz_file->fd, (char*)ptr, size*count);
	
	u32 bw=0;
	
	if(f_write(&mgz_file->fp, ptr, (u32) size*count, &bw)==FR_OK) return (size_t) bw;
	
	return -1;
}

char *MGZ_fgets(char *str, int length, MGZ_FILE* mgz_file)
{
	if(mgz_file->type==TYPE_NTFS) {
		char c;
		int count=0;
		if(length==0) return NULL;
		
		memset(str, 0, length);
		while(ps3ntfs_read(mgz_file->fd, &c, 1))
		{	
			str[count]=c;
			if(count==length) break;
			count++;
			if(c=='\n' || c==0) break;
		}
		if(count == 0) return NULL;
		
		return str;
	}
	
	return f_gets(str, length, &mgz_file->fp);
}

int MGZ_fputs(char *str, MGZ_FILE* mgz_file)
{
	if(mgz_file->type==TYPE_NTFS) return ps3ntfs_write(mgz_file->fd, str, strlen(str));
	
	return f_puts(str, &mgz_file->fp);
}

int MGZ_fclose(MGZ_FILE* mgz_file)
{	
	int ret = -1;
	
	if(mgz_file->type==TYPE_NTFS) ret=ps3ntfs_close(mgz_file->fd);
	if(mgz_file->type==TYPE_EXFAT) ret=f_close(&mgz_file->fp);
	
	FREE(mgz_file);
	
	if(ret!=0) ret=-1;

	return ret;
}

u64 MGZ_ftell(MGZ_FILE* mgz_file)
{
	if(mgz_file->type==TYPE_NTFS) return ps3ntfs_seek64(mgz_file->fd, 0, SEEK_CUR);
	
	return f_tell(&mgz_file->fp);
}

char MGZ_fgetc(MGZ_FILE* mgz_file)
{
	char c;
	
	if(mgz_file->type==TYPE_NTFS) {
		if( ps3ntfs_read(mgz_file->fd, &c, 1) != 1) return -1;
		return c;
	} else
	if(mgz_file->type==TYPE_EXFAT) {
		u32 br=0;
		if(f_read(&mgz_file->fp, &c, 1, &br)==FR_OK) {
			if(br!=1) return -1;
			return c;
		}
	}
	
	return -1;
}

char MGZ_fputc(char c, MGZ_FILE* mgz_file)
{
	if(mgz_file->type==TYPE_NTFS) ps3ntfs_write(mgz_file->fd, (const char *) &c, 1);
	
	if(mgz_file->type==TYPE_EXFAT) return f_putc(c, &mgz_file->fp);
	
	return -1;
}

// todo...
int MGZ_ferror(MGZ_FILE *mgz_file)
{
	return 0;
}

int MGZ_feof(MGZ_FILE *mgz_file)
{
	return 0;	
}

int MGZ_fflush(MGZ_FILE *mgz_file)
{
	if(mgz_file->type==TYPE_NTFS) return ps3ntfs_fsync(mgz_file->fd);
	
	if(mgz_file->type==TYPE_EXFAT) return f_sync(&mgz_file->fp);
	
	return -1;
}

#define FILE		MGZ_FILE

#define fopen		MGZ_fopen
#define fread		MGZ_fread
#define fwrite		MGZ_fwrite
#define fclose		MGZ_fclose
#define fseek		MGZ_fseek
#define ftell 		MGZ_ftell
#define fputc		MGZ_fputc
#define fgetc 		MGZ_fgetc
#define fgets 		MGZ_fgets
#define fputs 		MGZ_fputs
#define truncate 	MGZ_truncate
//#define ferror		MGZ_ferror
//#define feof			MGZ_feof
#define fflush		MGZ_fflush

//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************

int MGZ_rename(char *old_path, char *new_path)
{
	if( is_exFAT(old_path) && is_exFAT(new_path)) return f_rename(old_path, new_path);
	return ps3ntfs_rename(old_path, new_path);
}

int MGZ_unlink(char *path)
{
	if( is_exFAT(path) ) return f_unlink(path);
	
	return ps3ntfs_unlink(path);
}

int MGZ_mkdir(char *path, int mode)
{
	if( is_exFAT(path) ) {
		FRESULT res = f_mkdir(path);
		if( res!= FR_OK) return -1;
		// todo convert mode fflib chmod flags...
		res = f_chmod(path, 0, AM_RDO | AM_ARC | AM_SYS | AM_HID);
		return res;
	}
	return ps3ntfs_mkdir(path, mode);
}

#define unlink		MGZ_unlink
#define rename		MGZ_rename
#define mkdir		MGZ_mkdir
#define rmdir		unlink

int MGZ_stat(char *path, struct stat *st)
{
	if(is_exFAT(path)) {
		FILINFO fno;
		
		if(f_stat(path, &fno) != FR_OK) return -1;
		
		st->st_size = fno.fsize;
		st->st_mtime = fno.ftime;
		
		// todo 
		if(fno.fattrib & AM_DIR) {
			st->st_mode = S_IFDIR | 0777;
		} else {
			st->st_mode = S_IFMT | 0777;
		}
		return 0;
	}
	return ps3ntfs_stat(path, st);
}


//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************

MGZ_DIR* MGZ_opendir(char *path)
{
	MGZ_DIR *mgz_dir = (MGZ_DIR *) malloc(sizeof(MGZ_DIR));
	if(!mgz_dir) return NULL;
	
	mgz_dir->dir = (struct dirent *) malloc(sizeof(struct dirent));
	if(!mgz_dir->dir) {
		FREE(mgz_dir);
		return NULL;
	}
	
	u8 exfat = is_exFAT(path);
	
	mgz_dir->type = exfat;
	
	if(exfat) {
		int x = f_opendir(&mgz_dir->fdir, path);
		if(x != FR_OK) {
			FREE(mgz_dir->dir);
			FREE(mgz_dir);
		}
		return mgz_dir;
	}
	
	mgz_dir->dir_iter = ps3ntfs_diropen(path);
	if(mgz_dir->dir_iter == NULL) {
		FREE(mgz_dir->dir);
		FREE(mgz_dir);
	}
	
	return mgz_dir;
}

int MGZ_closedir(MGZ_DIR *mgz_dir)
{
	int res = -1;
	if(mgz_dir->type == TYPE_EXFAT) {
		res = f_closedir(&mgz_dir->fdir);
	} else {
		res = ps3ntfs_dirclose(mgz_dir->dir_iter);
	}
	
	FREE(mgz_dir->dir);
	FREE(mgz_dir);
	
	return res;
}

struct dirent *MGZ_readdir(MGZ_DIR *mgz_dir)
{
	memset(mgz_dir->dir, 0, sizeof(struct dirent));
	
	struct dirent *d = mgz_dir->dir;
	
	if(mgz_dir->type == TYPE_EXFAT) {
		FILINFO fno;
		
		if( f_readdir(&mgz_dir->fdir, &fno) != FR_OK ) return NULL;
		
		if( fno.fname[0] == 0 ) return NULL;
		
		d->d_namlen = strlen(fno.fname);
		strcpy(d->d_name, fno.fname);
		
		if(fno.fattrib & AM_DIR) {
			d->d_type = DT_DIR;
		} else {
			d->d_type = DT_REG;
		}
		
		return d;
	}
	
	struct stat s;
	if( ps3ntfs_dirnext(mgz_dir->dir_iter, d->d_name, &s)  != 0) return NULL;
	
	if(S_ISDIR(s.st_mode)) {
		d->d_type = DT_DIR;
	} else {
		d->d_type = DT_REG;
	}
	return d;
}

#define DIR			MGZ_DIR

#define	opendir		MGZ_opendir
#define readdir		MGZ_readdir
#define	closedir	MGZ_closedir
