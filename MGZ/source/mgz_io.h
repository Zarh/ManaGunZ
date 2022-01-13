#ifndef _MGZ_IO_H_
#define _MGZ_IO_H_

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ppu-types.h>
#include <sys/stat.h>

#include "ff.h"
#include "ntfs.h"
#include "exFAT.h"

#define FREE(x) if(x!=NULL) {free(x);x=NULL;}

#define YES 1
#define NO  0
	
#define TYPE_NTFS	0 // ntfs lib support file system
#define TYPE_EXFAT	1

typedef struct {
	int type;
	
// exFAT
	FIL fp;
	
// ntfs
	int fd;
} MGZ_FILE;

int MGZ_truncate(char *path, u64 len);
MGZ_FILE* MGZ_fopen(char *filepath, const char *mode);
s64 MGZ_fseek(MGZ_FILE* mgz_file, s64 pos, int whence);
size_t MGZ_fread(void *ptr, size_t size, size_t count, MGZ_FILE* mgz_file);
size_t MGZ_fwrite(void *ptr, size_t size, size_t count, MGZ_FILE* mgz_file);
char *MGZ_fgets(char *str, int length, MGZ_FILE* mgz_file);
int MGZ_fputs(char *str, MGZ_FILE* mgz_file);
int MGZ_fclose(MGZ_FILE* mgz_file);
u64 MGZ_ftell(MGZ_FILE* mgz_file);
char MGZ_fgetc(MGZ_FILE* mgz_file);
char MGZ_fputc(char c, MGZ_FILE* mgz_file);
//int MGZ_ferror(FILE * mgz_file);
//int MGZ_feof(MGZ_FILE *mgz_file);
int MGZ_fflush(MGZ_FILE *mgz_file);
int MGZ_fprintf(MGZ_FILE *mgz_file, const char *fmt, ...);

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
//#define fprintf		MGZ_fprintf

//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************

int MGZ_rename(char *old_path, char *new_path);
int MGZ_unlink(char *path);
int MGZ_mkdir(char *path, int mode);

#define unlink		MGZ_unlink
#define rename		MGZ_rename
#define mkdir		MGZ_mkdir
#define rmdir		unlink

int MGZ_stat(char *path, struct stat *st);

#define stat(x,y) 	MGZ_stat(x,y)

//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************

typedef struct {

	int type;

// exFAT
	FDIR fdir;
	
// ntfs
	DIR_ITER *dir_iter;
	
// readdir
	struct dirent *dir;
} MGZ_DIR;

MGZ_DIR* MGZ_opendir(char *path);
int MGZ_closedir(MGZ_DIR *mgz_dir);
struct dirent *MGZ_readdir(MGZ_DIR *mgz_dir);

#define DIR			MGZ_DIR

#define	opendir		MGZ_opendir
#define readdir		MGZ_readdir
#define	closedir	MGZ_closedir

#endif
