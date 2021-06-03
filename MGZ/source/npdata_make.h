// Copyright (C) 2014       Hykem <hykem@hotmail.com>
// Licensed under the terms of the GNU GPL, version 3
// http://www.gnu.org/licenses/gpl-3.0.txt

#ifndef _NPDATA_MAKE_H_
#define _NPDATA_MAKE_H_

#include <stdio.h>
#include <string.h>
#include "npdata_utils.h"

#define SDAT_FLAG 0x01000000
#define EDAT_COMPRESSED_FLAG 0x00000001
#define EDAT_FLAG_0x02 0x00000002
#define EDAT_ENCRYPTED_KEY_FLAG 0x00000008
#define EDAT_FLAG_0x10 0x00000010
#define EDAT_FLAG_0x20 0x00000020
#define EDAT_DEBUG_DATA_FLAG 0x80000000

//  encrypt arguments
#define NPDATA_FORMAT_SDAT				0
#define NPDATA_FORMAT_EDAT				1

#define NPDATA_DATA_DEBUG				0
#define NPDATA_DATA_FINALIZED			1

#define NPDATA_VERSION_1				1
#define NPDATA_VERSION_2				2
#define NPDATA_VERSION_3				3
#define NPDATA_VERSION_4				4

#define NPDATA_COMPRESSION_DISABLED		0
#define NPDATA_COMPRESSION_ENABLED		1

#define NPDATA_BLOCK_1KB				1
#define NPDATA_BLOCK_2KB				2
#define NPDATA_BLOCK_4KB				4
#define NPDATA_BLOCK_8KB				8
#define NPDATA_BLOCK_16KB				16
#define NPDATA_BLOCK_32KB				32

#define NPDATA_LICENSE_NET				1
#define NPDATA_LICENSE_LOCAL			2
#define NPDATA_LICENSE_FREE				3

#define NPDATA_TYPE_COMMON				00
#define NPDATA_TYPE_PS2_EDAT			01
#define NPDATA_TYPE_PSP_REMASTER		20
#define NPDATA_TYPE_MODULES				21 // (disc bind)
#define NPDATA_TYPE_UNKNOWN				30

// Brute-force mode
#define NPDATA_BF_MODE_BINARY 			1
#define NPDATA_BF_MODE_TEXT				2
#define NPDATA_BF_MODE_UNICODE			4
// only 1 stream can be used at once
#define NPDATA_BF_MODE_BINARY_STREAM	8
#define NPDATA_BF_MODE_TEXT_STREAM		16
#define NPDATA_BF_MODE_UNICODE_STREAM	32
#define NPDATA_BF_MODE_LINES_STREAM		64 //read 32 first characters of each line

typedef struct 
{
	unsigned char magic[4];
    int version;
    int license;
    int type;
    unsigned char content_id[0x30];
    unsigned char digest[0x10];
    unsigned char title_hash[0x10];
    unsigned char dev_hash[0x10];
    unsigned long long unk1;
    unsigned long long unk2;
} NPD_HEADER;

typedef struct 
{
	int flags;
	int block_size;
	unsigned long long file_size;
} EDAT_HEADER;

u8 npdata_bruteforce(char *npdata_file, char *source_file, u8 mode, u8 *dev_klicensee);
u8 npdata_decrypt(char *npdata_file, char *output_file, u8 *dev_klicensee, char *rap_file, char *rif_file);
u8 npdata_encrypt(char *input_file, char *npdata_file, u8 *dev_klicensee, char *raf_file, char *rif_file, 
					u8 format, u8 data, u8 version, u8 compression, u8 block, u8 license, u8 type, char *cID);

#endif