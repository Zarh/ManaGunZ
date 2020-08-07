#ifndef UNTAR_EXTRACTOR_H
#define UNTAR_EXTRACTOR_H

#define TAR_REGULAR         '\0'
#define TAR_NORMAL          '0'
#define TAR_HARDLINK        '1'
#define TAR_SYMLINK         '2'
#define TAR_CHAR            '3'
#define TAR_BLOCK           '4'
#define TAR_DIRECTORY       '5'
#define TAR_FIFO            '6'
#define TAR_CONTIGUOUS      '7'

/*
	void callback(const char* fileName, unsigned long fileSize, char fileType);
*/
typedef void (*tar_callback_t)(const char*, unsigned long, char);

int untarEx(const char* srcFile, const char* dstPath, tar_callback_t callback);
int untarEx_gz(const char* srcFile, const char* dstPath, tar_callback_t callback);
int untarEx_bz2(const char* srcFile, const char* dstPath, tar_callback_t callback);

int untar(const char* srcFile, const char* dstPath);
int untar_gz(const char* srcFile, const char* dstPath);
int untar_bz2(const char* srcFile, const char* dstPath);

int tar(const char* dstFile, const char* srcPath);
int tar_gz(const char* dstFile, const char* srcPath);
int tar_bz2(const char* dstFile, const char* srcPath);

#endif //UNTAR_EXTRACTOR_H
