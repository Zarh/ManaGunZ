#include <ppu-lv2.h>

#include "dumper.h"
#include "payload.h"

#define ERK_PAYLOAD_OFFSET       KERNEL_ADDRESS(0x7F0000)
#define ERK_PAYLOAD_OPD_OFFSET   KERNEL_ADDRESS(0x1830)

static uint64_t real_opd_offset = 0;
extern u64 TOC;
extern u64 SYSCALL_TABLE;
extern u64 *ERK_DUMPER;
extern size_t ERK_DUMPER_SIZE;

int install_payload(void) {

	if (ERK_DUMPER_SIZE <= 0)	return -1;
	
	lv2_copy_from_user(ERK_DUMPER, ERK_PAYLOAD_OFFSET, ERK_DUMPER_SIZE);

	lv2_poke64(ERK_PAYLOAD_OPD_OFFSET + 0, ERK_PAYLOAD_OFFSET);
	lv2_poke64(ERK_PAYLOAD_OPD_OFFSET + 8, TOC);

	real_opd_offset = SYSCALL_OPD_OFFSET(SYSCALL_RUN_PAYLOAD);
	lv2_poke64(SYSCALL_OPD_PTR_OFFSET(SYSCALL_RUN_PAYLOAD), ERK_PAYLOAD_OPD_OFFSET);

	return 0;
}

int remove_payload(void) {
	if (real_opd_offset != 0) {
		lv2_poke64(SYSCALL_OPD_PTR_OFFSET(SYSCALL_RUN_PAYLOAD), real_opd_offset);
		real_opd_offset = 0;
	}

	return 0;
}
