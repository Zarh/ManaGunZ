#ifndef _IRD_BUILD_H
#define _IRD_BUILD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ppu-types.h>

#include "mgz_io.h"
#include "ird_gz.h"
#include "md5.h"
#include "extern.h"

#define FREE_IRD(x)				if(x!=NULL) {                                                                  \
									int o;                                                                     \
									FREE(x->GameName);                                                         \
									FREE(x->Header);                                                           \
									FREE(x->Footer);                                                           \
									for(o=0; o<x->RegionHashesNumber; o++) FREE(x->RegionHashes[o]);           \
									FREE(x->RegionHashes);                                                     \
									for(o=0; o<x->FileHashesNumber; o++) FREE(x->FileHashes[o].FilePath);      \
									FREE(x->FileHashes);                                                       \
									FREE(x);                                                                   \
								}
#define MAGIC_IRD				"3IRD"			
#define SIZEOF_IRD(x)  (4+1+9+1+x->GameName_length+4+5+5+4+x->HeaderLength+4+x->FooterLength+\
						1+x->RegionHashesNumber*0x10+4+x->FileHashesNumber*(0x8+0x10)+2+2+\
						0x73+0x10+0x10+4+4)

typedef struct
{
	u64 Sector;
	u8 FileHash[0x10];
	char *FilePath; // not inside ird
} FileHash_t;

typedef struct
{
	char MAGIC[4]; // "3IRD" = 3key Iso Rebuild Data
	u8 Version;  // Ird version (lastest is 9)
	char GameId[10]; // TITLE_ID from param.sfo
	u8 GameName_length; // Length of TITLE from param.sfo
	char *GameName; // TITLE from param.sfo
	char UpdateVersion[5]; // +0 // PS3UPDATE.PUP version
	char GameVersion[6]; // +0 // VERSION from param.sfo
	char AppVersion[6]; // +0 // APP_VER from param.sfo
	u32 HeaderLength; // Length of iso header. it's equal to the first file's offset.
	u8 *Header; // iso's header
	u32 FooterLength; // Length of iso footer (just after the last file which is always PS3UPDATE.PUP
	u8 *Footer; // iso's footer
	u8 RegionHashesNumber; // without the 1st and the last region
	u8 **RegionHashes; // md5
	u32 FileHashesNumber; // ..
	FileHash_t *FileHashes; // md5
	u16 ExtraConfig; // unused
	u16 Attachments; // unused
	u8 PIC[0x73]; // extra disc info. AFAIK, it's unused by anyone (?)
	u8 Data1[0x10]; // decryption key
	u8 Data2[0x10]; // per-disc key. Also, unused (?). To avoid any risk, 3key team change the 4 last bytes
	u32 UniqueIdentifier;   // From IsoTools' sources, reversed
							// UniqueIdentifier is used as a unique 'signature' to identify (anonymously) the user who dumped the disc
							// It's the CRC of 'InstallationId' which is the md5 of guid.newguid ; UniqueIdentifier = guid.newguid.md5.crc
							// it was probably used by their server to manage the uploaded ird 
	u32 crc; // crc of ird_t
} ird_t;

ird_t *MALLOC_IRD();
u8 IRD_gz(u8 task, char *file_in, char *file_out);
ird_t *IRD_load(char *IRD_PATH);
u8 IRD_save(char *IRD_PATH, ird_t *ird);

#endif