#include "build_ird.h"

u8 IRD_gz(u8 task, char *file_in, char *file_out)
{
	int ret=FAILED;
	
	FILE *in=NULL;
	FILE *out=NULL;
	
	in= fopen(file_in, "rb");
	if( in==NULL ) {
		printf("Error : failed to open file_in");
		goto error;
	}
	out= fopen(file_out, "wb");
	if( out==NULL ) {
		printf("Error : failed to open file_out");
		goto error;
	}
	
	if( task == DECOMPRESS ) {
		if( inf(in, out) != Z_OK ) goto error;
	} else 
	if( task == COMPRESS ) {
		if( def(in, out, 9) != Z_OK ) goto error;
	} else {
		goto error;
	}
	
	ret=SUCCESS;
error:
	FCLOSE(in);
	FCLOSE(out);
	
	if(ret==FAILED) Delete(file_out);
	
	return ret;
}

ird_t *IRD_load(char *IRD_PATH)
{
	int ret = FAILED;
	int i;
	ird_t *ird = NULL;
	FILE *irdu = NULL;
	
	char IRDU_PATH[255];
	sprintf(IRDU_PATH, "%su", IRD_PATH);
	print_verbose("IRD_Load IRD_Decompress\n");
	if( IRD_gz(DECOMPRESS, IRD_PATH, IRDU_PATH) == FAILED) {
		printf("Error : IRD_Load Failed to Decompress IRD\n");
		goto error;
	}
	
	print_verbose("IRD_Load fopen\n");
	irdu = fopen(IRDU_PATH, "rb");
	if( irdu == NULL ) {printf("Error : IRD_Load Failed to fopen irdu\n"); goto error;}
	
	print_verbose("IRD_Load malloc ird\n");
	ird = (ird_t *) malloc( sizeof(ird_t)+1 );
	if( ird == NULL ) {printf("Error : IRD_Load Failed to malloc irdu\n"); goto error;}
	memset(ird, 0, sizeof(ird_t));
	
	print_verbose("IRD_Load fread MAGIC\n");
	fread(ird->MAGIC, sizeof(char), 4, irdu);
	
	if( strcmp(ird->MAGIC, MAGIC_IRD) ) {printf("Error : IRD_Load MAGIC\n"); goto error;}
	
	print_verbose("IRD_Load fread version = ");
	fread(&ird->Version			, sizeof(u8)  , 1, irdu);
	print_verbose("%d\n",  ird->Version);
	print_verbose("IRD_Load fread gameid = ");
	fread(ird->gameId			, sizeof(char), 9, irdu);
	print_verbose("%s\n", ird->gameId);
	print_verbose("IRD_Load fread gamename_lenght\n");
	fread(&ird->GameName_lenght	, sizeof(u8)  , 1, irdu);
	
	print_verbose("IRD_Load malloc gamename\n");
	ird->GameName = (char *) malloc(sizeof(char) * ird->GameName_lenght +1); // it's a string it need to finish by 0
	if( ird->GameName == NULL)  {printf("Error : IRD_Load Failed to malloc GameName\n"); goto error;}
	memset(ird->GameName, 0, ird->GameName_lenght+1);
	
	print_verbose("IRD_Load fread gamename = ");
	fread(ird->GameName			, sizeof(char), ird->GameName_lenght, irdu);
	print_verbose("%s\n", ird->GameName);
	print_verbose("IRD_Load fread updateversion = ");
	fread(ird->UpdateVersion	, sizeof(char), 4, irdu);
	ird->UpdateVersion[4] = 0;
	print_verbose("%s\n", ird->UpdateVersion);
	print_verbose("IRD_Load fread gameversion = ");
	fread(ird->gameVersion		, sizeof(char), 5, irdu);
	ird->gameVersion[5] = 0;
	print_verbose("%s\n", ird->gameVersion);
	print_verbose("IRD_Load fread appversion = ");
	fread(ird->AppVersion		, sizeof(char), 5, irdu);
	ird->AppVersion[5] = 0;
	print_verbose("%s\n", ird->AppVersion);
	
	if(ird->Version == 7) {
		print_verbose("IRD_Load fread ID = ");
		fread(&ird->UniqueIdentifier_v7, sizeof(u32) , 1, irdu);
		ird->UniqueIdentifier_v7 = ENDIAN_SWAP(ird->UniqueIdentifier_v7);
		print_verbose("%d\n",  ird->UniqueIdentifier_v7);
	}
	
	print_verbose("IRD_Load fread headerlenght = ");
	fread(&ird->HeaderLenght		, sizeof(u32) , 1, irdu);
	ird->HeaderLenght = ENDIAN_SWAP(ird->HeaderLenght);
	print_verbose("%d\n",  ird->HeaderLenght);
	
	print_verbose("IRD_Load malloc iso header\n");
	ird->Header = (u8 *) malloc(ird->HeaderLenght * sizeof(u8));
	if(ird->Header == NULL) {printf("Error : IRD_Load Failed to malloc iso header\n"); goto error;}
	print_verbose("IRD_Load fread iso header\n");
	fread(ird->Header			, sizeof(u8) , ird->HeaderLenght, irdu);
	
	print_verbose("IRD_Load fread iso footerlenght = ");
	fread(&ird->FooterLenght		, sizeof(u32) , 1, irdu);
	ird->FooterLenght = ENDIAN_SWAP(ird->FooterLenght);
	print_verbose("%X\n", ird->FooterLenght);
	
	print_verbose("IRD_Load malloc footer\n");
	ird->Footer = (u8 *) malloc(ird->FooterLenght * sizeof(u8));
	if(ird->Footer == NULL)  {printf("Error : IRD_Load Failed to malloc iso footer\n"); goto error;}
	
	print_verbose("IRD_Load fread footer\n");
	fread(ird->Footer			, sizeof(u8) , ird->FooterLenght, irdu);
	
	print_verbose("IRD_Load fread regionhashesnumber = ");
	fread(&ird->RegionHashesNumber	, sizeof(u8) , 1, irdu);
	print_verbose("%d\n",  ird->RegionHashesNumber);
	
	print_verbose("IRD_Load malloc regionhashes\n");
	ird->RegionHashes = (u8 **) malloc(ird->RegionHashesNumber * sizeof(u8*));
	if(ird->RegionHashes == NULL)  {printf("Error : IRD_Load Failed to malloc region hashes\n"); goto error;}
	
	for(i=0; i<ird->RegionHashesNumber; i++) {
		print_verbose("IRD_Load malloc region #%d\n", i+1);
		ird->RegionHashes[i] = (u8 *) malloc( 0x10 * sizeof(u8));
		if(ird->RegionHashes[i] == NULL)  {printf("Error : IRD_Load Failed to malloc RegionHashes\n"); goto error;}
		
		print_verbose("IRD_Load fread region #%d\n", i+1);
		fread(ird->RegionHashes[i], sizeof(u8), 0x10, irdu);
	}
	
	print_verbose("IRD_Load fread filehashesnumber\n");
	fread(&ird->FileHashesNumber	, sizeof(u32) , 1, irdu);
	ird->FileHashesNumber = ENDIAN_SWAP(ird->FileHashesNumber);
	
	print_verbose("IRD_Load malloc filehashes\n");
	ird->FileHashes = (FileHash_t *) malloc(ird->FileHashesNumber * sizeof(FileHash_t));
	if(ird->FileHashes == NULL)  {printf("Error : IRD_Load Failed to malloc filehashes\n"); goto error;}
	
	for(i=0; i<ird->FileHashesNumber; i++) {
		print_verbose("IRD_Load fread filehashes.sector #%d\n", i+1);
		fread(&ird->FileHashes[i].Sector, sizeof(u64), 1, irdu);
		ird->FileHashes[i].Sector =  ENDIAN_SWAP(ird->FileHashes[i].Sector);
		print_verbose("IRD_Load fread filehashes.FileHash #%d\n", i+1);
		fread(&ird->FileHashes[i].FileHash, sizeof(u8), 0x10, irdu);
	}
	
	print_verbose("IRD_Load fread extraConfig\n");
	fread(&ird->extraConfig, sizeof(u16), 1, irdu);
	ird->extraConfig = ENDIAN_SWAP(ird->extraConfig);
	print_verbose("IRD_Load fread attachments\n");
	fread(&ird->attachments, sizeof(u16), 1, irdu);
	ird->attachments = ENDIAN_SWAP(ird->attachments);
	
	if(ird->Version >= 9) {
		print_verbose("IRD_Load fread PIC\n");
		fread(ird->PIC  , sizeof(u8), 0x73, irdu);
	}
	
	print_verbose("IRD_Load fread Data1\n");
	fread(ird->Data1, sizeof(u8), 0x10, irdu);
	print_verbose("IRD_Load fread Data2\n");
	fread(ird->Data2, sizeof(u8), 0x10, irdu);
	
	if(ird->Version < 9) {
		print_verbose("IRD_Load fread PIC\n");
		fread(ird->PIC  , sizeof(u8), 0x73, irdu);
	}
	
	if(ird->Version > 7) {
		print_verbose("IRD_Load fread UniqueIdentifier = %X");
		fread(&ird->UniqueIdentifier, sizeof(u32), 1, irdu);
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
		print_verbose("%X\n", ird->UniqueIdentifier); 
	}
	
	print_verbose("IRD_Load fread crc = %X");
	fread(&ird->crc, sizeof(u32), 1, irdu);
	ird->crc = ENDIAN_SWAP(ird->crc);
	print_verbose("%X\n", ird->crc); 
	ret = SUCCESS;
	
error:
	print_verbose("IRD_Load fclose\n");
	FCLOSE(irdu);

	if( ret == FAILED ) {
		print_verbose("IRD_Load free_ird\n");
		FREE_IRD(ird);
	}
	
	return ird;
}

u8 IRD_save(char *IRD_PATH, ird_t *ird)
{
	int ret = FAILED;
	int i;
	
	char IRDU_PATH[255];
	sprintf(IRDU_PATH, "%su", IRD_PATH);
	
	print_verbose("IRD_Save fopen\n");
	FILE *irdu = fopen(IRDU_PATH, "wb");
	if( irdu == NULL ) {printf("Error : IRD_Save Failed to fopen irdu\n"); goto error;}
	
	print_verbose("IRD_Save fwrite MAGIC\n");
	fwrite(ird->MAGIC, sizeof(char), 4, irdu);
	
	print_verbose("IRD_Save fwrite version = ");
	fwrite(&ird->Version		, sizeof(u8)  , 1, irdu);
	print_verbose("%d\n",  ird->Version);
	print_verbose("IRD_Save fwrite gameid = ");
	fwrite(ird->gameId			, sizeof(char), 9, irdu);
	print_verbose("%s\n", ird->gameId);
	print_verbose("IRD_Save fwrite gamename_lenght\n");
	fwrite(&ird->GameName_lenght	, sizeof(u8)  , 1, irdu);
	
	print_verbose("IRD_Save fwrite gamename = ");
	fwrite(ird->GameName			, sizeof(char), ird->GameName_lenght, irdu);
	print_verbose("%s\n", ird->GameName);
	print_verbose("IRD_Save fwrite updateversion = ");
	fwrite(ird->UpdateVersion	, sizeof(char), 4, irdu);
	print_verbose("%s\n", ird->UpdateVersion);
	print_verbose("IRD_Save fwrite gameversion = ");
	fwrite(ird->gameVersion		, sizeof(char), 5, irdu);
	print_verbose("%s\n", ird->gameVersion);
	print_verbose("IRD_Save fwrite appversion = ");
	fwrite(ird->AppVersion		, sizeof(char), 5, irdu);
	print_verbose("%s\n", ird->AppVersion);
	
	if(ird->Version == 7) {
		print_verbose("IRD_Load fread ID = ");
		fwrite(&ird->ID, sizeof(u32) , 1, irdu);
		ird->ID = ENDIAN_SWAP(ird->ID);
		print_verbose("%d\n",  ird->ID);
	}
	
	print_verbose("IRD_Save fwrite headerlenght = ");
	ird->HeaderLenght = ENDIAN_SWAP(ird->HeaderLenght);
	fwrite(&ird->HeaderLenght		, sizeof(u32) , 1, irdu);
	print_verbose("%d\n",  ird->HeaderLenght);
	
	print_verbose("IRD_Save fwrite iso header\n");
	fwrite(ird->Header			, sizeof(u8) , ird->HeaderLenght, irdu);
	
	print_verbose("IRD_Save fwrite iso footerlenght = ");
	ird->FooterLenght = ENDIAN_SWAP(ird->FooterLenght);
	fwrite(&ird->FooterLenght		, sizeof(u32) , 1, irdu);
	print_verbose("%X\n", ird->FooterLenght);
	
	print_verbose("IRD_Save fwrite footer\n");
	fwrite(ird->Footer			, sizeof(u8) , ird->FooterLenght, irdu);
	
	print_verbose("IRD_Save fwrite regionhashesnumber = ");
	fwrite(&ird->RegionHashesNumber	, sizeof(u8) , 1, irdu);
	print_verbose("%d\n",  ird->RegionHashesNumber);
	
	for(i=0; i<ird->RegionHashesNumber; i++) {
		print_verbose("IRD_Save fwrite region #%d\n", i+1);
		fwrite(ird->RegionHashes[i], sizeof(u8), 0x10, irdu);
	}
	
	print_verbose("IRD_Save fwrite filehashesnumber\n");
	ird->FileHashesNumber = ENDIAN_SWAP(ird->FileHashesNumber);
	fwrite(&ird->FileHashesNumber	, sizeof(u32) , 1, irdu);
	
	for(i=0; i<ird->FileHashesNumber; i++) {
		print_verbose("IRD_Save fwrite filehashes.sector #%d\n", i+1);
		ird->FileHashes[i].Sector =  ENDIAN_SWAP(ird->FileHashes[i].Sector);
		fwrite(&ird->FileHashes[i].Sector, sizeof(u64), 1, irdu);
		print_verbose("IRD_Save fwrite filehashes.FileHash #%d\n", i+1);
		fwrite(&ird->FileHashes[i].FileHash, sizeof(u8), 0x10, irdu);
	}
	
	print_verbose("IRD_Save fwrite extraConfig\n");
	ird->extraConfig = ENDIAN_SWAP(ird->extraConfig);
	fwrite(&ird->extraConfig, sizeof(u16), 1, irdu);
	print_verbose("IRD_Save fwrite attachments\n");
	ird->attachments = ENDIAN_SWAP(ird->attachments);
	fwrite(&ird->attachments, sizeof(u16), 1, irdu);
	
	if(ird->Version >= 9) {
		print_verbose("IRD_Load fwrite PIC\n");
		fwrite(ird->PIC  , sizeof(u8), 0x73, irdu);
	}
	
	print_verbose("IRD_Save fwrite Data1\n");
	fwrite(ird->Data1, sizeof(u8), 0x10, irdu);
	print_verbose("IRD_Save fwrite Data2\n");
	fwrite(ird->Data2, sizeof(u8), 0x10, irdu);
	
	if(ird->Version < 9) {
		print_verbose("IRD_Load fwrite PIC\n");
		fwrite(ird->PIC  , sizeof(u8), 0x73, irdu);
	}
	
	if(ird->Version > 7) {
		print_verbose("IRD_Load fread UniqueIdentifier = %X");
		ird->UniqueIdentifier = ENDIAN_SWAP(ird->UniqueIdentifier);
		fwrite(&ird->UniqueIdentifier, sizeof(u32), 1, irdu);
		print_verbose("%X\n", ird->crc); 
	}
	
	print_verbose("IRD_Save fwrite crc\n");
	ird->crc = ENDIAN_SWAP(ird->crc);
	ret = fwrite(&ird->crc  , sizeof(u32), 1, irdu);
	
	ret = SUCCESS;
error:
	print_verbose("IRD_Save fclose\n");
	FCLOSE(irdu);
	
	if( ret == SUCCESS ) {
		print_verbose("IRD_Save IRD_Compress\n");
		if( IRD_gz(COMPRESS, IRDU_PATH, IRD_PATH) == FAILED) {
			printf("Error : IRD_Load Failed to compress IRD\n");
			ret = FAILED;
		}
	}
	
	return ret;
}

#ifdef LITTLE_ENDIAN
int main()
{
	return 0;
}
#endif