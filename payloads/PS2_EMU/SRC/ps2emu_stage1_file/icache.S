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
