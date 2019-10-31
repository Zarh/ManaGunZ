#ifndef __UTIL_H__
#define __UTIL_H__

#include "common.h"

#define TB_TICKS_PER_SEC 79800000

#define INSTR_B(from, to) ((0x48UL << 24) | ((uint64_t)((int64_t)(to) - (int64_t)(from)) & 0x3FFFFFFUL))
#define INSTR_BL(from, to) ((0x48UL << 24) | ((uint64_t)((int64_t)(to) - (int64_t)(from)) & 0x3FFFFFFUL) | 0x1)

//void lv2_patch_error(uint64_t lis_addr, uint32_t lis_instr, uint64_t ori_addr, uint32_t ori_instr);

uint64_t clear_data(void* dst, uint64_t size);
uint64_t copy_data(void* dst, const void* src, uint64_t size);

void sleep(uint64_t ticks);
void hang(void);

static INLINE uint64_t mflr(void) {
	uint64_t result;
	__asm__ __volatile__ (
		"mflr %0;"
		: "=r"(result)
	);
	return result;
}

static INLINE uint64_t mfpvr(void) {
	uint64_t result;
	__asm__ __volatile__ (
		"mfpvr %0;"
		: "=r"(result)
	);
	return result;
}

static INLINE uint64_t mfmsr(void) {
	uint64_t result;
	__asm__ __volatile__ (
		"mfmsr %0;"
		: "=r"(result)
	);
	return result;
}

static INLINE uint64_t mfdar(void) {
	uint64_t result;
	__asm__ __volatile__ (
		"mfdar %0;"
		: "=r"(result)
	);
	return result;
}

static INLINE void mtdec(uint64_t x) {
	__asm__ __volatile__ (
		"mtdec %0;"
		:
		: "r"(x)
	);
	return;
}

static INLINE void mttb(uint64_t x) {
	__asm__ __volatile__ (
		"mtspr tbl, %0;"
		:
		: "r"(x)
	);
	return;
}

static INLINE uint64_t mftb(void) {
	uint64_t result;
	__asm__ __volatile__ (
		"mftb %0;"
		: "=r"(result)
	);
	return result;
}

static INLINE void mttbu(uint64_t x) {
	__asm__ __volatile__ (
		"mtspr tbu, %0;"
		:
		: "r"(x)
	);
	return;
}

static INLINE uint64_t mftbu(void) {
	uint64_t result;
	__asm__ __volatile__ (
		"mftbu %0;"
		: "=r"(result)
	);
	return result;
}

static INLINE uint64_t mfl2cr(void) {
	uint64_t result;
	__asm__ __volatile__ (
		"mfspr %0, l2cr"
		: "=r"(result)
	);
	return result;
}

static INLINE uint64_t mfctr(void) {
	uint64_t result;
	__asm__ __volatile__ (
		"mfctr %0;"
		: "=r"(result)
	);
	return result;
}

static INLINE uint64_t mfsprg0(void) {
	uint64_t result; 
	__asm__ __volatile__ (
		"mfsprg0 %0;"
		: "=r"(result)
	);
	return result;
}

#define eieio() __asm__ __volatile__ ("eieio")
#define mb() __asm__ __volatile__ ("sync" : : : "memory")
#define rmb() __asm__ __volatile__ ("sync" : : : "memory")
#define wmb() __asm__ __volatile__ ("sync" : : : "memory")
#define sync() __asm__ __volatile__ ("sync")
#define isync() __asm__ __volatile__ ("isync")
#define lwsync() __asm__ __volatile__ ("lwsync" : : : "memory")
#define nop() __asm__ __volatile__ ("nop")

static inline uint64_t align_up(uint64_t x, uint64_t alignment)
{
	return ((x - 1) & ~((alignment) - 1)) + (alignment);
}

static inline void* ptr_align_up(void* p, uint64_t alignment)
{
	return (void*)align_up((uint64_t)p, alignment);
}

#endif