#include <ps2emu/symbols.h>

.global _start

_start:

	stdu 	%sp, -0xA0(%sp)
	mflr	%r0
	std	%r0, 0xB0(%sp)
	std	%r23, 0x70(%sp)
	std	%r24, 0x78(%sp)
	std	%r25, 0x80(%sp)
	std	%r26, 0x88(%sp)
	std	%r31, 0x90(%sp)
	std	%r30, 0x98(%sp)
		
	// Save registers
	mr	%r23, %r3
	mr	%r24, %r4
	mr	%r25, %r5
	mr	%r26, %r6
	
	lis	%r31, stage2_addr@ha
	addi	%r31, %r31, stage2_addr@l
	
	// r30 = ufs_open (0, stage2_file);
	li	%r3, 0
	lis	%r4, (stage1_addr+stage2_file)@ha
	addi	%r4, %r4, (stage1_addr+stage2_file)@l
	bla	ufs_open_symbol
	mr	%r30, %r3	
	
	// ufs_read(r30, 0, r31, 0x10000);
	li	%r4, 0
	mr	%r5, %r31
	lis	%r6, 1
	bla	ufs_read_symbol
	
	// ufs_close(r30);
	mr	%r3, %r30
	bla	ufs_close_symbol
	
	// clear_icache(r31, 0x10000);
	mr	%r3, %r31
	lis	%r4, 1
	bl	clear_icache	
	
	// Stage2 call
	mr	%r3, %r23
	mr	%r4, %r24
	mr	%r5, %r25
	mr	%r6, %r26
	mtctr	%r31
	bctrl	
	
# Exit must be at stage2
	
	/*ld	%r23, 0x70(%sp)
	ld	%r24, 0x78(%sp)
	ld	%r25, 0x80(%sp)
	ld	%r26, 0x88(%sp)
	ld	%r31, 0x90(%sp)
	ld	%r30, 0x98(%sp)
	ld	%r0, 0xB0(%sp)
	mtlr	%r0
	addi	%sp, %sp, 0xA0
	blr*/
	
stage2_file:
	
.string "/vm/pm0"
	

	
