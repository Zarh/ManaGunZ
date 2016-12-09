// Copyright 2010            Sven Peter <svenpeter@gmail.com>
// Copyright 2007,2008,2010  Segher Boessenkool  <segher@kernel.crashing.org>
// Licensed under the terms of the GNU GPL, version 2
// http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt

#ifndef TOOLS_H__
#define TOOLS_H__ 1
#include <stdint.h>

#include "types.h"
#include "sha.h"

#define die(format, ...) {                              \
    fprintf (stderr, format, ## __VA_ARGS__);           \
    exit (-1);                                          \
  }


typedef struct {
  struct SHA1Context sha1;
  u8 tmp[0x40 + 0x14]; // opad + hash(ipad + message)
} HMACContext;

void HMACReset(HMACContext *ctx, u8 *key);
void HMACInput(HMACContext *ctx, u8* data, u32 len);
void HMACResult(HMACContext *ctx, u8 *digest);

void print_hash(u8 *ptr, u32 len);

void *mmap_file(const char *path);
void memcpy_to_file(const char *fname, u8 *ptr, u64 size);
void get_rand(u8 *bfr, u32 size);

void aes256cbc(u8 *key, u8 *iv, u8 *in, u64 len, u8 *out);
void aes256cbc_enc(u8 *key, u8 *iv, u8 *in, u64 len, u8 *out);
void aes128ctr(u8 *key, u8 *iv, u8 *in, u64 len, u8 *out);
void aes128cfb_enc(u8 *key, u8 *iv, u8 *in, u64 len, u8 *out);
void aes128cfb(u8 *key, u8 *iv_in, u8 *in, u64 len, u8 *out);
void aes128cbc(u8 *key, u8 *iv_in, u8 *in, u64 len, u8 *out);
void aes128cbc_enc(u8 *key, u8 *iv, u8 *in, u64 len, u8 *out);
void aes128(u8 *key, const u8 *in, u8 *out);
void aes128_enc(u8 *key, const u8 *in, u8 *out);

void pkg_sha1(u8 *data, u32 len, u8 *digest);
//void pkg_sha1_hmac(u8 *key, u8 *data, u32 len, u8 *digest);

int mkdir_recursive (const char *path);
int parse_hex (const char *str, u8 *buffer, u32 size);

#define		round_up(x,n)	(-(-(x) & -(n)))

#define		array_size(x)	(sizeof(x) / sizeof(*(x)))
#endif
