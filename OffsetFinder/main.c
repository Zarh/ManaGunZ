#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <dirent.h>

#define SWAP16(x) ((((u16)(x))>>8) | ((x) << 8))
#define SWAP32(x) ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | (((x) >> 24) & 0xff))

typedef uint8_t		u8;
typedef uint16_t 	u16;
typedef uint32_t	u32;
typedef uint64_t 	u64;

typedef int8_t		s8;
typedef int16_t 	s16;
typedef int32_t		s32;
typedef int64_t 	s64;

typedef struct {
	unsigned char	e_ident[16];	/* ident bytes */
	uint16_t	e_type;			/* file type */
	uint16_t	e_machine;		/* target machine */
	uint32_t	e_version;		/* file version */
	uint64_t	e_entry;		/* start address */
	uint64_t	e_phoff;		/* phdr file offset */
	uint64_t	e_shoff;		/* shdr file offset */
	uint32_t	e_flags;		/* file flags */
	uint16_t	e_ehsize;		/* sizeof ehdr */
	uint16_t	e_phentsize;		/* sizeof phdr */
	uint16_t	e_phnum;		/* number phdrs */
	uint16_t	e_shentsize;		/* sizeof shdr */
	uint16_t	e_shnum;		/* number shdrs */
	uint16_t	e_shstrndx;		/* shdr string index */
} __attribute__((packed)) Elf64_Ehdr;
	
typedef struct {
	uint32_t	p_type;		/* entry type */
	uint32_t	p_flags;	/* entry flags */
	uint64_t	p_offset;	/* file offset */
	uint64_t	p_vaddr;	/* virtual address */
	uint64_t	p_paddr;	/* physical address */
	uint64_t	p_filesz;	/* file size */
	uint64_t	p_memsz;	/* memory size */
	uint64_t	p_align;	/* memory/file alignment */
} __attribute__((packed)) Elf64_Phdr;

typedef struct {
	uint32_t	sh_name;	/* section name */
	uint32_t	sh_type;	/* SHT_... */
	uint64_t	sh_flags;	/* SHF_... */
	uint64_t	sh_addr;	/* virtual address */
	uint64_t	sh_offset;	/* file offset */
	uint64_t	sh_size;	/* section size */
	uint32_t	sh_link;	/* misc info */
	uint32_t	sh_info;	/* misc info */
	uint64_t	sh_addralign;	/* memory alignment */
	uint64_t	sh_entsize;	/* entry size if table */
} __attribute__((packed)) Elf64_Shdr ;

typedef struct {
	uint32_t magic;
	uint32_t version;
	uint16_t flags;
	uint16_t type;
	uint32_t metadata_offset;
	uint64_t header_len;
	uint64_t elf_filesize;
	uint64_t unknown;
	uint64_t appinfo_offset;
	uint64_t elf_offset;
	uint64_t phdr_offset;
	uint64_t shdr_offset;
	uint64_t section_info_offset;
	uint64_t sceversion_offset;
	uint64_t controlinfo_offset;
	uint64_t controlinfo_size;
	uint64_t padding;
} __attribute__((packed)) SELF;

typedef struct {
	uint64_t offset;
	uint64_t size;
	uint32_t compressed; // 2=compressed
	uint32_t unknown1;
	uint32_t unknown2;
	uint32_t encrypted; // 1=encrypted
} __attribute__((packed)) SECTION_INFO;

#define	SHF_WRITE		0x01		/* sh_flags */
#define	SHF_ALLOC		0x02
#define	SHF_EXECINSTR		0x04
#define	SHF_MERGE		0x10
#define	SHF_STRINGS		0x20
#define	SHF_INFO_LINK		0x40
#define	SHF_LINK_ORDER		0x80
#define	SHF_OS_NONCONFORMING	0x100
#define	SHF_GROUP		0x200
#define	SHF_TLS			0x400

static uint64_t swap64(uint64_t data)
{
	uint64_t ret = (data << 56) & 0xff00000000000000ULL;
	ret |= ((data << 40) & 0x00ff000000000000ULL);
	ret |= ((data << 24) & 0x0000ff0000000000ULL);
	ret |= ((data << 8) & 0x000000ff00000000ULL);
	ret |= ((data >> 8) & 0x00000000ff000000ULL);
	ret |= ((data >> 24) & 0x0000000000ff0000ULL);
	ret |= ((data >> 40) & 0x000000000000ff00ULL);
	ret |= ((data >> 56) & 0x00000000000000ffULL);
	return ret;
}

uint64_t hash(char *self_path, uint8_t section, uint8_t mode)
{
	FILE *f;
	uint8_t *self_buf;
	uint32_t elf_buf[0x100];
	SELF *self;
	SECTION_INFO *section_info;
	Elf64_Ehdr *elf_header;
	Elf64_Phdr *elf_phdr;
	
	f = fopen(self_path, "rb");
	if (!f)
	{
		printf("Cannot open %s\n", self_path);
		return -1;
	}
	
	self_buf = malloc(256*1024);
	fread(self_buf, 1, 256*1024, f);
	fclose(f);
	
	char sce_decrypt[255];
	sprintf(sce_decrypt, "scetool -d %s temp_dec", self_path);
	system(sce_decrypt);
	
	f = fopen("temp_dec", "rb");
	if (!f)
	{
		free(self_buf);
		printf("Cannot extract self.\n");
		return -1;
	}
	
	self = (SELF *)self_buf;
	section_info = (SECTION_INFO *)(self_buf+swap64(self->section_info_offset));
	elf_header = (Elf64_Ehdr *)(self_buf+swap64(self->elf_offset));
	elf_phdr = (Elf64_Phdr *)(((uint8_t *)elf_header)+swap64(elf_header->e_phoff));
	
	uint8_t i=0;
	while(i != section) 
	{
		section_info++;
		elf_phdr++;
		i++;
	}
	
	uint64_t size;
	uint64_t hash = 0;
	
	size = swap64(section_info->size);
	if (size < 0x400)
	{
		printf("Size too small\n");
	}
	else
	{
		fseek(f, swap64(elf_phdr->p_offset), SEEK_SET);
		fread(elf_buf, 1, sizeof(elf_buf), f);
		
		if(mode==0) {
			for (int j = 0; j < 0x100; j++)
			{
				hash ^= SWAP32(elf_buf[j]);
			}
			
			hash = (hash << 32) | size;
		} else
		if(mode==1) {
			for (int j = 0; j < 0x8; j++)
			{
				hash ^= SWAP32(elf_buf[j+0xb0]);
			}
			size=(size&0xfff000);
			
			hash = ((hash << 32)&0xfffff00000000000)|(size);
		} else
		if(mode==2) {
			for (int j = 0; j < 0x8; j++)
			{
				hash ^= SWAP32(elf_buf[j+0xb0]);
			}
			if((size & 0xff0000)==0)
			{
				size=(size&0xfff000);
			}
			else
			{
				size=(size&0xff0000);
			}
			
			hash = ((hash << 32)&0xfffff00000000000)|(size);
		}
	}
		
	free(self_buf);
	fclose(f);
	
	unlink("temp_dec");
	
	return hash;
}

uint8_t exist(char *path)
{
	struct stat s;
	if(stat(path, &s) != 0) return 0; else
	return 1;
}

u64 reverse64(u64 x) {

	x = (x & 0x00000000FFFFFFFFULL) << 32 | (x & 0xFFFFFFFF00000000ULL) >> 32;
	x = (x & 0x0000FFFF0000FFFFULL) << 16 | (x & 0xFFFF0000FFFF0000ULL) >> 16;
	x = (x & 0x00FF00FF00FF00FFULL) << 8  | (x & 0xFF00FF00FF00FF00ULL) >> 8 ;
	return x;
}

uint8_t compare(u8 ignore, char *mem, char *flag, u32 size)
{
	int i;
	for(i = 0; i < size; i++) {
		if((u8) flag[i] != ignore && flag[i] != mem[i]) return 0;
	}
	return 1;
}

int main()
{	

	char dump[255];
	FILE *f;
	FILE *common;
	FILE *SKY;
	FILE *symbols;
	char temp[255];
	char temp2[255];	
	
	DIR *d;
	struct dirent* ent = NULL;
	
	SKY = fopen("firmware_symbols.h", "w");
	common = fopen("common.h", "w");
	symbols = fopen("symbols.h", "w");
	
	fputs("#ifndef __COMMON_H__\n", common);
	fputs("#define __COMMON_H__\n\n", common);
	fputs("#define NEW_POKE_SYSCALL     813\n", common);
	fputs("#define SYSCALL_PTR(n)       ((SYSCALL_TABLE) + ( 8 * (n) ))\n", common);
	fputs("#define MAP_BASE             0x80000000007FAE00ULL\n", common);
	fputs("#define MAP_ADDR             0xE8\n\n", common);

	fputs("#define open_mapping_table_ext      0x7fff00\n", SKY);
	fputs("#define perm_patch_func             0x3560\n", SKY);
	fputs("#define perm_var_offset             -0x7FF8\n", SKY);
	fputs("#define BASE                        0x3d90\n", SKY);
	fputs("#define BASE2                      (0x3d90+0x400)\n", SKY);
	fputs("#define strcpy                      memset + 0x1AC\n", SKY);
	fputs("#define strncmp                     memset + 0x200\n", SKY);
	fputs("#define free                        alloc + 0x43C\n", SKY);
	

	fputs("#ifndef __FIRMWARE_SYMBOLS_H_S__\n", symbols);
	fputs("#define __FIRMWARE_SYMBOLS_H_S__\n\n", symbols);
	
	fputs("#define umd_mutex_offset (0x64480+0x38C)\n\n", symbols);

	printf("Searching offsets...\n");
	
	d = opendir("LV2");
	if(d== NULL) {
		printf("Put your dumps in the directory 'LV2'\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(dump, "LV2/%s", ent->d_name);
		
		f=fopen(dump, "rb");
		if(f==NULL) {
			printf("Error : cannot open the dump\n");
			return 0;
		}
		
		fseek (f , 0 , SEEK_END);
		u32 size = ftell (f);
		fseek(f, 0, SEEK_SET);
		
		if(size != 0x800000) {
			printf("Error : bad size of your dump\n");
			fclose(f);
			return 0;
		}
		
		char *memLV2 = (char *) malloc(size);	
		if(memLV2 == NULL) {
			printf("Error : cannot malloc");
			free(memLV2);
			fclose(f);
			return 0;
		}
		
		fread(memLV2,size,1, f);
		fclose (f);
		
		u64 SYSCALL_TABLE=0;
		u64 OFFSET_FIX=0;
		u64 OFFSET_2_FIX=0;
		u64 OFFSET_FIX_3C=0;
		u64 OFFSET_FIX_2B17=0;
		u64 OFFSET_FIX_LIC=0;
		u64 OPEN_HOOK=0;
		u64 BASE_ADDR=0;
		u64 LV2MOUNTADDR=0;
		u64 LV2MOUNTADDR_ESIZE=0;
		u64 LV2MOUNTADDR_CSIZE=0;
		u64 FIRMWARE_OFFSET=0;
		u64 OFFSET_1_IDPS=0;
		u64 OFFSET_2_IDPS=0;
		u64 HV_START_OFFSET = 0;
		u64 FIRMWARE = 0;
		
		u64 FW_DATE_OFFSET=0;
		u64 FW_DATE_1=0;
		u64 FW_DATE_2=0;
		
		
		u8 flag_offset_fix[0x20] = {0x38, 0xDE, 0x00, 0x07, 0x88, 0x1E, 0x00, 0x07, 0x2F, 0x84, 0x00, 0x01, 0x98, 0x01, 0x00, 0x73, 0x88, 0x06, 0x00, 0x01, 0x88, 0xA6, 0x00, 0x08, 0x89, 0x26, 0x00, 0x02, 0x89, 0x66, 0x00, 0x03};
		u8 flag_offset_2_fix[0x20] = {0xF9, 0x1F, 0x00, 0x20, 0xF8, 0xFF, 0x00, 0x28, 0xF8, 0xDF, 0x00, 0x30, 0xF8, 0xBF, 0x00, 0x38, 0xFB, 0xBF, 0x00, 0x40, 0x4B, 0xFA, 0x97, 0x45, 0x54, 0x63, 0x06, 0x3E, 0x2F, 0x83, 0x00, 0x00};
		u8 flag_offset_fix_2B17[0x20] = {0x4E, 0x80, 0x00, 0x20, 0x3C, 0x80, 0x10, 0x50, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0x78, 0x84, 0x07, 0xC6, 0xFB, 0xE1, 0x00, 0x88, 0x64, 0x84, 0x03, 0x00, 0x7C, 0x7F, 0x1B, 0x78};
		u8 flag_offset_fix_lic[0x20] = {0x2F, 0x83, 0x00, 0x00, 0x3B, 0xFC, 0x00, 0x6C, 0x41, 0x9E, 0x00, 0x60, 0x38, 0x00, 0x00, 0x02, 0x3B, 0xE0, 0x00, 0x00, 0x90, 0x1C, 0x00, 0x6C, 0x4B, 0xFF, 0xFF, 0x38, 0x2F, 0xA7, 0x00, 0x00};
		u8 flag_offset_fix_3C[0x20] = {0x4B, 0xFF, 0xFF, 0xD8, 0xE8, 0x03, 0x01, 0xA8, 0x7C, 0x09, 0xFE, 0x76, 0x7D, 0x23, 0x02, 0x78, 0x7C, 0x69, 0x18, 0x50, 0x38, 0x63, 0xFF, 0xFF, 0x78, 0x63, 0x0F, 0xE0, 0x4E, 0x80, 0x00, 0x20};
		u8 flag_open_hook[0x30] = {0x2B, 0xA3, 0x04, 0x20, 0x3F, 0xE0, 0x80, 0x01, 0x63, 0xFF, 0x00, 0x34, 0x40, 0x9D, 0x00, 0x2C, 0xE8, 0x01, 0x00, 0xB0, 0x7F, 0xE3, 0x07, 0xB4, 0xEB, 0x41, 0x00, 0x70, 0xEB, 0x61, 0x00, 0x78, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0x81, 0x00, 0x80, 0xEB, 0xA1, 0x00, 0x88, 0xEB, 0xE1, 0x00, 0x98};
		u8 flag_base_addr[0x20]	= {0x42, 0x61, 0x63, 0x6B, 0x74, 0x72, 0x61, 0x63, 0x65, 0x20, 0x49, 0x6E, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x3A, 0x0A, 0x00, 0x20, 0x20, 0x2D, 0x20, 0x30, 0x78, 0x25, 0x30};
		u8 flag_lv2mountaddr[0x20] = {0x43, 0x45, 0x4C, 0x4C, 0x5F, 0x46, 0x53, 0x5F, 0x41, 0x44, 0x4D, 0x49, 0x4E, 0x46, 0x53, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		u8 flag_firmware_offset[0x20] = {0x6E, 0x3A, 0x20, 0x25, 0x75, 0x2E, 0x25, 0x30, 0x32, 0x75, 0x20, 0x28, 0x25, 0x73, 0x29, 0x0A, 0x23, 0x20, 0x72, 0x65, 0x76, 0x69, 0x73, 0x69, 0x6F, 0x6E, 0x3A, 0x20, 0x25, 0x64, 0x0A, 0x00};
		u8 flag_1_idpsoffset[8] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00}; 
		u8 flag_2_idpsoffset[8] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x90, 0x00, 0x00};
		
		u8 flag_hv_start_offset[0x10] = {0xE0, 0xD2, 0x51, 0xB5, 0x56, 0xC5, 0x9F, 0x05, 0xC2, 0x32, 0xFC, 0xAD, 0x55, 0x2C, 0x80, 0xD7};
		u8 flag_hv_start_offset2[0x20] = {0xD0, 0xF3, 0x4E, 0x3F, 0xF9, 0x62, 0x5C, 0xF2, 0x31, 0x54, 0xE5, 0x5D, 0xD7, 0x1E, 0xF2, 0x4E, 0x48, 0x0F, 0xF1, 0x36, 0x1D, 0xFD, 0x1A, 0x41, 0xC4, 0x23, 0x35, 0x97, 0x4F, 0xCE, 0x19, 0x5C};
		u8 flag_hv_start_offset3[0x28] = {[0 ... 0x27] = 0xFF};
		u8 flag_hv_start_offset4[0x8] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		
		u8 flag_fw1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
		u8 flag_fw2[8] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
				
		u64 OFF_alloc = 0;
		u64 OFF_memory_patch_func = 0;
		u64 OFF_memcpy = 0;
		u64 OFF_memset = 0;
		
		u8 flag_alloc[0x20] = {0x4B, 0xFF, 0xF7, 0x2D, 0x2C, 0x23, 0x00, 0x00, 0x40, 0x82, 0xFF, 0x50, 0x4B, 0xFF, 0xFF, 0xB0, 0x2C, 0x23, 0x00, 0x00, 0x7C, 0x85, 0x23, 0x78, 0x38, 0xC0, 0x00, 0x00, 0x7C, 0x64, 0x1B, 0x78};
		u8 flag_memory_patch_func[0x20] = {0x2B, 0xA3, 0x04, 0x20, 0x3F, 0xE0, 0x80, 0x01, 0x63, 0xFF, 0x00, 0x34, 0x40, 0x9D, 0x00, 0x2C, 0xE8, 0x01, 0x00, 0xB0, 0x7F, 0xE3, 0x07, 0xB4, 0xEB, 0x41, 0x00, 0x70, 0xEB, 0x61, 0x00, 0x78};
		u8 flag_memcpy[0x20] = {0x2B, 0xA5, 0x00, 0x07, 0x7C, 0x6B, 0x1B, 0x78, 0x41, 0x9D, 0x00, 0x2C, 0x2C, 0x25, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x4D, 0x82, 0x00, 0x20, 0x7C, 0xA9, 0x03, 0xA6, 0x88, 0x04, 0x00, 0x00};
		u8 flag_memset[0x20] = {0x2B, 0xA5, 0x00, 0x17, 0x7C, 0x6A, 0x1B, 0x78, 0x41, 0x9D, 0x00, 0x24, 0x2F, 0xA5, 0x00, 0x00, 0x4D, 0x9E, 0x00, 0x20, 0x7C, 0x80, 0x23, 0x78, 0x7C, 0xA9, 0x03, 0xA6, 0x98, 0x0A, 0x00, 0x00};
		
		u64 vsh_pos_in_ram=0;
		u8 vsh_pos_in_ram_FLAG[0x10] = {0xF8, 0x21, 0xFF, 0x91, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x00, 0x80, 0x48, 0x00, 0x03, 0x9D};
		
		u64 TOC=0;
		u64 open_shared_kernel_object_symbol=0;									  
		u64 close_kernel_object_handle_symbol=0;		   
		u64 open_kernel_object_symbol=0;
		u64 alloc_symbol=0;
		u64 dealloc_symbol=0;
		u64 copy_to_user_symbol=0;
		u64 copy_from_user_symbol=0;
		u64 copy_to_process_symbol=0;
		u64 copy_from_process_symbol=0;
		u64 page_allocate_symbol=0;
		u64 page_free_symbol=0;
		u64 page_export_to_proc_symbol=0;
		u64 page_unexport_from_proc_symbol=0;
		u64 kernel_ea_to_lpar_addr_symbol=0;
		u64 map_process_memory_symbol=0;
		u64 memcpy_symbol=0;
		u64 memset_symbol=0;
		u64 memcmp_symbol=0;
		u64 printf_symbol=0;
		u64 printfnull_symbol=0;
		u64 sprintf_symbol=0;
		u64 snprintf_symbol=0;
		u64 strcpy_symbol=0;
		u64 strncpy_symbol=0;
		u64 strlen_symbol=0;
		u64 strcat_symbol=0;
		u64 strcmp_symbol=0;
		u64 strncmp_symbol=0;
		u64 strchr_symbol=0;
		u64 spin_lock_irqsave_ex_symbol=0;
		u64 spin_unlock_irqrestore_ex_symbol=0;
		u64 load_process_symbol=0;
		u64 ppu_thread_create_symbol=0;
		u64 ppu_thread_exit_symbol=0;
		u64 ppu_thread_join_symbol=0;
		u64 ppu_thread_delay_symbol=0;
		u64 create_user_thread2_symbol=0;
		u64 start_thread_symbol=0;
		u64 run_thread_symbol=0;
		u64 register_thread_symbol=0;
		u64 allocate_user_stack_symbol=0;
		u64 mutex_create_symbol=0;
		u64 mutex_destroy_symbol=0;
		u64 mutex_lock_symbol=0;
		u64 mutex_unlock_symbol=0;
		u64 event_port_create_symbol=0;
		u64 event_port_destroy_symbol=0;
		u64 event_port_connect_symbol=0;
		u64 event_port_disconnect_symbol=0;
		u64 event_port_send_symbol=0;
		u64 event_queue_create_symbol=0;
		u64 event_queue_destroy_symbol=0;
		u64 event_queue_receive_symbol=0;
		u64 cellFsOpen_symbol=0;
		u64 cellFsClose_symbol=0;
		u64 cellFsRead_symbol=0;
		u64 cellFsWrite_symbol=0;
		u64 cellFsLseek_symbol=0;
		u64 cellFsStat_symbol=0;
		u64 cellFsUnlink_internal_symbol=0;
		u64 cellFsUtilMount_symbol=0;
		u64 cellFsUtilUmount_symbol=0;
		u64 pathdup_from_user_symbol=0;
		u64 open_path_symbol=0;
		u64 open_fs_object_symbol=0;
		u64 close_fs_object_symbol=0;
		u64 storage_get_device_info_symbol=0;
		u64 storage_open_symbol=0;
		u64 storage_close_symbol=0;
		u64 storage_read_symbol=0;
		u64 storage_send_device_command_symbol=0;
		u64 storage_map_io_memory_symbol=0;
		u64 storage_unmap_io_memory_symbol=0;
		u64 storage_internal_get_device_object_symbol=0;
		u64 decrypt_func_symbol=0;
		u64 lv1_call_99_wrapper_symbol=0;
		u64 modules_verification_symbol=0;
		u64 prx_load_module_symbol=0;
		u64 prx_start_module_symbol=0;
		u64 prx_stop_module_symbol=0;
		u64 prx_unload_module_symbol=0;
		u64 prx_get_module_info_symbol=0;
		u64 prx_get_module_list_symbol=0;
		u64 extend_kstack_symbol=0;
		u64 get_pseudo_random_number_symbol=0;
		u64 syscall_call_offset=0;
		u64 read_bdvd0_symbol=0;
		u64 read_bdvd1_symbol=0;
		u64 read_bdvd2_symbol=0;
		u64 device_event_port_send_call=0;
		u64 process_map_caller_call=0;
		u64 fsloop_open_call=0;
		u64 fsloop_close_call=0;
		u64 fsloop_read_call=0;
		s16 io_rtoc_entry_1=0;
		s16 io_sub_rtoc_entry_1=0;
		s16 decrypt_rtoc_entry_2=0;
		s16 storage_rtoc_entry_1=0;
		s16 device_event_rtoc_entry_1=0;
		s16 process_rtoc_entry_1=0;
		u64 patch_func2=0;
		//u64 patch_func2_offset=0;
		u64 user_thread_prio_patch=0;
		u64 user_thread_prio_patch2=0;
		u64 shutdown_patch_offset=0;
		u64 shutdown_copy_params_call=0;

		u8 open_shared_kernel_object_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0xB0, 0xFB, 0xC1, 0x00, 0xC0, 0xFB, 0xE1, 0x00, 0xC8, 0xF8, 0x01, 0x00, 0xE0, 0x78, 0x9C, 0x84, 0x02, 0x7C, 0xE0, 0x3B, 0x78};
		u8 close_kernel_object_handle_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x98, 0xFB, 0xE1, 0x00, 0xA8, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xC1, 0x00, 0xA0, 0xF8, 0x01, 0x00, 0xC0, 0x7C, 0x7D, 0x1B, 0x78, 0x7C, 0x9F, 0x23, 0x78, 0x7D, 0x30, 0x42, 0xA6};
		u8 open_kernel_object_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x98, 0xFB, 0xC1, 0x00, 0xA0, 0xFB, 0xE1, 0x00, 0xA8, 0x78, 0x9E, 0x84, 0x02, 0x78, 0x9F, 0xC6, 0x22, 0x78, 0x9D, 0x06, 0x20};
		u8 alloc_symbol_flag[] = {0x2C, 0x23, 0x00, 0x00, 0x7C, 0x85, 0x23, 0x78, 0x38, 0xC0, 0x00, 0x00, 0x7C, 0x64, 0x1B, 0x78, 0x4D, 0x82, 0x00, 0x20};
		u8 dealloc_symbol_flag[] = {0x7C, 0x85, 0x23, 0x78, 0x38, 0xC0, 0x00, 0x00, 0x7C, 0x64, 0x1B, 0x78, 0xE8, 0x69, 0x00, 0x00, 0x4B, 0xFF, 0xFB, 0xD0, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6};
		u8 copy_to_user_symbol_flag[] = {0x2C, 0x25, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x7E, 0x1B, 0x78, 0xFB, 0x81, 0x00, 0x70};
		u8 copy_from_user_symbol_flag[] = {0x2C, 0x25, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x70, 0x7C, 0x7F, 0x1B, 0x78};
		u8 copy_to_process_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x25, 0x00, 0x00, 0xFB, 0x61, 0x00, 0xA8, 0x3F, 0x60, 0x80, 0x01, 0xFB, 0x21, 0x00, 0x98, 0xFB, 0x81, 0x00, 0xB0, 0xFA, 0xE1, 0x00, 0x88};
		u8 copy_from_process_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x41, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x24, 0x00, 0x00, 0xFB, 0x61, 0x00, 0x98, 0x3F, 0x60, 0x80, 0x01, 0xFB, 0x21, 0x00, 0x88, 0xFB, 0x81, 0x00, 0xA0, 0xFB, 0x01, 0x00, 0x80};
		u8 page_allocate_symbol_flag[] = {0x7C, 0x80, 0x23, 0x78, 0x7C, 0xA9, 0x2B, 0x78, 0x7C, 0xCB, 0x33, 0x78, 0x7C, 0xE8, 0x3B, 0x78, 0x7C, 0x64, 0x1B, 0x78, 0x7C, 0x05, 0x03, 0x78, 0x7D, 0x26, 0x4B, 0x78, 0x7D, 0x67, 0x5B, 0x78};
		u8 page_free_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x61, 0xF8, 0x01, 0x00, 0xB0, 0xFB, 0xC1, 0x00, 0x90, 0xFB, 0xE1, 0x00, 0x98, 0xE9, 0x2B, 0x00, 0x00, 0x7C, 0x7F, 0x1B, 0x78, 0x7C, 0xBE, 0x2B, 0x78};
		u8 page_export_to_proc_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0x3D, 0x20, 0x00, 0x0C, 0xF8, 0x01, 0x00, 0xA0, 0x54, 0xA0, 0x03, 0x1A, 0xFB, 0xE1, 0x00, 0x88, 0x7F, 0xA0, 0x48, 0x00, 0x3D, 0x20, 0x80, 0x01};
		u8 page_unexport_from_proc_symbol_flag[] = {0x2B, 0xA3, 0x00, 0x3C, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0xF8, 0x01, 0x00, 0x80, 0x7C, 0x8B, 0x23, 0x78, 0x7C, 0x60, 0x1B, 0x78};
		u8 kernel_ea_to_lpar_addr_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x51, 0xF8, 0x01, 0x00, 0xC0, 0xFB, 0xC1, 0x00, 0xA0, 0xFB, 0x61, 0x00, 0x88, 0xEB, 0xC9, 0x00, 0x00, 0x7C, 0x9B, 0x23, 0x78, 0xFB, 0x81, 0x00, 0x90};
		u8 map_process_memory_symbol_flag[] = {0xF8, 0x21, 0xFE, 0xE1, 0xFA, 0xC1, 0x00, 0xD0, 0x7C, 0xF6, 0x3B, 0x78, 0xFB, 0x81, 0x01, 0x00};
		u8 memcpy_symbol_flag[] = {0x2B, 0xA5, 0x00, 0x07, 0x7C, 0x6B, 0x1B, 0x78, 0x41, 0x9D, 0x00, 0x2C, 0x2C, 0x25, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x4D, 0x82, 0x00, 0x20, 0x7C, 0xA9, 0x03, 0xA6, 0x88, 0x04, 0x00, 0x00};
		u8 memset_symbol_flag[] = {0x2B, 0xA5, 0x00, 0x17, 0x7C, 0x6A, 0x1B, 0x78, 0x41, 0x9D, 0x00, 0x24, 0x2F, 0xA5, 0x00, 0x00, 0x4D, 0x9E, 0x00, 0x20, 0x7C, 0x80, 0x23, 0x78, 0x7C, 0xA9, 0x03, 0xA6, 0x98, 0x0A, 0x00, 0x00};
		u8 memcmp_symbol_flag[] = {0x38, 0xA5, 0x00, 0x01, 0x7C, 0xA9, 0x03, 0xA6, 0x42, 0x40, 0x00, 0x30, 0x88, 0x03, 0x00, 0x00, 0x38, 0x63, 0x00, 0x01, 0x89, 0x24, 0x00, 0x00, 0x38, 0x84, 0x00, 0x01, 0x7F, 0x89, 0x00, 0x00};
		u8 printf_symbol_flag[] = {0xFB, 0xA1, 0x00, 0x98, 0x7C, 0x7D, 0x1B, 0x78, 0x7F, 0x63, 0xDB, 0x78, 0xF8, 0xE1, 0x01, 0x00, 0xF9, 0x01, 0x01, 0x08, 0xF9, 0x21, 0x01, 0x10, 0xF9, 0x41, 0x01, 0x18, 0xFB, 0x81, 0x00, 0x90};
		u8 printfnull_symbol_flag[] = {0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x9C, 0x23, 0x78, 0x7C, 0x7D, 0x1B, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x4B, 0xFF, 0xFF, 0xFF, 0xE8, 0x01, 0x00, 0xA0, 0x7F, 0xA4, 0xEB, 0x78, 0xEB, 0xA1, 0x00, 0x78};
		u8 sprintf_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0xA1, 0x00, 0xC0, 0xF8, 0x01, 0x00, 0x90, 0x38, 0x01, 0x00, 0xC0};
		u8 snprintf_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0xC1, 0x00, 0xD8, 0xF8, 0x01, 0x00, 0xA0, 0x38, 0x01, 0x00, 0xD8, 0xF8, 0x61, 0x00, 0x78, 0x90, 0x81, 0x00, 0x80, 0x7C, 0xA3, 0x2B, 0x78};
		u8 strcpy_symbol_flag[] = {0x88, 0x04, 0x00, 0x00, 0x2F, 0x80, 0x00, 0x00, 0x98, 0x03, 0x00, 0x00, 0x4D, 0x9E, 0x00, 0x20};
		u8 strncpy_symbol_flag[] = {0x2C, 0x25, 0x00, 0x00, 0x4D, 0x82, 0x00, 0x20, 0x88, 0x04, 0x00, 0x00, 0x7C, 0x6B, 0x1B, 0x78, 0x39, 0x40, 0x00, 0x00, 0x2F, 0x80, 0x00, 0x00, 0x98, 0x03, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x34};
		u8 strlen_symbol_flag[] = {0x7C, 0x69, 0x1B, 0x78, 0x38, 0x60, 0x00, 0x00, 0x88, 0x09, 0x00, 0x00, 0x2F, 0x80, 0x00, 0x00, 0x4D, 0x9E, 0x00, 0x20, 0x7D, 0x23, 0x4B, 0x78, 0x8C, 0x03, 0x00, 0x01, 0x2F, 0x80, 0x00, 0x00};
		u8 strcat_symbol_flag[] = {0x88, 0x03, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x2F, 0x80, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x10, 0x8C, 0x09, 0x00, 0x01, 0x2F, 0x80, 0x00, 0x00, 0x40, 0x9E, 0xFF, 0xF8, 0x88, 0x04, 0x00, 0x00};
		u8 strcmp_symbol_flag[] = {0x88, 0x03, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x89, 0x64, 0x00, 0x00, 0x7F, 0x8B, 0x00, 0x00, 0x7C, 0x0B, 0x00, 0x50, 0x40, 0x9E, 0x00, 0x2C, 0x2F, 0x8B, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x0C};
		u8 strncmp_symbol_flag[] = {0x2C, 0x25, 0x00, 0x00, 0x41, 0x82, 0x00, 0x50, 0x89, 0x64, 0x00, 0x00, 0x89, 0x23, 0x00, 0x00, 0x55, 0x60, 0x06, 0x3E, 0x7F, 0x89, 0x58, 0x00, 0x40, 0x9E, 0x00, 0x48, 0x2F, 0x80, 0x00, 0x00};
		u8 strchr_symbol_flag[] = {0x88, 0x03, 0x00, 0x00, 0x2F, 0x80, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x24, 0x7F, 0x80, 0x20, 0x00, 0x40, 0x9E, 0x00, 0x0C, 0x48, 0x00, 0x00, 0x24, 0x41, 0x9A, 0x00, 0x20, 0x8C, 0x03, 0x00, 0x01};
		u8 spin_lock_irqsave_ex_symbol_flag[] = {0x7C, 0x20, 0x04, 0xAC, 0x2F, 0x85, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0x20, 0x00, 0x00, 0x90, 0x03, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x0C, 0x7C, 0x81, 0x01, 0x64, 0x4E, 0x80, 0x00, 0x20, 0x61, 0x29, 0x80, 0x02, 0x7D, 0x21, 0x01, 0x64, 0x4E, 0x80, 0x00, 0x20};
		u8 spin_unlock_irqrestore_ex_symbol_flag[] = {0x7C, 0x20, 0x04, 0xAC, 0x2F, 0x85, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0x20, 0x00, 0x00, 0x90, 0x03, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x0C, 0x7C, 0x81, 0x01, 0x64, 0x4E, 0x80, 0x00, 0x20};
		u8 load_process_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x11, 0xFA, 0xC1, 0x00, 0xA0, 0xFB, 0x61, 0x00, 0xC8, 0xFB, 0x81, 0x00, 0xD0, 0x7C, 0x7B, 0x1B, 0x78, 0x7C, 0xB6, 0x2B, 0x78, 0x7C, 0x9C, 0x23, 0x78};
		u8 ppu_thread_create_symbol_flag[] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x81, 0xFB, 0xC1, 0x00, 0x70, 0xFB, 0xE1, 0x00, 0x78, 0x7C, 0x7E, 0x1B, 0x78, 0x7C, 0xDF, 0x33, 0x78, 0x91, 0x81, 0x00, 0x88, 0x7C, 0x08, 0x02, 0xA6};
		u8 ppu_thread_exit_symbol_flag[] = {0x80, 0x03, 0x00, 0x90, 0x54, 0x00, 0x04, 0x62, 0x2F, 0x80, 0x00, 0x00, 0x40, 0xDE, 0x00, 0x1C};
		u8 ppu_thread_join_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x80, 0xF8, 0x01, 0x00, 0xB0, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xC1, 0x00, 0x90, 0x7C, 0x7D, 0x1B, 0x78, 0xFB, 0xE1, 0x00, 0x98};
		u8 ppu_thread_delay_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x01, 0x7C, 0x08, 0x02, 0xA6, 0xFA, 0xC1, 0x00, 0xB0, 0xFA, 0xE1, 0x00, 0xB8, 0xFB, 0x61, 0x00, 0xD8, 0xFB, 0xA1, 0x00, 0xE8, 0xFB, 0xC1, 0x00, 0xF0, 0xFB, 0x01, 0x00, 0xC0};
		u8 create_user_thread2_symbol_flag[] = {0xF8, 0x21, 0xFE, 0xF1, 0x7C, 0x08, 0x02, 0xA6, 0xFA, 0x81, 0x00, 0xB0, 0xF8, 0x01, 0x01, 0x20, 0x80, 0x09, 0x00, 0x28, 0x7C, 0xD4, 0x33, 0x78, 0xFA, 0xA1, 0x00, 0xB8, 0xFA, 0xC1, 0x00, 0xC0};
		u8 start_thread_symbol_flag[] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x61, 0xFB, 0x41, 0x00, 0x70, 0xFB, 0x61, 0x00, 0x78, 0xFB, 0x81, 0x00, 0x80, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xC1, 0x00, 0x90, 0xFB, 0xE1, 0x00, 0x98};
		u8 run_thread_symbol_flag[] = {0x7C, 0x64, 0x1B, 0x78, 0xE8, 0x63, 0x00, 0x48, 0x48, 0x00, 0xFF, 0xFF, 0xF8, 0x21, 0xFF, 0x71};
		u8 register_thread_symbol_flag[] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x71, 0x2C, 0x24, 0x00, 0x00, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x9F, 0x23, 0x78, 0x7C, 0x7E, 0x1B, 0x78};
		u8 allocate_user_stack_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xB0, 0xE8, 0x03, 0x00, 0x30, 0x38, 0xC1, 0x00, 0x70, 0xFB, 0xC1, 0x00, 0x90, 0x2F, 0xA0, 0x00, 0x00};
		u8 mutex_create_symbol_flag[] = {0x2F, 0x85, 0x00, 0x20, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xA0, 0x7C, 0xBF, 0x2B, 0x78};
		u8 mutex_destroy_symbol_flag[] = {0x2F, 0xA3, 0x00, 0x00, 0x3C, 0x00, 0x80, 0x01, 0x60, 0x00, 0x00, 0x0A, 0x41, 0xDE, 0x00, 0x1C};
		u8 event_port_create_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0x38, 0xA0, 0x00, 0x00, 0x7C, 0x7E, 0x1B, 0x78, 0x7C, 0x9D, 0x23, 0x78, 0x38, 0x60, 0x00, 0x20};
		u8 event_port_destroy_symbol_flag[] = {0xE8, 0x01, 0x00, 0xA0, 0xEB, 0x81, 0x00, 0x70, 0x7F, 0xA3, 0x07, 0xB4, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xA1, 0x00, 0x78, 0x38, 0x21, 0x00, 0x90, 0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0xFF, 0x38, 0x80, 0x00, 0x00, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xA1, 0x00, 0x78};
		u8 event_port_connect_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0x78, 0xEB, 0x62, 0xFF, 0xFF, 0x38, 0xA0, 0x00, 0x00, 0xF8, 0x01, 0x00, 0xB0, 0xFB, 0x81, 0x00, 0x80, 0xFB, 0xA1, 0x00, 0x88};
		u8 event_port_disconnect_symbol_flag[] = {0x4B, 0xFF, 0xFF, 0x4C, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xEB, 0x82, 0xFF, 0xFF, 0x38, 0x80, 0x00, 0x00, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xA1, 0x00, 0x78, 0x38, 0xA0, 0x00, 0x00};
		u8 event_queue_create_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x98, 0xF8, 0x01, 0x00, 0xB0, 0x38, 0x06, 0xFF, 0xFF, 0x3F, 0xE0, 0x80, 0x01, 0x2B, 0x80, 0x00, 0x7E, 0x38, 0x04, 0xFF, 0xFF};
		u8 event_queue_destroy_symbol_flag[] = {0xEB, 0xC1, 0x00, 0x90, 0xEB, 0xE1, 0x00, 0x98, 0x7C, 0x08, 0x03, 0xA6, 0x7D, 0x23, 0x07, 0xB4};
		u8 event_queue_receive_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x98, 0xF8, 0x01, 0x00, 0xB0, 0x81, 0x23, 0x00, 0x88, 0x3F, 0xE0, 0x80, 0x01, 0x38, 0x00, 0x00, 0x00, 0x2F, 0x89, 0x00, 0x01};
		u8 cellFsOpen_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x00, 0x70, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0xA1, 0x00, 0x98, 0xFB, 0xC1, 0x00, 0xA0, 0x7C, 0x7D, 0x1B, 0x78};
		u8 cellFsClose_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x90, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xA1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xB0, 0x7C, 0x7D, 0x1B, 0x78};
		u8 cellFsRead_symbol_flag[] = {0x2C, 0x26, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0x3D, 0x20, 0x80, 0x01, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xE1, 0x00, 0x80, 0xF8, 0x01, 0x00, 0xA0, 0x7C, 0xDF, 0x33, 0x78};
		u8 cellFsWrite_symbol_flag[] = {0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0x7C, 0xDA, 0x33, 0x78, 0x7C, 0xBB, 0x2B, 0x78};
		u8 cellFsLseek_symbol_flag[] = {0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0x7C, 0xDA, 0x33, 0x78, 0x7C, 0x9B, 0x23, 0x78}; 
		u8 cellFsStat_symbol_flag[] = {0x2C, 0x23, 0x00, 0x00, 0x7C, 0x7F, 0x1B, 0x78, 0x3F, 0x80, 0x80, 0x01, 0x7F, 0xA3, 0xEB, 0x78, 0x7F, 0xE4, 0xFB, 0x78, 0x63, 0x9C, 0x00, 0x04, 0x41, 0x82, 0x00, 0x2C, 0x48, 0x00, 0x04, 0xC5};
		u8 cellFsUnlink_internal_symbol_flag[] = {0xF8, 0x21, 0xFE, 0xF1, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x24, 0x00, 0x00, 0xFB, 0xE1, 0x01, 0x08, 0x3F, 0xE0, 0x80, 0x01, 0xFB, 0x81, 0x00, 0xF0, 0xFB, 0xA1, 0x00, 0xF8, 0xFB, 0xC1, 0x01, 0x00};
		u8 cellFsUtilMount_symbol_flag[] = {0x7C, 0x64, 0x1B, 0x78, 0x7C, 0x05, 0x03, 0x78, 0x38, 0xE0, 0x00, 0x00, 0xE9, 0x3E, 0x80, 0xB0, 0xEB, 0xC1, 0xFF, 0xF0, 0xE8, 0x69, 0x00, 0x00, 0x4B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xFF, 0xFF, 0xFF, 0x3B, 0xFF, 0x00, 0x80};		
		u8 pathdup_from_user_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x21, 0x00, 0x78, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0xC1, 0x00, 0xA0, 0x7C, 0x7A, 0x1B, 0x78};
		u8 open_path_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x80, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xE1, 0x00, 0x98, 0xFB, 0x41, 0x00, 0x70, 0xFB, 0x61, 0x00, 0x78, 0xF8, 0x01, 0x00, 0xB0, 0x7C, 0x9C, 0x23, 0x78};
		u8 open_fs_object_symbol_flag[] = {0x4B, 0xFF, 0xBB, 0xBB, 0x7D, 0x80, 0x00, 0x26, 0xF8, 0xBB, 0xBB, 0xBB, 0xFB};		
		u8 close_fs_object_symbol_flag[] = {0xEB, 0xE1, 0x00, 0x78, 0x7C, 0x08, 0x03, 0xA6, 0x38, 0x21, 0x00, 0x80, 0x4E, 0x80, 0x00, 0x20, 0x7C, 0x83, 0x23, 0x78, 0x38, 0xA0, 0x00, 0x00, 0x38, 0x80, 0x00, 0x00};
		u8 storage_get_device_info_symbol_flag[] = {0x7D, 0x49, 0x03, 0xA6, 0x4E, 0x80, 0x04, 0x21, 0xE8, 0x01, 0x00, 0xB0, 0x7C, 0x63, 0x07, 0xB4, 0xEB, 0x61, 0x00, 0x78, 0xEB, 0x81, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xA1, 0x00, 0x88, 0xEB, 0xC1, 0x00, 0x90, 0xEB, 0xE1, 0x00, 0x98, 0x38, 0x21, 0x00, 0xA0, 0x4E, 0x80, 0x00, 0x20};
		u8 storage_open_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x11, 0xF8, 0x01, 0x01, 0x00, 0xFB, 0xA1, 0x00, 0xD8, 0xF8, 0x61, 0x01, 0x20, 0xEB, 0xA9, 0x00, 0x00, 0xFB, 0x41, 0x00, 0xC0, 0x7C, 0x9A, 0x23, 0x78};
		u8 storage_open_symbol_flag1[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x61, 0x01, 0x20, 0x38, 0x61, 0x01, 0x20, 0xFB, 0x01, 0x00, 0xB0, 0xFB, 0x21, 0x00, 0xB8, 0xFB, 0x41, 0x00, 0xC0, 0xFB, 0x81, 0x00, 0xD0, 0xFB, 0xA1, 0x00, 0xD8};
		u8 storage_close_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x51, 0xF8, 0x01, 0x00, 0xC0, 0xFB, 0xE1, 0x00, 0xA8, 0xFB, 0x81, 0x00, 0x90, 0xEB, 0xE9, 0x00, 0x00, 0x7C, 0x7C, 0x1B, 0x78, 0x38, 0x80, 0x00, 0x00};
		u8 storage_read_symbol_flag[] = {0xEA, 0xE1, 0x00, 0xB8, 0xEB, 0x01, 0x00, 0xC0, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0x21, 0x00, 0xC8, 0xEB, 0x41, 0x00, 0xD0, 0xEB, 0x61, 0x00, 0xD8, 0xEB, 0x81, 0x00, 0xE0, 0xEB, 0xA1, 0x00, 0xE8, 0xEB, 0xC1, 0x00, 0xF0, 0xEB, 0xE1, 0x00, 0xF8, 0x38, 0x21, 0x01, 0x00, 0x4E, 0x80, 0x00, 0x20, 0x48, 0x00, 0xFF, 0xFF, 0x7F, 0xE3, 0xFB, 0x78, 0x48, 0x00, 0xFF, 0xFF, 0x2F, 0x83, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x18, 0x93, 0xD7, 0x00, 0x00, 0x7F, 0xE3, 0xFB, 0x78, 0x48, 0x00, 0xFF, 0xFF, 0x7C, 0x7D, 0x1B, 0x78, 0x4B, 0xFF, 0xFF, 0x68, 0x93, 0x97, 0x00, 0x00, 0x4B, 0xFF, 0xFF, 0xEC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7C, 0x08, 0x02, 0xA6};
		u8 storage_send_device_command_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFE, 0xF1, 0xF8, 0x01, 0x01, 0x20, 0xFB, 0xE1, 0x01, 0x08, 0x7C, 0x7F, 0x1B, 0x78, 0xE8, 0x6B, 0x00, 0x00, 0xFB, 0xFF, 0x00, 0xFF, 0xFB, 0xC1, 0x01, 0x00};
		u8 storage_map_io_memory_symbol_flag[] = {0xE9, 0x4A, 0x00, 0x00, 0x7D, 0x49, 0x03, 0xA6, 0x4E, 0x80, 0x04, 0x21, 0xE8, 0x01, 0x00, 0xA0, 0x7C, 0x63, 0x07, 0xB4, 0xEB, 0x81, 0x00, 0x70, 0xEB, 0xA1, 0x00, 0x78, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xC1, 0x00, 0x80, 0xEB, 0xE1, 0x00, 0x88, 0x38, 0x21, 0x00, 0x90, 0x4E, 0x80, 0x00, 0x20};
		u8 storage_unmap_io_memory_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xE1, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x70, 0xEB, 0xE9, 0x00, 0x00, 0x7C, 0x9C, 0x23, 0x78, 0xFB, 0xC1, 0x00, 0x80};
		u8 storage_unmap_io_memory_symbol_flag1[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x61, 0x00, 0xC0, 0x38, 0x61, 0x00, 0xC0, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xA0};
		u8 storage_internal_get_device_object_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0xE8, 0x03, 0x00, 0x00, 0x7C, 0xBD, 0x2B, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0x2F, 0xA0, 0x00, 0x00, 0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x9E, 0x23, 0x78, 0x40, 0x9E, 0x00, 0x2C, 0x3C, 0x60, 0x80, 0x01, 0x60, 0x63, 0x00, 0x05, 0xE8, 0x01, 0x00, 0xA0, 0x7C, 0x63, 0x07, 0xB4, 0xEB, 0xA1, 0x00, 0x78, 0xEB, 0xC1, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xE1, 0x00, 0x88, 0x38, 0x21, 0x00, 0x90, 0x4E, 0x80, 0x00, 0x20, 0x78, 0x89, 0x00, 0x20, 0x81, 0x63, 0x00, 0x40, 0xE9, 0x43, 0x00, 0x38};
		u8 decrypt_func_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7C, 0x1B, 0x78, 0x7C, 0x9D, 0x23, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x4B, 0xFF, 0xFF, 0x95};
		u8 lv1_call_99_wrapper_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7D, 0x1B, 0x78, 0xFB, 0x81, 0x00, 0x70, 0x38, 0x63, 0x00, 0x80, 0x7C, 0x9C, 0x23, 0x78, 0xF8, 0x01, 0x00, 0xA0};
		u8 modules_verification_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0x2B, 0x84, 0x00, 0x36, 0xF8, 0x01, 0x00, 0x80, 0x41, 0x9D, 0x00, 0xFC};
		u8 prx_load_module_symbol_flag[] = { 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0x7C, 0xBC, 0x2B, 0x78, 0x38, 0xA0, 0x00, 0x01, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88};
		u8 prx_start_module_symbol_flag[] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFE, 0xF1, 0xFB, 0x21, 0x00, 0xD8, 0xFB, 0x41, 0x00, 0xE0, 0x7C, 0x79, 0x07, 0xB4, 0x7C, 0x9A, 0x23, 0x78, 0xFB, 0x01, 0x00, 0xD0, 0xFB, 0x81, 0x00, 0xF0};
		u8 prx_stop_module_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xC1, 0x00, 0x90, 0x7C, 0x7D, 0x1B, 0x78, 0x7C, 0x9E, 0x23, 0x78, 0xFB, 0x81, 0x00, 0x80, 0xF8, 0x01, 0x00, 0xB0};
		u8 prx_unload_module_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x80, 0xFB, 0xC1, 0x00, 0x90, 0x7C, 0x7C, 0x07, 0xB4, 0x7C, 0x9E, 0x23, 0x78, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xE1, 0x00, 0x98};
		u8 prx_get_module_info_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x21, 0x00, 0x78, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xA1, 0x00, 0x98, 0x7C, 0xBB, 0x2B, 0x78};
		u8 prx_get_module_list_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x00, 0x70, 0xFB, 0x21, 0x00, 0x78, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xA1, 0x00, 0x98, 0x7C, 0xF9, 0x3B, 0x78, 0x7D, 0x18, 0x43, 0x78, 0x7C, 0xDA, 0x33, 0x78, 0x7C, 0x7D, 0x1B, 0x78};
		u8 extend_kstack_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7D, 0x1B, 0x78};
		u8 get_pseudo_random_number_symbol_flag[] = {0x7C, 0x85, 0x23, 0x78, 0x7C, 0x04, 0x03, 0x78, 0x48, 0x00, 0x04, 0x04, 0x48, 0x00, 0x01, 0xE4, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xC1, 0x00, 0x80};
		u8 syscall_call_offset_flag[] = {0x4E, 0x80, 0x00, 0x21, 0x38, 0x21, 0x00, 0x70, 0xF8, 0x21, 0xFF, 0xB1, 0xF8, 0x61, 0x00, 0x08, 0xF8, 0x81, 0x00, 0x10, 0xF8, 0xA1, 0x00, 0x18, 0xF8, 0xC1, 0x00, 0x20, 0xF8, 0xE1, 0x00, 0x28};
		u8 read_bdvd0_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x01, 0x10, 0x7C, 0x78, 0x1B, 0x78, 0xF8, 0x01, 0x01, 0x60, 0xF9, 0xC1, 0x00, 0xC0, 0xFB, 0xC1, 0x01, 0x40, 0x7C, 0x8E, 0x23, 0x78};
		u8 read_bdvd1_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0xB0, 0xF8, 0x01, 0x00, 0xE0, 0xEB, 0x83, 0x00, 0x20, 0x7C, 0xA0, 0x2B, 0x78, 0xFA, 0xE1, 0x00, 0x88, 0x2F, 0xBC, 0x00, 0x00};
		u8 read_bdvd2_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0xA8, 0xF8, 0x01, 0x00, 0xC0, 0x7C, 0x7F, 0x1B, 0x78, 0xE8, 0x63, 0x00, 0x90, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90};
		u8 process_map_caller_call_flag[] = {0x2F, 0x83, 0x00, 0x00, 0x7C, 0x7D, 0x1B, 0x78, 0x41, 0x9E, 0xFF, 0x1C, 0x80, 0x7B, 0x00, 0x00};
		u8 fsloop_open_call_flag[] = {0x7C, 0x63, 0x07, 0xB4, 0x4B, 0xFF, 0xFF, 0xC0, 0x80, 0x63, 0x00, 0x08, 0x80, 0xAA, 0x00, 0x18, 0x7C, 0x63, 0x07, 0xB4, 0xE8, 0xCA, 0x00, 0x20, 0x7C, 0xA5, 0x07, 0xB4};
		u8 fsloop_close_call_flag[] = {0x7C, 0x63, 0x07, 0xB4, 0x4B, 0xFF, 0xFF, 0x70, 0x80, 0x63, 0x00, 0x08, 0xE8, 0xCA, 0x00, 0x20, 0x7C, 0x63, 0x07, 0xB4, 0xE8, 0x8A, 0x00, 0x10, 0xE8, 0xAA, 0x00, 0x18};
		u8 fsloop_read_call_flag[] = {0x7C, 0x63, 0x07, 0xB4, 0x4B, 0xFF, 0xFF, 0x30, 0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x00, 0x90, 0xFB, 0x61, 0x00, 0xA8, 0xFB, 0xA1, 0x00, 0xB8};
		u8 io_rtoc_entry_1_flag[] = {0x60, 0x63, 0x00, 0x02, 0x54, 0x00, 0x07, 0xFE, 0x2F, 0x24, 0xFF, 0xFF, 0x2F, 0x80, 0x00, 0x00};
		u8 io_sub_rtoc_entry_1_flag[] = {0xE9, 0x7E, 0x81, 0x68, 0xEB, 0x9E, 0x81, 0x40, 0xEB, 0xBE, 0x81, 0x70};
		u8 decrypt_rtoc_entry_2_flag[] = {0x4B, 0xFF, 0xFF, 0xFF, 0x39, 0x20, 0x00, 0x00, 0x4B, 0xFF, 0xFF, 0xCC, 0x2C, 0x24, 0x00, 0x00};
		u8 storage_rtoc_entry_1_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x51, 0xF8, 0x01, 0x00, 0xC0, 0xFB, 0xE1, 0x00, 0xA8, 0x7C, 0x9F, 0x23};
		u8 device_event_flag[] = {0x78, 0x05, 0x06, 0x20, 0xE8, 0xCA, 0x00, 0x38, 0x7D, 0x05, 0x2B, 0x78, 0xE9, 0x2B, 0x00, 0x00, 0xE8, 0x69, 0x00, 0x40};
		u8 process_rtoc_entry_1_flag[] = {0x3F, 0xC0, 0x80, 0x01, 0x63, 0xDE, 0x00, 0x05, 0xE8, 0x7D, 0x00, 0x00};
		u8 patch_func2_flag[] = {0x41, 0x9A, 0xFF, 0xAC, 0x3D, 0x20, 0x80, 0x01, 0x61, 0x29, 0x00, 0x09, 0x4B, 0xFF, 0xFF, 0xA0, 0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x90, 0x7C, 0x9E, 0x23, 0x78};
		u8 user_thread_prio_patch_flag[] = {0x3F, 0xE0, 0x80, 0x01, 0x2B, 0x80, 0x0E, 0x7F, 0x80, 0x01, 0x00, 0x94, 0x63, 0xFF, 0x00, 0x02}; // +0x10
		u8 shutdown_patch_offset_flag[] = {0x41, 0x82, 0xFE, 0xFC, 0x7F, 0x83, 0xE3, 0x78, 0x7F, 0x64, 0xDB, 0x78, 0x7F, 0xC5, 0xF3, 0x78};
		u8 shutdown_copy_params_call_flag[] = {0x2F, 0x83, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x5C, 0x7F, 0xC6, 0xF3, 0x78, 0x7F, 0xA3, 0xEB, 0x78, 0x38, 0x80, 0x00, 0x01, 0x7F, 0x65, 0xDB, 0x78};		
		
		memcpy(&TOC, &memLV2[0x3000], 8);
		TOC = reverse64(TOC);
		TOC = TOC - 0x8000000000000000ULL; 
		
		char D='C';
		u64 n;
		
		for(n=0; n<size ; n++) {
			if(0x340000 < n && n <size) {
				if(FIRMWARE == 0) {
					if(n-(n>>4)*0x10 == 0 || n-(n>>4)*0x10 == 8)
					if(memcmp((char *) &memLV2[n], (char *) flag_fw1, 8) > 0) 
					if(memcmp((char *) &memLV2[n], (char *) flag_fw2, 8) < 0) {
						memcpy(&FIRMWARE, &memLV2[n], 8);
						FIRMWARE = reverse64(FIRMWARE);
						FIRMWARE = FIRMWARE/100;
						if(FIRMWARE > 999 || FIRMWARE < 340) FIRMWARE=0;
					}
				}
			}
			
			if(0x40000 < n && n <0x90000) {
				if(!memcmp((char *) &memLV2[n], (char *) flag_alloc, 0x20)) {
					OFF_alloc = n + 0x10;
				}
				if(!memcmp((char *) &memLV2[n], (char *) flag_memcpy, 0x20)) {
					OFF_memcpy = n;
				}
				if(!memcmp((char *) &memLV2[n], (char *) flag_memset, 0x20)) {
					OFF_memset = n;
				}
			}
			if(0x200000 < n && n <0x300000) {
				if(!memcmp((char *) &memLV2[n], (char *) flag_memory_patch_func, 0x20)) {
					OFF_memory_patch_func = n - 0x4;
				}
			}
			if(!memcmp((char *) &memLV2[n+0x4], (char *) "/", 1))
			if(!memcmp((char *) &memLV2[n+0x7], (char *) "/", 1))
			if(!memcmp((char *) &memLV2[n+0xA], (char *) " ", 1))
			if(!memcmp((char *) &memLV2[n+0xD], (char *) ":", 1))
			{
				FW_DATE_OFFSET = n;
				memcpy(&FW_DATE_1, &memLV2[n], 8);
				memcpy(&FW_DATE_2, &memLV2[n+8], 8);
				FW_DATE_1 = reverse64(FW_DATE_1);
				FW_DATE_2 = reverse64(FW_DATE_2);
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
			if(0x250000 < n && n <0x350000) {
				if(!memcmp((char *) &memLV2[n], (char *) flag_firmware_offset, 0x20)) {
					FIRMWARE_OFFSET = n + 0x20;
					if(!memcmp((char *) &memLV2[FIRMWARE_OFFSET], (char *) "DEH", 0x3)) {
						D = 'H';
					}
					if(!memcmp((char *) &memLV2[FIRMWARE_OFFSET], (char *) "DEX", 0x3)) {
						D = 'D';
					}
					if(!memcmp((char *) &memLV2[FIRMWARE_OFFSET], (char *) "CEX", 0x3)) {
						D = 'C';
					}
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
			
			if(compare(0xFF, (char *) &memLV2[n], (char *) open_shared_kernel_object_symbol_flag, sizeof(open_shared_kernel_object_symbol_flag))) {
				open_shared_kernel_object_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) close_kernel_object_handle_symbol_flag, sizeof(close_kernel_object_handle_symbol_flag))) {
				close_kernel_object_handle_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) open_kernel_object_symbol_flag, sizeof(open_kernel_object_symbol_flag))) {
				open_kernel_object_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) alloc_symbol_flag, sizeof(alloc_symbol_flag))) {
				alloc_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) dealloc_symbol_flag, sizeof(dealloc_symbol_flag))) {
				dealloc_symbol = n - 4;
			}		
			if(compare(0xFF, (char *) &memLV2[n], (char *) copy_to_user_symbol_flag, sizeof(copy_to_user_symbol_flag))) {
				copy_to_user_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) copy_from_user_symbol_flag, sizeof(copy_from_user_symbol_flag))) {
				copy_from_user_symbol = n;
			}		
			if(compare(0xFF, (char *) &memLV2[n], (char *) copy_to_process_symbol_flag, sizeof(copy_to_process_symbol_flag))) {
				copy_to_process_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) copy_from_process_symbol_flag, sizeof(copy_from_process_symbol_flag))) {
				copy_from_process_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) page_allocate_symbol_flag, sizeof(page_allocate_symbol_flag))) {
				page_allocate_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) page_free_symbol_flag, sizeof(page_free_symbol_flag))) {
				page_free_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) page_export_to_proc_symbol_flag, sizeof(page_export_to_proc_symbol_flag))) {
				page_export_to_proc_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) page_unexport_from_proc_symbol_flag, sizeof(page_unexport_from_proc_symbol_flag))) {
				page_unexport_from_proc_symbol = n - 8;
			}			
			if(compare(0xFF, (char *) &memLV2[n], (char *) kernel_ea_to_lpar_addr_symbol_flag, sizeof(kernel_ea_to_lpar_addr_symbol_flag))) {
				kernel_ea_to_lpar_addr_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) map_process_memory_symbol_flag, sizeof(map_process_memory_symbol_flag))) {
				map_process_memory_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) memcpy_symbol_flag, sizeof(memcpy_symbol_flag))) {
				memcpy_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) memset_symbol_flag, sizeof(memset_symbol_flag))) {
				memset_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) memcmp_symbol_flag, sizeof(memcmp_symbol_flag))) {
				memcmp_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) printf_symbol_flag, sizeof(printf_symbol_flag))) {
				printf_symbol = n - 0x10;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) printfnull_symbol_flag, sizeof(printfnull_symbol_flag))) {
				printfnull_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) sprintf_symbol_flag, sizeof(sprintf_symbol_flag))) {
				sprintf_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) snprintf_symbol_flag, sizeof(snprintf_symbol_flag))) {
				snprintf_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) strcpy_symbol_flag, sizeof(strcpy_symbol_flag))) {
				strcpy_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) strncpy_symbol_flag, sizeof(strncpy_symbol_flag))) {
				strncpy_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) strlen_symbol_flag, sizeof(strlen_symbol_flag))) {
				strlen_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) strcat_symbol_flag, sizeof(strcat_symbol_flag))) {
				strcat_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) strcmp_symbol_flag, sizeof(strcmp_symbol_flag))) {
				strcmp_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) strncmp_symbol_flag, sizeof(strncmp_symbol_flag))) {
				strncmp_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) strchr_symbol_flag, sizeof(strchr_symbol_flag))) {
				strchr_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) spin_lock_irqsave_ex_symbol_flag, sizeof(spin_lock_irqsave_ex_symbol_flag))) {
				spin_lock_irqsave_ex_symbol = n + 0x2C;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) spin_unlock_irqrestore_ex_symbol_flag, sizeof(spin_unlock_irqrestore_ex_symbol_flag))) {
				spin_unlock_irqrestore_ex_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) load_process_symbol_flag, sizeof(load_process_symbol_flag))) {
				load_process_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) ppu_thread_create_symbol_flag, sizeof(ppu_thread_create_symbol_flag))) {
				ppu_thread_create_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) ppu_thread_exit_symbol_flag, sizeof(ppu_thread_exit_symbol_flag))) {
				ppu_thread_exit_symbol = n - 0x18;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) ppu_thread_join_symbol_flag, sizeof(ppu_thread_join_symbol_flag))) {
				ppu_thread_join_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) ppu_thread_delay_symbol_flag, sizeof(ppu_thread_delay_symbol_flag))) {
				ppu_thread_delay_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) create_user_thread2_symbol_flag, sizeof(create_user_thread2_symbol_flag))) {
				create_user_thread2_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) start_thread_symbol_flag, sizeof(start_thread_symbol_flag))) {
				start_thread_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) run_thread_symbol_flag, sizeof(run_thread_symbol_flag))) {
				run_thread_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) register_thread_symbol_flag, sizeof(register_thread_symbol_flag))) {
				register_thread_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) allocate_user_stack_symbol_flag, sizeof(allocate_user_stack_symbol_flag))) {
				allocate_user_stack_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) mutex_create_symbol_flag, sizeof(mutex_create_symbol_flag))) {
				mutex_create_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) mutex_destroy_symbol_flag, sizeof(mutex_destroy_symbol_flag))) {
				mutex_destroy_symbol = n - 0x18;
				mutex_lock_symbol = n - 0x20;
				mutex_unlock_symbol = n - 0x28;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) event_port_create_symbol_flag, sizeof(event_port_create_symbol_flag))) {
				event_port_create_symbol = n;
				event_port_send_symbol = n - 8;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) event_port_destroy_symbol_flag, sizeof(event_port_destroy_symbol_flag))) {
				event_port_destroy_symbol = n + 0x1C;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) event_port_connect_symbol_flag, sizeof(event_port_connect_symbol_flag))) {
				event_port_connect_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) event_port_disconnect_symbol_flag, sizeof(event_port_disconnect_symbol_flag))) {
				event_port_disconnect_symbol = n + 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) event_queue_create_symbol_flag, sizeof(event_queue_create_symbol_flag))) {
				event_queue_create_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) event_queue_destroy_symbol_flag, sizeof(event_queue_destroy_symbol_flag))) {
				event_queue_destroy_symbol = n + 0x18;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) event_queue_receive_symbol_flag, sizeof(event_queue_receive_symbol_flag))) {
				event_queue_receive_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) cellFsOpen_symbol_flag, sizeof(cellFsOpen_symbol_flag))) {
				cellFsOpen_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) cellFsClose_symbol_flag, sizeof(cellFsClose_symbol_flag))) {
				cellFsClose_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) cellFsRead_symbol_flag, sizeof(cellFsRead_symbol_flag))) {
				cellFsRead_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) cellFsWrite_symbol_flag, sizeof(cellFsWrite_symbol_flag))) {
				cellFsWrite_symbol = n - 0x10;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) cellFsLseek_symbol_flag, sizeof(cellFsLseek_symbol_flag))) {
				cellFsLseek_symbol = n - 0x10;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) cellFsStat_symbol_flag, sizeof(cellFsStat_symbol_flag))) {
				cellFsStat_symbol = n - 0x3C;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) cellFsUnlink_internal_symbol_flag, sizeof(cellFsUnlink_internal_symbol_flag))) {
				cellFsUnlink_internal_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) cellFsUtilMount_symbol_flag, sizeof(cellFsUtilMount_symbol_flag))) {
				cellFsUtilMount_symbol = n + 0x1C;
				cellFsUtilUmount_symbol = n - 0x10;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) pathdup_from_user_symbol_flag, sizeof(pathdup_from_user_symbol_flag))) {
				pathdup_from_user_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) open_path_symbol_flag, sizeof(open_path_symbol_flag))) {
				open_path_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) close_fs_object_symbol_flag, sizeof(close_fs_object_symbol_flag))) {
				close_fs_object_symbol = n + 0x10;
			}
			if(close_fs_object_symbol && !open_fs_object_symbol)
			if(compare(0xBB, (char *) &memLV2[n], (char *) open_fs_object_symbol_flag, sizeof(open_fs_object_symbol_flag)) ) {
				open_fs_object_symbol = n + 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_get_device_info_symbol_flag, sizeof(storage_get_device_info_symbol_flag))) {
				storage_get_device_info_symbol = n + 0x30;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_open_symbol_flag, sizeof(storage_open_symbol_flag))
			|| compare(0xFF, (char *) &memLV2[n], (char *) storage_open_symbol_flag1, sizeof(storage_open_symbol_flag1)) ) {
				storage_open_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_close_symbol_flag, sizeof(storage_close_symbol_flag))) {
				storage_close_symbol = n - 4;
			}
			if(!storage_read_symbol)
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_read_symbol_flag, sizeof(storage_read_symbol_flag))) {
				storage_read_symbol = n + 0x60;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_send_device_command_symbol_flag, sizeof(storage_send_device_command_symbol_flag))) {
				storage_send_device_command_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_map_io_memory_symbol_flag, sizeof(storage_map_io_memory_symbol_flag))) {
				storage_map_io_memory_symbol = n + 0x30;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_unmap_io_memory_symbol_flag, sizeof(storage_unmap_io_memory_symbol_flag))
			|| compare(0xFF, (char *) &memLV2[n], (char *) storage_unmap_io_memory_symbol_flag1, sizeof(storage_unmap_io_memory_symbol_flag1))
			) {
				storage_unmap_io_memory_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_internal_get_device_object_symbol_flag, sizeof(storage_internal_get_device_object_symbol_flag))) {
				storage_internal_get_device_object_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) decrypt_func_symbol_flag, sizeof(decrypt_func_symbol_flag))) {
				decrypt_func_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) lv1_call_99_wrapper_symbol_flag, sizeof(lv1_call_99_wrapper_symbol_flag))) {
				lv1_call_99_wrapper_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) modules_verification_symbol_flag, sizeof(modules_verification_symbol_flag))) {
				modules_verification_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) prx_load_module_symbol_flag, sizeof(prx_load_module_symbol_flag))) {
				prx_load_module_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) prx_start_module_symbol_flag, sizeof(prx_start_module_symbol_flag))) {
				prx_start_module_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) prx_stop_module_symbol_flag, sizeof(prx_stop_module_symbol_flag))) {
				prx_stop_module_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) prx_unload_module_symbol_flag, sizeof(prx_unload_module_symbol_flag))) {
				prx_unload_module_symbol =  n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) prx_get_module_info_symbol_flag, sizeof(prx_get_module_info_symbol_flag))) {
				prx_get_module_info_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) prx_get_module_list_symbol_flag, sizeof(prx_get_module_list_symbol_flag))) {
				prx_get_module_list_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) extend_kstack_symbol_flag, sizeof(extend_kstack_symbol_flag))) {
				extend_kstack_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) get_pseudo_random_number_symbol_flag, sizeof(get_pseudo_random_number_symbol_flag))) {
				get_pseudo_random_number_symbol = n - 8;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) syscall_call_offset_flag, sizeof(syscall_call_offset_flag))) {
				syscall_call_offset = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) read_bdvd0_symbol_flag, sizeof(read_bdvd0_symbol_flag))) {
				read_bdvd0_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) read_bdvd1_symbol_flag, sizeof(read_bdvd1_symbol_flag))) {
				read_bdvd1_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) read_bdvd2_symbol_flag, sizeof(read_bdvd2_symbol_flag))) {
				read_bdvd2_symbol = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) process_map_caller_call_flag, sizeof(process_map_caller_call_flag))) {
				process_map_caller_call = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) fsloop_open_call_flag, sizeof(fsloop_open_call_flag))) {
				fsloop_open_call = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) fsloop_close_call_flag, sizeof(fsloop_close_call_flag))) {
				fsloop_close_call = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) fsloop_read_call_flag, sizeof(fsloop_read_call_flag))) {
				fsloop_read_call = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) io_rtoc_entry_1_flag, sizeof(io_rtoc_entry_1_flag))) {
				memcpy(&io_rtoc_entry_1, &memLV2[n-2], 2);
				io_rtoc_entry_1 = SWAP16(io_rtoc_entry_1);
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) io_sub_rtoc_entry_1_flag, sizeof(io_sub_rtoc_entry_1_flag))) {
				memcpy(&io_sub_rtoc_entry_1, &memLV2[n-2], 2);
				io_sub_rtoc_entry_1 = SWAP16(io_sub_rtoc_entry_1);
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) decrypt_rtoc_entry_2_flag, sizeof(decrypt_rtoc_entry_2_flag))) {
				memcpy(&decrypt_rtoc_entry_2, &memLV2[n-2], 2);
				decrypt_rtoc_entry_2 = SWAP16(decrypt_rtoc_entry_2);
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_rtoc_entry_1_flag, sizeof(storage_rtoc_entry_1_flag))) {
				memcpy(&storage_rtoc_entry_1, &memLV2[n-2], 2);
				storage_rtoc_entry_1 = SWAP16(storage_rtoc_entry_1);
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) device_event_flag, sizeof(device_event_flag))) {
				memcpy(&device_event_rtoc_entry_1, &memLV2[n-2], 2);
				device_event_rtoc_entry_1 = SWAP16(device_event_rtoc_entry_1);
				device_event_port_send_call = n + 0x14;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) process_rtoc_entry_1_flag, sizeof(process_rtoc_entry_1_flag))) {
				memcpy(&process_rtoc_entry_1, &memLV2[n-2], 2);
				process_rtoc_entry_1 = SWAP16(process_rtoc_entry_1);
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) patch_func2_flag, sizeof(patch_func2_flag))) {
				patch_func2 = n + 0x10;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) user_thread_prio_patch_flag, sizeof(user_thread_prio_patch_flag))) {
				user_thread_prio_patch = n + 0x10;
				user_thread_prio_patch2 = n + 0x1C;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) shutdown_patch_offset_flag, sizeof(shutdown_patch_offset_flag))) {
				shutdown_patch_offset = n - 4;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) shutdown_copy_params_call_flag, sizeof(shutdown_copy_params_call_flag))) {
				shutdown_copy_params_call = n - 4;
			}
			
		}

		sprintf(dump, "LV1/%s", ent->d_name);
		
		f=fopen(dump, "r");
		if(f!=NULL) {
			fseek (f , 0 , SEEK_END);
			size = ftell (f);
			fseek(f, 0, SEEK_SET);
			
			if(size != 0x1000000) {
				printf("Error : bad size of your dump\n");
				fclose(f);
				return 0;
			}
			char *memLV1 = (char*) malloc (sizeof(char)*size);
			if (memLV1 == NULL) {
				printf("Error : cannot malloc");
				free(memLV1);
				fclose(f);
				return 0;
			}

			fread(memLV1,1,size, f);
			
			fclose(f);
			
			for(n=0x360000; n<size ; n++) {
				
				if( !memcmp((char *) &memLV1[n]     , (char *) flag_hv_start_offset3, 0x28)
				&&  !memcmp((char *) &memLV1[n+0x30], (char *) flag_hv_start_offset4, 0x8 ) )				
				{
					HV_START_OFFSET = n + 0x38;
				} else
				if(!memcmp((char *) &memLV1[n], (char *) flag_hv_start_offset2, 0x20)) {
					HV_START_OFFSET = n + 0x58;
				} else
				if(!memcmp((char *) &memLV1[n], (char *) flag_hv_start_offset, 0x10)) {
					HV_START_OFFSET = n - 0x8;
				}
				
				if(compare(0xFF, (char *) &memLV1[n], (char *) vsh_pos_in_ram_FLAG, sizeof(vsh_pos_in_ram_FLAG))){
					vsh_pos_in_ram = n - 0x200;
				}
				
				if(vsh_pos_in_ram)
				if(HV_START_OFFSET)
				break;
			}
			free(memLV1);
			
		} else printf("Warning : LV1 is missing, HV_START_OFFSET = unk \n");		

		if(SYSCALL_TABLE != 0) SYSCALL_TABLE = 0x8000000000000000ULL + SYSCALL_TABLE;
		if(OPEN_HOOK != 0) OPEN_HOOK = 0x8000000000000000ULL + OPEN_HOOK;
		if(BASE_ADDR != 0) BASE_ADDR = 0x8000000000000000ULL + BASE_ADDR;
		if(LV2MOUNTADDR != 0) LV2MOUNTADDR = 0x8000000000000000ULL + LV2MOUNTADDR;
		if(FIRMWARE_OFFSET != 0) FIRMWARE_OFFSET = 0x8000000000000000ULL + FIRMWARE_OFFSET;
		if(FW_DATE_OFFSET != 0) FW_DATE_OFFSET = 0x8000000000000000ULL + FW_DATE_OFFSET;
		if(OFFSET_1_IDPS != 0) OFFSET_1_IDPS = 0x8000000000000000ULL + OFFSET_1_IDPS;
		if(OFFSET_2_IDPS != 0) OFFSET_2_IDPS = 0x8000000000000000ULL + OFFSET_2_IDPS;
		
		char str[255];
		fputs("\n", common);
		sprintf(str, "#define SYSCALL_TABLE_%lld%c         0x%llXULL\n", FIRMWARE, D, SYSCALL_TABLE); fputs(str, common);
		sprintf(str, "#define HV_START_OFFSET_%lld%c       0x%06llX\n", FIRMWARE, D, HV_START_OFFSET); fputs(str, common);
		sprintf(str, "#define OFFSET_FIX_%lld%c            0x%06llX\n", FIRMWARE, D, OFFSET_FIX); fputs(str, common);
		sprintf(str, "#define OFFSET_2_FIX_%lld%c          0x%06llX\n", FIRMWARE, D, OFFSET_2_FIX); fputs(str, common);
		sprintf(str, "#define OFFSET_FIX_2B17_%lld%c       0x%06llX\n", FIRMWARE, D, OFFSET_FIX_2B17); fputs(str, common);
		sprintf(str, "#define OFFSET_FIX_LIC_%lld%c        0x%06llX\n", FIRMWARE, D, OFFSET_FIX_LIC); fputs(str, common);
		sprintf(str, "#define OFFSET_FIX_3C_%lld%c         0x%06llX\n", FIRMWARE, D, OFFSET_FIX_3C); fputs(str, common);
		sprintf(str, "#define OPEN_HOOK_%lld%c             0x%llXULL\n", FIRMWARE, D, OPEN_HOOK); fputs(str, common);
		sprintf(str, "#define BASE_ADDR_%lld%c             0x%llXULL\n", FIRMWARE, D, BASE_ADDR); fputs(str, common);
		sprintf(str, "#define LV2MOUNTADDR_%lld%c          0x%llXULL\n", FIRMWARE, D, LV2MOUNTADDR); fputs(str, common);
		sprintf(str, "#define LV2MOUNTADDR_ESIZE_%lld%c    0x%llX\n", FIRMWARE, D, LV2MOUNTADDR_ESIZE); fputs(str, common);
		sprintf(str, "#define LV2MOUNTADDR_CSIZE_%lld%c    0x%llX\n", FIRMWARE, D, LV2MOUNTADDR_CSIZE); fputs(str, common);
		//sprintf(str, "#define FIRMWARE_OFFSET_%lld%c       0x%llXULL\n", FIRMWARE, D, FIRMWARE_OFFSET); fputs(str, common);
		sprintf(str, "#define FW_DATE_OFFSET_%lld%c        0x%llXULL\n", FIRMWARE, D, FW_DATE_OFFSET); fputs(str, common);
		sprintf(str, "#define FW_DATE_1_%lld%c             0x%llXULL\n", FIRMWARE, D, FW_DATE_1); fputs(str, common);
		sprintf(str, "#define FW_DATE_2_%lld%c             0x%llXULL\n", FIRMWARE, D, FW_DATE_2); fputs(str, common);
		sprintf(str, "#define OFFSET_1_IDPS_%lld%c         0x%llXULL\n", FIRMWARE, D, OFFSET_1_IDPS); fputs(str, common);
		sprintf(str, "#define OFFSET_2_IDPS_%lld%c         0x%llXULL\n", FIRMWARE, D, OFFSET_2_IDPS); fputs(str, common);	
		
		fputs("\n", SKY);
		sprintf(str, "#ifdef CFW_%lld%c\n", FIRMWARE, D); fputs(str, SKY);
		sprintf(str, "#define alloc                   0x%llX\n", OFF_alloc); fputs(str, SKY);
		sprintf(str, "#define memory_patch_func       0x%llX\n", OFF_memory_patch_func); fputs(str, SKY);
		sprintf(str, "#define memcpy                  0x%llX\n", OFF_memcpy); fputs(str, SKY);
		sprintf(str, "#define memset                  0x%llX\n", OFF_memset); fputs(str, SKY);
		fputs("#endif\n", SKY);
		
		sprintf(temp, "#ifdef FIRMWARE_%lld%c\n\n", FIRMWARE, D); fputs(temp, symbols);
		
		sprintf(temp, "\t#define FIRMWARE_VERSION                                 0x%d\n\n", FIRMWARE); fputs(temp, symbols);
		
		fputs("\t#ifdef PS3M_API\n", symbols);
		sprintf(temp, "\t\t#define PS3MAPI_FW_VERSION                           0x%d\n", FIRMWARE); fputs(temp, symbols);
		if(D=='C') {
			    fputs("\t\t#define PS3MAPI_FW_TYPE                              \"CEX MAMBA\"\n", symbols);
		} else {
			    fputs("\t\t#define PS3MAPI_FW_TYPE                              \"DEX MAMBA\"\n", symbols);
		}
		sprintf(temp, "\t\t#define PS3MAPI_IDPS_1                               0x%llXULL\n", OFFSET_1_IDPS); fputs(temp, symbols);
		sprintf(temp, "\t\t#define PS3MAPI_IDPS_2                               0x%llXULL\n", OFFSET_2_IDPS); fputs(temp, symbols);
		sprintf(temp, "\t\t#define PS3MAPI_PSID                                 0x%llXULL\n", OFFSET_2_IDPS + 0x18); fputs(temp, symbols);	
		
		fputs("\t#endif\n\n", symbols);
		
		sprintf(temp, "\t/* lv2 */\n", FIRMWARE); fputs(temp, symbols);
		sprintf(temp, "\t#define TOC                                              0x%X\n", TOC); fputs(temp, symbols);
		sprintf(temp, "\t#define open_shared_kernel_object_symbol                 0x%X\n", open_shared_kernel_object_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define close_kernel_object_handle_symbol                0x%X\n", close_kernel_object_handle_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define open_kernel_object_symbol                        0x%X\n", open_kernel_object_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define alloc_symbol                                     0x%X\n", alloc_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define dealloc_symbol                                   0x%X\n", dealloc_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define copy_to_user_symbol                              0x%X\n", copy_to_user_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define copy_from_user_symbol                            0x%X\n", copy_from_user_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define copy_to_process_symbol                           0x%X\n", copy_to_process_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define copy_from_process_symbol                         0x%X\n", copy_from_process_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define page_allocate_symbol                             0x%X\n", page_allocate_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define page_free_symbol                                 0x%X\n", page_free_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define page_export_to_proc_symbol                       0x%X\n", page_export_to_proc_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define page_unexport_from_proc_symbol                   0x%X\n", page_unexport_from_proc_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define kernel_ea_to_lpar_addr_symbol                    0x%X\n", kernel_ea_to_lpar_addr_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define map_process_memory_symbol                        0x%X\n", map_process_memory_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define memcpy_symbol                                    0x%X\n", memcpy_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define memset_symbol                                    0x%X\n", memset_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define memcmp_symbol                                    0x%X\n", memcmp_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define printf_symbol                                    0x%X\n", printf_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define printfnull_symbol                                0x%X\n", printfnull_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define sprintf_symbol                                   0x%X\n", sprintf_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define snprintf_symbol                                  0x%X\n", snprintf_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define strcpy_symbol                                    0x%X\n", strcpy_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define strncpy_symbol                                   0x%X\n", strncpy_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define strlen_symbol                                    0x%X\n", strlen_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define strcat_symbol                                    0x%X\n", strcat_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define strcmp_symbol                                    0x%X\n", strcmp_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define strncmp_symbol                                   0x%X\n", strncmp_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define strchr_symbol                                    0x%X\n", strchr_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define spin_lock_irqsave_ex_symbol                      0x%X\n", spin_lock_irqsave_ex_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define spin_unlock_irqrestore_ex_symbol                 0x%X\n", spin_unlock_irqrestore_ex_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define load_process_symbol                              0x%X\n", load_process_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define ppu_thread_create_symbol                         0x%X\n", ppu_thread_create_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define ppu_thread_exit_symbol                           0x%X\n", ppu_thread_exit_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define ppu_thread_join_symbol                           0x%X\n", ppu_thread_join_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define ppu_thread_delay_symbol                          0x%X\n", ppu_thread_delay_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define create_user_thread2_symbol                       0x%X\n", create_user_thread2_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define start_thread_symbol                              0x%X\n", start_thread_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define run_thread_symbol                                0x%X\n", run_thread_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define register_thread_symbol                           0x%X\n", register_thread_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define allocate_user_stack_symbol                       0x%X\n", allocate_user_stack_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define mutex_create_symbol                              0x%X\n", mutex_create_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define mutex_destroy_symbol                             0x%X\n", mutex_destroy_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define mutex_lock_symbol                                0x%X\n", mutex_lock_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define mutex_unlock_symbol                              0x%X\n", mutex_unlock_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_create_symbol                         0x%X\n", event_port_create_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_destroy_symbol                        0x%X\n", event_port_destroy_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_connect_symbol                        0x%X\n", event_port_connect_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_disconnect_symbol                     0x%X\n", event_port_disconnect_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_send_symbol                           0x%X\n", event_port_send_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define event_queue_create_symbol                        0x%X\n", event_queue_create_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define event_queue_destroy_symbol                       0x%X\n", event_queue_destroy_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define event_queue_receive_symbol                       0x%X\n", event_queue_receive_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsOpen_symbol                                0x%X\n", cellFsOpen_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsClose_symbol                               0x%X\n", cellFsClose_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsRead_symbol                                0x%X\n", cellFsRead_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsWrite_symbol                               0x%X\n", cellFsWrite_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsLseek_symbol                               0x%X\n", cellFsLseek_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsStat_symbol                                0x%X\n", cellFsStat_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsUnlink_internal_symbol                     0x%X\n", cellFsUnlink_internal_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsUtilMount_symbol                           0x%X\n", cellFsUtilMount_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsUtilUmount_symbol                          0x%X\n", cellFsUtilUmount_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define pathdup_from_user_symbol                         0x%X\n", pathdup_from_user_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define open_path_symbol                                 0x%X\n", open_path_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define open_fs_object_symbol                            0x%X\n", open_fs_object_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define close_fs_object_symbol                           0x%X\n", close_fs_object_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_get_device_info_symbol                   0x%X\n", storage_get_device_info_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_open_symbol                              0x%X\n", storage_open_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_close_symbol                             0x%X\n", storage_close_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_read_symbol                              0x%X\n", storage_read_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_send_device_command_symbol               0x%X\n", storage_send_device_command_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_map_io_memory_symbol                     0x%X\n", storage_map_io_memory_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_unmap_io_memory_symbol                   0x%X\n", storage_unmap_io_memory_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_internal_get_device_object_symbol        0x%X\n", storage_internal_get_device_object_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define decrypt_func_symbol                              0x%X\n", decrypt_func_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define lv1_call_99_wrapper_symbol                       0x%X\n", lv1_call_99_wrapper_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define modules_verification_symbol                      0x%X\n", modules_verification_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_load_module_symbol                           0x%X\n", prx_load_module_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_start_module_symbol                          0x%X\n", prx_start_module_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_stop_module_symbol                           0x%X\n", prx_stop_module_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_unload_module_symbol                         0x%X\n", prx_unload_module_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_get_module_info_symbol                       0x%X\n", prx_get_module_info_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_get_module_list_symbol                       0x%X\n", prx_get_module_list_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define extend_kstack_symbol                             0x%X\n", extend_kstack_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define get_pseudo_random_number_symbol                  0x%X\n", get_pseudo_random_number_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define syscall_table_symbol                             0x%X\n", SYSCALL_TABLE - 0x8000000000000000ULL); fputs(temp, symbols);
		sprintf(temp, "\t#define syscall_call_offset                              0x%X\n", syscall_call_offset); fputs(temp, symbols);
		sprintf(temp, "\t#define read_bdvd0_symbol                                0x%X\n", read_bdvd0_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define read_bdvd1_symbol                                0x%X\n", read_bdvd1_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define read_bdvd2_symbol                                0x%X\n", read_bdvd2_symbol); fputs(temp, symbols);
		sprintf(temp, "\t#define device_event_port_send_call                      0x%X\n", device_event_port_send_call); fputs(temp, symbols);
		sprintf(temp, "\t#define process_map_caller_call                          0x%X\n", process_map_caller_call); fputs(temp, symbols);
		sprintf(temp, "\t#define fsloop_open_call                                 0x%X\n", fsloop_open_call); fputs(temp, symbols);
		sprintf(temp, "\t#define fsloop_close_call                                0x%X\n", fsloop_close_call); fputs(temp, symbols);
		sprintf(temp, "\t#define fsloop_read_call                                 0x%X\n", fsloop_read_call); fputs(temp, symbols);
		if(io_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define io_rtoc_entry_1                                 -0x%X\n", 0 - io_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define io_rtoc_entry_1                                  0x%X\n", io_rtoc_entry_1); fputs(temp, symbols);
		}
		if(io_sub_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define io_sub_rtoc_entry_1                             -0x%X\n", 0 - io_sub_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define io_sub_rtoc_entry_1                              0x%X\n", io_sub_rtoc_entry_1); fputs(temp, symbols);
		}
		if(decrypt_rtoc_entry_2 < 0) {
			sprintf(temp, "\t#define decrypt_rtoc_entry_2                            -0x%X\n", 0 - decrypt_rtoc_entry_2); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define decrypt_rtoc_entry_2                             0x%X\n", decrypt_rtoc_entry_2); fputs(temp, symbols);
		}
		if(storage_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define storage_rtoc_entry_1                            -0x%X\n", 0 - storage_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define storage_rtoc_entry_1                             0x%X\n", storage_rtoc_entry_1); fputs(temp, symbols);
		}
		if(device_event_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define device_event_rtoc_entry_1                       -0x%X\n", 0 - device_event_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define device_event_rtoc_entry_1                        0x%X\n", device_event_rtoc_entry_1); fputs(temp, symbols);
		}
		if(process_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define process_rtoc_entry_1                            -0x%X\n", 0 - process_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define process_rtoc_entry_1                             0x%X\n", process_rtoc_entry_1); fputs(temp, symbols);
		}
		sprintf(temp, "\t#define patch_func2                                      0x%X\n", patch_func2); fputs(temp, symbols);
				fputs("\t#define patch_func2_offset                               0x2C\n", symbols);
		sprintf(temp, "\t#define user_thread_prio_patch                           0x%X\n", user_thread_prio_patch); fputs(temp, symbols);
		sprintf(temp, "\t#define user_thread_prio_patch2                          0x%X\n", user_thread_prio_patch2); fputs(temp, symbols);
		sprintf(temp, "\t#define shutdown_patch_offset                            0x%X\n", shutdown_patch_offset); fputs(temp, symbols);
		sprintf(temp, "\t#define shutdown_copy_params_call                        0x%X\n", shutdown_copy_params_call); fputs(temp, symbols);
		
		fputs("\n", symbols);
		
		sprintf(temp2, "flash/%lld%c", FIRMWARE, D);
		if(exist(temp2)) {
			
			sprintf(temp, "\t/* hash */\n", FIRMWARE); fputs(temp, symbols);
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/explore_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EXPLORE_PLUGIN_HASH                         0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/explore_category_game.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EXPLORE_CATEGORY_GAME_HASH                  0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/game_ext_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define GAME_EXT_PLUGIN_HASH                        0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libfs.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define LIBFS_EXTERNAL_HASH                         0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/psp_emulator.self", FIRMWARE, D);
			sprintf(temp, "\t#define PSP_EMULATOR_HASH                           0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/PEmuCoreLib.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define PEMUCORELIB_HASH                            0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_api.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EMULATOR_API_HASH                           0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_drm.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EMULATOR_DRM_HASH                           0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_drm.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EMULATOR_DRM_DATA_HASH                      0x%016llX\n", hash(temp2, 1, 0));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libsysutil_savedata_psp.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols);

			fputs("\n\t/* lv1 */\n", symbols);
			sprintf(temp, "\t#define vsh_pos_in_ram                              0x%X\n", vsh_pos_in_ram); fputs(temp, symbols);
			
			u64 ps2tonet_patch=0;
			u8 ps2tonet_patch_FLAG[4] = {0x60, 0x63, 0x82, 0x02};
			
			u64 ps2tonet_size_patch=0;
			u8 ps2tonet_size_patch_FLAG[8] = {0x38, 0xA0, 0x04, 0xF0, 0x78, 0x64, 0x00, 0x20};
			
			u64 vmode_patch_offset=0;
			u8 vmode_patch_offset_FLAG1[8] = {0x80, 0x01, 0x00, 0x74, 0x2F, 0x80, 0x00, 0x00};
			u8 vmode_patch_offset_FLAG2[8] = {0x38, 0x61, 0x00, 0x70, 0x48, 0x00, 0x65, 0x1D};
			
			u64 psp_drm_patch1=0;
			u8 psp_drm_patch1_FLAG[0x10] = {0x2F, 0x83, 0x00, 0x00, 0x7C, 0x6B, 0x1B, 0x78, 0x41, 0x9E, 0x00, 0x0C, 0x3D, 0x60, 0x80, 0x02}; //-4
			
			u64 psp_drm_patch2=0;
			u8 psp_drm_patch2_FLAG[8] = {0x7F, 0xC4, 0xF3, 0x78, 0x38, 0xA0, 0x00, 0x98}; //+8
			
			u64 psp_drm_patch3=0;
			u8 psp_drm_patch3_FLAG[0x20] = {0x7D, 0x63, 0x07, 0xB4, 0xEB, 0xA1, 0x00, 0x78, 0xEB, 0xC1, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xE1, 0x00, 0x88, 0x38, 0x21, 0x00, 0x90, 0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFA, 0xC1};
			u8 psp_drm_patch3_FLAG1[0x20] = {0x7C, 0x63, 0x07, 0xB4, 0xEB, 0xC1, 0x00, 0x70, 0xEB, 0xE1, 0x00, 0x78, 0x7C, 0x08, 0x03, 0xA6, 0x38, 0x21, 0x00, 0x80, 0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFA, 0xC1, 0x7C, 0x08, 0x02, 0xA6};
			
			u64 psp_drm_patch4=0;
			u8 psp_drm_patch4_FLAG[8] = {0x60, 0x00, 0x95, 0x13, 0x79, 0x29, 0x00, 0x20};
			
			u64 psp_drm_patchA=0;
			u8 psp_drm_patchA_FLAG[8] = {0x60, 0x00, 0x95, 0x14, 0x7C, 0x03, 0x07, 0xB4};
			
			u64 psp_drm_patchB=0;
			u8 psp_drm_patchB_FLAG[8] = {0x63, 0xFF, 0x95, 0x14, 0x4B, 0xFF, 0xFF, 0x2C};
			
			u64 psp_drm_patchC=0;
			u8 psp_drm_patchC_FLAG[8] = {0x38, 0x00, 0x00, 0x00, 0x60, 0x63, 0x06, 0x01}; // +4
			
			u64 psp_drm_patchD=0;
			u8 psp_drm_patchD_FLAG[8] = {0x7F, 0xE3, 0xFB, 0x78, 0x60, 0x00, 0x95, 0x13}; // +8
			
			u64 psp_drm_patchE=0;
			u8 psp_drm_patchE_FLAG[8] = {0x60, 0x00, 0x95, 0x13, 0x40, 0x9E, 0x00, 0x1C}; // +8
			
			u64 psp_drm_patchF=0;
			u8 psp_drm_patchF_FLAG[0x20] = {0x2F, 0x83, 0x00, 0x00, 0x40, 0xFC, 0x00, 0x1C, 0x3F, 0xE0, 0x80, 0x02, 0x7F, 0xC3, 0xF3, 0x78, 0x38, 0x80, 0x00, 0x00, 0x38, 0xA0, 0x00, 0x98, 0x63, 0xFF, 0x95, 0x14, 0x48, 0x00, 0x00, 0x6C}; // -4
			
			u64 psp_extra_drm_patch=0;
			u8 psp_extra_drm_patch_FLAG[0x10] = {0xEB, 0x81, 0x01, 0xE0, 0xEB, 0xA1, 0x01, 0xE8, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xC1, 0x01, 0xF0};
			
			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/vsh/module/vsh.self temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {				
					if(!memcmp((char *) &mem[n], (char *) ps2tonet_patch_FLAG, 4))
					{
						ps2tonet_patch = n;
					}
					if(!memcmp((char *) &mem[n], (char *) ps2tonet_size_patch_FLAG, 8))
					{
						ps2tonet_size_patch = n;
					}
					if(!memcmp((char *) &mem[n     ], (char *) vmode_patch_offset_FLAG1, 8)) 
					if(!memcmp((char *) &mem[n+0x20], (char *) vmode_patch_offset_FLAG2, 8))
					{
						vmode_patch_offset = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patch1_FLAG, 0x10))
					{
						psp_drm_patch1 = n - 4;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patch2_FLAG, 8))
					{
						psp_drm_patch2 = n + 8;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patch3_FLAG, 0x20)
					|| !memcmp((char *) &mem[n], (char *) psp_drm_patch3_FLAG1, 0x20) )
					{
						psp_drm_patch3 = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patch4_FLAG, 8))
					{
						psp_drm_patch4 = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patchA_FLAG, 8))
					{
						psp_drm_patchA = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patchB_FLAG, 8))
					{
						psp_drm_patchB = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patchC_FLAG, 8))
					{
						psp_drm_patchC = n + 4;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patchD_FLAG, 8))
					{
						psp_drm_patchD = n + 8;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patchE_FLAG, 8))
					{
						psp_drm_patchE = n + 8;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patchF_FLAG, 0x20))
					{
						psp_drm_patchF = n - 4;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_extra_drm_patch_FLAG, 0x10))
					{
						psp_extra_drm_patch = n - 4;
					}
					
					if(ps2tonet_patch)
					if(ps2tonet_size_patch)
					if(vmode_patch_offset)
					if(psp_drm_patch1)
					if(psp_drm_patch2)
					if(psp_drm_patch3)
					if(psp_drm_patch4)
					if(psp_drm_patchA)
					if(psp_drm_patchB)
					if(psp_drm_patchC)
					if(psp_drm_patchD)
					if(psp_drm_patchE)
					if(psp_drm_patchF)
					if(psp_extra_drm_patch)
					break;
				}
				
				free(mem);
			}
			
			fputs("\n\t/* vsh */\n", symbols);
			sprintf(temp, "\t#define ps2tonet_patch                              0x%X\n", ps2tonet_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define ps2tonet_size_patch                         0x%X\n", ps2tonet_size_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define vmode_patch_offset                          0x%X\n", vmode_patch_offset); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch1                              0x%X\n", psp_drm_patch1); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch2                              0x%X\n", psp_drm_patch2); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch3                              0x%X\n", psp_drm_patch3); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch4                              0x%X\n", psp_drm_patch4); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchA                              0x%X\n", psp_drm_patchA); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchB                              0x%X\n", psp_drm_patchB); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchC                              0x%X\n", psp_drm_patchC); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchD                              0x%X\n", psp_drm_patchD); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchE                              0x%X\n", psp_drm_patchE); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchF                              0x%X\n", psp_drm_patchF); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_extra_drm_patch                         0x%X\n", psp_extra_drm_patch); fputs(temp, symbols);
			
			
			fputs("\n\t/* explore_plugin */\n", symbols);
			u64 ps2_nonbw_offset=0;
			u8 ps2_nonbw_offset_FLAG[0x10] = {0x7D, 0x2B, 0x02, 0x14, 0x80, 0x89, 0x00, 0x30, 0x48, 0x00, 0x00, 0x08, 0x38, 0xA0, 0x00, 0x00}; //+4
			
			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/vsh/module/explore_plugin.sprx temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {
					
					if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset_FLAG, 0xC)) 
					{
						ps2_nonbw_offset = n + 4;
					}
					
					if(ps2_nonbw_offset)
					break;
				}
				
				free(mem);
			}
			sprintf(temp, "\t#define ps2_nonbw_offset                            0x%X\n", ps2_nonbw_offset); fputs(temp, symbols);
			
			fputs("\n\t/* explore_category_game */\n", symbols);
			u64 ps2_nonbw_offset2=0;
			u8 ps2_nonbw_offset2_FLAG[0x10] = {0x7D, 0x2B, 0x02, 0x14, 0x80, 0x89, 0x00, 0x30, 0x48, 0x00, 0x00, 0x08, 0x38, 0xA0, 0x00, 0x00}; // +4
			
			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/vsh/module/explore_category_game.sprx temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {
					
					if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset2_FLAG, 0x10)) 
					{
						ps2_nonbw_offset2 = n + 4;
					}
					
					if(ps2_nonbw_offset2)
					break;
				}
				
				free(mem);
			}
			sprintf(temp, "\t#define ps2_nonbw_offset2                           0x%X\n", ps2_nonbw_offset2); fputs(temp, symbols);
			
			fputs("\n\t/* game_ext_plugin */\n", symbols);
			u64 ps2_nonbw_offset3=0;
			u8 ps2_nonbw_offset3_FLAG[0x10] = {0x38, 0x61, 0x00, 0x70, 0x2F, 0x9F, 0x00, 0x00, 0x41, 0x9C, 0x00, 0x58, 0x38, 0x00, 0x00, 0x70};
			
			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/vsh/module/game_ext_plugin.sprx temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {
					
					if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset3_FLAG, 0x10)) 
					{
						ps2_nonbw_offset3 = n;
					}
					
					if(ps2_nonbw_offset3)
					break;
				}
				
				free(mem);
			}
			sprintf(temp, "\t#define ps2_nonbw_offset3                           0x%X\n", ps2_nonbw_offset3); fputs(temp, symbols);
			
			fputs("\n\t/* psp_emulator */\n", symbols);
			u64 psp_set_psp_mode_offset=0;
			u8 psp_set_psp_mode_offset_FLAG[0x10] = {0x38, 0x80, 0x00, 0x01, 0x38, 0x60, 0x00, 0x05, 0x78, 0x84, 0x07, 0xC6, 0x64, 0x84, 0x00, 0x01};
			
			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/pspemu/psp_emulator.self temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {
					
					if(!memcmp((char *) &mem[n], (char *) psp_set_psp_mode_offset_FLAG, 0x10)) 
					{
						psp_set_psp_mode_offset = n;
					}
					
					if(psp_set_psp_mode_offset)
					break;
				}
				
				free(mem);
			}
			sprintf(temp, "\t#define psp_set_psp_mode_offset                     0x%X\n", psp_set_psp_mode_offset); fputs(temp, symbols);
			
			fputs("\n\t/* emulator_api */\n", symbols);
			
			u64 psp_read=0;
			u8 psp_read_FLAG[0x10] = {0x4B, 0xFF, 0xF1, 0x80, 0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x70}; // +8
			
			u64 psp_read_header=0;
			u64 psp_drm_patch9=0;	
			u64 psp_drm_patch11=0;
			u64 psp_drm_patch12=0;
			u8 psp_group_FLAG[0x30] = {0x7D, 0x63, 0xE2, 0x14, 0x7F, 0x04, 0xC3, 0x78, 0x79, 0x6B, 0x00, 0x20, 0x88, 0x09, 0x00, 0x00, 
										0x7F, 0xC3, 0xF3, 0x78, 0x89, 0x49, 0x00, 0x01, 0x89, 0x09, 0x00, 0x02, 0x88, 0xE9, 0x00, 0x03, 
										0x98, 0x0B, 0x00, 0x00, 0x99, 0x4B, 0x00, 0x01, 0x99, 0x0B, 0x00, 0x02, 0x98, 0xEB, 0x00, 0x03
										}; // h +30 ; 9 -0x20 ; 11 -0x1C ; 12 -0xC
			
			u64 psp_drm_patch5=0;
			u8 psp_drm_patch5_FLAG[0x10] = {0x7D, 0x63, 0xE2, 0x14, 0x38, 0x01, 0x00, 0xA0, 0x79, 0x6B, 0x00, 0x20, 0x89, 0x49, 0x00, 0x00}; // -4
			
			u64 psp_drm_patch6=0;
			u64 psp_drm_patch7=0;
			u64 psp_drm_patch8=0;
			u8 psp_group2_FLAG[0x10] = {0x99, 0x4B, 0x00, 0x00, 0x98, 0x0B, 0x00, 0x01, 0x99, 0x0B, 0x00, 0x02, 0x98, 0xEB, 0x00, 0x03}; // 7 :+0x18 ; 8 : +0x1C
			
			u64 psp_product_id_patch1=0;
			u8 psp_product_id_patch1_FLAG[0x10] = {0x2E, 0x03, 0x00, 0x00, 0x7C, 0x7F, 0x1B, 0x78, 0x40, 0x92, 0xFE, 0x4C, 0x3A, 0x41, 0x00, 0x90};
			
			u64 psp_product_id_patch3=0;
			u8 psp_product_id_patch3_FLAG[] = {0x7C, 0x7F, 0x1B, 0x78, 0x40, 0x92, 0x00, 0x18, 0xE8, 0x01, 0x00, 0x90, 0x2F, 0xA0, 0x00, 0x28};
			
			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/pspemu/release/emulator_api.sprx temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {
					
					if(!memcmp((char *) &mem[n], (char *) psp_read_FLAG, 0x10)) 
					{
						psp_read = n + 8;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_drm_patch5_FLAG, 0x10)) 
					{
						psp_drm_patch5 = n - 4;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_group2_FLAG, 0x10)) 
					{
						psp_drm_patch6 = n;
						psp_drm_patch7 = n + 0x18;
						psp_drm_patch8 = n + 0x1C;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_group_FLAG, 0x30)) 
					{
						psp_read_header = n + 0x30;
						psp_drm_patch9 = n - 0x20;
						psp_drm_patch11 = n - 0x1C;
						psp_drm_patch12 = n - 0xC;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_product_id_patch1_FLAG, 0x10)) 
					{
						psp_product_id_patch1 = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_product_id_patch3_FLAG, 0x10)) 
					{
						psp_product_id_patch3 = n;
					}
					
					if(psp_read)
					if(psp_read_header)
					if(psp_drm_patch5)
					if(psp_drm_patch6)
					if(psp_drm_patch7)
					if(psp_drm_patch8)
					if(psp_drm_patch9)
					if(psp_drm_patch11)
					if(psp_drm_patch12)
					if(psp_product_id_patch1)
					if(psp_product_id_patch3)
					break;
				}
				
				free(mem);
			}
			sprintf(temp, "\t#define psp_read                                    0x%X\n", psp_read); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_read_header                             0x%X\n", psp_read_header); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch5                              0x%X\n", psp_drm_patch5); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch6                              0x%X\n", psp_drm_patch6); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch7                              0x%X\n", psp_drm_patch7); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch8                              0x%X\n", psp_drm_patch8); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch9                              0x%X\n", psp_drm_patch9); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch11                             0x%X\n", psp_drm_patch11); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch12                             0x%X\n", psp_drm_patch12); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_product_id_patch1                       0x%X\n", psp_product_id_patch1); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_product_id_patch3                       0x%X\n", psp_product_id_patch3); fputs(temp, symbols);
			
			fputs("\n\t/* pemucorelib */\n", symbols);
			
			u64 psp_eboot_dec_patch=0;
			u8 psp_eboot_dec_patch_FLAG[0x10] = {0x38, 0xC0, 0x01, 0x11, 0x38, 0xE0, 0x00, 0x00, 0x39, 0x00, 0x00, 0x01, 0x39, 0x20, 0x00, 0x00};
			
			u64 psp_prx_patch=0;
			u8 psp_prx_patch_FLAG[0x10] = {0x88, 0x04, 0x00, 0x00, 0x38, 0xE4, 0x00, 0x12, 0x89, 0x24, 0x00, 0x01, 0x38, 0xC4, 0x00, 0x32};
			
			u64 psp_savedata_bind_patch1=0;
			u8 psp_savedata_bind_patch1_FLAG[0x10] = {0xEA, 0x61, 0x09, 0x18, 0x38, 0x00, 0x08, 0xD0, 0xEA, 0x81, 0x09, 0x20, 0x7C, 0x69, 0x18, 0x50};
			
			u64 psp_savedata_bind_patch2=0;
			u8 psp_savedata_bind_patch2_FLAG[0x10] = {0xEB, 0xE1, 0x09, 0x78, 0x38, 0x21, 0x09, 0x80, 0x4E, 0x80, 0x00, 0x20, 0x7F, 0xA3, 0xEB, 0x78}; // +8
			
			u64 psp_savedata_bind_patch3=0;
			u8 psp_savedata_bind_patch3_FLAG[0x20] = {0x60, 0x00, 0x00, 0x00, 0x4B, 0xFF, 0xFF, 0x75, 0xE8, 0x01, 0x00, 0x80, 0x38, 0x60, 0x00, 0x00, 0x7C, 0x08, 0x03, 0xA6, 0x38, 0x21, 0x00, 0x70, 0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFF, 0x91}; //+0x18
			
			u64 psp_extra_savedata_patch=0;
			u8 psp_extra_savedata_patch_FLAG[0x10] = {0x78, 0x7F, 0x00, 0x20, 0x4B, 0xFF, 0xFF, 0x64, 0x83, 0xFE, 0x04, 0x34, 0x4B, 0xFF, 0xFF, 0x5C}; // +8
			
			u64 psp_prometheus_patch=0;
			u8 psp_prometheus_patch_FLAG[0x20] = {0x64, 0x69, 0x73, 0x63, 0x30, 0x3A, 0x2F, 0x50, 0x53, 0x50, 0x5F, 0x47, 0x41, 0x4D, 0x45, 0x2F, 0x53, 0x59, 0x53, 0x44, 0x49, 0x52, 0x2F, 0x45, 0x42, 0x4F, 0x4F, 0x54, 0x2E, 0x42, 0x49, 0x4E};
			
			u64 prx_patch_call_lr=0;
			u8 prx_patch_call_lr_FLAG[0x10] = {0xA3, 0x5B, 0x00, 0x2C, 0x93, 0x5E, 0x00, 0xF8, 0x80, 0x1B, 0x00, 0x1C, 0x2F, 0x80, 0x00, 0x00};

			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/pspemu/release/PEmuCoreLib.sprx temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {
					
					if(!memcmp((char *) &mem[n], (char *) psp_eboot_dec_patch_FLAG, 0x10))
					{
						psp_eboot_dec_patch = n - 0x10000;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_prx_patch_FLAG, 0x10))
					{
						psp_prx_patch = n - 0x10000;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_savedata_bind_patch1_FLAG, 0x10))
					{
						psp_savedata_bind_patch1 = n - 0x10000;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_savedata_bind_patch2_FLAG, 0x10))
					{
						psp_savedata_bind_patch2 = n + 8 -  0x10000;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_savedata_bind_patch3_FLAG, 0x20))
					{
						psp_savedata_bind_patch3 = n + 0x18 - 0x10000;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_extra_savedata_patch_FLAG, 0x10))
					{
						psp_extra_savedata_patch = n + 8 - 0x10000;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_prometheus_patch_FLAG, 0x20))
					{
						psp_prometheus_patch = n - 0x10000;
					}
					if(!memcmp((char *) &mem[n], (char *) prx_patch_call_lr_FLAG, 0x10))
					{
						prx_patch_call_lr = n - 0x10000;
					}
					
					if(psp_eboot_dec_patch)
					if(psp_prx_patch)
					if(psp_savedata_bind_patch1)
					if(psp_savedata_bind_patch2)
					if(psp_savedata_bind_patch3)
					if(psp_extra_savedata_patch)
					if(psp_prometheus_patch)
					if(prx_patch_call_lr)
					break;
				}
				
				free(mem);
			}
			sprintf(temp, "\t#define psp_eboot_dec_patch                         0x%X\n", psp_eboot_dec_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_prx_patch                               0x%X\n", psp_prx_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_bind_patch1                    0x%X\n", psp_savedata_bind_patch1); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_bind_patch2                    0x%X\n", psp_savedata_bind_patch2); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_bind_patch3                    0x%X\n", psp_savedata_bind_patch3); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_extra_savedata_patch                    0x%X\n", psp_extra_savedata_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_prometheus_patch                        0x%X\n", psp_prometheus_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define prx_patch_call_lr                           0x%X\n", prx_patch_call_lr); fputs(temp, symbols);
			
			fputs("\n\t/* emulator_drm */\n", symbols);
			u64 psp_drm_tag_overwrite=0;
			u8 psp_drm_tag_overwrite_FLAG[0x10] = {0x39, 0x00, 0x00, 0x00, 0x7D, 0x3E, 0x52, 0x14, 0x39, 0x4A, 0x00, 0x01, 0x7D, 0x29, 0x5A, 0x14};
			
			u64 psp_drm_key_overwrite=0;
			u8 psp_drm_key_overwrite_FLAG[4] = {0x00, 0x00, 0xBC, 0xC0};
			
			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/pspemu/release/emulator_drm.sprx temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {
					if(!memcmp((char *) &mem[n], (char *) psp_drm_tag_overwrite_FLAG, 0x10))
					{
						psp_drm_tag_overwrite = n;
					}
					if(psp_drm_key_overwrite==0)
					if(!memcmp((char *) &mem[n], (char *) psp_drm_key_overwrite_FLAG, 4))
					{
						u32 tmp=0;
						memcpy(&tmp, &mem[n-4], 4);
						tmp = SWAP32(tmp);
						if(tmp!=0) psp_drm_key_overwrite = tmp;
					}
					if(psp_drm_tag_overwrite)
					if(psp_drm_key_overwrite)
					break;
				}
				
				free(mem);
			}
			sprintf(temp, "\t#define psp_drm_tag_overwrite                       0x%X\n", psp_drm_tag_overwrite); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_key_overwrite                       (0x%X - 0xBE80)\n", psp_drm_key_overwrite); fputs(temp, symbols);

			fputs("\n\t/* libsysutil_savedata_psp */\n", symbols);
			
			u64 psp_savedata_patch1=0;
			u8 psp_savedata_patch1_FLAG[] = {0xEA, 0xC1, 0x08, 0xE0, 0xEA, 0xE1, 0x08, 0xE8, 0xEB, 0x01, 0x08, 0xF0, 0xEB, 0x21, 0x08, 0xF8};
			
			u64 psp_savedata_patch2=0;
			u8 psp_savedata_patch2_FLAG[] = {0xE9, 0xC1, 0x08, 0xA0, 0xE9, 0xE1, 0x08, 0xA8, 0x7C, 0x08, 0x03, 0xA6, 0xEA, 0x01, 0x08, 0xB0};
			
			u64 psp_savedata_patch3=0;
			u8 psp_savedata_patch3_FLAG[] = {0xE8, 0xA1, 0x08, 0x80, 0x7E, 0x83, 0xA3, 0x78, 0x7F, 0x04, 0xC3, 0x78, 0x7F, 0xC6, 0xF3, 0x78};
			
			u64 psp_savedata_patch4=0;
			u8 psp_savedata_patch4_FLAG[] = {0x78, 0x1C, 0x00, 0x20, 0x80, 0x01, 0x09, 0xA4, 0x79, 0x3D, 0x00, 0x20, 0x2F, 0x80, 0x00, 0x00};
			
			u64 psp_savedata_patch5=0;
			u8 psp_savedata_patch5_FLAG[] = {0x38, 0xC0, 0x00, 0x14, 0x90, 0x1C, 0x00, 0x10, 0xF8, 0x1D, 0x00, 0x00, 0x92, 0x21, 0x00, 0xB8};
			
			u64 psp_savedata_patch6=0;
			u8 psp_savedata_patch6_FLAG[] = {0xEA, 0x21, 0x08, 0xB8, 0xEA, 0x41, 0x08, 0xC0, 0xEA, 0x61, 0x08, 0xC8, 0xEA, 0x81, 0x08, 0xD0};
			
			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/sys/external/libsysutil_savedata_psp.sprx temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {
					if(!memcmp((char *) &mem[n], (char *) psp_savedata_patch1_FLAG, 0x10))
					{
						psp_savedata_patch1 = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_savedata_patch2_FLAG, 0x10))
					{
						psp_savedata_patch2 = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_savedata_patch3_FLAG, 0x10))
					{
						psp_savedata_patch3 = n - 8;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_savedata_patch4_FLAG, 0x10))
					{
						psp_savedata_patch4 = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_savedata_patch5_FLAG, 0x10))
					{
						psp_savedata_patch5 = n;
					}
					if(!memcmp((char *) &mem[n], (char *) psp_savedata_patch6_FLAG, 0x10))
					{
						psp_savedata_patch6 = n;
					}
					if(psp_savedata_patch1)
					if(psp_savedata_patch2)
					if(psp_savedata_patch3)
					if(psp_savedata_patch4)
					if(psp_savedata_patch5)
					if(psp_savedata_patch6)
					break;
				}
				
				free(mem);
			}
			sprintf(temp, "\t#define psp_savedata_patch1                         0x%X\n", psp_savedata_patch1); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch2                         0x%X\n", psp_savedata_patch2); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch3                         0x%X\n", psp_savedata_patch3); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch4                         0x%X\n", psp_savedata_patch4); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch5                         0x%X\n", psp_savedata_patch5); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch6                         0x%X\n", psp_savedata_patch6); fputs(temp, symbols);

			fputs("\n\t/* libfs */\n", symbols);
			u64 aio_copy_root_offset=0;
			u8 aio_copy_root_offset_FLAG[] = {0x78, 0x84, 0x04, 0x20, 0x4B, 0xFF, 0xB1, 0x74, 0x38, 0x80, 0xFF, 0xFF, 0x38, 0x60, 0x00, 0x01};
			
			sprintf(temp2, "scetool -d flash/%lld%c/dev_flash/sys/external/libfs.sprx temp_dec", FIRMWARE, D);
			system(temp2);
			
			f = fopen("temp_dec", "rb");
			if(f!=NULL) {
				fseek (f , 0 , SEEK_END);
				size = ftell (f);
				fseek(f, 0, SEEK_SET);
				
				char *mem = (char*) malloc (sizeof(char)*size);
				if (mem == NULL) {
					printf("Error : cannot malloc vsh");
					free(mem);
					fclose(f);
					return 0;
				}

				fread(mem,1,size, f);
				
				fclose(f);
				
				system("del temp_dec");
				
				for(n=0; n<size ; n++) {
					if(!memcmp((char *) &mem[n], (char *) aio_copy_root_offset_FLAG, 0x10))
					{
						aio_copy_root_offset = n;
					}
					if(aio_copy_root_offset)
					break;
				}
				
				free(mem);
			}
			sprintf(temp, "\t#define aio_copy_root_offset                        0x%X\n", aio_copy_root_offset); fputs(temp, symbols);
			
			char temp3[64];
			sprintf(temp3, "flash/%lld%c/dev_flash_rebug", FIRMWARE, D);
			if(exist(temp3)) {
				fputs("\n\t/* rebug */\n", symbols);
			} else {
				if(D=='C') {
					sprintf(temp3, "flash/%lldD/dev_flash", FIRMWARE);
					if(exist(temp3)) fputs("\n\t/* DEX */\n", symbols);
				} else
				if(D=='D') {
					sprintf(temp3, "flash/%lldC/dev_flash", FIRMWARE);
					if(exist(temp3)) fputs("\n\t/* CEX */\n", symbols);
				}
			}
			
			if(exist(temp3)) {
				if(D=='C') {
					sprintf(temp2, "%s/vsh/module/explore_plugin.sprx", temp3);
					sprintf(temp, "\t#define EXPLORE_PLUGIN_REBUG_HASH                   0x%016llX\n", hash(temp2, 0, 0));
					fputs(temp, symbols);
					
					sprintf(temp2, "%s/vsh/module/explore_category_game.sprx", temp3);
					sprintf(temp, "\t#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x%016llX\n", hash(temp2, 0, 0));
					fputs(temp, symbols);
					
					sprintf(temp2, "%s/vsh/module/game_ext_plugin.sprx", temp3);
					sprintf(temp, "\t#define GAME_EXT_PLUGIN_REBUG_HASH                  0x%016llX\n", hash(temp2, 0, 0));
					fputs(temp, symbols);
				}
				
				ps2tonet_patch=0;
				ps2tonet_size_patch=0;
				vmode_patch_offset=0;
				psp_drm_patch1=0;
				psp_drm_patch2=0;
				psp_drm_patch3=0;
				psp_drm_patch4=0;
				psp_drm_patchA=0;
				psp_drm_patchB=0;
				psp_drm_patchC=0;
				psp_drm_patchD=0;
				psp_drm_patchE=0;
				psp_drm_patchF=0;
				psp_extra_drm_patch=0;
				
				sprintf(temp2, "scetool -d %s/vsh/module/vsh.self temp_dec", temp3);
				system(temp2);
				
				f = fopen("temp_dec", "rb");
				if(f!=NULL) {
					fseek (f , 0 , SEEK_END);
					size = ftell (f);
					fseek(f, 0, SEEK_SET);
					
					char *mem = (char*) malloc (sizeof(char)*size);
					if (mem == NULL) {
						printf("Error : cannot malloc vsh");
						free(mem);
						fclose(f);
						return 0;
					}

					fread(mem,1,size, f);
					
					fclose(f);
					
					system("del temp_dec");
					
					for(n=0; n<size ; n++) {				
						if(!memcmp((char *) &mem[n], (char *) ps2tonet_patch_FLAG, 4))
						{
							ps2tonet_patch = n;
						}
						if(!memcmp((char *) &mem[n], (char *) ps2tonet_size_patch_FLAG, 8))
						{
							ps2tonet_size_patch = n;
						}
						if(!memcmp((char *) &mem[n     ], (char *) vmode_patch_offset_FLAG1, 8)) 
						if(!memcmp((char *) &mem[n+0x20], (char *) vmode_patch_offset_FLAG2, 8))
						{
							vmode_patch_offset = n;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patch1_FLAG, 0x10))
						{
							psp_drm_patch1 = n - 4;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patch2_FLAG, 8))
						{
							psp_drm_patch2 = n + 8;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patch3_FLAG, 0x20)
						|| !memcmp((char *) &mem[n], (char *) psp_drm_patch3_FLAG1, 0x20) )
						{
							psp_drm_patch3 = n;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patch4_FLAG, 8))
						{
							psp_drm_patch4 = n;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patchA_FLAG, 8))
						{
							psp_drm_patchA = n;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patchB_FLAG, 8))
						{
							psp_drm_patchB = n;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patchC_FLAG, 8))
						{
							psp_drm_patchC = n + 4;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patchD_FLAG, 8))
						{
							psp_drm_patchD = n + 8;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patchE_FLAG, 8))
						{
							psp_drm_patchE = n + 8;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_drm_patchF_FLAG, 0x20))
						{
							psp_drm_patchF = n - 4;
						}
						if(!memcmp((char *) &mem[n], (char *) psp_extra_drm_patch_FLAG, 0x10))
						{
							psp_extra_drm_patch = n - 4;
						}
						
						if(ps2tonet_patch)
						if(ps2tonet_size_patch)
						if(vmode_patch_offset)
						if(psp_drm_patch1)
						if(psp_drm_patch2)
						if(psp_drm_patch3)
						if(psp_drm_patch4)
						if(psp_drm_patchA)
						if(psp_drm_patchB)
						if(psp_drm_patchC)
						if(psp_drm_patchD)
						if(psp_drm_patchE)
						if(psp_drm_patchF)
						if(psp_extra_drm_patch)
						break;
					}
					
					free(mem);
				}
				
				ps2_nonbw_offset=0;
				sprintf(temp2, "scetool -d %s/vsh/module/explore_plugin.sprx temp_dec", temp3);
				system(temp2);
				
				f = fopen("temp_dec", "rb");
				if(f!=NULL) {
					fseek (f , 0 , SEEK_END);
					size = ftell (f);
					fseek(f, 0, SEEK_SET);
					
					char *mem = (char*) malloc (sizeof(char)*size);
					if (mem == NULL) {
						printf("Error : cannot malloc vsh");
						free(mem);
						fclose(f);
						return 0;
					}

					fread(mem,1,size, f);
					
					fclose(f);
					
					system("del temp_dec");
					
					for(n=0; n<size ; n++) {
						
						if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset_FLAG, 0xC)) 
						{
							ps2_nonbw_offset = n + 4;
						}
						
						if(ps2_nonbw_offset)
						break;
					}
					
					free(mem);
				}

				ps2_nonbw_offset2=0;
				
				sprintf(temp2, "scetool -d %s/vsh/module/explore_category_game.sprx temp_dec", temp3);
				system(temp2);
				
				f = fopen("temp_dec", "rb");
				if(f!=NULL) {
					fseek (f , 0 , SEEK_END);
					size = ftell (f);
					fseek(f, 0, SEEK_SET);
					
					char *mem = (char*) malloc (sizeof(char)*size);
					if (mem == NULL) {
						printf("Error : cannot malloc vsh");
						free(mem);
						fclose(f);
						return 0;
					}

					fread(mem,1,size, f);
					
					fclose(f);
					
					system("del temp_dec");
					
					for(n=0; n<size ; n++) {
						
						if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset2_FLAG, 0x10)) 
						{
							ps2_nonbw_offset2 = n + 4;
						}
						
						if(ps2_nonbw_offset2)
						break;
					}
					
					free(mem);
				}
				
				ps2_nonbw_offset3=0;
				
				sprintf(temp2, "scetool -d %s/vsh/module/game_ext_plugin.sprx temp_dec", temp3);
				system(temp2);
				
				f = fopen("temp_dec", "rb");
				if(f!=NULL) {
					fseek (f , 0 , SEEK_END);
					size = ftell (f);
					fseek(f, 0, SEEK_SET);
					
					char *mem = (char*) malloc (sizeof(char)*size);
					if (mem == NULL) {
						printf("Error : cannot malloc vsh");
						free(mem);
						fclose(f);
						return 0;
					}

					fread(mem,1,size, f);
					
					fclose(f);
					
					system("del temp_dec");
					
					for(n=0; n<size ; n++) {
						
						if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset3_FLAG, 0x10)) 
						{
							ps2_nonbw_offset3 = n;
						}
						
						if(ps2_nonbw_offset3)
						break;
					}
					
					free(mem);
				}
				
				if(D=='C') {
					sprintf(temp, "\t#define dex_ps2_nonbw_offset                        0x%X\n", ps2_nonbw_offset); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_ps2_nonbw_offset2                       0x%X\n", ps2_nonbw_offset2); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_ps2_nonbw_offset3                       0x%X\n", ps2_nonbw_offset3); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_ps2tonet_patch                          0x%X\n", ps2tonet_patch); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_ps2tonet_size_patch                     0x%X\n", ps2tonet_size_patch); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_vmode_patch_offset                      0x%X\n", vmode_patch_offset); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patch1                          0x%X\n", psp_drm_patch1); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patch2                          0x%X\n", psp_drm_patch2); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patch3                          0x%X\n", psp_drm_patch3); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patch4                          0x%X\n", psp_drm_patch4); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchA                          0x%X\n", psp_drm_patchA); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchB                          0x%X\n", psp_drm_patchB); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchC                          0x%X\n", psp_drm_patchC); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchD                          0x%X\n", psp_drm_patchD); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchE                          0x%X\n", psp_drm_patchE); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchF                          0x%X\n", psp_drm_patchF); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_extra_drm_patch                     0x%X\n", psp_extra_drm_patch); fputs(temp, symbols);
				} else
				if(D=='D') {
					//sprintf(temp, "\t#define cex_ps2_nonbw_offset                        0x%X\n", ps2_nonbw_offset); fputs(temp, symbols);
					//sprintf(temp, "\t#define cex_ps2_nonbw_offset2                       0x%X\n", ps2_nonbw_offset2); fputs(temp, symbols);
					//sprintf(temp, "\t#define cex_ps2_nonbw_offset3                       0x%X\n", ps2_nonbw_offset3); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_ps2tonet_patch                          0x%X\n", ps2tonet_patch); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_ps2tonet_size_patch                     0x%X\n", ps2tonet_size_patch); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_vmode_patch_offset                      0x%X\n", vmode_patch_offset); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patch1                          0x%X\n", psp_drm_patch1); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patch2                          0x%X\n", psp_drm_patch2); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patch3                          0x%X\n", psp_drm_patch3); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patch4                          0x%X\n", psp_drm_patch4); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchA                          0x%X\n", psp_drm_patchA); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchB                          0x%X\n", psp_drm_patchB); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchC                          0x%X\n", psp_drm_patchC); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchD                          0x%X\n", psp_drm_patchD); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchE                          0x%X\n", psp_drm_patchE); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchF                          0x%X\n", psp_drm_patchF); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_extra_drm_patch                     0x%X\n", psp_extra_drm_patch); fputs(temp, symbols);
				}
			}
		}
		
		fputs("#endif\n\n", symbols);
		
		free(memLV2);
		
	}
	
	fputs("\n#endif /* __FIRMWARE_SYMBOLS_H_S__ */\n", symbols);
	
	fputs("\n#endif /* __COMMON_H__ */\n", common);	
	fclose(common);
	fclose(SKY);
	fclose(symbols);
	closedir(d);
	
	printf("Done !\n");
	
	return 0;
}