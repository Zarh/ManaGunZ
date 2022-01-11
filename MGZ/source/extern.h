#include <ppu-types.h>

#define printf		 		 	print_load
#define print_verbose 			print_debug

// https://www.cs.technion.ac.il/users/yechiel/c++-faq/macros-with-if.html
#define print_debug(...) 		if( DEBUG ) print_load(__VA_ARGS__); else (void)0
								

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

extern u64 HTAB_PATCH1;
extern u64 HTAB_PATCH2;
extern u64 HTAB_PATCH3;

extern u64 lv2peek(u64 addr);
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
extern u8 copy_cancel;
extern void task_Init(const u64 max);
extern void task_Update(u64 val);
extern void task_Update2(u64 val);
extern void task_End();
