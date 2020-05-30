#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ppu-types.h>

//#include <sys/syscall.h>
#include "common.h"
#include <ppu-lv2.h>

#define SYSCALL_POKE_WITH_CACHE_OFFSET SYSCALL_CODE_OFFSET(SYSCALL_POKE_WITH_CACHE)
extern u64 SYSCALL_TABLE;

static int poke_syscall = SYSCALL_LV2_POKE;
static int old_poke_syscall = -1;

static const uint32_t poke_with_cache_code[] = {
	0xF8830000,
	0x7C001FAC,
	0x4C00012C,
	0x4E800020,
};

static const uint64_t poke_with_cache_code_size = sizeof(poke_with_cache_code);
static uint32_t* poke_with_cache_original_code = NULL;

uint64_t lv1_peek64(uint64_t address) {
	lv2syscall1(SYSCALL_LV1_PEEK, address);
	return_to_user_prog(uint64_t);
}

void lv1_poke64(uint64_t address, uint64_t value) {
	lv2syscall2(SYSCALL_LV1_POKE, address, value);
}

uint64_t lv2_peek64(uint64_t address) {
	lv2syscall1(SYSCALL_LV2_PEEK, address);
	return_to_user_prog(uint64_t);
}

uint32_t lv2_peek32(uint64_t address) {
	return (lv2_peek64(address) >> 32) & 0xFFFFFFFFUL;
}

uint16_t lv2_peek16(uint64_t address) {
	return (lv2_peek64(address) >> 48) & 0xFFFFUL;
}

uint8_t lv2_peek8(uint64_t address) {
	return (lv2_peek64(address) >> 56) & 0xFFUL;
}

void lv2_poke64(uint64_t address, uint64_t value) {
	lv2syscall2(poke_syscall, address, value);
}

void lv2_poke32(uint64_t address, uint32_t value) {
	uint64_t old_value = lv2_peek64(address);
	lv2_poke64(address, ((uint64_t)value << 32) | (old_value & 0xFFFFFFFFULL));
}

void lv2_poke16(uint64_t addr, uint16_t value) {
	uint64_t old_value = lv2_peek64(addr);
	lv2_poke64(addr, ((uint64_t)value << 48) | (old_value & 0xFFFFFFFFFFFFULL));
}

void lv2_poke8(uint64_t addr, uint8_t value) {
	uint64_t old_value = lv2_peek64(addr);
	lv2_poke64(addr, ((uint64_t)value << 56) | (old_value & 0xFFFFFFFFFFFFFFULL));
}

void lv2_copy_from_user(const void* src, uint64_t dst, uint64_t size) {
	if (size == 0)
		return;
	const uint8_t* in = (const uint8_t*)src;
	while (size >= sizeof(uint64_t)) {
		lv2_poke64(dst, *(const uint64_t*)in);
		dst += sizeof(uint64_t); in += sizeof(uint64_t);
		size -= sizeof(uint64_t);
	}
	while (size >= sizeof(uint32_t)) {
		lv2_poke32(dst, *(const uint32_t*)in);
		dst += sizeof(uint32_t); in += sizeof(uint32_t);
		size -= sizeof(uint32_t);
	}
	while (size >= sizeof(uint16_t)) {
		lv2_poke16(dst, *(const uint16_t*)in);
		dst += sizeof(uint16_t); in += sizeof(uint16_t);
		size -= sizeof(uint16_t);
	}
	if (size > 0) {
		lv2_poke8(dst, *(const uint8_t*)in);
		size--;
	}
}

void lv2_copy_to_user(uint64_t src, const void* dst, uint64_t size) {
	if (size == 0)
		return;
	uint8_t* out = (uint8_t*)dst;
	while (size >= sizeof(uint64_t)) {
		*(uint64_t*)out = lv2_peek64(src);
		src += sizeof(uint64_t); out += sizeof(uint64_t);
		size -= sizeof(uint64_t);
	}
	while (size >= sizeof(uint32_t)) {
		*(uint32_t*)out = lv2_peek32(src);
		src += sizeof(uint32_t); out += sizeof(uint32_t);
		size -= sizeof(uint32_t);
	}
	while (size >= sizeof(uint16_t)) {
		*(uint16_t*)out = lv2_peek16(src);
		src += sizeof(uint16_t); out += sizeof(uint16_t);
		size -= sizeof(uint16_t);
	}
	if (size > 0) {
		*(uint8_t*)out = lv2_peek8(src);
		size--;
	}
}

int run_payload(uint64_t arg, uint64_t arg_size) {
	lv2syscall2(SYSCALL_RUN_PAYLOAD, (uint64_t)arg, (uint64_t)arg_size);
	return_to_user_prog(int);
}

int reboot(void) {
	lv2syscall4(SYSCALL_SM_SHUTDOWN, 0x8201, 0, 0, 0);
	return_to_user_prog(int);
}

int console_write(const char* message, unsigned int length) {
	lv2syscall2(SYSCALL_CONSOLE_WRITE, (uint64_t)(uintptr_t)message, (uint64_t)length);
	return_to_user_prog(int);
}

int console_printf(const char* format, ...) {
	char msg_buf[1024];
	va_list args;

	va_start(args, format);
	vsnprintf(msg_buf, sizeof(msg_buf), format, args);
	va_end(args);

	return console_write(msg_buf, strlen(msg_buf));
}

int ring_buzzer(uint64_t arg1, uint8_t arg2, uint32_t arg3) {
	lv2syscall3(SYSCALL_RING_BUZZER, (uint64_t)arg1, (uint64_t)arg2, (uint64_t)arg3);
	return_to_user_prog(int);
}

int triple_beep(void) {
	return ring_buzzer(0x1004, 0x0A, 0x1B6);
}

int install_new_poke(void) {
	poke_with_cache_original_code = (uint32_t*)malloc(poke_with_cache_code_size);
	if (!poke_with_cache_original_code)
		return FAILED;

	memset(poke_with_cache_original_code, 0, poke_with_cache_code_size);

	old_poke_syscall = poke_syscall;

	lv2_copy_to_user(SYSCALL_POKE_WITH_CACHE_OFFSET, poke_with_cache_original_code, poke_with_cache_code_size);
	lv2_copy_from_user(poke_with_cache_code, SYSCALL_POKE_WITH_CACHE_OFFSET, poke_with_cache_code_size);

	poke_syscall = SYSCALL_POKE_WITH_CACHE;

	return SUCCESS;
}

int remove_new_poke(void) {
	if (!poke_with_cache_original_code)
		return FAILED;

	poke_syscall = old_poke_syscall;
	old_poke_syscall = -1;

	lv2_copy_from_user(poke_with_cache_original_code, SYSCALL_POKE_WITH_CACHE_OFFSET, poke_with_cache_code_size);

	free(poke_with_cache_original_code);
	poke_with_cache_original_code = NULL;

	return SUCCESS;
}

