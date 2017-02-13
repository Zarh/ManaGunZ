OUTPUT_FORMAT("elf64-powerpc")
OUTPUT_ARCH(powerpc:common64)

__base = 0x80000000007F0000;

ENTRY(_start)

SECTIONS
{
	.text __base :
	{
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		*(.gnu.linkonce.t.*)
	}


	.data :
	{
		*(.data)
		*(.data.*)

	} : data = 0
	
	
	.opd :
	{
		*(.opd)
		*(.opd.*)
	}

	.got :
	{
		__toc_start = .;
		*(.got)
		*(.got.*)
		*(.toc)
		*(.toc.*)
		__toc_end = .;
	}

	.bss :
	{
		*(.bss)
		*(.bss.*)
	}
} 