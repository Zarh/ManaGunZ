.text
	.section .start,"ax",@progbits
	.align 3

	.global _start

_start:

	mflr	%r0
	bl	1f
1:
	mflr 	%r8
	lis 	%r9, 1b@ha
	addi 	%r9, %r9, 1b@l
	subf 	%r8, %r9, %r8
	
	li	%r11, 0
	oris	%r11, %r11, 0xBAD
	ori	%r11, %r11, 0xCAFE	

	lis 	%r9, __reloc_start@ha
	addi 	%r9, %r9, __reloc_start@l
	lis 	%r10, __reloc_end@ha
	addi 	%r10, %r10, __reloc_end@l
	subf 	%r10, %r9, %r10
	srdi 	%r10, %r10, 3
	mtctr 	%r10
	add 	%r9, %r9, %r8

2:
	ld 	%r10, 0(%r9)
	srdi 	%r7, %r10, 32	
	cmpw 	%r7, %r11
	bne 	3f	
	rldicl 	%r10, %r10, 0, 32
	add 	%r10, %r10, %r8
	std 	%r10, 0(%r9)	
	
3:
	addi 	%r9, %r9, 8
	bdnz 	2b
	
4:
	std 	%r0, 0x10(%sp)
	stdu 	%sp, -0x80(%sp)
	std	%rtoc, 0x28(%sp)

	lis 	%rtoc, __toc@ha
	addi 	%rtoc, %rtoc, __toc@l
	add	%rtoc, %rtoc, %r8
	bl	crt0	
	
	ld	%rtoc, 0x28(%sp)
	addi 	%sp, %sp, 0x80
	
	// Stage1 return. 
	ld	%r23, 0x70(%sp)
	ld	%r24, 0x78(%sp)
	ld	%r25, 0x80(%sp)
	ld	%r26, 0x88(%sp)
	ld	%r31, 0x90(%sp)
	ld	%r30, 0x98(%sp)
	ld	%r0, 0xB0(%sp)
	mtlr	%r0
	addi	%sp, %sp, 0xA0
	blr




