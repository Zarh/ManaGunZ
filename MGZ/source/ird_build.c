#include "ird_build.h"

u32 IRD_crc(ird_t *ird)
{
	u32 i;
	u32 crc = crc32(0L, Z_NULL, 0);
	
	crc = crc32(crc,  (const unsigned char*) ird->MAGIC                       , 4);
	crc = crc32(crc,  (const unsigned char*) &ird->Version                    , 1);
	crc = crc32(crc,  (const unsigned char*) ird->GameId                      , 9);
	crc = crc32(crc,  (const unsigned char*) &ird->GameName_length            , 1);
	crc = crc32(crc,  (const unsigned char*) ird->GameName                    , ird->GameName_length);
	crc = crc32(crc,  (const unsigned char*) ird->UpdateVersion               , 4);
	crc = crc32(crc,  (const unsigned char*) ird->GameVersion                 , 5);
	crc = crc32(crc,  (const unsigned char*) ird->AppVersion                  , 5);
	
	if(ird->Version == 7) {
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
		crc = crc32(crc,  (const unsigned char*) &ird->UniqueIdentifier       , 4);
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
	}
	
	ird->HeaderLength = ENDIAN_SWAP(ird->HeaderLength);
	crc = crc32(crc,  (const unsigned char*) &ird->HeaderLength               , 4);
	ird->HeaderLength = ENDIAN_SWAP(ird->HeaderLength);
	crc = crc32(crc,  (const unsigned char*) ird->Header                      , ird->HeaderLength);
	
	ird->FooterLength = ENDIAN_SWAP(ird->FooterLength);
	crc = crc32(crc,  (const unsigned char*) &ird->FooterLength               , 4);
	ird->FooterLength = ENDIAN_SWAP(ird->FooterLength);
	crc = crc32(crc,  (const unsigned char*) ird->Footer                      , ird->FooterLength);
	
	crc = crc32(crc,  (const unsigned char*) &ird->RegionHashesNumber         , 1);
	for(i=0; i<ird->RegionHashesNumber; i++) {
		crc = crc32(crc,  (const unsigned char*) ird->RegionHashes[i]         ,  0x10);
	}
	
	ird->FileHashesNumber = ENDIAN_SWAP(ird->FileHashesNumber);
	crc = crc32(crc,  (const unsigned char*) &ird->FileHashesNumber           , 4);
	ird->FileHashesNumber = ENDIAN_SWAP(ird->FileHashesNumber);
	
	for(i=0; i<ird->FileHashesNumber; i++) {
		ird->FileHashes[i].Sector =  ENDIAN_SWAP(ird->FileHashes[i].Sector);
		crc = crc32(crc,  (const unsigned char*) &ird->FileHashes[i].Sector    , 0x8);
		ird->FileHashes[i].Sector =  ENDIAN_SWAP(ird->FileHashes[i].Sector);
		crc = crc32(crc,  (const unsigned char*) ird->FileHashes[i].FileHash   , 0x10);
	}
	
	ird->ExtraConfig = ENDIAN_SWAP(ird->ExtraConfig);
	crc = crc32(crc,  (const unsigned char*) &ird->ExtraConfig                 , 2);
	ird->ExtraConfig = ENDIAN_SWAP(ird->ExtraConfig);
	
	ird->Attachments = ENDIAN_SWAP(ird->Attachments);
	crc = crc32(crc,  (const unsigned char*) &ird->Attachments                 , 2);
	ird->Attachments = ENDIAN_SWAP(ird->Attachments);
	
	if(ird->Version >= 9) {
		crc = crc32(crc,  (const unsigned char*) ird->PIC                     , 0x73);
	}
	crc = crc32(crc,  (const unsigned char*) ird->Data1                       , 0x10);
	crc = crc32(crc,  (const unsigned char*) ird->Data2                       , 0x10);
	if(ird->Version < 9) {
		crc = crc32(crc,  (const unsigned char*) ird->PIC                     , 0x73);
	}
	if(ird->Version > 7) {
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
		crc = crc32(crc,  (const unsigned char*) &ird->UniqueIdentifier       , 4);
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
	}
	
	return crc;
}

ird_t *MALLOC_IRD()
{
// must init to use FREE_IRD anytime
	ird_t *ird = NULL;
	ird = (ird_t *) malloc( sizeof(ird_t) );
	if( ird != NULL) {
		memset(ird, 0, sizeof(ird_t) );
		ird->GameName=NULL;
		ird->Header=NULL;
		ird->Footer=NULL;
		ird->RegionHashes=NULL;
		ird->FileHashes=NULL;
	}
	
	return ird;
}

ird_t *IRD_load(char *IRD_PATH)
{
	int ret = FAILED;
	int i;
	ird_t *ird = NULL;
	FILE *irdu = NULL;
	
	char IRDU_PATH[255];
	sprintf(IRDU_PATH, "%su", IRD_PATH);
	print_verbose("IRD_Load IRD_Decompress");
	if( GZ_decompress5(IRD_PATH, IRDU_PATH) != Z_OK) {
		printf("Error : IRD_Load Failed to Decompress IRD %s", IRD_PATH);
		goto error;
	}
	
	print_verbose("IRD_Load fopen");
	irdu = fopen(IRDU_PATH, "rb");
	if( irdu == NULL ) {printf("Error : IRD_Load Failed to fopen irdu"); goto error;}
	
	print_verbose("IRD_Load malloc ird");
	ird = MALLOC_IRD();
	if( ird == NULL ) {printf("Error : IRD_Load Failed to malloc irdu"); goto error;}
	memset(ird, 0, sizeof(ird_t));
	
	print_verbose("IRD_Load fread MAGIC");
	fread(ird->MAGIC, sizeof(char), 4, irdu);
	
	if( strcmp(ird->MAGIC, MAGIC_IRD) ) {printf("Error : IRD_Load MAGIC"); goto error;}
	
	print_verbose("IRD_Load fread version = ");
	fread(&ird->Version			, sizeof(u8)  , 1, irdu);
	print_verbose("%d",  ird->Version);
	print_verbose("IRD_Load fread gameid = ");
	fread(ird->GameId			, sizeof(char), 9, irdu);
	ird->GameId[9] = 0;
	print_verbose("%s", ird->GameId);
	print_verbose("IRD_Load fread gamename_length");
	fread(&ird->GameName_length	, sizeof(u8)  , 1, irdu);
	
	print_verbose("IRD_Load malloc gamename");
	ird->GameName = (char *) malloc(sizeof(char) * ird->GameName_length +1); // it's a string it need to finish by 0
	if( ird->GameName == NULL)  {printf("Error : IRD_Load Failed to malloc GameName"); goto error;}
	memset(ird->GameName, 0, ird->GameName_length+1);
	
	print_verbose("IRD_Load fread gamename = ");
	fread(ird->GameName			, sizeof(char), ird->GameName_length, irdu);
	print_verbose("%s", ird->GameName);
	print_verbose("IRD_Load fread updateversion = ");
	fread(ird->UpdateVersion	, sizeof(char), 4, irdu);
	ird->UpdateVersion[4] = 0;
	print_verbose("%s", ird->UpdateVersion);
	print_verbose("IRD_Load fread gameversion = ");
	fread(ird->GameVersion		, sizeof(char), 5, irdu);
	ird->GameVersion[5] = 0;
	print_verbose("%s", ird->GameVersion);
	print_verbose("IRD_Load fread appversion = ");
	fread(ird->AppVersion		, sizeof(char), 5, irdu);
	ird->AppVersion[5] = 0;
	print_verbose("%s", ird->AppVersion);
	
	if(ird->Version == 7) {
		print_verbose("IRD_Load fread UniqueIdentifier = ");
		fread(&ird->UniqueIdentifier, sizeof(u32) , 1, irdu);
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
		print_verbose("%d",  ird->UniqueIdentifier);
	}
	
	print_verbose("IRD_Load fread headerlength = ");
	fread(&ird->HeaderLength		, sizeof(u32) , 1, irdu);
	ird->HeaderLength = ENDIAN_SWAP(ird->HeaderLength);
	print_verbose("%d",  ird->HeaderLength);
	
	print_verbose("IRD_Load malloc iso header");
	ird->Header = (u8 *) malloc(ird->HeaderLength * sizeof(u8));
	if(ird->Header == NULL) {printf("Error : IRD_Load Failed to malloc iso header"); goto error;}
	print_verbose("IRD_Load fread iso header");
	fread(ird->Header			, sizeof(u8) , ird->HeaderLength, irdu);
	
	print_verbose("IRD_Load fread iso footerlength = ");
	fread(&ird->FooterLength		, sizeof(u32) , 1, irdu);
	ird->FooterLength = ENDIAN_SWAP(ird->FooterLength);
	print_verbose("%X", ird->FooterLength);
	
	print_verbose("IRD_Load malloc footer");
	ird->Footer = (u8 *) malloc(ird->FooterLength * sizeof(u8));
	if(ird->Footer == NULL)  {printf("Error : IRD_Load Failed to malloc iso footer"); goto error;}
	
	print_verbose("IRD_Load fread footer");
	fread(ird->Footer			, sizeof(u8) , ird->FooterLength, irdu);
	
	print_verbose("IRD_Load fread regionhashesnumber = ");
	fread(&ird->RegionHashesNumber	, sizeof(u8) , 1, irdu);
	print_verbose("%d",  ird->RegionHashesNumber);
	
	print_verbose("IRD_Load malloc regionhashes");
	ird->RegionHashes = (u8 **) malloc(ird->RegionHashesNumber * sizeof(u8*));
	if(ird->RegionHashes == NULL)  {printf("Error : IRD_Load Failed to malloc region hashes"); goto error;}
	
	print_verbose("IRD_Load RegionHashes");
	for(i=0; i<ird->RegionHashesNumber; i++) {
		ird->RegionHashes[i] = (u8 *) malloc( 0x10 * sizeof(u8));
		if(ird->RegionHashes[i] == NULL)  {printf("Error : IRD_Load Failed to malloc RegionHashes"); goto error;}
		fread(ird->RegionHashes[i], sizeof(u8), 0x10, irdu);
	}
	
	print_verbose("IRD_Load fread filehashesnumber");
	fread(&ird->FileHashesNumber	, sizeof(u32) , 1, irdu);
	ird->FileHashesNumber = ENDIAN_SWAP(ird->FileHashesNumber);
	print_load("%X", ird->FileHashesNumber);
	
	print_verbose("IRD_Load malloc filehashes");
	ird->FileHashes = (FileHash_t *) malloc(ird->FileHashesNumber * sizeof(FileHash_t));
	if(ird->FileHashes == NULL)  {printf("Error : IRD_Load Failed to malloc filehashes"); goto error;}
	
	print_verbose("IRD_Load fread filehashes");
	for(i=0; i<ird->FileHashesNumber; i++) {
		fread(&ird->FileHashes[i].Sector, sizeof(u64), 1, irdu);
		ird->FileHashes[i].Sector =  ENDIAN_SWAP(ird->FileHashes[i].Sector);
		fread(&ird->FileHashes[i].FileHash, sizeof(u8), 0x10, irdu);
		ird->FileHashes[i].FilePath=NULL;
	}
	
	print_verbose("IRD_Load fread ExtraConfig");
	fread(&ird->ExtraConfig, sizeof(u16), 1, irdu);
	ird->ExtraConfig = ENDIAN_SWAP(ird->ExtraConfig);
	print_verbose("IRD_Load fread Attachments");
	fread(&ird->Attachments, sizeof(u16), 1, irdu);
	ird->Attachments = ENDIAN_SWAP(ird->Attachments);
	
	if(ird->Version >= 9) {
		print_verbose("IRD_Load fread PIC");
		fread(ird->PIC  , sizeof(u8), 0x73, irdu);
	}
	
	print_verbose("IRD_Load fread Data1");
	fread(ird->Data1, sizeof(u8), 0x10, irdu);
	print_verbose("IRD_Load fread Data2");
	fread(ird->Data2, sizeof(u8), 0x10, irdu);
	
	if(ird->Version < 9) {
		print_verbose("IRD_Load fread PIC");
		fread(ird->PIC  , sizeof(u8), 0x73, irdu);
	}
	
	if(ird->Version > 7) {
		print_verbose("IRD_Load fread UniqueIdentifier = %X");
		fread(&ird->UniqueIdentifier, sizeof(u32), 1, irdu);
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
		print_verbose("%X", ird->UniqueIdentifier); 
	}
	
	print_verbose("IRD_Load fread crc = ");
	fread(&ird->crc, sizeof(u32), 1, irdu);
	ird->crc = ENDIAN_SWAP(ird->crc);
	print_verbose("%X", ird->crc); 
	ret = SUCCESS;
	
error:
	print_verbose("IRD_Load fclose");
	FCLOSE(irdu);

	if( ret == FAILED ) {
		print_verbose("IRD_Load free_ird");
		FREE_IRD(ird);
	}
	
	Delete(IRDU_PATH);
	
	return ird;
}

u8 IRD_save(char *IRD_PATH, ird_t *ird)
{
	int ret = FAILED;
	int i;
	
	char IRDU_PATH[255];
	sprintf(IRDU_PATH, "%su", IRD_PATH);
	
	print_verbose("IRD_Save fopen");
	FILE *irdu = fopen(IRDU_PATH, "wb");
	if( irdu == NULL ) {printf("Error : IRD_Save Failed to fopen irdu"); goto error;}
	
	print_verbose("IRD_Save fwrite MAGIC");
	fwrite(ird->MAGIC, sizeof(char), 4, irdu);
	
	print_verbose("IRD_Save fwrite version = %d",  ird->Version);
	fwrite(&ird->Version		, sizeof(u8)  , 1, irdu);
	
	print_verbose("IRD_Save fwrite gameid = %s", ird->GameId);
	fwrite(ird->GameId			, sizeof(char), 9, irdu);
	
	print_verbose("IRD_Save fwrite gamename_length");
	fwrite(&ird->GameName_length	, sizeof(u8)  , 1, irdu);
	
	print_verbose("IRD_Save fwrite gamename = %s", ird->GameName);
	fwrite(ird->GameName			, sizeof(char), ird->GameName_length, irdu);
	
	print_verbose("IRD_Save fwrite updateversion = %s", ird->UpdateVersion);
	fwrite(ird->UpdateVersion	, sizeof(char), 4, irdu);
	
	print_verbose("IRD_Save fwrite gameversion = %s", ird->GameVersion);
	fwrite(ird->GameVersion		, sizeof(char), 5, irdu);
	
	print_verbose("IRD_Save fwrite appversion = %s", ird->AppVersion);
	fwrite(ird->AppVersion		, sizeof(char), 5, irdu);
	
	if(ird->Version == 7) {
		print_verbose("IRD_Load fwrite UniqueIdentifier = %X", ird->UniqueIdentifier);
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
		fwrite(&ird->UniqueIdentifier, sizeof(u32) , 1, irdu);
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
	}
	
	print_verbose("IRD_Save fwrite headerlength = %X",  ird->HeaderLength);
	ird->HeaderLength = ENDIAN_SWAP(ird->HeaderLength);
	fwrite(&ird->HeaderLength		, sizeof(u32) , 1, irdu);
	ird->HeaderLength = ENDIAN_SWAP(ird->HeaderLength);
	
	print_verbose("IRD_Save fwrite iso header");
	fwrite(ird->Header			, sizeof(u8) , ird->HeaderLength, irdu);
	
	print_verbose("IRD_Save fwrite iso footerlength = %X", ird->FooterLength);
	ird->FooterLength = ENDIAN_SWAP(ird->FooterLength);
	fwrite(&ird->FooterLength		, sizeof(u32) , 1, irdu);
	ird->FooterLength = ENDIAN_SWAP(ird->FooterLength);
	
	print_verbose("IRD_Save fwrite footer");
	fwrite(ird->Footer			, sizeof(u8) , ird->FooterLength, irdu);
	
	print_verbose("IRD_Save fwrite regionhashesnumber = %d", ird->RegionHashesNumber);
	fwrite(&ird->RegionHashesNumber	, sizeof(u8) , 1, irdu);
	
	print_verbose("IRD_Save fwrite RegionHashes");
	for(i=0; i<ird->RegionHashesNumber; i++) {
		fwrite(ird->RegionHashes[i], sizeof(u8), 0x10, irdu);
	}
	
	print_verbose("IRD_Save fwrite filehashesnumber");
	ird->FileHashesNumber = ENDIAN_SWAP(ird->FileHashesNumber);
	fwrite(&ird->FileHashesNumber	, sizeof(u32) , 1, irdu);
	ird->FileHashesNumber = ENDIAN_SWAP(ird->FileHashesNumber);
	
	print_verbose("IRD_Save fwrite filehashes");
	for(i=0; i<ird->FileHashesNumber; i++) {
		ird->FileHashes[i].Sector =  ENDIAN_SWAP(ird->FileHashes[i].Sector);
		fwrite(&ird->FileHashes[i].Sector, sizeof(u64), 1, irdu);
		ird->FileHashes[i].Sector =  ENDIAN_SWAP(ird->FileHashes[i].Sector);
		fwrite(&ird->FileHashes[i].FileHash, sizeof(u8), 0x10, irdu);
	}
	
	print_verbose("IRD_Save fwrite ExtraConfig");
	ird->ExtraConfig = ENDIAN_SWAP(ird->ExtraConfig);
	fwrite(&ird->ExtraConfig, sizeof(u16), 1, irdu);
	ird->ExtraConfig = ENDIAN_SWAP(ird->ExtraConfig);
	
	print_verbose("IRD_Save fwrite Attachments");
	ird->Attachments = ENDIAN_SWAP(ird->Attachments);
	fwrite(&ird->Attachments, sizeof(u16), 1, irdu);
	ird->Attachments = ENDIAN_SWAP(ird->Attachments);
	
	if(ird->Version >= 9) {
		print_verbose("IRD_Load fwrite PIC");
		fwrite(ird->PIC  , sizeof(u8), 0x73, irdu);
	}
	
	print_verbose("IRD_Save fwrite Data1");
	fwrite(ird->Data1, sizeof(u8), 0x10, irdu);
	print_verbose("IRD_Save fwrite Data2");
	fwrite(ird->Data2, sizeof(u8), 0x10, irdu);
	
	if(ird->Version < 9) {
		print_verbose("IRD_Save fwrite PIC");
		fwrite(ird->PIC  , sizeof(u8), 0x73, irdu);
	}
	
	if(ird->Version > 7) {
		print_verbose("IRD_Load fread UniqueIdentifier = %X", ird->UniqueIdentifier );
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
		fwrite(&ird->UniqueIdentifier, sizeof(u32), 1, irdu);
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
	}
	
	ird->crc = IRD_crc(ird);
	
	print_verbose("IRD_Save fwrite crc = %X", ird->crc);
	ird->crc = ENDIAN_SWAP(ird->crc);
	ret = fwrite(&ird->crc  , sizeof(u32), 1, irdu);
	ird->crc = ENDIAN_SWAP(ird->crc);
	
	ret = SUCCESS;
error:
	print_verbose("IRD_Save fclose");
	FCLOSE(irdu);
	
	if( ret == SUCCESS ) {
		print_verbose("IRD_Save IRD_Compress");
		if( GZ_compress5(IRDU_PATH, IRD_PATH) != Z_OK) {
			printf("Error : IRD_Load Failed to compress IRD");
			ret = FAILED;
		}
	}
	
	Delete(IRDU_PATH);
	
	return ret;
}
