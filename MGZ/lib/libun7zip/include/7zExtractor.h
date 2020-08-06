//
// Created by huzongyao on 17-11-24.
//


#ifndef ANDROIDUN7ZIP_7ZEXTRACTOR_H
#define ANDROIDUN7ZIP_7ZEXTRACTOR_H

#define DEFAULT_IN_BUF_SIZE 0x100000

#ifdef __cplusplus
extern "C" {
#endif

/*
	void callback(const char* fileName, unsigned long fileSize, unsigned fileNum, unsigned numFiles);
*/
typedef void (*callback7z_t)(const char*, unsigned long, unsigned, unsigned);

int Extract7zFile(const char *srcFile, const char *destDir);
int Test7zFile(const char *srcFile);
int List7zFile(const char *srcFile, callback7z_t callback);

int Extract7zFileEx(const char *srcFile, const char *destDir, callback7z_t callback, unsigned long inBufSize);
int Test7zFileEx(const char *srcFile, callback7z_t callback, unsigned long inBufSize);

#ifdef __cplusplus
}
#endif

#endif //ANDROIDUN7ZIP_7ZEXTRACTER_H
