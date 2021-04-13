#ifndef __IRD_GZ_H
#define __IRD_GZ_H

#include "ird_build.h"


// mem to mem. Don't forget to free(dest).
int GZ_compress(char *source, int sourceLen, char **dest, int *destLen);
// FileStream to mem. Don't forget to free(dest).
int GZ_compress2(FILE *source, int sourceLen, char **dest, int *destLen);
// FileStream to FileStream.
int GZ_compress3(FILE *source, FILE *dest);
// FilePath to FilePath
int GZ_compress5(char *source, char *dest);

// mem to mem. Don't forget to free(dest).
int GZ_decompress(char *source, int sourceLen, char **dest, int *destLen);
// FileStream to FileStream.
int GZ_decompress3(FILE *source, FILE *dest);
// mem to FileStream
int GZ_decompress4(char *source, int sourceLen, FILE *dest);
// FilePath to FilePath
int GZ_decompress5(char *source, char *dest);
// FileStream to mem with fixed size. It will extract until destLen is reached. Don't forget to free(dest).
int GZ_decompress6(FILE *source, int sourceLen, char **dest, int destLen);
// mem to FilePath
int GZ_decompress7(char *source, int sourceLen, char *dest);
// FilePath to mem with fixed size. It will extract until destLen is reached. Don't forget to free(dest).
int GZ_decompress8(char *source, char **dest, int destLen);

#endif