#include "util.h"
#include "kernel.h"

/*
void lv2_patch_error(uint64_t lis_addr, uint32_t lis_instr, uint64_t ori_addr, uint32_t ori_instr)
{
	uint64_t value;
	value = (lv2_peek64(lis_addr) & 0xFFFFFFFFUL) | ((uint64_t)lis_instr << 32);
	lv2_poke64(lis_addr, value);
	value = (lv2_peek64(ori_addr) & 0xFFFFFFFFUL) | ((uint64_t)ori_instr << 32);
	lv2_poke64(ori_addr, value);
}
*/

uint64_t clear_data(void* dst, uint64_t size) {
	uint64_t count;
	uint64_t i;
	count = 1 + (size - 1) / sizeof(uint64_t);
	for (i = 0; i < count; ++i)
		*((uint64_t*)dst + i) = 0;
	return count;
}

uint64_t copy_data(void* dst, const void* src, uint64_t size) {
	uint64_t count;
	uint64_t i;
	count = 1 + (size - 1) / sizeof(uint64_t);
	for (i = 0; i < count; ++i)
		*((uint64_t*)dst + i) = *((uint64_t*)src + i);
	return count;
}

void sleep(uint64_t ticks) {
	uint64_t end = mftb() + ticks;
	while (mftb() < end) {
		nop();
	}
}
