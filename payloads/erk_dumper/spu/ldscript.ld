ENTRY(_start)

SECTIONS {
	. = 0x12C00;

	.text : {
		*(.text)
	}

	.data : {
		*(.data)
		*(.rodata)
	}

	.bss : {
		bss = .;
		*(.bss)
	}
}
