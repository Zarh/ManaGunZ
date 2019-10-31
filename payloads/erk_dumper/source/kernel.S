#include "asm.h"
#include "symbols.h"

#define KERNEL_FUNCTION(name, address) \
	.section .name.text, "ax"; \
	.global name; \
	.align 3; \
	name:; \
	.quad KERNEL_BASE | address, KERNEL_BASE | KERNEL_TOC; \
	.previous; 

KERNEL_FUNCTION(lv2_extend_kstack, KERNEL_SYMBOL_EXTEND_KSTACK)
KERNEL_FUNCTION(lv2_memset, KERNEL_SYMBOL_MEMSET)
KERNEL_FUNCTION(lv2_memcpy, KERNEL_SYMBOL_MEMCPY)
KERNEL_FUNCTION(lv2_copy_to_user, KERNEL_SYMBOL_COPY_TO_USER)

GLOBAL(get_current_thread)
	mfsprg0 %r9
	ld %r4, 0xA0(%r9)
	ld %r3, 0x40(%r4)
	blr

GLOBAL(get_current_thread_name)
	mfsprg0 %r3
	blr

GLOBAL(get_current_process)
	mfsprg0 %r3
	lhz %r0, 0xC0(%r3)
	cmpwi cr7, %r0, 3
	beq cr7, loc_0
	ld %r3, 0xB0(%r3)
	blr
loc_0:                               
	mfsprg0 %r9
	ld %r11, 0x68(%r9)
	li %r3, 0
	ld %r11, 0(%r11)
	cmpdi cr7, %r11, 0
	beqlr cr7
	ld %r3, 0x80(%r11)
	blr

GLOBAL(suspend_interrupts)
	mfsprg0 %r9
	ld %r3, 0x48(%r9)
	li %r0, 2
	mtmsrd %r0, 1
	blr
	
GLOBAL(resume_interrupts)
	mfsprg0 %r9
	ld %r3, 0x48(%r9)
	li %r0, 0
	ori %r0, %r0, 0x8002
	lwsync
	mtmsrd %r0, 1
	blr

GLOBAL(lv1_peek64)
	mflr %r0
	std %r0, 0x10(%r1)
	li %r11, 0xB6
	sc 1
	mr %r3, %r4
	ld %r0, 0x10(%r1)
	mtlr %r0
	blr

GLOBAL(lv1_poke64)
	mflr %r0
	std %r0, 0x10(%r1)
	li %r11, 0xB7
	sc 1
	li %r3, 0
	ld %r0, 0x10(%r1)
	mtlr %r0
	blr

GLOBAL(lv2_peek64)
	ld %r3, 0(%r3)
	blr

GLOBAL(lv2_poke64)
	std %r4, 0(%r3)
	icbi 0, %r3
	isync
	blr

GLOBAL(lv2_poke64_no_sync)
	std %r4, 0(%r3)
	blr

GLOBAL(clear_icache)
	add %r4, %r3, %r4
	rldicr %r3, %r3, 0, 56	
1:	
	cmpld %r3, %r4
	bge 2f
	dcbst 0, %r3
	sync
	icbi 0, %r3
	isync
	addi %r3, %r3, 0x80
	b 1b	
2:
	blr	

GLOBAL(get_call_address)
	ld %r5, 0(%sp)
	cmpwi %r3, 0
	ble 4f
	mtctr %r3	
3:
	cmpdi %r5, 0
	beq 5f
	ld %r5, 0(%r5)
	bdnz 3b	
4:	
	cmpdi %r5, 0
	beq 5f
	ld %r3, 0x10(%r5)
	addi %r3, %r3, -4
	blr	
5:
	li %r3, 0
	blr	
