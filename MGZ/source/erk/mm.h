#ifndef _MM_H_
#define _MM_H_

#include "common.h"

#define HTAB_HASH_MASK  0x7FFULL
#define HPTES_PER_GROUP 8

#define HPTE_V_AVPN_SHIFT 7
#define HPTE_V_BOLTED     0x0000000000000010ULL
#define HPTE_V_LARGE      0x0000000000000004ULL
#define HPTE_V_VALID      0x0000000000000001ULL
#define HPTE_V_FLAGS_MASK 0x000000000000007FULL

#define HPTE_R_R          0x0000000000000100ULL
#define HPTE_R_C          0x0000000000000080ULL
#define HPTE_R_W          0x0000000000000040ULL
#define HPTE_R_I          0x0000000000000020ULL
#define HPTE_R_M          0x0000000000000010ULL
#define HPTE_R_G          0x0000000000000008ULL
#define HPTE_R_N          0x0000000000000004ULL
#define HPTE_R_PROT_MASK  0x0000000000000003ULL
#define HPTE_R_FLAGS_MASK 0x000000000000FFFFULL

#define PAGE_SIZES(ps0, ps1) (((uint64_t)(ps0) << 56) | ((uint64_t)(ps1) << 48))

#define PAGE_SIZE_4KB  12
#define PAGE_SIZE_64KB 16
#define PAGE_SIZE_1MB  20
#define PAGE_SIZE_16MB 24

#define MM_LOAD_BASE(ptr, offset) \
	__asm__ __volatile__ ( \
		"li %0, 1;" \
		"rldicr %0, %0, 63, 0;" \
		"oris %0, %0, %1;" \
		"ori %0, %0, %2" \
		: "=r"(ptr) \
		: "g"(((offset) >> 16) & 0xFFFF), "g"((offset) & 0xFFFF) \
	)

#define MM_EA2VA(ea) ((uint64_t)(ea) & ~(1ULL << 63))

int mm_insert_htab_entry(uint64_t va_address, uint64_t lpar_address, uint64_t protection, uint64_t* index);
int mm_map_lpar_memory_region(uint64_t lpar_start_address, uint64_t ea_start_address, uint64_t size, uint64_t page_shift, uint64_t protection);

int patch_htab_entry(uint64_t vas_id, uint64_t hpte_index);
int patch_htab_group_entry(uint64_t vas_id, uint64_t hpte_group, uint64_t hpte_group_index);
int patch_htab_entries(uint64_t vas_id);

#endif
