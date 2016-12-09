/*
 * general.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#include <string.h>		// memset()
#include <stdio.h>
#include <math.h>		// sqrt
#include <stdlib.h>		// free()

#include <zlib.h>
#include "general.h"
#include "rlzpack.h"
#include "7z/7z.h"
#include "../tools.h"

uint32_t
zlib_compress (void *src, uint32_t srcLen, void *dest, uint32_t destLen,
    int level, int strat)
{
  if (strat == Z_USE_7Z) {
    // compress with 7z
    if (destLen < 6)
      return 0;

    unsigned int outSize = destLen - 6;	// = 2 for sig + 4 for checksum
    unsigned char *destPtr = (unsigned char *) dest;

    *(uint16_t *) destPtr = 0xDA78;	// zlib signature
    destPtr += 2;

    int passes = 1, fastbytes = 64;

    switch (level) {
      case 1:
	passes = 1;
	fastbytes = 64;
	break;
      case 2:
	passes = 3;
	fastbytes = 128;
	break;
      case 3:
	passes = 5;
	fastbytes = 255;
	break;
      case 4:			// overkill
	passes = 15;		// max is 255
	fastbytes = 255;	// seems to work better than 256 or 257
	break;
    }
    // limits: passes [1-255], fastbytes [3-257(kMatchMaxLen)]
    if (!compress_deflate_7z ((unsigned char *) src, srcLen, destPtr, &outSize,
	    passes, fastbytes))
      return 0;

    if (outSize + 6 > destLen)
      return 0;

    uLong adler = adler32 (adler32 (0L, Z_NULL, 0), (Bytef *) src, srcLen);

    *(uint32_t *) (destPtr + outSize) = ENDIAN_SWAP_32 (adler);

    return outSize + 6;
  } else {
    // compress with zlib
    z_stream s;

    memset (&s, 0, sizeof (s));
    if (deflateInit2 (&s, level, Z_DEFLATED, 15, 8, strat))
      return 0;

    s.next_in = (Bytef *) src;
    s.avail_in = srcLen;
    s.next_out = (Bytef *) dest;
    s.avail_out = destLen;

    if (deflate (&s, Z_FINISH) < 0)
      return 0;

    deflateEnd (&s);
    return s.total_out;
  }
}

int
zlib_uncompress (void *dest, unsigned int destLen, const void *src,
    unsigned int srcLen)
{
  z_stream zs;
  int ret;

  zs.next_in = (Bytef *) src;
  zs.avail_in = srcLen;
  zs.next_out = (Bytef *) dest;
  zs.avail_out = destLen;
  zs.zalloc = Z_NULL;
  zs.zfree = Z_NULL;
  zs.opaque = 0;

  ret = inflateInit (&zs);
  if (ret == Z_OK) {
    ret = inflate (&zs, Z_FINISH);
    if (ret == Z_STREAM_END)
      ret = Z_OK;
    if (inflateEnd (&zs) == Z_DATA_ERROR)
      ret = Z_DATA_ERROR;
  }
  if (ret == Z_BUF_ERROR)
    ret = Z_DATA_ERROR;
  return ret;
}

uint32_t
zlib_unpacked_size (void *src, uint32_t srcLen)
{
  z_stream s;

  memset (&s, 0, sizeof (s));

#define ZLIB_TESTUNPACK_BUFSIZE 65536
  char buffer[ZLIB_TESTUNPACK_BUFSIZE];

  s.next_in = (Bytef *) src;
  s.avail_in = srcLen;
  s.next_out = (Bytef *) buffer;
  s.avail_out = ZLIB_TESTUNPACK_BUFSIZE;

  if (inflateInit (&s) != Z_OK)
    return 0xFFFFFFFF;

  uint32_t size = 0;
  int ret;

  while ((ret = inflate (&s, Z_NO_FLUSH)) == Z_OK) {
    size += ZLIB_TESTUNPACK_BUFSIZE - s.avail_out;
    if (!s.avail_in)
      break;
    s.next_out = (Bytef *) buffer;
    s.avail_out = ZLIB_TESTUNPACK_BUFSIZE;
  }

  if (ret == Z_STREAM_END) {
    size += ZLIB_TESTUNPACK_BUFSIZE - s.avail_out;
  }

  inflateEnd (&s);
  if (s.avail_in || (ret != Z_STREAM_END && ret != Z_OK))
    return 0xFFFFFFFF;

  return size;
}

uint32_t
rlz_compress (void *src, uint32_t srcLen, void *dest, uint32_t destLen,
    int mode)
{
  if (mode == -1) {
    // theme creator compatible mode
    // we'll be just as bad as the theme creator and run _4_ compression passes
    //
    // >_>

    int size5, size6, size7;

    size5 = rlzcompress (dest, srcLen, src, 5);
    size6 = rlzcompress (dest, srcLen, src, 6);
    size7 = rlzcompress (dest, srcLen, src, 7);

    if ((size5 == -1) && (size6 == -1) && (size7 == -1))
      return 0;			// all failed, lol

    if (size7 != -1 && (size7 < size6 || size6 != -1)
	&& (size7 < size5 || size5 != -1))
      return size7;		// okay, we're _slightly_ more optimised than
    // the theme creator :P
    if (size6 != -1 && (size6 < size5 || size5 != -1))
      return rlzcompress (dest, srcLen, src, 6);
    if (size5 != -1)
      return rlzcompress (dest, srcLen, src, 5);

    return 0;			// should never occur

  } else {
    int size = rlzcompress (dest, srcLen, src, mode);

    if (size == -1)
      return 0;
    else
      return size;
  }
}

uint8_t
file_exists (char *fn)
{
  // our deetection routine is weird - just tries to open the file
  FILE *fp;

  if ((fp = fopen (fn, "r"))) {
    // file exists
    fclose (fp);
    return TRUE;
  }
  return FALSE;
}

uint32_t
filesize (const char *fn)
{
  FILE *fp = fopen (fn, "rb");

  if (!fp)
    return 0;
  fseek (fp, 0, SEEK_END);
  uint32_t f = ftell (fp);

  fclose (fp);

  return f;
}

// finds the smallest prime number which is >= in
uint32_t
find_larger_prime (uint32_t in)
{
  if (in <= 2)
    return 2;

  if (!(in & 1))
    in++;			// in is an odd number

  while (TRUE) {
    if (is_prime (in))
      return in;
    in += 2;
  }
}

uint8_t
is_prime (uint32_t in)
{
  if (in < 12) {		// need this buffer as "lim" (below) may
    // underflow
    return (in <= 3 || in == 5 || in == 7 || in == 11);
  }
  // filter out half the results by checking if the number is even
  if ((in ^ 1) & 1)
    return FALSE;

  uint32_t i;
  uint32_t lim = (uint32_t) floor (sqrt ((float) in));

  for (i = 3; i <= lim; i += 2)
    if (in % i == 0)
      return FALSE;

  return TRUE;
}

void
get_temp_fname (char *out, const char *ext)
{
  char *tmp = tempnam (NULL, "rcomage_tmp");

  if (tmp) {
    strcpy (out, tmp);
    free (tmp);
  } else
    strcpy (out, "rcomage_tmp");
  if (ext)
    sprintf (out + strlen (out), ".%s", ext);
}
