#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SWAP32(x) ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | (((x) >> 24) & 0xff))

#define MAKE_JUMP_VALUE(addr, to) ((0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2))
#define MAKE_CALL_VALUE(addr, to) ((0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2)) | 1

#define ADDITIONAL_SIZE		0x10000

uint8_t GX;

char *PWD;
char temp[2048];

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

/*static void command2(char *cmd, char *arg1, char *arg2)
{
	char buf[2048];
	
	snprintf(buf, sizeof(buf), "%s %s %s", cmd, arg1, arg2);
	system(buf);
}*/

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

static void patch_self(char *src, char *dst)
{
	char *buf;
	FILE *f;
	
	int extend_ph=1;
	int extend_sh=1;
	
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
	
	uint32_t sh_offset, data_address;
	
	memcpy(&sh_offset, buf + 0x44, 4);
	sh_offset = SWAP32(sh_offset) + 0x40;
	
	memcpy(&data_address, buf + 0xF4, 4);
	data_address = SWAP32(data_address);
	
	if(GX) {
		data_address += 0x60;
	} else {
		extend_sh=0;
		extend_ph=0;
	}
	
	printf("DATA ADDR : %X\n", data_address);
	printf("SH ADDR : %X\n", sh_offset);
	
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

int main(int argc, char *argv[])
{	
	
	PWD = getenv("PWD");
	char *PS3ENV = getenv("PS3");
	if(PS3ENV==NULL) {
		printf("Environnement variable 'PS3' is missing.\nType : export PS3=$PS3DEV/bin/data\nscetool need it to load the keys.\n\n");
		return 0;
	}
	
	char *payload, *self_input;
	char self_output[255];
	uint32_t payload_addr, payload_size;
	
	FILE *bin, *elf;
	uint8_t *payload_buf;

	self_input = argv[1];
	
	payload = argv[2];
	sprintf(self_output, "PATCHED_%s", self_input);
	
	
	if(strstr(self_input, "ps2_gxemu.self") != NULL ) {
		GX=1;
	} else 
	if(strstr(self_input, "ps2_emu.self") != NULL ) {
		GX=0;
	} else {
		printf("Input must be 'ps2_gxemu.self' or 'ps2_emu.self'");
		return 1;
	}
	
	patch_self(self_input, "temp.self");	
	sprintf(temp, "scetool --decrypt", "%s/temp.self", "%s/temp.elf", PWD, PWD);
	system(temp);
	
	system("del temp.self");
	
	bin = fopen(payload, "rb");
	if (!bin)
	{
		printf("Cannot open %s\n", payload);
		return -2;
	}
	
	fseek(bin, 0, SEEK_END);
	payload_size = ftell(bin);
	fseek(bin, 0, SEEK_SET);
	
	payload_buf = malloc(payload_size);
	if (!payload_buf)
	{
		printf("Cannot allocate payload\n");
		return -3;
	}
	
	fread(payload_buf, 1, payload_size, bin);
	fclose(bin);
	
	elf = fopen("temp.elf", "rb+");
	if (!elf)
	{
		printf("Cannot open temp.elf\n");
		return -4;
	}
	
	{ // get payload_addr
		fseek (elf , 0 , SEEK_END);
		uint32_t size = ftell (elf);
		fseek(elf, 0, SEEK_SET);
	
		char *mem = (char *) malloc(size);
		if (!mem)
		{
			printf("Cannot allocate mem\n");
			return -3;
		}		
		fread(mem,size,1,elf);

		if(GX) {
			uint8_t flag[0x1C] = {0x79, 0x29, 0x80, 0x00, 0x7D, 0x20, 0x01, 0x64, 0x55, 0x60, 0x06, 0x3C, 0x4B, 0xFF, 0xFF, 0x8C, 0x38, 0x60, 0x00, 0x01, 0x4B, 0xFB, 0x32, 0x85, 0x60, 0x00, 0x00, 0x00};
			int n;
			for(n=0x10000; n<size ; n++) {
				if(!memcmp((char *) &mem[n], (char *) flag, 0x1C)) {
					payload_addr = n + 0x1C;
					printf("PAYLOAD ADDR : %X\n", payload_addr - 0x10000);
					break;
				}
			}
		} 
		else {
			uint8_t flag[0x1C] = {0x7C, 0xFF, 0x30, 0x38, 0x2F, 0x9F, 0x00, 0x00, 0x40, 0x9E, 0xFD, 0x3C, 0x4B, 0xFF, 0xFE, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x03, 0x80, 0x0C, 0x00, 0x00};
			int n;
			for(n=0x10000; n<size ; n++) {
				if(!memcmp((char *) &mem[n], (char *) flag, 0x1C)) {
					payload_addr = n + 0x1C;
					printf("PAYLOAD ADDR : %X\n", payload_addr - 0x10000);
					break;
				}
			}
		}
		free(mem);
	}
	
	fseek(elf, payload_addr, SEEK_SET);
	fwrite(payload_buf, 1, payload_size, elf);
	
	fclose(elf);
	
	sprintf(temp, "scetool -v --sce-type=SELF --compress-data=TRUE --compress-data=TRUE --skip-sections=FALSE --self-auth-id=1020000401000001 --self-add-shdrs=TRUE --self-vendor-id=02000003 --self-type=LV2 --self-fw-version=0004002100000000 --key-revision=0 --self-app-version=0001000000000000 --encrypt %s/temp.elf %s/%s", PWD, PWD, self_output);
	system(temp);
	
	
	system("del temp.elf");
	
	return 0;
}
