#include "mm.h"
#include "hypervisor.h"

int mm_insert_htab_entry(uint64_t vas_id, uint64_t va_addr, uint64_t lpar_addr, uint64_t page_shift, uint64_t vflags, uint64_t rflags, uint64_t* index) {
	int result;

	uint64_t hpte_group, hpte_index, hpte_v, hpte_r, hpte_evicted_v, hpte_evicted_r;

	hpte_index = 0;
	hpte_group = (((va_addr >> 28) ^ ((va_addr & 0xFFFFFFFULL) >> page_shift)) & HTAB_HASH_MASK) * HPTES_PER_GROUP;

	hpte_v = ((va_addr >> 23) << HPTE_V_AVPN_SHIFT) | HPTE_V_VALID | (vflags & HPTE_V_FLAGS_MASK);
	if (page_shift != PAGE_SIZE_4KB)
		hpte_v |= HPTE_V_LARGE;

	hpte_r = (lpar_addr & ~((1ULL << page_shift) - 1)) | (rflags & HPTE_R_FLAGS_MASK);
	if (page_shift == PAGE_SIZE_1MB)
		hpte_r |= (1 << 12);

	result = lv1_insert_htab_entry(vas_id, hpte_group, hpte_v, hpte_r, HPTE_V_BOLTED, 0, &hpte_index, &hpte_evicted_v, &hpte_evicted_r);
	if (result != 0)
		return result;

	if (index)
		*index = hpte_index;

	return 0;
}

int mm_map_lpar_memory_region(uint64_t vas_id, uint64_t va_start_addr, uint64_t lpar_start_addr, uint64_t size, uint64_t page_shift, uint64_t vflags, uint64_t rflags) {
	int result;

	uint64_t i;
	for (i = 0; i < (size >> page_shift); ++i) {
		result = mm_insert_htab_entry(vas_id, va_start_addr, lpar_start_addr, page_shift, vflags, rflags, 0);
 		if (result != 0) 
 			return result;

		va_start_addr += 1ULL << page_shift;
		lpar_start_addr += 1ULL << page_shift;
	}

	return 0;
}

int mm_lpar_addr_to_ra(uint64_t lpar_addr, uint64_t* ra) {
	int result;

	static volatile uint64_t va_addr = 0x5000000000000ULL;

	uint64_t hpte_index;
	uint64_t hpte_v;
	uint64_t hpte_r;
	uint64_t* htab;

	hpte_index = GAMEOS_HTAB_SIZE / 16 - 1;

	result = lv1_write_htab_entry(0, hpte_index, 0, 0);
	if (result != 0)
		return result;

	hpte_v = ((va_addr >> 23) << HPTE_V_AVPN_SHIFT) | HPTE_V_VALID;
	hpte_r = lpar_addr & ~((1ULL << 12) - 1);

	result = lv1_write_htab_entry(0, hpte_index, hpte_v, hpte_r);
	if (result != 0)
		return result;

	MM_LOAD_BASE(htab, GAMEOS_HTAB_OFFSET);

	if (ra)
		*ra = (htab[hpte_index * 2 + 1] & ~((1ULL << 12) - 1)) + (lpar_addr & ((1ULL << 12) - 1));

	result = lv1_write_htab_entry(0, hpte_index, 0, 0);
	if (result != 0)
		return result;

	return 0;
}

int mm_phys_ra_to_lpar_addr(uint64_t ra, uint64_t* lpar_addr) {
	static struct {
		uint64_t lpar_addr;
		uint64_t size;
		int num_regions;

		struct {
			uint64_t ra;
			uint64_t size;
		} ra_regions[8];
	} lpar_ra_regions[] = {
		{
			0x0000000000000000ULL,
			0x1000000ULL,
			1,
			{
				{ 0x1000000ULL, 0x1000000ULL },
			}
		},
		{
			0x500000300000ULL,
			0xA0000ULL,
			5,
			{
				{ 0x380000ULL, 0x10000ULL },
				{ 0x3B0000ULL, 0x10000ULL },
				{ 0x1E0000ULL, 0x20000ULL },
				{ 0x3C0000ULL, 0x40000ULL },
				{ 0xFF00000ULL, 0x20000ULL },
			}
		},
		{
			0x700020000000ULL,
			0xE900000ULL,
			3,
			{
				{ 0x400000ULL, 0x200000ULL },
				{ 0x800000ULL, 0x800000ULL },
				{ 0x2000000ULL, 0xDF00000ULL },
			}
		},
	};

	uint64_t ra_region_lpar_addr, ra_region_start, ra_region_size;
	int i, j;

	for (i = 0; i < COUNT_OF(lpar_ra_regions); ++i) {
		ra_region_lpar_addr = lpar_ra_regions[i].lpar_addr;

		for (j = 0; j < lpar_ra_regions[i].num_regions; ++j) {
			ra_region_start = lpar_ra_regions[i].ra_regions[j].ra;
			ra_region_size = lpar_ra_regions[i].ra_regions[j].size;

			if ((ra >= ra_region_start) && (ra < (ra_region_start + ra_region_size))) {
				if (lpar_addr)
					*lpar_addr = ra_region_lpar_addr + (ra - ra_region_start);
				return 0;
			}

			ra_region_lpar_addr += ra_region_size;
		}
	}

	return -1;
}
