#include <string.h>
#include <png.h>
#include <ppu-types.h>
#include "makepng.h"

#define SUCCESS 	1
#define FAILED	 	0

extern s8 gimLoadFromBuffer(const void *buffer, int file_size, imgData *data);
extern char *LoadFile(char *path, int *file_size);

int gim2png(char* gimfilename,char* pngfilename) {
	
	int file_size;
	imgData gimData;
	
	u8 *gimFile = (u8 *) LoadFile(gimfilename, &file_size);
	if( gimFile == NULL ) return FAILED;
	
	
	if( gimLoadFromBuffer(gimFile, file_size, &gimData) != 0) {
		free(gimFile);
		return FAILED;
	}
		
	int ret = make_png(pngfilename, gimData);
	
	free(gimFile);
	free(gimData.bmp_out);
	
	return ret;	
}
