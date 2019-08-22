#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

uint64_t cdvd_read_symbol;
uint64_t read_iso_size_call;
uint64_t fstat_iso_call;
uint64_t open_iso_call1;
uint64_t open_iso_call2;
uint64_t read_config_size_call;
uint64_t open_config_call;
uint64_t decrypt_config_call;

#define ADDITIONAL_CODE_SIZE		0x46B0
#define ADDITIONAL_DATA_SIZE		0x1000

#define MAKE_JUMP(addr, to) *(uint32_t *)(addr) = (0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2)
#define MAKE_CALL(addr, to) *(uint32_t *)(addr) = (0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xffffff) << 2) | 1

#define MAKE_JUMP_VALUE(addr, to) ((0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2))
#define MAKE_CALL_VALUE(addr, to) ((0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2)) | 1

#define BLR	0x4E800020
#define BLRL	0x4E800021
#define BCTR	0x4E800420
#define BCTRL	0x4E800421
#define NOP	0x60000000

#define MFSPR(SPR, RS) ((31 << 26) | (RS << 21) | (SPR << 16) | (339 << 1))
#define MFLR(RS) MFSPR(8, RS)
#define MFCTR(RS) MFSPR(9, RS)

#define MTSPR(SPR, RS) ((31 << 26) | (RS << 21) | (SPR << 16) | (467 << 1))
#define MTLR(RS) MTSPR(8, RS)
#define MTCTR(RS) MTSPR(9, RS)

#define OR(RA, RS, RB) (31 << 26) | (RS << 21) | (RA << 16) | (RB << 11) | (444 << 1)
#define ORI(RA, RS, UI) (24 << 26) | (RS << 21) | (RA << 16) | (UI&0xFFFF)
#define ORIS(RA, RS, UI) (25 << 26) | (RS << 21) | (RA << 16) | (UI&0xFFFF)
#define MR(RS, RA) OR(RS, RA, RA)

#define ADDI(RT, RA, SI) (14 << 26) | (RT << 21) | (RA << 16) | (SI&0xFFFF)
#define LI(RA, UI) ADDI(RA, 0, UI)

#define ADDIS(RT, RA, SI) (15 << 26) | (RT << 21) | (RA << 16) | (SI&0xFFFF)
#define LIS(RA, UI) ADDIS(RA, 0, UI)

#define LD(RT, DS, RA) (58 << 26) | (RT << 21) | (RA << 16) | ((DS >> 2) << 2)
#define STD(RS, DS, RA) (62 << 26) | (RS << 21) | (RA << 16) | ((DS >> 2) << 2)

#define STW(RS, D, RA) (36 << 26) | (RS << 21) | (RA << 16) | D

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

char *PWD;
char temp[2048];

typedef struct function_descriptor 
{
	uint64_t addr;
	uint64_t toc;	
} f_desc_t;

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

uint8_t *ps2_netemu;

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

static uint32_t swap32(uint32_t data)
{
	uint32_t ret = (((data) & 0xff) << 24);
	ret |= (((data) & 0xff00) << 8);
	ret |= (((data) & 0xff0000) >> 8);
	ret |= (((data) >> 24) & 0xff);
	
	return ret;
}

static void make_long_jump(void *addr, uint64_t to)
{
	uint32_t *ins = (uint32_t *)addr;
	
	ins[0] = LIS(0, ((to>>16)&0xFFFF));
	ins[1] = ORI(0, 0, (to&0xFFFF));
	ins[2] = MTCTR(0);
	ins[3] = BCTR;
	
	for (int i = 0; i < 4; i++)
		ins[i] = swap32(ins[i]);
}

static void make_long_call_with_inst(void *addr, uint64_t to, uint32_t *inst)
{
	int i, j;
	uint32_t *ins = (uint32_t *)addr;
	uint32_t ins_ps3;
	
	ins_ps3 = (uint8_t *)addr - ps2_netemu;
	
	ins[0] = LIS(0, ((to>>16)&0xFFFF));
	ins[1] = ORI(0, 0, (to&0xFFFF));
	ins[2] = MTCTR(0);
	
	for (i = 0, j = 3; i < 4; i++, j++)
	{
		if (swap32(inst[i]) == MFLR(0))
		{
			ins[j] = LIS(0, (((uint64_t)(ins_ps3+(9*4))>>16)&0xFFFF));
			j++;
			ins[j] = ORI(0, 0, ((uint64_t)(ins_ps3+(9*4))&0xFFFF));
		}
		else if (swap32(inst[i]) == MFLR(11))
		{			
			ins[j] = LIS(11, (((uint64_t)(ins_ps3+(9*4))>>16)&0xFFFF));
			j++;
			ins[j] = ORI(11, 11, ((uint64_t)(ins_ps3+(9*4))&0xFFFF));
		}
		else
		{			
			ins[j] = swap32(inst[i]);
		}
		
		if (i == 3 && j == 6)
		{
			ins[7] = NOP;
		}
	}
	
	ins[8] = BCTRL;
	
	for (i = 0; i < 9; i++)
		ins[i] = swap32(ins[i]);
}

static void patch_call(uint64_t call_addr, void *newfunc)
{
	f_desc_t *f = (f_desc_t *)newfunc;
	uint32_t inst = MAKE_CALL_VALUE(call_addr, swap64(f->addr));
	
	*(uint32_t *)&ps2_netemu[call_addr] = swap32(inst);
}

static void change_function(uint64_t func_addr, void *newfunc)
{
	f_desc_t *f = (f_desc_t *)newfunc;
	make_long_jump(ps2_netemu+func_addr, swap64(f->addr));	
}

// func_addr -> ps3, newfunc -> native
/*static void hook_function_with_postcall(uint64_t func_addr, void *newfunc, unsigned int nparams)
{
	if (nparams > 8)
		return;
	
	f_desc_t *f = (f_desc_t *)newfunc;
	uint32_t *inst = (uint32_t *)(ps2_netemu+func_addr);
	uint32_t *orig_call = &((uint32_t *)(ps2_netemu+swap64(f->addr)))[16+(nparams*2)]; // WARNING: relies on HOOKED_FUNCTION_POST_CALL_N not being changed	
	
	make_long_call_with_inst(&orig_call[0], func_addr+16, inst);
	change_function(func_addr, newfunc);
}*/

// func_addr -> ps3, newfunc -> native
static void hook_function_with_cond_postcall(uint64_t func_addr, void *newfunc, unsigned int nparams)
{
	if (nparams > 8)
		return;
	
	f_desc_t *f = (f_desc_t *)newfunc;
	uint32_t *inst = (uint32_t *)(ps2_netemu+func_addr);
	uint32_t *orig_call = &((uint32_t *)(ps2_netemu+swap64(f->addr)))[19+(nparams*2)]; // WARNING: relies on HOOKED_FUNCTION_COND_POST_CALL_N not being changed	
	
	make_long_call_with_inst(&orig_call[0], func_addr+16, inst);
	change_function(func_addr, newfunc);
}

static void get_func_name(char *line, char *name)
{
	int len = strlen(line);
	int in_name = 0;
	char *begin = NULL, *end = NULL;
	
	*name = 0;
	
	for (int i = len-1; i >= 0; i--)
	{
		if (in_name)
		{
			if (line[i] <= ' ')
			{
				begin = &line[i+1];
				break;
			}
		}
		else
		{
			if (line[i] > ' ')
			{
				in_name = 1;
				end = &line[i];
			}
		}
	}
	
	len = (int)(end-begin)+1;
	
	if (begin && end)
	{
		memcpy(name, begin, len);
		name[len] = 0;
		
	}
}

static uint64_t get_func_address(char *line)
{
	int len = strlen(line);
	uint64_t address = 0;
	
	for (int i = 1; i < len; i++)
	{
		if (line[i-1] == '0' && line[i] == 'x')
		{
			sscanf(line+i-1, "0x%lx", (long unsigned int*)&address);
			break;
		}
	}
	
	return address;
}

static int patch_emu(char *payload_map_file)
{
	FILE *map = fopen(payload_map_file, "r");
	char line[512], name[512];
	int in_opd = 0;
	int ret = 0;
	
	if (!map)
	{
		printf("Error opening %s\n", payload_map_file);
		return -1;
	}
	
	while (fgets(line, sizeof(line), map))
	{
		if (in_opd)
		{
			uint64_t addr;
			
			if (strncmp(line, " *(.opd.*)", 10) == 0)
				break;
			
			get_func_name(line, name);
			//printf("name = %s\n", name);
/*			if (strcmp(name, "ufs_read_patched") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of ufs_read_patched\n");
					ret = -1;
					break;
				}
				
				printf("ufs_read_patched found at %lx\n", addr);
				hook_function_with_cond_postcall(ufs_read_symbol, ps2_netemu+addr, 4);
			}
			else if (strcmp(name, "ufs_fstat_patched") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of ufs_fstat_patched\n");
					ret = -1;
					break;
				}
				
				printf("ufs_fstat_patched found at %lx\n", addr);
				hook_function_with_cond_postcall(ufs_fstat_symbol, ps2_netemu+addr, 2);
			}*/
			/*else if (strcmp(name, "ufs_open_patched") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of ufs_open_patched\n");
					ret = -1;
					break;
				}
				
				printf("ufs_open_patched found at %lx\n", addr);
				hook_function_with_cond_postcall(ufs_open_symbol, ps2_netemu+addr, 2);
			}*/
			//else 
				if (strcmp(name, "cdvd_read_patched") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of cdvd_read_patched\n");
					ret = -1;
					break;
				}
				
				printf("cdvd_read_patched found at %lx\n", (unsigned long)addr);
				hook_function_with_cond_postcall(cdvd_read_symbol, ps2_netemu+addr, 4);
			}
			else if (strcmp(name, "read_iso_size") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of read_iso_size\n");
					ret = -1;
					break;
				}
				
				printf("read_iso_size found at %lx\n", (unsigned long)addr);
				patch_call(read_iso_size_call, ps2_netemu+addr);
			}
			else if (strcmp(name, "fstat_iso_patched") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of fstat_iso_patched\n");
					ret = -1;
					break;
				}
				
				printf("fstat_iso_patched found at %lx\n", (unsigned long)addr);
				patch_call(fstat_iso_call, ps2_netemu+addr);
			}
			else if (strcmp(name, "open_config") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of open_config\n");
					ret = -1;
					break;
				}
				
				printf("open_config found at %lx\n", (unsigned long)addr);
				patch_call(open_config_call, ps2_netemu+addr);
			}
			else if (strcmp(name, "read_config_size") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of read_config_size\n");
					ret = -1;
					break;
				}
				
				printf("read_config_size found at %lx\n", (unsigned long)addr);
				patch_call(read_config_size_call, ps2_netemu+addr);
			}
			else if (strcmp(name, "decrypt_config") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of decrypt_config\n");
					ret = -1;
					break;
				}
				
				printf("decrypt_config found at %lx\n", (unsigned long)addr);
				patch_call(decrypt_config_call, ps2_netemu+addr);
			}
			else if (strcmp(name, "open_iso") == 0)
			{
				addr = get_func_address(line);
				
				if (addr == 0)
				{
					printf("Cannot find address of open_iso\n");
					ret = -1;
					break;
				}
				
				printf("open_iso found at %lx\n", (unsigned long)addr);
				patch_call(open_iso_call1, ps2_netemu+addr);
				patch_call(open_iso_call2, ps2_netemu+addr);
			}
		}
		else
		{
			if (strncmp(line, " *(.opd)", 8) == 0)
				in_opd = 1;
		}
	}
	
	fclose(map);
	return ret;
}

static void command3(char *cmd, char *arg1, char *arg2, char *arg3)
{
	char buf[2048];
	
	snprintf(buf, sizeof(buf), "%s %s %s %s", cmd, arg1, arg2, arg3);
	system(buf);
}

static void command15(char *cmd, char *arg1, char *arg2, char *arg3, char *arg4, char *arg5, char *arg6, char *arg7, char *arg8, char *arg9, char *arg10, char *arg11, char *arg12, char *arg13, char *arg14, char *arg15)
{
	char buf[2048];
	
	snprintf(buf, sizeof(buf), "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", cmd, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13,arg14, arg15);
	system(buf);
}

static void patch_self(char *src, char *dst, uint64_t *first_section_size)
{
	char *buf;
	FILE *f;
	int patches = 0;
	
	f = fopen(src, "rb");
	if (!f)
	{
		printf("Cannot open %s\n", src);
		exit(-1);
	}
	
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	buf = malloc(size);
	
	fread(buf, 1, size, f);
	fclose(f);
	
	uint32_t sh_offset;
	
	memcpy(&sh_offset, buf + 0x44, 4);
	sh_offset = swap32(sh_offset) + 0x40;
	printf("sh_offset = %X\n", sh_offset);
	Elf64_Phdr *phdr = (Elf64_Phdr *)(buf+0xD0);
	
	phdr->p_memsz = swap64(swap64(phdr->p_memsz)); //+ ADDITIONAL_CODE_SIZE);
	phdr->p_filesz = swap64(swap64(phdr->p_filesz));// + ADDITIONAL_CODE_SIZE);
	*first_section_size = swap64(phdr->p_filesz);
	
	phdr += 2;
	
	phdr->p_memsz = swap64(swap64(phdr->p_memsz) + ADDITIONAL_DATA_SIZE);
	
	Elf64_Shdr *shdr = (Elf64_Shdr *)(buf+sh_offset);
	
	while (patches < 2)
	{
		//uint64_t flags = swap64(shdr->sh_flags);
		
		if (0xB20000 < swap64(shdr->sh_addr) && swap64(shdr->sh_addr) < 0xB30000)
		{
			printf("sh_addr : %X\n", (unsigned int) swap64(shdr->sh_addr));
			shdr->sh_size = swap64(swap64(shdr->sh_size)+ADDITIONAL_DATA_SIZE);
			patches++;
		}
		else if (swap64(shdr->sh_addr) == 0x3800)
		{
			shdr->sh_size = swap64(swap64(shdr->sh_size)+ADDITIONAL_CODE_SIZE);
			patches++;
		}
		
		/*if (flags & SHF_EXECINSTR)
		{
			// Write permissions on code
			shdr->sh_flags = swap64(flags | SHF_WRITE);
		}*/
		
		shdr++;
	}
	
	f = fopen(dst, "wb");
	fwrite(buf, 1, size, f);
	fclose(f);
}

int Search_Offset(char *elf_p)
{
	
	FILE *elf;
	
	elf = fopen(elf_p, "rb");
	if (!elf)
	{
		printf("Cannot open ELF");
		return -1;
	}
	
	fseek(elf, 0, SEEK_END);
	int elf_size = ftell(elf);
	fseek(elf, 0, SEEK_SET);
	
	uint8_t *elf_buf = malloc(elf_size);
	if(elf_buf==NULL) {
		fclose(elf);
		printf("Cannot MALLOC ELF %X\n", elf_size);
		return -1;
	}
	
	fread(elf_buf, 1, elf_size, elf);
	fclose(elf);
	
	cdvd_read_symbol=0;
	read_iso_size_call=0;
	fstat_iso_call=0;
	open_iso_call1=0;
	open_iso_call2=0;
	read_config_size_call=0;// -0x24
	open_config_call=0; // -0x48
	decrypt_config_call=0; // +0x10
	 
	uint8_t cdvd_read_symbol_FLAG[0x10] = {0x2F, 0x86, 0x00, 0x00, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x21, 0xFE, 0xF1, 0xF9, 0xC1, 0x00, 0x80};
	uint8_t read_iso_size_call_FLAG[0x10] = {0x60, 0x00, 0x00, 0x00, 0x2F, 0x83, 0x00, 0x08, 0x41, 0x9E, 0x01, 0x34, 0xE8, 0x7F, 0x00, 0x58}; // -4
	uint8_t fstat_iso_call_FLAG[0x10] = {0x60, 0x00, 0x00, 0x00, 0x2F, 0x83, 0x00, 0x00, 0x7C, 0x60, 0x1B, 0x78, 0x41, 0x9C, 0x02, 0x14}; // -4
	uint8_t open_iso_call1_FLAG[0x10] = {0x60, 0x00, 0x00, 0x00, 0x2F, 0x83, 0x00, 0x00, 0x7C, 0x7E, 0x1B, 0x78, 0x7C, 0x7D, 0x07, 0xB4}; // -4
	uint8_t open_iso_call2_FLAG[0x20] = {0x60, 0x00, 0x00, 0x00, 0x39, 0x60, 0x00, 0x00, 0x90, 0x7E, 0x00, 0x04, 0x80, 0x1E, 0x00, 0x04}; // -4
	uint8_t CONFIG_FLAG[0x10] = {0x7F, 0x83, 0xE3, 0x78, 0x38, 0x80, 0x00, 0x00, 0x7F, 0xE5, 0xFB, 0x78, 0x7F, 0xA6, 0x07, 0xB4};
		
	printf("\n");
	
	int n;
	int i=0;
	for(n=0; n<elf_size ; n++) {
		if(!memcmp((char *) &elf_buf[n], (char *) cdvd_read_symbol_FLAG, 0x10)) {
			cdvd_read_symbol = n - 0x10000;
			i++;
			printf("cdvd_read_symbol %X\n", (unsigned int) cdvd_read_symbol);
		}
		if(!memcmp((char *) &elf_buf[n], (char *) read_iso_size_call_FLAG, 0x10)) {
			read_iso_size_call = n - 4 - 0x10000;
			i++;
			printf("read_iso_size_call %X\n", (unsigned int) read_iso_size_call);
		}
		if(!memcmp((char *) &elf_buf[n], (char *) fstat_iso_call_FLAG, 0x10)) {
			fstat_iso_call = n - 4 - 0x10000;
			i++;
			printf("fstat_iso_call %X\n", (unsigned int) fstat_iso_call);
		}
		if(!memcmp((char *) &elf_buf[n], (char *) open_iso_call1_FLAG, 0x10)) {
			open_iso_call1 = n - 4 - 0x10000;
			i++;
			printf("open_iso_call1 %X\n", (unsigned int) open_iso_call1);
		}
		if(!memcmp((char *) &elf_buf[n], (char *) open_iso_call2_FLAG, 0x10)) {
			open_iso_call2 = n - 4 - 0x10000;
			i++;
			printf("open_iso_call2 %X\n", (unsigned int) open_iso_call2);
		}
		if(!memcmp((char *) &elf_buf[n], (char *) CONFIG_FLAG, 0x10)) {
			read_config_size_call = n - 0x24 - 0x10000;
			open_config_call = n - 0x48 - 0x10000;
			decrypt_config_call = n + 0x10 - 0x10000;
			i++;
			printf("read_config_size_call %X\n", (unsigned int) read_config_size_call);
			printf("open_config_call %X\n", (unsigned int) open_config_call);
			printf("decrypt_config_call %X\n", (unsigned int) decrypt_config_call);
		}
		if(i==6) break;
	}
	
	printf("\n");
	
	free(elf_buf);
	
	if(i!=6) return -1; 

	return 0;
	
	
}

int main(int argc, char *argv[])
{
	PWD = getenv("PWD");
	char *PS3ENV = getenv("PS3");
	if(PS3ENV==NULL) {
		printf("Environnement variable 'PS3' is missing.\nType : export PS3=$PS3DEV/bin/data\nscetool need it to load the keys.\n\n");
		return 0;
	}
	
	char *payload, *self_input, *self_output, *payload_map;
	uint32_t text_offset, payload_addr, payload_size;
	FILE *bin, *elf;
	uint8_t *payload_buf;
	uint64_t load_size;
	
	if (argc < 5)
	{
		printf("Usage: %s payload self_input self_output payload_map\n", argv[0]);
		return -1;
	}
	
	payload = argv[1];
	self_input = argv[2];
	self_output = argv[3];
	payload_map = argv[4];
	
	text_offset = 0x10000;
	payload_addr = 0x3940;
	
	patch_self(self_input, "temp.self", &load_size);	
	sprintf(temp, "scetool --decrypt", "%s/temp.self", "%s/temp.elf", PWD, PWD);
	system(temp);
	
	bin = fopen(payload, "rb");
	if (!bin)
	{
		printf("Cannot open %s\n", payload);
		return -2;
	}
	
	fseek(bin, 0, SEEK_END);
	payload_size = ftell(bin);
	fseek(bin, 0, SEEK_SET);
	
	if (payload_size > ADDITIONAL_CODE_SIZE)
	{
		printf("payload is bigger than limit, %d > %d\n", payload_size, ADDITIONAL_CODE_SIZE);
		return -7;
	}
	
	payload_buf = malloc(payload_size);
	if (!payload_buf)
	{
		printf("Cannot allocate %d bytes.\n", payload_size);
		return -3;
	}
	
	fread(payload_buf, 1, payload_size, bin);
	fclose(bin);
	
	if( Search_Offset("temp.elf") < 0) {
		return -22;
	}
	
	elf = fopen("temp.elf", "rb+");
	if (!elf)
	{
		printf("Cannot open temp.elf\n");
		return -4;
	}
	
	ps2_netemu = malloc(load_size);
	if (!ps2_netemu)
	{
		printf("Cannot allocate %ld bytes\n", (unsigned long int)load_size);
		return -5;
	}
	
	fseek(elf, text_offset, SEEK_SET);
	if (fread(ps2_netemu, 1, load_size, bin) != load_size)
	{
		printf("fread read less than load_size\n");
		return -6;
	}
	
	memcpy(ps2_netemu+payload_addr, payload_buf, payload_size);
	free(payload_buf);
	
	if (patch_emu(payload_map) != 0)
	{
		printf("Error patching emu\n");
		return -8;
	}
	
	fseek(elf, text_offset, SEEK_SET);
	fwrite(ps2_netemu, 1, load_size, elf);	
	free(ps2_netemu);
	fclose(elf);
		
	sprintf(temp, "scetool -v --sce-type=SELF --compress-data=TRUE --compress-data=TRUE --skip-sections=FALSE --self-auth-id=1020000401000001 --self-add-shdrs=TRUE --self-vendor-id=02000003 --self-type=LV2 --self-fw-version=0004002100000000 --key-revision=0 --self-app-version=0001000000000000 --encrypt %s/temp.elf %s/%s", PWD, PWD, self_output);
	system(temp);
	
	system("del temp.elf");
	system("del temp.self");
	
	return 0;
}

