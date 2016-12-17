#ifndef __GTFCONV_UTILS_H__
#define __GTFCONV_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

#include "ddsutil.h"
#include "gtfutil.h"

typedef long LONG;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef uint32_t BOOL;
typedef uint32_t UINT;

namespace gtfconv{

void SET_PRINTF_MODE(bool bPrint);
void PRINTF(const char* format, ...);

typedef struct
{
	uint32_t dds_offset;
	uint32_t dds_size;
	uint32_t gtf_linear_offset;
	uint32_t gtf_linear_size;
	uint32_t gtf_swizzle_offset;
	uint32_t gtf_swizzle_size;
	
	uint16_t width;
	uint16_t height;
	uint16_t depth;
	uint16_t color_depth;
	uint32_t pitch;

	uint32_t dds_pitch;
	uint16_t dds_depth;
	bool dds_expand;
}layout_t;

// utils.cpp
float log2(float value);
int32_t log2d(int32_t value);
float power(float left, uint32_t right);
uint32_t my_min(uint32_t a, uint32_t b);
uint32_t my_max(uint32_t a, uint32_t b);
uint8_t utilGetMipmapSize(uint16_t width, uint16_t height, uint16_t depth);
bool is_pow2(uint32_t x);
uint32_t utilGetAlign(uint32_t size, uint32_t alignment);
uint8_t utilCountBit(uint32_t bits);
bool utilReadFile(const char *fname, uint8_t **buffer, uint32_t *buf_size);
bool utilWriteFile(const char *fname, uint8_t **buffer, uint32_t *buf_size);
const char* utilRemap2Str(uint32_t remap);
uint32_t utilToSwizzle(uint32_t x, uint32_t y, uint32_t z, uint32_t log2_width, uint32_t log2_height, uint32_t log2_depth);

// endian util
inline bool is_little_endian(void)
{
	union {
		uint8_t c[4];
		uint32_t i;
	} endian_checker;

	endian_checker.i = 0;
	endian_checker.c[0] = 1;

	return endian_checker.i == 1;
}

inline bool is_big_endian(void)
{
	return !is_little_endian();
}

inline uint32_t invert_endian32(uint32_t v)
{
	return (v << 24) | ((v << 8) & 0x00FF0000) | ((v >> 8) & 0x0000FF00) | ((v >> 24) & 0x000000FF) ;
}

inline uint32_t invert_endian32_cross(uint32_t v)
{
	return ((v << 8) & 0xFF00FF00) | ((v >> 8) & 0x00FF00FF);
}

inline uint16_t invert_endian16(uint16_t v)
{
	return (v << 8) | ((v >> 8) & 0x00FF);
}

inline uint32_t to_big_endian32(uint32_t v)
{
	if(is_big_endian()) return v;

	return invert_endian32(v);
}

inline uint16_t to_big_endian16(uint16_t v)
{
	if(is_big_endian()) return v;

	return invert_endian16(v);
}

inline uint32_t to_little_endian32(uint32_t v)
{
	if(is_little_endian()) return v;

	return invert_endian32(v);
}

inline uint16_t to_little_endian16(uint16_t v)
{
	if(is_little_endian()) return v;

	return invert_endian16(v);
}


inline uint32_t from_big_endian32(uint32_t v)
{
	if(is_big_endian()) return v;

	return invert_endian32(v);
}

inline uint16_t from_big_endian16(uint16_t v)
{
	if(is_big_endian()) return v;

	return invert_endian16(v);
}

inline uint32_t from_little_endian32(uint32_t v)
{
	if(is_little_endian()) return v;

	return invert_endian32(v);
}

inline uint16_t from_little_endian16(uint16_t v)
{
	if(is_little_endian()) return v;

	return invert_endian16(v);
}

void memmove_with_invert_endian16(void *dest, const void *src, size_t size);
void memmove_with_invert_endian32(void *dest, const void *src, size_t size);

typedef struct{
	uint8_t *addr;
	uint32_t size;
	CellGcmTexture gcmt;
} GTF_CONV_T;

} // namespace gtfconv

#endif // __GTFCONV_UTILS_H__
