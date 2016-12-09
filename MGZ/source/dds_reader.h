/**
* dds_reader.h
*
* Copyright (c) 2015 Kenji Sasaki
* Released under the MIT license.
* https://github.com/npedotnet/DDSReader/blob/master/LICENSE
*
* English document
* https://github.com/npedotnet/DDSReader/blob/master/README.md
*
* Japanese document
* http://3dtech.jp/wiki/index.php?DDSReader
*
*/

#ifndef __DDS_READER_H__
#define __DDS_READER_H__

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DDS_ORDER {
	int redShift;
	int greenShift;
	int blueShift;
	int alphaShift;
} DDS_ORDER;

const DDS_ORDER *DDS_READER_ARGB;
const DDS_ORDER *DDS_READER_ABGR;

void *ddsMalloc(size_t size);
void ddsFree(void *memory);

int ddsGetHeight(const unsigned char *buffer);
int ddsGetWidth(const unsigned char *buffer);
int ddsGetMipmap(const unsigned char *buffer);
int *ddsRead(const unsigned char *buffer, const DDS_ORDER *order, int mipmapLevel);

#ifdef __cplusplus
}
#endif

#endif /* __DDS_READER_H__ */
