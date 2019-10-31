#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#include "kernel.h"

struct opd64_entry_t {
	uint64_t address;
	uint64_t toc;
} opd64_entry_t;

KERNEL_EXPORT int sys_dbg_get_process_list(uint64_t r3, uint64_t r4, uint64_t r5);

#endif