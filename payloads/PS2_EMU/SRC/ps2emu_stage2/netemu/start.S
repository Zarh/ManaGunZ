.text
	.section .start,"ax",@progbits
	.align 3

	.global _start

_start:

// Fill this with jumps to the patched functions
//	b	ufs_open_patched
//	b	ufs_read_patched
//	b	ufs_fstat_patched
	b	open_iso
	b	fstat_iso_patched
	b	read_iso_size
	b	cdvd_read_patched


	


	

	
	
