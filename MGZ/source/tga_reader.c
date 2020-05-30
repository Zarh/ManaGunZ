/**
 * tga_reader.c
 * 
 * Copyright (c) 2014 Kenji Sasaki
 * Released under the MIT license.
 * https://github.com/npedotnet/TGAReader/blob/master/LICENSE
 * 
 * English document
 * https://github.com/npedotnet/TGAReader/blob/master/README.md
 * 
 * Japanese document
 * http://3dtech.jp/wiki/index.php?TGAReader
 * 
 */

#include "tga_reader.h"

static const TGA_ORDER _TGA_READER_ARGB = {16, 8, 0, 24};
const TGA_ORDER *TGA_READER_ARGB = &_TGA_READER_ARGB;

static const TGA_ORDER _TGA_READER_ABGR = {0, 8, 16, 24};
const TGA_ORDER *TGA_READER_ABGR = &_TGA_READER_ABGR;

void *tgaMalloc(size_t size) {
	return malloc(size);
}

void tgaFree(void *memory) {
	free(memory);
}

int tgaGetWidth(const unsigned char *buffer) {
	return (buffer[12] & 0xFF) | (buffer[13] & 0xFF) << 8;
}

int tgaGetHeight(const unsigned char *buffer) {
	return (buffer[14] & 0xFF) | (buffer[15] & 0xFF) << 8;
}

#define COLORMAP 1
#define RGB 2
#define GRAYSCALE 3
#define COLORMAP_RLE 9
#define RGB_RLE 10
#define GRAYSCALE_RLE 11
#define RIGHT_ORIGIN 0x10
#define UPPER_ORIGIN 0x20

static unsigned char *decodeRLE(int width, int height, int depth, const unsigned char *buffer, int offset);

static int *createPixelsFromColormap(int width, int height, int depth, const unsigned char *bytes, int offset, const unsigned char *palette, int colormapOrigin, int descriptor, const TGA_ORDER *order);
static int *createPixelsFromRGB(int width, int height, int depth, const unsigned char *bytes, int offset, int descriptor, const TGA_ORDER *order);
static int *createPixelsFromGrayscale(int width, int height, int depth, const unsigned char *bytes, int offset, int descriptor, const TGA_ORDER *order);

int *tgaRead(const unsigned char *buffer, const TGA_ORDER *order) {

	// header
//	int idFieldLength = buffer[0] & 0xFF;
//	int colormapType = buffer[1] & 0xFF;
	int type = buffer[2] & 0xFF;
	int colormapOrigin = (buffer[3] & 0xFF) | (buffer[4] & 0xFF) << 8;
	int colormapLength = (buffer[5] & 0xFF) | (buffer[6] & 0xFF) << 8;
	int colormapDepth = buffer[7] & 0xFF;
//	int originX = (buffer[8] & 0xFF) | (buffer[9] & 0xFF) << 8; // unsupported
//	int originY = (buffer[10] & 0xFF) | (buffer[11] & 0xFF) << 8; // unsupported
	int width = tgaGetWidth(buffer);
	int height = tgaGetHeight(buffer);
	int depth = buffer[16] & 0xFF;
	int descriptor = buffer[17] & 0xFF;
	    
	int *pixels = NULL;
		
	// data
	switch(type) {
	case COLORMAP: {
		int imageDataOffset = 18 + (colormapDepth / 8) * colormapLength;
		pixels = createPixelsFromColormap(width, height, colormapDepth, buffer, imageDataOffset, buffer, colormapOrigin, descriptor, order);
		} break;
	case RGB:
		pixels = createPixelsFromRGB(width, height, depth, buffer, 18, descriptor, order);
		break;
	case GRAYSCALE:
		pixels = createPixelsFromGrayscale(width, height, depth, buffer, 18, descriptor, order);
		break;
	case COLORMAP_RLE: {
		int imageDataOffset = 18 + (colormapDepth / 8) * colormapLength;
		unsigned char *decodeBuffer = decodeRLE(width, height, depth, buffer, imageDataOffset);
		pixels = createPixelsFromColormap(width, height, colormapDepth, decodeBuffer, 0, buffer, colormapOrigin, descriptor, order);
		tgaFree(decodeBuffer);
		} break;
	case RGB_RLE: {
		unsigned char *decodeBuffer = decodeRLE(width, height, depth, buffer, 18);
		pixels = createPixelsFromRGB(width, height, depth, decodeBuffer, 0, descriptor, order);
		tgaFree(decodeBuffer);
		} break;
	case GRAYSCALE_RLE: {
		unsigned char *decodeBuffer = decodeRLE(width, height, depth, buffer, 18);
		pixels = createPixelsFromGrayscale(width, height, depth, decodeBuffer, 0, descriptor, order);
		tgaFree(decodeBuffer);
		} break;
	default:
		break;
	}
	
	return pixels;

}

static unsigned char *decodeRLE(int width, int height, int depth, const unsigned char *buffer, int offset) {
	int elementCount = depth/8;
	unsigned char elements[4];
	int decodeBufferLength = elementCount * width * height;
	unsigned char *decodeBuffer = (unsigned char *)tgaMalloc(decodeBufferLength);
	int decoded = 0;
	while(decoded < decodeBufferLength) {
		int packet = buffer[offset++] & 0xFF;
		if((packet & 0x80) != 0) { // RLE
			int i, j, count;
			for(i=0; i<elementCount; i++) {
				elements[i] = buffer[offset++];
			}
			count = (packet&0x7F)+1;
			for(i=0; i<count; i++) {
				for(j=0; j<elementCount; j++) {
					decodeBuffer[decoded++] = elements[j];
				}
			}
		}
		else { // RAW
			int count = (packet+1) * elementCount;
			int i;
			for(i=0; i<count; i++) {
				decodeBuffer[decoded++] = buffer[offset++];
			}
		}
	}
	return decodeBuffer;
}

static int *createPixelsFromColormap(int width, int height, int depth, const unsigned char *bytes, int offset, const unsigned char *palette, int colormapOrigin, int descriptor, const TGA_ORDER *order) {
	int *pixels = NULL;
	int rs = order->redShift;
	int gs = order->greenShift;
	int bs = order->blueShift;
	int as = order->alphaShift;
	switch(depth) {
	case 24:
		pixels = (int *)tgaMalloc(4*width*height);
		if((descriptor & RIGHT_ORIGIN) != 0) {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int colormapIndex = (bytes[offset+width*i+j] & 0xFF) - colormapOrigin;
						int color = 0xFFFFFFFF;
						if(colormapIndex >= 0) {
							int index = 3*colormapIndex+18;
							int b = palette[index+0] & 0xFF;
							int g = palette[index+1] & 0xFF;
							int r = palette[index+2] & 0xFF;
							int a = 0xFF;
							color = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
						}
						pixels[width*i+(width-j-1)] = color;
					}
				}
			}
			else {
				// LowerRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int colormapIndex = (bytes[offset+width*i+j] & 0xFF) - colormapOrigin;
						int color = 0xFFFFFFFF;
						if(colormapIndex >= 0) {
							int index = 3*colormapIndex+18;
							int b = palette[index+0] & 0xFF;
							int g = palette[index+1] & 0xFF;
							int r = palette[index+2] & 0xFF;
							int a = 0xFF;
							color = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
						}
						pixels[width*(height-i-1)+(width-j-1)] = color;
					}
				}
			}
		}
		else {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int colormapIndex = (bytes[offset+width*i+j] & 0xFF) - colormapOrigin;
						int color = 0xFFFFFFFF;
						if(colormapIndex >= 0) {
							int index = 3*colormapIndex+18;
							int b = palette[index+0] & 0xFF;
							int g = palette[index+1] & 0xFF;
							int r = palette[index+2] & 0xFF;
							int a = 0xFF;
							color = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
						}
						pixels[width*i+j] = color;
					}
				}
			}
			else {
				// LowerLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int colormapIndex = (bytes[offset+width*i+j] & 0xFF) - colormapOrigin;
						int color = 0xFFFFFFFF;
						if(colormapIndex >= 0) {
							int index = 3*colormapIndex+18;
							int b = palette[index+0] & 0xFF;
							int g = palette[index+1] & 0xFF;
							int r = palette[index+2] & 0xFF;
							int a = 0xFF;
							color = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
						}
						pixels[width*(height-i-1)+j] = color;
					}
				}
			}
		}
		break;
	case 32:
		pixels = (int *)tgaMalloc(4*width*height);
		if((descriptor & RIGHT_ORIGIN) != 0) {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int colormapIndex = (bytes[offset+width*i+j] & 0xFF) - colormapOrigin;
						int color = 0xFFFFFFFF;
						if(colormapIndex >= 0) {
							int index = 4*colormapIndex+18;
							int b = palette[index+0] & 0xFF;
							int g = palette[index+1] & 0xFF;
							int r = palette[index+2] & 0xFF;
							int a = palette[index+3] & 0xFF;
							color = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
						}
						pixels[width*i+(width-j-1)] = color;
					}
				}
			}
			else {
				// LowerRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int colormapIndex = (bytes[offset+width*i+j] & 0xFF) - colormapOrigin;
						int color = 0xFFFFFFFF;
						if(colormapIndex >= 0) {
							int index = 4*colormapIndex+18;
							int b = palette[index+0] & 0xFF;
							int g = palette[index+1] & 0xFF;
							int r = palette[index+2] & 0xFF;
							int a = palette[index+3] & 0xFF;
							color = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
						}
						pixels[width*(height-i-1)+(width-j-1)] = color;
					}
				}
			}
		}
		else {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int colormapIndex = (bytes[offset+width*i+j] & 0xFF) - colormapOrigin;
						int color = 0xFFFFFFFF;
						if(colormapIndex >= 0) {
							int index = 4*colormapIndex+18;
							int b = palette[index+0] & 0xFF;
							int g = palette[index+1] & 0xFF;
							int r = palette[index+2] & 0xFF;
							int a = palette[index+3] & 0xFF;
							color = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
						}
						pixels[width*i+j] = color;
					}
				}
			}
			else {
				// LowerLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int colormapIndex = (bytes[offset+width*i+j] & 0xFF) - colormapOrigin;
						int color = 0xFFFFFFFF;
						if(colormapIndex >= 0) {
							int index = 4*colormapIndex+18;
							int b = palette[index+0] & 0xFF;
							int g = palette[index+1] & 0xFF;
							int r = palette[index+2] & 0xFF;
							int a = palette[index+3] & 0xFF;
							color = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
						}
						pixels[width*(height-i-1)+j] = color;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	return pixels;
}
	
static int *createPixelsFromRGB(int width, int height, int depth, const unsigned char *bytes, int offset, int descriptor, const TGA_ORDER *order) {
	int *pixels = NULL;
	int rs = order->redShift;
	int gs = order->greenShift;
	int bs = order->blueShift;
	int as = order->alphaShift;
	switch(depth) {
	case 24:
		pixels = (int *)tgaMalloc(4*width*height);
		if((descriptor & RIGHT_ORIGIN) != 0) {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int index = offset+3*width*i+3*j;
						int b = bytes[index+0] & 0xFF;
						int g = bytes[index+1] & 0xFF;
						int r = bytes[index+2] & 0xFF;
						int a = 0xFF;
						pixels[width*i+(width-j-1)] = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
					}
				}
			}
			else {
				// LowerRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int index = offset+3*width*i+3*j;
						int b = bytes[index+0] & 0xFF;
						int g = bytes[index+1] & 0xFF;
						int r = bytes[index+2] & 0xFF;
						int a = 0xFF;
						pixels[width*(height-i-1)+(width-j-1)] = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
					}
				}
			}
		}
		else {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int index = offset+3*width*i+3*j;
						int b = bytes[index+0] & 0xFF;
						int g = bytes[index+1] & 0xFF;
						int r = bytes[index+2] & 0xFF;
						int a = 0xFF;
						pixels[width*i+j] = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
					}
				}
			}
			else {
				// LowerLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int index = offset+3*width*i+3*j;
						int b = bytes[index+0] & 0xFF;
						int g = bytes[index+1] & 0xFF;
						int r = bytes[index+2] & 0xFF;
						int a = 0xFF;
						pixels[width*(height-i-1)+j] = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
					}
				}
			}
		}
		break;
	case 32:
		pixels = (int *)tgaMalloc(4*width*height);
		if((descriptor & RIGHT_ORIGIN) != 0) {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int index = offset+4*width*i+4*j;
						int b = bytes[index+0] & 0xFF;
						int g = bytes[index+1] & 0xFF;
						int r = bytes[index+2] & 0xFF;
						int a = bytes[index+3] & 0xFF;
						pixels[width*i+(width-j-1)] = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
					}
				}
			}
			else {
				// LowerRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int index = offset+4*width*i+4*j;
						int b = bytes[index+0] & 0xFF;
						int g = bytes[index+1] & 0xFF;
						int r = bytes[index+2] & 0xFF;
						int a = bytes[index+3] & 0xFF;
						pixels[width*(height-i-1)+(width-j-1)] = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
					}
				}
			}
		}
		else {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int index = offset+4*width*i+4*j;
						int b = bytes[index+0] & 0xFF;
						int g = bytes[index+1] & 0xFF;
						int r = bytes[index+2] & 0xFF;
						int a = bytes[index+3] & 0xFF;
						pixels[width*i+j] = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
					}
				}
			}
			else {
				// LowerLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int index = offset+4*width*i+4*j;
						int b = bytes[index+0] & 0xFF;
						int g = bytes[index+1] & 0xFF;
						int r = bytes[index+2] & 0xFF;
						int a = bytes[index+3] & 0xFF;
						pixels[width*(height-i-1)+j] = (r<<rs) | (g<<gs) | (b<<bs) | (a<<as);
					}
				}
			}
		}
		break;
	default:
		break;
	}
	return pixels;
}
	
static int *createPixelsFromGrayscale(int width, int height, int depth, const unsigned char *bytes, int offset, int descriptor, const TGA_ORDER *order) {
	int *pixels = NULL;
	int rs = order->redShift;
	int gs = order->greenShift;
	int bs = order->blueShift;
	int as = order->alphaShift;
	switch(depth) {
	case 8:
		pixels = (int *)tgaMalloc(4*width*height);
		if((descriptor & RIGHT_ORIGIN) != 0) {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int e = bytes[offset+width*i+j] & 0xFF;
						int a = 0xFF;
						pixels[width*i+(width-j-1)] = (e<<rs) | (e<<gs) | (e<<bs) | (a<<as);
					}
				}
			}
			else {
				// LowerRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int e = bytes[offset+width*i+j] & 0xFF;
						int a = 0xFF;
						pixels[width*(height-i-1)+(width-j-1)] = (e<<rs) | (e<<gs) | (e<<bs) | (a<<as);
					}
				}
			}
		}
		else {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int e = bytes[offset+width*i+j] & 0xFF;
						int a = 0xFF;
						pixels[width*i+j] = (e<<rs) | (e<<gs) | (e<<bs) | (a<<as);
					}
				}
			}
			else {
				// LowerLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int e = bytes[offset+width*i+j] & 0xFF;
						int a = 0xFF;
						pixels[width*(height-i-1)+j] = (e<<rs) | (e<<gs) | (e<<bs) | (a<<as);
					}
				}
			}
		}
		break;
	case 16:
		pixels = (int *)tgaMalloc(4*width*height);
		if((descriptor & RIGHT_ORIGIN) != 0) {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int e = bytes[offset+2*width*i+2*j+0] & 0xFF;
						int a = bytes[offset+2*width*i+2*j+1] & 0xFF;
						pixels[width*i+(width-j-1)] = (e<<rs) | (e<<gs) | (e<<bs) | (a<<as);
					}
				}
			}
			else {
				// LowerRight
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int e = bytes[offset+2*width*i+2*j+0] & 0xFF;
						int a = bytes[offset+2*width*i+2*j+1] & 0xFF;
						pixels[width*(height-i-1)+(width-j-1)] = (e<<rs) | (e<<gs) | (e<<bs) | (a<<as);
					}
				}
			}
		}
		else {
			if((descriptor & UPPER_ORIGIN) != 0) {
				// UpperLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int e = bytes[offset+2*width*i+2*j+0] & 0xFF;
						int a = bytes[offset+2*width*i+2*j+1] & 0xFF;
						pixels[width*i+j] = (e<<rs) | (e<<gs) | (e<<bs) | (a<<as);
					}
				}
			}
			else {
				// LowerLeft
				int i, j;
				for(i=0; i<height; i++) {
					for(j=0; j<width; j++) {
						int e = bytes[offset+2*width*i+2*j+0] & 0xFF;
						int a = bytes[offset+2*width*i+2*j+1] & 0xFF;
						pixels[width*(height-i-1)+j] = (e<<rs) | (e<<gs) | (e<<bs) | (a<<as);
					}
				}
			}
		}
		break;
	default:
		break;
	}
	return pixels;
}

/* EOF */
