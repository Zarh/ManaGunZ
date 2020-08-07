/*
 * This file is in the public domain.  Use it as you see fit.
 */

/*
 * "untar" is an extremely simple tar extractor:
 *  * A single C source file, so it should be easy to compile
 *    and run on any system with a C compiler.
 *  * Extremely portable standard C.  The only non-ANSI function
 *    used is mkdir().
 *  * Reads basic ustar tar archives.
 *  * Does not require libarchive or any other special library.
 *
 * To compile: cc -o untar untar.c
 *
 * Usage:  untar <archive>
 *
 * In particular, this program should be sufficient to extract the
 * distribution for libarchive, allowing people to bootstrap
 * libarchive on systems that do not already have a tar program.
 *
 * To unpack libarchive-x.y.z.tar.gz:
 *    * gunzip libarchive-x.y.z.tar.gz
 *    * untar libarchive-x.y.z.tar
 *
 * Written by Tim Kientzle, March 2009.
 *
 * Released into the public domain.
 */

/* These are all highly standard and portable headers. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zlib.h>
#include "bzlib.h"
#include "minitar.h"

/* This is for mkdir(); this may need to be changed for some platforms. */
#include <sys/stat.h>  /* For mkdir() */

#define Print(...)
#define BLOCKSIZE       512

typedef int (*read_callback_t)(void*, char*, int);

/* Parse an octal number, ignoring leading and trailing nonsense. */
static int
parseoct(const char *p, size_t n)
{
	int i = 0;

	while ((*p < '0' || *p > '7') && n > 0) {
		++p;
		--n;
	}
	while (*p >= '0' && *p <= '7' && n > 0) {
		i *= 8;
		i += *p - '0';
		++p;
		--n;
	}
	return (i);
}

/* Returns true if this is 512 zero bytes. */
static int
is_end_of_archive(const char *p)
{
	int n;
	for (n = 511; n >= 0; --n)
		if (p[n] != '\0')
			return (0);
	return (1);
}

/* Create a directory, including parent directories as necessary. */
static void
create_dir(char *pathname, int mode)
{
	char *p;
	int r;

	/* Strip trailing '/' */
	if (pathname[strlen(pathname) - 1] == '/')
		pathname[strlen(pathname) - 1] = '\0';

	/* Try creating the directory. */
	r = mkdir(pathname, mode);

	if (r != 0) {
		/* On failure, try creating parent directory. */
		p = strrchr(pathname, '/');
		if (p != NULL) {
			*p = '\0';
			create_dir(pathname, 0755);
			*p = '/';
			r = mkdir(pathname, mode);
		}
	}
	if (r != 0)
		Print("Could not create directory %s\n", pathname);
}

/* Create a file, including parent directory as necessary. */
static FILE *
create_file(char *pathname, int mode)
{
	FILE *f;
	f = fopen(pathname, "wb+");
	if (f == NULL) {
		/* Try creating parent dir and then creating file. */
		char *p = strrchr(pathname, '/');
		if (p != NULL) {
			*p = '\0';
			create_dir(pathname, 0755);
			*p = '/';
			f = fopen(pathname, "wb+");
		}
	}
	return (f);
}

/* Verify the tar checksum. */
static int
verify_checksum(const char *p)
{
	int n, u = 0;
	for (n = 0; n < BLOCKSIZE; ++n) {
		if (n < 148 || n > 155)
			/* Standard tar checksum adds unsigned bytes. */
			u += ((unsigned char *)p)[n];
		else
			u += 0x20;

	}
	return (u == parseoct(p + 148, 8));
}

int gz_read(void* gzF, char* buf, int len)
{
	return gzread(gzF, buf, len);
}

int bz2_read(void* bzF, char* buf, int len)
{
	return BZ2_bzread(bzF, buf, len);
}

int std_read(void* stdF, char* buf, int len)
{
	return fread(buf, 1, len, stdF);
}

void get_full_path(const char *dst_path, const char *file, char *out)
{
	if (file[0] == '/')
		file++;

	if (dst_path[strlen(dst_path) - 1] == '/')
		snprintf(out, 256, "%s%s", dst_path, file);
	else
		snprintf(out, 256, "%s/%s", dst_path, file);
}

/* Extract a tar archive. */
static int
untar_archive(void *a, read_callback_t read_cb, const char *dst_path, tar_callback_t callback)
{
	char buff[BLOCKSIZE];
	char path[256];
	FILE *f = NULL;
	size_t bytes_read;
	int filesize;

	Print("Extracting to %s\n", dst_path);
	for (;;) {
		bytes_read = read_cb(a, buff, BLOCKSIZE);
		if (bytes_read < BLOCKSIZE) {
			Print("Short read on file: expected %d, got %d\n", BLOCKSIZE, (int)bytes_read);
			return (-1);
		}
		if (is_end_of_archive(buff)) {
			Print("End of file.\n");
			return 0;
		}
		if (!verify_checksum(buff)) {
			Print("Checksum failure\n");
			return (-1);
		}
		filesize = parseoct(buff + 124, 12);
		switch (buff[156]) {
		case TAR_HARDLINK:
			Print(" Ignoring hardlink %s\n", buff);
			break;
		case TAR_SYMLINK:
			Print(" Ignoring symlink %s\n", buff);
			break;
		case TAR_CHAR:
			Print(" Ignoring character device %s\n", buff);
			break;
		case TAR_BLOCK:
			Print(" Ignoring block device %s\n", buff);
			break;
		case TAR_DIRECTORY:
			Print(" Extracting dir %s\n", buff);
			get_full_path(dst_path, buff, path);
			create_dir(path, parseoct(buff + 100, 8));
			filesize = 0;
			break;
		case TAR_FIFO:
			Print(" Ignoring FIFO %s\n", buff);
			break;
		default:
			Print(" Extracting file %s\n", buff);
			get_full_path(dst_path, buff, path);
			f = create_file(path, parseoct(buff + 100, 8));
			break;
		}

		if (callback)
			callback(buff, filesize, buff[156]);

		while (filesize > 0) {
			bytes_read = read_cb(a, buff, BLOCKSIZE);
			if (bytes_read < BLOCKSIZE) {
				Print("Short read on file: Expected %d, got %d\n", BLOCKSIZE, (int)bytes_read);
				return (-1);
			}
			if (filesize < BLOCKSIZE)
				bytes_read = filesize;
			if (f != NULL) {
				if (fwrite(buff, 1, bytes_read, f) != bytes_read)
				{
					Print("Failed write\n");
					fclose(f);
					f = NULL;
				}
			}
			filesize -= bytes_read;
		}
		if (f != NULL) {
			fclose(f);
			f = NULL;
		}
	}
}

int untarEx(const char* srcFile, const char* dstPath, tar_callback_t cb)
{
	FILE *a = fopen(srcFile, "rb");

	if (!a)
		return (-1);

	int ret = untar_archive(a, &std_read, dstPath, cb);
	fclose(a);
	return (ret);
}

int untarEx_gz(const char* srcFile, const char* dstPath, tar_callback_t cb)
{
	gzFile gz = gzopen(srcFile, "rb");

	if (!gz)
		return (-1);

	int ret = untar_archive(gz, &gz_read, dstPath, cb);
	gzclose_r(gz);
	return (ret);
}

int untarEx_bz2(const char* srcFile, const char* dstPath, tar_callback_t cb)
{
	BZFILE *bz = BZ2_bzopen(srcFile, "rb");

	if (!bz)
		return (-1);

	int ret = untar_archive(bz, &bz2_read, dstPath, cb);
	BZ2_bzclose(bz);
	return (ret);
}

int untar(const char* srcFile, const char* dstPath)
{
	return untarEx(srcFile, dstPath, NULL);
}

int untar_gz(const char* srcFile, const char* dstPath)
{
	return untarEx_gz(srcFile, dstPath, NULL);
}

int untar_bz2(const char* srcFile, const char* dstPath)
{
	return untarEx_bz2(srcFile, dstPath, NULL);
}
