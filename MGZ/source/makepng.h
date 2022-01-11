#ifndef MAKEPNG_H
#define MAKEPNG_H

#include "extern.h"

typedef struct
{
	void *bmp_out;

	u32 pitch;
	u32 width;
	u32 height;
} imgData;

u8 make_png(char *outfile, imgData data);

#endif
