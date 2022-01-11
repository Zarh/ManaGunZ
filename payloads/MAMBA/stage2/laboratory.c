#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lv2/lv2.h>
#include <lv2/libc.h>
#include <lv2/memory.h>
#include <lv2/patch.h>
#include <lv2/syscall.h>
#include <lv2/usb.h>
#include <lv2/storage.h>
#include <lv2/thread.h>
#include <lv2/synchronization.h>
#include <lv2/modules.h>
#include <lv2/io.h>
#include <lv2/time.h>
#include <lv2/security.h>
#include <lv2/pad.h>
#include <lv2/error.h>
#include <lv2/symbols.h>
#include <lv1/stor.h>
#include <lv1/patch.h>

#include "common.h"

LV2_PATCHED_FUNCTION(u64, syscall_handler, (u64 r3, u64 r4, u64 r5, u64 r6, u64 r7, u64 r8, u64 r9, u64 r10))
{
	register u64 r11 asm("r11");
	register u64 r13 asm("r13");
	u64 num, p;
	f_desc_t func;

	num = r11/8;
	p = r13;

	func.addr = (void *)p;
	func.toc = (void *)MKA(TOC);
	u64 (* syscall)() = (void *)&func;

	suspend_intr();

	if (1)
	{
		/*if (num == 378)
		{
			u64 *p1, *p2, *p3;

			p1 = (u64 *)r3;
			p2 = (u64 *)r4;
			p3 = (u64 *)r5;

			resume_intr();
			u64 ret = syscall(r3, r4, r5, r6);

			DPRINTF("ret=%lx r3 %016lx r4 %016lx r5 %016lx\n", ret, *p1, *p2, *p3);
			// r3 = 3 -> power off button pressed
			if (*p1 == 3)
			{
				// Change to reboot :)
				*p1 = 5; *p2 = 2;
			}
			return ret;
		}*/
		// Prepare your self for a big amount of data in your terminal!
		// And big ps3 slowdown
		// Uncomment the if to skip some too common syscalls and make things faster and smaller

		/*if (num != 378 && num != 173 && num != 178 && num != 130 && num != 138 && num != 104 && num != 102 && num != 579 && num != 122 && num != 124
			&& num != 113 && num != 141 && num != 125 && num != 127 && num != 141) */

		DPRINTF("syscall %ld %lx %lx %lx %lx %lx %lx %lx %lx\n", num, r3, r4, r5, r6, r7, r8, r9, r10);
	}

	resume_intr();

	return syscall(r3, r4, r5, r6, r7, r8, r9, r10);
}

void do_hook_all_syscalls(void)
{
	set_syscall_handler(syscall_handler);
}

static void dump_threads_info(void)
{
	u8 *thread_info = (u8 *)MKA(thread_info_symbol);
	int num_threads;

	num_threads = *(u32 *)&thread_info[8];

	for (int i = 0; i < num_threads; i++)
	{
		DPRINTF("Thread: %s   entry: %016lx    PC: %016lx\n", (char *)(thread_info+0x58), *(u64 *)(thread_info+0xB0), *(u64 *)(thread_info+0x208));
		thread_info += 0x600;
	}
}

static void dump_threads_info_test(u64 arg0)
{
	DPRINTF("Threads info will be dumped in 13 seconds.\n");
	timer_usleep(SECONDS(13));

	DPRINTF("----Dump threads info begin----\n");
	dump_threads_info();
	DPRINTF("----Dump threads info end----\n");

	ppu_thread_exit(0);
}

void do_dump_threads_info_test(void)
{
	thread_t my_thread;
	ppu_thread_create(&my_thread, dump_threads_info_test, 0, -0x1D8, 0x4000, 0, "Dump Threads");
}

static void dump_process(process_t process)
{
	char path[0x420];
	void *buf;
	u64 addr;
	int ret, fd;

	DPRINTF("Dumping process %s\n", get_process_name(process));
	sprintf(path, "/dev_usb000/%s.main_segment", get_process_name(process));

	buf = malloc(KB(64));
	if (!buf)
	{
		DPRINTF("Not enough memory.\n");
		return;
	}

	ret = cellFsOpen(path, CELL_FS_O_WRONLY | CELL_FS_O_CREAT | CELL_FS_O_TRUNC, &fd, 0666, NULL, 0);
	if (ret) // (ret != CELL_FS_SUCCEEDED)
	{
		DPRINTF("Cannot create %s\n", path);
		return;
	}

	for (addr = 0x10000; ; addr += KB(64))
	{
		u64 written;

		ret = copy_from_process(process, (void *)addr, buf, KB(64));
		if (ret) // (ret != 0)
		{
			DPRINTF("End of maing segment: %lx\n", addr);
			break;
		}

		cellFsWrite(fd, buf, KB(64), &written);
	}

	cellFsClose(fd);

	sprintf(path, "/dev_usb000/%s.heap_segment", get_process_name(process));

	ret = cellFsOpen(path, CELL_FS_O_WRONLY | CELL_FS_O_CREAT | CELL_FS_O_TRUNC, &fd, 0666, NULL, 0);
	if (ret) // (ret != CELL_FS_SUCCEEDED)
	{
		DPRINTF("Cannot create %s\n", path);
		return;
	}

	for (addr = 0x30000000; ; addr += KB(64))
	{
		u64 written;

		ret = copy_from_process(process, (void *)addr, buf, KB(64));
		if (ret) // (ret != 0)
		{
			DPRINTF("End of heap segment: %lx\n", addr);
			break;
		}

		cellFsWrite(fd, buf, KB(64), &written);
	}

	cellFsClose(fd);
	free(buf);
}

static void dump_processes(void)
{
	u64 *proc_list = *(u64 **)MKA(TOC + process_rtoc_entry_1);

	proc_list = *(u64 **)proc_list;
	proc_list = *(u64 **)proc_list;

	for (int i = 0; i < 0x10; i++)
	{
		process_t process = (process_t)proc_list[1];

		proc_list += 2;
		DPRINTF("%p\n", process);

		if ((((u64)process) & 0xFFFFFFFF00000000ULL) != MKA(0))
			continue;

		dump_process(process);
	}
}

static void dump_processes_test(u64 arg0)
{
	DPRINTF("Processes will be dumped in 74 seconds.\nGo, go, run what you want to dump!\n");
	timer_usleep(SECONDS(74));

	DPRINTF("----Dump processes begin----\n");
	dump_processes();
	DPRINTF("----Dump processes end----\n");

	ppu_thread_exit(0);
}

void do_dump_processes_test(void)
{
	thread_t my_thread;
	ppu_thread_create(&my_thread, dump_processes_test, 0, -0x1D8, 0x4000, 0, "Dump Proc Thread");
}

LV2_HOOKED_FUNCTION_POSTCALL_6(void, load_module_hook, (char *r3))
{
	DPRINTF("Load module: %s (%s)\n", r3, get_process_name(get_current_process())+8);
}

void do_hook_load_module(void)
{
	hook_function_with_postcall(get_syscall_address(_SYS_PRX_LOAD_MODULE_ON_MEMCONTAINER ), load_module_hook, 6);
}

LV2_HOOKED_FUNCTION_POSTCALL_2(void, mutex_create_hooked, (void *mutex, u64 blah))
{
	process_t process = get_current_process();
	//char *name = get_process_name(process)+8;
	if (1)
	{
		static char name[32];
		u64 r3 = (u64)mutex;

		if (r3 > 0xb90000 && r3 < 0x100000000ULL && prx_get_module_name_by_address(process, mutex, name) == 0)
		{
			/*DPRINTF("Addr: %lx\n", r3);
			DPRINTF("Module: %s\n", name);
			DPRINTF("Call address: %p\n", get_call_address(1));*/

			if (strcmp(name, "sceEmulatorApi") == 0)
			{
				DPRINTF("Addr: %lx\n", r3);
				DPRINTF("Module: %s\n", name);
				DPRINTF("Call address: %p\n", get_call_address(1));
			}
		}
	}

}

void do_hook_mutex_create(void)
{
	hook_function_with_postcall(get_syscall_address(SYS_MUTEX_CREATE), mutex_create_hooked, 2);
}

static void read_and_clear_ps2netemu_log(void)
{
	u8 *buf;

	if (page_allocate_auto(NULL, 0x10000, (void **)&buf) != 0)
	{
		DPRINTF("page_allocate failed\n");
		return;
	}

	memset(buf, 0, 0x10000);

	if (read_file("/dev_hdd0/log_file.bin", buf, 0x10000))
	{
		DPRINTF("%s\n", buf);

		memset(buf, 0, 0x10000);
		save_file("/dev_hdd0/log_file.bin", buf, 0x10000);
	}
	else
	{
		DPRINTF("Open log file failed\n");
	}


	free_page(NULL, buf);
}

static void ps2net_copy_test(u64 arg0)
{
	DPRINTF("+++ Sleeping for 16 seconds\n");
	timer_usleep(SECONDS(16));
	read_and_clear_ps2netemu_log();
	DPRINTF("Attempting to write ps2_netemu.self\n");

	if (cellFsUtilMount_h("CELL_FS_IOS:BUILTIN_FLSH1", "CELL_FS_FAT", "/dev_wflash", 0, 0, 0, NULL, 0) != CELL_FS_SUCCEEDED)
	{
		DPRINTF("Mount R/W failed\n");
		ppu_thread_exit(0);
	}

	int src, dst;
	u64 rw;

	if (cellFsOpen("/dev_usb000/ps2_netemu.self", CELL_FS_O_RDONLY, &src, 0, NULL, 0) != CELL_FS_SUCCEEDED)
	{
		DPRINTF("open Src read failed\n");
		goto umount_exit;
	}

	if (cellFsOpen("/dev_wflash/ps2emu/ps2_netemu.self", CELL_FS_O_WRONLY | CELL_FS_O_CREAT | CELL_FS_O_TRUNC, &dst, 0666, NULL, 0) != CELL_FS_SUCCEEDED)
	{
		DPRINTF("open dst write failed\n");
		cellFsClose(src);
		goto umount_exit;
	}

	u8 *buf;

	if (page_allocate_auto(NULL, 0x10000, (void **)&buf) != SUCCEEDED)
	{
		DPRINTF("page_allocate failed\n");
		cellFsClose(src);
		cellFsClose(dst);
		goto umount_exit;
	}

	memset(buf, 0, 0x10000);

	DPRINTF("Enter copy loop\n");
	u64 total = 0;

	while (1)
	{
		if (cellFsRead(src, buf, 0x10000, &rw) != CELL_FS_SUCCEEDED)
		{
			DPRINTF("cellFsRead failed\n");
			cellFsClose(src);
			cellFsClose(dst);
			free_page(NULL, buf);
			goto umount_exit;
		}

		if (cellFsWrite(dst, buf, rw, &rw) != CELL_FS_SUCCEEDED)
		{
			DPRINTF("cellFsWrite failed\n");
			cellFsClose(src);
			cellFsClose(dst);
			free_page(NULL, buf);
			goto umount_exit;
		}

		total += rw;

		if (rw < 0x10000)
			break;
	}

	cellFsClose(src);
	cellFsClose(dst);
	free_page(NULL, buf);

	DPRINTF("++++ copy finished (%ld) (%ld KB)\n", total, total / 1024);

umount_exit:

	if (cellFsUtilUmount("/dev_wflash", 0, 0) != CELL_FS_SUCCEEDED)
		cellFsUtilUmount("/dev_wflash", 0, 1);

	ppu_thread_exit(0);
}

void do_ps2net_copy_test(void)
{
	thread_t my_thread;
	ppu_thread_create(&my_thread, ps2net_copy_test, 0, -0x1D8, 0x4000, 0, "Ps2 net copy");
}

#define SPRX_NUM 128

static void dump_process_modules_info(process_t process)
{
	sys_prx_id_t *list;
	u32 *unk;
	u32 n, unk2;

	DPRINTF("******** %s ********\n", get_process_name(process));

	list = kalloc(SPRX_NUM*sizeof(sys_prx_module_info_t));
	unk  = kalloc(SPRX_NUM*sizeof(u32));

	if (prx_get_module_list(process, list, unk, SPRX_NUM, &n, &unk2) == 0)
	{
		char *filename = kalloc(256);
		sys_prx_segment_info_t *segments = kalloc(sizeof(sys_prx_segment_info_t));

		for (int i = 0; i < n; i++)
		{
			sys_prx_module_info_t modinfo;

			memset(&modinfo, 0, sizeof(sys_prx_module_info_t));
			modinfo.filename_size = 256;
			modinfo.segments_num = 1;

			if (prx_get_module_info(process, list[i], &modinfo, filename, segments) == 0)
				DPRINTF("Module %s\nText_addr:%08lX\n", filename, segments[0].base);
		}

		kfree(filename);
		kfree(segments);
	}

	DPRINTF("****************\n");

	kfree(list);
	kfree(unk);
}

static void dump_processes_modules_info(void)
{
	u64 *proc_list = *(u64 **)MKA(TOC+process_rtoc_entry_1);

	proc_list = *(u64 **)proc_list;
	proc_list = *(u64 **)proc_list;

	for (int i = 0; i < 0x10; i++)
	{
		process_t process = (process_t)proc_list[1];

		proc_list += 2;

		if ((((u64)process) & 0xFFFFFFFF00000000ULL) != MKA(0))
			continue;

		dump_process_modules_info(process);
	}
}

static void dump_modules_info_test(u64 arg0)
{
	DPRINTF("Modules info will be dumped in 71 seconds.\n");
	timer_usleep(SECONDS(71));

	dump_processes_modules_info();
	ppu_thread_exit(0);
}

void do_dump_modules_info_test(void)
{
	thread_t my_thread;
	ppu_thread_create(&my_thread, dump_modules_info_test, 0, -0x1D8, 0x4000, 0, "Dump Modules Info");
}


static void pad_test(u64 arg0)
{
	int error_shown = 0;
	pad_data data, odata;

	memset(&data, 0, sizeof(pad_data));
	memset(&odata, 0, sizeof(pad_data));
	odata.button[PAD_BTN_OFFSET_ANALOG_LEFT] = 0x8080;
	odata.button[PAD_BTN_OFFSET_ANALOG_RIGHT] = 0x8080;

	DPRINTF("PAD TEST: press R2+triangle to leave.\n");

	while (1)
	{
		int len = pad_get_data(&data);

		if (len < 0)
		{
			if (!error_shown)
			{
				DPRINTF("PAD err %x\n", len);
				error_shown = 1;
			}
		}
		else
			error_shown = 0;

		if (len >= ((PAD_BTN_OFFSET_DIGITAL+1)*2))
		{
			uint16_t digital = data.button[PAD_BTN_OFFSET_DIGITAL] & ~odata.button[PAD_BTN_OFFSET_DIGITAL];

			odata.button[PAD_BTN_OFFSET_DIGITAL] = data.button[PAD_BTN_OFFSET_DIGITAL];

			if (digital & PAD_CTRL_LEFT)
				DPRINTF("LEFT pressed\n");

			if (digital & PAD_CTRL_RIGHT)
				DPRINTF("RIGHT pressed\n");

			if (digital & PAD_CTRL_UP)
				DPRINTF("UP pressed\n");

			if (digital & PAD_CTRL_DOWN)
				DPRINTF("DOWN pressed\n");

			if (digital & PAD_CTRL_START)
				DPRINTF("START pressed\n");

			if (digital & PAD_CTRL_SELECT)
				DPRINTF("SELECT pressed\n");

			if (digital & PAD_CTRL_SQUARE)
				DPRINTF("SQUARE pressed\n");

			if (digital & PAD_CTRL_TRIANGLE)
				DPRINTF("TRIANGLE pressed\n");

			if (digital & PAD_CTRL_CROSS)
				DPRINTF("CROSS pressed\n");

			if (digital & PAD_CTRL_CIRCLE)
				DPRINTF("CIRCLE pressed\n");

			if (digital & PAD_CTRL_L1)
				DPRINTF("L1 pressed\n");

			if (digital & PAD_CTRL_R1)
				DPRINTF("R1 pressed\n");

			if (digital & PAD_CTRL_L2)
				DPRINTF("L2 pressed\n");

			if (digital & PAD_CTRL_R2)
				DPRINTF("R2 pressed\n");

			if (digital & PAD_CTRL_L3)
				DPRINTF("L3 pressed\n");

			if (digital & PAD_CTRL_R3)
				DPRINTF("R3 pressed\n");

			if ((data.button[PAD_BTN_OFFSET_DIGITAL] & (PAD_CTRL_R2|PAD_CTRL_TRIANGLE)) == (PAD_CTRL_R2|PAD_CTRL_TRIANGLE))
				break;
		}

		if (len >= ((PAD_BTN_OFFSET_PS+1)*2))
		{
			uint16_t ps = data.button[PAD_BTN_OFFSET_PS] & ~odata.button[PAD_BTN_OFFSET_PS];

			odata.button[PAD_BTN_OFFSET_PS] = data.button[PAD_BTN_OFFSET_PS];

			if (ps & PAD_CTRL_PS)
				DPRINTF("PS pressed\n");
		}

		if (len >= ((PAD_BTN_OFFSET_ANALOG_LEFT+1)*2))
		{
			uint16_t current = data.button[PAD_BTN_OFFSET_ANALOG_LEFT];
			uint16_t old = odata.button[PAD_BTN_OFFSET_ANALOG_LEFT];

			odata.button[PAD_BTN_OFFSET_ANALOG_LEFT] = current;

			if (PAD_CTRL_ANALOG_X(current) < 0x40 && PAD_CTRL_ANALOG_X(old) >= 0x40)
				DPRINTF("ANALOG L LEFT pressed\n");

			if (PAD_CTRL_ANALOG_X(current) > 0xC0 && PAD_CTRL_ANALOG_X(old) <= 0xC0)
				DPRINTF("ANALOG L RIGHT pressed\n");

			if (PAD_CTRL_ANALOG_Y(current) < 0x40 && PAD_CTRL_ANALOG_Y(old) >= 0x40)
				DPRINTF("ANALOG L UP pressed\n");

			if (PAD_CTRL_ANALOG_Y(current) > 0xC0 && PAD_CTRL_ANALOG_Y(old) <= 0xC0)
				DPRINTF("ANALOG L DOWN pressed\n");
		}

		if (len >= ((PAD_BTN_OFFSET_ANALOG_RIGHT+1)*2))
		{
			uint16_t current = data.button[PAD_BTN_OFFSET_ANALOG_RIGHT];
			uint16_t old = odata.button[PAD_BTN_OFFSET_ANALOG_RIGHT];

			odata.button[PAD_BTN_OFFSET_ANALOG_RIGHT] = current;

			if (PAD_CTRL_ANALOG_X(current) < 0x40 && PAD_CTRL_ANALOG_X(old) >= 0x40)
				DPRINTF("ANALOG R LEFT pressed\n");

			if (PAD_CTRL_ANALOG_X(current) > 0xC0 && PAD_CTRL_ANALOG_X(old) <= 0xC0)
				DPRINTF("ANALOG R RIGHT pressed\n");

			if (PAD_CTRL_ANALOG_Y(current) < 0x40 && PAD_CTRL_ANALOG_Y(old) >= 0x40)
				DPRINTF("ANALOG R UP pressed\n");

			if (PAD_CTRL_ANALOG_Y(current) > 0xC0 && PAD_CTRL_ANALOG_Y(old) <= 0xC0)
				DPRINTF("ANALOG R DOWN pressed\n");
		}

		timer_usleep(50000);
	}

	DPRINTF("PAD test end\n");

	ppu_thread_exit(0);
}

void do_pad_test(void)
{
	thread_t my_thread;
	ppu_thread_create(&my_thread, pad_test, 0, -0x1D8, 0x4000, 0, "Pad Test");
}

