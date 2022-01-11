#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ppu-types.h>

#define ADDITIONAL_SIZE		0x10000
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

#define MAKE_JUMP_VALUE(addr, to) ((0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2))
#define MAKE_CALL_VALUE(addr, to) ((0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2)) | 1

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

#define HW	0
#define GX	1
#define NET	2

#define SUCCESS 	1
#define FAILED	 	0
#define YES			1
#define NO 			0

#define swap64(x) x
#define swap32(x) x

uint8_t *ps2_netemu;

uint64_t cdvd_read_symbol;
uint64_t read_iso_size_call;
uint64_t fstat_iso_call;
uint64_t open_iso_call1;
uint64_t open_iso_call2;
uint64_t read_config_size_call;
uint64_t open_config_call;
uint64_t decrypt_config_call;

uint64_t payload_addr;

extern int Extract_SELF(char *in, char *out);
extern int Sign_PS2ELF(char *in, char *out);
extern void Delete(char* path);
extern void print_load(char *format, ...);
extern char ManaGunZ_id[10];

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

static void make_long_jump(void *addr, uint64_t to)
{
	uint32_t *ins = (uint32_t *)addr;
	
	ins[0] = LIS(0, ((to>>16)&0xFFFF));
	ins[1] = ORI(0, 0, (to&0xFFFF));
	ins[2] = MTCTR(0);
	ins[3] = BCTR;
	int i;
	for (i = 0; i < 4; i++)
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

void patch_netemu()
{
	hook_function_with_cond_postcall(cdvd_read_symbol, ps2_netemu + 0x4710, 4);
	patch_call(read_iso_size_call, ps2_netemu + 0x46D0);
	patch_call(fstat_iso_call, ps2_netemu + 0x46C0);
	patch_call(open_iso_call1, ps2_netemu + 0x46B0);
	patch_call(open_iso_call2, ps2_netemu + 0x46B0);
	patch_call(read_config_size_call, ps2_netemu + 0x46f0);
	patch_call(open_config_call, ps2_netemu + 0x46E0);
	patch_call(decrypt_config_call, ps2_netemu + 0x4700);
}

static void patch_netself(char *src, char *dst, uint64_t *first_section_size)
{
	char *buf;
	FILE *f;
	int patches = 0;
	
	f = fopen(src, "rb");
	if (!f)
	{
		print_load("Error : Cannot open %s", src);
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
	// print_load("SH OFFSET = %X", sh_offset);
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
			//print_load("sh_addr : %X", (unsigned int) swap64(shdr->sh_addr));
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

int Search_Offset(char *elf_p, uint8_t type)
{
	FILE *elf;
	
	elf = fopen(elf_p, "rb");
	if (!elf)
	{
		print_load("Error : Cannot open ELF");
		return -1;
	}
	
	fseek(elf, 0, SEEK_END);
	int elf_size = ftell(elf);
	fseek(elf, 0, SEEK_SET);
	
	uint8_t *elf_buf = malloc(elf_size);
	if(elf_buf==NULL) {
		fclose(elf);
		print_load("Error : Cannot MALLOC ELF %X", elf_size);
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
				//print_load("cdvd_read_symbol %X", (unsigned int) cdvd_read_symbol);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) read_iso_size_call_FLAG, 0x10)) {
				read_iso_size_call = n - 4 - 0x10000;
				i++;
				//print_load("read_iso_size_call %X", (unsigned int) read_iso_size_call);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) fstat_iso_call_FLAG, 0x10)) {
				fstat_iso_call = n - 4 - 0x10000;
				i++;
				//print_load("fstat_iso_call %X", (unsigned int) fstat_iso_call);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) open_iso_call1_FLAG, 0x10)) {
				open_iso_call1 = n - 4 - 0x10000;
				i++;
				//print_load("open_iso_call1 %X", (unsigned int) open_iso_call1);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) open_iso_call2_FLAG, 0x10)) {
				open_iso_call2 = n - 4 - 0x10000;
				i++;
				//print_load("open_iso_call2 %X", (unsigned int) open_iso_call2);
			}
			if(!memcmp((char *) &elf_buf[n], (char *) CONFIG_FLAG, 0x10)) {
				read_config_size_call = n - 0x24 - 0x10000;
				open_config_call = n - 0x48 - 0x10000;
				decrypt_config_call = n + 0x10 - 0x10000;
				i++;
			}
			if(i==6) break;
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

static void patch_self(char *src, char *dst, uint8_t type)
{
	char *buf;
	FILE *f;
	
	int extend_ph=1;
	int extend_sh=1;
	
	f = fopen(src, "rb");
	if (!f)
	{
		print_load("Error : Cannot open %s", src);
		exit(-1);
	}
	
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	buf = malloc(size);
	
	fread(buf, 1, size, f);
	fclose(f);
	
	uint32_t sh_offset, data_address;
	
	memcpy(&sh_offset, buf + 0x44, 4);
	sh_offset = swap32(sh_offset) + 0x40;
	
	memcpy(&data_address, buf + 0xF4, 4);
	data_address = swap32(data_address);
	
	if(type==GX) {
		data_address += 0x60;
	} else {
		extend_sh=0;
		extend_ph=0;
	}
	
	//print_load("DATA ADDR : %X", data_address);
	//print_load("SH ADDR : %X", sh_offset);
	
	Elf64_Phdr *phdr = (Elf64_Phdr *)(buf+0xD0);
	
	if (extend_ph)	
		phdr->p_memsz = swap64(swap64(phdr->p_memsz) + ADDITIONAL_SIZE);
	
	Elf64_Shdr *shdr = (Elf64_Shdr *)(buf+sh_offset);
	
	while (1)
	{
		uint64_t flags = swap64(shdr->sh_flags);
		
		if (swap64(shdr->sh_addr) == data_address)
		{
			// Grant execution on data
			shdr->sh_flags = swap64(flags | SHF_EXECINSTR); 
			if (extend_sh)
				shdr->sh_size = swap64(swap64(shdr->sh_size)+ADDITIONAL_SIZE);
			break;
		}
		
		if (flags & SHF_EXECINSTR)
		{
			// Write permissions on code
			shdr->sh_flags = swap64(flags | SHF_WRITE);
		}
		
		shdr++;
	}
	
	f = fopen(dst, "wb");
	fwrite(buf, 1, size, f);
	fclose(f);
}

uint8_t ps2gen(char *self_input, char *self_output, uint8_t *payload, uint32_t payload_size)
{
	uint8_t type;
	
	if(strstr(self_input, "ps2_emu.self")) {
		type=HW;
		print_load("Patching ps2_emu.self");
	} else
	if(strstr(self_input, "ps2_gxemu.self")) {
		type=GX;
		print_load("Patching ps2_gxemu.self");
	} else 
	if(strstr(self_input, "ps2_netemu.self")) {
		type=NET;
		print_load("Patching ps2_netemu.self");
	} else {
		print_load("Error : use this only with ps2 self files");
		return FAILED;
	}	
	
	uint64_t load_size=0;
	char tmp_elf[128];
	char tmp_self[128];
	char tmp_dir[128]; 
	
	sprintf(tmp_dir, "/dev_hdd0/game/%s/USRDIR/temp", ManaGunZ_id);
	sprintf(tmp_self, "/dev_hdd0/game/%s/USRDIR/temp/temp.self", ManaGunZ_id);
	sprintf(tmp_elf, "/dev_hdd0/game/%s/USRDIR/temp/temp.elf", ManaGunZ_id);
	
	Delete(tmp_self);
	Delete(tmp_elf);
	mkdir(tmp_dir, 0777);

	if(type == NET) {
		patch_netself(self_input, tmp_self, &load_size);
	} else {
		patch_self(self_input, tmp_self, type);	
	}
	
	Extract_SELF(tmp_self, tmp_elf);	
		
	if( Search_Offset(tmp_elf, type) < 0) {
		print_load("Error : failed to find offsets");
		Delete(tmp_elf);
		Delete(tmp_self);
		return FAILED;
	}
	
	FILE *elf;
	
	elf = fopen(tmp_elf, "rb+");
	if (!elf)
	{
		print_load("Error : Cannot open temp.elf");
		Delete(tmp_elf);
		Delete(tmp_self);
		return FAILED;
	}
	
	if(type == NET) {
		
		ps2_netemu = malloc(load_size);
		if (!ps2_netemu)
		{
			print_load("Error : Cannot allocate %ld bytes", (unsigned long int)load_size);
			Delete(tmp_elf);
			Delete(tmp_self);
			return FAILED;
		}
		
		fseek(elf, 0x10000, SEEK_SET);
		if (fread(ps2_netemu, 1, load_size, elf) != load_size)
		{
			print_load("Error : fread read less than load_size");
			Delete(tmp_elf);
			Delete(tmp_self);
			return FAILED;
		}
		
		memcpy(ps2_netemu+payload_addr, payload, payload_size);
		
		patch_netemu();
		
		fseek(elf, 0x10000, SEEK_SET);
		fwrite(ps2_netemu, 1, load_size, elf);	
		free(ps2_netemu);
	
	} else {
		fseek(elf, payload_addr, SEEK_SET);
		fwrite(payload, 1, payload_size, elf);
	}
	
	fclose(elf);

	if( Sign_PS2ELF( tmp_elf, self_output) == FAILED ) {
		print_load("Error : failed to sign temp.elf");
		Delete(tmp_elf);
		Delete(tmp_self);
		return FAILED;
	}
	
	Delete(tmp_elf);
	Delete(tmp_self);
	
	return SUCCESS;
}
