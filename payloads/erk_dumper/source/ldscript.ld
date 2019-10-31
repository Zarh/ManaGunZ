OUTPUT_FORMAT("elf64-powerpc")
OUTPUT_ARCH(powerpc:common64)
ENTRY(_start)

__base = 0x80000000007F0000;

PHDRS {
	payload PT_LOAD FLAGS(0x1 | 0x2 | 0x4);
}

SECTIONS {
	. = __base;

	.start : {
		*(.start)
	} :payload = 0

	. = ALIGN(32);
	.text : {
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		*(.gnu.linkonce.t.*)
	}

	.data : {
		*(.data)
		*(.data.*)
	}

	.got : {
		*(.got)
		*(.got.*)
		__toc = .;
		*(.toc)
		*(.toc.*)
	}

	.opd : {
		*(.opd)
		*(.opd.*)
	}

	.bss : {
		*(.bss)
		*(.bss.*)
	}
}

.process_write_memory_inner = 0x8000000000073528;
.process_write_wrapper = 0x800000000007EB48;
.process_allocate_mapped_memory = 0x8000000000075294;
.address_space_allocate_ppc_segments = 0x800000000000E8A4;
.hid_manager_read_impl = 0x80000000000C2B08;
.set_pte = 0x800000000005CAE0;

/* FIXME: DELETE ME */

extend_kstack = 0x800000000006E7C0;
disable_interrupts = 0x8000000000025730;
get_current_proc_locked = 0x8000000000007E3C;
enable_external_interrupt = 0x800000000002573C;
access_control_engine_check_capability = 0x8000000000003560;
copy_from_user_copyin = 0x800000000000FA74;
copy_to_user_copyout = 0x800000000000F858;
alloc = 0x8000000000062F74;
dealloc = 0x80000000000633B0;
sub_8000000000011470 = 0x8000000000011470;
sub_80000000000114E8 = 0x80000000000114E8;
sub_8000000000003B38 = 0x8000000000003B38;
.sub_8000000000011470 = 0x8000000000011470;

