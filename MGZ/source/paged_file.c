/*
 * Copyright (C) Youness Alaoui (KaKaRoTo)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#include "tools.h"
#include "types.h"
#include "paged_file.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ntfs.h"

#define SUCCESS 	1
#define FAILED	 	0
#define YES			1
#define NO		 	0

extern int64_t prog_bar2_value;
extern u8 cancel;
extern void print_load(char *format, ...);

static int paged_file_init (PagedFile *f, FILE *fd, int reader)
{
  f->fd = fd;
  f->ptr = malloc (PAGED_FILE_PAGE_SIZE);
  f->size = 0;
  f->pos = 0;
  f->page_pos = 0;
  f->reader = reader;
  f->crypt = PAGED_FILE_CRYPT_NONE;
  f->hash = FAILED;

  return SUCCESS;
}

int
paged_file_open (PagedFile *f, const char *path, int reader)
{
  FILE *fd = NULL;
  
  fd = fopen (path, reader? "rb" : "wb");
  if (fd == NULL) {
    return FAILED;
  }

  return paged_file_init (f, fd, reader);
}

static void
paged_file_hash_internal (PagedFile *f)
{
  if (f->hash && (f->size - f->pos) > 0)
    HMACInput (&f->hmac_ctx, f->ptr + f->pos, f->size - f->pos);
}

static void
paged_file_crypt_internal_encrypt (PagedFile *f)
{
  if (f->size > 0) {
    if (f->crypt == PAGED_FILE_CRYPT_AES_128_CBC) {
      aes128cbc_enc (f->key, f->iv, f->ptr, f->size, f->ptr);
      if (f->size >= 0x10)
        memcpy (f->iv, f->ptr + f->size - 0x10, 0x10);
    } else if (f->crypt == PAGED_FILE_CRYPT_AES_256_CBC) {
      aes256cbc_enc (f->key, f->iv, f->ptr, f->size, f->ptr);
      if (f->size >= 0x10)
        memcpy (f->iv, f->ptr + f->size - 0x10, 0x10);
    } else if (f->crypt == PAGED_FILE_CRYPT_AES_128_CTR) {
      aes128ctr (f->key, f->iv, f->ptr, f->size, f->ptr);
    } else if (f->crypt == PAGED_FILE_CRYPT_CUSTOM) {
      f->crypt_cb (f, PAGED_FILE_CRYPT_ENCRYPT, f->ptr, f->size,
          f->crypt_cb_data);
    }
  }
}

static void
paged_file_crypt_internal_decrypt (PagedFile *f)
{
  if (f->size - f->pos > 0) {
    if (f->crypt == PAGED_FILE_CRYPT_AES_128_CBC) {
      u8 iv[0x10];

      memcpy (iv, f->iv, 0x10);
      if ((f->size - f->pos) >= 0x10)
        memcpy (f->iv, f->ptr + f->size - 0x10, 0x10);
      aes128cbc (f->key, iv, f->ptr + f->pos, f->size - f->pos,
          f->ptr + f->pos);
    } else if (f->crypt == PAGED_FILE_CRYPT_AES_256_CBC) {
      u8 iv[0x10];

      memcpy (iv, f->iv, 0x10);
      if ((f->size - f->pos) >= 0x10)
        memcpy (f->iv, f->ptr + f->size - 0x10, 0x10);
      aes256cbc (f->key, iv, f->ptr + f->pos, f->size - f->pos, f->ptr + f->pos);
    } else if (f->crypt == PAGED_FILE_CRYPT_AES_128_CTR) {
      aes128ctr (f->key, f->iv, f->ptr + f->pos, f->size - f->pos, f->ptr + f->pos);
    } else if (f->crypt == PAGED_FILE_CRYPT_CUSTOM) {
      f->crypt_cb (f, PAGED_FILE_CRYPT_DECRYPT, f->ptr + f->pos,
          f->size - f->pos, f->crypt_cb_data);
    }
  }
}

static void
paged_file_crypt_internal (PagedFile *f)
{
  if (f->reader) {
    paged_file_crypt_internal_decrypt (f);
  } else {
    paged_file_crypt_internal_encrypt (f);
  }
}

int
paged_file_crypt (PagedFile *f, u8 *key, u8 *iv, PagedFileCryptType type,
    PagedFileCryptCB callback, void *user_data)
{
  if (f->crypt != PAGED_FILE_CRYPT_NONE)
    return FAILED;

  memcpy (f->key, key, 0x10);
  memcpy (f->iv, iv, 0x10);
  f->crypt = type;
  f->crypt_cb = callback;
  f->crypt_cb_data = user_data;

  paged_file_crypt_internal (f);

  return SUCCESS;
}

/*
int
paged_file_hash (PagedFile *f, u8 *key)
{
  if (f->hash)
    return FAILED;

  HMACReset (&f->hmac_ctx, key);
  f->hash = TRUE;
  paged_file_hash_internal (f);

  return TRUE;
}
*/

static int
paged_file_read_new_page (PagedFile *f)
{
  if (!f->reader)
    return -1;

  f->page_pos += f->size;
  f->size = fread (f->ptr, 1, 0x1000, f->fd);
  f->pos = 0;

  if (f->size == 0)
    return 0;

  paged_file_hash_internal (f);
  paged_file_crypt_internal (f);

  return f->size;
}

int
paged_file_read (PagedFile *f, void *buffer, u32 len)
{
  int ret;
  int pos = 0;
  u32 size = len;

  if (!f->reader)
    return -1;

  while (len > 0) {
    size = len;
    if (size > (f->size - f->pos))
      size = f->size - f->pos;
    if (size == 0) {
      ret = paged_file_read_new_page (f);
      if (ret == 0)
        break;
      continue;
    }
    memcpy ((u8*)buffer + pos, f->ptr + f->pos, size);
    f->pos += size;
    pos += size;
    len -= size;
  }

  return pos;
}

int
paged_file_flush (PagedFile *f)
{
  int written;

  if (f->reader)
    return -1;

  if (f->size == 0)
    return 0;

  paged_file_crypt_internal (f);
  f->pos = 0;
  paged_file_hash_internal (f);

  written = fwrite (f->ptr, 1, f->size, f->fd);
  f->page_pos += f->size;
  f->size = 0;

  return written;
}


int
paged_file_write (PagedFile *f, void *buffer, u32 len)
{
  int ret;
  int pos = 0;
  u32 size = len;

  if (f->reader)
    return -1;

  while (len > 0) {
    size = len;
    if (size > (PAGED_FILE_PAGE_SIZE - f->pos))
      size = PAGED_FILE_PAGE_SIZE - f->pos;
    if (size == 0) {
      ret = paged_file_flush (f);
      if (ret != PAGED_FILE_PAGE_SIZE)
        break;
      continue;
    }
    memcpy (f->ptr + f->pos, (u8 *)buffer + pos, size);
    f->pos += size;
    if (f->pos > f->size)
      f->size = f->pos;
    pos += size;
    len -= size;
  }

  return pos;
}

int
paged_file_seek (PagedFile *f, u64 offset)
{
  u32 pos;

  if (!f->reader)
    return -1;

  pos = offset % 0x10;
  offset &= ~0xF;

  if (offset + pos > f->page_pos && offset + pos < f->page_pos + f->size) {
    f->pos = offset + pos - f->page_pos;
    return f->page_pos + f->pos;
  }

  if (f->crypt != PAGED_FILE_CRYPT_NONE) {
    /* TODO: support other crypto */
    if (f->crypt == PAGED_FILE_CRYPT_AES_128_CBC ||
        f->crypt == PAGED_FILE_CRYPT_AES_256_CBC) {
      if (offset >= 0x10) {
        fseek (f->fd, offset - 0x10, SEEK_SET);
        if (fread (f->iv, 1, 0x10, f->fd) != 1)
          return -1;
      }
    } else if (f->crypt == PAGED_FILE_CRYPT_AES_128_CTR) {
      s64 seek_diff = (signed) (offset - (f->page_pos + f->size)) / 0x10;
      u64 tmp = be64(f->iv + 8) + seek_diff;

      if (seek_diff > 0 && tmp < be64 (f->iv + 8))
        wbe64(f->iv, be64(f->iv) + 1);
      else if (seek_diff < 0 && tmp > be64 (f->iv + 8))
        wbe64(f->iv, be64(f->iv) - 1);
      wbe64(f->iv + 8, tmp);
    } else if (f->crypt == PAGED_FILE_CRYPT_CUSTOM) {
      if (!f->crypt_cb (f, PAGED_FILE_CRYPT_SEEK,
              NULL, offset, f->crypt_cb_data))
        return -1;
    }
  }
  fseek (f->fd, offset, SEEK_SET);
  f->size = 0;
  f->page_pos = ftell (f->fd);
  paged_file_read_new_page (f);
  f->pos = pos;

  return f->page_pos;
}

int
paged_file_splice (PagedFile *f, PagedFile *from, int len)
{
  char buffer[1024];
  int total = 0;
  int size;
  int read;

  prog_bar2_value = 0;
  while (len == -1 || total < len) {
    size = len - total;
    if (len == -1 || (u32) size > sizeof(buffer))
      size = sizeof(buffer);

    read = paged_file_read (from, buffer, size);
    if (read == 0)
      break;
    paged_file_write (f, buffer, read);
    total += read;
	
	if(cancel==YES) break;
	prog_bar2_value = (total*100)/len;
  }

  return total;
}

void
paged_file_free (PagedFile *f)
{
  if (f->ptr)
    free (f->ptr);
  f->ptr = NULL;
  f->size = 0;
}

void
paged_file_close (PagedFile *f)
{
  if (!f->reader)
    paged_file_flush (f);

  if (f->fd)
    fclose (f->fd);
  f->fd = NULL;
  paged_file_free (f);

  if (f->hash)
    HMACResult (&f->hmac_ctx, f->digest);
}

int
paged_file_getline (PagedFile *f, char **line, int *line_len)
{
  int pos = 0;

  if (!f->reader)
    return -1;

  if (*line == NULL) {
    *line_len = 1024;
    *line = malloc (*line_len);
  }
  while (TRUE) {
    if (pos > (*line_len - 1)) {
      *line_len += 1024;
      *line = realloc (*line, *line_len);
    }
    if (paged_file_read (f, (*line) + pos, 1) != 1) {
      (*line)[pos] = 0;
      break;
    } else if ((*line)[pos] == '\n') {
      (*line)[pos + 1] = 0;
      break;
    }
    pos++;
  }

  return pos == 0 ? -1 : pos;
}
