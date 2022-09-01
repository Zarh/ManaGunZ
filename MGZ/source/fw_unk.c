#include <stdio.h>
#include <string.h>

#include "fw_unk.h"
#include "extern.h"

// todo : include this with offsetfinder
#define LAST_FW(x)   (x##_488C)

u8 compare(u8 ignore, char *mem, char *flag, u32 size)
{
	u32 i;
	for(i = 0; i < size; i++) {
		if((u8) flag[i] != ignore && (u8) flag[i] != (u8) mem[i]) return 0;
	}
	return 1;
}

#define MEM_LV2_SIZE 0x800000ULL
#define MEM_LV1_SIZE 0x1000000ULL

u8 *LoadLV1(u64 peek_start, u64 peek_end)
{
	disable_cancel = YES;
	u8 *memLV1 = (u8 *) malloc(MEM_LV1_SIZE);
	if(memLV1 == NULL) {
		printf("Error : cannot malloc LV1");
		return NULL;
	}
	prog_bar1_value = 0;
	
	memset(memLV1, 0, MEM_LV1_SIZE);
	
	u64 peek_size=peek_end-peek_start;
	u64 data;
	u64 i;
	for(i=peek_start ; i < peek_end; i+=0x8) {
		memset(&data, 0, 8);
		
		data = lv1peek(i);
		memcpy(&memLV1[i], &data, sizeof(u64));
		
		prog_bar1_value = (i-peek_start)*100/peek_size;
	}
	prog_bar1_value = -1;
	
	disable_cancel = NO;
	return memLV1;
}

u8 *LoadLV2(u64 peek_start, u64 peek_end)
{
	disable_cancel=YES;
	u8 *memLV2 = (u8 *) malloc(MEM_LV2_SIZE);
	if(memLV2 == NULL) {
		printf("Error : cannot malloc LV2");
		return NULL;
	}
	prog_bar1_value = 0;
	
	memset(memLV2, 0, MEM_LV2_SIZE);
	
	u64 peek_size=peek_end-peek_start;
	u64 data;
	u64 i;
	for(i=peek_start ; i < peek_end; i+=0x8) {
		memset(&data, 0, 8);

		data = lv2peek(0x8000000000000000ULL + i);
		memcpy(&memLV2[i], &data, sizeof(u64));
		
		prog_bar1_value = (i-peek_start)*100/peek_size;
	}
	prog_bar1_value = -1;
	
	disable_cancel=NO;
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

u8 is_scanned()
{
	char fw_scan[255];
	
	sprintf(fw_scan, "%s/USRDIR/sys/fw_scan.dat",  ManaGunZ_path);
	
	FILE *fp = fopen(fw_scan, "rb");
	if(!fp) return FAILED;

	u64 TEMP_FW_DATE_OFFSET=0;
	u64 TEMP_FW_DATE_1=0;
	u64 TEMP_FW_DATE_2=0;
	
	fread(&TEMP_FW_DATE_OFFSET                         , sizeof(u64), 1, fp);
	fread(&TEMP_FW_DATE_1                              , sizeof(u64), 1, fp);
	fread(&TEMP_FW_DATE_2                              , sizeof(u64), 1, fp);
	fclose(fp);


	if( FW_DATE_OFFSET == 0 || FW_DATE_1 == 0 || FW_DATE_2 == 0) {
		Delete(fw_scan);
		return FAILED;
	}
	
	if(( lv2peek(TEMP_FW_DATE_OFFSET    )==TEMP_FW_DATE_1) &&
	   ( lv2peek(TEMP_FW_DATE_OFFSET + 8)==TEMP_FW_DATE_2) )
	{
		return SUCCESS;
	}
	
	Delete(fw_scan);
	
	return FAILED;
}

u8 save_scanned()
{
	if( FW_DATE_OFFSET == 0 || FW_DATE_1 == 0 || FW_DATE_2 == 0) return FAILED;
	
	char fw_scan[255];
	
	sprintf(fw_scan, "%s/USRDIR/sys/fw_scan.dat",  ManaGunZ_path);
	
	FILE *fp = fopen(fw_scan, "wb");
	if(!fp) return FAILED;
	
	fread(&FW_DATE_OFFSET                         , sizeof(u64), 1, fp);
	fread(&FW_DATE_1                              , sizeof(u64), 1, fp);
	fread(&FW_DATE_2                              , sizeof(u64), 1, fp);
	fclose(fp);

	return SUCCESS;
}

u8 flag_ufs_sb_addr[8] = {0, 0, 0, 0, 0x19, 0x54, 0x01, 0x19};
u8 flag_htab[0x8] = {0x41, 0xDA, 0x00, 0x54, 0xE9, 0x7F, 0x00, 0xA8};
u8 flag_mmap1[0x8] = {0x88, 0x1F, 0x00, 0x99, 0x54, 0x00, 0x06, 0x3E};
u8 flag_mmap2[0x8] = {0xE8, 0xFF, 0x00, 0xE0, 0x7C, 0x08, 0x03, 0x78};
u8 flag_spe[0x8] = {0x39, 0x20, 0x00, 0x09, 0xE9, 0x43, 0x00, 0x00 };

u8 flag_offset_fix[0x20] = {0x38, 0xDE, 0x00, 0x07, 0x88, 0x1E, 0x00, 0x07, 0x2F, 0x84, 0x00, 0x01, 0x98, 0x01, 0x00, 0x73, 0x88, 0x06, 0x00, 0x01, 0x88, 0xA6, 0x00, 0x08, 0x89, 0x26, 0x00, 0x02, 0x89, 0x66, 0x00, 0x03};
u8 flag_offset_2_fix[0x10] = {0xF9, 0x1F, 0x00, 0x20, 0xF8, 0xFF, 0x00, 0x28, 0xF8, 0xDF, 0x00, 0x30, 0xF8, 0xBF, 0x00, 0x38};
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


#define MACRO_CHECK_LV2(val, diff, flag) \
	print_debug(#val); \
	memset(mem, 0, 0x1000); \
	TEMP_##val = LAST_FW(val); \
	MEM_lv2peek(TEMP_##val + (diff), mem, sizeof(flag)); \
	if(memcmp((char *) mem, (char *) flag, sizeof(flag))) { \
		print_debug("Not the same %s", #val); \
		return FAILED; \
	} \

#define MACRO_CHECK_LV1(val, diff, flag, mask) \
	print_debug(#val); \
	memset(mem, 0, 0x1000); \
	TEMP_##val = LAST_FW(val); \
	MEM_lv1peek((u64) (TEMP_##val + (diff)), (char *) mem, (u64) sizeof(flag)); \
	if(!compare((u8) mask, (char *) mem, (char *) flag, (u32) sizeof(flag))) { \
		print_debug("Not the same %s", #val); \
		return FAILED; \
	} \


u8 try_latest_fw()
{
	print_debug("try_latest_fw");
	
	u64 TEMP_TOC;
	u64 TEMP_FW_DATE_OFFSET;
	u64 TEMP_FW_DATE_1;
	u64 TEMP_FW_DATE_2;
	u64 TEMP_SYSCALL_TABLE;
	u64 TEMP_HV_START_OFFSET;
	u64 TEMP_HTAB_OFFSET;
	u64 TEMP_MMAP_OFFSET1;
	u64 TEMP_MMAP_OFFSET2;
	u64 TEMP_SPE_OFFSET;
	u64 TEMP_OFFSET_FIX;
	u64 TEMP_OFFSET_2_FIX;
	u64 TEMP_OFFSET_FIX_3C;
	u64 TEMP_OFFSET_FIX_2B17;
	u64 TEMP_OFFSET_FIX_LIC;
	u64 TEMP_OPEN_HOOK;
	u64 TEMP_BASE_ADDR;
	u64 TEMP_LV2MOUNTADDR;
	u64 TEMP_LV2MOUNTADDR_ESIZE;
	u64 TEMP_LV2MOUNTADDR_CSIZE;
	u64 TEMP_OFFSET_1_IDPS;
	u64 TEMP_OFFSET_2_IDPS;
	
	u8 mem[0x1000];
	
	//TOC
	print_debug("TOC");
	TEMP_TOC = lv2peek(0x3000ULL);
	if( TEMP_TOC != LAST_FW(TOC) ) {
		print_debug("Not the same TOC current(0x%X) != old (0x%X)", TEMP_TOC, LAST_FW(TOC));
		return FAILED;
	}
	
	print_debug("FW_DATE_OFFSET");
	TEMP_FW_DATE_OFFSET = LAST_FW(FW_DATE_OFFSET);
	TEMP_FW_DATE_1 = lv2peek(TEMP_FW_DATE_OFFSET);
	TEMP_FW_DATE_2 = lv2peek(TEMP_FW_DATE_OFFSET + 8 );
	MEM_lv2peek(TEMP_FW_DATE_OFFSET, mem, 0x10);
	
	if(memcmp((char *) &mem[0x4], (char *) "/", 1)
	|| memcmp((char *) &mem[0x7], (char *) "/", 1)
	|| memcmp((char *) &mem[0xA], (char *) " ", 1)
	|| memcmp((char *) &mem[0xD], (char *) ":", 1))
	{
		print_debug("Not the same FW_DATE_OFFSET.");
		return FAILED;
	}
	
	print_debug("SYSCALL_TABLE");
	memset(mem, 0, 0x1000);
	TEMP_SYSCALL_TABLE = LAST_FW(SYSCALL_TABLE);	
	MEM_lv2peek(TEMP_SYSCALL_TABLE, mem, 8*50);
	
	if(!memcmp((char *) &mem[8*1],  (char *) mem, 8)
	|| !memcmp((char *) &mem[8*2],  (char *) mem, 8)
	|| !memcmp((char *) &mem[8*3],  (char *) mem, 8)
	|| !memcmp((char *) &mem[8*14], (char *) mem, 8)
	||  memcmp((char *) &mem[8*16], (char *) mem, 8)
	||  memcmp((char *) &mem[8*17], (char *) mem, 8)
	|| !memcmp((char *) &mem[8*18], (char *) mem, 8)
	|| !memcmp((char *) &mem[8*19], (char *) mem, 8)
	||  memcmp((char *) &mem[8*20], (char *) mem, 8)
	|| !memcmp((char *) &mem[8*21], (char *) mem, 8)
	||  memcmp((char *) &mem[8*32], (char *) mem, 8)
	||  memcmp((char *) &mem[8*33], (char *) mem, 8)
	|| !memcmp((char *) &mem[8*41], (char *) mem, 8)
	||  memcmp((char *) &mem[8*42], (char *) mem, 8)
	|| !memcmp((char *) &mem[8*43], (char *) mem, 8))
	{
		print_debug("Not the same SYSCALL_TABLE.");
		return FAILED;
	}
	
	MACRO_CHECK_LV2(OFFSET_FIX, 0x8, flag_offset_fix);
	
	MACRO_CHECK_LV2(OFFSET_2_FIX, -0x20, flag_offset_2_fix);
	
	MACRO_CHECK_LV2(OFFSET_FIX_2B17, 0x8, flag_offset_fix_2B17);
	
	MACRO_CHECK_LV2(OFFSET_FIX_3C, -0x20, flag_offset_fix_3C);
	
	MACRO_CHECK_LV2(OPEN_HOOK, 0x2C, flag_open_hook);
	
	MACRO_CHECK_LV2(BASE_ADDR, 0, flag_base_addr);
	
	print_debug("OFFSET_FIX_LIC");
	memset(mem, 0, 0x1000);
	TEMP_OFFSET_FIX_LIC = LAST_FW(OFFSET_FIX_LIC);	
	MEM_lv2peek(TEMP_OFFSET_FIX_LIC + 0x4, mem, 0x20);
	if(memcmp((char *) mem, (char *) flag_offset_fix_lic, 0x5)
    || memcmp((char *) &mem[6], (char *) &flag_offset_fix_lic[6], 0x5)
	|| memcmp((char *) &mem[0xC], (char *) &flag_offset_fix_lic[0xC], 0x5)) 
	{	
		print_debug("Not the same OFFSET_FIX_LIC"); 
		return FAILED;
	}
	
	print_debug("OFFSET_1_IDPS");
	memset(mem, 0, 0x1000);
	TEMP_OFFSET_1_IDPS = LAST_FW(OFFSET_1_IDPS);	
	MEM_lv2peek(TEMP_OFFSET_1_IDPS, mem, 0x8);
	if(memcmp((char *) mem, (char *) flag_1_idpsoffset, 0x8) < 0 
	|| memcmp((char *) mem, (char *) flag_2_idpsoffset, 0x8) > 0 )
	{
		print_debug("Not the same OFFSET_1_IDPS"); 
		return FAILED;
	}
	
	print_debug("OFFSET_2_IDPS");
	memset(mem, 0, 0x1000);
	TEMP_OFFSET_2_IDPS = LAST_FW(OFFSET_2_IDPS);	
	MEM_lv2peek(TEMP_OFFSET_2_IDPS, mem, 0x8);
	if(memcmp((char *) mem, (char *) flag_1_idpsoffset, 0x8) < 0 
	|| memcmp((char *) mem, (char *) flag_2_idpsoffset, 0x8) > 0 )
	{
		print_debug("Not the same OFFSET_2_IDPS"); 
		return FAILED;
	}
	
	
	MACRO_CHECK_LV2(LV2MOUNTADDR, 0, flag_lv2mountaddr);
	
	TEMP_LV2MOUNTADDR_ESIZE = LAST_FW(LV2MOUNTADDR_ESIZE);
	TEMP_LV2MOUNTADDR_CSIZE = LAST_FW(LV2MOUNTADDR_CSIZE);

	MACRO_CHECK_LV1(HTAB_OFFSET, 0, flag_htab, 0xFF);
	
	MACRO_CHECK_LV1(MMAP_OFFSET1, -8, flag_mmap1, 0xFF);
	
	MACRO_CHECK_LV1(MMAP_OFFSET2, -8, flag_mmap2, 0xFF);
	
	MACRO_CHECK_LV1(SPE_OFFSET, 0, flag_spe, 0xFF);
	
	MACRO_CHECK_LV1(HV_START_OFFSET, -0xA8, flag_hv_start_offset, 0xBB);
	
	TOC=TEMP_TOC;
	FW_DATE_OFFSET=TEMP_FW_DATE_OFFSET;
	FW_DATE_1=TEMP_FW_DATE_1;
	FW_DATE_2=TEMP_FW_DATE_2;
	SYSCALL_TABLE=TEMP_SYSCALL_TABLE;
	HV_START_OFFSET=TEMP_HV_START_OFFSET;
	HTAB_OFFSET=TEMP_HTAB_OFFSET;
	MMAP_OFFSET1=TEMP_MMAP_OFFSET1;
	MMAP_OFFSET2=TEMP_MMAP_OFFSET2;
	SPE_OFFSET=TEMP_SPE_OFFSET;
	OFFSET_FIX=TEMP_OFFSET_FIX;
	OFFSET_2_FIX=TEMP_OFFSET_2_FIX;
	OFFSET_FIX_3C=TEMP_OFFSET_FIX_3C;
	OFFSET_FIX_2B17=TEMP_OFFSET_FIX_2B17;
	OFFSET_FIX_LIC=TEMP_OFFSET_FIX_LIC;
	OPEN_HOOK=TEMP_OPEN_HOOK;
	BASE_ADDR=TEMP_BASE_ADDR;
	LV2MOUNTADDR=TEMP_LV2MOUNTADDR;
	LV2MOUNTADDR_ESIZE=TEMP_LV2MOUNTADDR_ESIZE;
	LV2MOUNTADDR_CSIZE=TEMP_LV2MOUNTADDR_CSIZE;
	OFFSET_1_IDPS=TEMP_OFFSET_1_IDPS;
	OFFSET_2_IDPS=TEMP_OFFSET_2_IDPS;

	NEW_POKE_SYSCALL_ADDR = lv2peek( lv2peek(SYSCALL_TABLE + NEW_POKE_SYSCALL*8) ) + 0ULL;
	UMOUNT_SYSCALL_OFFSET = lv2peek( lv2peek(SYSCALL_TABLE + 838*8) )  + 8ULL;

	save_fw_unk();
	
	print_debug("try_latest_fw = SUCCESS");
	
	return SUCCESS;

}

u8 init_fw_unk()
{		
	if( read_fw_unk() == SUCCESS) return SUCCESS;
	if( is_scanned() == SUCCESS) return SUCCESS;
	if( try_latest_fw() == SUCCESS) return SUCCESS;
	
	print_load("New firmware, searching for the new offsets...");
	
	u8 flag = FAILED;
	
	u64 start = 0x50000ULL;
	u64 end = MEM_LV2_SIZE;
	
	print_load("Loading lv2 in memory...");
	u8 *memLV2 = LoadLV2(start, end);
	if(memLV2 == NULL) {
		return FAILED;
	}
	
	memcpy(&TOC, &memLV2[0x3000], 8);
	//TOC = reverse64(TOC);
	
	u64 n;
	print_load("Searching lv2 offsets...");
	for(n=start; n<end ; n++) {
		if(0x200000 < n && n <0x400000) {
			if(!memcmp((char *) &memLV2[n+0x4], (char *) "/", 1))
			if(!memcmp((char *) &memLV2[n+0x7], (char *) "/", 1))
			if(!memcmp((char *) &memLV2[n+0xA], (char *) " ", 1))
			if(!memcmp((char *) &memLV2[n+0xD], (char *) ":", 1))
			{
				FW_DATE_OFFSET = n;
				memcpy(&FW_DATE_1, &memLV2[n], 8);
				memcpy(&FW_DATE_2, &memLV2[n+8], 8);
			}
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
		print_load("Failed to find all offsets...");
		save_scanned();
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
	
	start = 0x280000ULL;
	end = MEM_LV1_SIZE;
	
	print_load("Loading lv1 in memory...");
	u8 *memLV1 = LoadLV1(start, end);
	if( memLV1 == NULL) {
		init_values();
		return FAILED;
	}
	
	print_load("Searching lv1 offsets...");
	for(n=start; n<end ; n++) {
	
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
		print_load("Failed to find all offsets...");
		save_scanned();
		init_values();
		return FAILED;
	}
	
	save_fw_unk();
	
	return SUCCESS;
}
