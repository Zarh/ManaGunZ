#ifndef _HVCALL_H
#define _HVCALL_H

#include "common.h"

int lv1_insert_htab_entry(uint64_t htab_id, uint64_t hpte_group, uint64_t hpte_v, uint64_t hpte_r, uint64_t bolted_flag, uint64_t flags, uint64_t* hpte_index, uint64_t* hpte_evicted_v, uint64_t* hpte_evicted_r);
int lv1_write_htab_entry(uint64_t vas_id, uint64_t hpte_index, uint64_t hpte_v, uint64_t hpte_r);

int lv1_allocate_memory(uint64_t size, uint64_t page_size_exp, uint64_t flags, uint64_t* addr, uint64_t* muid);

int lv1_map_memory_area(uint64_t start, uint64_t page_size, uint64_t size, uint64_t* lpar_addr);
int lv1_unmap_memory_area(uint64_t lpar_addr);

int lv1_panic(uint64_t flag);

#endif
