#include <ppu-types.h>

#define printf		 		 	print_load
#define print_verbose 			print_debug

// https://www.cs.technion.ac.il/users/yechiel/c++-faq/macros-with-if.html
#define print_debug(...) 		if( DEBUG ) print_load(__VA_ARGS__); else (void)0

#define LV2ADDR(x) 0x8000000000000000ULL + x

#define OK 			1
#define NOK 		0
#define YES			1
#define NO 			0
#define TRUE 		1
#define FALSE 		0
#define SUCCESS 	1
#define FAILED	 	0

#define IS_BIG_ENDIAN 			(!*(unsigned char *)&(uint16_t){1})
#define IS_LITTLE_ENDIAN		(*(unsigned char *)&(uint16_t){1})

#define ENDIAN_SWAP_16(x)		(((x) & 0x00FF) << 8 | ((x) & 0xFF00) >> 8)
#define ENDIAN_SWAP_32(x)		(((x) & 0x000000FF) << 24 | ((x) & 0x0000FF00) << 8 | \
								 ((x) & 0x00FF0000) >>  8 | ((x) & 0xFF000000) >> 24  )
#define ENDIAN_SWAP_64(x)		(((x) & 0x00000000000000FFULL) << 56 | ((x) & 0x000000000000FF00ULL) << 40 | \
								 ((x) & 0x0000000000FF0000ULL) << 24 | ((x) & 0x00000000FF000000ULL) <<  8 | \
								 ((x) & 0x000000FF00000000ULL) >>  8 | ((x) & 0x0000FF0000000000ULL) >> 24 | \
								 ((x) & 0x00FF000000000000ULL) >> 40 | ((x) & 0xFF00000000000000ULL) >> 56 )
#define ENDIAN_SWAP(x)			(sizeof(x) == 2 ? ENDIAN_SWAP_16(x) : (sizeof(x) == 4 ? ENDIAN_SWAP_32(x) : ENDIAN_SWAP_64(x)))

// note for me...
// SWAP to/from BigEndian & LittleEndian
// if the file is in LittleEndian (like IRD) use SWAP_LE
// if it's BigEndian (like ISO) use SWAP_BE
#define SWAP_BE(x)				(IS_BIG_ENDIAN    ? x : ENDIAN_SWAP(x))
#define SWAP_LE(x)				(IS_LITTLE_ENDIAN ? x : ENDIAN_SWAP(x))

#define FREE(x)					if(x!=NULL) {free(x);x=NULL;}
#define FCLOSE(x) 				if(x!=NULL) {fclose(x);x=NULL;}

extern u64 TOC;
extern int firmware;
extern u64 SYSCALL_TABLE;
extern u64 HV_START_OFFSET;
extern u64 HTAB_OFFSET;
extern u64 HTAB_PATCH1;
extern u64 HTAB_PATCH2;
extern u64 HTAB_PATCH3;
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
extern u64 PAYLOAD_SKY;
extern size_t PAYLOAD_SKY_SIZE;
extern u64 UMOUNT;
extern size_t UMOUNT_SIZE;
extern u64 MAMBA;
extern size_t MAMBA_SIZE;
extern u64 *MAMBA_LOADER;
extern size_t MAMBA_LOADER_SIZE;
extern u64 *ERK_DUMPER;
extern size_t ERK_DUMPER_SIZE;
extern u64 OFFSET_1_IDPS;
extern u64 OFFSET_2_IDPS;
extern u64 UFS_SB_ADDR;
extern u64 FW_DATE_OFFSET;
extern u64 FW_DATE_1;
extern u64 FW_DATE_2;

extern u64 lv2peek(u64 addr);
extern u64 lv1peek(u64 addr);
extern void MEM_lv2peek(uint64_t src, const void* dst, uint64_t size);
extern void MEM_lv1peek(uint64_t src, const void* dst, uint64_t size);
extern void remove_lv2_protection();
extern void write_htab(void);
extern u64 lv2poke(u64 addr, u64 value);
extern u8 dump_3Dump();
extern u8 *Load_3Dump();
extern void hex_print_load(char *data, size_t len);
extern u8 Copy(char *src, char *dst);
extern void Delete(char* path);
extern void print_head(char *format2, ...);
extern void print_load(char *format, ...);
extern u8 DEBUG;
extern u8 cancel;
extern u8 disable_cancel;
extern u8 copy_cancel;
extern void task_Init(const u64 max);
extern void task_Update(u64 val);
extern void task_Update2(u64 val);
extern void task_End();
extern char *ManaGunZ_path;
extern int64_t prog_bar1_value;
extern char ManaGunZ_id[10];
extern u8 SetFilePerms(char *path);
