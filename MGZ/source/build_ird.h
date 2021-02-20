#ifndef _BUILD__IRD_H
#define _BUILD__IRD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "zpipe.h"
#include "md5.h"

//#define VERBOSE	 1

#ifdef VERBOSE
	#define print_verbose printf
#else
	#define print_verbose(...)
#endif

#ifdef LITTLE_ENDIAN
#define ENDIAN_SWAP(x) 			x
#define Delete(...)
typedef uint8_t		u8;
typedef uint16_t 	u16;
typedef uint32_t	u32;
typedef uint64_t 	u64;
#else
#include <ppu-types.h>
#define ENDIAN_SWAP(x)			(sizeof(x) == 2 ? ENDIAN_SWAP_16(x) : (sizeof(x) == 4 ? ENDIAN_SWAP_32(x) : ENDIAN_SWAP_64(x)))
#define printf					print_load
extern void print_load(char *format, ...);
extern void Delete(char* path);
#endif

#define SUCCESS		1
#define FAILED 		0
#define COMPRESS 	0
#define DECOMPRESS	1

#define ENDIAN_SWAP_16(x)		(((x) & 0x00FF) << 8 | ((x) & 0xFF00) >> 8)
#define ENDIAN_SWAP_32(x)		(((x) & 0x000000FF) << 24 | ((x) & 0x0000FF00) << 8 | \
								 ((x) & 0x00FF0000) >>  8 | ((x) & 0xFF000000) >> 24  )
#define ENDIAN_SWAP_64(x)		(((x) & 0x00000000000000FFULL) << 56 | ((x) & 0x000000000000FF00ULL) << 40 | \
								 ((x) & 0x0000000000FF0000ULL) << 24 | ((x) & 0x00000000FF000000ULL) <<  8 | \
								 ((x) & 0x000000FF00000000ULL) >>  8 | ((x) & 0x0000FF0000000000ULL) >> 24 | \
								 ((x) & 0x00FF000000000000ULL) >> 40 | ((x) & 0xFF00000000000000ULL) >> 56 )
#define FREE(x)					if(x!=NULL) {free(x);x=NULL;}
#define FCLOSE(x) 				if(x!=NULL) {fclose(x);x=NULL;}
#define FREE_IRD(x)				if(x!=NULL) {                                                                     \
									int o;                                                                     \
									FREE(x->GameName);                                                         \
									FREE(x->Header);                                                           \
									FREE(x->Footer);                                                           \
									for(o=0; o<x->RegionHashesNumber; o++) FREE(x->RegionHashes[o]);           \
									FREE(x->RegionHashes);                                                     \
									FREE(x->FileHashes);                                                       \
									FREE(x);                                                                   \
								}
#define MAGIC_IRD				"3IRD"

typedef struct
{
	u64 Sector;
	u8 FileHash[0x10];
} FileHash_t;

typedef struct
{
	char MAGIC[4]; 
	u8 Version;
	char gameId[9];
	u8 GameName_lenght;
	char *GameName;
	char UpdateVersion[5]; // +0
	char gameVersion[6]; // +0
	char AppVersion[6]; // +0
	u32 ID; // v7 only
	u32 HeaderLenght;
	u8 *Header;
	u32 FooterLenght;
	u8 *Footer;
	u8 RegionHashesNumber;
	u8 **RegionHashes; 
	u32 FileHashesNumber;
	FileHash_t *FileHashes; 
	u16 extraConfig;
	u16 attachments;
	u8 PIC[0x73];
	u8 Data1[0x10];
	u8 Data2[0x10];
// I have no idea how it's calculated, it's probably a CRC32.
	u32 UniqueIdentifier; //v7+
	u32 crc;
} ird_t;

u8 IRD_gz(u8 task, char *file_in, char *file_out);
ird_t *IRD_load(char *IRD_PATH);
u8 IRD_save(char *IRD_PATH, ird_t *ird);

#endif