/*
* Copyright (c) 2011-2012 by ps3dev.net
* This file is released under the GPLv2.
*/

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <ppu-types.h>

uint64_t lv1_peek64(uint64_t address);
void lv1_poke64(uint64_t address, uint64_t value);

uint64_t lv2_peek64(uint64_t address);
uint32_t lv2_peek32(uint64_t address);
uint16_t lv2_peek16(uint64_t address);
uint8_t lv2_peek8(uint64_t address);

void lv2_poke64(uint64_t address, uint64_t value);
void lv2_poke32(uint64_t address, uint32_t value);
void lv2_poke16(uint64_t addr, uint16_t value);
void lv2_poke8(uint64_t addr, uint8_t value);

void lv2_copy_from_user(const void* src, uint64_t dst, uint64_t size);
void lv2_copy_to_user(uint64_t src, const void* dst, uint64_t size);

int run_payload(uint64_t arg, uint64_t arg_size);

int reboot(void);

int console_write(const char* message, unsigned int length);
int console_printf(const char* format, ...);

int ring_buzzer(uint64_t arg1, uint8_t arg2, uint32_t arg3);
int triple_beep(void);

int install_new_poke(void);
int remove_new_poke(void);


#endif
