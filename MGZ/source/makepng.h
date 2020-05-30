#ifndef MAKEPNG_H
#define MAKEPNG_H

#define FAILED	0
#define SUCCESS	1

typedef struct
{
	void *bmp_out;

	u32 pitch;
	u32 width;
	u32 height;
} imgData;

u8 make_png(char *outfile, imgData data);

#endif
