#include "mm.h"
#include "hvcall.h"
#include "utils.h"

int mm_insert_htab_entry(uint64_t va_address, uint64_t lpar_address, uint64_t protection, uint64_t* index) {
	int result;

	uint64_t hpte_group, hpte_index = 0, hpte_v, hpte_r, hpte_evicted_v, hpte_evicted_r;

	hpte_group = (((va_address >> 28) ^ ((va_address & 0xFFFFFFFULL) >> 12)) & 0x7FF) << 3;
	hpte_v = ((va_address >> 23) << 7) | HPTE_V_VALID;
	hpte_r = lpar_address | 0x38 | (protection & HPTE_R_PROT_MASK);

	result = lv1_insert_htab_entry(0, hpte_group, hpte_v, hpte_r, HPTE_V_BOLTED, 0, &hpte_index, &hpte_evicted_v, &hpte_evicted_r);
	if (result != 0)
		return result;

	if (index)
		*index = hpte_index;

	return 0;
}

int mm_map_lpar_memory_region(uint64_t lpar_start_address, uint64_t ea_start_address, uint64_t size, uint64_t page_shift, uint64_t protection) {
	int result;

	uint64_t i;

	for (i = 0; i < (size >> page_shift); ++i) {
		result = mm_insert_htab_entry(MM_EA2VA(ea_start_address), lpar_start_address, protection, 0);
 		if (result != 0) 
 			return result;

		lpar_start_address += (1 << page_shift);
		ea_start_address += (1 << page_shift);
	}

	return 0;
}

int patch_htab_entry(uint64_t vas_id, uint64_t hpte_index) {
	int result;

	uint64_t hpte_offset = HTAB_BASE + HTAB_ENTRY_SIZE * hpte_index;
	uint64_t hpte_pte0 = lv2_peek64(hpte_offset + 0);
	uint64_t hpte_pte1 = lv2_peek64(hpte_offset + HTAB_ENTRY_SIZE / 2);
	uint64_t hpte_va = hpte_pte0;
	uint64_t hpte_pa = (hpte_pte1 & 0xFF0000ULL) | HPTE_R_R | HPTE_R_C | HPTE_R_M;

	result = lv1_write_htab_entry(vas_id, hpte_index, hpte_va, hpte_pa);
	if (result != 0)
		goto error;

	result = 0;

error:
	return result;
}

int patch_htab_group_entry(uint64_t vas_id, uint64_t hpte_group, uint64_t hpte_group_index) {
	return patch_htab_entry(vas_id, hpte_group * HPTES_PER_GROUP + hpte_group_index);
}

int patch_htab_entries(uint64_t vas_id) {
	int result;

	const uint64_t num_hpte_groups = 128;
	uint64_t hpte_group;

	for (hpte_group = 0; hpte_group < num_hpte_groups; ++hpte_group) {
		result = patch_htab_group_entry(vas_id, hpte_group, 0);
		if (result != 0)
			goto error;
	}

	result = 0;

error:
	return result;
}
