// Copyright 2010            Sven Peter <svenpeter@gmail.com>
// Copyright 2007,2008,2010  Segher Boessenkool  <segher@kernel.crashing.org>
// Licensed under the terms of the GNU GPL, version 2
// http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt

#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <zlib.h>
#include <dirent.h>
#include <assert.h>
#include <ctype.h>

#include "tools.h"
#include "pkg_aes.h"
#include "sha.h"
#include <sys/file.h>

void print_hash(u8 *ptr, u32 len)
{
	while(len--)
		printf(" %02x", *ptr++);
}


void memcpy_to_file(const char *fname, u8 *ptr, u64 size)
{
	FILE *fp;

	fp = fopen(fname, "wb");
	fwrite(ptr, size, 1, fp);
	fclose(fp);
}

static void fail(const char *a, ...)
{
	char msg[1024];
	va_list va;

	va_start(va, a);
	vsnprintf(msg, sizeof msg, a, va);
	fprintf(stderr, "%s\n", msg);
	perror("perror");

	exit(1);
}


#ifdef WIN32
void get_rand(u8 *bfr, u32 size)
{
	HCRYPTPROV hProv;

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		fail("unable to open random");

	if (!CryptGenRandom(hProv, size, bfr))
		fail("unable to read random numbers");

	CryptReleaseContext(hProv, 0);
}
#else
void get_rand(u8 *bfr, u32 size)
{
	FILE *fp;

	fp = fopen("/dev/urandom", "r");
	if (fp == NULL)
		fail("unable to open random");

	if (fread(bfr, size, 1, fp) != 1)
		fail("unable to read random numbers");

	fclose(fp);
}
#endif


//
// crypto
//
void aes256cbc(u8 *key, u8 *iv_in, u8 *in, u64 len, u8 *out)
{
	AES_KEY k;
	u32 i;
	u8 tmp[16];
	u8 iv[16];

	memcpy(iv, iv_in, 16);
	memset(&k, 0, sizeof k);
	AES_set_decrypt_key(key, 256, &k);

	while (len > 0) {
		memcpy(tmp, in, 16);
		AES_decrypt(in, out, &k);

		for (i = 0; i < 16; i++)
			out[i] ^= iv[i];

		memcpy(iv, tmp, 16);

		out += 16;
		in += 16;
		len -= 16;

	}
}


void aes256cbc_enc(u8 *key, u8 *iv, u8 *in, u64 len, u8 *out)
{
	AES_KEY k;
	u32 i;
	u8 tmp[16];

	memcpy(tmp, iv, 16);
	memset(&k, 0, sizeof k);
	AES_set_encrypt_key(key, 256, &k);

	while (len > 0) {
		for (i = 0; i < 16; i++)
			tmp[i] ^= *in++;

		AES_encrypt(tmp, out, &k);
		memcpy(tmp, out, 16);

		out += 16;
		len -= 16;
	}
}

void aes128cfb_enc(u8 *key, u8 *iv_in, u8 *in, u64 len, u8 *out)
{
	AES_KEY k;
	u32 i;
	u8 tmp[16];
	u8 iv[16];

	memcpy(iv, iv_in, 16);
	memset(&k, 0, sizeof k);
	AES_set_encrypt_key(key, 128, &k);

	while (len > 0) {
		memcpy(tmp, in, 16);
		AES_encrypt(iv, out, &k);

		for (i = 0; i < 16; i++)
			out[i] ^= tmp[i];

		memcpy(iv, out, 16);

                if (len >= 16) {
                  out += 16;
                  in += 16;
                  len -= 16;
                } else {
                  len = 0;
                }

	}
}

void aes128cfb(u8 *key, u8 *iv_in, u8 *in, u64 len, u8 *out)
{
	AES_KEY k;
	u32 i;
	u8 tmp[16];
	u8 iv[16];

	memcpy(iv, iv_in, 16);
	memset(&k, 0, sizeof k);
	AES_set_decrypt_key(key, 128, &k);

	while (len > 0) {
		memcpy(tmp, in, 16);
		AES_decrypt(iv, out, &k);

		for (i = 0; i < 16; i++)
			out[i] ^= tmp[i];

		memcpy(iv, tmp, 16);

                if (len >= 16) {
                  out += 16;
                  in += 16;
                  len -= 16;
                } else {
                  len = 0;
                }

	}
}

void aes128cbc(u8 *key, u8 *iv_in, u8 *in, u64 len, u8 *out)
{
	AES_KEY k;
	u32 i;
	u8 tmp[16];
	u8 iv[16];

	memcpy(iv, iv_in, 16);
	memset(&k, 0, sizeof k);
	AES_set_decrypt_key(key, 128, &k);

	while (len > 0) {
                memcpy(tmp, in, len > 16 ? 16 : len);
                if (len < 16) {
                  u8 tmp_out[16];

                  memset(&k, 0, sizeof k);
                  AES_set_encrypt_key(key, 128, &k);
                  AES_encrypt(iv, tmp_out, &k);
                  for (i = 0; i < len; i++)
                    out[i] = in[i] ^ tmp_out[i];
                  break;
                } else {
                  AES_decrypt(in, out, &k);
                }

		for (i = 0; i < 16; i++)
			out[i] ^= iv[i];

		memcpy(iv, tmp, 16);

		out += 16;
		in += 16;
		len -= 16;

	}
}
void aes128cbc_enc(u8 *key, u8 *iv, u8 *in, u64 len, u8 *out)
{
	AES_KEY k;
	u32 i;
	u8 tmp[16];

	memcpy(tmp, iv, 16);
	memset(&k, 0, sizeof k);
	AES_set_encrypt_key(key, 128, &k);

	while (len > 0) {
                if (len < 16) {
                  u8 tmp_out[16];

                  AES_encrypt(tmp, tmp_out, &k);
                  for (i = 0; i < len; i++)
                    out[i] ^= tmp_out[i];
                  break;
                } else {
                  for (i = 0; i < 16; i++)
			tmp[i] ^= *in++;
                  AES_encrypt(tmp, out, &k);
                }
		memcpy(tmp, out, 16);

		out += 16;
		len -= 16;
	}
}

void aes128ctr(u8 *key, u8 *iv, u8 *in, u64 len, u8 *out)
{
	AES_KEY k;
	u32 i;
	u8 ctr[16];
	u64 tmp;

	memset(ctr, 0, 16);
	memset(&k, 0, sizeof k);

	AES_set_encrypt_key(key, 128, &k);

	for (i = 0; i < len; i++) {
		if ((i & 0xf) == 0) {
			AES_encrypt(iv, ctr, &k);

			// increase nonce
			tmp = be64(iv + 8) + 1;
			wbe64(iv + 8, tmp);
			if (tmp == 0)
				wbe64(iv, be64(iv) + 1);
		}
		*out++ = *in++ ^ ctr[i & 0x0f];
	}
}

void aes128(u8 *key, const u8 *in, u8 *out) {
    AES_KEY k;

    assert(!AES_set_decrypt_key(key, 128, &k));
    AES_decrypt(in, out, &k);
}

void aes128_enc(u8 *key, const u8 *in, u8 *out) {
    AES_KEY k;

    assert(!AES_set_encrypt_key(key, 128, &k));
    AES_encrypt(in, out, &k);
}



// FIXME: use a non-broken sha1.c *sigh*
static void sha1_fixup(struct SHA1Context *ctx, u8 *digest)
{
	u32 i;

	for(i = 0; i < 5; i++) {
		*digest++ = ctx->Message_Digest[i] >> 24 & 0xff;
		*digest++ = ctx->Message_Digest[i] >> 16 & 0xff;
		*digest++ = ctx->Message_Digest[i] >> 8 & 0xff;
		*digest++ = ctx->Message_Digest[i] & 0xff;
	}
}


void pkg_sha1(u8 *data, u32 len, u8 *digest)
{
	struct SHA1Context ctx;

	SHA1Reset(&ctx);
	SHA1Input(&ctx, data, len);
	SHA1Result(&ctx);

	sha1_fixup(&ctx, digest);
}

/*
void pkg_sha1_hmac(u8 *key, u8 *data, u32 len, u8 *digest)
{
	struct SHA1Context ctx;
	u32 i;
	u8 ipad[0x40];
	u8 tmp[0x40 + 0x14]; // opad + hash(ipad + message)

	SHA1Reset(&ctx);

	for (i = 0; i < sizeof ipad; i++) {
		tmp[i] = key[i] ^ 0x5c; // opad
		ipad[i] = key[i] ^ 0x36;
	}

	SHA1Input(&ctx, ipad, sizeof ipad);
	SHA1Input(&ctx, data, len);
	SHA1Result(&ctx);

	sha1_fixup(&ctx, tmp + 0x40);

	pkg_sha1(tmp, sizeof tmp, digest);

}
*/

void HMACReset(HMACContext *ctx, u8 *key)
{
	u32 i;
	u8 ipad[0x40];

	SHA1Reset(&ctx->sha1);

	for (i = 0; i < sizeof ipad; i++) {
		ctx->tmp[i] = key[i] ^ 0x5c; // opad
		ipad[i] = key[i] ^ 0x36;
	}

	SHA1Input(&ctx->sha1, ipad, sizeof ipad);
}

void HMACInput(HMACContext *ctx, u8* data, u32 len)
{
	SHA1Input(&ctx->sha1, data, len);
}

void HMACResult(HMACContext *ctx, u8 *digest)
{
	SHA1Result(&ctx->sha1);

	sha1_fixup(&ctx->sha1, ctx->tmp + 0x40);

	pkg_sha1(ctx->tmp, sizeof ctx->tmp, digest);
}

int mkdir_recursive(const char *path)
{
  int len = strlen (path);
  char *temp = malloc (len + 1);
  int i;
  int ret = 0;
  struct stat stat_buf;

  memcpy (temp, path, len);

  if (temp[0] == '/')
    i = 1;
  else
    i = 0;
  while (i < len) {
    for (; i < len && temp[i] != '/'; i++);
    temp[i] = 0;
    if (stat (temp, &stat_buf) != 0) {
      ret = mkdir(temp, 0777);;
      if (ret != 0) {
		goto end;
	  }
    }
    if (i < len)
      temp[i] = '/';
    i++;
  }
 end:
  free (temp);
  return ret;
}

static int hex_to_int (char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  else if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  else if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  else
    return -1;
}

int parse_hex (const char *str, u8 *buffer, u32 size)
{
  u32 len = strlen (str);
  u32 i;

  if (len > (size * 2))
    return -1;
  for (i = 0; i < size; i++) {
    int left = hex_to_int (str[i*2]);
    int right = hex_to_int (str[i*2 + 1]);

    if (left == -1 || right == -1)
      break;
    buffer[i] = left << 4 | right;
  }

  return i;
}
