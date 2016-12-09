/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

#include "types.h"

/*! Verbose. */
extern BOOL _verbose;
#define _LOG_VERBOSE(...) _IF_VERBOSE(printf("[*] " __VA_ARGS__))
#define _IF_VERBOSE(code) \
	do \
	{ \
		if(_verbose == TRUE) \
		{ \
			code; \
		} \
	} while(0)

/*! Raw. */
extern BOOL _raw;
#define _PRINT_RAW(fp, ...) _IF_RAW(fprintf(fp, __VA_ARGS__))
#define _IF_RAW(code) \
	do \
	{ \
		if(_raw == TRUE) \
		{ \
			code; \
		} \
	} while(0)

/*! ID to name entry. */
typedef struct _id_to_name
{
	unsigned long long int id;
	const char *name;
} id_to_name_t;

/*! Utility functions. */
void _hexdump(FILE *fp, const char *name, unsigned int offset, unsigned char *buf, int len, BOOL print_addr);
void _print_align(FILE *fp, const char *str, int align, int len);
unsigned char *_read_buffer(const char *file, unsigned int *length);
int _write_buffer(const char *file, unsigned char *buffer, unsigned int length);
const char *_get_name(id_to_name_t *tab, unsigned long long int id);
unsigned long long int _get_id(id_to_name_t *tab, const char *name);
void _zlib_inflate(unsigned char *in, unsigned long long int len_in, unsigned char *out, unsigned long long int len_out);
void _zlib_deflate(unsigned char *in, unsigned long long int len_in, unsigned char *out, unsigned long long int len_out);
unsigned char _get_rand_byte();
void _fill_rand_bytes(unsigned char *dst, unsigned int len);
void _memcpy_inv(unsigned char *dst, unsigned char *src, unsigned int len);
void *_memdup(void *ptr, unsigned int size);
unsigned long long int _x_to_u64(const char *hex);
unsigned char *_x_to_u8_buffer(const char *hex);

#endif
