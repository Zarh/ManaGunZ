/*
 * general.h - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#ifndef __RCOGENERAL_H__
#define __RCOGENERAL_H__

// #define DISABLE_RLZ

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define APPNAME "Rcomage"
#define APPNAME_VER "Rcomage v1.1.1"
#define APPXMLVER 1.10f
#define APPVER 1.11f

#define TRUE 	1
#define FALSE   0

#define ENDIAN_SWAP_16(x)		(((x) & 0xFF) << 8 | ((x) & 0xFF00) >> 8)
#define ENDIAN_SWAP_32(x)		(((x) & 0xFF) << 24 | ((x) & 0xFF00) << 8 | ((x) & 0xFF0000) >> 8 | ((x) & 0xFF000000) >> 24)
#define ENDIAN_SWAP(x)			(sizeof(x) == 2 ? ENDIAN_SWAP_16(x) : ENDIAN_SWAP_32(x))
#define ENDIAN_SWAP_HALF32(x)	(((x) & 0xFF) << 8 | ((x) & 0xFF00) >> 8 | ((x) & 0xFF0000) << 8 | ((x) & 0xFF000000) >> 8)

extern void print_load(char *format, ...);
extern uint8_t ERR;
extern uint8_t WAR;

#define info(...) 		{print_load(__VA_ARGS__);}
#define error(...) 		{ERR = TRUE ; print_load( __VA_ARGS__);}
#define warning(...)	{WAR = TRUE ; print_load(__VA_ARGS__);}

#define fileread(fp, buf, len) fread(buf, len, 1, fp)
#define filewrite(fp, buf, len) fwrite(buf, len, 1, fp)
#define openread(fn) ((fn)[0] == '-' && (fn)[1] == 0 ? stdin : fopen(fn, "rb"))
#define openwrite(fn) ((fn)[0] == '-' && (fn)[1] == 0 ? stdout : fopen(fn, "wb"))

// note, "n % 4" can also be written as "n & 3" (faster version as this does
// not invoke division)
// #define ALIGN_TO_4(n) (((n)&3) ? ((n) + (4-((n)&3))) : (n))
// #define ALIGN_TO_4(n) (((n)&3) ? (((n) >> 2 + 1) << 2) : (n))
// #define ALIGN_TO_4(n) (((n) + 3) & 0xFFFFFFFC)
// #define ALIGN_TO_4(n) (((n) + 3) & ((~0) ^ 3))
#define ALIGN_TO_4(n) (((n) + 3) & (~3))
// #define ALIGN_TO_4(n) (((n) + 3) >>2 <<2) // problem: upper 2 bits gets
// wiped too

#define UTF8_BOM  ((uint32_t) 0xBFBBEF)
#define UTF16_BOM ((uint16_t) 0xFEFF)
#define UTF32_BOM ((uint32_t) 0x0000FEFF)

#define PACK_STRUCT(nam, struc) typedef struct struc __attribute__ ((packed)) nam

uint32_t zlib_compress (void *src, uint32_t srcLen, void *dest,
    uint32_t destLen, int level, int strat);
int zlib_uncompress (void *dest, unsigned int destLen, const void *src,
    unsigned int srcLen);
uint32_t zlib_unpacked_size (void *src, uint32_t srcLen);
uint32_t rlz_compress (void *src, uint32_t srcLen, void *dest, uint32_t destLen,
    int mode);
uint8_t file_exists (char *fn);

uint32_t filesize (const char *fn);

uint32_t find_larger_prime (uint32_t in);
uint8_t is_prime (uint32_t in);

void get_temp_fname (char *out, const char *ext);

#define Z_USE_7Z 10

#ifdef WIN32
#define DIR_SEPARATOR '\\'
#else
#define DIR_SEPARATOR '/'
#endif

#endif
