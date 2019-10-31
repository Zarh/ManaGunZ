.text
.section .start, "ax", @progbits
.align 3

.global _start
_start:
	mflr %r0
	std %r0, 0x10(%r1)
	stdu %r1, -0x90(%r1)

	std %r11, 0x88(%r1)
	std %r10, 0x80(%r1)
	std %r9, 0x78(%r1)
	std %r8, 0x70(%r1)
	std %r7, 0x68(%r1)
	std %r6, 0x60(%r1)
	std %r5, 0x58(%r1)
	std %r4, 0x50(%r1)
	std %r3, 0x48(%r1)
	std %r2, 0x40(%r1)

	li %r2, 1
	sldi %r2, %r2, 63
	oris %r2, %r2, (__toc + 0x8000)@h
	ori %r2, %r2, (__toc + 0x8000)@l

	bl payload_main
	
	std %r3, 0x48(%r1)

	ld %r2, 0x40(%r1)
	ld %r3, 0x48(%r1)
	ld %r4, 0x50(%r1)
	ld %r5, 0x58(%r1)
	ld %r6, 0x60(%r1)
	ld %r7, 0x68(%r1)
	ld %r8, 0x70(%r1)
	ld %r9, 0x78(%r1)
	ld %r10, 0x80(%r1)
	ld %r11, 0x88(%r1)

	addi %r1, %r1, 0x90
	ld %r0, 0x10(%r1)
	mtlr %r0
	blr
