#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <dirent.h>

#define SWAP16(x) ((((u16)(x))>>8) | ((x) << 8))
#define SWAP32(x) ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | (((x) >> 24) & 0xff))

#define warning(x) "## Warning: "x"\n"
#define error(x) "## Error: "x"\n"

char *PWD;

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

void Extract(char *self_path)
{
	char temp[512];
	sprintf(temp, "scetool -d %s/%s %s/temp_dec", PWD, self_path, PWD);
	system(temp);
}

char *LoadFile(char *path, int *size)
{
	struct stat s;
	if(stat(path, &s) != 0) return NULL;  
	if(S_ISDIR(s.st_mode)) return NULL;
	int file_size = s.st_size;
	FILE *f = fopen(path, "rb");
	if(f==NULL) return NULL;
	char *mem = malloc(file_size);
	if(mem==NULL) return NULL;
	fread(mem, file_size, 1, f);
	fclose(f);
	*size = file_size;
	return mem;
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
	
	Extract(self_path);
	
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
	
	uint64_t size;
	uint64_t hash = 0;
	uint8_t i=0;
	
	while(i != section) 
	{
		section_info++;
		elf_phdr++;
		i++;
	}
	
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
		} else 
		if(mode==3) {
			for (int j = 0; j < 0x8; j++)
			{
				hash ^= SWAP32(elf_buf[j+0xb0]);
			}
			size=(size&0xfff000);
			
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

uint8_t compare(u16 ignore, char *mem, char *flag, u32 size)
{
	int i;
	
	for(i = 0; i < size; i++) {
		if(flag[i] != mem[i]) {
			if(ignore <= 0xFF) {
				if( (u8) flag[i] != ignore ) {
					return 0;
				}
			} else {
				return 0;
			}	
		}
	}
	return 1;
}

int PS2_CRC()
{
	char temp[255];
	char str[255];
	
	u32 memsize=0x1000;
	
	DIR *d;
	struct dirent* ent = NULL;
	
	FILE *ps2crc = fopen("ps2crc.h", "w");
	if(ps2crc==NULL) return 0;
	
	fputs("#ifndef __PS2CRC_H__\n", ps2crc);
	fputs("#define __PS2CRC_H__\n\n", ps2crc);
	
	sprintf(temp, "/* CRC32 of the 0x%X first bytes */\n\n", memsize); fputs(temp, ps2crc); 
	
	d = opendir("flash");
	if(d== NULL) {
		printf("Directory flash not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		if(exist(temp)) continue;
		//sprintf(temp, "../payloads/PS2_EMU/BIN/ps2hwemu_stage2_%s.bin", ent->d_name);
		//if(exist(temp)==0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/ps2emu/ps2_emu.self", ent->d_name);
		
		FILE *self = fopen(temp, "rb");
		u8 *mem = (u8*) malloc(memsize);
		fread(mem, memsize, 1, self);
		fclose(self);
		
		u32 crc = crc32(0L, Z_NULL, 0);
		crc = crc32(crc, (const unsigned char*) mem, memsize);
		sprintf(str, "#define CRC32HWEMU_%s        0x%08lX\n", ent->d_name, crc); fputs(str, ps2crc);
		free(mem);mem=NULL;
	}
	closedir(d);
	
	fputs("\n", ps2crc);
	
	d = opendir("flash");
	if(d== NULL) {
		printf("Directory flash not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		if(exist(temp)) continue;
		//sprintf(temp, "../payloads/PS2_EMU/BIN/ps2gxemu_stage2_%s.bin", ent->d_name);
		//if(exist(temp)==0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/ps2emu/ps2_gxemu.self", ent->d_name);
		
		FILE *self = fopen(temp, "rb");
		u8 *mem = (u8*) malloc(memsize);
		fread(mem, memsize, 1, self);
		fclose(self);
		
		u32 crc = crc32(0L, Z_NULL, 0);
		crc = crc32(crc, (const unsigned char*) mem, memsize);
		sprintf(str, "#define CRC32GXEMU_%s        0x%08lX\n", ent->d_name, crc); fputs(str, ps2crc);
		free(mem);mem=NULL;
	}
	closedir(d);
	
	fputs("\n", ps2crc);
	
	d = opendir("flash");
	if(d== NULL) {
		printf("Directory flash not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		if(exist(temp)) continue;
		
		sprintf(temp, "flash/%s/dev_flash/ps2emu/ps2_netemu.self", ent->d_name);
		
		FILE *self = fopen(temp, "rb");
		u8 *mem = (u8*) malloc(memsize);
		fread(mem, memsize, 1, self);
		fclose(self);
		
		u32 crc = crc32(0L, Z_NULL, 0);
		crc = crc32(crc, (const unsigned char*) mem, memsize);
		sprintf(str, "#define CRC32NETEMU_%s        0x%08lX\n", ent->d_name, crc); fputs(str, ps2crc);
		free(mem);mem=NULL;
	}
	closedir(d);
	
	fputs("\n#endif /* __PS2CRC_H__ */\n", ps2crc);
	
	fclose(ps2crc);
	
	return 0;
}

int PS2_SearchOffsets()
{	
	char temp[2048];
	char str[2048];
	FILE *elf;
	FILE *sym;
	FILE *fw;
	FILE *ps2vers;
	FILE *ps2data;
	
	DIR *d;
	struct dirent* ent = NULL;
	
	ps2data = fopen("ps2data.h", "w");
	sym = fopen("ps2symbols.h", "wb");
	ps2vers = fopen("ps2vers.c", "w");
	fw = fopen("FIRMWARES", "a");
	
	fputs("\n\
#include \"ps2vers.h\"\n\
\n\
#define SUCCESS 1\n\
#define FAILED  0\n\
\n\
u8 get_hwemu(u32 crc, u8 **stage1, u32 *stage1_size, u8 **stage2, u32 *stage2_size)\n\
{\n", ps2vers);
	
	
	fputs("\nPS2_PAYLOADS := ", fw);
	
	fputs("#ifndef __PS2EMU_SYMBOLS_H_S__\n", sym);
	fputs("#define __PS2EMU_SYMBOLS_H_S__\n\n", sym);
	
	fputs("#ifndef __PS2DATA_H__\n", ps2data);
	fputs("#define __PS2DATA_H__\n\n", ps2data);
	fputs("#include <ppu-types.h>\n\n", ps2data);
	
// ps2_emu
	
	fputs("#ifdef PS2HWEMU\n\n", sym);
	
	fputs("\t#define DATA_TOC_OFFSET              -0x7358\n", sym);
	fputs("\t#define DATA_SUBTOC_OFFSET           0x20\n", sym);
	fputs("\t#define LPAR_SUBTOC_OFFSET           0x18\n", sym);
	fputs("\t#define FILESZ_TOC_OFFSET            -0x63E0\n", sym);
	
	fputs("\n", sym);
	
	d = opendir("flash");
	if(d== NULL) {
		printf("Directory ps2emu not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		if(exist(temp)) continue;
		
		sprintf(str, "%s ", ent->d_name); fputs(str, fw);
		
		sprintf(temp, "#include \"ps2hwemu_stage1_%s_bin.h\"\n", ent->d_name); fputs(temp, ps2data);
		sprintf(temp, "#include \"ps2hwemu_stage2_%s_bin.h\"\n", ent->d_name); fputs(temp, ps2data);
		sprintf(temp, "#include \"ps2gxemu_stage1_%s_bin.h\"\n", ent->d_name); fputs(temp, ps2data);
		sprintf(temp, "#include \"ps2gxemu_stage2_%s_bin.h\"\n", ent->d_name); fputs(temp, ps2data);
		sprintf(temp, "#include \"ps2netemu_stage2_%s_bin.h\"\n\n", ent->d_name); fputs(temp, ps2data);
	
		
		sprintf(str, "\n\
	if(crc == CRC32HWEMU_%s) {\n\
		*stage1_size = (uint32_t) ps2hwemu_stage1_%s_bin_size;\n\
		*stage1 = (uint8_t *) ps2hwemu_stage1_%s_bin;\n\
		*stage2_size = (uint32_t) ps2hwemu_stage2_%s_bin_size;\n\
		*stage2 = (uint8_t *) ps2hwemu_stage2_%s_bin;\n\
	} else ", ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name);
		fputs(str, ps2vers);
		
		sprintf(temp, "flash/%s/dev_flash/ps2emu/ps2_emu.self", ent->d_name);
		Extract(temp);

		u32 elf_size = 0;
		
		elf = fopen("temp_dec", "rb");
		if(elf==NULL) {
			printf(error("cannot open ps2_emu.elf %s\n"), ent->d_name);
			continue;
		}
		fseek (elf , 0 , SEEK_END);
		elf_size = ftell(elf);
		fseek(elf, 0, SEEK_SET);
				
		char *elf_data = (char*) malloc (sizeof(char)*elf_size);
		if (elf_data == NULL) {
			printf(error("cannot malloc ps2_emu.self %s\n"), ent->d_name);
			fclose(elf);
			continue;
		}
		fread(elf_data,1,elf_size, elf);			
		fclose(elf);
			
		system("del temp_dec");
		
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
	
	fputs("\n", fw);
	fclose(fw);
	
	fputs(" return FAILED;\n\
\n\
	return SUCCESS;\n\
}\n\
\n\
u8 get_gxemu(u32 crc, u8 **stage1, u32 *stage1_size, u8 **stage2, u32 *stage2_size)\n\
{\n", ps2vers);
	
	fputs("#endif /* PS2HWEMU */\n\n", sym);
	
// ps2_gxemu
	
	fputs("#ifdef PS2GXEMU\n\n", sym);
	
	fputs("\t#define DATA_TOC_OFFSET             -0x5B00\n", sym);
	fputs("\t#define LPAR_TOC_OFFSET            -0x5BC8\n", sym);
	fputs("\t#define FILESZ_TOC_OFFSET           -0xE68\n\n", sym);
	
	d = opendir("flash");
	if(d== NULL) {
		printf("Directory ps2emu not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		if(exist(temp)) continue;
		
		sprintf(str, "\n\
	if(crc == CRC32GXEMU_%s) {\n\
		*stage1_size = (uint32_t) ps2gxemu_stage1_%s_bin_size;\n\
		*stage1 = (uint8_t *) ps2gxemu_stage1_%s_bin;\n\
		*stage2_size = (uint32_t) ps2gxemu_stage2_%s_bin_size;\n\
		*stage2 = (uint8_t *) ps2gxemu_stage2_%s_bin;\n\
	} else ", ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name);
		fputs(str, ps2vers);
		
		sprintf(temp, "flash/%s/dev_flash/ps2emu/ps2_gxemu.self", ent->d_name);
		Extract(temp);
		
		u32 elf_size = 0;
		
		elf = fopen("temp_dec", "rb");
		if(elf==NULL) {
			printf(error("cannot open ps2_gxemu.elf %s\n"), ent->d_name);
			continue;
		}
		fseek (elf , 0 , SEEK_END);
		elf_size = ftell (elf);
		fseek(elf, 0, SEEK_SET);
				
		char *elf_data = (char*) malloc (sizeof(char)*elf_size);
		if (elf_data == NULL) {
			printf(error("cannot malloc ps2_gxemu.self %s\n"), ent->d_name);
			fclose(elf);
			continue;
		}
		fread(elf_data,1,elf_size, elf);			
		fclose(elf);
			
		system("del temp_dec");
		
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
		
		free(elf_data);
	}
	closedir(d);
	
	fputs("#endif /* PS2GXEMU */\n\n", sym);

	fputs(" return FAILED;\n\
	\n\
	return SUCCESS;\n\
	\n\
}\n\
\n\
u8 get_netemu(u32 crc, u8 **stage2, u32 *stage2_size)\n\
{\n", ps2vers);
	
//ps2netemu

	fputs("#ifdef PS2NETEMU\n\n", sym);
	
	fputs("\t#define EXTENDED_DATA	(0x821000+0x2953478)\n\n", sym);
	
	d = opendir("flash");
	if(d== NULL) {
		printf("Directory ps2emu not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		if(exist(temp)) continue;
		
		sprintf(str, "\n\
	if(crc == CRC32NETEMU_%s) {\n\
		*stage2_size = (uint32_t) ps2netemu_stage2_%s_bin_size;\n\
		*stage2 = (uint8_t *) ps2netemu_stage2_%s_bin;\n\
	} else ", ent->d_name, ent->d_name, ent->d_name);
		fputs(str, ps2vers);
		
		sprintf(temp, "flash/%s/dev_flash/ps2emu/ps2_netemu.self", ent->d_name);
		Extract(temp);
		
		u32 elf_size = 0;
		
		elf = fopen("temp_dec", "rb");
		if(elf==NULL) {
			printf(error("cannot open ps2_netemu.elf %s\n"), ent->d_name);
			continue;
		}
		fseek (elf , 0 , SEEK_END);
		elf_size = ftell (elf);
		fseek(elf, 0, SEEK_SET);
				
		char *elf_data = (char*) malloc (sizeof(char)*elf_size);
		if (elf_data == NULL) {
			printf(error("cannot malloc ps2_netemu.self %s\n"), ent->d_name);
			fclose(elf);
			continue;
		}
		fread(elf_data,1,elf_size, elf);			
		fclose(elf);
			
		system("del temp_dec");
		
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
		       fputs("\t\t#define decrypt_symbol                           cdvd_read_symbol\n", sym);
		fputs("\t#endif /* FIRMWARE */\n\n", sym);
		
		free(elf_data);
	}
	closedir(d);
	
	fputs("#endif /* PS2NETEMU */\n\n", sym);
	
	fputs("\n#endif /* __PS2EMU_SYMBOLS_H_S__ */\n", sym);
	
	fputs("\n#endif /* __PS2DATA_H__ */\n", ps2data);
	
	fputs(" return FAILED;\n\
	\n\
	return SUCCESS;\n\
}\n", ps2vers);

	fclose(ps2vers);
	fclose(sym);
	
	return 0;
}

int SearchOffsets()
{	
	char *mem;
	char dump[255];
	FILE *common;
	FILE *SKY;
	FILE *symbols_old;
	FILE *symbols;
	FILE *IDPSET_firmware_h;
	FILE *IDPSET_firmware_c;
	FILE *IDPSET_symbols_h;
	FILE *IDPSET_data_h;
	FILE *fw;
	FILE *data;
	FILE *fwc;
	
	char temp[2048];
	char temp2[2048];
	
	DIR *d;
	struct dirent* ent = NULL;
	
	int size=0;
	
	IDPSET_firmware_h = fopen("IDPSET_firmware.h", "w");
	IDPSET_data_h = fopen("IDPSET_data.h", "w");
	IDPSET_symbols_h = fopen("IDPSET_symbols.h", "w");
	IDPSET_firmware_c = fopen("IDPSET_firmware.c", "w");
	
	SKY = fopen("firmware_symbols.h", "w");
	common = fopen("common.h", "w");
	symbols_old = fopen("symbols_old.h", "w");
	symbols = fopen("symbols.h", "w");
	
	fw = fopen("FIRMWARES", "w");
	fwc = fopen("fw.c", "w");
	data = fopen("data.h","w");
	
	fputs("#ifndef __DATA_H__\n", data);
	fputs("#define __DATA_H__\n\n", data);
	fputs("#include <ppu-types.h>\n\n", data);
	
	fputs("PAYLOADS     :=", fw);
	
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
	
	fputs("#ifndef __FIRMWARE_SYMBOLS_H_S__\n", symbols_old);
	fputs("#define __FIRMWARE_SYMBOLS_H_S__\n\n", symbols_old);
	
	fputs("#define umd_mutex_offset (0x64480+0x38C)\n\n", symbols_old);
	
	fputs("#ifndef __FIRMWARE_SYMBOLS_H_S__\n", symbols);
	fputs("#define __FIRMWARE_SYMBOLS_H_S__\n\n", symbols);
	
	fputs("#define umd_mutex_offset (0x64480+0x38C)\n\n", symbols);
	
	fputs("#ifndef __SYMBOLS_H__\n", IDPSET_symbols_h);
	fputs("#define __SYMBOLS_H__\n\n", IDPSET_symbols_h);
	fputs("#define KERNEL_BASE 0x8000000000000000\n\n", IDPSET_symbols_h);
	
	fputs("#ifndef __DATA_H__\n", IDPSET_data_h);
	fputs("#define __DATA_H__\n\n", IDPSET_data_h);

	fputs("#ifndef __FIRMWARE_H__\n", IDPSET_firmware_h);
	fputs("#define __FIRMWARE_H__\n", IDPSET_firmware_h);
	fputs("\n\
#include <ppu-types.h>\n\
#include \"data.h\"\n\
\n\
int init_IDPSet();\n", IDPSET_firmware_h);
	
	fputs("\n\
#include <sys/file.h>\n\
#include \"firmware.h\"\n\
\n\
#define SUCCESS		1\n\
#define FAILED 		0\n\
\n\
extern u8 rebug;\n\
extern u64 *payload;\n\
extern size_t payload_size;\n\
extern u32 firmware;\n\
extern u64 TOC_OFFSET;\n\
extern u64 HV_START_OFFSET;\n\
extern u64 HTAB_OFFSET;\n\
extern u64 SYSCALL_TABLE_OFFSET;\n\
extern u64 MMAP_OFFSET1;\n\
extern u64 MMAP_OFFSET2;\n\
extern u64 SPE_OFFSET;\n\
extern u64 OFFSET_1_IDPS;\n\
extern u64 OFFSET_2_IDPS;\n\
\n\
extern int fw_is_rebug();\n\
extern u64 lv2peek(u64 addr);\n\
\n\
int init_IDPSet()\n\
{\n\
\n\
	OFFSET_1_IDPS = 0;\n\
	OFFSET_2_IDPS = 0;\n", IDPSET_firmware_c);

	fputs("\n\
#include \"fw.h\"\n\
\n\
#define SUCCESS		1\n\
#define FAILED 		0\n\
\n\
extern int firmware;\n\
extern u64 TOC;\n\
extern u64 SYSCALL_TABLE;\n\
extern u64 HV_START_OFFSET;\n\
extern u64 HTAB_OFFSET;\n\
extern u64 HTAB_PATCH1;\n\
extern u64 HTAB_PATCH2;\n\
extern u64 HTAB_PATCH3;\n\
extern u64 MMAP_OFFSET1;\n\
extern u64 MMAP_OFFSET2;\n\
extern u64 SPE_OFFSET;\n\
extern u64 OFFSET_FIX;\n\
extern u64 OFFSET_2_FIX;\n\
extern u64 OFFSET_FIX_3C;\n\
extern u64 OFFSET_FIX_2B17;\n\
extern u64 OFFSET_FIX_LIC;\n\
extern u64 OPEN_HOOK;\n\
extern u64 BASE_ADDR;\n\
extern u64 UMOUNT_SYSCALL_OFFSET;\n\
extern u64 LV2MOUNTADDR;\n\
extern u64 LV2MOUNTADDR_ESIZE;\n\
extern u64 LV2MOUNTADDR_CSIZE;\n\
extern u64 NEW_POKE_SYSCALL_ADDR;\n\
extern u64 PAYLOAD_SKY;\n\
extern size_t PAYLOAD_SKY_SIZE;\n\
extern u64 UMOUNT;\n\
extern size_t UMOUNT_SIZE;\n\
extern u64 MAMBA;\n\
extern size_t MAMBA_SIZE;\n\
extern u64 *MAMBA_LOADER;\n\
extern size_t MAMBA_LOADER_SIZE;\n\
extern u64 *ERK_DUMPER;\n\
extern size_t ERK_DUMPER_SIZE;\n\
extern u64 OFFSET_1_IDPS;\n\
extern u64 OFFSET_2_IDPS;\n\
\n\
extern void print_load(char *format, ...);\n\
extern u64 lv2peek(u64 addr);\n\
\n\
u8 init_fw()\n\
{", fwc);
	
	printf("Searching offsets...\n");
	
	d = opendir("LV2");
	if(d== NULL) {
		printf("Put your dumps in the directory 'LV2'\n");
		return 0;
	}
	
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "%s ", ent->d_name); fputs(temp, fw);

		sprintf(temp, "#include \"erk_dumper_%s_bin.h\"\n", ent->d_name); fputs(temp, data);
		sprintf(temp, "#include \"payload_sky_%s_bin.h\"\n", ent->d_name); fputs(temp, data);
		sprintf(temp, "#include \"umount_%s_bin.h\"\n", ent->d_name); fputs(temp, data);
		sprintf(temp, "#include \"mamba_%s_lz_bin.h\"\n", ent->d_name); fputs(temp, data);
		sprintf(temp, "#include \"mamba_loader_%s_bin.h\"\n\n", ent->d_name); fputs(temp, data);
		
		sprintf(temp, "#include \"payload_%s_bin.h\"\n", ent->d_name); fputs(temp, IDPSET_data_h);
		
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		u8 ps2payloads = 1;
		if( exist(temp) ) ps2payloads = 0;

		
		sprintf(temp, "\n\
	if(( lv2peek(FW_DATE_OFFSET_%s    )==FW_DATE_1_%s) &&\n\
	( lv2peek(FW_DATE_OFFSET_%s + 8)==FW_DATE_2_%s) )\n\
	{\n\
		firmware = 0x%s;\n\
		\n\
		TOC_OFFSET = TOC_OFFSET_%s;\n\
		HV_START_OFFSET = HV_START_OFFSET_%s;\n\
		HTAB_OFFSET = HTAB_OFFSET_%s;\n\
		SYSCALL_TABLE_OFFSET = SYSCALL_TABLE_%s;\n\
		MMAP_OFFSET1 = MMAP_OFFSET1_%s;\n\
		MMAP_OFFSET2 = MMAP_OFFSET2_%s;\n\
		SPE_OFFSET = SPE_OFFSET_%s;\n\
		OFFSET_1_IDPS = OFFSET_1_IDPS_%s;\n\
		OFFSET_2_IDPS = OFFSET_2_IDPS_%s;\n\
		\n\
		payload_size = payload_%s_bin_size;\n\
		payload = (u64 *) payload_%s_bin;\n\
	} else", ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name,
			 ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name);
		
		fputs(temp, IDPSET_firmware_c);
				
		sprintf(temp, "\n\
	if(( lv2peek(FW_DATE_OFFSET_%s    )==FW_DATE_1_%s) &&\n\
	   ( lv2peek(FW_DATE_OFFSET_%s + 8)==FW_DATE_2_%s) )\n\
	{\n\
		\n\
		firmware = 0x%s;\n\
		\n\
		OFFSET_2_FIX = OFFSET_2_FIX_%s;\n\
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_%s;\n\
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_%s;\n\
		OFFSET_FIX = OFFSET_FIX_%s;\n\
		HV_START_OFFSET = HV_START_OFFSET_%s;\n\
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_%s;\n\
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_%s;\n\
		OFFSET_FIX_3C = OFFSET_FIX_3C_%s;\n\
		TOC = TOC_%s;\n\
		SYSCALL_TABLE = SYSCALL_TABLE_%s;\n\
		HTAB_OFFSET = HTAB_OFFSET_%s;\n\
		HTAB_PATCH1 = HTAB_PATCH1_%s;\n\
		HTAB_PATCH2 = HTAB_PATCH2_%s;\n\
		HTAB_PATCH3 = HTAB_PATCH3_%s;\n\
		MMAP_OFFSET1 = MMAP_OFFSET1_%s;\n\
		MMAP_OFFSET2 = MMAP_OFFSET2_%s;\n\
		SPE_OFFSET = SPE_OFFSET_%s;\n\
		LV2MOUNTADDR = LV2MOUNTADDR_%s;\n\
		OPEN_HOOK = OPEN_HOOK_%s;\n\
		BASE_ADDR = BASE_ADDR_%s;\n\
		OFFSET_1_IDPS = OFFSET_1_IDPS_%s;\n\
		OFFSET_2_IDPS = OFFSET_2_IDPS_%s;\n\
		\n\
		PAYLOAD_SKY_SIZE = payload_sky_%s_bin_size;\n\
		PAYLOAD_SKY = (u64) payload_sky_%s_bin;\n\
		UMOUNT_SIZE = umount_%s_bin_size;\n\
		UMOUNT = (u64) umount_%s_bin;\n\
		MAMBA_SIZE = mamba_%s_lz_bin_size;\n\
		MAMBA = (u64) mamba_%s_lz_bin;\n\
		MAMBA_LOADER_SIZE = mamba_loader_%s_bin_size;\n\
		MAMBA_LOADER = (u64 *) mamba_loader_%s_bin;\n\
		ERK_DUMPER_SIZE = erk_dumper_%s_bin_size;\n\
		ERK_DUMPER = (u64 *) erk_dumper_%s_bin;\n\
		\n\
	} else",
		ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name,
		ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name,
		ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name,
		ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, ent->d_name, 
		ent->d_name);
		
		fputs(temp, fwc);
		
		
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
		
		u64 HTAB_OFFSET=0;
		u64 MMAP_OFFSET1=0;
		u64 MMAP_OFFSET2=0;
		u64 SPE_OFFSET=0;
		
		u64 HTAB_PATCH1=0;
		u64 HTAB_PATCH2=0;
		u64 HTAB_PATCH3=0;
		
		// need to do a dynamic search. It can be at different offset with the same firmware.
		//u64 UFS_SB_ADDR=0;
		
		//u8 ufs_sb_addr_flag[]={0x19, 0x54, 0x01, 0x19};
		u8 htab_patch1_flag[]={0x44, 0x00, 0x00, 0x22, 0x2C, 0x23, 0x00, 0x00, 0x7C, 0x7C, 0x1B, 0x78, 0x41, 0xE2, 0xFD, 0x64};
		u8 htab_patch2_flag[]={0x44, 0x00, 0x00, 0x22, 0x2C, 0x23, 0x00, 0x00, 0x7C, 0x7B, 0x1B, 0x78, 0x40, 0xC2, 0x00, 0xAC};
		u8 htab_patch3_flag[]={0x44, 0x00, 0x00, 0x22, 0x2C, 0x23, 0x00, 0x00, 0x7C, 0x78, 0x1B, 0x78, 0x40, 0xC2, 0x02, 0xD8};
		
		u64 LPAR=0;
		
		u8 flag_lpar[0x10]={0x00, 0x00, 0x50, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00};
		
		u8 flag_htab[0x8] = {0x41, 0xDA, 0x00, 0x54, 0xE9, 0x7F, 0x00, 0xA8};
		u8 flag_mmap1[0x8] = {0x88, 0x1F, 0x00, 0x99, 0x54, 0x00, 0x06, 0x3E};
		u8 flag_mmap2[0x8] = {0xE8, 0xFF, 0x00, 0xE0, 0x7C, 0x08, 0x03, 0x78};
		u8 flag_spe[0x8] = {0x39, 0x20, 0x00, 0x09, 0xE9, 0x43, 0x00, 0x00 };

		u8 flag_offset_fix[0x20] = {0x38, 0xDE, 0x00, 0x07, 0x88, 0x1E, 0x00, 0x07, 0x2F, 0x84, 0x00, 0x01, 0x98, 0x01, 0x00, 0x73, 0x88, 0x06, 0x00, 0x01, 0x88, 0xA6, 0x00, 0x08, 0x89, 0x26, 0x00, 0x02, 0x89, 0x66, 0x00, 0x03};
		u8 flag_offset_2_fix[0x20] = {0xF9, 0x1F, 0x00, 0x20, 0xF8, 0xFF, 0x00, 0x28, 0xF8, 0xDF, 0x00, 0x30, 0xF8, 0xBF, 0x00, 0x38, 0xFB, 0xBF, 0x00, 0x40, 0x4B, 0xFA, 0x97, 0x45, 0x54, 0x63, 0x06, 0x3E, 0x2F, 0x83, 0x00, 0x00};
		u8 flag_offset_fix_2B17[0x20] = {0x4E, 0x80, 0x00, 0x20, 0x3C, 0x80, 0x10, 0x50, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0x78, 0x84, 0x07, 0xC6, 0xFB, 0xE1, 0x00, 0x88, 0x64, 0x84, 0x03, 0x00, 0x7C, 0x7F, 0x1B, 0x78};
		u8 flag_offset_fix_lic[] = {0x2F, 0x83, 0x00, 0x00, 0x3B, 0xFF, 0x00, 0x6C, 0x41, 0x9E, 0x00, 0xFF, 0x38, 0x00, 0x00, 0x02, 0x3B};
		u8 flag_offset_fix_3C[0x20] = {0x4B, 0xFF, 0xFF, 0xD8, 0xE8, 0x03, 0x01, 0xA8, 0x7C, 0x09, 0xFE, 0x76, 0x7D, 0x23, 0x02, 0x78, 0x7C, 0x69, 0x18, 0x50, 0x38, 0x63, 0xFF, 0xFF, 0x78, 0x63, 0x0F, 0xE0, 0x4E, 0x80, 0x00, 0x20};
		u8 flag_open_hook[0x30] = {0x2B, 0xA3, 0x04, 0x20, 0x3F, 0xE0, 0x80, 0x01, 0x63, 0xFF, 0x00, 0x34, 0x40, 0x9D, 0x00, 0x2C, 0xE8, 0x01, 0x00, 0xB0, 0x7F, 0xE3, 0x07, 0xB4, 0xEB, 0x41, 0x00, 0x70, 0xEB, 0x61, 0x00, 0x78, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0x81, 0x00, 0x80, 0xEB, 0xA1, 0x00, 0x88, 0xEB, 0xE1, 0x00, 0x98};
		u8 flag_base_addr[0x20]	= {0x42, 0x61, 0x63, 0x6B, 0x74, 0x72, 0x61, 0x63, 0x65, 0x20, 0x49, 0x6E, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x3A, 0x0A, 0x00, 0x20, 0x20, 0x2D, 0x20, 0x30, 0x78, 0x25, 0x30};
		u8 flag_lv2mountaddr[0x20] = {0x43, 0x45, 0x4C, 0x4C, 0x5F, 0x46, 0x53, 0x5F, 0x41, 0x44, 0x4D, 0x49, 0x4E, 0x46, 0x53, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		u8 flag_firmware_offset[0x20] = {0x6E, 0x3A, 0x20, 0x25, 0x75, 0x2E, 0x25, 0x30, 0x32, 0x75, 0x20, 0x28, 0x25, 0x73, 0x29, 0x0A, 0x23, 0x20, 0x72, 0x65, 0x76, 0x69, 0x73, 0x69, 0x6F, 0x6E, 0x3A, 0x20, 0x25, 0x64, 0x0A, 0x00};
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
		
		u64 create_kernel_object_symbol=0;
		u64 destroy_kernel_object_symbol=0;
		u64 destroy_shared_kernel_object_symbol=0;
		u64 open_kernel_object_symbol=0;
		u64 open_shared_kernel_object_symbol=0;
		u64 close_kernel_object_handle_symbol=0;
		u64 alloc_symbol=0;
		u64 dealloc_symbol=0;
		u64 copy_to_user_symbol=0;
		u64 copy_from_user_symbol=0;
		u64 copy_to_process_symbol=0;
		u64 copy_from_process_symbol=0;
		u64 process_read_memory_symbol=0;
		u64 process_write_memory_symbol=0;
		u64 page_allocate_symbol=0;
		u64 page_free_symbol=0;
		u64 page_export_to_proc_symbol=0;
		u64 page_unexport_from_proc_symbol=0;
		u64 kernel_ea_to_lpar_addr_symbol=0;
		u64 process_ea_to_lpar_addr_ex_symbol=0;
		u64 set_pte_symbol=0;
		u64 map_process_memory_symbol=0;
		u64 panic_symbol=0;
		u64 memcpy_symbol=0;
		u64 memset_symbol=0;
		u64 memcmp_symbol=0;
		u64 memchr_symbol=0;
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
		u64 strrchr_symbol=0;		
		u64 spin_lock_irqsave_ex_symbol=0;
		u64 spin_unlock_irqrestore_ex_symbol=0;
		u64 create_process_common_symbol=0;
		u64 create_process_base_symbol=0;
		u64 load_process_symbol=0;
		u64 process_kill_symbol=0;
		u64 ppu_thread_create_symbol=0;
		u64 ppu_thread_exit_symbol=0;
		u64 ppu_thread_join_symbol=0;
		u64 ppu_thread_delay_symbol=0;
		u64 create_kernel_thread_symbol=0;
		u64 create_user_thread_symbol=0;
		u64 create_user_thread2_symbol=0;
		u64 start_thread_symbol=0;
		u64 run_thread_symbol=0;
		u64 self_threading_symbol=0;
		u64 register_thread_symbol=0;
		u64 allocate_user_stack_symbol=0;
		u64 deallocate_user_stack_symbol=0;
		u64 mutex_create_symbol=0;
		u64 mutex_destroy_symbol=0;
		u64 mutex_lock_symbol=0;
		u64 mutex_lock_ex_symbol=0;
		u64 mutex_trylock_symbol=0;
		u64 mutex_unlock_symbol=0;
		u64 cond_create_symbol=0;
		u64 cond_destroy_symbol=0;
		u64 cond_wait_symbol=0;
		u64 cond_wait_ex_symbol=0;
		u64 cond_signal_symbol=0;
		u64 cond_signal_all_symbol=0;
		u64 semaphore_initialize_symbol=0;
		u64 semaphore_wait_ex_symbol=0;
		u64 semaphore_trywait_symbol=0;
		u64 semaphore_post_ex_symbol=0;
		u64 event_port_create_symbol=0;
		u64 event_port_destroy_symbol=0;
		u64 event_port_connect_symbol=0;
		u64 event_port_disconnect_symbol=0;
		u64 event_port_send_symbol=0;
		u64 event_port_send_ex_symbol=0;
		u64 event_queue_create_symbol=0;
		u64 event_queue_destroy_symbol=0;
		u64 event_queue_receive_symbol=0;
		u64 event_queue_tryreceive_symbol=0;
		u64 cellFsOpen_symbol=0;
		u64 cellFsClose_symbol=0;
		u64 cellFsRead_symbol=0;
		u64 cellFsWrite_symbol=0;
		u64 cellFsLseek_symbol=0;
		u64 cellFsStat_symbol=0;
		u64 cellFsUtime_symbol=0;
		u64 cellFsUnlink_internal_symbol=0;
		u64 cellFsRename_internal_symbol =0;
		u64 cellFsUtilMount_symbol=0;
		u64 cellFsUtilUmount_symbol =0;
		u64 cellFsUtilNewfs_symbol=0;
		u64 pathdup_from_user_symbol=0;
		u64 open_path_symbol=0;
		u64 open_fs_object_symbol=0;
		u64 close_fs_object_symbol=0;	
		u64 storage_get_device_info_symbol=0;
		u64 storage_get_device_config_symbol=0;
		u64 storage_open_symbol=0;
		u64 storage_close_symbol=0;
		u64 storage_read_symbol=0;
		u64 storage_write_symbol=0;
		u64 storage_send_device_command_symbol=0;
		u64 storage_map_io_memory_symbol=0;
		u64 storage_unmap_io_memory_symbol=0;
		u64 new_medium_listener_object_symbol=0;
		u64 delete_medium_listener_object_symbol=0;
		u64 set_medium_event_callbacks_symbol=0;
		u64 cellUsbdRegisterLdd_symbol=0;
		u64 cellUsbdUnregisterLdd_symbol=0;
		u64 cellUsbdScanStaticDescriptor_symbol=0;
		u64 cellUsbdOpenPipe_symbol=0;
		u64 cellUsbdClosePipe_symbol=0;
		u64 cellUsbdControlTransfer_symbol=0;
		u64 cellUsbdBulkTransfer_symbol=0;
		u64 decrypt_func_symbol=0;
		u64 lv1_call_99_wrapper_symbol=0;
		u64 modules_verification_symbol=0;
		u64 authenticate_program_segment_symbol=0;
		u64 prx_load_module_symbol=0;
		u64 prx_start_module_symbol=0;
		u64 prx_stop_module_symbol=0;
		u64 prx_unload_module_symbol=0;
		u64 prx_get_module_info_symbol=0;
		u64 prx_get_module_id_by_address_symbol=0;
		u64 prx_get_module_id_by_name_symbol=0;
		u64 prx_get_module_list_symbol=0;
		u64 load_module_by_fd_symbol=0;
		u64 parse_sprx_symbol=0;
		u64 open_prx_object_symbol=0;
		u64 close_prx_object_symbol=0;
		u64 lock_prx_mutex_symbol=0;
		u64 unlock_prx_mutex_symbol=0;
		u64 extend_kstack_symbol=0;
		u64 get_pseudo_random_number_symbol=0;
		u64 md5_reset_symbol=0;
		u64 md5_update_symbol=0;
		u64 md5_final_symbol=0;
		u64 ss_get_open_psid_symbol=0;
		u64 update_mgr_read_eeprom_symbol=0;
		u64 update_mgr_write_eeprom_symbol=0;
		u64 update_mgr_if_get_token_symbol=0;
		u64 SHA1_init_symbol=0;
		u64 SHA1_update_symbol=0;
		u64 SHA1_final_symbol=0;
		u64 aescbccfb_dec_symbol=0;
		u64 aescbccfb_enc_symbol=0;
		u64 ss_params_get_update_status_symbol=0;
		u64 syscall_call_offset=0;
		u64 read_bdvd0_symbol=0;
		u64 read_bdvd1_symbol=0;
		u64 read_bdvd2_symbol=0;
		u64 storage_internal_get_device_object_symbol=0;
		u64 hid_mgr_read_usb_symbol=0;
		u64 hid_mgr_read_bt_symbol=0;
		u64 bt_set_controller_info_internal_symbol=0;
		u64 device_event_port_send_call=0;
		u32 device_event_port_send_call_restore=0;
		u64 ss_pid_call_1=0;
		u64 process_map_caller_call=0;
		u64 read_module_header_call=0;
		u64 read_module_body_call=0;
		u64 load_module_by_fd_call1=0;
		u64 shutdown_copy_params_call=0;
		u32 shutdown_copy_params_call_restore=0;
		u64 fsloop_open_call=0;
		u64 fsloop_close_call=0;
		u64 fsloop_read_call=0;
		u64 shutdown_patch_offset=0;
		u64 module_sdk_version_patch_offset=0;
		u64 module_add_parameter_to_parse_sprxpatch_offset=0;
		u64 user_thread_prio_patch=0;
		u64 user_thread_prio_patch2=0;
		u64 lic_patch=0;
		u64 ode_patch=0;
		s16 io_rtoc_entry_1=0;
		s16 io_sub_rtoc_entry_1=0;
		s16 decrypt_rtoc_entry_2=0;
		//u64 decrypter_data_entry=0;
		s16 storage_rtoc_entry_1=0;
		s16 device_event_rtoc_entry_1=0;
		s16 process_rtoc_entry_1=0;
		s16 time_rtoc_entry_1=0;
		s16 time_rtoc_entry_2=0;
		s16 thread_rtoc_entry_1=0;
		s16 bt_rtoc_entry_1=0;
		u64 permissions_func_symbol=0;
		u64 permissions_exception1=0;
		u64 permissions_exception2=0;
		u64 permissions_exception3=0;
		//u64 patch_data1_offset=0;
		u64 patch_func2=0;
		///u64 patch_func2_offset=0;
		///u64 patch_func8=0;
		u64 patch_func8_offset1=0;
		u64 patch_func8_offset2=0;
		///u64 patch_func9=0;
		u64 patch_func9_offset=0;
		u64 mem_base2=0;
		u64 thread_info_symbol=0;
		u64 ECDSA_1=0;	
		u64 ECDSA_2=0;
		//u64 ECDSA_FLAG=0;
		u64 fix_80010009=0;
		u64 fix_8001003D=0;
		u64 fix_8001003E=0;
		u64 PATCH_JUMP=0;
		//u64 sysmem_obj=0;
		u64 qa_eeprom_offset=0;
		u64 sm_get_temperature_symbol=0;
		u64 sm_get_fan_policy_symbol=0;
		u64 sm_set_fan_policy_symbol=0;
		u64 sm_get_temperature_patch=0;
		u64 sm_get_fan_policy_patch=0;
		u64 sm_set_fan_policy_patch=0;
		u64 get_path_by_fd_symbol=0;
		//u64 hash_checked_area=0;
		//u64 vsh_patch=0;                  
		u64 rsx_syscall_check=0;
		u64 unk_func2_unregister_service=0;
		u64 unk_func3_unregister_service=0;
		u64 mmapper_flags_temp_patch=0;
		u64 lic_patch_restore=0;
		u64 patch_func2_restore=0;
		u64 patch_func8_offset2_restore=0;
		
		u8 rsx_syscall_check_flag[]={0x7C, 0x70, 0x42, 0xA6, 0xA0, 0x03, 0x00, 0xC0, 0x2F, 0x80, 0x00, 0x03, 0x41, 0x9E, 0x00, 0x0C, 0xE8, 0x63, 0x00, 0xB0, 0x4E, 0x80, 0x00, 0x20, 0x7D, 0x30, 0x42, 0xA6, 0xE9, 0x69, 0x00, 0x68, 0x38, 0x60, 0x00, 0x00, 0xE9, 0x6B, 0x00, 0x00, 0x2F, 0xAB, 0x00, 0x00, 0x4D, 0x9E, 0x00, 0x20};
		u8 unk_func2_unregister_service_flag[]={0x4B, 0xAA, 0xAA, 0xAA, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x9D, 0x23, 0x78, 0x3C, 0x80, 0x00, 0x3D, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xE1, 0x00, 0x88, 0x60, 0x84, 0x09, 0x00};
		u8 unk_func3_unregister_service_flag[]={0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0x90, 0xE9, 0x23, 0x00, 0x20, 0x7C, 0x7F, 0x1B, 0x78, 0x2F, 0xA9, 0x00, 0x00, 0x7D, 0x23, 0x4B, 0x78};
		
		u8 create_kernel_object_symbol_flag[]={0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0x78, 0xF8, 0x01, 0x00, 0xB0, 0xE8, 0x03, 0x08, 0x00, 0x7C, 0x9B, 0x23, 0x78, 0xFB, 0x81, 0x00, 0x80, 0x2F, 0xA0, 0x00, 0x00};
		u8 destroy_kernel_object_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xA0, 0x7C, 0x68, 0x1B, 0x78};
		u8 destroy_shared_kernel_object_symbol_flag[]={0x54, 0x80, 0x06, 0x3E, 0x3D, 0x60, 0x80, 0x01, 0x2B, 0x80, 0x00, 0x7F, 0x54, 0x0A, 0x25, 0x36, 0x61, 0x6B, 0x00, 0x05, 0x7D, 0x0A, 0x1A, 0x14, 0x40, 0x9D, 0x00, 0x0C, 0x7D, 0x63, 0x07, 0xB4};
		u8 open_kernel_object_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x98, 0xFB, 0xC1, 0x00, 0xA0, 0xFB, 0xE1, 0x00, 0xA8, 0x78, 0x9E, 0x84, 0x02, 0x78, 0x9F, 0xC6, 0x22, 0x78, 0x9D, 0x06, 0x20};
		u8 open_shared_kernel_object_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0xB0, 0xFB, 0xC1, 0x00, 0xC0, 0xFB, 0xE1, 0x00, 0xC8, 0xF8, 0x01, 0x00, 0xE0, 0x78, 0x9C, 0x84, 0x02, 0x7C, 0xE0, 0x3B, 0x78};
		u8 close_kernel_object_handle_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x98, 0xFB, 0xE1, 0x00, 0xA8, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xC1, 0x00, 0xA0, 0xF8, 0x01, 0x00, 0xC0, 0x7C, 0x7D, 0x1B, 0x78, 0x7C, 0x9F, 0x23, 0x78, 0x7D, 0x30, 0x42, 0xA6};
		
		u8 alloc_symbol_flag[] = {0x2C, 0x23, 0x00, 0x00, 0x7C, 0x85, 0x23, 0x78, 0x38, 0xC0, 0x00, 0x00, 0x7C, 0x64, 0x1B, 0x78, 0x4D, 0x82, 0x00, 0x20};
		u8 dealloc_symbol_flag[] = {0x7C, 0x85, 0x23, 0x78, 0x38, 0xC0, 0x00, 0x00, 0x7C, 0x64, 0x1B, 0x78, 0xE8, 0x69, 0x00, 0x00, 0x4B, 0xFF, 0xFB, 0xD0, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6};
		u8 copy_to_user_symbol_flag[] = {0x2C, 0x25, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x7E, 0x1B, 0x78, 0xFB, 0x81, 0x00, 0x70};
		u8 copy_from_user_symbol_flag[] = {0x2C, 0x25, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x70, 0x7C, 0x7F, 0x1B, 0x78};
		u8 copy_to_process_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x25, 0x00, 0x00, 0xFB, 0x61, 0x00, 0xA8, 0x3F, 0x60, 0x80, 0x01, 0xFB, 0x21, 0x00, 0x98, 0xFB, 0x81, 0x00, 0xB0, 0xFA, 0xE1, 0x00, 0x88};
		u8 copy_from_process_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x41, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x24, 0x00, 0x00, 0xFB, 0x61, 0x00, 0x98, 0x3F, 0x60, 0x80, 0x01, 0xFB, 0x21, 0x00, 0x88, 0xFB, 0x81, 0x00, 0xA0, 0xFB, 0x01, 0x00, 0x80};
		u8 process_read_memory_symbol_flag[]={0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x25, 0x00, 0x00, 0xFB, 0xE1, 0x00, 0xA8, 0x3F, 0xE0, 0x80, 0x01, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xA1, 0x00, 0x98};
		u8 process_write_memory_symbol_flag[]={0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x25, 0x00, 0x00, 0xFB, 0xE1, 0x00, 0xA8, 0x3F, 0xE0, 0x80, 0x01, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90};
		u8 page_allocate_symbol_flag[] = {0x7C, 0x80, 0x23, 0x78, 0x7C, 0xA9, 0x2B, 0x78, 0x7C, 0xCB, 0x33, 0x78, 0x7C, 0xE8, 0x3B, 0x78, 0x7C, 0x64, 0x1B, 0x78, 0x7C, 0x05, 0x03, 0x78, 0x7D, 0x26, 0x4B, 0x78, 0x7D, 0x67, 0x5B, 0x78};
		u8 page_free_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x61, 0xF8, 0x01, 0x00, 0xB0, 0xFB, 0xC1, 0x00, 0x90, 0xFB, 0xE1, 0x00, 0x98, 0xE9, 0x2B, 0x00, 0x00, 0x7C, 0x7F, 0x1B, 0x78, 0x7C, 0xBE, 0x2B, 0x78};
		u8 page_export_to_proc_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0x3D, 0x20, 0x00, 0x0C, 0xF8, 0x01, 0x00, 0xA0, 0x54, 0xA0, 0x03, 0x1A, 0xFB, 0xE1, 0x00, 0x88, 0x7F, 0xA0, 0x48, 0x00, 0x3D, 0x20, 0x80, 0x01};
		u8 page_unexport_from_proc_symbol_flag[] = {0x2B, 0xA3, 0x00, 0x3C, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0xF8, 0x01, 0x00, 0x80, 0x7C, 0x8B, 0x23, 0x78, 0x7C, 0x60, 0x1B, 0x78};
		u8 kernel_ea_to_lpar_addr_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x51, 0xF8, 0x01, 0x00, 0xC0, 0xFB, 0xC1, 0x00, 0xA0, 0xFB, 0x61, 0x00, 0x88, 0xEB, 0xC9, 0x00, 0x00, 0x7C, 0x9B, 0x23, 0x78, 0xFB, 0x81, 0x00, 0x90};
		u8 process_ea_to_lpar_addr_ex_symbol_flag[]={0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xC0, 0xE9, 0x63, 0x00, 0x08, 0x7C, 0xBB, 0x2B, 0x78, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xC1, 0x00, 0xA0};
		u8 set_pte_symbol_flag[]={0xF8, 0x21, 0xFF, 0x21, 0x7C, 0x08, 0x02, 0xA6, 0xFA, 0xE1, 0x00, 0x98, 0x7C, 0x77, 0x1B, 0x78, 0x7C, 0x83, 0x23, 0x78, 0x7C, 0xA4, 0x2B, 0x78, 0x7D, 0x05, 0x43, 0x78, 0xF8, 0x01, 0x00, 0xF0};
		u8 map_process_memory_symbol_flag[] = {0xF8, 0x21, 0xFE, 0xE1, 0xFA, 0xC1, 0x00, 0xD0, 0x7C, 0xF6, 0x3B, 0x78, 0xFB, 0x81, 0x01, 0x00};
		u8 panic_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xA0, 0x7F, 0x8C, 0x42, 0xE6};
		
		u8 memcpy_symbol_flag[] = {0x2B, 0xA5, 0x00, 0x07, 0x7C, 0x6B, 0x1B, 0x78, 0x41, 0x9D, 0x00, 0x2C, 0x2C, 0x25, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x4D, 0x82, 0x00, 0x20, 0x7C, 0xA9, 0x03, 0xA6, 0x88, 0x04, 0x00, 0x00};
		u8 memset_symbol_flag[] = {0x2B, 0xA5, 0x00, 0x17, 0x7C, 0x6A, 0x1B, 0x78, 0x41, 0x9D, 0x00, 0x24, 0x2F, 0xA5, 0x00, 0x00, 0x4D, 0x9E, 0x00, 0x20, 0x7C, 0x80, 0x23, 0x78, 0x7C, 0xA9, 0x03, 0xA6, 0x98, 0x0A, 0x00, 0x00};
		u8 memcmp_symbol_flag[] = {0x38, 0xA5, 0x00, 0x01, 0x7C, 0xA9, 0x03, 0xA6, 0x42, 0x40, 0x00, 0x30, 0x88, 0x03, 0x00, 0x00, 0x38, 0x63, 0x00, 0x01, 0x89, 0x24, 0x00, 0x00, 0x38, 0x84, 0x00, 0x01, 0x7F, 0x89, 0x00, 0x00};
		u8 memchr_symbol_flag[]={0x2C, 0x25, 0x00, 0x00, 0x41, 0x82, 0x00, 0x3C, 0x88, 0x03, 0x00, 0x00, 0x39, 0x20, 0x00, 0x00, 0x38, 0x63, 0x00, 0x01, 0x7F, 0x80, 0x20, 0x00, 0x40, 0x9E, 0x00, 0x18, 0x48, 0x00, 0x00, 0x2C};
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
		u8 strrchr_symbol_flag[]={0x39, 0x20, 0x00, 0x00, 0x48, 0x00, 0x00, 0x0C, 0x38, 0x63, 0x00, 0x01, 0x41, 0x9A, 0x00, 0x20, 0x88, 0x03, 0x00, 0x00, 0x7F, 0x80, 0x20, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x40, 0x9E, 0xFF, 0xEC};
		
		u8 spin_lock_irqsave_ex_symbol_flag[] = {0x7C, 0x20, 0x04, 0xAC, 0x2F, 0x85, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0x20, 0x00, 0x00, 0x90, 0x03, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x0C, 0x7C, 0x81, 0x01, 0x64, 0x4E, 0x80, 0x00, 0x20, 0x61, 0x29, 0x80, 0x02, 0x7D, 0x21, 0x01, 0x64, 0x4E, 0x80, 0x00, 0x20};
		u8 spin_unlock_irqrestore_ex_symbol_flag[] = {0x7C, 0x20, 0x04, 0xAC, 0x2F, 0x85, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0x20, 0x00, 0x00, 0x90, 0x03, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x0C, 0x7C, 0x81, 0x01, 0x64, 0x4E, 0x80, 0x00, 0x20};
		
		u8 create_process_common_symbol_flag[]={0x7C, 0x08, 0x02, 0xA6, 0xFA, 0x41, 0x01, 0x40, 0xFA, 0x61, 0x01, 0x48, 0xEA, 0x41, 0x02, 0x50, 0xEA, 0x61, 0x02, 0x48};
		u8 create_process_base_symbol_flag[]={0xF8, 0x21, 0xFF, 0x11, 0x7C, 0x08, 0x02, 0xA6, 0xFA, 0xC1, 0x00, 0xA0, 0xFA, 0xE1, 0x00, 0xA8, 0xFB, 0x01, 0x00, 0xB0, 0xFB, 0x21, 0x00, 0xB8};
		u8 load_process_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x11, 0xFA, 0xC1, 0x00, 0xA0, 0xFB, 0x61, 0x00, 0xC8, 0xFB, 0x81, 0x00, 0xD0, 0x7C, 0x7B, 0x1B, 0x78, 0x7C, 0xB6, 0x2B, 0x78, 0x7C, 0x9C, 0x23, 0x78};
		u8 process_kill_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xE1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xA0, 0x7C, 0x7E, 0x1B, 0x78};

		u8 ppu_thread_create_symbol_flag[] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x81, 0xFB, 0xC1, 0x00, 0x70, 0xFB, 0xE1, 0x00, 0x78, 0x7C, 0x7E, 0x1B, 0x78, 0x7C, 0xDF, 0x33, 0x78, 0x91, 0x81, 0x00, 0x88, 0x7C, 0x08, 0x02, 0xA6};
		u8 ppu_thread_exit_symbol_flag[] = {0x80, 0x03, 0x00, 0x90, 0x54, 0x00, 0x04, 0x62, 0x2F, 0x80, 0x00, 0x00, 0x40, 0xDE, 0x00, 0x1C};
		u8 ppu_thread_join_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x80, 0xF8, 0x01, 0x00, 0xB0, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xC1, 0x00, 0x90, 0x7C, 0x7D, 0x1B, 0x78, 0xFB, 0xE1, 0x00, 0x98};
		u8 ppu_thread_delay_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x01, 0x7C, 0x08, 0x02, 0xA6, 0xFA, 0xC1, 0x00, 0xB0, 0xFA, 0xE1, 0x00, 0xB8, 0xFB, 0x61, 0x00, 0xD8, 0xFB, 0xA1, 0x00, 0xE8, 0xFB, 0xC1, 0x00, 0xF0, 0xFB, 0x01, 0x00, 0xC0};
		u8 create_kernel_thread_symbol_flag[]={0xF8, 0x21, 0xFF, 0x11, 0x7C, 0x08, 0x02, 0xA6, 0x55, 0x0B, 0x06, 0x32, 0xF8, 0x01, 0x01, 0x00, 0x55, 0x00, 0x07, 0xFE, 0xFB, 0x21, 0x00, 0xB8, 0x2F, 0x80, 0x00, 0x00, 0xFB, 0x41, 0x00, 0xC0};
		u8 create_user_thread_symbol_flag[]={0xF8, 0x21, 0xFF, 0x11, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x00, 0xB0, 0xEB, 0x02, 0x8B};
		u8 create_user_thread2_symbol_flag[] = {0xF8, 0x21, 0xFE, 0xF1, 0x7C, 0x08, 0x02, 0xA6, 0xFA, 0x81, 0x00, 0xB0, 0xF8, 0x01, 0x01, 0x20, 0x80, 0x09, 0x00, 0x28, 0x7C, 0xD4, 0x33, 0x78, 0xFA, 0xA1, 0x00, 0xB8, 0xFA, 0xC1, 0x00, 0xC0};
		u8 start_thread_symbol_flag[] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x61, 0xFB, 0x41, 0x00, 0x70, 0xFB, 0x61, 0x00, 0x78, 0xFB, 0x81, 0x00, 0x80, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xC1, 0x00, 0x90, 0xFB, 0xE1, 0x00, 0x98};
		u8 run_thread_symbol_flag[] = {0x7C, 0x64, 0x1B, 0x78, 0xE8, 0x63, 0x00, 0x48, 0x48, 0x00, 0xFF, 0xFF, 0xF8, 0x21, 0xFF, 0x71};
		u8 self_threading_symbol_flag[] = {0x7C, 0x9D, 0x23, 0x78, 0xF8, 0x01, 0x00, 0xB0, 0xFB, 0x81, 0x00, 0x80, 0x38, 0x80, 0x00, 0x00, 0x7F, 0xA3, 0xEB, 0x78, 0xEB, 0x9D, 0x05, 0x20, 0xFB, 0x61, 0x00, 0x78};
		u8 register_thread_symbol_flag[] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x71, 0x2C, 0x24, 0x00, 0x00, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x9F, 0x23, 0x78, 0x7C, 0x7E, 0x1B, 0x78};
		u8 allocate_user_stack_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xB0, 0xE8, 0x03, 0x00, 0x30, 0x38, 0xC1, 0x00, 0x70, 0xFB, 0xC1, 0x00, 0x90, 0x2F, 0xA0, 0x00, 0x00};
		u8 deallocate_user_stack_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0xE8, 0x03, 0x00, 0x30, 0x7C, 0xBD, 0x2B, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0x2F, 0xA0, 0x00, 0x00};
		
		u8 mutex_create_symbol_flag[] = {0x2F, 0x85, 0x00, 0x20, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xA0, 0x7C, 0xBF, 0x2B, 0x78};
		u8 mutex_destroy_symbol_flag[] = {0x2F, 0xA3, 0x00, 0x00, 0x3C, 0x00, 0x80, 0x01, 0x60, 0x00, 0x00, 0x0A, 0x41, 0xDE, 0x00, 0x1C};
		u8 mutex_lock_ex_symbol_flag[]={0xF8, 0x21, 0xFF, 0x01, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0xD8, 0x7C, 0x7B, 0x1B, 0x78, 0xFB, 0x01, 0x00, 0xC0, 0xFB, 0x81, 0x00, 0xE0, 0xFB, 0xA1, 0x00, 0xE8, 0xFB, 0xE1, 0x00, 0xF8};
		
		u8 cond_create_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0x7C, 0x9D, 0x23, 0x78, 0x7C, 0x7E, 0x1B, 0x78, 0x38, 0x80, 0x00, 0x36, 0x38, 0xA0, 0x00, 0x00};
		u8 cond_destroy_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x7D, 0x1B, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x48, 0x00};
		u8 cond_wait_ex_symbol_flag[]={0xF8, 0x21, 0xFE, 0xF1, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0xE8, 0x7C, 0x7B, 0x1B, 0x78, 0xFB, 0x21, 0x00, 0xD8, 0xFB, 0xA1, 0x00, 0xF8, 0xFB, 0xC1, 0x01, 0x00, 0xFB, 0xE1, 0x01, 0x08};
		
		u8 semaphore_initialize_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7D, 0x1B, 0x78, 0xE9, 0x22, 0xFF, 0xFF, 0x38, 0x63, 0x00, 0x18, 0xF8, 0x01, 0x00, 0xA0, 0xF9, 0x3D, 0x00, 0x00, 0x90, 0xBD, 0x00, 0x08, 0x90, 0xDD, 0x00, 0x0C};
		u8 semaphore_wait_ex_symbol_flag[]={0xF8, 0x21, 0xFF, 0x11, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0xC8, 0xFB, 0x81, 0x00, 0xD0, 0xFB, 0xA1, 0x00, 0xD8, 0xFB, 0xC1, 0x00, 0xE0, 0xFB, 0x01, 0x00, 0xB0, 0xFB, 0x21, 0x00, 0xB8};
		u8 semaphore_trywait_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xE1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xA0, 0x7C, 0x7E, 0x1B, 0x78, 0x7D, 0x30, 0x42, 0xA6, 0xEB, 0x89, 0x00, 0x48, 0x3B, 0xA3, 0x00, 0x14, 0x3F, 0xE0, 0x80, 0x01};
		u8 semaphore_post_ex_symbol_flag[]={0xF8, 0x21, 0xFF, 0x41, 0x7C, 0x08, 0x02, 0xA6, 0x2F, 0x84, 0x00, 0x00, 0xFB, 0xC1, 0x00, 0xB0, 0x3F, 0xC0, 0x80, 0x01, 0xFB, 0x81, 0x00, 0xA0, 0xFB, 0xE1, 0x00, 0xB8, 0xFA, 0xC1, 0x00, 0x70};

		u8 event_port_create_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0x38, 0xA0, 0x00, 0x00, 0x7C, 0x7E, 0x1B, 0x78, 0x7C, 0x9D, 0x23, 0x78, 0x38, 0x60, 0x00, 0x20};
		u8 event_port_destroy_symbol_flag[] = {0xE8, 0x01, 0x00, 0xA0, 0xEB, 0x81, 0x00, 0x70, 0x7F, 0xA3, 0x07, 0xB4, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xA1, 0x00, 0x78, 0x38, 0x21, 0x00, 0x90, 0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x80, 0xEB, 0xFF, 0xFF, 0xFF, 0x38, 0x80, 0x00, 0x00, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xA1, 0x00, 0x78};
		u8 event_port_connect_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0x78, 0xEB, 0x62, 0xFF, 0xFF, 0x38, 0xA0, 0x00, 0x00, 0xF8, 0x01, 0x00, 0xB0, 0xFB, 0x81, 0x00, 0x80, 0xFB, 0xA1, 0x00, 0x88};
		u8 event_port_disconnect_symbol_flag[] = {0x4B, 0xFF, 0xFF, 0x4C, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xEB, 0x82, 0xFF, 0xFF, 0x38, 0x80, 0x00, 0x00, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xA1, 0x00, 0x78, 0x38, 0xA0, 0x00, 0x00};
		u8 event_port_send_symbol_flag[]={0x38, 0xE0, 0x00, 0x01, 0x48, 0x01, 0x81, 0x90, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0x38, 0xA0, 0x00, 0x00, 0x7C, 0x7E, 0x1B, 0x78};
		u8 event_port_send_ex_symbol_flag[]={0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0xA8, 0x7C, 0x7F, 0x1B, 0x78, 0xFB, 0xC1, 0x00, 0xA0, 0x3B, 0xC3, 0x00, 0x18, 0xFB, 0x21, 0x00, 0x78, 0x7F, 0xC3, 0xF3, 0x78};

		u8 event_queue_create_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x98, 0xF8, 0x01, 0x00, 0xB0, 0x38, 0x06, 0xFF, 0xFF, 0x3F, 0xE0, 0x80, 0x01, 0x2B, 0x80, 0x00, 0x7E, 0x38, 0x04, 0xFF, 0xFF};
		u8 event_queue_destroy_symbol_flag[] = {0xEB, 0xC1, 0x00, 0x90, 0xEB, 0xE1, 0x00, 0x98, 0x7C, 0x08, 0x03, 0xA6, 0x7D, 0x23, 0x07, 0xB4};
		u8 event_queue_receive_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x98, 0xF8, 0x01, 0x00, 0xB0, 0x81, 0x23, 0x00, 0x88, 0x3F, 0xE0, 0x80, 0x01, 0x38, 0x00, 0x00, 0x00, 0x2F, 0x89, 0x00, 0x01};
		u8 event_queue_tryreceive_symbol_flag[]={0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0x3D, 0x20, 0x80, 0x01, 0xF8, 0x01, 0x00, 0xB0, 0x38, 0x00, 0x00, 0x00, 0xFB, 0xA1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0x70, 0x80, 0x03, 0x00, 0x88};
				
		u8 cellFsOpen_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x00, 0x70, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0xA1, 0x00, 0x98, 0xFB, 0xC1, 0x00, 0xA0, 0x7C, 0x7D, 0x1B, 0x78};
		u8 cellFsClose_symbol_flag[] = {0x4B, 0xFF, 0xFF, 0x10, 0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x90};
		u8 cellFsRead_symbol_flag[] = {0x2C, 0x26, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0x3D, 0x20, 0x80, 0x01, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xE1, 0x00, 0x80, 0xF8, 0x01, 0x00, 0xA0, 0x7C, 0xDF, 0x33, 0x78};
		u8 cellFsWrite_symbol_flag[] = {0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0x7C, 0xDA, 0x33, 0x78, 0x7C, 0xBB, 0x2B, 0x78};
		u8 cellFsLseek_symbol_flag[] = {0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0x7C, 0xDA, 0x33, 0x78, 0x7C, 0x9B, 0x23, 0x78}; 
		u8 cellFsStat_symbol_flag[] = {0x2C, 0x23, 0x00, 0x00, 0x7C, 0x7F, 0x1B, 0x78, 0x3F, 0x80, 0x80, 0x01, 0x7F, 0xA3, 0xEB, 0x78, 0x7F, 0xE4, 0xFB, 0x78, 0x63, 0x9C, 0x00, 0x04, 0x41, 0x82, 0x00, 0x2C, 0x48, 0x00, 0x04, 0xC5};
		u8 cellFsUtime_symbol_flag[]={0x7C, 0x7C, 0x1B, 0x78, 0x7F, 0xE3, 0xFB, 0x78, 0x4B, 0xFF, 0xFF, 0xBC, 0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0x78, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xC1, 0x00, 0x90, 0x7C, 0x7D, 0x1B, 0x78};
		u8 cellFsUnlink_internal_symbol_flag[] = {0xF8, 0x21, 0xFE, 0xF1, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x24, 0x00, 0x00, 0xFB, 0xE1, 0x01, 0x08, 0x3F, 0xE0, 0x80, 0x01, 0xFB, 0x81, 0x00, 0xF0, 0xFB, 0xA1, 0x00, 0xF8, 0xFB, 0xC1, 0x01, 0x00};
		u8 cellFsRename_internal_symbol_flag[]={0x7D, 0x80, 0x00, 0x26, 0x2C, 0x24, 0x00, 0x00, 0xF8, 0x21, 0xFF, 0x11, 0xFB, 0x61, 0x00, 0xC8};
		u8 cellFsUtilMount_symbol_flag[] = {0x7C, 0x64, 0x1B, 0x78, 0x7C, 0x05, 0x03, 0x78, 0x38, 0xE0, 0x00, 0x00, 0xE9, 0x3E, 0x80, 0xB0, 0xEB, 0xC1, 0xFF, 0xF0, 0xE8, 0x69, 0x00, 0x00, 0x4B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xFF, 0xFF, 0xFF, 0x3B, 0xFF, 0x00, 0x80};		
		u8 cellFsUtilUmount_symbol_flag[]={0xFB, 0xC1, 0xFF, 0xF0, 0xEB, 0xC2, 0x25, 0xB0, 0x7C, 0x80, 0x23, 0x78, 0x7C, 0xA6, 0x2B, 0x78, 0x7C, 0x64, 0x1B, 0x78, 0x7C, 0x05, 0x03, 0x78, 0x38, 0xE0, 0x00, 0x00, 0xE9, 0x3E, 0x80, 0xB0};
		u8 cellFsUtilNewfs_symbol_flag[]={0xF8, 0x21, 0xFF, 0x01, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0xE8, 0x3B, 0xA1, 0x00, 0x70, 0xFB, 0x61};

		u8 pathdup_from_user_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x21, 0x00, 0x78, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0xC1, 0x00, 0xA0, 0x7C, 0x7A, 0x1B, 0x78};
		u8 open_path_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x80, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xE1, 0x00, 0x98, 0xFB, 0x41, 0x00, 0x70, 0xFB, 0x61, 0x00, 0x78, 0xF8, 0x01, 0x00, 0xB0, 0x7C, 0x9C, 0x23, 0x78};
		u8 open_fs_object_symbol_flag[] = {0x4B, 0xFF, 0xBB, 0xBB, 0x7D, 0x80, 0x00, 0x26, 0xF8, 0xBB, 0xBB, 0xBB, 0xFB};		
		u8 close_fs_object_symbol_flag[] = {0xEB, 0xE1, 0x00, 0x78, 0x7C, 0x08, 0x03, 0xA6, 0x38, 0x21, 0x00, 0x80, 0x4E, 0x80, 0x00, 0x20, 0x7C, 0x83, 0x23, 0x78, 0x38, 0xA0, 0x00, 0x00, 0x38, 0x80, 0x00, 0x00};
		
		u8 storage_get_device_info_symbol_flag[] = {0x7D, 0x49, 0x03, 0xA6, 0x4E, 0x80, 0x04, 0x21, 0xE8, 0x01, 0x00, 0xB0, 0x7C, 0x63, 0x07, 0xB4, 0xEB, 0x61, 0x00, 0x78, 0xEB, 0x81, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xA1, 0x00, 0x88, 0xEB, 0xC1, 0x00, 0x90, 0xEB, 0xE1, 0x00, 0x98, 0x38, 0x21, 0x00, 0xA0, 0x4E, 0x80, 0x00, 0x20};
		u8 storage_get_device_config_symbol_flag[]={0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xE1, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x70, 0xEB, 0xE9, 0x00, 0x00, 0x7C, 0x9C, 0x23, 0x78, 0xFB, 0xFF, 0xFF, 0xFF, 0x38, 0x80, 0x00, 0x00, 0x7C, 0x7D, 0x1B, 0x78};
		u8 storage_open_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x11, 0xF8, 0x01, 0x01, 0x00, 0xFB, 0xA1, 0x00, 0xD8, 0xF8, 0x61, 0x01, 0x20, 0xEB, 0xA9, 0x00, 0x00, 0xFB, 0x41, 0x00, 0xC0, 0x7C, 0x9A, 0x23, 0x78};
		u8 storage_open_symbol_flag1[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x61, 0x01, 0x20, 0x38, 0x61, 0x01, 0x20, 0xFB, 0x01, 0x00, 0xB0, 0xFB, 0x21, 0x00, 0xB8, 0xFB, 0x41, 0x00, 0xC0, 0xFB, 0x81, 0x00, 0xD0, 0xFB, 0xA1, 0x00, 0xD8};
		u8 storage_close_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x51, 0xF8, 0x01, 0x00, 0xC0, 0xFB, 0xE1, 0x00, 0xA8, 0xFB, 0x81, 0x00, 0x90, 0xEB, 0xE9, 0x00, 0x00, 0x7C, 0x7C, 0x1B, 0x78, 0x38, 0x80, 0x00, 0x00};
		u8 storage_read_symbol_flag[] = {0xEA, 0xE1, 0x00, 0xB8, 0xEB, 0x01, 0x00, 0xC0, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0x21, 0x00, 0xC8, 0xEB, 0x41, 0x00, 0xD0, 0xEB, 0x61, 0x00, 0xD8, 0xEB, 0x81, 0x00, 0xE0, 0xEB, 0xA1, 0x00, 0xE8, 0xEB, 0xC1, 0x00, 0xF0, 0xEB, 0xE1, 0x00, 0xF8, 0x38, 0x21, 0x01, 0x00, 0x4E, 0x80, 0x00, 0x20, 0x48, 0x00, 0xFF, 0xFF, 0x7F, 0xE3, 0xFB, 0x78, 0x48, 0x00, 0xFF, 0xFF, 0x2F, 0x83, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x18, 0x93, 0xD7, 0x00, 0x00, 0x7F, 0xE3, 0xFB, 0x78, 0x48, 0x00, 0xFF, 0xFF, 0x7C, 0x7D, 0x1B, 0x78, 0x4B, 0xFF, 0xFF, 0x68, 0x93, 0x97, 0x00, 0x00, 0x4B, 0xFF, 0xFF, 0xEC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7C, 0x08, 0x02, 0xA6};
		u8 storage_write_symbol_flag[]={0xF8, 0x21, 0xFF, 0x01, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0xF8, 0x3B, 0xE1, 0x00, 0x70, 0xFB, 0x01, 0x00, 0xC0, 0xFB, 0x21, 0x00, 0xC8, 0xFB, 0x41, 0x00, 0xD0, 0xFB, 0x61, 0x00, 0xD8};
		u8 storage_send_device_command_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFE, 0xF1, 0xF8, 0x01, 0x01, 0x20, 0xFB, 0xE1, 0x01, 0x08, 0x7C, 0x7F, 0x1B, 0x78, 0xE8, 0x6B, 0x00, 0x00, 0xFB, 0xFF, 0x00, 0xFF, 0xFB, 0xC1, 0x01, 0x00};
		u8 storage_map_io_memory_symbol_flag[] = {0xE9, 0x4A, 0x00, 0x00, 0x7D, 0x49, 0x03, 0xA6, 0x4E, 0x80, 0x04, 0x21, 0xE8, 0x01, 0x00, 0xA0, 0x7C, 0x63, 0x07, 0xB4, 0xEB, 0x81, 0x00, 0x70, 0xEB, 0xA1, 0x00, 0x78, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xC1, 0x00, 0x80, 0xEB, 0xE1, 0x00, 0x88, 0x38, 0x21, 0x00, 0x90, 0x4E, 0x80, 0x00, 0x20};
		u8 storage_unmap_io_memory_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xE1, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x70, 0xEB, 0xE9, 0x00, 0x00, 0x7C, 0x9C, 0x23, 0x78, 0xFB, 0xC1, 0x00, 0x80};
		u8 storage_unmap_io_memory_symbol_flag1[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x61, 0x00, 0xC0, 0x38, 0x61, 0x00, 0xC0, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0xF8, 0x01, 0x00, 0xA0};
		u8 new_medium_listener_object_symbol_flag[]={0x4B, 0xFF, 0xFF, 0x2C, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x88, 0xEB};
		u8 delete_medium_listener_object_symbol_flag[]={0x40, 0x9E, 0xFD, 0xC0, 0x4B, 0xAA, 0xAA, 0xAA, 0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x24, 0x00, 0x00, 0xFB, 0xE1, 0x00, 0x78, 0x3F, 0xE0, 0x80, 0x01, 0xFB, 0xC1, 0x00, 0x70, 0xF8, 0x01, 0x00, 0x90, 0x7C, 0x9E, 0x23, 0x78};
		u8 set_medium_event_callbacks_symbol_flag[]={0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x41, 0x00, 0x80, 0xF8, 0x01, 0x00, 0xC0, 0x38, 0x00, 0x00, 0x00, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0x7C, 0x9B, 0x23, 0x78};		
			
		u8 cellUsbdRegisterLdd_symbol_flag[]={0xE9, 0x61, 0x00, 0x78, 0xE8, 0x09, 0x00, 0x00, 0x7D, 0x6B, 0x02, 0x79, 0x38, 0x00, 0x00, 0x00, 0x40, 0xC2, 0x00, 0x20, 0xE9, 0x22, 0xAA, 0xAA, 0x7C, 0x64, 0x1B, 0x78, 0xE8, 0x01, 0x00, 0x90, 0x38, 0x21, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6, 0xE8, 0x69, 0x00, 0x00, 0x4B, 0xFF, 0xAA, 0xAA, 0x4B, 0xAA, 0xAA, 0xAA, 0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xE9, 0x22, 0xAA, 0xAA, 0xF8, 0x01, 0x00, 0x90, 0xE8, 0x09, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x78, 0x38, 0x00, 0x00, 0x00, 0xE9, 0x61, 0x00, 0x78, 0xE8, 0x09, 0x00, 0x00, 0x7D, 0x6B, 0x02, 0x79, 0x38, 0x00, 0x00, 0x00, 0x40, 0xC2, 0x00, 0x20};
		u8 cellUsbdUnregisterLdd_symbol_flag[]={0x7F, 0x07, 0x07, 0xB4, 0x48, 0x00, 0x08, 0x99, 0xE8, 0x81, 0x00, 0x80, 0x7C, 0x7F, 0x1B, 0x78, 0x7F, 0xC3, 0xF3, 0x78, 0x4B, 0xAA, 0xAA, 0xAA, 0x4B, 0xFF, 0xFF, 0x54, 0x4B, 0xAA, 0xAA, 0xAA, 0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xE9, 0x22, 0xAA, 0xAA, 0xF8, 0x01, 0x00, 0x90, 0xE8, 0x09, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x78, 0x38, 0x00, 0x00, 0x00, 0xE9, 0x61, 0x00, 0x78};
		u8 cellUsbdScanStaticDescriptor_symbol_flag[]={0x7C, 0x03, 0x07, 0xB4, 0x40, 0xC2, 0x00, 0x18, 0xE8, 0x01, 0x00, 0xB0, 0xEB, 0xE1, 0x00, 0x98, 0x38, 0x21, 0x00, 0xA0, 0x7C, 0x08, 0x03, 0xA6, 0x4E, 0x80, 0x00, 0x20, 0x4B};
		//u8 cellUsbdOpenPipe_symbol_flag[]={0xF8, 0x21, 0xFF, 0x81, 0x7C, 0x08, 0x02, 0xA6, 0xE9, 0x22, 0x0E, 0x90, 0x7C, 0x85, 0x23, 0x78, 0xF8, 0x01, 0x00, 0x90, 0xE8, 0x09, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x78, 0x38, 0x00, 0x00, 0x00};
		u8 cellUsbdClosePipe_symbol_flag[]={0xE8, 0x01, 0x00, 0x90, 0x7C, 0x64, 0x07, 0xB4, 0x78, 0xC6, 0x06, 0x20, 0x38, 0x21, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6, 0xE8, 0x69, 0x00, 0x00, 0x4B};
		u8 cellUsbdControlTransfer_symbol_flag[]={0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0x2C, 0x24, 0x00, 0x00, 0xF8, 0x01, 0x00, 0xB0, 0xFB, 0xE1, 0x00, 0x98, 0x3C, 0x00, 0x80, 0x11};
		u8 cellUsbdBulkTransfer_symbol_flag[]={0x40, 0xC2, 0x00, 0x1C, 0xE8, 0x01, 0x00, 0xC0, 0xEB, 0x81, 0x00, 0x90, 0xEB, 0xA1, 0x00, 0x98, 0x7C, 0x08, 0x03, 0xA6, 0x38, 0x21, 0x00, 0xB0};
		
		u8 decrypt_func_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7C, 0x1B, 0x78, 0x7C, 0x9D, 0x23, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x4B, 0xFF, 0xFF, 0x95};
		u8 lv1_call_99_wrapper_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7D, 0x1B, 0x78, 0xFB, 0x81, 0x00, 0x70, 0x38, 0x63, 0x00, 0x80, 0x7C, 0x9C, 0x23, 0x78, 0xF8, 0x01, 0x00, 0xA0};
		u8 modules_verification_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0x2B, 0x84, 0x00, 0x36, 0xF8, 0x01, 0x00, 0x80, 0x41, 0x9D, 0x00, 0xFC};
		u8 authenticate_program_segment_symbol_flag[]={0xE9, 0x62, 0xAA, 0xAA, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x51, 0xF8, 0x01, 0x00, 0xC0, 0xE8, 0x62, 0xAA, 0xAA, 0x38, 0x00, 0x00, 0x01};
		
		u8 prx_load_module_symbol_flag[] = { 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0x7C, 0xBC, 0x2B, 0x78, 0x38, 0xA0, 0x00, 0x01, 0xFB, 0xA1, 0x00, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88};
		u8 prx_start_module_symbol_flag[] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFE, 0xF1, 0xFB, 0x21, 0x00, 0xD8, 0xFB, 0x41, 0x00, 0xE0, 0x7C, 0x79, 0x07, 0xB4, 0x7C, 0x9A, 0x23, 0x78, 0xFB, 0x01, 0x00, 0xD0, 0xFB, 0x81, 0x00, 0xF0};
		u8 prx_stop_module_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xC1, 0x00, 0x90, 0x7C, 0x7D, 0x1B, 0x78, 0x7C, 0x9E, 0x23, 0x78, 0xFB, 0x81, 0x00, 0x80, 0xF8, 0x01, 0x00, 0xB0};
		u8 prx_unload_module_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x80, 0xFB, 0xC1, 0x00, 0x90, 0x7C, 0x7C, 0x07, 0xB4, 0x7C, 0x9E, 0x23, 0x78, 0xFB, 0xA1, 0x00, 0x88, 0xFB, 0xE1, 0x00, 0x98};
		u8 prx_get_module_info_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x21, 0x00, 0x78, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xA1, 0x00, 0x98, 0x7C, 0xBB, 0x2B, 0x78};
		u8 prx_get_module_id_by_address_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x9C, 0x23, 0x78, 0x7C, 0x7D, 0x1B, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x4B, 0xFF, 0xFF, 0x8D};
		u8 prx_get_module_id_by_name_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x9C, 0x23, 0x78, 0x7C, 0x7D, 0x1B, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x4B, 0xFF, 0xFF, 0x3D};
		u8 prx_get_module_list_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x00, 0x70, 0xFB, 0x21, 0x00, 0x78, 0xFB, 0x41, 0x00, 0x80, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xA1, 0x00, 0x98, 0x7C, 0xF9, 0x3B, 0x78, 0x7D, 0x18, 0x43, 0x78, 0x7C, 0xDA, 0x33, 0x78, 0x7C, 0x7D, 0x1B, 0x78};
		u8 load_module_by_fd_symbol_flag[]={0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xFF, 0x11, 0xFA, 0xE1, 0x00, 0xA8, 0xFB, 0x01, 0x00, 0xB0, 0xFB, 0x61, 0x00, 0xC8, 0xFA, 0xC1, 0x00, 0xA0, 0xFB, 0x21, 0x00, 0xB8, 0xFB, 0x41, 0x00, 0xC0};
		u8 parse_sprx_symbol_flag[]={0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x90, 0xFB, 0xE1, 0x00, 0xA8, 0x7C, 0x7C, 0x1B, 0x78, 0x7C, 0x9F, 0x23, 0x78, 0x38, 0x60, 0x00, 0x20, 0x38, 0x80, 0x00, 0x00};
		u8 open_prx_object_symbol_flag[]={0xF8, 0x21, 0xFF, 0x91, 0x7C, 0x08, 0x02, 0xA6, 0x78, 0x84, 0x00, 0x20, 0xF8, 0x01, 0x00, 0x80, 0xE8, 0x63, 0x02, 0x08, 0x38, 0xE0, 0x00, 0x23};
		u8 close_prx_object_symbol_flag[]={0x38, 0x60, 0x00, 0x00, 0x7C, 0x08, 0x03, 0xA6, 0x38, 0x21, 0x00, 0x70, 0x4E, 0x80, 0x00, 0x20, 0xE8, 0x63, 0xAA, 0xAA, 0x4B, 0xAA, 0xAA, 0xAA, 0x2C, 0x23, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x81, 0xFB, 0xC1, 0x00, 0x70, 0xFB, 0xE1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0x90};
		u8 lock_prx_mutex_symbol_flag[]={0x7C, 0x60, 0x03, 0x78, 0x7C, 0x00, 0xFE, 0x70, 0x7C, 0x63, 0x00, 0x38, 0xE8, 0x01, 0x00, 0x80, 0x38, 0x21, 0x00, 0x70, 0x7C, 0x63, 0x07, 0xB4, 0x7C, 0x08, 0x03, 0xA6, 0x4E, 0x80, 0x00, 0x20, 0xE9, 0x22};

		u8 extend_kstack_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xF8, 0x01, 0x00, 0xA0, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x7D, 0x1B, 0x78};
		
		u8 get_pseudo_random_number_symbol_flag[] = {0x7C, 0x85, 0x23, 0x78, 0x7C, 0x04, 0x03, 0x78, 0x48, 0x00, 0x04, 0x04, 0x48, 0x00, 0x01, 0xE4, 0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xC1, 0x00, 0x80};
		u8 md5_reset_symbol_flag[]={0x3D, 0x20, 0x67, 0x45, 0x3D, 0x60, 0xEF, 0xCD, 0x3D, 0x40, 0x98, 0xBA, 0x3C, 0x00, 0x10, 0x32, 0x39, 0x00, 0x00, 0x00, 0x61, 0x29, 0x23, 0x01, 0x61, 0x6B, 0xAB, 0x89, 0x61, 0x4A, 0xDC, 0xFE};
		u8 md5_update_symbol_flag[]={0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0x54, 0xAB, 0x18, 0x38, 0xF8, 0x01, 0x00, 0xC0, 0x80, 0x03, 0x00, 0x10, 0xFB, 0xC1, 0x00, 0xA0, 0x7D, 0x20, 0x5A, 0x14, 0x7C, 0x7E, 0x1B, 0x78};
		u8 md5_final_symbol_flag[]={0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x98, 0x7C, 0x9F, 0x23, 0x78, 0xFB, 0xC1, 0x00, 0x90, 0x3B, 0xC1, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x88, 0x38, 0xA0, 0x00, 0x08};
		u8 ss_get_open_psid_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0x70, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x9C, 0x23, 0x78, 0x7C, 0x7D, 0x1B, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x48, 0x00, 0x00, 0xF5};
		u8 update_mgr_read_eeprom_symbol_flag[]={0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0xC8, 0x3B, 0xE1, 0x00, 0x70, 0xFB, 0x81, 0x00, 0xB0, 0xFB, 0xA1, 0x00, 0xB8, 0x7C, 0x7C, 0x1B, 0x78, 0x7C, 0xBD, 0x2B, 0x78};
		u8 update_mgr_write_eeprom_symbol_flag[]={0xF8, 0x21, 0xFF, 0x21, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0xD8, 0x3B, 0xE1, 0x00, 0x70, 0xFB, 0x61, 0x00, 0xB8, 0xFB, 0xA1, 0x00, 0xC8, 0x7C, 0x7B, 0x1B, 0x78, 0x7C, 0xBD, 0x2B, 0x78};	

		u8 SHA1_init_symbol_flag[]={0x3C, 0x00, 0x67, 0x45, 0x3D, 0x80, 0xEF, 0xCD, 0x3C, 0xC0, 0x98, 0xBA, 0x3C, 0xA0, 0x10, 0x32, 0x3C, 0x80, 0xC3, 0xD2, 0x60, 0x09, 0x23, 0x01, 0x61, 0x8B, 0xAB, 0x89, 0x91, 0x23, 0x00, 0x00};
		u8 SHA1_update_symbol_flag[]={0x2F, 0x85, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0xFB, 0xA1, 0x00, 0x78, 0x7C, 0x9D, 0x23, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0x7C, 0x7E, 0x1B, 0x78, 0xFB, 0xE1, 0x00, 0x88};
		u8 SHA1_final_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x00, 0xA0, 0x81, 0x44, 0x00, 0x1C, 0x2B, 0x8A, 0x00, 0x3F, 0xFB, 0xC1, 0x00, 0x80, 0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x7E, 0x1B, 0x78};
		u8 aescbccfb_dec_symbol_flag[]={0x7D, 0x80, 0x00, 0x26, 0x2E, 0x05, 0x00, 0x00, 0xF8, 0x21, 0xFD, 0xC1, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x21, 0x02, 0x08, 0x7C, 0xB9, 0x2B, 0x78, 0xFB, 0xA1, 0x02, 0x28, 0x7D, 0x1D, 0x43, 0x78};
		u8 aescbccfb_enc_symbol_flag[]={0x7D, 0x80, 0x00, 0x26, 0x2E, 0x05, 0x00, 0x00, 0xF8, 0x21, 0xFE, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x01, 0x88, 0x7C, 0x7B, 0x1B, 0x78, 0xFB, 0xA1, 0x01, 0x98, 0x38, 0x60, 0xFF, 0xFE};
		
		u8 ss_params_get_update_status_symbol_flag[]={0x3C, 0xA0, 0x70, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0x3C, 0xC0, 0x75, 0x70, 0x3C, 0xE0, 0x73, 0x74, 0x60, 0xA5, 0x72, 0x61, 0x60, 0xC6, 0x64, 0x61, 0x60, 0xE7, 0x61, 0x74, 0x2C, 0x23, 0x00, 0x00};

		u8 syscall_call_offset_flag[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x38, 0x21, 0x00, 0x70, 0xF8, 0x21, 0xFF, 0xB1, 0xF8, 0x61, 0x00, 0x08, 0xF8, 0x81, 0x00, 0x10, 0xF8, 0xA1, 0x00, 0x18, 0xF8, 0xC1, 0x00, 0x20, 0xF8, 0xE1, 0x00, 0x28};
		
		u8 read_bdvd0_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x01, 0x10, 0x7C, 0x78, 0x1B, 0x78, 0xF8, 0x01, 0x01, 0x60, 0xF9, 0xC1, 0x00, 0xC0, 0xFB, 0xC1, 0x01, 0x40, 0x7C, 0x8E, 0x23, 0x78};
		u8 read_bdvd1_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0xB0, 0xF8, 0x01, 0x00, 0xE0, 0xEB, 0x83, 0x00, 0x20, 0x7C, 0xA0, 0x2B, 0x78, 0xFA, 0xE1, 0x00, 0x88, 0x2F, 0xBC, 0x00, 0x00};
		u8 read_bdvd2_symbol_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0xA8, 0xF8, 0x01, 0x00, 0xC0, 0x7C, 0x7F, 0x1B, 0x78, 0xE8, 0x63, 0x00, 0x90, 0xFB, 0x61, 0x00, 0x88, 0xFB, 0x81, 0x00, 0x90};
		
		u8 storage_internal_get_device_object_symbol_flag[] = {0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xA1, 0x00, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0xE8, 0x03, 0x00, 0x00, 0x7C, 0xBD, 0x2B, 0x78, 0xFB, 0xC1, 0x00, 0x80, 0x2F, 0xA0, 0x00, 0x00, 0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x9E, 0x23, 0x78, 0x40, 0x9E, 0x00, 0x2C, 0x3C, 0x60, 0x80, 0x01, 0x60, 0x63, 0x00, 0x05, 0xE8, 0x01, 0x00, 0xA0, 0x7C, 0x63, 0x07, 0xB4, 0xEB, 0xA1, 0x00, 0x78, 0xEB, 0xC1, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xE1, 0x00, 0x88, 0x38, 0x21, 0x00, 0x90, 0x4E, 0x80, 0x00, 0x20, 0x78, 0x89, 0x00, 0x20, 0x81, 0x63, 0x00, 0x40, 0xE9, 0x43, 0x00, 0x38};
		
		u8 hid_mgr_read_usb_symbol_flag[]={0xE9, 0x62, 0xAA, 0xAA, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x91, 0xF8, 0x01, 0x00, 0x80, 0x2F, 0x24, 0x00, 0x00, 0x38, 0x00, 0xFF, 0xEB, 0x81, 0x2B, 0x00, 0x00, 0x2F, 0x89, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x18, 0x7C, 0x03, 0x07, 0xB4, 0xE8, 0x01, 0x00, 0x80, 0x38, 0x21, 0x00, 0x70};
		u8 hid_mgr_read_bt_symbol_flag[]={0x7C, 0x08, 0x03, 0xA6, 0x38, 0x21, 0x00, 0xA0, 0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFF, 0x51, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x41, 0x00, 0x80};

		u8 bt_set_controller_info_internal_symbol_flag[]={0xF8, 0x21, 0xFF, 0x41, 0x7C, 0x08, 0x02, 0xA6, 0x2F, 0x85, 0x05, 0x4C, 0xF8, 0x01, 0x00, 0xD0, 0x54, 0xC0, 0x04, 0x3E, 0xFB, 0x41, 0x00, 0x90, 0xFB, 0xA1, 0x00, 0xA8, 0xFB, 0xC1, 0x00, 0xB0};

		///u8 device_event_port_send_call_flag[]={0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x90, 0xF8, 0x01, 0x00, 0xB0, 0xFB, 0xE1, 0x00, 0x98, 0x7C, 0x7E, 0x1B, 0x78, 0xE8, 0x63, 0x00, 0xD8, 0x7C, 0x9F, 0x23, 0x78};

		u8 ss_pid_call_1_flag[]={0x90, 0x61, 0x00, 0x70, 0x38, 0x81, 0x00, 0x78, 0x38, 0xA1, 0x00, 0x80, 0x38, 0xC1, 0x00, 0xA0, 0x38, 0x61, 0x00, 0x70};
		
		u8 process_map_caller_call_flag[] = {0x2F, 0x83, 0x00, 0x00, 0x7C, 0x7D, 0x1B, 0x78, 0x41, 0x9E, 0xFF, 0x1C, 0x80, 0x7B, 0x00, 0x00};
		
		u8 read_module_header_call_flag[]={0x2F, 0x83, 0x00, 0x00, 0x7C, 0x63, 0x07, 0xB4, 0x40, 0x9E, 0x00, 0x08, 0xE8, 0x61, 0x00, 0x70, 0xE8, 0x01, 0x00, 0x90, 0x38, 0x21, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6, 0x4E, 0x80, 0x00, 0x20};
		u8 read_module_body_call_flag[]={0x2F, 0x83, 0x00, 0x00, 0x7C, 0x7F, 0x1B, 0x78, 0x40, 0xDE, 0x01, 0x3C, 0xE8, 0x01, 0x00, 0x88, 0x7F, 0xBE, 0x00, 0x00, 0x40, 0xDE, 0x01, 0x60, 0xFB, 0xDD, 0x00, 0x10, 0xE8, 0x1C, 0x00, 0x18};
		u8 load_module_by_fd_call1_flag[]={0x4B, 0xFF, 0xF7, 0x95, 0x80, 0x1B, 0x00, 0x0C, 0x7C, 0x7D, 0x1B, 0x78, 0xE8, 0x7B, 0x00, 0x10, 0x2F, 0x80, 0x00, 0x00, 0x40, 0x9D, 0xFF, 0xBC, 0x3B, 0xE3, 0x00, 0x18, 0x3B, 0xC0, 0x00, 0x00};
		
		u8 shutdown_copy_params_call_flag[] = {0x2F, 0x83, 0x00, 0x00, 0x40, 0x9E, 0x00, 0x5C, 0x7F, 0xC6, 0xF3, 0x78, 0x7F, 0xA3, 0xEB, 0x78, 0x38, 0x80, 0x00, 0x01, 0x7F, 0x65, 0xDB, 0x78};		
		
		u8 fsloop_open_call_flag[] = {0x7C, 0x63, 0x07, 0xB4, 0x4B, 0xFF, 0xFF, 0xC0, 0x80, 0x63, 0x00, 0x08, 0x80, 0xAA, 0x00, 0x18, 0x7C, 0x63, 0x07, 0xB4, 0xE8, 0xCA, 0x00, 0x20, 0x7C, 0xA5, 0x07, 0xB4};
		u8 fsloop_close_call_flag[] = {0x7C, 0x63, 0x07, 0xB4, 0x4B, 0xFF, 0xFF, 0x70, 0x80, 0x63, 0x00, 0x08, 0xE8, 0xCA, 0x00, 0x20, 0x7C, 0x63, 0x07, 0xB4, 0xE8, 0x8A, 0x00, 0x10, 0xE8, 0xAA, 0x00, 0x18};
		u8 fsloop_read_call_flag[] = {0x7C, 0x63, 0x07, 0xB4, 0x4B, 0xFF, 0xFF, 0x30, 0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x00, 0x90, 0xFB, 0x61, 0x00, 0xA8, 0xFB, 0xA1, 0x00, 0xB8};

		/* Patches */
		u8 shutdown_patch_offset_flag[] = {0x41, 0x82, 0xFE, 0xFC, 0x7F, 0x83, 0xE3, 0x78, 0x7F, 0x64, 0xDB, 0x78, 0x7F, 0xC5, 0xF3, 0x78};
		
		u8 module_sdk_version_patch_offset_flag[]={0x38, 0x60, 0x00, 0x00, 0x7C, 0x63, 0x07, 0xB4, 0x4E, 0x80, 0x00, 0x20, 0x80, 0x04, 0x00, 0x04, 0x7F, 0x80, 0x48, 0x00, 0x40, 0x9E, 0xFF, 0xEC, 0x80, 0x04, 0x00, 0x08, 0x2B, 0x80, 0x00, 0x02};
		u8 module_add_parameter_to_parse_sprxpatch_offset_flag[]={0x90, 0x03, 0x01, 0x98, 0xFB, 0x43, 0x01, 0xA8, 0xFB, 0x43, 0x01, 0xA0, 0x93, 0x43, 0x01, 0xB8, 0xFB, 0x43, 0x01, 0xC8, 0xFB, 0x43, 0x01, 0xC0, 0x4B, 0xFF, 0xAA, 0xAA, 0x2F, 0x83, 0x00, 0x00, 0x7C, 0x7E, 0x1B, 0x78, 0x41, 0x9E, 0x00, 0x0C, 0x41, 0x9C, 0x01, 0xCC, 0x3B, 0xA0, 0x00, 0x00};
		
		u8 user_thread_prio_patch_flag[] = {0x3F, 0xE0, 0x80, 0x01, 0x2B, 0x80, 0x0E, 0x7F, 0x80, 0x01, 0x00, 0x94, 0x63, 0xFF, 0x00, 0x02}; // +0x10
		u8 user_thread_prio_patch2_flag[]={0x7B, 0x80, 0x07, 0xA0, 0x3F, 0xE0, 0x80, 0x01, 0x2F, 0xA0, 0x00, 0x03, 0x63, 0xFF, 0x00, 0x09, 0x41, 0x9E, 0xFF, 0x64, 0xFB, 0x41, 0x00, 0xB8, 0x7D, 0x30, 0x42, 0xA6, 0xE8, 0x69, 0x00, 0x48};
		
		///u8 lic_patch_flag[]={0x38, 0x60, 0x00, 0x01, 0x2F, 0x83, 0x00, 0x00, 0x3B, 0xFC, 0x00, 0x6C, 0x41, 0x9E, 0x00, 0x60, 0x38, 0x00, 0x00, 0x02, 0x3B, 0xE0, 0x00, 0x00, 0x90, 0x1C, 0x00, 0x6C, 0x4B, 0xFF, 0xFF, 0x38};
		///u8 ode_patch_flag[]={0x38, 0x60, 0x00, 0x00, 0xF8, 0x69, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20, 0x3C, 0x80, 0x10, 0x50, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x71, 0x78, 0x84, 0x07, 0xC6, 0xFB, 0xE1, 0x00, 0x88};

		/* Rtoc entries */
		u8 io_rtoc_entry_1_flag[]={0x60, 0x63, 0x00, 0x02, 0x54, 0x00, 0x07, 0xFE, 0x2F, 0x24, 0xFF, 0xFF, 0x2F, 0x80, 0x00, 0x00};
		u8 io_sub_rtoc_entry_1_flag[]={0xE9, 0x7E, 0x81, 0x68, 0xEB, 0x9E, 0x81, 0x40, 0xEB, 0xBE, 0x81, 0x70};
		u8 decrypt_rtoc_entry_2_flag[]={0x4B, 0xFF, 0xFF, 0xFF, 0x39, 0x20, 0x00, 0x00, 0x4B, 0xFF, 0xFF, 0xCC, 0x2C, 0x24, 0x00, 0x00};
		//u8 decrypter_data_entry_flag[]={0};
		
		u8 storage_rtoc_entry_1_flag[] = {0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x51, 0xF8, 0x01, 0x00, 0xC0, 0xFB, 0xE1, 0x00, 0xA8, 0x7C, 0x9F, 0x23};
		u8 device_event_flag[] = {0x78, 0x05, 0x06, 0x20, 0xE8, 0xCA, 0x00, 0x38, 0x7D, 0x05, 0x2B, 0x78, 0xE9, 0x2B, 0x00, 0x00, 0xE8, 0x69, 0x00, 0x40};
		
		u8 time_rtoc_entry_1_flag[]={0x3D, 0x40, 0x3B, 0x9A, 0xE8, 0xE2, 0xAA, 0xAA, 0x7C, 0x64, 0x1B, 0x78};
		u8 time_rtoc_entry_2_flag[]={0x3D, 0x20, 0x11, 0x2E, 0xE9, 0x02, 0xAA, 0xAA, 0x38, 0xC0, 0x00, 0x00};
		
		u8 thread_rtoc_entry_1_flag[]={0x80, 0x09, 0x00, 0x00, 0x90, 0x01, 0x00, 0x70, 0x4B};
		
		u8 process_rtoc_entry_1_flag[]={0x3F, 0xC0, 0x80, 0x01, 0x63, 0xDE, 0x00, 0x05, 0xE8, 0x7D, 0x00, 0x00};
		
		u8 bt_rtoc_entry_1_flag[]={0x38, 0xA0, 0x00, 0x00, 0x48, 0x00, 0xAA, 0xAA, 0x7F, 0xA4, 0xEB, 0x78, 0x7C, 0x60, 0x1B, 0x78, 0x38, 0xA0, 0x01, 0x00, 0x2F, 0x80, 0x00, 0x00};
		
		u8 permissions_func_symbol_flag[]={0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFF, 0x21, 0xFB, 0xA1, 0x00, 0xC8, 0xFB, 0xC1, 0x00, 0xD0, 0xFB, 0xE1, 0x00, 0xD8, 0xE8, 0xE9, 0x00, 0x18, 0x7C, 0x9F, 0x23, 0x78};
		u8 permissions_exception1_flag[]={0xFB, 0xA1, 0x00, 0xF8, 0xFB, 0xE1, 0x01, 0x08, 0x90, 0x01, 0x00, 0x90, 0xF9, 0x21, 0x00, 0x98, 0x7C, 0xF8, 0x3B, 0x78, 0x7D, 0x1A, 0x43, 0x78, 0x7D, 0x5E, 0x53, 0x78, 0xF9, 0x21, 0x00, 0xA0};
		u8 permissions_exception2_flag[]={0x4B, 0xAA, 0xAA, 0xAA, 0xE8, 0x01, 0x00, 0xA0, 0x78, 0x63, 0x06, 0x20, 0x7C, 0x08, 0x03, 0xA6, 0x38, 0x21, 0x00, 0x90, 0x38, 0x63, 0xFF, 0xFF, 0x78, 0x63, 0x0F, 0xE0, 0x7C, 0x63, 0x00, 0x34, 0x54, 0x63, 0xD9, 0x7E};
		u8 permissions_exception3_flag[]={0x38, 0xC1, 0x00, 0xA8, 0x91, 0x21, 0x00, 0x80, 0xF8, 0x01, 0x00, 0xA8, 0xF8, 0x01, 0x00, 0x98, 0x4B, 0xAA, 0xAA, 0xAA, 0x54, 0x63, 0x06, 0x3E, 0x2F, 0x83, 0x00, 0x00, 0x41, 0x9E, 0x01, 0xF8};

		//u8 patch_data1_offset_flag[]={0}; // offset found after the first idps on LV2 dump
		u8 patch_func2_flag[] = {0x41, 0x9A, 0xFF, 0xAC, 0x3D, 0x20, 0x80, 0x01, 0x61, 0x29, 0x00, 0x09, 0x4B, 0xFF, 0xFF, 0xA0, 0xF8, 0x21, 0xFF, 0x61, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0x90, 0x7C, 0x9E, 0x23, 0x78};
		///u8 patch_func2_offset_flag[]={0};
		///u8 patch_func8_flag={0};
		u8 patch_func8_offset1_flag[]={0x98, 0x01, 0x00, 0x71, 0x4B, 0xFF, 0xAA, 0xAA, 0x2C, 0x23, 0x00, 0x00, 0x40, 0x82, 0x00, 0x38, 0x3F, 0xE0, 0x80, 0x01, 0x63, 0xFF, 0x00, 0x02, 0xE8, 0x01, 0x00, 0xC0, 0xAA, 0xAA, 0xAA, 0xAA, 0xEB, 0x41, 0x00, 0x80, 0xEB, 0x61, 0x00, 0x88, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0x81, 0x00, 0x90, 0xEB, 0xA1, 0x00, 0x98, 0xEB, 0xC1, 0x00, 0xA0, 0xEB, 0xE1, 0x00, 0xA8, 0x38, 0x21, 0x00, 0xB0, 0x4E, 0x80, 0x00, 0x20, 0x38, 0x1E, 0x00, 0x24, 0x7F, 0xA0, 0x18, 0x00, 0x40, 0x9E, 0xFF, 0xC4, 0x38, 0x61, 0x00, 0x70};
		u8 patch_func8_offset2_flag[]={0x3F, 0xE0, 0x80, 0x01, 0x63, 0xFF, 0x00, 0x0F, 0x4B, 0xFF, 0xFF, 0x44, 0x2F, 0x9B, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x28, 0x88, 0x1C, 0x00, 0x60, 0x2F, 0x80, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x1C};
		///u8 patch_func9_flag={0};
		u8 patch_func9_offset_flag[]={0x54, 0x63, 0x06, 0x3E, 0x2F, 0x83, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x38, 0x61, 0x00, 0x70, 0x4B, 0xFF, 0xAA, 0xAA, 0x2F, 0x83, 0x00, 0x00, 0x7C, 0x64, 0x1B, 0x78};
		u8 mem_base2_flag[]={0x7F, 0xA0, 0x50, 0x00, 0x7F, 0x29, 0x58, 0x00, 0x40, 0x9E, 0xFF, 0xDC, 0x7C, 0xE0, 0x40, 0x38, 0x40, 0x9A, 0xFF, 0xD4, 0x7F, 0xA0, 0x38, 0x00, 0x40, 0x9E, 0xFF, 0xCC, 0x48, 0xAA, 0xAA, 0xAA, 0x78, 0x63, 0x06, 0x20, 0x7C, 0x63, 0x00, 0xD0, 0x78, 0x66, 0x0F, 0xE0};
		
		u8 thread_info_symbol_flag[]={0x5F, 0x53, 0x59, 0x53, 0x54, 0x45, 0x4D, 0x20, 0x49, 0x44, 0x4C, 0x45, 0x20, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

		u8 mmapper_flags_temp_patch_flag[]={0x3B, 0x80, 0x40, 0x00, 0x48, 0x00, 0xAA, 0xAA, 0x57, 0xE0, 0x03, 0x5A, 0x2F, 0xA0, 0x00, 0x00, 0x7C, 0x69, 0x1B, 0x78, 0x40, 0x9E, 0x00, 0x08, 0x57, 0xFC, 0xE4, 0x20, 0x2F, 0x89, 0x00, 0x10};

		u8 ECDSA_1_flag[]={0xEB, 0x81, 0x00, 0x80, 0xEB, 0xA1, 0x00, 0x88, 0x7C, 0x08, 0x03, 0xA6, 0xEB, 0xC1, 0x00, 0x90, 0xEB, 0xE1, 0x00, 0x98, 0x38, 0x21, 0x00, 0xA0, 0x4E, 0x80, 0x00, 0x20, 0x80, 0x61, 0x00, 0x70};
		u8 ECDSA_2_flag[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xFB, 0x21, 0x01, 0x68, 0x3B, 0x21, 0x00, 0x70, 0xFB, 0x81, 0x01, 0x80, 0x7C, 0x7C, 0x1B, 0x78, 0xFB, 0x01, 0x01, 0x60, 0x7F, 0x23, 0xCB, 0x78, 0xFB, 0x61, 0x01, 0x78, 0x7C, 0x98, 0x23, 0x78};
		
		u8 fix_8001003E_flag[]={0x4B, 0xFF, 0xAA, 0xAA, 0x83, 0xBC, 0x00, 0x78, 0x2F, 0x9D, 0x00, 0x00, 0x40, 0x9D, 0xFF, 0xC0};
		u8 PATCH_JUMP_flag[]={0x98, 0xC1, 0x00, 0x7A, 0x98, 0xA1, 0x00, 0x7B, 0x98, 0x01, 0x00, 0x7C, 0x41, 0x9E, 0x00, 0x70, 0x2F, 0x84, 0x00, 0x03, 0x41, 0x9E, 0x00, 0x30};
		
		//u8 ECDSA_FLAG_flag={0};
		//u8 sysmem_obj_flag={0};
		u8 qa_eeprom_offset_flag[]={0x1B, 0x78, 0x40, 0x9E, 0x00, 0x44, 0xE9, 0x21, 0x00, 0x78, 0x3F, 0xE0, 0x80, 0x01, 0x7B, 0x64, 0x00, 0x20, 0x7F, 0xA5, 0xEB, 0x78, 0x63, 0xFF, 0x00, 0x02, 0x80, 0x09, 0x00, 0x88, 0x54, 0x00};
		
		u8 sm_get_temperature_symbol_flag[]={0xF8, 0x21, 0xFF, 0x41, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x61, 0x00, 0x98, 0x7C, 0xDB, 0x33, 0x78, 0xFB, 0x41, 0x00, 0x90, 0xFB, 0xA1, 0x00, 0xA8, 0x7C, 0xBA, 0x2B, 0x78, 0x7C, 0x9D, 0x23, 0x78};
		u8 sm_get_fan_policy_symbol_flag[]={0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x01, 0x00, 0x90, 0xFB, 0x21, 0x00, 0x98, 0xFB, 0x41, 0x00, 0xA0, 0xFB, 0xA1, 0x00, 0xB8, 0x7C, 0xBA, 0x2B, 0x78, 0x7C, 0x9D, 0x23, 0x78};
		u8 sm_set_fan_policy_symbol_flag[]={0xF8, 0x21, 0xFF, 0x71, 0x7C, 0x08, 0x02, 0xA6, 0x39, 0x20, 0x00, 0x08, 0xF8, 0x01, 0x00, 0xA0, 0x38, 0x00, 0x00, 0x10, 0x98, 0x81, 0x00, 0x81, 0x98, 0xA1, 0x00, 0x82, 0x39, 0x60, 0x00, 0x01};
	
		u8 sm_get_temperature_patch_flag[]={0x7C, 0x7D, 0x1B, 0x78, 0xEB, 0xC1, 0x00, 0xA0, 0xEB, 0xE1, 0x00, 0xA8, 0x7C, 0x08, 0x03, 0xA6, 0x7F, 0xA3, 0x07, 0xB4, 0xEB, 0xA1, 0x00, 0x98, 0x38, 0x21, 0x00, 0xB0, 0x4E, 0x80, 0x00, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0x2F, 0x83, 0x00, 0x00};
		u8 sm_get_fan_policy_patch_flag[]={0x7C, 0xB9, 0x2B, 0x78, 0x7C, 0xD8, 0x33, 0x78, 0x7C, 0xF7, 0x3B, 0x78, 0x7C, 0x7F, 0x1B, 0x78};
		u8 sm_set_fan_policy_patch_flag[]={0xFB, 0xE1, 0x00, 0x88, 0x7C, 0x9E, 0x23, 0x78, 0x7C, 0x7F, 0x1B, 0x78, 0xF8, 0x01, 0x00, 0xA0, 0x48, 0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7B, 0xE4, 0x06, 0x20, 0x2F, 0x83, 0x00, 0x00};
		
		u8 update_mgr_if_get_token_symbol_flag[]={0x7C, 0x08, 0x03, 0xA6, 0x7C, 0x63, 0x07, 0xB4, 0x38, 0x21, 0x00, 0xB0, 0x4E, 0x80, 0x00, 0x20, 0xF8, 0x21, 0xFF, 0x01, 0x7C, 0x08, 0x02, 0xA6};
		u8 get_path_by_fd_symbol_flag[]={0xF8, 0x21, 0xFF, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0x81, 0x00, 0xB0, 0xFB, 0xC1, 0x00, 0xC0, 0xF8, 0x01, 0x00, 0xE0};
		
		/* LV2 POKE	*/
		//u8 hash_checked_area_flag={0};
		
// *************
//	LV2
// *************

		sprintf(dump, "LV2/%s", ent->d_name);
		
		char *memLV2 = (char *) LoadFile(dump,&size);	
		if(memLV2 == NULL) continue;
		
		memcpy(&TOC, &memLV2[0x3000], 8);
		TOC = reverse64(TOC);
		
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
					fix_8001003D = n - 0x8;
				}
				if(!memcmp((char *) &memLV2[n], (char *) flag_offset_2_fix, 0x10)) {
					OFFSET_2_FIX = n + 0x20;
					fix_80010009 = n + 0x20;
				}
				if(compare(0xFF, (char *) &memLV2[n], (char *) flag_offset_fix_lic, sizeof(flag_offset_fix_lic))) {
					OFFSET_FIX_LIC = n - 0x4;
					lic_patch = n - 0x4;
					memcpy(&lic_patch_restore, &memLV2[lic_patch], 4);
					lic_patch_restore = SWAP32(lic_patch_restore);
					if(lic_patch_restore == 0x38600001) {
						if(ent->d_name[3] == 'C') {
							lic_patch_restore = 0x48240EED;
						} else
						//if(ent->d_name[3] == 'D') 
						{
							lic_patch_restore = 0x482584B5;
						}
					}
				}
			}							  
			if(0x200000 < n && n <0x400000) {
				if(!memcmp((char *) &memLV2[n], (char *) flag_offset_fix_2B17, 0x20)) {
					OFFSET_FIX_2B17 = n - 0x8;
					ode_patch = n - 0x8;
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
			
			// if(compare(0xFF, (char *) &memLV2[n], (char *) ufs_sb_addr_flag, sizeof(ufs_sb_addr_flag))) {
				// UFS_SB_ADDR = n - 0x55C;
			// }
			if(compare(0xFF, (char *) &memLV2[n], (char *) htab_patch1_flag, sizeof(htab_patch1_flag))) {
				HTAB_PATCH1 = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) htab_patch2_flag, sizeof(htab_patch2_flag))) {
				HTAB_PATCH2 = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) htab_patch3_flag, sizeof(htab_patch3_flag))) {
				HTAB_PATCH3 = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) flag_lpar, sizeof(flag_lpar))) {
				LPAR = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellUsbdBulkTransfer_symbol_flag, sizeof(cellUsbdBulkTransfer_symbol_flag))) {
				cellUsbdBulkTransfer_symbol = n+0x20;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellUsbdControlTransfer_symbol_flag, sizeof(cellUsbdControlTransfer_symbol_flag))) {
				cellUsbdControlTransfer_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellUsbdClosePipe_symbol_flag, sizeof(cellUsbdClosePipe_symbol_flag))) {
				cellUsbdClosePipe_symbol = n+0x20;
				cellUsbdOpenPipe_symbol = n+0x70;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellUsbdScanStaticDescriptor_symbol_flag, sizeof(cellUsbdScanStaticDescriptor_symbol_flag))) {
				cellUsbdScanStaticDescriptor_symbol = n+0x20;
			}
			if(!cellUsbdRegisterLdd_symbol)
			if(compare(0xAA, (char *) &memLV2[n], (char *) cellUsbdRegisterLdd_symbol_flag, sizeof(cellUsbdRegisterLdd_symbol_flag))) {
				cellUsbdRegisterLdd_symbol = n + 0x34;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) cellUsbdUnregisterLdd_symbol_flag, sizeof(cellUsbdUnregisterLdd_symbol_flag))) {
				cellUsbdUnregisterLdd_symbol = n + 0x20;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) create_kernel_object_symbol_flag, sizeof(create_kernel_object_symbol_flag))) {
				create_kernel_object_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) destroy_kernel_object_symbol_flag, sizeof(destroy_kernel_object_symbol_flag))) {
				destroy_kernel_object_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) destroy_shared_kernel_object_symbol_flag, sizeof(destroy_shared_kernel_object_symbol_flag))) {
				destroy_shared_kernel_object_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) open_shared_kernel_object_symbol_flag, sizeof(open_shared_kernel_object_symbol_flag))) {
				open_shared_kernel_object_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) close_kernel_object_handle_symbol_flag, sizeof(close_kernel_object_handle_symbol_flag))) {
				close_kernel_object_handle_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) open_kernel_object_symbol_flag, sizeof(open_kernel_object_symbol_flag))) {
				open_kernel_object_symbol = n;
			}		
			if(compare(-1, (char *) &memLV2[n], (char *) alloc_symbol_flag, sizeof(alloc_symbol_flag))) {
				alloc_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) dealloc_symbol_flag, sizeof(dealloc_symbol_flag))) {
				dealloc_symbol = n - 4;
			}		
			if(compare(-1, (char *) &memLV2[n], (char *) copy_to_user_symbol_flag, sizeof(copy_to_user_symbol_flag))) {
				copy_to_user_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) copy_from_user_symbol_flag, sizeof(copy_from_user_symbol_flag))) {
				copy_from_user_symbol = n;
			}		
			if(compare(-1, (char *) &memLV2[n], (char *) copy_to_process_symbol_flag, sizeof(copy_to_process_symbol_flag))) {
				copy_to_process_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) copy_from_process_symbol_flag, sizeof(copy_from_process_symbol_flag))) {
				copy_from_process_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) process_read_memory_symbol_flag, sizeof(process_read_memory_symbol_flag))) {
				process_read_memory_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) process_write_memory_symbol_flag, sizeof(process_write_memory_symbol_flag))) {
				process_write_memory_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) page_allocate_symbol_flag, sizeof(page_allocate_symbol_flag))) {
				page_allocate_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) page_free_symbol_flag, sizeof(page_free_symbol_flag))) {
				page_free_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) page_export_to_proc_symbol_flag, sizeof(page_export_to_proc_symbol_flag))) {
				page_export_to_proc_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) page_unexport_from_proc_symbol_flag, sizeof(page_unexport_from_proc_symbol_flag))) {
				page_unexport_from_proc_symbol = n - 8;
			}			
			if(compare(-1, (char *) &memLV2[n], (char *) kernel_ea_to_lpar_addr_symbol_flag, sizeof(kernel_ea_to_lpar_addr_symbol_flag))) {
				kernel_ea_to_lpar_addr_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) process_ea_to_lpar_addr_ex_symbol_flag, sizeof(process_ea_to_lpar_addr_ex_symbol_flag))) {
				process_ea_to_lpar_addr_ex_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) set_pte_symbol_flag, sizeof(set_pte_symbol_flag))) {
				set_pte_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) map_process_memory_symbol_flag, sizeof(map_process_memory_symbol_flag))) {
				map_process_memory_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) panic_symbol_flag, sizeof(panic_symbol_flag))) {
				panic_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) memcpy_symbol_flag, sizeof(memcpy_symbol_flag))) {
				memcpy_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) memset_symbol_flag, sizeof(memset_symbol_flag))) {
				memset_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) memcmp_symbol_flag, sizeof(memcmp_symbol_flag))) {
				memcmp_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) memchr_symbol_flag, sizeof(memchr_symbol_flag))) {
				memchr_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) printf_symbol_flag, sizeof(printf_symbol_flag))) {
				printf_symbol = n - 0x10;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) printfnull_symbol_flag, sizeof(printfnull_symbol_flag))) {
				printfnull_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) sprintf_symbol_flag, sizeof(sprintf_symbol_flag))) {
				sprintf_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) snprintf_symbol_flag, sizeof(snprintf_symbol_flag))) {
				snprintf_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) strcpy_symbol_flag, sizeof(strcpy_symbol_flag))) {
				strcpy_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) strncpy_symbol_flag, sizeof(strncpy_symbol_flag))) {
				strncpy_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) strlen_symbol_flag, sizeof(strlen_symbol_flag))) {
				strlen_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) strcat_symbol_flag, sizeof(strcat_symbol_flag))) {
				strcat_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) strcmp_symbol_flag, sizeof(strcmp_symbol_flag))) {
				strcmp_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) strncmp_symbol_flag, sizeof(strncmp_symbol_flag))) {
				strncmp_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) strchr_symbol_flag, sizeof(strchr_symbol_flag))) {
				strchr_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) strrchr_symbol_flag, sizeof(strrchr_symbol_flag))) {
				strrchr_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) spin_lock_irqsave_ex_symbol_flag, sizeof(spin_lock_irqsave_ex_symbol_flag))) {
				spin_lock_irqsave_ex_symbol = n + 0x2C;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) spin_unlock_irqrestore_ex_symbol_flag, sizeof(spin_unlock_irqrestore_ex_symbol_flag))) {
				spin_unlock_irqrestore_ex_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) load_process_symbol_flag, sizeof(load_process_symbol_flag))) {
				load_process_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) ppu_thread_create_symbol_flag, sizeof(ppu_thread_create_symbol_flag))) {
				ppu_thread_create_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) ppu_thread_exit_symbol_flag, sizeof(ppu_thread_exit_symbol_flag))) {
				ppu_thread_exit_symbol = n - 0x18;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) ppu_thread_join_symbol_flag, sizeof(ppu_thread_join_symbol_flag))) {
				ppu_thread_join_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) ppu_thread_delay_symbol_flag, sizeof(ppu_thread_delay_symbol_flag))) {
				ppu_thread_delay_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) create_user_thread2_symbol_flag, sizeof(create_user_thread2_symbol_flag))) {
				create_user_thread2_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) start_thread_symbol_flag, sizeof(start_thread_symbol_flag))) {
				start_thread_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) run_thread_symbol_flag, sizeof(run_thread_symbol_flag))) {
				run_thread_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) self_threading_symbol_flag, sizeof(self_threading_symbol_flag))) {
				self_threading_symbol = n + 0x10;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) register_thread_symbol_flag, sizeof(register_thread_symbol_flag))) {
				register_thread_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) allocate_user_stack_symbol_flag, sizeof(allocate_user_stack_symbol_flag))) {
				allocate_user_stack_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) mutex_create_symbol_flag, sizeof(mutex_create_symbol_flag))) {
				mutex_create_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) mutex_destroy_symbol_flag, sizeof(mutex_destroy_symbol_flag))) {
				mutex_destroy_symbol = n - 0x18;
				mutex_lock_symbol = n - 0x20;
				mutex_trylock_symbol = n - 0x24;
				mutex_unlock_symbol = n - 0x28;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) event_port_create_symbol_flag, sizeof(event_port_create_symbol_flag))) {
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
			if(compare(-1, (char *) &memLV2[n], (char *) event_queue_create_symbol_flag, sizeof(event_queue_create_symbol_flag))) {
				event_queue_create_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) event_queue_destroy_symbol_flag, sizeof(event_queue_destroy_symbol_flag))) {
				event_queue_destroy_symbol = n + 0x18;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) event_queue_receive_symbol_flag, sizeof(event_queue_receive_symbol_flag))) {
				event_queue_receive_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsOpen_symbol_flag, sizeof(cellFsOpen_symbol_flag))) {
				cellFsOpen_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsClose_symbol_flag, sizeof(cellFsClose_symbol_flag))) {
				cellFsClose_symbol = n+4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsRead_symbol_flag, sizeof(cellFsRead_symbol_flag))) {
				cellFsRead_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsWrite_symbol_flag, sizeof(cellFsWrite_symbol_flag))) {
				cellFsWrite_symbol = n - 0x10;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsLseek_symbol_flag, sizeof(cellFsLseek_symbol_flag))) {
				cellFsLseek_symbol = n - 0x10;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsStat_symbol_flag, sizeof(cellFsStat_symbol_flag))) {
				cellFsStat_symbol = n - 0x3C;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsUnlink_internal_symbol_flag, sizeof(cellFsUnlink_internal_symbol_flag))) {
				cellFsUnlink_internal_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) cellFsUtilMount_symbol_flag, sizeof(cellFsUtilMount_symbol_flag))) {
				cellFsUtilMount_symbol = n + 0x1C;
				cellFsUtilUmount_symbol = n - 0x10;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) pathdup_from_user_symbol_flag, sizeof(pathdup_from_user_symbol_flag))) {
				pathdup_from_user_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) open_path_symbol_flag, sizeof(open_path_symbol_flag))) {
				open_path_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) close_fs_object_symbol_flag, sizeof(close_fs_object_symbol_flag))) {
				close_fs_object_symbol = n + 0x10;
			}
			if(close_fs_object_symbol && !open_fs_object_symbol)
			if(compare(0xBB, (char *) &memLV2[n], (char *) open_fs_object_symbol_flag, sizeof(open_fs_object_symbol_flag)) ) {
				open_fs_object_symbol = n + 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) storage_get_device_info_symbol_flag, sizeof(storage_get_device_info_symbol_flag))) {
				storage_get_device_info_symbol = n + 0x30;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) storage_open_symbol_flag, sizeof(storage_open_symbol_flag))
			|| compare(-1, (char *) &memLV2[n], (char *) storage_open_symbol_flag1, sizeof(storage_open_symbol_flag1)) ) {
				storage_open_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) storage_close_symbol_flag, sizeof(storage_close_symbol_flag))) {
				storage_close_symbol = n - 4;
			}
			if(!storage_read_symbol)
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_read_symbol_flag, sizeof(storage_read_symbol_flag))) {
				storage_read_symbol = n + 0x60;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_send_device_command_symbol_flag, sizeof(storage_send_device_command_symbol_flag))) {
				storage_send_device_command_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) storage_map_io_memory_symbol_flag, sizeof(storage_map_io_memory_symbol_flag))) {
				storage_map_io_memory_symbol = n + 0x30;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) storage_unmap_io_memory_symbol_flag, sizeof(storage_unmap_io_memory_symbol_flag))
			|| compare(-1, (char *) &memLV2[n], (char *) storage_unmap_io_memory_symbol_flag1, sizeof(storage_unmap_io_memory_symbol_flag1))
			) {
				storage_unmap_io_memory_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) storage_internal_get_device_object_symbol_flag, sizeof(storage_internal_get_device_object_symbol_flag))) {
				storage_internal_get_device_object_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) decrypt_func_symbol_flag, sizeof(decrypt_func_symbol_flag))) {
				decrypt_func_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) lv1_call_99_wrapper_symbol_flag, sizeof(lv1_call_99_wrapper_symbol_flag))) {
				lv1_call_99_wrapper_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) modules_verification_symbol_flag, sizeof(modules_verification_symbol_flag))) {
				modules_verification_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) prx_load_module_symbol_flag, sizeof(prx_load_module_symbol_flag))) {
				prx_load_module_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) prx_start_module_symbol_flag, sizeof(prx_start_module_symbol_flag))) {
				prx_start_module_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) prx_stop_module_symbol_flag, sizeof(prx_stop_module_symbol_flag))) {
				prx_stop_module_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) prx_unload_module_symbol_flag, sizeof(prx_unload_module_symbol_flag))) {
				prx_unload_module_symbol =  n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) prx_get_module_info_symbol_flag, sizeof(prx_get_module_info_symbol_flag))) {
				prx_get_module_info_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) prx_get_module_list_symbol_flag, sizeof(prx_get_module_list_symbol_flag))) {
				prx_get_module_list_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) extend_kstack_symbol_flag, sizeof(extend_kstack_symbol_flag))) {
				extend_kstack_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) get_pseudo_random_number_symbol_flag, sizeof(get_pseudo_random_number_symbol_flag))) {
				get_pseudo_random_number_symbol = n - 8;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) syscall_call_offset_flag, sizeof(syscall_call_offset_flag))) {
				syscall_call_offset = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) read_bdvd0_symbol_flag, sizeof(read_bdvd0_symbol_flag))) {
				read_bdvd0_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) read_bdvd1_symbol_flag, sizeof(read_bdvd1_symbol_flag))) {
				read_bdvd1_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) read_bdvd2_symbol_flag, sizeof(read_bdvd2_symbol_flag))) {
				read_bdvd2_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) process_map_caller_call_flag, sizeof(process_map_caller_call_flag))) {
				process_map_caller_call = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) fsloop_open_call_flag, sizeof(fsloop_open_call_flag))) {
				fsloop_open_call = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) fsloop_close_call_flag, sizeof(fsloop_close_call_flag))) {
				fsloop_close_call = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) fsloop_read_call_flag, sizeof(fsloop_read_call_flag))) {
				fsloop_read_call = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) io_rtoc_entry_1_flag, sizeof(io_rtoc_entry_1_flag))) {
				memcpy(&io_rtoc_entry_1, &memLV2[n-2], 2);
				io_rtoc_entry_1 = SWAP16(io_rtoc_entry_1);
			}
			if(compare(-1, (char *) &memLV2[n], (char *) io_sub_rtoc_entry_1_flag, sizeof(io_sub_rtoc_entry_1_flag))) {
				memcpy(&io_sub_rtoc_entry_1, &memLV2[n-2], 2);
				io_sub_rtoc_entry_1 = SWAP16(io_sub_rtoc_entry_1);
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) decrypt_rtoc_entry_2_flag, sizeof(decrypt_rtoc_entry_2_flag))) {
				memcpy(&decrypt_rtoc_entry_2, &memLV2[n-2], 2);
				decrypt_rtoc_entry_2 = SWAP16(decrypt_rtoc_entry_2);
			}
			if(compare(-1, (char *) &memLV2[n], (char *) storage_rtoc_entry_1_flag, sizeof(storage_rtoc_entry_1_flag))) {
				memcpy(&storage_rtoc_entry_1, &memLV2[n-2], 2);
				storage_rtoc_entry_1 = SWAP16(storage_rtoc_entry_1);
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) time_rtoc_entry_1_flag, sizeof(time_rtoc_entry_1_flag))) {
				memcpy(&time_rtoc_entry_1, &memLV2[n-2], 2);
				time_rtoc_entry_1 = SWAP16(time_rtoc_entry_1);
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) time_rtoc_entry_2_flag, sizeof(time_rtoc_entry_2_flag))) {
				memcpy(&time_rtoc_entry_2, &memLV2[n-2], 2);
				time_rtoc_entry_2 = SWAP16(time_rtoc_entry_2);
			}
			if(compare(-1, (char *) &memLV2[n], (char *) thread_rtoc_entry_1_flag, sizeof(thread_rtoc_entry_1_flag))) {
				memcpy(&thread_rtoc_entry_1, &memLV2[n-2], 2);
				thread_rtoc_entry_1 = SWAP16(thread_rtoc_entry_1);
			}
			if(compare(-1, (char *) &memLV2[n], (char *) device_event_flag, sizeof(device_event_flag))) {
				memcpy(&device_event_rtoc_entry_1, &memLV2[n-2], 2);
				device_event_rtoc_entry_1 = SWAP16(device_event_rtoc_entry_1);
				device_event_port_send_call = n + 0x14;
				memcpy(&device_event_port_send_call_restore, &memLV2[device_event_port_send_call], 4);			
			}
			if(compare(-1, (char *) &memLV2[n], (char *) process_rtoc_entry_1_flag, sizeof(process_rtoc_entry_1_flag))) {
				memcpy(&process_rtoc_entry_1, &memLV2[n-2], 2);
				process_rtoc_entry_1 = SWAP16(process_rtoc_entry_1);
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) bt_rtoc_entry_1_flag, sizeof(bt_rtoc_entry_1_flag))) {
				memcpy(&bt_rtoc_entry_1, &memLV2[n-2], 2);
				bt_rtoc_entry_1 = SWAP16(bt_rtoc_entry_1);
			}
			if(compare(-1, (char *) &memLV2[n], (char *) thread_info_symbol_flag, sizeof(thread_info_symbol_flag))) {
				thread_info_symbol = n-0x58;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) patch_func2_flag, sizeof(patch_func2_flag))) {
				patch_func2 = n + 0x10;
				memcpy(&patch_func2_restore, &memLV2[patch_func2 + 0x2C], 4);
				patch_func2_restore = SWAP32(patch_func2_restore);
				// if(patch_func2_restore == ) {
					// if(ent->d_name[3] == 'C') {
						// patch_func2_restore = ;
					// } else
					// //if(ent->d_name[3] == 'D') 
					// {
						// patch_func2_restore = ;
					// }
				// }				
			}
			if(compare(-1, (char *) &memLV2[n], (char *) user_thread_prio_patch_flag, sizeof(user_thread_prio_patch_flag))) {
				user_thread_prio_patch = n + 0x10;
				user_thread_prio_patch2 = n + 0x14;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) shutdown_patch_offset_flag, sizeof(shutdown_patch_offset_flag))) {
				shutdown_patch_offset = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) shutdown_copy_params_call_flag, sizeof(shutdown_copy_params_call_flag))) {
				shutdown_copy_params_call = n-4;
				memcpy(&shutdown_copy_params_call_restore, &memLV2[shutdown_copy_params_call], 4);		
			}		
			if(compare(-1, (char *) &memLV2[n], (char *) create_process_common_symbol_flag, sizeof(create_process_common_symbol_flag))) {
				create_process_common_symbol = n-4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) create_process_base_symbol_flag, sizeof(create_process_base_symbol_flag))) {
				create_process_base_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) process_kill_symbol_flag, sizeof(process_kill_symbol_flag))) {
				process_kill_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) create_kernel_thread_symbol_flag, sizeof(create_kernel_thread_symbol_flag))) {
				create_kernel_thread_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) create_user_thread_symbol_flag, sizeof(create_user_thread_symbol_flag))) {
				create_user_thread_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) deallocate_user_stack_symbol_flag, sizeof(deallocate_user_stack_symbol_flag))) {
				deallocate_user_stack_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) mutex_lock_ex_symbol_flag, sizeof(mutex_lock_ex_symbol_flag))) {
				mutex_lock_ex_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cond_create_symbol_flag, sizeof(cond_create_symbol_flag))) {
				cond_create_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cond_destroy_symbol_flag, sizeof(cond_destroy_symbol_flag))) {
				cond_destroy_symbol = n;
				cond_wait_symbol = n - 0x8;
				cond_signal_symbol = n - 0x2C;
				cond_signal_all_symbol = n - 0x50;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cond_wait_ex_symbol_flag, sizeof(cond_wait_ex_symbol_flag))) {
				cond_wait_ex_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) event_queue_tryreceive_symbol_flag, sizeof(event_queue_tryreceive_symbol_flag))) {
				event_queue_tryreceive_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) event_port_send_ex_symbol_flag, sizeof(event_port_send_ex_symbol_flag))) {
				event_port_send_ex_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) event_port_send_symbol_flag, sizeof(event_port_send_symbol_flag))) {
				event_port_send_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) semaphore_post_ex_symbol_flag, sizeof(semaphore_post_ex_symbol_flag))) {
				semaphore_post_ex_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) semaphore_trywait_symbol_flag, sizeof(semaphore_trywait_symbol_flag))) {
				semaphore_trywait_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) semaphore_wait_ex_symbol_flag, sizeof(semaphore_wait_ex_symbol_flag))) {
				semaphore_wait_ex_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) semaphore_initialize_symbol_flag, sizeof(semaphore_initialize_symbol_flag))) {
				semaphore_initialize_symbol = n;
			}
			if(!cellFsUtime_symbol)
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsUtime_symbol_flag, sizeof(cellFsUtime_symbol_flag))) {
				cellFsUtime_symbol = n+0xC;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsRename_internal_symbol_flag, sizeof(cellFsRename_internal_symbol_flag))) {
				cellFsRename_internal_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsUtilUmount_symbol_flag, sizeof(cellFsUtilUmount_symbol_flag))) {
				cellFsUtilUmount_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) cellFsUtilNewfs_symbol_flag, sizeof(cellFsUtilNewfs_symbol_flag))) {
				cellFsUtilNewfs_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) storage_get_device_config_symbol_flag, sizeof(storage_get_device_config_symbol_flag))) {
				storage_get_device_config_symbol = n-4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) storage_write_symbol_flag, sizeof(storage_write_symbol_flag))) {
				storage_write_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) new_medium_listener_object_symbol_flag, sizeof(new_medium_listener_object_symbol_flag))) {
				new_medium_listener_object_symbol = n+4;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) delete_medium_listener_object_symbol_flag, sizeof(delete_medium_listener_object_symbol_flag))) {
				delete_medium_listener_object_symbol = n+8;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) set_medium_event_callbacks_symbol_flag, sizeof(set_medium_event_callbacks_symbol_flag))) {
				set_medium_event_callbacks_symbol = n;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) mmapper_flags_temp_patch_flag, sizeof(mmapper_flags_temp_patch_flag))) {
				mmapper_flags_temp_patch = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) PATCH_JUMP_flag, sizeof(PATCH_JUMP_flag))) {
				PATCH_JUMP = n+0x24;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) sm_get_temperature_symbol_flag, sizeof(sm_get_temperature_symbol_flag))) {
				sm_get_temperature_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) sm_get_fan_policy_symbol_flag, sizeof(sm_get_fan_policy_symbol_flag))) {
				sm_get_fan_policy_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) sm_set_fan_policy_symbol_flag, sizeof(sm_set_fan_policy_symbol_flag))) {
				sm_set_fan_policy_symbol = n;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) sm_get_temperature_patch_flag, sizeof(sm_get_temperature_patch_flag))) {
				sm_get_temperature_patch = n + 0x20;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) sm_get_fan_policy_patch_flag, sizeof(sm_get_fan_policy_patch_flag))) {
				sm_get_fan_policy_patch = n + 0x14;
			}
			if(compare(0xFF, (char *) &memLV2[n], (char *) sm_set_fan_policy_patch_flag, sizeof(sm_set_fan_policy_patch_flag))) {
				sm_set_fan_policy_patch = n + 0x14;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) update_mgr_if_get_token_symbol_flag, sizeof(update_mgr_if_get_token_symbol_flag))) {
				update_mgr_if_get_token_symbol = n+0x10;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) get_path_by_fd_symbol_flag, sizeof(get_path_by_fd_symbol_flag))) {
				get_path_by_fd_symbol = n;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) patch_func8_offset1_flag, sizeof(patch_func8_offset1_flag))) {
				patch_func8_offset1 = n+0x20;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) patch_func8_offset2_flag, sizeof(patch_func8_offset2_flag))) {
				patch_func8_offset2 = n - 4;
				memcpy(&patch_func8_offset2_restore, &memLV2[patch_func8_offset2], 4);
				patch_func8_offset2_restore = SWAP32(patch_func8_offset2_restore);
				if(patch_func8_offset2_restore == 0x60000000) {
					if(ent->d_name[3] == 'C') {
						patch_func8_offset2_restore = 0x48216FB5;
					} else
					//if(ent->d_name[3] == 'D') 
					{
						patch_func8_offset2_restore = 0x4821B4BD;
					}
				}
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) patch_func9_offset_flag, sizeof(patch_func9_offset_flag))) {
				patch_func9_offset = n+8;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) mem_base2_flag, sizeof(mem_base2_flag))) {
				mem_base2 = n+0x30;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) permissions_func_symbol_flag, sizeof(permissions_func_symbol_flag))) {
				permissions_func_symbol = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) permissions_exception1_flag, sizeof(permissions_exception1_flag))) {
				permissions_exception1 = n+0x20;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) permissions_exception2_flag, sizeof(permissions_exception2_flag))) {
				permissions_exception2 = n;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) permissions_exception3_flag, sizeof(permissions_exception3_flag))) {
				permissions_exception3 = n+0x10;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) module_sdk_version_patch_offset_flag, sizeof(module_sdk_version_patch_offset_flag))) {
				module_sdk_version_patch_offset = n-4;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) module_add_parameter_to_parse_sprxpatch_offset_flag, sizeof(module_add_parameter_to_parse_sprxpatch_offset_flag))) {
				module_add_parameter_to_parse_sprxpatch_offset = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) user_thread_prio_patch2_flag, sizeof(user_thread_prio_patch2_flag))) {
				user_thread_prio_patch2 = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) ss_pid_call_1_flag, sizeof(ss_pid_call_1_flag))) {
				ss_pid_call_1 = n - 4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) read_module_header_call_flag, sizeof(read_module_header_call_flag))) {
				read_module_header_call = n-4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) read_module_body_call_flag, sizeof(read_module_body_call_flag))) {
				read_module_body_call = n-4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) load_module_by_fd_call1_flag, sizeof(load_module_by_fd_call1_flag))) {
				load_module_by_fd_call1 = n;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) hid_mgr_read_usb_symbol_flag, sizeof(hid_mgr_read_usb_symbol_flag))) {
				hid_mgr_read_usb_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) hid_mgr_read_bt_symbol_flag, sizeof(hid_mgr_read_bt_symbol_flag))) {
				hid_mgr_read_bt_symbol = n+0xC;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) bt_set_controller_info_internal_symbol_flag, sizeof(bt_set_controller_info_internal_symbol_flag))) {
				bt_set_controller_info_internal_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) SHA1_init_symbol_flag, sizeof(SHA1_init_symbol_flag))) {
				SHA1_init_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) SHA1_update_symbol_flag, sizeof(SHA1_update_symbol_flag))) {
				SHA1_update_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) SHA1_final_symbol_flag, sizeof(SHA1_final_symbol_flag))) {
				SHA1_final_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) aescbccfb_dec_symbol_flag, sizeof(aescbccfb_dec_symbol_flag))) {
				aescbccfb_dec_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) aescbccfb_enc_symbol_flag, sizeof(aescbccfb_enc_symbol_flag))) {
				aescbccfb_enc_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) ss_params_get_update_status_symbol_flag, sizeof(ss_params_get_update_status_symbol_flag))) {
				ss_params_get_update_status_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) md5_reset_symbol_flag, sizeof(md5_reset_symbol_flag))) {
				md5_reset_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) md5_update_symbol_flag, sizeof(md5_update_symbol_flag))) {
				md5_update_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) md5_final_symbol_flag, sizeof(md5_final_symbol_flag))) {
				md5_final_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) ss_get_open_psid_symbol_flag, sizeof(ss_get_open_psid_symbol_flag))) {
				ss_get_open_psid_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) update_mgr_read_eeprom_symbol_flag, sizeof(update_mgr_read_eeprom_symbol_flag))) {
				update_mgr_read_eeprom_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) update_mgr_write_eeprom_symbol_flag, sizeof(update_mgr_write_eeprom_symbol_flag))) {
				update_mgr_write_eeprom_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) prx_get_module_id_by_address_symbol_flag, sizeof(prx_get_module_id_by_address_symbol_flag))) {
				prx_get_module_id_by_address_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) prx_get_module_id_by_name_symbol_flag, sizeof(prx_get_module_id_by_name_symbol_flag))) {
				prx_get_module_id_by_name_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) load_module_by_fd_symbol_flag, sizeof(load_module_by_fd_symbol_flag))) {
				load_module_by_fd_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) parse_sprx_symbol_flag, sizeof(parse_sprx_symbol_flag))) {
				parse_sprx_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) open_prx_object_symbol_flag, sizeof(open_prx_object_symbol_flag))) {
				open_prx_object_symbol = n;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) close_prx_object_symbol_flag, sizeof(close_prx_object_symbol_flag))) {
				close_prx_object_symbol = n+0x10;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) lock_prx_mutex_symbol_flag, sizeof(lock_prx_mutex_symbol_flag))) {
				lock_prx_mutex_symbol = n + 0x20;
				unlock_prx_mutex_symbol = n + 0x2C;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) authenticate_program_segment_symbol_flag, sizeof(authenticate_program_segment_symbol_flag))) {
				authenticate_program_segment_symbol = n;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) rsx_syscall_check_flag, sizeof(rsx_syscall_check_flag))) {
				rsx_syscall_check = n;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) unk_func2_unregister_service_flag, sizeof(unk_func2_unregister_service_flag))) {
				unk_func2_unregister_service = n+4;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) unk_func3_unregister_service_flag, sizeof(unk_func3_unregister_service_flag))) {
				unk_func3_unregister_service = n;
			}			
			if(compare(-1, (char *) &memLV2[n], (char *) qa_eeprom_offset_flag, sizeof(qa_eeprom_offset_flag))) {
				qa_eeprom_offset = n;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) fix_8001003E_flag, sizeof(fix_8001003E_flag))) {
				fix_8001003E = n-8;
			}
			if(compare(0xAA, (char *) &memLV2[n], (char *) ECDSA_2_flag, sizeof(ECDSA_2_flag))) {
				ECDSA_2 = n+8;
			}
			if(compare(-1, (char *) &memLV2[n], (char *) ECDSA_1_flag, sizeof(ECDSA_1_flag))) {
				ECDSA_1 = n-4;
			}
		}
		free(memLV2);

// *************
//	LV1
// *************

		sprintf(dump, "LV1/%s", ent->d_name);
		char *memLV1 = LoadFile(dump,&size);
		
		if(memLV1!=NULL) {
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
				if(compare(0xFF, (char *) &memLV1[n], (char *) vsh_pos_in_ram_FLAG, sizeof(vsh_pos_in_ram_FLAG))){
					vsh_pos_in_ram = n - 0x200;
				}
				
				if(HV_START_OFFSET && HTAB_OFFSET && MMAP_OFFSET1 && MMAP_OFFSET2 && SPE_OFFSET && n<0x360000)	n=0x360000;
					
				if(vsh_pos_in_ram)
				if(HV_START_OFFSET)
				if(HTAB_OFFSET)
				if(MMAP_OFFSET1)
				if(MMAP_OFFSET2)
				if(SPE_OFFSET)
					break;
			}
			free(memLV1);
			
		} else printf(warning("LV1 is missing, HV_START_OFFSET = unk \n"));		

		if(SYSCALL_TABLE != 0) SYSCALL_TABLE = 0x8000000000000000ULL + SYSCALL_TABLE;
		if(OPEN_HOOK != 0) OPEN_HOOK = 0x8000000000000000ULL + OPEN_HOOK;
		if(BASE_ADDR != 0) BASE_ADDR = 0x8000000000000000ULL + BASE_ADDR;
		if(LV2MOUNTADDR != 0) LV2MOUNTADDR = 0x8000000000000000ULL + LV2MOUNTADDR;
		if(FIRMWARE_OFFSET != 0) FIRMWARE_OFFSET = 0x8000000000000000ULL + FIRMWARE_OFFSET;
		if(FW_DATE_OFFSET != 0) FW_DATE_OFFSET = 0x8000000000000000ULL + FW_DATE_OFFSET;
		if(OFFSET_1_IDPS != 0) OFFSET_1_IDPS = 0x8000000000000000ULL + OFFSET_1_IDPS;
		if(OFFSET_2_IDPS != 0) OFFSET_2_IDPS = 0x8000000000000000ULL + OFFSET_2_IDPS;
		if(LPAR != 0) LPAR = 0x8000000000000000ULL + LPAR;
		// if(UFS_SB_ADDR != 0) UFS_SB_ADDR += 0x8000000000000000ULL; 
		
		
		char str[255];
		
		fputs("\n", IDPSET_firmware_h);
		sprintf(str, "#define HTAB_OFFSET_%lld%c         0x%06llX\n", FIRMWARE, D, HTAB_OFFSET); fputs(str, IDPSET_firmware_h);
		sprintf(str, "#define MMAP_OFFSET1_%lld%c        0x%06llX\n", FIRMWARE, D, MMAP_OFFSET1); fputs(str, IDPSET_firmware_h);		
		sprintf(str, "#define MMAP_OFFSET2_%lld%c        0x%06llX\n", FIRMWARE, D, MMAP_OFFSET2); fputs(str, IDPSET_firmware_h);		
		sprintf(str, "#define SPE_OFFSET_%lld%c          0x%06llX\n", FIRMWARE, D, SPE_OFFSET); fputs(str, IDPSET_firmware_h);
		sprintf(str, "#define HV_START_OFFSET_%lld%c     0x%06llX\n", FIRMWARE, D, HV_START_OFFSET); fputs(str, IDPSET_firmware_h);
		sprintf(str, "#define TOC_OFFSET_%lld%c          0x%llXULL\n", FIRMWARE, D, TOC); fputs(str, IDPSET_firmware_h);
		sprintf(str, "#define SYSCALL_TABLE_%lld%c       0x%llXULL\n", FIRMWARE, D, SYSCALL_TABLE); fputs(str, IDPSET_firmware_h);
		sprintf(str, "#define FW_DATE_OFFSET_%lld%c      0x%llXULL\n", FIRMWARE, D, FW_DATE_OFFSET); fputs(str, IDPSET_firmware_h);
		sprintf(str, "#define FW_DATE_1_%lld%c           0x%llXULL\n", FIRMWARE, D, FW_DATE_1); fputs(str, IDPSET_firmware_h);
		sprintf(str, "#define FW_DATE_2_%lld%c           0x%llXULL\n", FIRMWARE, D, FW_DATE_2); fputs(str, IDPSET_firmware_h);
		sprintf(str, "#define OFFSET_1_IDPS_%lld%c       0x%llXULL\n", FIRMWARE, D, OFFSET_1_IDPS); fputs(str, IDPSET_firmware_h);
		sprintf(str, "#define OFFSET_2_IDPS_%lld%c       0x%llXULL\n", FIRMWARE, D, OFFSET_2_IDPS); fputs(str, IDPSET_firmware_h);	
		
		sprintf(str, "#ifdef FIRMWARE_%lld%c\n", FIRMWARE, D); fputs(str, IDPSET_symbols_h);
		sprintf(str, "\t#define KERNEL_TOC			                 0x%06llX\n", TOC - 0x8000000000000000ULL); fputs(str, IDPSET_symbols_h);
		sprintf(str, "\t#define KERNEL_SYMBOL_EXTEND_KSTACK          0x%06llX\n", extend_kstack_symbol); fputs(str, IDPSET_symbols_h);
		sprintf(str, "\t#define KERNEL_SYMBOL_COPY_TO_USER           0x%06llX\n", copy_to_user_symbol); fputs(str, IDPSET_symbols_h);
		sprintf(str, "\t#define KERNEL_SYMBOL_MEMSET                 0x%06llX\n", memset_symbol); fputs(str, IDPSET_symbols_h);
		sprintf(str, "\t#define KERNEL_SYMBOL_MEMCPY                 0x%06llX\n", memcpy_symbol); fputs(str, IDPSET_symbols_h);
		sprintf(str, "\t#define GAMEOS_LPAR_BASE_PTR                 0x%llXULL\n", LPAR); fputs(str, IDPSET_symbols_h);
		sprintf(str, "\t#define GAMEOS_LPAR_SIZE_PTR                 0x%llXULL\n", LPAR+8); fputs(str, IDPSET_symbols_h);
		fputs("#endif\n\n", IDPSET_symbols_h);
		
		fputs("\n", common);
		sprintf(str, "#define TOC_%lld%c                   0x%llXULL\n", FIRMWARE, D, TOC); fputs(str, common);
		sprintf(str, "#define SYSCALL_TABLE_%lld%c         0x%llXULL\n", FIRMWARE, D, SYSCALL_TABLE); fputs(str, common);
		sprintf(str, "#define HV_START_OFFSET_%lld%c       0x%06llX\n", FIRMWARE, D, HV_START_OFFSET); fputs(str, common);
		sprintf(str, "#define HTAB_OFFSET_%lld%c           0x%06llX\n", FIRMWARE, D, HTAB_OFFSET); fputs(str, common);
		sprintf(str, "#define HTAB_PATCH1_%lld%c           0x%06llX\n", FIRMWARE, D, HTAB_PATCH1); fputs(str, common);
		sprintf(str, "#define HTAB_PATCH2_%lld%c           0x%06llX\n", FIRMWARE, D, HTAB_PATCH2); fputs(str, common);
		sprintf(str, "#define HTAB_PATCH3_%lld%c           0x%06llX\n", FIRMWARE, D, HTAB_PATCH3); fputs(str, common);
		sprintf(str, "#define MMAP_OFFSET1_%lld%c          0x%06llX\n", FIRMWARE, D, MMAP_OFFSET1); fputs(str, common);		
		sprintf(str, "#define MMAP_OFFSET2_%lld%c          0x%06llX\n", FIRMWARE, D, MMAP_OFFSET2); fputs(str, common);		
		sprintf(str, "#define SPE_OFFSET_%lld%c            0x%06llX\n", FIRMWARE, D, SPE_OFFSET); fputs(str, common);
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
		sprintf(str, "#define FW_DATE_OFFSET_%lld%c        0x%llXULL\n", FIRMWARE, D, FW_DATE_OFFSET); fputs(str, common);
		sprintf(str, "#define FW_DATE_1_%lld%c             0x%llXULL\n", FIRMWARE, D, FW_DATE_1); fputs(str, common);
		sprintf(str, "#define FW_DATE_2_%lld%c             0x%llXULL\n", FIRMWARE, D, FW_DATE_2); fputs(str, common);
		sprintf(str, "#define OFFSET_1_IDPS_%lld%c         0x%llXULL\n", FIRMWARE, D, OFFSET_1_IDPS); fputs(str, common);
		sprintf(str, "#define OFFSET_2_IDPS_%lld%c         0x%llXULL\n", FIRMWARE, D, OFFSET_2_IDPS); fputs(str, common);
		//sprintf(str, "#define UFS_SB_ADDR_%lld%c           0x%llXULL\n", FIRMWARE, D, UFS_SB_ADDR); fputs(str, common);
		
		
		
		fputs("\n", SKY);
		sprintf(str, "#ifdef CFW_%lld%c\n", FIRMWARE, D); fputs(str, SKY);
		sprintf(str, "#define alloc                   0x%llX\n", OFF_alloc); fputs(str, SKY);
		sprintf(str, "#define memory_patch_func       0x%llX\n", OFF_memory_patch_func); fputs(str, SKY);
		sprintf(str, "#define memcpy                  0x%llX\n", OFF_memcpy); fputs(str, SKY);
		sprintf(str, "#define memset                  0x%llX\n", OFF_memset); fputs(str, SKY);
		fputs("#endif\n", SKY);
		
		sprintf(temp, "#ifdef FIRMWARE_%lld%c\n\n", FIRMWARE, D); fputs(temp, symbols_old);
		
		
		sprintf(temp, "\t#define FIRMWARE_VERSION                                 0x%d\n\n", FIRMWARE); fputs(temp, symbols_old);
		
		fputs("\t#ifdef PS3M_API\n", symbols_old);
		sprintf(temp, "\t\t#define PS3MAPI_FW_VERSION                           0x%d\n", FIRMWARE); fputs(temp, symbols_old);
		if(D=='C') {
			    fputs("\t\t#define PS3MAPI_FW_TYPE                              \"CEX MAMBA\"\n", symbols_old);
		} else {
			    fputs("\t\t#define PS3MAPI_FW_TYPE                              \"DEX MAMBA\"\n", symbols_old);
		}
		sprintf(temp, "\t\t#define PS3MAPI_IDPS_1                               0x%llXULL\n", OFFSET_1_IDPS); fputs(temp, symbols_old);
		sprintf(temp, "\t\t#define PS3MAPI_IDPS_2                               0x%llXULL\n", OFFSET_2_IDPS); fputs(temp, symbols_old);
		sprintf(temp, "\t\t#define PS3MAPI_PSID                                 0x%llXULL\n", OFFSET_2_IDPS + 0x18); fputs(temp, symbols_old);	
		fputs("\t#endif\n\n", symbols_old);
		
		
		fputs("\t/* lv2 */\n", symbols_old);
		sprintf(temp, "\t#define TOC                                              0x%X\n", TOC); fputs(temp, symbols_old);
		sprintf(temp, "\t#define open_shared_kernel_object_symbol                 0x%X\n", open_shared_kernel_object_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define close_kernel_object_handle_symbol                0x%X\n", close_kernel_object_handle_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define open_kernel_object_symbol                        0x%X\n", open_kernel_object_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define alloc_symbol                                     0x%X\n", alloc_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define dealloc_symbol                                   0x%X\n", dealloc_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define copy_to_user_symbol                              0x%X\n", copy_to_user_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define copy_from_user_symbol                            0x%X\n", copy_from_user_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define copy_to_process_symbol                           0x%X\n", copy_to_process_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define copy_from_process_symbol                         0x%X\n", copy_from_process_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define page_allocate_symbol                             0x%X\n", page_allocate_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define page_free_symbol                                 0x%X\n", page_free_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define page_export_to_proc_symbol                       0x%X\n", page_export_to_proc_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define page_unexport_from_proc_symbol                   0x%X\n", page_unexport_from_proc_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define kernel_ea_to_lpar_addr_symbol                    0x%X\n", kernel_ea_to_lpar_addr_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define map_process_memory_symbol                        0x%X\n", map_process_memory_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define memcpy_symbol                                    0x%X\n", memcpy_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define memset_symbol                                    0x%X\n", memset_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define memcmp_symbol                                    0x%X\n", memcmp_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define printf_symbol                                    0x%X\n", printf_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define printfnull_symbol                                0x%X\n", printfnull_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define sprintf_symbol                                   0x%X\n", sprintf_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define snprintf_symbol                                  0x%X\n", snprintf_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define strcpy_symbol                                    0x%X\n", strcpy_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define strncpy_symbol                                   0x%X\n", strncpy_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define strlen_symbol                                    0x%X\n", strlen_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define strcat_symbol                                    0x%X\n", strcat_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define strcmp_symbol                                    0x%X\n", strcmp_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define strncmp_symbol                                   0x%X\n", strncmp_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define strchr_symbol                                    0x%X\n", strchr_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define spin_lock_irqsave_ex_symbol                      0x%X\n", spin_lock_irqsave_ex_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define spin_unlock_irqrestore_ex_symbol                 0x%X\n", spin_unlock_irqrestore_ex_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define load_process_symbol                              0x%X\n", load_process_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define ppu_thread_create_symbol                         0x%X\n", ppu_thread_create_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define ppu_thread_exit_symbol                           0x%X\n", ppu_thread_exit_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define ppu_thread_join_symbol                           0x%X\n", ppu_thread_join_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define ppu_thread_delay_symbol                          0x%X\n", ppu_thread_delay_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define create_user_thread2_symbol                       0x%X\n", create_user_thread2_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define start_thread_symbol                              0x%X\n", start_thread_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define run_thread_symbol                                0x%X\n", run_thread_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define register_thread_symbol                           0x%X\n", register_thread_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define allocate_user_stack_symbol                       0x%X\n", allocate_user_stack_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define mutex_create_symbol                              0x%X\n", mutex_create_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define mutex_destroy_symbol                             0x%X\n", mutex_destroy_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define mutex_lock_symbol                                0x%X\n", mutex_lock_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define mutex_unlock_symbol                              0x%X\n", mutex_unlock_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define event_port_create_symbol                         0x%X\n", event_port_create_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define event_port_destroy_symbol                        0x%X\n", event_port_destroy_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define event_port_connect_symbol                        0x%X\n", event_port_connect_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define event_port_disconnect_symbol                     0x%X\n", event_port_disconnect_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define event_port_send_symbol                           0x%X\n", event_port_send_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define event_queue_create_symbol                        0x%X\n", event_queue_create_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define event_queue_destroy_symbol                       0x%X\n", event_queue_destroy_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define event_queue_receive_symbol                       0x%X\n", event_queue_receive_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define cellFsOpen_symbol                                0x%X\n", cellFsOpen_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define cellFsClose_symbol                               0x%X\n", cellFsClose_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define cellFsRead_symbol                                0x%X\n", cellFsRead_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define cellFsWrite_symbol                               0x%X\n", cellFsWrite_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define cellFsLseek_symbol                               0x%X\n", cellFsLseek_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define cellFsStat_symbol                                0x%X\n", cellFsStat_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define cellFsUnlink_internal_symbol                     0x%X\n", cellFsUnlink_internal_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define cellFsUtilMount_symbol                           0x%X\n", cellFsUtilMount_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define cellFsUtilUmount_symbol                          0x%X\n", cellFsUtilUmount_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define pathdup_from_user_symbol                         0x%X\n", pathdup_from_user_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define open_path_symbol                                 0x%X\n", open_path_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define open_fs_object_symbol                            0x%X\n", open_fs_object_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define close_fs_object_symbol                           0x%X\n", close_fs_object_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define storage_get_device_info_symbol                   0x%X\n", storage_get_device_info_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define storage_open_symbol                              0x%X\n", storage_open_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define storage_close_symbol                             0x%X\n", storage_close_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define storage_read_symbol                              0x%X\n", storage_read_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define storage_send_device_command_symbol               0x%X\n", storage_send_device_command_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define storage_map_io_memory_symbol                     0x%X\n", storage_map_io_memory_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define storage_unmap_io_memory_symbol                   0x%X\n", storage_unmap_io_memory_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define storage_internal_get_device_object_symbol        0x%X\n", storage_internal_get_device_object_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define decrypt_func_symbol                              0x%X\n", decrypt_func_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define lv1_call_99_wrapper_symbol                       0x%X\n", lv1_call_99_wrapper_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define modules_verification_symbol                      0x%X\n", modules_verification_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define prx_load_module_symbol                           0x%X\n", prx_load_module_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define prx_start_module_symbol                          0x%X\n", prx_start_module_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define prx_stop_module_symbol                           0x%X\n", prx_stop_module_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define prx_unload_module_symbol                         0x%X\n", prx_unload_module_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define prx_get_module_info_symbol                       0x%X\n", prx_get_module_info_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define prx_get_module_list_symbol                       0x%X\n", prx_get_module_list_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define extend_kstack_symbol                             0x%X\n", extend_kstack_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define get_pseudo_random_number_symbol                  0x%X\n", get_pseudo_random_number_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define syscall_table_symbol                             0x%X\n", SYSCALL_TABLE - 0x8000000000000000ULL); fputs(temp, symbols_old);
		sprintf(temp, "\t#define syscall_call_offset                              0x%X\n", syscall_call_offset); fputs(temp, symbols_old);
		sprintf(temp, "\t#define read_bdvd0_symbol                                0x%X\n", read_bdvd0_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define read_bdvd1_symbol                                0x%X\n", read_bdvd1_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define read_bdvd2_symbol                                0x%X\n", read_bdvd2_symbol); fputs(temp, symbols_old);
		sprintf(temp, "\t#define device_event_port_send_call                      0x%X\n", device_event_port_send_call); fputs(temp, symbols_old);
		sprintf(temp, "\t#define process_map_caller_call                          0x%X\n", process_map_caller_call); fputs(temp, symbols_old);
		sprintf(temp, "\t#define fsloop_open_call                                 0x%X\n", fsloop_open_call); fputs(temp, symbols_old);
		sprintf(temp, "\t#define fsloop_close_call                                0x%X\n", fsloop_close_call); fputs(temp, symbols_old);
		sprintf(temp, "\t#define fsloop_read_call                                 0x%X\n", fsloop_read_call); fputs(temp, symbols_old);
		if(io_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define io_rtoc_entry_1                                 -0x%X\n", 0 - io_rtoc_entry_1); fputs(temp, symbols_old);
		} else 	{
			sprintf(temp, "\t#define io_rtoc_entry_1                                  0x%X\n", io_rtoc_entry_1); fputs(temp, symbols_old);
		}
		if(io_sub_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define io_sub_rtoc_entry_1                             -0x%X\n", 0 - io_sub_rtoc_entry_1); fputs(temp, symbols_old);
		} else 	{
			sprintf(temp, "\t#define io_sub_rtoc_entry_1                              0x%X\n", io_sub_rtoc_entry_1); fputs(temp, symbols_old);
		}
		if(decrypt_rtoc_entry_2 < 0) {
			sprintf(temp, "\t#define decrypt_rtoc_entry_2                            -0x%X\n", 0 - decrypt_rtoc_entry_2); fputs(temp, symbols_old);
		} else 	{
			sprintf(temp, "\t#define decrypt_rtoc_entry_2                             0x%X\n", decrypt_rtoc_entry_2); fputs(temp, symbols_old);
		}
		if(storage_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define storage_rtoc_entry_1                            -0x%X\n", 0 - storage_rtoc_entry_1); fputs(temp, symbols_old);
		} else 	{
			sprintf(temp, "\t#define storage_rtoc_entry_1                             0x%X\n", storage_rtoc_entry_1); fputs(temp, symbols_old);
		}
		if(device_event_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define device_event_rtoc_entry_1                       -0x%X\n", 0 - device_event_rtoc_entry_1); fputs(temp, symbols_old);
		} else 	{
			sprintf(temp, "\t#define device_event_rtoc_entry_1                        0x%X\n", device_event_rtoc_entry_1); fputs(temp, symbols_old);
		}
		if(process_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define process_rtoc_entry_1                            -0x%X\n", 0 - process_rtoc_entry_1); fputs(temp, symbols_old);
		} else 	{
			sprintf(temp, "\t#define process_rtoc_entry_1                             0x%X\n", process_rtoc_entry_1); fputs(temp, symbols_old);
		}
		sprintf(temp, "\t#define patch_func2                                      0x%X\n", patch_func2); fputs(temp, symbols_old);
				fputs("\t#define patch_func2_offset                               0x2C\n", symbols_old);
		sprintf(temp, "\t#define user_thread_prio_patch                           0x%X\n", user_thread_prio_patch); fputs(temp, symbols_old);
		sprintf(temp, "\t#define user_thread_prio_patch2                          0x%X\n", user_thread_prio_patch2); fputs(temp, symbols_old);
		sprintf(temp, "\t#define shutdown_patch_offset                            0x%X\n", shutdown_patch_offset); fputs(temp, symbols_old);
		sprintf(temp, "\t#define shutdown_copy_params_call                        0x%X\n", shutdown_copy_params_call); fputs(temp, symbols_old);
		
		fputs("\n", symbols_old);
		
		sprintf(temp, "#ifdef FIRMWARE_%lld%c\n\n", FIRMWARE, D); fputs(temp, symbols);
		
		sprintf(temp, "\t#define FIRMWARE_VERSION                                 0x%d\n\n", FIRMWARE); fputs(temp, symbols);
		
		fputs("\t#ifdef PS3M_API\n", symbols);
		//sprintf(temp, "\t\t#define PS3MAPI_FW_VERSION                           0x%d\n", FIRMWARE); fputs(temp, symbols);
		if(D=='C') {
			    fputs("\t\t#define PS3MAPI_FW_TYPE                              \"CEX MAMBA\"\n", symbols);
		} else {
			    fputs("\t\t#define PS3MAPI_FW_TYPE                              \"DEX MAMBA\"\n", symbols);
		}
		sprintf(temp, "\t\t#define PS3MAPI_IDPS_1                               0x%llXULL\n", OFFSET_1_IDPS); fputs(temp, symbols);
		sprintf(temp, "\t\t#define PS3MAPI_IDPS_2                               0x%llXULL\n", OFFSET_2_IDPS); fputs(temp, symbols);
		sprintf(temp, "\t\t#define PS3MAPI_PSID                                 0x%llXULL\n", OFFSET_2_IDPS + 0x18); fputs(temp, symbols);	
		
		fputs("\t#endif\n", symbols);
		if(D=='C') {
			fputs(    "\t#define FIRMWARE_CEX                                     FIRMWARE_VERSION\n", symbols);
		} else {
			fputs(    "\t#define FIRMWARE_DEX                                     FIRMWARE_VERSION\n", symbols);
		}
		fputs("\n", symbols);
		
		
		fputs("\t/* lv2 */\n", symbols);
		sprintf(temp, "\t#define TOC                                              0x%X\n", TOC); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define create_kernel_object_symbol                      0x%X\n",create_kernel_object_symbol                      ); fputs(temp, symbols);
		sprintf(temp, "\t#define destroy_kernel_object_symbol                     0x%X\n",destroy_kernel_object_symbol                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define destroy_shared_kernel_object_symbol              0x%X\n",destroy_shared_kernel_object_symbol              ); fputs(temp, symbols);
		sprintf(temp, "\t#define open_kernel_object_symbol                        0x%X\n",open_kernel_object_symbol                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define open_shared_kernel_object_symbol                 0x%X\n",open_shared_kernel_object_symbol                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define close_kernel_object_handle_symbol                0x%X\n",close_kernel_object_handle_symbol                ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define alloc_symbol                                     0x%X\n",alloc_symbol                                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define dealloc_symbol                                   0x%X\n",dealloc_symbol                                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define copy_to_user_symbol                              0x%X\n",copy_to_user_symbol                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define copy_from_user_symbol                            0x%X\n",copy_from_user_symbol                            ); fputs(temp, symbols);
		sprintf(temp, "\t#define copy_to_process_symbol                           0x%X\n",copy_to_process_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define copy_from_process_symbol                         0x%X\n",copy_from_process_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define process_read_memory_symbol                       0x%X\n",process_read_memory_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define process_write_memory_symbol                      0x%X\n",process_write_memory_symbol                      ); fputs(temp, symbols);
		sprintf(temp, "\t#define page_allocate_symbol                             0x%X\n",page_allocate_symbol                             ); fputs(temp, symbols);
		sprintf(temp, "\t#define page_free_symbol                                 0x%X\n",page_free_symbol                                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define page_export_to_proc_symbol                       0x%X\n",page_export_to_proc_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define page_unexport_from_proc_symbol                   0x%X\n",page_unexport_from_proc_symbol                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define kernel_ea_to_lpar_addr_symbol                    0x%X\n",kernel_ea_to_lpar_addr_symbol                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define process_ea_to_lpar_addr_ex_symbol                0x%X\n",process_ea_to_lpar_addr_ex_symbol                ); fputs(temp, symbols);
		sprintf(temp, "\t#define set_pte_symbol                                   0x%X\n",set_pte_symbol                                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define map_process_memory_symbol                        0x%X\n",map_process_memory_symbol                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define panic_symbol                                     0x%X\n",panic_symbol                                     ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define memcpy_symbol                                    0x%X\n",memcpy_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define memset_symbol                                    0x%X\n",memset_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define memcmp_symbol                                    0x%X\n",memcmp_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define memchr_symbol                                    0x%X\n",memchr_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define printf_symbol                                    0x%X\n",printf_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define printfnull_symbol                                0x%X\n",printfnull_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define sprintf_symbol                                   0x%X\n",sprintf_symbol                                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define snprintf_symbol                                  0x%X\n",snprintf_symbol                                  ); fputs(temp, symbols);
		sprintf(temp, "\t#define strcpy_symbol                                    0x%X\n",strcpy_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define strncpy_symbol                                   0x%X\n",strncpy_symbol                                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define strlen_symbol                                    0x%X\n",strlen_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define strcat_symbol                                    0x%X\n",strcat_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define strcmp_symbol                                    0x%X\n",strcmp_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define strncmp_symbol                                   0x%X\n",strncmp_symbol                                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define strchr_symbol                                    0x%X\n",strchr_symbol                                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define strrchr_symbol                                   0x%X\n",strrchr_symbol                                   ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define spin_lock_irqsave_ex_symbol                      0x%X\n",spin_lock_irqsave_ex_symbol                      ); fputs(temp, symbols);
		sprintf(temp, "\t#define spin_unlock_irqrestore_ex_symbol                 0x%X\n",spin_unlock_irqrestore_ex_symbol                 ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define create_process_common_symbol                     0x%X\n",create_process_common_symbol                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define create_process_base_symbol                       0x%X\n",create_process_base_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define load_process_symbol                              0x%X\n",load_process_symbol                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define process_kill_symbol                              0x%X\n",process_kill_symbol                              ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define ppu_thread_create_symbol                         0x%X\n",ppu_thread_create_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define ppu_thread_exit_symbol                           0x%X\n",ppu_thread_exit_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define ppu_thread_join_symbol                           0x%X\n",ppu_thread_join_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define ppu_thread_delay_symbol                          0x%X\n",ppu_thread_delay_symbol                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define create_kernel_thread_symbol                      0x%X\n",create_kernel_thread_symbol                      ); fputs(temp, symbols);
		sprintf(temp, "\t#define create_user_thread_symbol                        0x%X\n",create_user_thread_symbol                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define create_user_thread2_symbol                       0x%X\n",create_user_thread2_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define start_thread_symbol                              0x%X\n",start_thread_symbol                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define run_thread_symbol                                0x%X\n",run_thread_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define self_threading_symbol                            0x%X\n",self_threading_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define register_thread_symbol                           0x%X\n",register_thread_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define allocate_user_stack_symbol                       0x%X\n",allocate_user_stack_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define deallocate_user_stack_symbol                     0x%X\n",deallocate_user_stack_symbol                     ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define mutex_create_symbol                              0x%X\n",mutex_create_symbol                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define mutex_destroy_symbol                             0x%X\n",mutex_destroy_symbol                             ); fputs(temp, symbols);
		sprintf(temp, "\t#define mutex_lock_symbol                                0x%X\n",mutex_lock_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define mutex_lock_ex_symbol                             0x%X\n",mutex_lock_ex_symbol                             ); fputs(temp, symbols);
		sprintf(temp, "\t#define mutex_trylock_symbol                             0x%X\n",mutex_trylock_symbol                             ); fputs(temp, symbols);
		sprintf(temp, "\t#define mutex_unlock_symbol                              0x%X\n",mutex_unlock_symbol                              ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define cond_create_symbol                               0x%X\n",cond_create_symbol                               ); fputs(temp, symbols);
		sprintf(temp, "\t#define cond_destroy_symbol                              0x%X\n",cond_destroy_symbol                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define cond_wait_symbol                                 0x%X\n",cond_wait_symbol                                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define cond_wait_ex_symbol                              0x%X\n",cond_wait_ex_symbol                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define cond_signal_symbol                               0x%X\n",cond_signal_symbol                               ); fputs(temp, symbols);
		sprintf(temp, "\t#define cond_signal_all_symbol                           0x%X\n",cond_signal_all_symbol                           ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define semaphore_initialize_symbol                      0x%X\n",semaphore_initialize_symbol                      ); fputs(temp, symbols);
		sprintf(temp, "\t#define semaphore_wait_ex_symbol                         0x%X\n",semaphore_wait_ex_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define semaphore_trywait_symbol                         0x%X\n",semaphore_trywait_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define semaphore_post_ex_symbol                         0x%X\n",semaphore_post_ex_symbol                         ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define event_port_create_symbol                         0x%X\n",event_port_create_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_destroy_symbol                        0x%X\n",event_port_destroy_symbol                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_connect_symbol                        0x%X\n",event_port_connect_symbol                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_disconnect_symbol                     0x%X\n",event_port_disconnect_symbol                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_send_symbol                           0x%X\n",event_port_send_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define event_port_send_ex_symbol                        0x%X\n",event_port_send_ex_symbol                        ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define event_queue_create_symbol                        0x%X\n",event_queue_create_symbol                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define event_queue_destroy_symbol                       0x%X\n",event_queue_destroy_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define event_queue_receive_symbol                       0x%X\n",event_queue_receive_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define event_queue_tryreceive_symbol                    0x%X\n",event_queue_tryreceive_symbol                    ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define cellFsOpen_symbol                                0x%X\n",cellFsOpen_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsClose_symbol                               0x%X\n",cellFsClose_symbol                               ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsRead_symbol                                0x%X\n",cellFsRead_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsWrite_symbol                               0x%X\n",cellFsWrite_symbol                               ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsLseek_symbol                               0x%X\n",cellFsLseek_symbol                               ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsStat_symbol                                0x%X\n",cellFsStat_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsUtime_symbol                               0x%X\n",cellFsUtime_symbol                               ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsUnlink_internal_symbol                     0x%X\n",cellFsUnlink_internal_symbol                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsRename_internal_symbol                     0x%X\n",cellFsRename_internal_symbol                     ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define cellFsUtilMount_symbol                           0x%X\n",cellFsUtilMount_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsUtilUmount_symbol                          0x%X\n",cellFsUtilUmount_symbol                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellFsUtilNewfs_symbol                           0x%X\n",cellFsUtilNewfs_symbol                           ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define pathdup_from_user_symbol                         0x%X\n",pathdup_from_user_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define open_path_symbol                                 0x%X\n",open_path_symbol                                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define open_fs_object_symbol                            0x%X\n",open_fs_object_symbol                            ); fputs(temp, symbols);
		sprintf(temp, "\t#define close_fs_object_symbol                           0x%X\n",close_fs_object_symbol                           ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define storage_get_device_info_symbol                   0x%X\n",storage_get_device_info_symbol                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_get_device_config_symbol                 0x%X\n",storage_get_device_config_symbol                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_open_symbol                              0x%X\n",storage_open_symbol                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_close_symbol                             0x%X\n",storage_close_symbol                             ); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_read_symbol                              0x%X\n",storage_read_symbol                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_write_symbol                             0x%X\n",storage_write_symbol                             ); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_send_device_command_symbol               0x%X\n",storage_send_device_command_symbol               ); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_map_io_memory_symbol                     0x%X\n",storage_map_io_memory_symbol                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define storage_unmap_io_memory_symbol                   0x%X\n",storage_unmap_io_memory_symbol                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define new_medium_listener_object_symbol                0x%X\n",new_medium_listener_object_symbol                ); fputs(temp, symbols);
		sprintf(temp, "\t#define delete_medium_listener_object_symbol             0x%X\n",delete_medium_listener_object_symbol             ); fputs(temp, symbols);
		sprintf(temp, "\t#define set_medium_event_callbacks_symbol                0x%X\n",set_medium_event_callbacks_symbol                ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define cellUsbdRegisterLdd_symbol                       0x%X\n",cellUsbdRegisterLdd_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellUsbdUnregisterLdd_symbol                     0x%X\n",cellUsbdUnregisterLdd_symbol                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellUsbdScanStaticDescriptor_symbol              0x%X\n",cellUsbdScanStaticDescriptor_symbol              ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellUsbdOpenPipe_symbol                          0x%X\n",cellUsbdOpenPipe_symbol                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellUsbdClosePipe_symbol                         0x%X\n",cellUsbdClosePipe_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellUsbdControlTransfer_symbol                   0x%X\n",cellUsbdControlTransfer_symbol                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define cellUsbdBulkTransfer_symbol                      0x%X\n",cellUsbdBulkTransfer_symbol                      ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define decrypt_func_symbol                              0x%X\n",decrypt_func_symbol                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define lv1_call_99_wrapper_symbol                       0x%X\n",lv1_call_99_wrapper_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define modules_verification_symbol                      0x%X\n",modules_verification_symbol                      ); fputs(temp, symbols);
		sprintf(temp, "\t#define authenticate_program_segment_symbol              0x%X\n",authenticate_program_segment_symbol              ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define prx_load_module_symbol                           0x%X\n",prx_load_module_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_start_module_symbol                          0x%X\n",prx_start_module_symbol                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_stop_module_symbol                           0x%X\n",prx_stop_module_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_unload_module_symbol                         0x%X\n",prx_unload_module_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_get_module_info_symbol                       0x%X\n",prx_get_module_info_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_get_module_id_by_address_symbol              0x%X\n",prx_get_module_id_by_address_symbol              ); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_get_module_id_by_name_symbol                 0x%X\n",prx_get_module_id_by_name_symbol                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define prx_get_module_list_symbol                       0x%X\n",prx_get_module_list_symbol                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define load_module_by_fd_symbol                         0x%X\n",load_module_by_fd_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define parse_sprx_symbol                                0x%X\n",parse_sprx_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define open_prx_object_symbol                           0x%X\n",open_prx_object_symbol                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define close_prx_object_symbol                          0x%X\n",close_prx_object_symbol                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define lock_prx_mutex_symbol                            0x%X\n",lock_prx_mutex_symbol                            ); fputs(temp, symbols);
		sprintf(temp, "\t#define unlock_prx_mutex_symbol                          0x%X\n",unlock_prx_mutex_symbol                          ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define extend_kstack_symbol                             0x%X\n",extend_kstack_symbol                             ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define get_pseudo_random_number_symbol                  0x%X\n",get_pseudo_random_number_symbol                  ); fputs(temp, symbols);
		sprintf(temp, "\t#define md5_reset_symbol                                 0x%X\n",md5_reset_symbol                                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define md5_update_symbol                                0x%X\n",md5_update_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define md5_final_symbol                                 0x%X\n",md5_final_symbol                                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define ss_get_open_psid_symbol                          0x%X\n",ss_get_open_psid_symbol                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define update_mgr_read_eeprom_symbol                    0x%X\n",update_mgr_read_eeprom_symbol                    ); fputs(temp, symbols);
		sprintf(temp, "\t#define update_mgr_write_eeprom_symbol                   0x%X\n",update_mgr_write_eeprom_symbol                   ); fputs(temp, symbols);
		sprintf(temp, "\t#define update_mgr_if_get_token_symbol                   0x%X\n",update_mgr_if_get_token_symbol                   ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define ss_params_get_update_status_symbol               0x%X\n",ss_params_get_update_status_symbol               ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define sm_get_temperature_symbol                        0x%X\n",sm_get_temperature_symbol                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define sm_get_fan_policy_symbol                         0x%X\n",sm_get_fan_policy_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define sm_set_fan_policy_symbol                         0x%X\n",sm_set_fan_policy_symbol                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define sm_get_temperature_patch                         0x%X\n",sm_get_temperature_patch                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define sm_get_fan_policy_patch                          0x%X\n",sm_get_fan_policy_patch                         ); fputs(temp, symbols);
		sprintf(temp, "\t#define sm_set_fan_policy_patch                          0x%X\n",sm_set_fan_policy_patch                         ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define SHA1_init_symbol                                 0x%X\n",SHA1_init_symbol                                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define SHA1_update_symbol                               0x%X\n",SHA1_update_symbol                               ); fputs(temp, symbols);
		sprintf(temp, "\t#define SHA1_final_symbol                                0x%X\n",SHA1_final_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define aescbccfb_dec_symbol                             0x%X\n",aescbccfb_dec_symbol                             ); fputs(temp, symbols);
		sprintf(temp, "\t#define aescbccfb_enc_symbol                             0x%X\n",aescbccfb_enc_symbol                             ); fputs(temp, symbols);
		sprintf(temp, "\t#define get_path_by_fd_symbol                            0x%X\n",get_path_by_fd_symbol                            ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define ECDSA_1                                          0x%X\n",ECDSA_1                                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define ECDSA_2                                          0x%X\n",ECDSA_2                                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define ECDSA_FLAG                                       0x%X\n",OFFSET_2_IDPS - 0x8000000000000000ULL - 0x74     ); fputs(temp, symbols);
		sprintf(temp, "\t#define sysmem_obj                                       0x%X\n",OFFSET_2_IDPS - 0x8000000000000000ULL + 0x144                                       ); fputs(temp, symbols);
		sprintf(temp, "\t#define qa_eeprom_offset                                 0x%X\n",qa_eeprom_offset                                 ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define syscall_table_symbol                             0x%X\n",SYSCALL_TABLE - 0x8000000000000000ULL            ); fputs(temp, symbols);
		sprintf(temp, "\t#define syscall_call_offset                              0x%X\n",syscall_call_offset                              ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define read_bdvd0_symbol                                0x%X\n",read_bdvd0_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define read_bdvd1_symbol                                0x%X\n",read_bdvd1_symbol                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define read_bdvd2_symbol                                0x%X\n",read_bdvd2_symbol                                ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define storage_internal_get_device_object_symbol        0x%X\n",storage_internal_get_device_object_symbol        ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define hid_mgr_read_usb_symbol                          0x%X\n",hid_mgr_read_usb_symbol                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define hid_mgr_read_bt_symbol                           0x%X\n",hid_mgr_read_bt_symbol                           ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define bt_set_controller_info_internal_symbol           0x%X\n",bt_set_controller_info_internal_symbol           ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define device_event_port_send_call                      0x%X\n",device_event_port_send_call                      ); fputs(temp, symbols);
		sprintf(temp, "\t#define device_event_port_send_call_restore              0x%X\n",device_event_port_send_call_restore              ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define ss_pid_call_1                                    0x%X\n",ss_pid_call_1                                    ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define process_map_caller_call                          0x%X\n",process_map_caller_call                          ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define read_module_header_call                          0x%X\n",read_module_header_call                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define read_module_body_call                            0x%X\n",read_module_body_call                            ); fputs(temp, symbols);
		sprintf(temp, "\t#define load_module_by_fd_call1                          0x%X\n",load_module_by_fd_call1                          ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define shutdown_copy_params_call                        0x%X\n",shutdown_copy_params_call                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define shutdown_copy_params_call_restore                0x%X\n",shutdown_copy_params_call_restore                ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define fsloop_open_call                                 0x%X\n",fsloop_open_call                                 ); fputs(temp, symbols);
		sprintf(temp, "\t#define fsloop_close_call                                0x%X\n",fsloop_close_call                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define fsloop_read_call                                 0x%X\n",fsloop_read_call                                 ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define shutdown_patch_offset                            0x%X\n",shutdown_patch_offset                            ); fputs(temp, symbols);
		sprintf(temp, "\t#define module_sdk_version_patch_offset                  0x%X\n",module_sdk_version_patch_offset                  ); fputs(temp, symbols);
		sprintf(temp, "\t#define module_add_parameter_to_parse_sprxpatch_offset   0x%X\n",module_add_parameter_to_parse_sprxpatch_offset   ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define user_thread_prio_patch                           0x%X\n",user_thread_prio_patch                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define user_thread_prio_patch2                          0x%X\n",user_thread_prio_patch2                          ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define lic_patch                                        0x%X\n",lic_patch                                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define lic_patch_restore                                0x%X\n",lic_patch_restore                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define ode_patch                                        0x%X\n",ode_patch                                        ); fputs(temp, symbols);
		sprintf(temp, "\t#define fix_80010009                                     0x%X\n",fix_80010009                                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define fix_8001003D                                     0x%X\n",fix_8001003D                                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define fix_8001003E                                     0x%X\n",fix_8001003E                                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define PATCH_JUMP                                       0x%X\n",PATCH_JUMP                                       ); fputs(temp, symbols);
		
		
		fputs("\n", symbols);	
/* RTOC */		
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
		/*
		if(decrypter_data_entry < 0) {
			sprintf(temp, "\t#define decrypter_data_entry                            -0x%X\n", 0 - decrypter_data_entry); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define decrypter_data_entry                             0x%X\n", decrypter_data_entry); fputs(temp, symbols);
		}
		*/
		fputs("\n", symbols);
		if(storage_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define storage_rtoc_entry_1                            -0x%X\n", 0 - storage_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define storage_rtoc_entry_1                             0x%X\n", storage_rtoc_entry_1); fputs(temp, symbols);
		}
		fputs("\n", symbols);
		if(device_event_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define device_event_rtoc_entry_1                       -0x%X\n", 0 - device_event_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define device_event_rtoc_entry_1                        0x%X\n", device_event_rtoc_entry_1); fputs(temp, symbols);
		}
		fputs("\n", symbols);
		if(time_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define time_rtoc_entry_1                               -0x%X\n", 0 - time_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define time_rtoc_entry_1                                0x%X\n", time_rtoc_entry_1); fputs(temp, symbols);
		}
		if(time_rtoc_entry_2 < 0) {
			sprintf(temp, "\t#define time_rtoc_entry_2                               -0x%X\n", 0 - time_rtoc_entry_2); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define time_rtoc_entry_2                                0x%X\n", time_rtoc_entry_2); fputs(temp, symbols);
		}
		fputs("\n", symbols);
		if(thread_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define thread_rtoc_entry_1                             -0x%X\n", 0 - thread_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define thread_rtoc_entry_1                              0x%X\n", thread_rtoc_entry_1); fputs(temp, symbols);
		}
		fputs("\n", symbols);
		if(process_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define process_rtoc_entry_1                            -0x%X\n", 0 - process_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define process_rtoc_entry_1                             0x%X\n", process_rtoc_entry_1); fputs(temp, symbols);
		}
		fputs("\n", symbols);
		if(bt_rtoc_entry_1 < 0) {
			sprintf(temp, "\t#define bt_rtoc_entry_1                                 -0x%X\n", 0 - bt_rtoc_entry_1); fputs(temp, symbols);
		} else 	{
			sprintf(temp, "\t#define bt_rtoc_entry_1                                  0x%X\n", bt_rtoc_entry_1); fputs(temp, symbols);
		}
		fputs("\n", symbols);
		sprintf(temp, "\t#define permissions_func_symbol                          0x%X\n",permissions_func_symbol                          ); fputs(temp, symbols);
		sprintf(temp, "\t#define permissions_exception1                           0x%X\n",permissions_exception1                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define permissions_exception2                           0x%X\n",permissions_exception2                           ); fputs(temp, symbols);
		sprintf(temp, "\t#define permissions_exception3                           0x%X\n",permissions_exception3                           ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define patch_data1_offset                               0x%X\n",OFFSET_1_IDPS - 0x8000000000000000ULL + 0x10     ); fputs(temp, symbols);
		sprintf(temp, "\t#define patch_func2                                      0x%X\n",patch_func2                                      ); fputs(temp, symbols);
				fputs("\t#define patch_func2_offset                               0x2C\n",symbols);
		sprintf(temp, "\t#define patch_func2_restore                              0x%X\n",patch_func2_restore                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define patch_func8_offset1                              0x%X\n",patch_func8_offset1                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define patch_func8_offset2                              0x%X\n",patch_func8_offset2                              ); fputs(temp, symbols);
		sprintf(temp, "\t#define patch_func8_offset2_restore                      0x%X\n",patch_func8_offset2_restore                      ); fputs(temp, symbols);
		sprintf(temp, "\t#define patch_func9_offset                               0x%X\n",patch_func9_offset                               ); fputs(temp, symbols);
		sprintf(temp, "\t#define mem_base2                                        0x%X\n",mem_base2                                        ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define thread_info_symbol                               0x%X\n",thread_info_symbol                               ); fputs(temp, symbols);
		fputs("\n", symbols);
		sprintf(temp, "\t#define mmapper_flags_temp_patch                         0x%X\n",mmapper_flags_temp_patch                         ); fputs(temp, symbols);
		fputs("\n", symbols);
		//sprintf(temp, "\t#define vsh_patch                                        0x%X\n",vsh_patch                                        ); fputs(temp, symbols);
		//fputs("\n", symbols);
		//sprintf(temp, "\t#define hash_checked_area                                0x%X\n",hash_checked_area                                ); fputs(temp, symbols);
		//fputs("\n", symbols);
		sprintf(temp, "\t#define rsx_syscall_check                                0x%X\n",rsx_syscall_check                                ); fputs(temp, symbols);
		sprintf(temp, "\t#define unk_func2_unregister_service                     0x%X\n",unk_func2_unregister_service                     ); fputs(temp, symbols);
		sprintf(temp, "\t#define unk_func3_unregister_service                     0x%X\n",unk_func3_unregister_service                     ); fputs(temp, symbols);
		fputs("\n", symbols);
		fputs("\t/* lv1 */\n", symbols);
		sprintf(temp, "\t#define vsh_pos_in_ram                                   0x%X\n",vsh_pos_in_ram                         ); fputs(temp, symbols);
		fputs("\n", symbols);
		
// *************
//	PLUGINS FOR MAMBA
// *************
		sprintf(temp2, "flash/%lld%c", FIRMWARE, D);
		if(exist(temp2)) {
			
			sprintf(temp, "\t/* hash */\n", FIRMWARE); fputs(temp, symbols_old);
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/explore_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EXPLORE_PLUGIN_HASH                         0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols_old);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/explore_category_game.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EXPLORE_CATEGORY_GAME_HASH                  0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols_old);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/game_ext_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define GAME_EXT_PLUGIN_HASH                        0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols_old);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libfs.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define LIBFS_EXTERNAL_HASH                         0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols_old);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/psp_emulator.self", FIRMWARE, D);
			sprintf(temp, "\t#define PSP_EMULATOR_HASH                           0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols_old);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/PEmuCoreLib.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define PEMUCORELIB_HASH                            0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols_old);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_api.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EMULATOR_API_HASH                           0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols_old);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_drm.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EMULATOR_DRM_HASH                           0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols_old);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_drm.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EMULATOR_DRM_DATA_HASH                      0x%016llX\n", hash(temp2, 1, 0));
			fputs(temp, symbols_old);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libsysutil_savedata_psp.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x%016llX\n", hash(temp2, 0, 0));
			fputs(temp, symbols_old);

			fputs("\n\t/* lv1 */\n", symbols_old);
			sprintf(temp, "\t#define vsh_pos_in_ram                              0x%X\n", vsh_pos_in_ram); fputs(temp, symbols_old);	
			
			sprintf(temp, "\t/* hash */\n", FIRMWARE); fputs(temp, symbols);
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/vsh.self", FIRMWARE, D);
			sprintf(temp, "\t#define VSH_HASH                                         0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
						
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/explore_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EXPLORE_PLUGIN_HASH                              0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/explore_category_game.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EXPLORE_CATEGORY_GAME_HASH                       0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);		
			
			sprintf(temp2, "flash/%lld%c/dev_flash/ps1emu/ps1_emu.self", FIRMWARE, D);
			sprintf(temp, "\t#define PS1_EMU_HASH                                     0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);		
			
			sprintf(temp2, "flash/%lld%c/dev_flash/ps1emu/ps1_netemu.self", FIRMWARE, D);
			sprintf(temp, "\t#define PS1_NETEMU_HASH                                  0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);		
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/game_ext_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define GAME_EXT_PLUGIN_HASH                             0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libfs.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define LIBFS_EXTERNAL_HASH                              0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/nas_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define NAS_PLUGIN_HASH                                  0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			// DEX firmware doesn't have bdp, rebug use cex files
			sprintf(temp2, "flash/%lldC/dev_flash/vsh/module/bdp_disccheck_plugin.sprx", FIRMWARE);
			sprintf(temp, "\t#define BDP_DISC_CHECK_PLUGIN_HASH                       0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lldC/dev_flash/bdplayer/bdp_BDMV.self", FIRMWARE);
			sprintf(temp, "\t#define BDP_BDMV_HASH                                    0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lldC/dev_flash/bdplayer/bdp_BDVD.self", FIRMWARE);
			sprintf(temp, "\t#define BDP_BDVD_HASH                                    0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/download_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define DOWNLOAD_PLUGIN_HASH                             0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/autodownload_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define AUTODOWNLOAD_PLUGIN_HASH                         0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/premo_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define PREMO_PLUGIN_HASH                                0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/premo_game_plugin.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define PREMO_GAME_PLUGIN_HASH                           0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/basic_plugins.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define BASIC_PLUGINS_HASH                               0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/psp_emulator.self", FIRMWARE, D);
			sprintf(temp, "\t#define PSP_EMULATOR_HASH                                0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/PEmuCoreLib.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define PEMUCORELIB_HASH                                 0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_api.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EMULATOR_API_HASH                                0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_drm.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EMULATOR_DRM_HASH                                0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_drm.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define EMULATOR_DRM_DATA_HASH                           0x%016llX\n", hash(temp2, 1, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libsysutil_savedata_psp.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libaudio.sprx", FIRMWARE, D);
			sprintf(temp, "\t#define LIBAUDIO_HASH                                    0x%016llX\n", hash(temp2, 0, 3));
			fputs(temp, symbols);
			
			u64 dvd_video_region_check_offset=0;
			u8 dvd_video_region_check_offset_flag[]={0x38, 0x60, 0x00, 0x08, 0x88, 0x1E, 0x00, 0x34, 0x7C, 0x00, 0x18, 0x38, 0x7C, 0x00, 0x07, 0x74, 0x7C, 0x00, 0x00, 0x34, 0x54, 0x00, 0xD9, 0x7E, 0x48, 0x00, 0x00, 0x08, 0x38, 0x00, 0x00, 0x00};
			sprintf(temp2, "flash/%lldC/dev_flash/vsh/module/bdp_disccheck_plugin.sprx", FIRMWARE);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					if(compare(-1, (char *) &mem[n], (char *) dvd_video_region_check_offset_flag, sizeof(dvd_video_region_check_offset_flag))) {
						dvd_video_region_check_offset = n;
						break;
					}
				}
				fputs("\n\t/* bdp_disccheck_plugin */\n", symbols);
				sprintf(temp, "\t#define dvd_video_region_check_offset                    0x%X\n", dvd_video_region_check_offset); fputs(temp, symbols);
				
				free(mem);mem=NULL;
			}
			
			u64 ps1_emu_get_region_offset=0;
			u8 ps1_emu_get_region_offset_flag[]={0x60, 0x00, 0x00, 0x00, 0x81, 0x22, 0x81, 0xF0, 0x7C, 0x7D, 0x07, 0xB4, 0x80, 0x62, 0x81, 0xF4};
			sprintf(temp2, "flash/%lld%c/dev_flash/ps1emu/ps1_emu.self", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					if(compare(-1, (char *) &mem[n], (char *) ps1_emu_get_region_offset_flag, sizeof(ps1_emu_get_region_offset_flag))) {
						ps1_emu_get_region_offset = n+8;
						break;
					}
				}
				fputs("\n\t/* ps1_emu */\n", symbols);
				sprintf(temp, "\t#define ps1_emu_get_region_offset                        0x%X\n", ps1_emu_get_region_offset); fputs(temp, symbols);
				
				free(mem);mem=NULL;
			}
			
			u64 ps1_netemu_get_region_offset=0;
			u8 ps1_netemu_get_region_offset_flag[]={0x80, 0x69, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20, 0x81, 0x22, 0x81, 0x74, 0x88, 0x69, 0x00, 0x00};
			sprintf(temp2, "flash/%lld%c/dev_flash/ps1emu/ps1_netemu.self", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					if(compare(-1, (char *) &mem[n], (char *) ps1_netemu_get_region_offset_flag, sizeof(ps1_netemu_get_region_offset_flag))) {
						ps1_netemu_get_region_offset = n;
						break;
					}
				}
				fputs("\n\t/* ps1_netemu */\n", symbols);
				sprintf(temp, "\t#define ps1_netemu_get_region_offset                     0x%X\n", ps1_netemu_get_region_offset); fputs(temp, symbols);
				
				free(mem);mem=NULL;
			}
		
			u64 vsh_text_size=0;
			u8 vsh_text_size_flag[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF};
			
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
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/vsh.self", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
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
					if(compare(-1, (char *) &mem[n], (char *) vsh_text_size_flag, sizeof(vsh_text_size_flag))) {
						if(!((n+0x10) % 0x10000)) vsh_text_size = n+0x10;
					}
					
					if(vsh_text_size)
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
				
				free(mem);mem=NULL;
			}
			
			fputs("\n\t/* vsh */\n", symbols_old);
			sprintf(temp, "\t#define ps2tonet_patch                              0x%X\n", ps2tonet_patch); fputs(temp, symbols_old);
			sprintf(temp, "\t#define ps2tonet_size_patch                         0x%X\n", ps2tonet_size_patch); fputs(temp, symbols_old);
			sprintf(temp, "\t#define vmode_patch_offset                          0x%X\n", vmode_patch_offset); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch1                              0x%X\n", psp_drm_patch1); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch2                              0x%X\n", psp_drm_patch2); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch3                              0x%X\n", psp_drm_patch3); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch4                              0x%X\n", psp_drm_patch4); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patchA                              0x%X\n", psp_drm_patchA); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patchB                              0x%X\n", psp_drm_patchB); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patchC                              0x%X\n", psp_drm_patchC); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patchD                              0x%X\n", psp_drm_patchD); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patchE                              0x%X\n", psp_drm_patchE); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patchF                              0x%X\n", psp_drm_patchF); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_extra_drm_patch                         0x%X\n", psp_extra_drm_patch); fputs(temp, symbols_old);
			
			fputs("\n\t/* vsh */\n", symbols);
			sprintf(temp, "\t#define vsh_text_size                                    0x%X\n", vsh_text_size); fputs(temp, symbols);
			sprintf(temp, "\t#define ps2tonet_patch                                   0x%X\n", ps2tonet_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define ps2tonet_size_patch                              0x%X\n", ps2tonet_size_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define vmode_patch_offset                               0x%X\n", vmode_patch_offset); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch1                                   0x%X\n", psp_drm_patch1); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch2                                   0x%X\n", psp_drm_patch2); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch3                                   0x%X\n", psp_drm_patch3); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch4                                   0x%X\n", psp_drm_patch4); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchA                                   0x%X\n", psp_drm_patchA); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchB                                   0x%X\n", psp_drm_patchB); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchC                                   0x%X\n", psp_drm_patchC); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchD                                   0x%X\n", psp_drm_patchD); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchE                                   0x%X\n", psp_drm_patchE); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patchF                                   0x%X\n", psp_drm_patchF); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_extra_drm_patch                              0x%X\n", psp_extra_drm_patch); fputs(temp, symbols);
			
			
			fputs("\n\t/* explore_plugin */\n", symbols_old);
			fputs("\n\t/* explore_plugin */\n", symbols);
			
			u64 app_home_offset=0;
			char app_home_offset_flag[]="/app_home/PS3_GAME\0";
			
			//u64 whatsnew_offset=0;
			//u8 whatsnew_offset_flag[]={};
			
			u64 ps2_nonbw_offset=0;
			u8 ps2_nonbw_offset_FLAG[0x10] = {0x7D, 0x2B, 0x02, 0x14, 0x80, 0x89, 0x00, 0x30, 0x48, 0x00, 0x00, 0x08, 0x38, 0xA0, 0x00, 0x00}; //+4
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/explore_plugin.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset_FLAG, 0xC)) 
					{
						ps2_nonbw_offset = n + 4;
					}
					if(compare(-1, (char *) &mem[n], (char *) app_home_offset_flag, sizeof(app_home_offset_flag))) {
						app_home_offset = n;
					}
					/*
					if(compare(-1, (char *) &mem[n], (char *) whatsnew_offset_flag, sizeof(whatsnew_offset_flag))) {
						whatsnew_offset = n;
					}
					if(whatsnew_offset)
					*/
					if(app_home_offset)
					if(ps2_nonbw_offset)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define ps2_nonbw_offset                            0x%X\n", ps2_nonbw_offset); fputs(temp, symbols_old);
			
			sprintf(temp, "\t#define ps2_nonbw_offset                                 0x%X\n", ps2_nonbw_offset); fputs(temp, symbols);
			sprintf(temp, "\t#define app_home_offset                                  0x%X\n", app_home_offset); fputs(temp, symbols);
			//sprintf(temp, "\t#define whatsnew_offset                                  0x%X\n", whatsnew_offset); fputs(temp, symbols);
			
			fputs("\n\t/* explore_category_game */\n", symbols_old);
			fputs("\n\t/* explore_category_game */\n", symbols);
			u64 ps2_nonbw_offset2=0;
			u8 ps2_nonbw_offset2_FLAG[0x10] = {0x7D, 0x2B, 0x02, 0x14, 0x80, 0x89, 0x00, 0x30, 0x48, 0x00, 0x00, 0x08, 0x38, 0xA0, 0x00, 0x00}; // +4
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/explore_category_game.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset2_FLAG, 0x10)) 
					{
						ps2_nonbw_offset2 = n + 4;
					}
					
					if(ps2_nonbw_offset2)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define ps2_nonbw_offset2                           0x%X\n", ps2_nonbw_offset2); fputs(temp, symbols_old);
			sprintf(temp, "\t#define ps2_nonbw_offset2                                0x%X\n", ps2_nonbw_offset2); fputs(temp, symbols);
			
			fputs("\n\t/* game_ext_plugin */\n", symbols_old);
			fputs("\n\t/* game_ext_plugin */\n", symbols);
			
			u64 sfo_check_offset=0;
			u64 ps_region_error_offset=0;
			u64 remote_play_offset=0;
			u64 ps2_nonbw_offset3=0;
			
			u8 sfo_check_offset_flag[]={0x7C, 0x7E, 0x1B, 0x78, 0x7F, 0x03, 0xF8, 0x00, 0x80, 0x09, 0xAA, 0xAA, 0x2F, 0x80, 0x00, 0x06, 0xAA, 0xAA, 0xAA, 0xAA, 0x40, 0x9A, 0x00, 0x3C};
			u8 ps_region_error_offset_flag[]={0x60, 0x00, 0x00, 0x40, 0x90, 0x09, 0x02, 0x48, 0x3D, 0x20, 0x00, 0x05};
			u8 remote_play_offset_flag[]={0x7F, 0xA3, 0x07, 0xB4, 0x7F, 0xE4, 0x07, 0xB4, 0x4B, 0xAA, 0xAA, 0xAA, 0xE8, 0x01, 0x00, 0xE0, 0x7C, 0x63, 0x07, 0xB4, 0x81, 0x81, 0x00, 0xD8, 0xEB, 0x81, 0x00, 0xB0, 0x7C, 0x08, 0x03, 0xA6};
			u8 ps2_nonbw_offset3_FLAG[] = {0x38, 0x61, 0x00, 0x70, 0x2F, 0x9F, 0x00, 0x00, 0x41, 0x9C, 0x00, 0x58, 0x38, 0x00, 0x00, 0x70};
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/game_ext_plugin.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(compare(0xAA, (char *) &mem[n], (char *) sfo_check_offset_flag, sizeof(sfo_check_offset_flag))) {
						sfo_check_offset = n+0x10;
					}
					if(compare(-1, (char *) &mem[n], (char *) ps_region_error_offset_flag, sizeof(ps_region_error_offset_flag))) {
						ps_region_error_offset = n;
					}
					if(compare(0xAA, (char *) &mem[n], (char *) remote_play_offset_flag, sizeof(remote_play_offset_flag))) {
						remote_play_offset = n;
					}
					if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset3_FLAG, 0x10)) 
					{
						ps2_nonbw_offset3 = n;
					}
					if(sfo_check_offset)
					if(ps_region_error_offset)
					if(remote_play_offset)
					if(ps2_nonbw_offset3)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define ps2_nonbw_offset3                           0x%X\n", ps2_nonbw_offset3); fputs(temp, symbols_old);
			
			sprintf(temp, "\t#define sfo_check_offset                                 0x%X\n", sfo_check_offset); fputs(temp, symbols);
			sprintf(temp, "\t#define ps_region_error_offset                           0x%X\n", ps_region_error_offset); fputs(temp, symbols);
			sprintf(temp, "\t#define remote_play_offset                               0x%X\n", remote_play_offset); fputs(temp, symbols);
			sprintf(temp, "\t#define ps2_nonbw_offset3                                0x%X\n", ps2_nonbw_offset3); fputs(temp, symbols);
			
			
			fputs("\n\t/* premo_plugin */\n", symbols);
			
			u64 pcremote_play_offset1=0;
			u8 pcremote_play_offset1_flag[]={0x7C, 0x08, 0x03, 0xA6, 0x4E, 0x80, 0x00, 0x20, 0x38, 0x80, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0x39, 0x60, 0x00, 0x7A, 0xF8, 0x01, 0x00, 0x10, 0x80, 0x63, 0x00, 0x08, 0x44, 0x00, 0x00, 0x02};
		
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/premo_plugin.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(compare(-1, (char *) &mem[n], (char *) pcremote_play_offset1_flag, sizeof(pcremote_play_offset1_flag))) {
						pcremote_play_offset1 = n;
					}
					
					if(pcremote_play_offset1)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define pcremote_play_offset1                            0x%X\n", pcremote_play_offset1); fputs(temp, symbols);
			
			fputs("\n\t/* premo_game_plugin */\n", symbols);
			
			u64 pcremote_play_offset2=0;
			u8 pcremote_play_offset2_flag[]={0x7C, 0x08, 0x03, 0xA6, 0x4E, 0x80, 0x00, 0x20, 0x38, 0x80, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0x39, 0x60, 0x00, 0x7A, 0xF8, 0x01, 0x00, 0x10, 0x80, 0x63, 0x00, 0x08, 0x44, 0x00, 0x00, 0x02};
		
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/premo_game_plugin.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(compare(-1, (char *) &mem[n], (char *) pcremote_play_offset2_flag, sizeof(pcremote_play_offset2_flag))) {
						pcremote_play_offset2 = n;
					}
					
					if(pcremote_play_offset2)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define pcremote_play_offset2                            0x%X\n", pcremote_play_offset2); fputs(temp, symbols);
			
			
			fputs("\n\t/* nas_plugin */\n", symbols);
			
			u64 patch1_nas=0;
			u64 patch2_nas=0;
			u64 patch3_nas=0;
		
			u8 patch1_nas_flag[]={0x2F, 0x83, 0x00, 0x00, 0x90, 0x7F, 0x01, 0x90, 0x40, 0x9E, 0x09, 0xB8, 0x38, 0x61, 0x00, 0x74};
			u8 patch2_nas_flag[]={0x61, 0x29, 0x0D, 0x2C, 0x61, 0x6B, 0x8D, 0x70, 0x61, 0x4A, 0xE6, 0x2B, 0x90, 0x7B, 0x00, 0xF0};
			u8 patch3_nas_flag[]={0x2F, 0x9F, 0x00, 0x0D, 0x40, 0x9E, 0x00, 0x34};
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/nas_plugin.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(compare(-1, (char *) &mem[n], (char *) patch1_nas_flag, sizeof(patch1_nas_flag))) {
						patch1_nas = n;
					}
					if(compare(-1, (char *) &mem[n], (char *) patch2_nas_flag, sizeof(patch2_nas_flag))) {
						patch2_nas = n;
					}
					if(compare(-1, (char *) &mem[n], (char *) patch3_nas_flag, sizeof(patch3_nas_flag))) {
						patch3_nas = n+4;
					}
					
					if(patch1_nas)
					if(patch2_nas)
					if(patch3_nas)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define patch1_nas                                       0x%X\n", patch1_nas); fputs(temp, symbols);
			sprintf(temp, "\t#define patch2_nas                                       0x%X\n", patch2_nas); fputs(temp, symbols);
			sprintf(temp, "\t#define patch3_nas                                       0x%X\n", patch3_nas); fputs(temp, symbols);
			
			
			fputs("\n\t/* basic_plugins */\n", symbols);
			
			u64 ps1emu_type_check_offset=0;
			u64 pspemu_path_offset=0;
			u64 psptrans_path_offset=0;
		
			u8 ps1emu_type_check_offset_flag[]={0x48, 0xAA, 0xAA, 0xAA, 0xE8, 0x01, 0x00, 0xB0, 0xEB, 0x81, 0x00, 0x80, 0x7F, 0x63, 0x07, 0xB4, 0xEB, 0xA1, 0x00, 0x88};
			char pspemu_path_offset_flag[]="/dev_flash/pspemu/psp_emulator.self";
			char psptrans_path_offset_flag[]="/dev_flash/pspemu/psp_translator.self";
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/basic_plugins.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(compare(0xAA, (char *) &mem[n], (char *) ps1emu_type_check_offset_flag, sizeof(ps1emu_type_check_offset_flag))) {
						ps1emu_type_check_offset = n;
					}
					if(compare(-1, (char *) &mem[n], (char *) pspemu_path_offset_flag, sizeof(pspemu_path_offset_flag))) {
						pspemu_path_offset = n;
					}
					if(compare(-1, (char *) &mem[n], (char *) psptrans_path_offset_flag, sizeof(psptrans_path_offset_flag))) {
						psptrans_path_offset = n;
					}
					
					if(ps1emu_type_check_offset)
					if(pspemu_path_offset)
					if(psptrans_path_offset)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define ps1emu_type_check_offset                         0x%X\n", ps1emu_type_check_offset); fputs(temp, symbols);
			sprintf(temp, "\t#define pspemu_path_offset                               0x%X\n", pspemu_path_offset); fputs(temp, symbols);
			sprintf(temp, "\t#define psptrans_path_offset                             0x%X\n", psptrans_path_offset); fputs(temp, symbols);
		
			fputs("\n\t/* download_plugin */\n", symbols);
			
			u64 elf_patch1_download=0;
			u64 elf_patch2_download=0;
			//https://www.psx-place.com/threads/updates-post-your-favorite-cfw-patches.23904/page-4#post-177219
			u64 elf_patch3_download=0;
			u64 elf_patch4_download=0;
			u64 elf_patch5_download=0;
			u64 elf_patch6_download=0;
			
			u8 elf_patch1_download_flag[]={0x2F, 0x83, 0x00, 0x00, 0x90, 0x7F, 0x01, 0x90, 0x40, 0x9E, 0x09, 0xD0, 0x38, 0x61, 0x00, 0x70};
			u8 elf_patch3_download_flag[]={0x2F, 0x64, 0x65, 0x76, 0x5F, 0x68, 0x64, 0x64, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x61, 0x6D, 0x65, 0x5F, 0x65, 0x78, 0x74, 0x5F, 0x70, 0x6C, 0x75, 0x67, 0x69, 0x6E, 0x00};
			u8 elf_patch4_download_flag[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x6B, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00};
			char elf_patch6_download_flag[]="application/x-psp-update";
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/download_plugin.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(compare(-1, (char *) &mem[n], (char *) elf_patch1_download_flag, sizeof(elf_patch1_download_flag))) {
						elf_patch1_download = n+0x4;
						elf_patch2_download = n+0xC;
					}
					if(compare(-1, (char *) &mem[n], (char *) elf_patch3_download_flag, sizeof(elf_patch3_download_flag))) {
						elf_patch3_download = n+0x8;
					}
					if(compare(-1, (char *) &mem[n], (char *) elf_patch4_download_flag, sizeof(elf_patch4_download_flag))) {
						elf_patch4_download = n+0x8;
						elf_patch5_download = n+0x28;
					}
					if(compare(-1, (char *) &mem[n], (char *) elf_patch6_download_flag, sizeof(elf_patch6_download_flag))) {
						elf_patch6_download = n;
					}
					if(elf_patch1_download)
					if(elf_patch2_download)
					if(elf_patch3_download)
					if(elf_patch4_download)
					if(elf_patch5_download)
					if(elf_patch6_download)
					break;
				}
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define elf_patch1_download                              0x%X\n", elf_patch1_download); fputs(temp, symbols);	
			sprintf(temp, "\t#define elf_patch2_download                              0x%X\n", elf_patch2_download); fputs(temp, symbols);	
			sprintf(temp, "\t#define elf_patch3_download                              0x%X\n", elf_patch3_download); fputs(temp, symbols);	
			sprintf(temp, "\t#define elf_patch4_download                              0x%X\n", elf_patch4_download); fputs(temp, symbols);	
			sprintf(temp, "\t#define elf_patch5_download                              0x%X\n", elf_patch5_download); fputs(temp, symbols);	
			sprintf(temp, "\t#define elf_patch6_download                              0x%X\n", elf_patch6_download); fputs(temp, symbols);	
			
			fputs("\n\t/* autodownload_plugin */\n", symbols);
			
			u64 elf_patch1_autodownload=0;
			u64 elf_patch2_autodownload=0;
			
			u8 elf_patch1_autodownload_flag[]={0x90, 0x7F, 0x01, 0x90, 0x40, 0x9E, 0x09, 0xD0, 0x38, 0x61, 0x00, 0x70};
			
			sprintf(temp2, "flash/%lld%c/dev_flash/vsh/module/autodownload_plugin.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(compare(-1, (char *) &mem[n], (char *) elf_patch1_autodownload_flag, sizeof(elf_patch1_autodownload_flag))) {
						elf_patch1_autodownload = n;
						elf_patch2_autodownload = n+8;
					}
				
					if(elf_patch1_autodownload)
					if(elf_patch2_autodownload)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define elf_patch1_autodownload                          0x%X\n", elf_patch1_autodownload); fputs(temp, symbols);	
			sprintf(temp, "\t#define elf_patch2_autodownload                          0x%X\n", elf_patch2_autodownload); fputs(temp, symbols);	
			
			
			u64 bdp_cinavia_patch=0;
			u64 bdp_cinavia1_patch=0;
			
			u8 bdp_cinavia_patch_flag[]={0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xE1, 0x00, 0x70, 0xF8, 0x01, 0x00, 0x90, 0x4B, 0xFF, 0xFF, 0x81, 0xE8, 0x01, 0x00, 0x90, 0x78, 0x63, 0x00, 0x20, 0xEB, 0xE1, 0x00, 0x70};
			u8 bdp_cinavia1_patch_flag[]={0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x00, 0x90, 0x4B, 0xFF, 0xFF, 0x59, 0x38, 0x00, 0x00, 0x01, 0x98, 0x03, 0x00, 0x08, 0xE8, 0x01, 0x00, 0x90, 0x38, 0x21, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6};
			
			sprintf(temp2, "flash/%lldC/dev_flash/bdplayer/bdp_BDVD.self", FIRMWARE);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				fputs("\n\t/* bdp_BDVD */\n", symbols);
			
				for(n=0; n<size ; n++) {
					
					if(compare(-1, (char *) &mem[n], (char *) bdp_cinavia_patch_flag, sizeof(bdp_cinavia_patch_flag))) {
						bdp_cinavia_patch = n-4;
					}
					if(compare(-1, (char *) &mem[n], (char *) bdp_cinavia1_patch_flag, sizeof(bdp_cinavia1_patch_flag))) {
						bdp_cinavia1_patch = n-4;
					}
						
					if(bdp_cinavia_patch)
					if(bdp_cinavia1_patch)
					break;	
				}
				free(mem);mem=NULL;
			
				sprintf(temp, "\t#define bdp_cinavia_patch                                0x%X\n", bdp_cinavia_patch); fputs(temp, symbols);	
				sprintf(temp, "\t#define bdp_cinavia1_patch                               0x%X\n", bdp_cinavia1_patch); fputs(temp, symbols);			
			}
			
			fputs("\n\t/* psp_emulator */\n", symbols_old);
			fputs("\n\t/* psp_emulator */\n", symbols);
			u64 psp_set_psp_mode_offset=0;
			u8 psp_set_psp_mode_offset_FLAG[0x10] = {0x38, 0x80, 0x00, 0x01, 0x38, 0x60, 0x00, 0x05, 0x78, 0x84, 0x07, 0xC6, 0x64, 0x84, 0x00, 0x01};
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/psp_emulator.self", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
				for(n=0; n<size ; n++) {
					
					if(!memcmp((char *) &mem[n], (char *) psp_set_psp_mode_offset_FLAG, 0x10)) 
					{
						psp_set_psp_mode_offset = n;
					}
					
					if(psp_set_psp_mode_offset)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define psp_set_psp_mode_offset                          0x%X\n", psp_set_psp_mode_offset); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_set_psp_mode_offset                          0x%X\n", psp_set_psp_mode_offset); fputs(temp, symbols);
			
			fputs("\n\t/* emulator_api */\n", symbols_old);
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
						
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_api.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
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
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define psp_read                                    0x%X\n", psp_read); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_read_header                             0x%X\n", psp_read_header); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch5                              0x%X\n", psp_drm_patch5); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch6                              0x%X\n", psp_drm_patch6); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch7                              0x%X\n", psp_drm_patch7); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch8                              0x%X\n", psp_drm_patch8); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch9                              0x%X\n", psp_drm_patch9); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch11                             0x%X\n", psp_drm_patch11); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_patch12                             0x%X\n", psp_drm_patch12); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_product_id_patch1                       0x%X\n", psp_product_id_patch1); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_product_id_patch3                       0x%X\n", psp_product_id_patch3); fputs(temp, symbols_old);
			
			fputs("\n\t/* pemucorelib */\n", symbols_old);
			
			sprintf(temp, "\t#define psp_read                                         0x%X\n", psp_read); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_read_header                                  0x%X\n", psp_read_header); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch5                                   0x%X\n", psp_drm_patch5); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch6                                   0x%X\n", psp_drm_patch6); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch7                                   0x%X\n", psp_drm_patch7); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch8                                   0x%X\n", psp_drm_patch8); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch9                                   0x%X\n", psp_drm_patch9); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch11                                  0x%X\n", psp_drm_patch11); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_patch12                                  0x%X\n", psp_drm_patch12); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_product_id_patch1                            0x%X\n", psp_product_id_patch1); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_product_id_patch3                            0x%X\n", psp_product_id_patch3); fputs(temp, symbols);
			
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
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/PEmuCoreLib.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
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
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define psp_eboot_dec_patch                         0x%X\n", psp_eboot_dec_patch); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_prx_patch                               0x%X\n", psp_prx_patch); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_savedata_bind_patch1                    0x%X\n", psp_savedata_bind_patch1); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_savedata_bind_patch2                    0x%X\n", psp_savedata_bind_patch2); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_savedata_bind_patch3                    0x%X\n", psp_savedata_bind_patch3); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_extra_savedata_patch                    0x%X\n", psp_extra_savedata_patch); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_prometheus_patch                        0x%X\n", psp_prometheus_patch); fputs(temp, symbols_old);
			sprintf(temp, "\t#define prx_patch_call_lr                           0x%X\n", prx_patch_call_lr); fputs(temp, symbols_old);
			
			fputs("\n\t/* emulator_drm */\n", symbols_old);
			
			sprintf(temp, "\t#define psp_eboot_dec_patch                              0x%X\n", psp_eboot_dec_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_prx_patch                                    0x%X\n", psp_prx_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_bind_patch1                         0x%X\n", psp_savedata_bind_patch1); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_bind_patch2                         0x%X\n", psp_savedata_bind_patch2); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_bind_patch3                         0x%X\n", psp_savedata_bind_patch3); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_extra_savedata_patch                         0x%X\n", psp_extra_savedata_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_prometheus_patch                             0x%X\n", psp_prometheus_patch); fputs(temp, symbols);
			sprintf(temp, "\t#define prx_patch_call_lr                                0x%X\n", prx_patch_call_lr); fputs(temp, symbols);
			
			fputs("\n\t/* emulator_drm */\n", symbols);
			
			u64 psp_drm_tag_overwrite=0;
			u8 psp_drm_tag_overwrite_FLAG[0x10] = {0x39, 0x00, 0x00, 0x00, 0x7D, 0x3E, 0x52, 0x14, 0x39, 0x4A, 0x00, 0x01, 0x7D, 0x29, 0x5A, 0x14};
			
			u64 psp_drm_key_overwrite=0;
			u8 psp_drm_key_overwrite_FLAG[4] = {0x00, 0x00, 0xBC, 0xC0};
			
			sprintf(temp2, "flash/%lld%c/dev_flash/pspemu/release/emulator_drm.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {		
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
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define psp_drm_tag_overwrite                            0x%X\n", psp_drm_tag_overwrite); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_drm_key_overwrite                            (0x%X - 0xBE80)\n", psp_drm_key_overwrite); fputs(temp, symbols_old);

			fputs("\n\t/* libsysutil_savedata_psp */\n", symbols_old);
			
			sprintf(temp, "\t#define psp_drm_tag_overwrite                            0x%X\n", psp_drm_tag_overwrite); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_drm_key_overwrite                            (0x%X - 0xBE80)\n", psp_drm_key_overwrite); fputs(temp, symbols);

			fputs("\n\t/* libsysutil_savedata_psp */\n", symbols);
			
			u64 psp_savedata_patch1=0;
			u8 psp_savedata_patch1_FLAG[] = {0xEA, 0xC1, 0x08, 0xE0, 0xEA, 0xE1, 0x08, 0xE8, 0xEB, 0x01, 0x08, 0xF0, 0xEB, 0x21, 0x08, 0xF8};
			
			u64 psp_savedata_patch2=0;
			u8 psp_savedata_patch2_FLAG[] = {0xE9, 0xC1, 0x08, 0xA0, 0xE9, 0xE1, 0x08, 0xA8, 0x7C, 0x08, 0x03, 0xA6, 0xEA, 0x01, 0x08, 0xB0};
			
			u64 psp_savedata_patch3=0;
			u8 psp_savedata_patch3_FLAG[] = {0xE9, 0x01, 0x08, 0x88, 0xE8, 0xA1, 0x08, 0x80, 0x7E, 0x83, 0xA3, 0x78, 0x7F, 0x04, 0xC3, 0x78};
			
			u64 psp_savedata_patch4=0;
			u8 psp_savedata_patch4_FLAG[] = {0x78, 0x1C, 0x00, 0x20, 0x80, 0x01, 0x09, 0xA4, 0x79, 0x3D, 0x00, 0x20, 0x2F, 0x80, 0x00, 0x00};
			
			u64 psp_savedata_patch5=0;
			u8 psp_savedata_patch5_FLAG[] = {0x38, 0xC0, 0x00, 0x14, 0x90, 0x1C, 0x00, 0x10, 0xF8, 0x1D, 0x00, 0x00, 0x92, 0x21, 0x00, 0xB8};
			
			u64 psp_savedata_patch6=0;
			u8 psp_savedata_patch6_FLAG[] = {0xEA, 0x21, 0x08, 0xB8, 0xEA, 0x41, 0x08, 0xC0, 0xEA, 0x61, 0x08, 0xC8, 0xEA, 0x81, 0x08, 0xD0};
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libsysutil_savedata_psp.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				
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
						psp_savedata_patch3 = n - 4;
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
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define psp_savedata_patch1                         0x%X\n", psp_savedata_patch1); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_savedata_patch2                         0x%X\n", psp_savedata_patch2); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_savedata_patch3                         0x%X\n", psp_savedata_patch3); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_savedata_patch4                         0x%X\n", psp_savedata_patch4); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_savedata_patch5                         0x%X\n", psp_savedata_patch5); fputs(temp, symbols_old);
			sprintf(temp, "\t#define psp_savedata_patch6                         0x%X\n", psp_savedata_patch6); fputs(temp, symbols_old);

			fputs("\n\t/* libfs */\n", symbols_old);
			
			sprintf(temp, "\t#define psp_savedata_patch1                              0x%X\n", psp_savedata_patch1); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch2                              0x%X\n", psp_savedata_patch2); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch3                              0x%X\n", psp_savedata_patch3); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch4                              0x%X\n", psp_savedata_patch4); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch5                              0x%X\n", psp_savedata_patch5); fputs(temp, symbols);
			sprintf(temp, "\t#define psp_savedata_patch6                              0x%X\n", psp_savedata_patch6); fputs(temp, symbols);

			fputs("\n\t/* libfs */\n", symbols);
			
			u64 aio_copy_root_offset=0;
			u8 aio_copy_root_offset_FLAG[] = {0x78, 0x84, 0x04, 0x20, 0x4B, 0xFF, 0xB1, 0x74, 0x38, 0x80, 0xFF, 0xFF, 0x38, 0x60, 0x00, 0x01};
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libfs.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {			
				for(n=0; n<size ; n++) {
					if(!memcmp((char *) &mem[n], (char *) aio_copy_root_offset_FLAG, 0x10))
					{
						aio_copy_root_offset = n;
					}
					if(aio_copy_root_offset)
					break;
				}
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define aio_copy_root_offset                        0x%X\n", aio_copy_root_offset); fputs(temp, symbols_old);
			
			sprintf(temp, "\t#define aio_copy_root_offset                             0x%X\n", aio_copy_root_offset); fputs(temp, symbols);
			
			fputs("\n\t/* libaudio */\n", symbols);
			//https://blog.madnation.net/ps3-bt-usb-audio-passthrough/
			u64 bt_usb_audio_offset=0;
			u8 bt_usb_audio_offset_flag[] = {0xE8, 0x03, 0x00, 0x00, 0x2F, 0xA0, 0x00, 0x00, 0x41, 0x9E, 0x00, 0x0C, 0x2F, 0xA0, 0x00, 0x02, 0x40, 0x9E, 0x01, 0x44, 0xE8, 0x7E, 0x00, 0x08, 0x2F, 0xA3, 0x00, 0x02, 0x41, 0x9E, 0x00, 0x1C};
			
			sprintf(temp2, "flash/%lld%c/dev_flash/sys/external/libaudio.sprx", FIRMWARE, D);
			Extract(temp2);
			
			mem = LoadFile("temp_dec",&size);
			system("del temp_dec");
			if(mem!=NULL) {
				for(n=0; n<size ; n++) {
					if(compare(-1, (char *) &mem[n], (char *) bt_usb_audio_offset_flag, sizeof(bt_usb_audio_offset_flag))) {
						bt_usb_audio_offset = n;
					}
					if(bt_usb_audio_offset)
					break;
				}
				
				free(mem);mem=NULL;
			}
			sprintf(temp, "\t#define bt_usb_audio_offset                         0x%X\n", bt_usb_audio_offset); fputs(temp, symbols_old);
			
			sprintf(temp, "\t#define bt_usb_audio_offset                              0x%X\n", bt_usb_audio_offset); fputs(temp, symbols);
			
			char temp3[64];
			
			if(D=='C') {
				sprintf(temp3, "flash/%lldD/dev_flash", FIRMWARE);
			} else
			if(D=='D') {
				sprintf(temp3, "flash/%lldC/dev_flash", FIRMWARE);
			}
			
			if(exist(temp3)) {
				// ONLY for CEX! because rebug use only DEX modules.
				// https://www.psx-place.com/threads/4-84-cfw-homebrew-plugins-tools.22528/page-10#post-164287
				if(D=='C') {
					fputs("\n\t/* DEX */\n", symbols_old);
					fputs("\n\t/* DEX */\n", symbols);
					
					char temp_rebug[512];
					sprintf(temp_rebug, "flash/%lld%c/dev_flash_rebug", FIRMWARE, D);
					
					if( !exist(temp_rebug) ) {
						sprintf(temp_rebug, "flash/%lldD/dev_flash", FIRMWARE);
					}
					
					if(exist(temp_rebug)) {
						sprintf(temp2, "%s/vsh/module/explore_plugin.sprx", temp_rebug);
						sprintf(temp, "\t#define EXPLORE_PLUGIN_REBUG_HASH                   0x%016llX\n", hash(temp2, 0, 0)); fputs(temp, symbols_old);
						sprintf(temp, "\t#define EXPLORE_PLUGIN_REBUG_HASH                        0x%016llX\n", hash(temp2, 0, 3)); fputs(temp, symbols);
						
						
						sprintf(temp2, "%s/vsh/module/explore_category_game.sprx", temp_rebug);
						sprintf(temp, "\t#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x%016llX\n", hash(temp2, 0, 0)); fputs(temp, symbols_old);
						sprintf(temp, "\t#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0x%016llX\n", hash(temp2, 0, 3)); fputs(temp, symbols);
						
						sprintf(temp2, "%s/vsh/module/game_ext_plugin.sprx", temp_rebug);
						sprintf(temp, "\t#define GAME_EXT_PLUGIN_REBUG_HASH                  0x%016llX\n", hash(temp2, 0, 0)); fputs(temp, symbols_old);
						sprintf(temp, "\t#define GAME_EXT_PLUGIN_REBUG_HASH                       0x%016llX\n", hash(temp2, 0, 3)); fputs(temp, symbols);
					}
				} 
				else {
					fputs("\n\t/* CEX */\n", symbols_old);
					fputs("\n\t/* CEX */\n", symbols);
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
				
				sprintf(temp2, "%s/vsh/module/vsh.self", temp3);
				Extract(temp2);
							
				mem = LoadFile("temp_dec",&size);
				system("del temp_dec");
				if(mem!=NULL) {
					
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
					
					free(mem);mem=NULL;
				}
				
				ps2_nonbw_offset=0;
				sprintf(temp2, "%s/vsh/module/explore_plugin.sprx", temp3);
				Extract(temp2);
				
				mem = LoadFile("temp_dec",&size);
				system("del temp_dec");
				if(mem!=NULL) {
						
					for(n=0; n<size ; n++) {
						
						if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset_FLAG, 0xC)) 
						{
							ps2_nonbw_offset = n + 4;
						}
						
						if(ps2_nonbw_offset)
						break;
					}
					
					free(mem);mem=NULL;
				}

				ps2_nonbw_offset2=0;
				
				sprintf(temp2, "%s/vsh/module/explore_category_game.sprx", temp3);
				Extract(temp2);
				
				mem = LoadFile("temp_dec",&size);
				system("del temp_dec");
				if(mem!=NULL) {
					
					for(n=0; n<size ; n++) {
						
						if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset2_FLAG, 0x10)) 
						{
							ps2_nonbw_offset2 = n + 4;
						}
						
						if(ps2_nonbw_offset2)
						break;
					}
					
					free(mem);mem=NULL;
				}
				
				ps2_nonbw_offset3=0;
				sprintf(temp2, "%s/vsh/module/game_ext_plugin.sprx", temp3);
				Extract(temp2);
				
				mem = LoadFile("temp_dec",&size);
				system("del temp_dec");
				if(mem!=NULL) {
					
					for(n=0; n<size ; n++) {
						
						if(!memcmp((char *) &mem[n], (char *) ps2_nonbw_offset3_FLAG, 0x10)) 
						{
							ps2_nonbw_offset3 = n;
						}
						
						if(ps2_nonbw_offset3)
						break;
					}
					
					free(mem);mem=NULL;
				}
				
				if(D=='C') {
					sprintf(temp, "\t#define dex_ps2_nonbw_offset                        0x%X\n", ps2_nonbw_offset); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_ps2_nonbw_offset2                       0x%X\n", ps2_nonbw_offset2); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_ps2_nonbw_offset3                       0x%X\n", ps2_nonbw_offset3); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_ps2tonet_patch                          0x%X\n", ps2tonet_patch); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_ps2tonet_size_patch                     0x%X\n", ps2tonet_size_patch); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_vmode_patch_offset                      0x%X\n", vmode_patch_offset); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patch1                          0x%X\n", psp_drm_patch1); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patch2                          0x%X\n", psp_drm_patch2); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patch3                          0x%X\n", psp_drm_patch3); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patch4                          0x%X\n", psp_drm_patch4); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patchA                          0x%X\n", psp_drm_patchA); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patchB                          0x%X\n", psp_drm_patchB); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patchC                          0x%X\n", psp_drm_patchC); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patchD                          0x%X\n", psp_drm_patchD); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patchE                          0x%X\n", psp_drm_patchE); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_drm_patchF                          0x%X\n", psp_drm_patchF); fputs(temp, symbols_old);
					sprintf(temp, "\t#define dex_psp_extra_drm_patch                     0x%X\n", psp_extra_drm_patch); fputs(temp, symbols_old);
					
					sprintf(temp, "\t#define dex_ps2_nonbw_offset                             0x%X\n", ps2_nonbw_offset); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_ps2_nonbw_offset2                            0x%X\n", ps2_nonbw_offset2); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_ps2_nonbw_offset3                            0x%X\n", ps2_nonbw_offset3); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_ps2tonet_patch                               0x%X\n", ps2tonet_patch); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_ps2tonet_size_patch                          0x%X\n", ps2tonet_size_patch); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_vmode_patch_offset                           0x%X\n", vmode_patch_offset); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patch1                               0x%X\n", psp_drm_patch1); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patch2                               0x%X\n", psp_drm_patch2); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patch3                               0x%X\n", psp_drm_patch3); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patch4                               0x%X\n", psp_drm_patch4); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchA                               0x%X\n", psp_drm_patchA); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchB                               0x%X\n", psp_drm_patchB); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchC                               0x%X\n", psp_drm_patchC); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchD                               0x%X\n", psp_drm_patchD); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchE                               0x%X\n", psp_drm_patchE); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_drm_patchF                               0x%X\n", psp_drm_patchF); fputs(temp, symbols);
					sprintf(temp, "\t#define dex_psp_extra_drm_patch                          0x%X\n", psp_extra_drm_patch); fputs(temp, symbols);
				} else
				if(D=='D') {
					//sprintf(temp, "\t#define cex_ps2_nonbw_offset                        0x%X\n", ps2_nonbw_offset); fputs(temp, symbols_old);
					//sprintf(temp, "\t#define cex_ps2_nonbw_offset2                       0x%X\n", ps2_nonbw_offset2); fputs(temp, symbols_old);
					//sprintf(temp, "\t#define cex_ps2_nonbw_offset3                       0x%X\n", ps2_nonbw_offset3); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_ps2tonet_patch                          0x%X\n", ps2tonet_patch); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_ps2tonet_size_patch                     0x%X\n", ps2tonet_size_patch); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_vmode_patch_offset                      0x%X\n", vmode_patch_offset); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patch1                          0x%X\n", psp_drm_patch1); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patch2                          0x%X\n", psp_drm_patch2); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patch3                          0x%X\n", psp_drm_patch3); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patch4                          0x%X\n", psp_drm_patch4); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patchA                          0x%X\n", psp_drm_patchA); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patchB                          0x%X\n", psp_drm_patchB); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patchC                          0x%X\n", psp_drm_patchC); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patchD                          0x%X\n", psp_drm_patchD); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patchE                          0x%X\n", psp_drm_patchE); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_drm_patchF                          0x%X\n", psp_drm_patchF); fputs(temp, symbols_old);
					sprintf(temp, "\t#define cex_psp_extra_drm_patch                     0x%X\n", psp_extra_drm_patch); fputs(temp, symbols_old);
					
					//sprintf(temp, "\t#define cex_ps2_nonbw_offset                             0x%X\n", ps2_nonbw_offset); fputs(temp, symbols);
					//sprintf(temp, "\t#define cex_ps2_nonbw_offset2                            0x%X\n", ps2_nonbw_offset2); fputs(temp, symbols);
					//sprintf(temp, "\t#define cex_ps2_nonbw_offset3                            0x%X\n", ps2_nonbw_offset3); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_ps2tonet_patch                               0x%X\n", ps2tonet_patch); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_ps2tonet_size_patch                          0x%X\n", ps2tonet_size_patch); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_vmode_patch_offset                           0x%X\n", vmode_patch_offset); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patch1                               0x%X\n", psp_drm_patch1); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patch2                               0x%X\n", psp_drm_patch2); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patch3                               0x%X\n", psp_drm_patch3); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patch4                               0x%X\n", psp_drm_patch4); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchA                               0x%X\n", psp_drm_patchA); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchB                               0x%X\n", psp_drm_patchB); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchC                               0x%X\n", psp_drm_patchC); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchD                               0x%X\n", psp_drm_patchD); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchE                               0x%X\n", psp_drm_patchE); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_drm_patchF                               0x%X\n", psp_drm_patchF); fputs(temp, symbols);
					sprintf(temp, "\t#define cex_psp_extra_drm_patch                          0x%X\n", psp_extra_drm_patch); fputs(temp, symbols);
				}
			}
		}
		
		fputs("#endif\n\n", symbols_old);
		fputs("#endif\n\n", symbols);
	}
	
	fputs(" {return FAILED;}\n\
	\n\
	NEW_POKE_SYSCALL_ADDR = lv2peek( lv2peek(SYSCALL_TABLE + NEW_POKE_SYSCALL*8) ) + 0ULL;\n\
	UMOUNT_SYSCALL_OFFSET = lv2peek( lv2peek(SYSCALL_TABLE + 838*8) )  + 8ULL;\n\
	\n\
	return SUCCESS;\n\
}\n", fwc);

	fputs("\n\
	{\n\
		u64 n;\n\
		for(n=0x350000; n<0x4A0000; n++) {\n\
			u64 data = lv2peek(0x8000000000000000ULL + n);\n\
			\n\
			if(0x350000 < n && n <0x450000) {\n\
				if(OFFSET_1_IDPS == 0) {\n\
					if(0x0000000100800000 < data && data <0x0000000100900000)\n\
					{\n\
						OFFSET_1_IDPS = 0x8000000000000000ULL + n;\n\
					}\n\
				}\n\
			}\n\
			if(0x450000 < n && n <0x4A0000) {\n\
				if(OFFSET_2_IDPS == 0) {\n\
					if(0x0000000100800000 < data && data <0x0000000100900000)\n\
					{\n\
						OFFSET_2_IDPS = 0x8000000000000000ULL + n;\n\
					}\n\
				}\n\
			}\n\
			if(OFFSET_1_IDPS != 0)\n\
			if(OFFSET_2_IDPS != 0) break;\n\
		}\n\
		if(OFFSET_1_IDPS == 0 || OFFSET_2_IDPS == 0) return FAILED;\n\
		}\n\
	\n\
	rebug =  fw_is_rebug();\n\
	\n\
	sysFSStat st;\n\
	if(sysLv2FsStat(\"/dev_hdd0/tmp\", &st) != 0) {\n\
		sysLv2FsMkdir(\"/dev_hdd0/tmp\", 0777);\n\
	}\n\
	sysLv2FsChmod(\"/dev_hdd0/tmp\", 0777);\n\
	\n\
	return SUCCESS;\n\
}\n", IDPSET_firmware_c);

	fputs("\n#endif /* __FIRMWARE_SYMBOLS_H_S__ */\n", symbols_old);
	fputs("\n#endif /* __FIRMWARE_SYMBOLS_H_S__ */\n", symbols);
	fputs("\n#endif /* __COMMON_H__ */\n", common);	
	fputs("\n#endif /* __FIRMWARE_H__ */\n", IDPSET_firmware_h);
	fputs("\n#endif /* __SYMBOLS_H__ */\n", IDPSET_symbols_h);
	fputs("\n#endif /* __DATA_H__ */\n", IDPSET_data_h);
	fputs("\n#endif /* __DATA_H__ */\n", data);
	
	fputs("\n", fw);
	
	fclose(fwc);
	fclose(data);
	fclose(fw);
	fclose(IDPSET_symbols_h);
	fclose(IDPSET_firmware_h);
	fclose(IDPSET_firmware_c);
	fclose(IDPSET_data_h);
	fclose(common);
	fclose(SKY);
	fclose(symbols_old);
	fclose(symbols);
	closedir(d);
	
	return 0;
}

void Extract_DevFlash(char *fw)
{	
	printf("Extracting %s dev_flash...\n", fw);

	char PUP_path[512];
	char target[512];
	char cmd[512];
	if(exist("GetFlash.exe") == 0) {
		printf(error("GetFlash.exe is missing")); 
		return;
	}
	
	sprintf(target, "flash/%s", fw);
	mkdir(target);
	
	int do_rebug=0;
	
rebug:
	if(do_rebug) {
		sprintf(PUP_path, "PUP/REBUG/%s.PUP", fw);
		sprintf(target, "flash/%s/dev_flash_rebug", fw);
	} else {
		sprintf(PUP_path, "PUP/OFFICIAL/%s.PUP", fw);
		sprintf(target, "flash/%s/dev_flash", fw);
	}
	
	
	if(exist(PUP_path) == 0) {
		printf(warning("%s is missing"), PUP_path);
		if(!do_rebug) {do_rebug=1; goto rebug;}
		return;
	}	
	if(exist(target)) {
		printf(warning("%s already exist"), target); 
		if(!do_rebug) {do_rebug=1; goto rebug;}
		return;
	}
	
	sprintf(cmd, "GetFlash.exe %s", PUP_path);
	system(cmd);
	
	rename("dev_flash", target);
	
	if(!do_rebug) {do_rebug=1; goto rebug;}
}

void ExtractAll_DevFlash()
{
	DIR *d;
	struct dirent* ent = NULL;
	
	d = opendir("PUP/OFFICIAL");
	if(d== NULL) {
		printf(error("Directory PUP/OFFICIAL not found"));
		return;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		if(strcmp(&ent->d_name[strlen(ent->d_name)-4], ".PUP")==0) {
			char fw[512];
			strcpy(fw, ent->d_name);
			strtok(fw, ".");
			Extract_DevFlash(fw);
		}
	}
	closedir(d);
	
}


#define HW	0
#define GX	1
#define NET	2

#define SUCCESS 	1
#define FAILED	 	0

uint64_t cdvd_read_symbol;
uint64_t read_iso_size_call;
uint64_t fstat_iso_call;
uint64_t open_iso_call1;
uint64_t open_iso_call2;
uint64_t read_config_size_call;
uint64_t open_config_call;
uint64_t decrypt_config_call;

uint64_t payload_addr;
FILE *info;

int PS2_SearchOffset(char *elf_p, uint8_t type)
{
	Extract(elf_p);
	
	char temp[256];
	FILE *elf = fopen("temp_dec", "rb");
	
	//FILE *elf = fopen(elf_p, "rb");
	if (!elf)
	{
		printf("Error : Cannot open ELF");
		return -1;
	}
	
	fseek(elf, 0, SEEK_END);
	int elf_size = ftell(elf);
	fseek(elf, 0, SEEK_SET);
	
	uint8_t *elf_buf = malloc(elf_size);
	if(elf_buf==NULL) {
		fclose(elf);
		printf("Error : Cannot MALLOC ELF %X", elf_size);
		return -1;
	}
	
	fread(elf_buf, 1, elf_size, elf);
	fclose(elf);
	
	if(type == NET) {
		
		cdvd_read_symbol=0;
		read_iso_size_call=0;
		fstat_iso_call=0;
		open_iso_call1=0;
		open_iso_call2=0;
		read_config_size_call=0;// -0x24
		open_config_call=0; // -0x48
		decrypt_config_call=0; // +0x10
		
		uint8_t CONFIG_FLAG[0x10] = {0x7F, 0x83, 0xE3, 0x78, 0x38, 0x80, 0x00, 0x00, 0x7F, 0xE5, 0xFB, 0x78, 0x7F, 0xA6, 0x07, 0xB4};
		
		uint8_t cdvd_read_symbol_FLAG[0x10] = {0x2F, 0x86, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFE, 0xF1, 0xF9, 0xC1, 0x00, 0x80};
		uint8_t read_iso_size_call_FLAG[0x10] = {0x60, 0x00, 0x00, 0x00, 0x2F, 0x83, 0x00, 0x08, 0x41, 0x9E, 0x01, 0x34, 0xE8, 0x7F, 0x00, 0x58}; // -4
		uint8_t fstat_iso_call_FLAG[0x10] = {0x60, 0x00, 0x00, 0x00, 0x2F, 0x83, 0x00, 0x00, 0x7C, 0x60, 0x1B, 0x78, 0x41, 0x9C, 0x02, 0x14}; // -4
		uint8_t open_iso_call1_FLAG[0x10] = {0x60, 0x00, 0x00, 0x00, 0x2F, 0x83, 0x00, 0x00, 0x7C, 0x7E, 0x1B, 0x78, 0x7C, 0x7D, 0x07, 0xB4}; // -4
		uint8_t open_iso_call2_FLAG[0x20] = {0x60, 0x00, 0x00, 0x00, 0x39, 0x60, 0x00, 0x00, 0x90, 0x7E, 0x00, 0x04, 0x80, 0x1E, 0x00, 0x04}; // -4

		int n;
		int i=0;
		for(n=0; n<elf_size ; n++) {
			if(!memcmp((char *) &elf_buf[n], (char *) cdvd_read_symbol_FLAG, 0x10)) {
				cdvd_read_symbol = n - 0x10000;
				i++;
				sprintf(temp, "cdvd_read_symbol %X ", (unsigned int) cdvd_read_symbol); fputs(temp, info);
				//print_load("cdvd_read_symbol %X", (unsigned int) cdvd_read_symbol);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) read_iso_size_call_FLAG, 0x10)) {
				read_iso_size_call = n - 4 - 0x10000;
				i++;
				sprintf(temp, "read_iso_size_call %X ", (unsigned int) read_iso_size_call); fputs(temp, info);
				//print_load("read_iso_size_call %X", (unsigned int) read_iso_size_call);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) fstat_iso_call_FLAG, 0x10)) {
				fstat_iso_call = n - 4 - 0x10000;
				i++;
				sprintf(temp, "fstat_iso_call %X ", (unsigned int) fstat_iso_call); fputs(temp, info);
				//print_load("fstat_iso_call %X", (unsigned int) fstat_iso_call);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) open_iso_call1_FLAG, 0x10)) {
				open_iso_call1 = n - 4 - 0x10000;
				i++;
				sprintf(temp, "open_iso_call1 %X ", (unsigned int) open_iso_call1); fputs(temp, info);
				
				//print_load("open_iso_call1 %X", (unsigned int) open_iso_call1);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) open_iso_call2_FLAG, 0x10)) {
				open_iso_call2 = n - 4 - 0x10000;
				i++;
				sprintf(temp, "open_iso_call2 %X ", (unsigned int) open_iso_call2); fputs(temp, info);
				//print_load("open_iso_call2 %X", (unsigned int) open_iso_call2);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) CONFIG_FLAG, 0x10)) {
				read_config_size_call = n - 0x24 - 0x10000;
				open_config_call = n - 0x48 - 0x10000;
				decrypt_config_call = n + 0x10 - 0x10000;
				sprintf(temp, "decrypt_config_call %X ", (unsigned int) decrypt_config_call); fputs(temp, info);
				i++;
			}
			if(i==6) {
				fputs(" OK", info);
				break;
			}
		}
		
		free(elf_buf);
		
		if(i!=6) return FAILED;
		
		payload_addr = 0x3940;

		return SUCCESS;
		
	} else
	if(type == GX) {
		uint8_t payload_addr_FLAG[0x14] = {0x79, 0x29, 0x80, 0x00, 0x7D, 0x20, 0x01, 0x64, 0x55, 0x60, 0x06, 0x3C, 0x4B, 0xFF, 0xFF, 0x8C, 0x38, 0x60, 0x00, 0x01};
		int n;
		for(n=0x10000; n<elf_size ; n++) {
			if(!memcmp((char *) &elf_buf[n], (char *) payload_addr_FLAG, 0x14)) {
				payload_addr = n + 0x1C;
				sprintf(temp, "payload_addr %X OK", (unsigned int) payload_addr); fputs(temp, info);
				
				//print_load("PAYLOAD ADDR : %X", payload_addr - 0x10000);
				break;
			}
		}
		
		free(elf_buf);
		
		if(payload_addr == 0) return FAILED;
		
		return SUCCESS;
	} 
	if(type == HW) {
		uint8_t payload_addr_FLAG[0x1C] = {0x7C, 0xFF, 0x30, 0x38, 0x2F, 0x9F, 0x00, 0x00, 0x40, 0x9E, 0xFD, 0x3C, 0x4B, 0xFF, 0xFE, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x03, 0x80, 0x0C, 0x00, 0x00};
		int n;
		for(n=0x10000; n<elf_size ; n++) {
			if(!memcmp((char *) &elf_buf[n], (char *) payload_addr_FLAG, 0x1C)) {
				payload_addr = n + 0x1C;
				sprintf(temp, "payload_addr %X OK", (unsigned int) payload_addr); fputs(temp, info);
				
				//print_load("PAYLOAD ADDR : %X", payload_addr - 0x10000);
				break;
			}
		}
		
		free(elf_buf);
		
		if(payload_addr == 0) return FAILED;
		
		return SUCCESS;
	}
	return FAILED;
		
}

int ps2_info()
{
	info = fopen("ps2info.txt", "w");
	
	char temp[255];
	DIR *d;
	struct dirent* ent = NULL;
	
	fputs("HW\n", info);
	
	d = opendir("flash");
	if(d== NULL) {
		printf("Directory flash not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		if(exist(temp)) continue;
		sprintf(temp, "../payloads/PS2_EMU/BIN/ps2hwemu_stage2_%s.bin", ent->d_name);
		if(exist(temp)==0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/ps2emu/ps2_emu.self", ent->d_name);
		
		fputs(ent->d_name, info);
		fputs(" ", info);
		PS2_SearchOffset(temp, HW);
		fputs("\n", info);
		
	}
	closedir(d);
	
	fputs("\nGX\n", info);
	
	d = opendir("flash");
	if(d== NULL) {
		printf("Directory flash not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		if(exist(temp)) continue;
		sprintf(temp, "../payloads/PS2_EMU/BIN/ps2gxemu_stage2_%s.bin", ent->d_name);
		if(exist(temp)==0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/ps2emu/ps2_gxemu.self", ent->d_name);
		
		fputs(ent->d_name, info);
		fputs(" ", info);
		PS2_SearchOffset(temp, GX);
		fputs("\n", info);
	}
	closedir(d);
	
	fputs("\nNET\n", info);
	
	d = opendir("flash");
	if(d== NULL) {
		printf("Directory flash not found\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "flash/%s/dev_flash/rebug", ent->d_name);
		if(exist(temp)) continue;
		
		sprintf(temp, "flash/%s/dev_flash/ps2emu/ps2_netemu.self", ent->d_name);
		
		fputs(ent->d_name, info);
		fputs(" ", info);
		PS2_SearchOffset(temp, NET);
		fputs("\n", info);
	}
	closedir(d);
	
	
	fclose(info);
	
	return 0;
}

void print_help()
{
	printf("offsetfinder.exe [option]\n\n\
	search\t\tsearch offsets and generate files\n\
	idpset\t\tsearch offsets, generate files and move them to idpset folder\n\
	move\t\tmove files to their directories\n\
	extract\t\textract dev_flash from PUP\n");
	exit(0);
}

void force_rename(char *old, char *new)
{
	if(exist(old)==0) {
		printf("Error : %s doesn't exist\n", old);
		exit(0);
	}
	remove(new);
	rename(old, new);
}

int test_lv2flag()
{ 
	u8 flag[] = {};
	int flag_pos=-4;
	
	char *flag_name = "blabla";
	
	s16 ignore = 0xAA;
	
	char dump[255];
	char temp[255];
	FILE *test = fopen("test.h", "w");
	
	DIR *d;
	struct dirent* ent = NULL;
	
	d = opendir("LV2");
	if(d== NULL) {
		printf("Put your dumps in the directory 'LV2'\n");
		return 0;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(dump, "LV2/%s", ent->d_name);
		FILE *f=fopen(dump, "rb");
		if(f==NULL) {
			printf(error("Cannot open the dump\n"));
			return 0;
		}
		fseek (f , 0 , SEEK_END);
		u32 size = ftell (f);
		fseek(f, 0, SEEK_SET);
		
		if(size != 0x800000) {
			printf(error("bad size of your dump\n"));
			fclose(f);
			return 0;
		}
		
		char *memLV2 = (char *) malloc(size);	
		if(memLV2 == NULL) {
			printf(error("cannot malloc LV2"));
			free(memLV2);
			fclose(f);
			return 0;
		}
		fread(memLV2,size,1, f);
		fclose(f);
		u64 n;
		u64 flag_value=0;
		for(n=0; n<size ; n++) {
			if(compare(ignore, (char *) &memLV2[n], (char *) flag, sizeof(flag))) {
				flag_value = n + flag_pos;
				break;
			}
		}
		sprintf(temp, "#define %s_%s\t\t\t%X", flag_name, ent->d_name, flag_value);
		strcat(temp, "\n");
		
		fputs(temp, test);
	}
	closedir(d);
	fclose(test);
	
	return 0;
}

char *self_paths[] = {
	"/dev_flash/vsh/module/download_plugin.sprx"                    ,
	"/dev_flash/vsh/module/autodownload_plugin.sprx"                ,
	"/dev_flash/vsh/module/premo_plugin.sprx"                       ,
	"/dev_flash/vsh/module/premo_game_plugin.sprx"                  ,
	"/dev_flash/vsh/module/basic_plugins.sprx"                      ,
	"/dev_flash/vsh/module/bdp_disccheck_plugin.sprx"               ,
	"/dev_flash/vsh/module/game_ext_plugin.sprx"                    ,
	"/dev_flash/vsh/module/nas_plugin.sprx"                         ,
	"/dev_flash/vsh/module/vsh.self"                                ,
	"/dev_flash/bdplayer/bdp_BDMV.self"                             ,
	"/dev_flash/bdplayer/bdp_BDVD.self"                             ,
	"/dev_flash/ps1emu/ps1_emu.self"                                ,
	"/dev_flash/ps1emu/ps1_netemu.self"                             ,
	"/dev_flash/pspemu/release/PEmuCoreLib.sprx"                    ,
	"/dev_flash/pspemu/release/emulator_api.sprx"                   ,
	"/dev_flash/pspemu/release/emulator_drm.sprx"                   ,
	"/dev_flash/pspemu/release/emulator_drm.sprx"                   ,
	"/dev_flash/pspemu/psp_emulator.self"                           ,
	"/dev_flash/sys/external/libsysutil_savedata_psp.sprx"          ,
	"/dev_flash/sys/external/libaudio.sprx"                         
};
#define self_count 20

char *GetFilename(char *path)
{
    int n = strlen(path);
	
    while(path[n] != '/') n--;
	
    return &path[n+1];
}

void get_elfs()
{
	char temp[512];
	char cmd[512];
	DIR *d;
	struct dirent* ent = NULL;
	
	d = opendir("LV2");
	if(d== NULL) {
		printf("Put your dumps in the directory 'LV2'\n");
		return;
	}
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		int i;
		for(i=0; i<self_count; i++) {
			sprintf(temp, "flash/%s%s", ent->d_name, self_paths[i]);
			sprintf(cmd, "scetool -d %s/%s %s/elfs/%s_%s", PWD, temp, PWD, ent->d_name, GetFilename(self_paths[i]));
			system(cmd);
		}
	}
	closedir(d);
	
}

void test_elf()
{
	FILE *test;
	test = fopen("test.txt", "w");
	u8 flag[]={};
	int flag_pos=0x60;
	char *elf_name = "plugin.sprx";
	char *flag_name = "blabla";
	
	char temp[512];
	
	s16 ignore = 0xAA;
	
	DIR *d;
	struct dirent* ent = NULL;
	
	d = opendir("LV2");
	if(d== NULL) return;
	
	while ((ent = readdir(d)) != NULL) {
		if(strcmp(ent->d_name, ".") == 0) continue;
		if(strcmp(ent->d_name, "..") == 0) continue;
		
		sprintf(temp, "elfs/%s_%s", ent->d_name, elf_name);
		
		FILE *f=fopen(temp, "rb");
		if(f==NULL) continue;
		
		fseek (f , 0 , SEEK_END);
		u32 size = ftell (f);
		fseek(f, 0, SEEK_SET);		
		char *mem = (char *) malloc(size);	
		if(mem == NULL) {
			free(mem);mem=NULL;
			fclose(f);
			return;
		}
		fread(mem,size,1, f);
		fclose(f);
		u64 flag_value = 0;
		int n;
		for(n=0; n<size ; n++) {
			if(0x1000<n && n < 0x1800){
				if(compare(ignore, (char *) &mem[n], (char *) flag, sizeof(flag))) {
					flag_value = n + flag_pos;
				}
			}
		}
		
		sprintf(temp, "#define %s_%s\t\t\t%X\n", flag_name, ent->d_name, flag_value);
		fputs(temp, test);
		
	}
	closedir(d);
	fclose(test);
}

int main(int argc, char **argv)
{
	PWD = getenv("PWD");
	char *PS3ENV = getenv("PS3");
	if(PS3ENV==NULL) {
		//putenv("PS3=$PS3DEV/bin/data");
		printf(error(" "));
		printf("* Environnement variable 'PS3' is missing.\n* Type : export PS3=$PS3DEV/bin/data\n* scetool need it to load the keys.\n\n");
		return 0;
	}
	
	if(argc<2) print_help();
	
	if(strcmp(argv[1], "search")==0) {
		SearchOffsets();
		PS2_SearchOffsets();
		PS2_CRC();
	} else
	if(strcmp(argv[1], "move")==0) {
		force_rename("firmware_symbols.h", "../payloads/SKY/firmware_symbols.h");
		force_rename("symbols.h", "../payloads/MAMBA/lv2/include/lv2/symbols.h");
		force_rename("ps2symbols.h", "../payloads/PS2_EMU/ps2emu/include/ps2emu/symbols.h");
		force_rename("IDPSET_symbols.h", "../payloads/erk_dumper/source/symbols.h");
		force_rename("common.h", "../MGZ/source/common.h");
		force_rename("data.h", "../MGZ/source/data.h");
		force_rename("ps2data.h", "../MGZ/source/ps2data.h");
		force_rename("ps2crc.h", "../MGZ/source/ps2crc.h");
		force_rename("ps2vers.c", "../MGZ/source/ps2vers.c");
		force_rename("fw.c", "../MGZ/source/fw.c");
		force_rename("FIRMWARES", "../payloads/FIRMWARES");
	} else
	if(strcmp(argv[1], "extract")==0) {
		if(2<argc) {
			int i;
			for(i=2;i<argc;i++) Extract_DevFlash(argv[i]);
		} else {
			ExtractAll_DevFlash();
		}
	} else
	if(strcmp(argv[1], "idpset")==0) {
		SearchOffsets();
		
		if(exist("../../IDPSet")) {
			force_rename("IDPSET_symbols.h", "../../IDPSet/payload/source/symbols.h");
			force_rename("IDPSET_firmware.h", "../../IDPSet/source/firmware.h");
			force_rename("IDPSET_firmware.c", "../../IDPSet/source/firmware.c");
			force_rename("IDPSET_data.h", "../../IDPSet/source/data.h");
			force_rename("FIRMWARES", "../../IDPSet/payload/source/FIRMWARES");
		}
		
	} else
	if(strcmp(argv[1], "test")==0) {
		SearchOffsets();
	} else	print_help();
	
	printf("Done !\n");
	
	return 0;
}