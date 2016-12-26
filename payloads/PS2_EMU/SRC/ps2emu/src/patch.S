#include <ps2emu/macros.h.S>
#include <ps2emu/symbols.h>

	.global clear_icache
clear_icache:

	add	%r4, %r3, %r4
	rldicr	%r3, %r3, 0, 56	
1:	
	cmpld	%r3, %r4
	bge	2f
	dcbst	0, %r3
	sync
	icbi	0, %r3
	isync
	addi	%r3, %r3, 0x80
	b	1b	
2:
	blr
	
	.global get_call_address
get_call_address:

	ld	%r5, 0(%sp)
	cmpwi	%r3, 0
	ble	4f
	mtctr	%r3	
3:
	cmpdi	%r5, 0
	beq	5f
	ld	%r5, 0(%r5)
	bdnz	3b	
4:	
	cmpdi	%r5, 0
	beq	5f
	ld	%r3, 0x10(%r5)
	addi	%r3, %r3, -4
	blr	
5:
	li	%r3, 0
	blr
	
	.global get_patched_func_call_address
get_patched_func_call_address:

	ld 	%r3, 0(%sp)
	cmpdi	%r3, 0
	beq	6f
	ld	%r3, 0x20(%r3)
	cmpdi	%r3, 0
	beq	6f
	addi	%r3, %r3, -4
6: 
	blr

	.global call_hooked_function
call_hooked_function:

	std	%rtoc, 0x28(%sp)
	stdu	%sp, -0x70(%sp)
	mflr	%r0
	std	%r0, 0x80(%sp)
	
	ld	%r0, 0(%r3)
	mtctr	%r0
	mr	%r3, %r4
	mr	%r4, %r5
	mr	%r5, %r6
	mr	%r6, %r7
	mr	%r7, %r8
	mr	%r8, %r9
	mr	%r9, %r10
	
	li	%r0, 0
	LOAD_LABEL(%rtoc, %r0, TOC)
	bctrl
		
	ld	%r0, 0x80(%sp)
	mtlr	%r0
	addi	%sp, %sp, 0x70
	ld	%rtoc, 0x28(%sp)
	blr


	
