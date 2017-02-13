	.text
	.section .text,"ax",@progbits
	.align 3

	.global _start
_start:
	// push to the stack
	stdu	%sp, -0x0090(%sp)
	std		%r31, 0x0088(%sp)
	std		%r2, 0x0070(%sp)
	mflr	%r0
	std		%r0, 0x00A0(%sp)

	// setup proper rtoc
	li		%r2, 1
	rldicr	%r2, %r2, 63, 0
	oris	%r2, %r2, (__toc_start + 0x8000)@h
	ori		%r2, %r2, (__toc_start + 0x8000)@l

	// branch to main func
	bl		syscall1022

	// pop the stack
	ld		%r31, 0x0088(%sp)
	ld		%r2, 0x0070(%sp)
	ld		%r0, 0x00A0(%sp)
	mtlr	%r0
	addi	%sp, %sp, 0x90
	blr

	.global .panic

