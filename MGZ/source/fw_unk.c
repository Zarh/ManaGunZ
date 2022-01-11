#include <stdio.h>
#include <string.h>

#include "fw_unk.h"

#define YES			1
#define SUCCESS		1
#define FAILED 		0

#define LV2ADDR(x) 0x8000000000000000ULL + x

extern u8 cancel;

u64 FW_DATE_OFFSET=0;
u64 FW_DATE_1=0;
u64 FW_DATE_2=0;

extern int firmware;
extern u64 TOC;
extern u64 FW_DATE_OFFSET;
extern u64 FW_DATE_1;
extern u64 FW_DATE_2;
extern u64 SYSCALL_TABLE;
extern u64 HV_START_OFFSET;
extern u64 HTAB_OFFSET;
extern u64 MMAP_OFFSET1;
extern u64 MMAP_OFFSET2;
extern u64 SPE_OFFSET;
extern u64 OFFSET_FIX;
extern u64 OFFSET_2_FIX;
extern u64 OFFSET_FIX_3C;
extern u64 OFFSET_FIX_2B17;
extern u64 OFFSET_FIX_LIC;
extern u64 OPEN_HOOK;
extern u64 BASE_ADDR;
extern u64 UMOUNT_SYSCALL_OFFSET;
extern u64 LV2MOUNTADDR;
extern u64 LV2MOUNTADDR_ESIZE;
extern u64 LV2MOUNTADDR_CSIZE;
extern u64 NEW_POKE_SYSCALL_ADDR;
extern u64 OFFSET_1_IDPS;
extern u64 OFFSET_2_IDPS;
extern u64 UFS_SB_ADDR;

extern void print_head(char *format2, ...);
extern void print_load(char *format, ...);
extern u64 lv2peek(u64 addr);
extern u64 lv1peek(u64 addr);
extern int64_t prog_bar1_value;
extern char ManaGunZ_id[10];
extern u8 SetFilePerms(char *path);
extern void Delete(char* path);

u8 compare(u8 ignore, char *mem, char *flag, u32 size)
{
	int i;
	for(i = 0; i < size; i++) {
		if((u8) flag[i] != ignore && flag[i] != mem[i]) return 0;
	}
	return 1;
}

u8 *LoadLV1()
{
	u8 *memLV1 = (u8 *) malloc(0x1000000ULL);
	if(memLV1 == NULL) {
		printf("Error : cannot malloc LV2");
		return NULL;
	}
	prog_bar1_value = 0;
	
	u64 data;
	u64 i;
	for(i=0x0ULL ; i < 0x1000000ULL; i+=0x8) {
		memset(&data, 0, 8);

		data = lv1peek(i);
		memcpy(&memLV1[i], &data, sizeof(u64));
		
		prog_bar1_value = i*100/0x1000000ULL;
		
		if(cancel==YES) {
			free(memLV1);
			memLV1=NULL;
			break;
		}
	}
	prog_bar1_value = -1;
	
	return memLV1;
}

u8 *LoadLV2()
{
	u8 *memLV2 = (u8 *) malloc(0x800000);
	if(memLV2 == NULL) {
		printf("Error : cannot malloc LV2");
		return NULL;
	}
	prog_bar1_value = 0;
	
	u64 data;
	u64 i;
	for(i=0 ; i < 0x800000ULL; i+=0x8 ) {
		memset(&data, 0, 8);

		data = lv2peek(0x8000000000000000ULL + i);
		memcpy(&memLV2[i], &data, sizeof(u64));
		
		prog_bar1_value = i*100/0x800000ULL;
		
		if(cancel==YES) {
			free(memLV2);
			memLV2=NULL;
			break;
		}
	}
	prog_bar1_value = -1;
	
	return memLV2;
}

void init_values()
{
	firmware=0;
	TOC=0;
	FW_DATE_OFFSET=0;
	FW_DATE_1=0;
	FW_DATE_2=0;
	SYSCALL_TABLE=0;
	HV_START_OFFSET=0;
	HTAB_OFFSET=0;
	MMAP_OFFSET1=0;
	MMAP_OFFSET2=0;
	SPE_OFFSET=0;
	OFFSET_FIX=0;
	OFFSET_2_FIX=0;
	OFFSET_FIX_3C=0;
	OFFSET_FIX_2B17=0;
	OFFSET_FIX_LIC=0;
	OPEN_HOOK=0;
	BASE_ADDR=0;
	UMOUNT_SYSCALL_OFFSET=0;
	LV2MOUNTADDR=0;
	LV2MOUNTADDR_ESIZE=0;
	LV2MOUNTADDR_CSIZE=0;
	NEW_POKE_SYSCALL_ADDR=0;
	OFFSET_1_IDPS=0;
	OFFSET_2_IDPS=0;	
}

void save_fw_unk()
{
	char fw_unk_path[255];
	
	sprintf(fw_unk_path, "/dev_hdd0/game/%s/USRDIR/sys/fw_unk.dat",  ManaGunZ_id);
	
	FILE *fp = fopen(fw_unk_path, "wb");
	if(!fp) return;
	
	fwrite(&TOC                                    , sizeof(u64), 1, fp);
	fwrite(&FW_DATE_OFFSET                         , sizeof(u64), 1, fp);
	fwrite(&FW_DATE_1                              , sizeof(u64), 1, fp);
	fwrite(&FW_DATE_2                              , sizeof(u64), 1, fp);
	fwrite(&SYSCALL_TABLE                          , sizeof(u64), 1, fp);
	fwrite(&HV_START_OFFSET                        , sizeof(u64), 1, fp);
	fwrite(&HTAB_OFFSET                            , sizeof(u64), 1, fp);
	fwrite(&MMAP_OFFSET1                           , sizeof(u64), 1, fp);
	fwrite(&MMAP_OFFSET2                           , sizeof(u64), 1, fp);
	fwrite(&SPE_OFFSET                             , sizeof(u64), 1, fp);
	fwrite(&OFFSET_FIX                             , sizeof(u64), 1, fp);
	fwrite(&OFFSET_2_FIX                           , sizeof(u64), 1, fp);
	fwrite(&OFFSET_FIX_3C                          , sizeof(u64), 1, fp);
	fwrite(&OFFSET_FIX_2B17                        , sizeof(u64), 1, fp);
	fwrite(&OFFSET_FIX_LIC                         , sizeof(u64), 1, fp);
	fwrite(&OPEN_HOOK                              , sizeof(u64), 1, fp);
	fwrite(&BASE_ADDR                              , sizeof(u64), 1, fp);
	fwrite(&UMOUNT_SYSCALL_OFFSET                  , sizeof(u64), 1, fp);
	fwrite(&LV2MOUNTADDR                           , sizeof(u64), 1, fp);
	fwrite(&LV2MOUNTADDR_ESIZE                     , sizeof(u64), 1, fp);
	fwrite(&LV2MOUNTADDR_CSIZE                     , sizeof(u64), 1, fp);
	fwrite(&NEW_POKE_SYSCALL_ADDR                  , sizeof(u64), 1, fp);
	fwrite(&OFFSET_1_IDPS                          , sizeof(u64), 1, fp);
	fwrite(&OFFSET_2_IDPS                          , sizeof(u64), 1, fp);
	
	fclose(fp);
	
	SetFilePerms(fw_unk_path);
	
	firmware = fw_unk;
}

u8 read_fw_unk()
{
	print_load("read_fw_unk");

	char fw_unk_path[255];
	
	sprintf(fw_unk_path, "/dev_hdd0/game/%s/USRDIR/sys/fw_unk.dat",  ManaGunZ_id);
	
	FILE *fp = fopen(fw_unk_path, "rb");
	if(!fp) return FAILED;
	
	// check size
	fseek (fp , 0 , SEEK_END);
	int file_size = ftell (fp);
	if(file_size != 24*8 ) {
		fclose(fp);
		unlink(fw_unk_path);
		return FAILED;
	}
	
	fseek(fp, 0, SEEK_SET);
	
	fread(&TOC                                    , sizeof(u64), 1, fp);
	fread(&FW_DATE_OFFSET                         , sizeof(u64), 1, fp);
	fread(&FW_DATE_1                              , sizeof(u64), 1, fp);
	fread(&FW_DATE_2                              , sizeof(u64), 1, fp);
	fread(&SYSCALL_TABLE                          , sizeof(u64), 1, fp);
	fread(&HV_START_OFFSET                        , sizeof(u64), 1, fp);
	fread(&HTAB_OFFSET                            , sizeof(u64), 1, fp);
	fread(&MMAP_OFFSET1                           , sizeof(u64), 1, fp);
	fread(&MMAP_OFFSET2                           , sizeof(u64), 1, fp);
	fread(&SPE_OFFSET                             , sizeof(u64), 1, fp);
	fread(&OFFSET_FIX                             , sizeof(u64), 1, fp);
	fread(&OFFSET_2_FIX                           , sizeof(u64), 1, fp);
	fread(&OFFSET_FIX_3C                          , sizeof(u64), 1, fp);
	fread(&OFFSET_FIX_2B17                        , sizeof(u64), 1, fp);
	fread(&OFFSET_FIX_LIC                         , sizeof(u64), 1, fp);
	fread(&OPEN_HOOK                              , sizeof(u64), 1, fp);
	fread(&BASE_ADDR                              , sizeof(u64), 1, fp);
	fread(&UMOUNT_SYSCALL_OFFSET                  , sizeof(u64), 1, fp);
	fread(&LV2MOUNTADDR                           , sizeof(u64), 1, fp);
	fread(&LV2MOUNTADDR_ESIZE                     , sizeof(u64), 1, fp);
	fread(&LV2MOUNTADDR_CSIZE                     , sizeof(u64), 1, fp);
	fread(&NEW_POKE_SYSCALL_ADDR                  , sizeof(u64), 1, fp);
	fread(&OFFSET_1_IDPS                          , sizeof(u64), 1, fp);
	fread(&OFFSET_2_IDPS                          , sizeof(u64), 1, fp);
	
	fclose(fp);

	if(( lv2peek(FW_DATE_OFFSET    )==FW_DATE_1) &&
	   ( lv2peek(FW_DATE_OFFSET + 8)==FW_DATE_2) )
	{
		firmware = fw_unk;
		return SUCCESS;
	}
	
	Delete(fw_unk_path);
	
	init_values();
	return FAILED;
}

u8 init_fw_unk()
{		
	if( read_fw_unk() == SUCCESS) return SUCCESS;
	
	print_load("New firmware ! Please wait while MGZ search for the new offsets...");
	
	u8 flag_ufs_sb_addr[8] = {0, 0, 0, 0, 0x19, 0x54, 0x01, 0x19};
	u8 flag_htab[0x8] = {0x41, 0xDA, 0x00, 0x54, 0xE9, 0x7F, 0x00, 0xA8};
	u8 flag_mmap1[0x8] = {0x88, 0x1F, 0x00, 0x99, 0x54, 0x00, 0x06, 0x3E};
	u8 flag_mmap2[0x8] = {0xE8, 0xFF, 0x00, 0xE0, 0x7C, 0x08, 0x03, 0x78};
	u8 flag_spe[0x8] = {0x39, 0x20, 0x00, 0x09, 0xE9, 0x43, 0x00, 0x00 };

	u8 flag_offset_fix[0x20] = {0x38, 0xDE, 0x00, 0x07, 0x88, 0x1E, 0x00, 0x07, 0x2F, 0x84, 0x00, 0x01, 0x98, 0x01, 0x00, 0x73, 0x88, 0x06, 0x00, 0x01, 0x88, 0xA6, 0x00, 0x08, 0x89, 0x26, 0x00, 0x02, 0x89, 0x66, 0x00, 0x03};
	u8 flag_offset_2_fix[0x20] = {0xF9, 0x1F, 0x00, 0x20, 0xF8, 0xFF, 0x00, 0x28, 0xF8, 0xDF, 0x00, 0x30, 0xF8, 0xBF, 0x00, 0x38, 0xFB, 0xBF, 0x00, 0x40, 0x4B, 0xFA, 0x97, 0x45, 0x54, 0x63, 0x06, 0x3E, 0x2F, 0x83, 0x00, 0x00};
	u8 flag_offset_fix_2B17[0x20] = {0x4E, 0x80, 0x00, 0x20, 0x3C, 0x80, 0x10, 0x50, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0x78, 0x84, 0x07, 0xC6, 0xFB, 0xE1, 0x00, 0x88, 0x64, 0x84, 0x03, 0x00, 0x7C, 0x7F, 0x1B, 0x78};
	u8 flag_offset_fix_lic[0x20] = {0x2F, 0x83, 0x00, 0x00, 0x3B, 0xFC, 0x00, 0x6C, 0x41, 0x9E, 0x00, 0x60, 0x38, 0x00, 0x00, 0x02, 0x3B, 0xE0, 0x00, 0x00, 0x90, 0x1C, 0x00, 0x6C, 0x4B, 0xFF, 0xFF, 0x38, 0x2F, 0xA7, 0x00, 0x00};
	u8 flag_offset_fix_3C[0x20] = {0x4B, 0xFF, 0xFF, 0xD8, 0xE8, 0x03, 0x01, 0xA8, 0x7C, 0x09, 0xFE, 0x76, 0x7D, 0x23, 0x02, 0x78, 0x7C, 0x69, 0x18, 0x50, 0x38, 0x63, 0xFF, 0xFF, 0x78, 0x63, 0x0F, 0xE0, 0x4E, 0x80, 0x00, 0x20};
	u8 flag_open_hook[0x30] = {0x2B, 0xA3, 0x04, 0x20, 0x3F, 0xE0, 0x80, 0x01, 0x63, 0xFF, 0x00, 0x34, 0x40, 0x9D, 0x00, 0x2C, 0xE8, 0x01, 0x00, 0xB0, 0x7F, 0xE3, 0x07, 0xB4, 0xEB, 0x41, 0x00, 0x70, 0xEB, 0x61, 0x00, 0x78, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0x81, 0x00, 0x80, 0xEB, 0xA1, 0x00, 0x88, 0xEB, 0xE1, 0x00, 0x98};
	u8 flag_base_addr[0x20]	= {0x42, 0x61, 0x63, 0x6B, 0x74, 0x72, 0x61, 0x63, 0x65, 0x20, 0x49, 0x6E, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x3A, 0x0A, 0x00, 0x20, 0x20, 0x2D, 0x20, 0x30, 0x78, 0x25, 0x30};
	u8 flag_lv2mountaddr[0x20] = {0x43, 0x45, 0x4C, 0x4C, 0x5F, 0x46, 0x53, 0x5F, 0x41, 0x44, 0x4D, 0x49, 0x4E, 0x46, 0x53, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	u8 flag_1_idpsoffset[8] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00}; 
	u8 flag_2_idpsoffset[8] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x90, 0x00, 0x00};
	
	u8 flag_hv_start_offset[0xD0] = {
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		
		0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB, 0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,
		0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB, 0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,
		0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB, 0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,
		0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB, 0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,
		0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB, 0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,
	
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,
		0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,
		0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB, 0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,
		0xBB,0xBB,0xBB,0xBB,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	};
	
	u8 flag = FAILED;
	
	u32 size = 0x800000;
	
	print_load("Loading lv2 in memory...");
	u8 *memLV2 = LoadLV2();
	if(memLV2 == NULL) {
		return FAILED;
	}
	
	memcpy(&TOC, &memLV2[0x3000], 8);
	//TOC = reverse64(TOC);
	
	u64 n;
	
	print_load("Searching lv2 offsets...");
	for(n=0; n<size ; n++) {
		if(!memcmp((char *) &memLV2[n+0x4], (char *) "/", 1))
		if(!memcmp((char *) &memLV2[n+0x7], (char *) "/", 1))
		if(!memcmp((char *) &memLV2[n+0xA], (char *) " ", 1))
		if(!memcmp((char *) &memLV2[n+0xD], (char *) ":", 1))
		{
			FW_DATE_OFFSET = n;
			memcpy(&FW_DATE_1, &memLV2[n], 8);
			memcpy(&FW_DATE_2, &memLV2[n+8], 8);
			//FW_DATE_1 = reverse64(FW_DATE_1);
			//FW_DATE_2 = reverse64(FW_DATE_2);
		}
		if(!memcmp((char *) &memLV2[n], (char *) flag_ufs_sb_addr, 0x8)) {
			UFS_SB_ADDR = n - 0x558;
		}
		if(0x50000 < n && n <0x80000) {
			if(!memcmp((char *) &memLV2[n], (char *) flag_offset_fix, 0x20)) {
				OFFSET_FIX = n - 0x8;
			}
			if(!memcmp((char *) &memLV2[n], (char *) flag_offset_2_fix, 0x10)) {
				OFFSET_2_FIX = n + 0x20;
			}
			if(!memcmp((char *) &memLV2[n], (char *) flag_offset_fix_lic, 0x5)) {
				if(!memcmp((char *) &memLV2[n+6], (char *) &flag_offset_fix_lic[6], 0x5)) {
					if(!memcmp((char *) &memLV2[n+0xC], (char *) &flag_offset_fix_lic[0xC], 0x5)) {
						OFFSET_FIX_LIC = n - 0x4;
					}
				}
			}
		}						  
		if(0x200000 < n && n <0x400000) {
			if(!memcmp((char *) &memLV2[n], (char *) flag_offset_fix_2B17, 0x20)) {
				OFFSET_FIX_2B17 = n - 0x8;
			}
			if(!memcmp((char *) &memLV2[n], (char *) flag_offset_fix_3C, 0x20)) {
				OFFSET_FIX_3C = n + 0x20;
			}
			if(!memcmp((char *) &memLV2[n], (char *) flag_open_hook, 0x30)) {
				OPEN_HOOK = n - 0x2C;
			}
			if(!memcmp((char *) &memLV2[n], (char *) flag_base_addr, 0x20)) {
				BASE_ADDR = n;
			}
		}
		if(0x300000 < n && n <0x400000) {
			if(n-(n>>4)*0x10 == 0 || n-(n>>4)*0x10 == 8)
			if(memcmp((char *) &memLV2[n +8*1], (char *) &memLV2[n], 8))
			if(memcmp((char *) &memLV2[n +8*2], (char *) &memLV2[n], 8))
			if(memcmp((char *) &memLV2[n +8*3], (char *) &memLV2[n], 8))
			if(memcmp((char *) &memLV2[n +8*14], (char *) &memLV2[n], 8))
			//if(!memcmp((char *) &memLV2[n +8*15], (char *) &memLV2[n], 8))
			if(!memcmp((char *) &memLV2[n +8*16], (char *) &memLV2[n], 8))
			if(!memcmp((char *) &memLV2[n +8*17], (char *) &memLV2[n], 8))
			if(memcmp((char *) &memLV2[n +8*18], (char *) &memLV2[n], 8))
			if(memcmp((char *) &memLV2[n +8*19], (char *) &memLV2[n], 8))
			if(!memcmp((char *) &memLV2[n +8*20], (char *) &memLV2[n], 8))
			if(memcmp((char *) &memLV2[n +8*21], (char *) &memLV2[n], 8))
			if(!memcmp((char *) &memLV2[n +8*32], (char *) &memLV2[n], 8))
			if(!memcmp((char *) &memLV2[n +8*33], (char *) &memLV2[n], 8))
			if(memcmp((char *) &memLV2[n +8*41], (char *) &memLV2[n], 8))
			if(!memcmp((char *) &memLV2[n +8*42], (char *) &memLV2[n], 8))
			if(memcmp((char *) &memLV2[n +8*43], (char *) &memLV2[n], 8))
			{
				SYSCALL_TABLE = n;
			}
		}
		if(0x350000 < n && n <0x450000) {
			if(memcmp((char *) &memLV2[n], (char *) flag_1_idpsoffset, 0x8) > 0) 
			if(memcmp((char *) &memLV2[n], (char *) flag_2_idpsoffset, 0x8) < 0) {
				OFFSET_1_IDPS = n;
			}
		}
		if(0x450000 < n && n <0x4A0000) {
			if(memcmp((char *) &memLV2[n], (char *) flag_1_idpsoffset, 0x8) > 0) 
			if(memcmp((char *) &memLV2[n], (char *) flag_2_idpsoffset, 0x8) < 0) {
				OFFSET_2_IDPS = n;
			}
		}
		if(0x400000 < n && n <0x500000) {
			if(!memcmp((char *) &memLV2[n], (char *) flag_lv2mountaddr, 0x20)) {
				LV2MOUNTADDR = n;
				u64 i;
				for(i=0x70; i<0x120; i++) {
					if(!memcmp((char *) &memLV2[n+i], (char *) flag_lv2mountaddr, 0x8))  {
						LV2MOUNTADDR_ESIZE = i;
						LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_ESIZE - 0x10;
					}
				}
			}
		}
		
		if(LV2MOUNTADDR
		&& LV2MOUNTADDR_ESIZE
		&& LV2MOUNTADDR_CSIZE
		&& OFFSET_2_IDPS
		&& OFFSET_1_IDPS
		&& SYSCALL_TABLE
		&& BASE_ADDR
		&& OPEN_HOOK
		&& OFFSET_FIX_3C
		&& OFFSET_FIX_2B17
		&& OFFSET_FIX_LIC
		&& OFFSET_2_FIX
		&& OFFSET_FIX
		&& FW_DATE_OFFSET
		&& UFS_SB_ADDR) {
			flag = SUCCESS;	
			break;
		}
		
	}
	free(memLV2);
	
	if(flag == FAILED) {
		print_load("Error : can't find all offsets...");
		init_values();
		return FAILED;
	} else {
		flag = FAILED;
	}
	
	TOC                      = LV2ADDR(TOC                    );
	FW_DATE_OFFSET           = LV2ADDR(FW_DATE_OFFSET         );
	SYSCALL_TABLE            = LV2ADDR(SYSCALL_TABLE          );
	OPEN_HOOK                = LV2ADDR(OPEN_HOOK              );
	BASE_ADDR                = LV2ADDR(BASE_ADDR              );
	LV2MOUNTADDR             = LV2ADDR(LV2MOUNTADDR           );
	OFFSET_1_IDPS            = LV2ADDR(OFFSET_1_IDPS          );
	OFFSET_2_IDPS            = LV2ADDR(OFFSET_2_IDPS          );
	UFS_SB_ADDR              = LV2ADDR(UFS_SB_ADDR            );
	
	NEW_POKE_SYSCALL_ADDR = lv2peek( lv2peek(SYSCALL_TABLE + NEW_POKE_SYSCALL*8) ) + 0ULL;
	UMOUNT_SYSCALL_OFFSET = lv2peek( lv2peek(SYSCALL_TABLE + 838*8) )  + 8ULL;
	
	print_load("Loading lv1 in memory...");
	u8 *memLV1 = LoadLV1();
	if( memLV1 == NULL) {
		init_values();
		return FAILED;
	}
	
	print_load("Searching lv1 offsets...");
	size=0x1000000;
	for(n=0x280000; n<size ; n++) {
	
		if(compare(0xFF, (char *) &memLV1[n], (char *) flag_htab, sizeof(flag_htab))){
			HTAB_OFFSET = n;
		}
		if(compare(0xFF, (char *) &memLV1[n], (char *) flag_mmap1, sizeof(flag_mmap1))){
			MMAP_OFFSET1 = n+8;
		}
		if(compare(0xFF, (char *) &memLV1[n], (char *) flag_mmap2, sizeof(flag_mmap2))){
			MMAP_OFFSET2 = n+8;
		}
		if(compare(0xFF, (char *) &memLV1[n], (char *) flag_spe, sizeof(flag_spe))){
			SPE_OFFSET = n;
		}
		
		if(compare(0xBB, (char *) &memLV1[n], (char *) flag_hv_start_offset, sizeof(flag_hv_start_offset))) {
			HV_START_OFFSET = n+0xA8;
		}

		if(HV_START_OFFSET
		&& HTAB_OFFSET 
		&& MMAP_OFFSET1
		&& MMAP_OFFSET2
		&& SPE_OFFSET ) {
			flag = SUCCESS;
			break;
		}
	}
	free(memLV1);
	
	if(flag == FAILED) {
		init_values();
		return FAILED;
	}
	
	save_fw_unk();
	
	return SUCCESS;
}


