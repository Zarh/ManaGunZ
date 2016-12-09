/*
 * Copyright (C) Youness Alaoui (KaKaRoTo)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#ifndef __PAGED_FILE_H__
#define __PAGED_FILE_H__

#include "tools.h"
#include "types.h"

#include <stdio.h>

#define PAGED_FILE_PAGE_SIZE 0x10000

typedef enum {
  PAGED_FILE_CRYPT_NONE = 0,
  PAGED_FILE_CRYPT_AES_128_CBC,
  PAGED_FILE_CRYPT_AES_256_CBC,
  PAGED_FILE_CRYPT_AES_128_CTR,
  PAGED_FILE_CRYPT_CUSTOM,
} PagedFileCryptType;

typedef enum {
  PAGED_FILE_CRYPT_ENCRYPT,
  PAGED_FILE_CRYPT_DECRYPT,
  PAGED_FILE_CRYPT_SEEK,
} PagedFileCryptOperation;

typedef struct _PagedFile PagedFile;

typedef int (* PagedFileCryptCB) (PagedFile *f, PagedFileCryptOperation operation,
    u8 *ptr, u32 len, void *user_data);

struct _PagedFile {
  FILE *fd;
  int reader;
  u8 *ptr;
  u32 size;
  u32 pos;
  u64 page_pos;
  HMACContext hmac_ctx;
  u8 key[0x10];
  u8 iv[0x10];
  u8 digest[0x14];
  int crypt;
  PagedFileCryptCB crypt_cb;
  void *crypt_cb_data;
  int hash;
};


int paged_file_open (PagedFile *f, const char *path, int reader);
int paged_file_crypt (PagedFile *f, u8 *key, u8 *iv, PagedFileCryptType type,
    PagedFileCryptCB callback, void *user_data);
int paged_file_hash (PagedFile *f, u8 *key);
int paged_file_read (PagedFile *f, void *buffer, u32 len);
int paged_file_getline (PagedFile *f, char **line, int *line_len);
int paged_file_seek (PagedFile *f, u64 offset);
int paged_file_write (PagedFile *f, void *buffer, u32 len);
int paged_file_splice (PagedFile *f, PagedFile *from, int len);
int paged_file_flush (PagedFile *f);
void paged_file_free (PagedFile *f);
void paged_file_close (PagedFile *f);

#endif /* __PAGED_FILE_H__ */
