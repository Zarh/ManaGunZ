#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <dirent.h>

#define SWAP16(x) ((((u16)(x))>>8) | ((x) << 8))

typedef uint8_t		u8;
typedef uint16_t 	u16;
typedef uint32_t	u32;
typedef uint64_t 	u64;

u64 reverse64(u64 x) {

	x = (x & 0x00000000FFFFFFFFULL) << 32 | (x & 0xFFFFFFFF00000000ULL) >> 32;
	x = (x & 0x0000FFFF0000FFFFULL) << 16 | (x & 0xFFFF0000FFFF0000ULL) >> 16;
	x = (x & 0x00FF00FF00FF00FFULL) << 8  | (x & 0xFF00FF00FF00FF00ULL) >> 8 ;
	return x;
}

int main()
{	
	char ELF[64];
	char str[255];
	FILE *elf;
	FILE *sym;
	
	printf("Searching offsets...\n");
	
	DIR *d;
	struct dirent* ent = NULL;
	
	sym = fopen("symbols.h", "w");

	fputs("#ifndef __PS2EMU_SYMBOLS_H_S__\n", sym);
	fputs("#define __PS2EMU_SYMBOLS_H_S__\n\n", sym);
	
// ps2_emu
	
	fputs("#ifdef PS2HWEMU\n\n", sym);
	
	fputs("\t#define DATA_TOC_OFFSET              -0x7358\n", sym);
	fputs("\t#define DATA_SUBTOC_OFFSET           0x20\n", sym);
	fputs("\t#define LPAR_SUBTOC_OFFSET           0x18\n", sym);
	fputs("\t#define FILESZ_TOC_OFFSET            -0x63E0\n", sym);
	
	fputs("\n", sym);
	
	d = opendir("ps2emu");
	if(d== NULL) {
		printf("Directory ps2emu not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(ELF, "ps2emu/%s/ps2_emu.elf", ent->d_name);
		
		elf=fopen(ELF, "rb");
		if(elf==NULL) {
			printf("Error : cannot open the %s\n", ELF);
			return 0;
		}
		
		fseek (elf , 0 , SEEK_END);
		u32 elf_size = ftell (elf);
		fseek(elf, 0, SEEK_SET);
		
		char *elf_data = (char *) malloc(elf_size);	
		if(elf_data == NULL) {
			printf("Error : cannot malloc %s", ELF);
			free(elf_data);
			fclose(elf);
			return 0;
		}
		
		fread(elf_data, elf_size, 1, elf);
		fclose(elf);
		
		sprintf(str, "\t#ifdef FIRMWARE_%s\n", ent->d_name); fputs(str, sym);
		
		u64 DISC_SIZE_OFFSET=0;
		u64 DISC_TYPE_OFFSET=0;
		
		u64 TOC=0;

		u64 cdvd_send_atapi_command_symbol=0;

		u64 ufs_open_symbol=0;
		u64 ufs_close_symbol=0;
		u64 ufs_read_symbol=0;
		u64 ufs_write_symbol=0;
		u64 ufs_fstat_symbol=0;

		u64 zeroalloc_symbol=0;
		u64 malloc_symbol=0;
		u64 free_symbol=0;
		
		u64 memcpy_symbol=0;
		u64 memset_symbol=0;
		u64 strcpy_symbol=0;
		u64 strcat_symbol=0;
		u64 strlen_symbol=0;
				
		u64 vuart_read_symbol=0;
		u64 vuart_write_symbol=0;

		u64 ps2_disc_auth_symbol=0;
		u64 ps2_disc_auth_caller_symbol=0;

		u64 overwritten_symbol=0;
		
		u8 DISC_SIZE_OFFSET_FLAG[0x10] = {0xE8, 0xFD, 0x00, 0x20, 0x83, 0xA7, 0x00, 0x00, 0x39, 0x5D, 0x00, 0x01, 0x91, 0x56, 0x00, 0x00};
		u8 DISC_TYPE_OFFSET_FLAG[0x10] = {0x38, 0x00, 0x00, 0x2B, 0x9B, 0x81, 0x00, 0x93, 0x7B, 0xEB, 0x46, 0x02, 0x9A, 0xE1, 0x00, 0x94};
		
		u8 cdvd_send_atapi_command_symbol_FLAG[0x10] = {0xF8, 0x21, 0xFF, 0x51, 0x7D, 0x68, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0x88, 0x7C, 0x9B, 0x23, 0x78};

		u8 ufs_open_symbol_FLAG[0x10] = {0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x00, 0x90, 0x7C, 0x98, 0x23, 0x78};
		u8 ufs_close_symbol_FLAG[0x10] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x6B, 0x1B, 0x78};
		u8 ufs_read_symbol_FLAG[0x20] = {0x00, 0x09, 0x00, 0x01, 0x80, 0x08, 0x00, 0x00, 0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0x7C, 0x8A, 0x23, 0x78, 0xFB, 0xE1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0x90, 0x7C, 0x6B, 0x1B, 0x78}; //+8
		u8 ufs_write_symbol_FLAG[0x20] = {0x00, 0x09, 0x00, 0x01, 0x80, 0x01, 0x00, 0x00, 0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0x7C, 0x8A, 0x23, 0x78, 0xFB, 0xE1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0x90, 0x7C, 0x6B, 0x1B, 0x78}; //+8
		u8 ufs_fstat_symbol_FLAG[0x10] = {0x7C, 0x88, 0x23, 0x78, 0xE9, 0x22, 0x9C, 0x18, 0x7C, 0x6A, 0x1B, 0x78, 0x38, 0x80, 0x00, 0x40};

		u8 zeroalloc_symbol_FLAG[0x20] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x7C, 0x7D, 0x1B, 0x78, 0x4B, 0xFF, 0xFF, 0x01, 0x7C, 0x7C, 0x1B, 0x78};
		u8 malloc_symbol_FLAG[0x20] = {0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0x90, 0x7C, 0x7F, 0x1B, 0x78, 0xE9, 0x22, 0xCD, 0x40, 0xE8, 0x09, 0x00, 0x00, 0x2F, 0xA0, 0x00, 0x00};
		u8 free_symbol_FLAG[0x10] = {0xF8, 0x21, 0xFF, 0x91, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x00, 0x80, 0x48, 0x00, 0x1B, 0xD5};
		
		u8 memcpy_symbol_FLAG[0x10] = {0x7F, 0xA3, 0x20, 0x00, 0x7C, 0x8A, 0x23, 0x78, 0x4D, 0x9E, 0x00, 0x20, 0x7C, 0x24, 0x18, 0x40};
		u8 memset_symbol_FLAG[0x10] = {0x2B, 0xA5, 0x00, 0x07, 0x78, 0x84, 0x06, 0x20, 0x7C, 0x69, 0x1B, 0x78, 0x7C, 0xC3, 0x2A, 0x14};
		u8 strcpy_symbol_FLAG[0x10] = {0x7C, 0x69, 0x1B, 0x78, 0x88, 0x04, 0x00, 0x00, 0x38, 0x84, 0x00, 0x01, 0x2F, 0xA0, 0x00, 0x00};
		u8 strcat_symbol_FLAG[0x10] = {0x7C, 0x69, 0x1B, 0x78, 0x88, 0x03, 0x00, 0x00, 0x48, 0x00, 0x00, 0x08, 0x8C, 0x09, 0x00, 0x01};
		u8 strlen_symbol_FLAG[0x10] = {0x7C, 0x69, 0x1B, 0x78, 0x88, 0x09, 0x00, 0x00, 0x48, 0x00, 0x00, 0x08, 0x8C, 0x03, 0x00, 0x01};
		
		u8 vuart_read_symbol_FLAG[0x20] = {0x00, 0x09, 0x00, 0x01, 0x80, 0x03, 0x00, 0x00, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7D, 0x1B, 0x78, 0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x83, 0x23, 0x78}; //+8
		u8 vuart_write_symbol_FLAG[0x20] = {0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7D, 0x1B, 0x78, 0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x83, 0x23, 0x78}; //+8

		u8 ps2_disc_auth_symbol_FLAG[0x10] = {0xF8, 0x21, 0xFE, 0xE1, 0x7C, 0xE8, 0x02, 0xA6, 0xFB, 0x21, 0x00, 0xE8, 0x7C, 0x79, 0x1B, 0x78};
		u8 ps2_disc_auth_caller_symbol_FLAG[0x10] = {0x38, 0xC0, 0xFF, 0xFF, 0x7C, 0xE8, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x81, 0x78, 0xC5, 0x00, 0x20};

		u8 overwritten_symbol_FLAG[0x10] = {0x7D, 0x80, 0x00, 0x26, 0xE8, 0x62, 0x8D, 0x68, 0xF8, 0x21, 0xFE, 0xE1, 0xFA, 0xA1, 0x00, 0xC8};
		
		u64 n, i;
		
		for(n=0; n < elf_size ; n++) {
			
			u64 value = 0;
			
			memcpy(&value, &elf_data[n], 8);
			value = reverse64(value);
			
			if(TOC==0)
			if( 0 < value && value < elf_size) {
				for(i=0; i<=30; i++) {
					if(!memcmp((char *) &elf_data[n], (char *) &elf_data[n+0x18*i], 8)) 
					{
						if(i==30) TOC = value;
					} else break;
				}
			}
			
			if(DISC_SIZE_OFFSET==0)
			if(!memcmp((char *) &elf_data[n], (char *) DISC_SIZE_OFFSET_FLAG, 0x10)) {
				DISC_SIZE_OFFSET = n - 0x10000;
			}
			if(DISC_TYPE_OFFSET==0)
			if(!memcmp((char *) &elf_data[n], (char *) DISC_TYPE_OFFSET_FLAG, 0x10)) {
				DISC_TYPE_OFFSET = n - 0x10000;
			}
			if(cdvd_send_atapi_command_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) cdvd_send_atapi_command_symbol_FLAG, 0x10)) {
				cdvd_send_atapi_command_symbol = n - 0x10000;
			}
			if(ufs_open_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_open_symbol_FLAG, 0x10)) {
				ufs_open_symbol = n - 0x10000;
			}
			if(ufs_close_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_close_symbol_FLAG, 0x10)) {
				ufs_close_symbol = n - 0x10000;
			}
			if(ufs_read_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_read_symbol_FLAG, 0x20)) {
				ufs_read_symbol = n + 8 - 0x10000;
			}
			if(ufs_write_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_write_symbol_FLAG, 0x20)) {
				ufs_write_symbol = n + 8 - 0x10000;
			}
			if(ufs_fstat_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_fstat_symbol_FLAG, 0x10)) {
				ufs_fstat_symbol = n - 0x10000;
			}
			if(zeroalloc_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) zeroalloc_symbol_FLAG, 0x20)) {
				zeroalloc_symbol = n - 0x10000;
			}
			if(malloc_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) malloc_symbol_FLAG, 0x20)) {
				malloc_symbol = n - 0x10000;
			}
			if(free_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) free_symbol_FLAG, 0x10)) {
				free_symbol = n - 0x10000;
			}
			if(memcpy_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) memcpy_symbol_FLAG, 0x10)) {
				memcpy_symbol = n - 0x10000;
			}
			if(memset_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) memset_symbol_FLAG, 0x10)) {
				memset_symbol = n - 0x10000;
			}
			if(strcpy_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) strcpy_symbol_FLAG, 0x10)) {
				strcpy_symbol = n - 0x10000;
			}
			if(strcat_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) strcat_symbol_FLAG, 0x10)) {
				strcat_symbol = n - 0x10000;
			}
			if(strlen_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) strlen_symbol_FLAG, 0x10)) {
				strlen_symbol = n - 0x10000;
			}
			if(vuart_read_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) vuart_read_symbol_FLAG, 0x20)) {
				vuart_read_symbol = n + 8 - 0x10000;
			}
			if(vuart_write_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) vuart_write_symbol_FLAG, 0x20)) {
				vuart_write_symbol = n + 8 - 0x10000;
			}
			if(ps2_disc_auth_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ps2_disc_auth_symbol_FLAG, 0x10)) {
				ps2_disc_auth_symbol = n - 0x10000;
			}
			if(ps2_disc_auth_caller_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ps2_disc_auth_caller_symbol_FLAG, 0x10)) {
				ps2_disc_auth_caller_symbol = n - 0x10000;
			}
			if(overwritten_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) overwritten_symbol_FLAG, 0x10)) {
				overwritten_symbol = n - 0x10000;
			}
			
			if(TOC)
			if(DISC_SIZE_OFFSET)
			if(DISC_TYPE_OFFSET)
			if(cdvd_send_atapi_command_symbol)
			if(ufs_open_symbol)
			if(ufs_close_symbol)
			if(ufs_read_symbol)
			if(ufs_write_symbol)
			if(ufs_fstat_symbol)
			if(zeroalloc_symbol)
			if(malloc_symbol)
			if(free_symbol)
			if(memcpy_symbol)
			if(memset_symbol)
			if(strcpy_symbol)
			if(strcat_symbol)
			if(strlen_symbol)
			if(vuart_read_symbol)
			if(vuart_write_symbol)
			if(ps2_disc_auth_symbol)
			if(ps2_disc_auth_caller_symbol)
			if(overwritten_symbol)
			break;
			
		}

		sprintf(str, "\t\t#define TOC                                      0x%llX\n", TOC); fputs(str, sym);
		sprintf(str, "\t\t#define DISC_SIZE_OFFSET                         0x%llX\n", DISC_SIZE_OFFSET); fputs(str, sym);
		sprintf(str, "\t\t#define DISC_TYPE_OFFSET                         0x%llX\n", DISC_TYPE_OFFSET); fputs(str, sym);
		sprintf(str, "\t\t#define cdvd_send_atapi_command_symbol           0x%llX\n", cdvd_send_atapi_command_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_open_symbol                          0x%llX\n", ufs_open_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_close_symbol                         0x%llX\n", ufs_close_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_read_symbol                          0x%llX\n", ufs_read_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_write_symbol                         0x%llX\n", ufs_write_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_fstat_symbol                         0x%llX\n", ufs_fstat_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define zeroalloc_symbol                         0x%llX\n", zeroalloc_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define malloc_symbol                            0x%llX\n", malloc_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define free_symbol                              0x%llX\n", free_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define memcpy_symbol                            0x%llX\n", memcpy_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define memset_symbol                            0x%llX\n", memset_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define strcpy_symbol                            0x%llX\n", strcpy_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define strcat_symbol                            0x%llX\n", strcat_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define strlen_symbol                            0x%llX\n", strlen_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define vuart_read_symbol                        0x%llX\n", vuart_read_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define vuart_write_symbol                       0x%llX\n", vuart_write_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ps2_disc_auth_symbol                     0x%llX\n", ps2_disc_auth_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ps2_disc_auth_caller_symbol              0x%llX\n", ps2_disc_auth_caller_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define overwritten_symbol                       0x%llX\n", overwritten_symbol); fputs(str, sym);
		
		fputs("\t\t#define stage1_addr                              overwritten_symbol\n", sym);
		fputs("\t\t#define stage2_addr                              0x021f0000\n", sym);
		
		fputs("\t#endif /* FIRMWARE */\n\n", sym);
		
		free(elf_data);
	}
	closedir(d);
	
	fputs("#endif /* PS2HWEMU */\n\n", sym);
	
// ps2_gxemu
	
	fputs("#ifdef PS2GXEMU\n\n", sym);
	fputs("\t#define DATA_TOC_OFFSET             -0x5B00\n", sym);
	fputs("\t#define LPAR_TOC_OFFSET            -0x5BC8\n", sym);
	fputs("\t#define FILESZ_TOC_OFFSET           -0xE68\n\n", sym);
	
	d = opendir("ps2emu");
	if(d== NULL) {
		printf("Directory ps2emu not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(ELF, "ps2emu/%s/ps2_gxemu.elf", ent->d_name);
		
		elf=fopen(ELF, "rb");
		if(elf==NULL) {
			printf("Error : cannot open the %s\n", ELF);
			return 0;
		}
		
		fseek (elf , 0 , SEEK_END);
		u32 elf_size = ftell (elf);
		fseek(elf, 0, SEEK_SET);
		
		char *elf_data = (char *) malloc(elf_size);	
		if(elf_data == NULL) {
			printf("Error : cannot malloc %s", ELF);
			free(elf_data);
			fclose(elf);
			return 0;
		}
		
		fread(elf_data, elf_size, 1, elf);
		fclose(elf);
		
		sprintf(str, "\t#ifdef FIRMWARE_%s\n", ent->d_name); fputs(str, sym);
		
		u64 TOC=0;
		u64 cdvd_read_symbol=0;
		u64 cdvd_send_atapi_command_symbol=0;
		u64 cdvd_send_device_command_symbol=0;
		u64 ufs_open_symbol=0;
		u64 ufs_close_symbol=0;
		u64 ufs_read_symbol=0;
		u64 ufs_write_symbol=0;
		u64 ufs_fstat_symbol=0;
		u64 zeroalloc_symbol=0;
		u64 malloc_symbol=0;
		u64 free_symbol=0;
		u64 memcpy_symbol=0;
		u64 memset_symbol=0;
		u64 strcpy_symbol=0;
		u64 strcat_symbol=0;
		u64 strlen_symbol=0;
		u64 vuart_read_symbol=0;
		u64 vuart_write_symbol=0;
		u64 ps2_disc_auth_symbol=0;
		u64 ps2_disc_auth_caller_symbol=0;
		u64 overwritten_symbol=0;
		u64 stage2_addr=0;
		
		u8 cdvd_read_symbol_FLAG[0x10] = {0x2B, 0x84, 0xFF, 0xFF, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xA1, 0x00, 0x78};
		u8 cdvd_send_atapi_command_symbol_FLAG[0x20] = {0x2C, 0x23, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x81, 0xFB, 0xE1, 0x00, 0x78, 0x7C, 0xBF, 0x2B, 0x78, 0xF8, 0x01, 0x00, 0x90, 0x41, 0xC2, 0x01, 0x6C, 0xE9, 0x62, 0xA4, 0xA8};
		u8 cdvd_send_device_command_symbol_FLAG[0x10] = {0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x78, 0x7C, 0x64, 0x1B, 0x78};
		u8 ufs_open_symbol_FLAG[0x10] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x41, 0xFA, 0xC1, 0x00, 0x70, 0x7C, 0x96, 0x23, 0x78};
		u8 ufs_close_symbol_FLAG[0x20] = {0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x78, 0x7C, 0x7F, 0x1B, 0x78, 0xFB, 0xC1, 0x00, 0x70, 0xF8, 0x01, 0x00, 0x90, 0x7D, 0x60, 0x00, 0xA6, 0x79, 0x60, 0x80, 0x42};
		u8 ufs_read_symbol_FLAG[0x10] = {0x7D, 0x20, 0x01, 0x64, 0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6}; // +8
		u8 ufs_write_symbol_FLAG[0x20] = {0x38, 0x21, 0x00, 0x90, 0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0x7C, 0xDC, 0x33, 0x78, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0xBD, 0x2B, 0x78}; // +8
		u8 ufs_fstat_symbol_FLAG[0x20] = {0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x70, 0x7C, 0x7E, 0x1B, 0x78, 0xFB, 0xE1, 0x00, 0x78, 0x7C, 0x9F, 0x23, 0x78, 0xF8, 0x01, 0x00, 0x90, 0x7D, 0x60, 0x00, 0xA6};
		u8 zeroalloc_symbol_FLAG[0x20] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x7C, 0x7D, 0x1B, 0x78, 0x4B, 0xFF, 0xFF, 0x89, 0x7C, 0x7C, 0x1B, 0x78};
		u8 malloc_symbol_FLAG[0x20] = {0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0x90, 0x7C, 0x7F, 0x1B, 0x78, 0xE9, 0x62, 0xE0, 0xB0, 0xE8, 0x0B, 0x00, 0x00, 0x2F, 0xA0, 0x00, 0x00};
		u8 free_symbol_FLAG[0x10] = {0xF8, 0x21, 0xFF, 0x91, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x00, 0x80, 0x48, 0x00, 0x32, 0x51};
		u8 memcpy_symbol_FLAG[0x20] = {0x2C, 0x25, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0xF8, 0x01, 0x00, 0x80, 0x41, 0x82, 0x00, 0x0C, 0x2F, 0xA3, 0x00, 0x00, 0x41, 0xDE, 0x00, 0x48, 0x38, 0x05, 0xFF, 0xFF};
		u8 memset_symbol_FLAG[0x20] = {0x2C, 0x25, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0xF8, 0x01, 0x00, 0x80, 0x41, 0x82, 0x00, 0x0C, 0x2F, 0xA3, 0x00, 0x00, 0x41, 0xDE, 0x00, 0x40, 0x38, 0x05, 0xFF, 0xFF};
		u8 strcpy_symbol_FLAG[0x10] = {0x88, 0x04, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x2F, 0xA0, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x18};
		u8 strcat_symbol_FLAG[0x10] = {0x88, 0x03, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x2F, 0x80, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x10};
		u8 strlen_symbol_FLAG[0x10] = {0x88, 0x03, 0x00, 0x00, 0x39, 0x20, 0x00, 0x00, 0x39, 0x63, 0x00, 0x01, 0x2F, 0x80, 0x00, 0x00};
		u8 vuart_read_symbol_FLAG[0x10] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x81, 0xFB, 0xE1, 0x00, 0x78, 0x39, 0x60, 0x00, 0xA2};
		u8 vuart_write_symbol_FLAG[0x10] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7D, 0x1B, 0x78};
		u8 ps2_disc_auth_symbol_FLAG[0x10] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x98, 0xEB, 0xA2, 0xA6, 0x28};
		u8 ps2_disc_auth_caller_symbol_FLAG[0x10] = {0x7C, 0x69, 0x18, 0xF8, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0x7D, 0x2B, 0xFE, 0x70};
		u8 overwritten_symbol_FLAG[0x20] = {0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x70, 0x7C, 0x7E, 0x1B, 0x78, 0xF8, 0x01, 0x00, 0x90, 0x80, 0x03, 0x00, 0x04, 0xFB, 0xE1, 0x00, 0x78, 0x2F, 0x80, 0x00, 0x00};
		
		memcpy(&TOC, &elf_data[0x101C0], 8);
		TOC = reverse64(TOC);
		
		memcpy(&stage2_addr, &elf_data[0x68], 8);
		stage2_addr = reverse64(stage2_addr);
		
		u64 n;
		
		for(n=0; n < elf_size ; n++) {
			
			if(cdvd_read_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) cdvd_read_symbol_FLAG, 0x10)) {
				cdvd_read_symbol = n - 0x10000;
			}
			if(cdvd_send_atapi_command_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) cdvd_send_atapi_command_symbol_FLAG, 0x20)) {
				cdvd_send_atapi_command_symbol = n - 0x10000;
			}
			if(cdvd_send_device_command_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) cdvd_send_device_command_symbol_FLAG, 0x10)) {
				cdvd_send_device_command_symbol = n - 0x10000;
			}
			if(ufs_open_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_open_symbol_FLAG, 0x10)) {
				ufs_open_symbol = n - 0x10000;
			}
			if(ufs_close_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_close_symbol_FLAG, 0x20)) {
				ufs_close_symbol = n - 0x10000;
			}
			if(ufs_read_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_read_symbol_FLAG, 0x10)) {
				ufs_read_symbol = n + 8 - 0x10000;
			}
			if(ufs_write_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_write_symbol_FLAG, 0x20)) {
				ufs_write_symbol = n + 8 - 0x10000;
			}
			if(ufs_fstat_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_fstat_symbol_FLAG, 0x20)) {
				ufs_fstat_symbol = n - 0x10000;
			}
			if(zeroalloc_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) zeroalloc_symbol_FLAG, 0x20)) {
				zeroalloc_symbol = n - 0x10000;
			}
			if(malloc_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) malloc_symbol_FLAG, 0x20)) {
				malloc_symbol = n - 0x10000;
			}
			if(free_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) free_symbol_FLAG, 0x10)) {
				free_symbol = n - 0x10000;
			}
			if(memcpy_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) memcpy_symbol_FLAG, 0x20)) {
				memcpy_symbol = n - 0x10000;
			}
			if(memset_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) memset_symbol_FLAG, 0x20)) {
				memset_symbol = n - 0x10000;
			}
			if(strcpy_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) strcpy_symbol_FLAG, 0x10)) {
				strcpy_symbol = n - 0x10000;
			}
			if(strcat_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) strcat_symbol_FLAG, 0x10)) {
				strcat_symbol = n - 0x10000;
			}
			if(strlen_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) strlen_symbol_FLAG, 0x10)) {
				strlen_symbol = n - 0x10000;
			}
			if(vuart_read_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) vuart_read_symbol_FLAG, 0x10)) {
				vuart_read_symbol = n - 0x10000;
			}
			if(vuart_write_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) vuart_write_symbol_FLAG, 0x10)) {
				vuart_write_symbol = n - 0x10000;
			}
			if(ps2_disc_auth_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ps2_disc_auth_symbol_FLAG, 0x10)) {
				ps2_disc_auth_symbol = n - 0x10000;
			}
			if(ps2_disc_auth_caller_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) ps2_disc_auth_caller_symbol_FLAG, 0x10)) {
				ps2_disc_auth_caller_symbol = n - 0x10000;
			}
			if(overwritten_symbol==0)
			if(!memcmp((char *) &elf_data[n], (char *) overwritten_symbol_FLAG, 0x20)) {
				overwritten_symbol = n - 0x10000;
			}
			
			if(cdvd_read_symbol)
			if(cdvd_send_atapi_command_symbol)
			if(cdvd_send_device_command_symbol)
			if(ufs_open_symbol)
			if(ufs_close_symbol)
			if(ufs_read_symbol)
			if(ufs_write_symbol)
			if(ufs_fstat_symbol)
			if(zeroalloc_symbol)
			if(malloc_symbol)
			if(free_symbol)
			if(memcpy_symbol)
			if(memset_symbol)
			if(strcpy_symbol)
			if(strcat_symbol)
			if(strlen_symbol)
			if(vuart_read_symbol)
			if(vuart_write_symbol)
			if(ps2_disc_auth_symbol)
			if(ps2_disc_auth_caller_symbol)
			if(overwritten_symbol)
			break;
			
		}
		
		sprintf(str, "\t\t#define TOC                                      0x%llX\n", TOC); fputs(str, sym);
		sprintf(str, "\t\t#define cdvd_read_symbol                         0x%llX\n", cdvd_read_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define cdvd_send_atapi_command_symbol           0x%llX\n", cdvd_send_atapi_command_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define cdvd_send_device_command_symbol          0x%llX\n", cdvd_send_device_command_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_open_symbol                          0x%llX\n", ufs_open_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_close_symbol                         0x%llX\n", ufs_close_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_read_symbol                          0x%llX\n", ufs_read_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_write_symbol                         0x%llX\n", ufs_write_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_fstat_symbol                         0x%llX\n", ufs_fstat_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define zeroalloc_symbol                         0x%llX\n", zeroalloc_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define malloc_symbol                            0x%llX\n", malloc_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define free_symbol                              0x%llX\n", free_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define memcpy_symbol                            0x%llX\n", memcpy_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define memset_symbol                            0x%llX\n", memset_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define strcpy_symbol                            0x%llX\n", strcpy_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define strcat_symbol                            0x%llX\n", strcat_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define strlen_symbol                            0x%llX\n", strlen_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define vuart_read_symbol                        0x%llX\n", vuart_read_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define vuart_write_symbol                       0x%llX\n", vuart_write_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ps2_disc_auth_symbol                     0x%llX\n", ps2_disc_auth_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ps2_disc_auth_caller_symbol              0x%llX\n", ps2_disc_auth_caller_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define overwritten_symbol                       0x%llX\n", overwritten_symbol); fputs(str, sym);
		fputs("\t\t#define stage1_addr                              overwritten_symbol\n", sym);
		sprintf(str, "\t\t#define stage2_addr                              0x%llX\n", stage2_addr); fputs(str, sym);
		
		fputs("\t#endif /* FIRMWARE */\n\n", sym);
		
	}
	closedir(d);
	
	fputs("#endif /* PS2GXEMU */\n\n", sym);

//ps2netemu
	fputs("#ifdef PS2NETEMU\n\n", sym);
	
	fputs("\t#define EXTENDED_DATA	(0x821000+0x2953478)\n\n", sym);
	
	d = opendir("ps2emu");
	if(d== NULL) {
		printf("Directory ps2emu not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(ELF, "ps2emu/%s/ps2_netemu.elf", ent->d_name);
		
		elf=fopen(ELF, "rb");
		if(elf==NULL) {
			printf("Error : cannot open the %s\n", ELF);
			return 0;
		}
		
		fseek (elf , 0 , SEEK_END);
		u32 elf_size = ftell (elf);
		fseek(elf, 0, SEEK_SET);
		
		char *elf_data = (char *) malloc(elf_size);	
		if(elf_data == NULL) {
			printf("Error : cannot malloc %s", ELF);
			free(elf_data);
			fclose(elf);
			return 0;
		}
		
		fread(elf_data, elf_size, 1, elf);
		fclose(elf);
		
		sprintf(str, "\t#ifdef FIRMWARE_%s\n", ent->d_name); fputs(str, sym);
		
		u64 TOC=0;
		u64 cdvd_read_symbol=0;
		u64 ufs_open_symbol=0;
		u64 ufs_close_symbol=0;
		u64 ufs_read_symbol=0;
		u64 ufs_write_symbol=0;
		u64 ufs_fstat_symbol=0;
		u64 memcpy_symbol=0;
		u64 memset_symbol=0;
		u64 strcpy_symbol=0;
		u64 strcat_symbol=0;
		u64 strlen_symbol=0;
		
		u8 cdvd_read_symbol_FLAG[0x10] = {0x2F, 0x86, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFE, 0xF1, 0xF9, 0xC1, 0x00, 0x80};
		
		u8 ufs_open_symbol_FLAG[0x10] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x31, 0xFB, 0x01, 0x00, 0x90, 0xFB, 0x41, 0x00, 0xA0};
		u8 ufs_close_symbol_FLAG[0x20] = {0x38, 0x60, 0xFF, 0xFB, 0x4B, 0xFF, 0xFF, 0x30, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x7E, 0x1B, 0x78}; //+8
		u8 ufs_read_symbol_FLAG[0x20] = {0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x21, 0x00, 0x78, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xC1, 0x00, 0xA0}; //+4
		u8 ufs_write_symbol_FLAG[0x20] = {0x4B, 0xFF, 0xFE, 0xAC, 0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x21, 0x00, 0x78, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xC1, 0x00, 0xA0}; //+4
		u8 ufs_fstat_symbol_FLAG[0x20] = {0x4B, 0xFF, 0xFF, 0x28, 0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0x78, 0xFB, 0x81, 0x00, 0x80, 0xFB, 0xC1, 0x00, 0x90, 0xFB, 0xE1, 0x00, 0x98, 0x7C, 0x9C, 0x23, 0x78}; //+4
		
		u8 memcpy_symbol_FLAG[0x20] = {0x2F, 0x85, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0xF8, 0x01, 0x00, 0x80, 0x41, 0x9E, 0x00, 0x2C, 0x2F, 0xA3, 0x00, 0x00, 0x78, 0xA5, 0x00, 0x20, 0x7C, 0x69, 0x1B, 0x78};
		u8 memset_symbol_FLAG[0x20] = {0x2F, 0x85, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0xF8, 0x01, 0x00, 0x80, 0x41, 0x9E, 0x00, 0x28, 0x2F, 0xA3, 0x00, 0x00, 0x78, 0xA5, 0x00, 0x20, 0x7C, 0x69, 0x1B, 0x78};
		
		u8 strcpy_symbol_FLAG[0x10] = {0x88, 0x04, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x2F, 0x80, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x1C};
		u8 strcat_symbol_FLAG[0x10] = {0x88, 0x03, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x2F, 0x80, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x14};
		u8 strlen_symbol_FLAG[0x10] = {0x7C, 0x69, 0x1B, 0x78, 0x38, 0x60, 0x00, 0x00, 0x88, 0x09, 0x00, 0x00, 0x2F, 0x80, 0x00, 0x00};
		
		memcpy(&TOC, &elf_data[0x13008], 8);
		TOC = reverse64(TOC);
		
		u64 n;
		
		for(n=0; n < elf_size ; n++) {
		
			if(cdvd_read_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) cdvd_read_symbol_FLAG, 0x10)) {
				cdvd_read_symbol = n - 0x10000;
			}
			if(ufs_open_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_open_symbol_FLAG, 0x10)) {
				ufs_open_symbol = n - 0x10000;
			}
			if(ufs_close_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_close_symbol_FLAG, 0x20)) {
				ufs_close_symbol = n + 8 - 0x10000;
			}
			if(ufs_read_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_read_symbol_FLAG, 0x20)) {
				ufs_read_symbol = n + 4 - 0x10000;
			}
			if(ufs_write_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_write_symbol_FLAG, 0x20)) {
				ufs_write_symbol = n + 4 - 0x10000;
			}
			if(ufs_fstat_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) ufs_fstat_symbol_FLAG, 0x20)) {
				ufs_fstat_symbol = n + 4 - 0x10000;
			}
			if(memcpy_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) memcpy_symbol_FLAG, 0x20)) {
				memcpy_symbol = n - 0x10000;
			}
			if(memset_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) memset_symbol_FLAG, 0x20)) {
				memset_symbol = n - 0x10000;
			}
			if(strcpy_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) strcpy_symbol_FLAG, 0x10)) {
				strcpy_symbol = n - 0x10000;
			}
			if(strcat_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) strcat_symbol_FLAG, 0x10)) {
				strcat_symbol = n - 0x10000;
			}
			if(strlen_symbol == 0)
			if(!memcmp((char *) &elf_data[n], (char *) strlen_symbol_FLAG, 0x10)) {
				strlen_symbol = n - 0x10000;
			}
			
			if(cdvd_read_symbol)
			if(ufs_open_symbol)
			if(ufs_close_symbol)
			if(ufs_read_symbol)
			if(ufs_write_symbol)
			if(ufs_fstat_symbol)
			if(memcpy_symbol)
			if(memset_symbol)
			if(strcpy_symbol)
			if(strcat_symbol)
			if(strlen_symbol)
			break;
			
			
		}
		
		sprintf(str, "\t\t#define TOC                                      0x%llX\n", TOC); fputs(str, sym);
		sprintf(str, "\t\t#define cdvd_read_symbol                         0x%llX\n", cdvd_read_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_open_symbol                          0x%llX\n", ufs_open_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_close_symbol                         0x%llX\n", ufs_close_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_read_symbol                          0x%llX\n", ufs_read_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_write_symbol                         0x%llX\n", ufs_write_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define ufs_fstat_symbol                         0x%llX\n", ufs_fstat_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define memcpy_symbol                            0x%llX\n", memcpy_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define memset_symbol                            0x%llX\n", memset_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define strcpy_symbol                            0x%llX\n", strcpy_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define strcat_symbol                            0x%llX\n", strcat_symbol); fputs(str, sym);
		sprintf(str, "\t\t#define strlen_symbol                            0x%llX\n", strlen_symbol); fputs(str, sym);
		
		fputs("\t#endif /* FIRMWARE */\n\n", sym);
		
		free(elf_data);
	}
	closedir(d);
	
	fputs("#endif /* PS2NETEMU */\n\n", sym);
	
	fputs("\n#endif /* __PS2EMU_SYMBOLS_H_S__ */\n", sym);
	fclose(sym);
	
	printf("Done !\n");
	
	return 0;
}