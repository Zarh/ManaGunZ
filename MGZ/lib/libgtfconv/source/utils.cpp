#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

namespace {
	bool sPrint = true;
}

namespace gtfconv{

float log2(float value){
	return log(value) / log(2.0f);
}

int32_t log2d(int32_t value)
{
	return (value > 0)?static_cast<int>(log2(static_cast<float>(value))): -1;
}

float power(float left, uint32_t right){
	float retf = 1.0f;
	for(uint32_t i = 0; i < right; ++i){
		retf *= left;
	}
	return retf;
}

uint32_t my_min(uint32_t a, uint32_t b){
	return (a < b ? a: b);
}

uint32_t my_max(uint32_t a, uint32_t b){
	return (a > b ? a: b);
}

void SET_PRINTF_MODE(bool bPrint)
{
	sPrint = bPrint;
}

void PRINTF(const char* format, ...)
{
	if(!sPrint) return;

	char buffer[1024];
	va_list marker;
	va_start(marker,format);
	vsprintf(buffer, format, marker);
	va_end(marker);
	
	fprintf(stdout, buffer);
}

bool is_pow2(uint32_t x)
{
	return ((x & (x - 1)) == 0);
}

uint8_t utilGetMipmapSize(uint16_t width, uint16_t height, uint16_t depth)
{
	return static_cast<uint8_t>(my_max(my_max(log2d(width), log2d(height)), log2d(depth)) + 1);
}

uint32_t utilGetAlign(uint32_t size, uint32_t alignment)
{
	return (size + alignment - 1) & ~(alignment - 1);
}

uint8_t utilCountBit(uint32_t bits)
{
	uint8_t ret = 0;

	for(int32_t i = 0; i < 32; ++i){
		if((bits >> i) & 0x01) ++ret;
	}
	return ret;
}

void memmove_with_invert_endian16(void *dest, const void *src, size_t size)
{
	const uint16_t *inptr16 = reinterpret_cast<const uint16_t*>(src);
	uint16_t *outptr16 = reinterpret_cast<uint16_t*>(dest);
	
	for(size_t i = 0; i < size / 2; ++i){
		*outptr16 = invert_endian16(*inptr16);

		++inptr16;
		++outptr16;
	}
	if(size % 2 != 0){
		memmove(outptr16, inptr16, size % 2);
	}
}

void memmove_with_invert_endian32(void *dest, const void *src, size_t size)
{
	const uint32_t *inptr32 = reinterpret_cast<const uint32_t*>(src);
	uint32_t *outptr32 = reinterpret_cast<uint32_t*>(dest);
	
	for(size_t i = 0; i < size / 4; ++i){
		*outptr32 = invert_endian32(*inptr32);

		++inptr32;
		++outptr32;
	}
	if(size % 4 != 0){
		memmove(outptr32, inptr32, size % 4);
	}
}

uint32_t utilToSwizzle(uint32_t x, uint32_t y, uint32_t z, uint32_t log2_width, uint32_t log2_height, uint32_t log2_depth)
{
	uint32_t offset = 0;

	uint32_t t = 0;
	while(log2_width | log2_height | log2_depth){
		if(log2_width){
			offset |= (x & 0x01) << t;
			x >>= 1;
			++t;
			--log2_width;
		}
		if(log2_height){
			offset |= (y & 0x01) << t;
			y >>= 1;
			++t;
			--log2_height;
		}
		if(log2_depth){
			offset |= (z & 0x01) << t;
			z >>= 1;
			++t;
			--log2_depth;
		}
	}

	return offset;
}

const char* utilRemap2Str(uint32_t remap)
{
	static char strRemap[5] = "ARGB";

	for(uint32_t i = 0; i < 4; ++i){
		uint32_t src = (remap >> (i * 2)) & 0x3;

		char c = 'N';

		if(src == CELL_GCM_TEXTURE_REMAP_FROM_A){
			c = 'A';
		}else if(src == CELL_GCM_TEXTURE_REMAP_FROM_R){
			c = 'R';
		}else if(src == CELL_GCM_TEXTURE_REMAP_FROM_G){
			c = 'G';
		}else if(src == CELL_GCM_TEXTURE_REMAP_FROM_B){
			c = 'B';
		}

		uint32_t opp = (remap >> (i * 2 + 8)) & 0x3; // default: CELL_GCM_TEXTURE_REMAP_REMAP
		if(opp == CELL_GCM_TEXTURE_REMAP_ZERO){
			c = '0';
		}else if(opp == CELL_GCM_TEXTURE_REMAP_ONE){
			c = '1';
		}

		strRemap[i] = c;
	}

	return strRemap;
}

} // namespace gtfconv
