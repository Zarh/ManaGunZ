/*
	==============================================================

	MAMBA/PRX Loader payload by NzV

	==============================================================
*/

#define MAMBA_LOADER
//#define PRX_LOADER

#include <lv2/lv2.h>
#include <lv2/libc.h>
#include <lv2/memory.h>
#include <lv2/syscall.h>
#include <lv2/symbols.h>
#include <lv2/error.h>

#ifdef MAMBA_LOADER
//-----------------------
//MAMBA LOADER
//-----------------------

#include <lv2/io.h>
#include <lv2/patch.h>

#define SYSCALL1022_OPCODE_LOAD_MAMBA				0x7755

void *malloc(size_t size);
void free(void *ptr);

static size_t read_file(const char *path, void *buf, size_t size)
{
	int fd;
	if (cellFsOpen(path, CELL_FS_O_RDONLY, &fd, 0, NULL, 0) == CELL_FS_SUCCEEDED)
	{
		uint64_t offset;
		cellFsLseek(fd, 0, SEEK_SET, &offset);
		cellFsRead(fd, buf, size, &size);
		cellFsClose(fd);
		return size;
	}
	return 0;
}

int mamba_loaded = 0;

int sys_load_mamba(char *mamba_file)
{
	if (mamba_loaded == 1) return ECANCELED;
	mamba_file = get_secure_user_ptr(mamba_file);
	CellFsStat stat;
	int ret = cellFsStat(mamba_file, &stat);
	if (ret == SUCCEEDED)
	{
		uint32_t psize = stat.st_size;
		void *mamba = malloc(psize);
		if (mamba)
		{
			if (!read_file(mamba_file, mamba, psize))
			{
				free(mamba);
				mamba = NULL;
				return ret;
			}

			mamba_loaded = 1;
			f_desc_t f;
			f.toc = (void *)MKA(TOC);
			f.addr = mamba;

			int (* func)(void);
			func = (void *)&f;
			func();
			return SUCCEEDED;
		}
		return ENOMEM;
	}
	return ret;
}
#endif

#ifdef PRX_LOADER
//-----------------------
//PRX LOADER
//-----------------------

#include <lv2/thread.h>
#include <lv2/process.h>
#include <lv2/modules.h>

#define SYSCALL1022_OPCODE_LOAD_VSH_PLUGIN			0x1EE7 //Same as COBRA
#define SYSCALL1022_OPCODE_UNLOAD_VSH_PLUGIN		0x364F //Same as COBRA

#define MAX_VSH_PLUGINS		6

sys_prx_id_t vsh_plugins[MAX_VSH_PLUGINS];

process_t vsh_process;

process_t get_vsh_process(void)
{
	uint64_t *proc_list = *(uint64_t **)MKA(TOC + process_rtoc_entry_1);
	proc_list = *(uint64_t **)proc_list;
	proc_list = *(uint64_t **)proc_list;
	for (int i = 0; i < 16; i++)
	{
		process_t p = (process_t)proc_list[1];
		proc_list += 2;
		if ((((uint64_t)p) & 0xFFFFFFFF00000000ULL) != MKA(0)) continue;
		if (is_vsh_process(p)) return p;
	}
	return 0;
}

int sys_prx_load_vsh_plugin(unsigned int slot, char *path, void *arg, uint32_t arg_size)
{
	#ifdef MAMBA_LOADER
	if (mamba_loaded == 1) return ECANCELED; //USE MAMBA INSTEAD TO LOAD THEM !
	#endif
	if (!vsh_process) vsh_process = get_vsh_process();
	if (!vsh_process) return ESRCH;
	void *kbuf, *vbuf;
	sys_prx_id_t prx;
	int ret;
	path = get_secure_user_ptr(path);
	arg = get_secure_user_ptr(arg);
	if (slot >= MAX_VSH_PLUGINS || (arg != NULL && arg_size > KB(64))) return EINVAL;
	if (vsh_plugins[slot] != 0) return EKRESOURCE;
	prx = prx_load_module(vsh_process, 0, 0, path);
	if (prx < 0) return prx;
	if (arg && arg_size > 0)
	{
		page_allocate_auto(vsh_process, KB(64), &kbuf);
		page_export_to_proc(vsh_process, kbuf, 0x40000, &vbuf);
		copy_from_user(arg, kbuf, arg_size);
	}
	else vbuf = NULL;
	ret = prx_start_module_with_thread(prx, vsh_process, 0, (uint64_t)vbuf);
	if (vbuf)
	{
		page_unexport_from_proc(vsh_process, vbuf);
		free_page(vsh_process, kbuf);
	}
	if (ret == 0) vsh_plugins[slot] = prx;
	else
	{
		prx_stop_module_with_thread(prx, vsh_process, 0, 0);
		prx_unload_module(prx, vsh_process);
	}
	return ret;
}

int sys_prx_unload_vsh_plugin(unsigned int slot)
{
	#ifdef MAMBA_LOADER
	if (mamba_loaded == 1) return ECANCELED; //USE MAMBA INSTEAD TO LOAD THEM !
	#endif
	if (!vsh_process) vsh_process = get_vsh_process();
	if (!vsh_process) return ESRCH;
	int ret;
	sys_prx_id_t prx;
	if (slot >= MAX_VSH_PLUGINS) return EINVAL;
	prx = vsh_plugins[slot];
	if (prx == 0)return ENOENT;
	ret = prx_stop_module_with_thread(prx, vsh_process, 0, 0);
	if (ret == 0) ret = prx_unload_module(prx, vsh_process);
	if (ret == 0) vsh_plugins[slot] = 0;
	return ret;
}
#endif

//-----------------------
//MAIN
//-----------------------

#define SYSCALL1022_OPCODE_IS_ENABLED				0x7750

int syscall1022(uint64_t function, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5, uint64_t param6, uint64_t param7)
{
	extend_kstack(0);

	switch (function)
	{

		case SYSCALL1022_OPCODE_IS_ENABLED:
		#ifdef MAMBA_LOADER
			#ifdef PRX_LOADER
				return 0x333; //MAMBA + PRX LOADER
			#else
				return 0x222; //MAMBA LOADER ONLY
			#endif
		#elif defined PRX_LOADER
			return 0x111; //PRX LOADER ONLY
		#else
			return ENOSYS;
		#endif
		break;

		#ifdef MAMBA_LOADER
		case SYSCALL1022_OPCODE_LOAD_MAMBA:
			return sys_load_mamba((char *)param1);
		break;
		#endif

		#ifdef PRX_LOADER
		case SYSCALL1022_OPCODE_LOAD_VSH_PLUGIN:
			return sys_prx_load_vsh_plugin((unsigned int)param1, (char *)param2, (void *)param3, (uint32_t)param4);
		break;

		case SYSCALL1022_OPCODE_UNLOAD_VSH_PLUGIN:
			return sys_prx_unload_vsh_plugin((unsigned int)param1);
		break;
		#endif

	}

	return ENOSYS;
}
