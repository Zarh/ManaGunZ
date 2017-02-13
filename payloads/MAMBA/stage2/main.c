/*
 'Mamba' is the payload version of Cobra code CFW (developed by Cobra Team) for Iris Manager
 and updated by NzV to work without Iris (sky) payload (also autoboot features)

 PS2 and PSP ISO support added by Ps3ita Team

 LICENSED under GPL v3.0

*/

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
#include <lv2/error.h>
#include <lv2/symbols.h>
#include <lv1/stor.h>
#include <lv1/patch.h>
#include "common.h"
#include "modulespatch.h"
#include "mappath.h"
#include "storage_ext.h"
#include "psp.h"
#include "config.h"
#include "syscall8.h"
#include "region.h"

#ifdef PS3M_API
#include "ps3mapi_core.h"
#endif

//----------------------------------------
//VERSION
//----------------------------------------

#define IS_CFW			1

#define MAMBA_VERSION		0x0F
#define MAMBA_VERSION_BCD	0x0730

// Format of version:
// byte 0, 7 MS bits -> reserved
// byte 0, 1 LS bit -> 1 = CFW version, 0 = OFW/exploit version
// byte 1 and 2 -> ps3 fw version in BCD e.g 3.55 = 03 55. For legacy reasons, 00 00 means 3.41
// byte 3 is cobra firmware version,
// 1 = version 1.0-1.2,
// 2 = 2.0,
// 3 = 3.0
// 4 = 3.1
// 5 = 3.2
// 6 = 3.3
// 7 = 4.0
// 8 = 4.1
// 9 = 4.2
// A = 4.3
// B = 4.4
// C = 5.0
// D = 5.1
// E = 6.0
// F = 7.0

#define MAKE_VERSION(mamba, fw, type) ((mamba&0xFF) | ((fw&0xffff)<<8) | ((type&0x1)<<24))

static INLINE int sys_get_version(uint32_t *version)
{
	uint32_t pv = MAKE_VERSION(MAMBA_VERSION, FIRMWARE_VERSION, IS_CFW);
	return copy_to_user(&pv, get_secure_user_ptr(version), sizeof(uint32_t));
}

static INLINE int sys_get_version2(uint16_t *version)
{
	uint16_t cb = MAMBA_VERSION_BCD;
	return copy_to_user(&cb, get_secure_user_ptr(version), sizeof(uint16_t));
}

//----------------------------------------
//LV1 SYSCALL PEEK/POKE/CALL
//----------------------------------------

LV2_SYSCALL2(uint64_t, sys_cfw_lv1_peek, (uint64_t lv1_addr))
{
	#ifdef DEBUG
	DPRINTF("peek %016lx\n", lv1_addr);
	#endif

    uint64_t ret;
    ret = lv1_peekd(lv1_addr);
    return ret;

}

LV2_SYSCALL2(void, sys_cfw_lv1_poke, (uint64_t lv1_addr, uint64_t lv1_value))
{
	#ifdef DEBUG
	DPRINTF("poke %016lx %016lx\n", lv1_addr, lv1_value);
	#endif

	lv1_poked(lv1_addr, lv1_value);
}

LV2_SYSCALL2(void, sys_cfw_lv1_call, (uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6, uint64_t a7, uint64_t num))
{
	/* DO NOT modify */
	asm("mflr 0\n");
	asm("std 0, 16(1)\n");
	asm("mr 11, 10\n");
	asm("sc 1\n");
	asm("ld 0, 16(1)\n");
	asm("mtlr 0\n");
	asm("blr\n");
}

//----------------------------------------
//LV2 SYSCALL PEEK/POKE
//----------------------------------------

LV2_SYSCALL2(uint64_t, sys_cfw_peek, (uint64_t *addr))
{
	#ifdef DEBUG
	DPRINTF("peek %p\n", addr);
	#endif

	uint64_t ret = *addr;

	// Fix compatibilty issue with prx loader (before v1.08 [U]). It searches for a string... that is also in this payload, and then lv2_peek((vsh_str + 0x70)) crashes the system.
	if (ret == 0x5F6D61696E5F7673)
	{
		extern uint64_t _start;
		extern uint64_t __self_end;

		if ((uint64_t)addr >= (uint64_t)&_start && (uint64_t)addr < (uint64_t)&__self_end)
		{
			#ifdef DEBUG
			DPRINTF("peek to addr %p blocked for compatibility.\n", addr);
			#endif
			return 0;
		}
	}

	return ret;
}

void _sys_cfw_poke(uint64_t *addr, uint64_t value);

LV2_HOOKED_FUNCTION(void, sys_cfw_new_poke, (uint64_t *addr, uint64_t value))
{
	#ifdef DEBUG
	DPRINTF("New poke called\n");
	#endif

	_sys_cfw_poke(addr, value);
	asm volatile("icbi 0,%0; isync" :: "r"(addr));
}

LV2_HOOKED_FUNCTION(void *, sys_cfw_memcpy, (void *dst, void *src, uint64_t len))
{
	#ifdef DEBUG
	DPRINTF("sys_cfw_memcpy: %p %p 0x%lx\n", dst, src, len);
	#endif

	if (len == 8)
	{
		_sys_cfw_poke(dst, *(uint64_t *)src);
		return dst;
	}

	return memcpy(dst, src, len);
}

static uint8_t isLoadedFromIrisManager = 0;

int64_t syscall8(uint64_t function, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5, uint64_t param6, uint64_t param7);
f_desc_t extended_syscall8;
static void *current_813;

LV2_SYSCALL2(void, sys_cfw_poke, (uint64_t *ptr, uint64_t value))
{
	uint64_t addr = (uint64_t)ptr;

	#ifdef DEBUG
	DPRINTF("poke %016lx %016lx\n", addr, value);
	#endif

	if (addr >= MKA(syscall_table_symbol))
	{
		uint64_t syscall_num = (addr-MKA(syscall_table_symbol)) / 8;

		if ((syscall_num >= 6 && syscall_num <= 10) || syscall_num == 35)//Rewrite protection
		{
			uint64_t sc_null = *(uint64_t *)MKA(syscall_table_symbol);
			uint64_t syscall_not_impl = *(uint64_t *)sc_null;
			if (syscall_num == 8 && (value & 0xFFFFFFFF00000000ULL) == MKA(0))
			{
				// Probably iris manager or similar
				// Lets extend our syscall 8 so that it can call this other syscall 8
				// First check if it is trying to restore our syscall8
				if (*(uint64_t *)syscall8 == value)
				{
					#ifdef DEBUG
					DPRINTF("Removing syscall 8 extension\n");
					#endif
					if (isLoadedFromIrisManager == 0)
						extended_syscall8.addr = 0;
					return;
				}

				extended_syscall8.addr = (void *) *(uint64_t *)value;
				if (isLoadedFromIrisManager == 0)
					extended_syscall8.toc = (void *) *(uint64_t *)(value+8);
				else
					extended_syscall8.toc = (void *) *(uint64_t *)(MKA(0x3000));

				#ifdef DEBUG
				DPRINTF("Adding syscall 8 extension %p %p\n", extended_syscall8.addr, extended_syscall8.toc);
				#endif

				return;
			}
			else if (((value == sc_null) ||(value == syscall_not_impl)) && (syscall_num != 8)) //Allow remove protected syscall 6 7 9 10 11 35 NOT 8
			{
				#ifdef DEBUG
				DPRINTF("HB remove syscall %ld\n", syscall_num);
				#endif
			}
			else
			{
				#ifdef DEBUG
				DPRINTF("HB has been blocked from rewriting syscall %ld\n", syscall_num);
				#endif
				return;
			}
		}
	}

	else if (addr == MKA(open_path_symbol))
	{

		#ifdef DEBUG
		DPRINTF("open_path poke: %016lx\n", value);
		#endif

		if (value == 0xf821ff617c0802a6ULL)
		{
			#ifdef DEBUG
			DPRINTF("Restoring map_path patches\n");
			#endif
			*ptr = value;
			clear_icache(ptr, 8);
			map_path_patches(0);
			return;
		}
	}
	else
	{
		uint64_t sc813 = get_syscall_address(813);

		if (addr == sc813)
		{
			if (value == 0xF88300007C001FACULL)
			{
				// Assume app is trying to write the so called "new poke"
				f_desc_t f;

				#ifdef DEBUG
				DPRINTF("Making sys_cfw_new_poke\n");
				#endif

				if (current_813)
				{
					unhook_function(sc813, current_813);
				}

				hook_function(sc813, sys_cfw_new_poke, &f);
				current_813 = sys_cfw_new_poke;
				return;
			}
			else if (value == 0x4800000428250000ULL)
			{
				// Assume app is trying to write a memcpy
				f_desc_t f;

				#ifdef DEBUG
				DPRINTF("Making sys_cfw_memcpy\n");
				#endif
				if (current_813)
				{
					unhook_function(sc813, current_813);
				}

				hook_function(sc813, sys_cfw_memcpy, &f);
				current_813 = sys_cfw_memcpy;
				return;
			}
			else if (value == 0xF821FF017C0802A6ULL)
			{
				// Assume app is trying to restore sc 813
				if (current_813)
				{
					#ifdef DEBUG
					DPRINTF("Restoring syscall 813\n");
					#endif

					unhook_function(sc813, current_813);
					current_813 = NULL;
					return;
				}
			}
			else
			{
				#ifdef DEBUG
				DPRINTF("Warning: syscall 813 being overwritten with unknown value (%016lx). *blocking it*\n", value);
				#endif
				return;
			}
		}
		else if (addr > sc813 && addr < (sc813+0x20))
		{
			return;
		}
    }

    *ptr = value;
}

//----------------------------------------
//UNHOOK (PS3M_API)
//----------------------------------------

#ifdef PS3M_API
static inline void ps3mapi_unhook_all(void)
{
	unhook_all_modules();
	unhook_all_region();
	unhook_all_map_path();
    unhook_all_storage_ext();
}
#endif

//----------------------------------------
//SYSCALL 8 MAMBA
//----------------------------------------

#ifdef PS3M_API

static uint64_t ps3mapi_key = 0;
static uint8_t ps3mapi_access_tries = 0;
static uint8_t ps3mapi_access_granted = 1;

static int ps3mapi_partial_disable_syscall8 = 0;
static uint8_t disable_cobra = 0;

uint64_t LV2_OFFSET_ON_LV1 = 0; // 0x1000000 on 4.46, 0x8000000 on 4.76

#endif

LV2_SYSCALL2(int64_t, syscall8, (uint64_t function, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5, uint64_t param6, uint64_t param7))
{
	static uint32_t pid_blocked = 0;
	uint32_t pid;

	extend_kstack(0);

	#ifdef PS3ITA
	DPRINTF("Syscall 8 -> %lx\n", function);
	#endif

	// -- AV: temporary disable cobra syscall (allow dumpers peek 0x1000 to 0x9800)
	static uint8_t tmp_lv1peek = 0;

	if(ps3mapi_partial_disable_syscall8 == 0 && extended_syscall8.addr == 0 && ps3mapi_access_granted)
	{
		if((function >= 0x9800) || (function & 3)) tmp_lv1peek=0; else
		if(function <= 0x1000) {tmp_lv1peek=1; if(function <= SYSCALL8_OPCODE_ENABLE_COBRA) {if(param1>=SYSCALL8_DISABLE_COBRA_CAPABILITY) return (param1==SYSCALL8_DISABLE_COBRA_CAPABILITY) ? SYSCALL8_DISABLE_COBRA_OK : disable_cobra; else disable_cobra = (function==SYSCALL8_OPCODE_DISABLE_COBRA && param1==1);}}

		if(tmp_lv1peek) {return lv1_peekd(function);}
	}
	else tmp_lv1peek=0;
	// --

	// Some processsing to avoid crashes with lv1 dumpers

	pid = get_current_process_critical()->pid;

	if (pid == pid_blocked)
	{
		if (function <= 0x1000 ||function >= 0x9800 || (function & 3)) // Keep all cobra opcodes below 0x9800 //
		{
			#ifdef ENABLE_LOG
			WriteToLog("App was unblocked from using syscall8\n");
			#endif

			#ifdef DEBUG
			DPRINTF("App was unblocked from using syscall8\n");
			#endif
			pid_blocked = 0;
		}
		else
		{
			#ifdef ENABLE_LOG
			sprintf(buffer_log, "App was blocked from using syscall8\n");
			WriteToLog(buffer_log);
			#endif

			#ifdef DEBUG
			DPRINTF("App was blocked from using syscall8\n");
			#endif
			return ENOSYS;
		}
	}

	if (function == (SYSCALL8_OPCODE_GET_VERSION-8))
	{
		// 0x6FF8. On 0x7000 it *could* crash
		pid_blocked = pid;
		return ENOSYS;
	}

	#ifdef DO_PATCH_PSP
	else if (function == (SYSCALL8_OPCODE_PSP_POST_SAVEDATA_INITSTART-8))
	{
		// 0x3000, On 0x3008 it *could* crash
		pid_blocked = pid;
		return ENOSYS;
	}
	#endif

	#ifdef PS3M_API
	if (3 <= ps3mapi_partial_disable_syscall8)
	{
		if (function == SYSCALL8_OPCODE_PS3MAPI)
		{
			if ((int)param1 == PS3MAPI_OPCODE_PDISABLE_SYSCALL8)
			{
				ps3mapi_partial_disable_syscall8 = (int)param2;
				return SUCCEEDED;
			}
			else if ((int)param1 == PS3MAPI_OPCODE_PCHECK_SYSCALL8)
			{
				return ps3mapi_partial_disable_syscall8;
			}
			return ENOSYS;
		}
		return ENOSYS;
	}

	if ((function != SYSCALL8_OPCODE_PS3MAPI) && (2 <= ps3mapi_partial_disable_syscall8))	return ENOSYS;

	if ((function == SYSCALL8_OPCODE_PS3MAPI) && ((int)param1 == PS3MAPI_OPCODE_REQUEST_ACCESS) && (param2 == ps3mapi_key) && (ps3mapi_access_tries < 3)) {ps3mapi_access_tries = 0; ps3mapi_access_granted = 1;}

	if((!ps3mapi_access_granted) && (ps3mapi_key != 0))
	{
		ps3mapi_access_tries += 1;
		if(ps3mapi_access_tries > 3) ps3mapi_access_tries = 99;
		return ENOSYS;
	}
	#endif

	// -- AV: disable cobra without reboot (use lv1 peek)
	if(disable_cobra) return lv1_peekd(function);

	switch (function)
	{
		#ifdef PS3M_API
		case SYSCALL8_OPCODE_PS3MAPI:
			switch ((int)param1)
			{
				//----------
				//CORE
				//----------
				case PS3MAPI_OPCODE_GET_CORE_VERSION:
					return PS3MAPI_CORE_VERSION;
				break;
				case PS3MAPI_OPCODE_GET_CORE_MINVERSION:
					return PS3MAPI_CORE_MINVERSION;
				break;
				case PS3MAPI_OPCODE_GET_FW_VERSION:
					return PS3MAPI_FW_VERSION;
				break;
				case PS3MAPI_OPCODE_GET_FW_TYPE:
					return ps3mapi_get_fw_type((char *)param2);
				break;

				//----------------
				//PEEK & POKE (av)
				//----------------
				case PS3MAPI_OPCODE_SUPPORT_SC8_PEEK_POKE:
					return PS3MAPI_OPCODE_SUPPORT_SC8_PEEK_POKE_OK;
				break;
				case PS3MAPI_OPCODE_LV1_PEEK:
					return lv1_peekd(param2);
				break;
				case PS3MAPI_OPCODE_LV1_POKE:
					lv1_poked(param2, param3);
					return 0;
				break;
				case PS3MAPI_OPCODE_LV2_PEEK:
					return lv1_peekd(param2+LV2_OFFSET_ON_LV1);
				break;
				case PS3MAPI_OPCODE_LV2_POKE:
					lv1_poked(param2+LV2_OFFSET_ON_LV1, param3);
					return 0;
				break;

				//----------
				//SECURITY
				//----------
				case PS3MAPI_OPCODE_SET_ACCESS_KEY:
					ps3mapi_key = param2;
					ps3mapi_access_granted = 0;
					ps3mapi_access_tries = 0;
					return 0;

				//----------
				//PROCESS
				//----------
				case PS3MAPI_OPCODE_GET_ALL_PROC_PID:
					return ps3mapi_get_all_processes_pid((process_id_t *)param2);
				break;
				case PS3MAPI_OPCODE_GET_PROC_NAME_BY_PID:
					return ps3mapi_get_process_name_by_pid((process_id_t)param2, (char *)param3);
				break;
				case PS3MAPI_OPCODE_GET_PROC_BY_PID:
					return ps3mapi_get_process_by_pid((process_id_t)param2, (process_t)param3);
				break;
				case PS3MAPI_OPCODE_GET_CURRENT_PROC:
					return ps3mapi_get_current_process((process_t)param2);
				break;
				case PS3MAPI_OPCODE_GET_CURRENT_PROC_CRIT:
					return ps3mapi_get_current_process_critical((process_t)param2);
				break;
				//----------
				//MEMORY
				//----------
				case PS3MAPI_OPCODE_GET_PROC_MEM:
					return ps3mapi_get_process_mem((process_id_t)param2, param3, (char *)param4, (int)param5);
				break;
				case PS3MAPI_OPCODE_SET_PROC_MEM:
					return ps3mapi_set_process_mem((process_id_t)param2, param3, (char *)param4, (int)param5);
				break;
				//----------
				//MODULE
				//----------
				case PS3MAPI_OPCODE_GET_ALL_PROC_MODULE_PID:
					return ps3mapi_get_all_process_modules_prx_id((process_id_t)param2, (sys_prx_id_t *)param3);
				break;
				case PS3MAPI_OPCODE_GET_PROC_MODULE_NAME:
					return ps3mapi_get_process_module_name_by_prx_id((process_id_t)param2, (sys_prx_id_t)param3, (char *)param4);
				break;
				case PS3MAPI_OPCODE_GET_PROC_MODULE_FILENAME:
					return ps3mapi_get_process_module_filename_by_prx_id((process_id_t)param2, (sys_prx_id_t)param3, (char *)param4);
				break;
				case PS3MAPI_OPCODE_LOAD_PROC_MODULE:
					return ps3mapi_load_process_modules((process_id_t)param2, (char *)param3, (void *)param4, (uint32_t)param5);
				break;
				case PS3MAPI_OPCODE_UNLOAD_PROC_MODULE:
					return ps3mapi_unload_process_modules((process_id_t)param2, (sys_prx_id_t)param3);
				break;
				//----------
				//VSH PLUGINS
				//----------
				case PS3MAPI_OPCODE_UNLOAD_VSH_PLUGIN:
					return ps3mapi_unload_vsh_plugin((char *)param2);
				break;
				case PS3MAPI_OPCODE_GET_VSH_PLUGIN_INFO:
					return ps3mapi_get_vsh_plugin_info((unsigned int)param2, (char *)param3, (char *)param4);
				break;
				//----------
				//SYSCALL
				//----------
				case PS3MAPI_OPCODE_DISABLE_SYSCALL:
					return ps3mapi_disable_syscall((int)param2);
				break;
				case PS3MAPI_OPCODE_CHECK_SYSCALL:
					return ps3mapi_check_syscall((int)param2);
				break;
				case PS3MAPI_OPCODE_PDISABLE_SYSCALL8:
					ps3mapi_partial_disable_syscall8 = (int)param2;
					return SUCCEEDED;
				break;
				case PS3MAPI_OPCODE_PCHECK_SYSCALL8:
					return ps3mapi_partial_disable_syscall8;
				break;
				//----------
				//REMOVE HOOK
				//----------
				case PS3MAPI_OPCODE_REMOVE_HOOK:
					ps3mapi_unhook_all();
					return SUCCEEDED;
				break;
				//-----------------------------------------------
				//PSID/IDPS
				//-----------------------------------------------
				case PS3MAPI_OPCODE_GET_IDPS:
					return ps3mapi_get_idps((uint64_t *)param2);
				break;
				case PS3MAPI_OPCODE_SET_IDPS:
					return ps3mapi_set_idps(param2, param3);
				break;
				case PS3MAPI_OPCODE_GET_PSID:
					return ps3mapi_get_psid((uint64_t *)param2);
				break;
				case PS3MAPI_OPCODE_SET_PSID:
					return ps3mapi_set_psid(param2, param3);
				break;
				//----------
				//DEFAULT
				//----------
				default:
					return ENOSYS;
				break;
			}
		break;

		#endif

		#ifdef KW_STEALTH_EXT
		case SYSCALL8_OPCODE_STEALTH_TEST:  //KW PSNPatch stealth extension compatibility
			return SYSCALL8_STEALTH_OK;
		break;

		case SYSCALL8_OPCODE_STEALTH_ACTIVATE: //KW PSNPatch stealth extension compatibility
		{
				uint64_t syscall_not_impl = *(uint64_t *)MKA(syscall_table_symbol);
				#ifdef PS3M_API
				ps3mapi_partial_disable_syscall8 = 2; //Keep PS3M_API Features only.
				#else
				*(uint64_t *)MKA(syscall_table_symbol+ 8* 8) = syscall_not_impl;
				#endif
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 9) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 10) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 11) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 35) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 36) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 38) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 6) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 7) = syscall_not_impl;
			return SYSCALL8_STEALTH_OK;
		}
		break;
		#endif

		case SYSCALL8_OPCODE_GET_MAMBA:
			return 0x666;
		break;

		case SYSCALL8_OPCODE_GET_VERSION:
			return sys_get_version((uint32_t *)param1);
		break;

		case SYSCALL8_OPCODE_GET_VERSION2:
			return sys_get_version2((uint16_t *)param1);
		break;

		case SYSCALL8_OPCODE_GET_DISC_TYPE:
			return sys_storage_ext_get_disc_type((unsigned int *)param1, (unsigned int *)param2, (unsigned int *)param3);
		break;

		case SYSCALL8_OPCODE_READ_PS3_DISC:
			return sys_storage_ext_read_ps3_disc((void *)param1, param2, (uint32_t)param3);
		break;

		case SYSCALL8_OPCODE_FAKE_STORAGE_EVENT:
			return sys_storage_ext_fake_storage_event(param1, param2, param3);
		break;

		case SYSCALL8_OPCODE_GET_EMU_STATE:
			return sys_storage_ext_get_emu_state((sys_emu_state_t *)param1);
		break;

		case SYSCALL8_OPCODE_MOUNT_PS3_DISCFILE:
			return sys_storage_ext_mount_ps3_discfile(param1, (char **)param2);
		break;

		case SYSCALL8_OPCODE_MOUNT_DVD_DISCFILE:
			return sys_storage_ext_mount_dvd_discfile(param1, (char **)param2);
		break;

		case SYSCALL8_OPCODE_MOUNT_BD_DISCFILE:
			return sys_storage_ext_mount_bd_discfile(param1, (char **)param2);
		break;

		case SYSCALL8_OPCODE_MOUNT_PSX_DISCFILE:
			return sys_storage_ext_mount_psx_discfile((char *)param1, param2, (ScsiTrackDescriptor *)param3);
		break;
		#ifdef DO_PATCH_PS2
		case SYSCALL8_OPCODE_MOUNT_PS2_DISCFILE:
			return sys_storage_ext_mount_ps2_discfile(param1, (char **)param2, param3, (ScsiTrackDescriptor *)param4);
		break;
		#endif
		case SYSCALL8_OPCODE_MOUNT_DISCFILE_PROXY:
			return sys_storage_ext_mount_discfile_proxy(param1, param2, param3, param4, param5, param6, (ScsiTrackDescriptor *)param7);
		break;

		case SYSCALL8_OPCODE_UMOUNT_DISCFILE:
			return sys_storage_ext_umount_discfile();
		break;

		case SYSCALL8_OPCODE_MOUNT_ENCRYPTED_IMAGE:
			return sys_storage_ext_mount_encrypted_image((char *)param1, (char *)param2, (char *)param3, param4);

		case SYSCALL8_OPCODE_READ_COBRA_CONFIG:
			return sys_read_mamba_config((MambaConfig *)param1);
		break;

		case SYSCALL8_OPCODE_WRITE_COBRA_CONFIG:
			return sys_write_mamba_config((MambaConfig *)param1);
		break;

		case SYSCALL8_OPCODE_MAP_PATHS:
			return sys_map_paths((char **)param1, (char **)param2, param3);
		break;

		case SYSCALL8_OPCODE_AIO_COPY_ROOT:
			return sys_aio_copy_root((char *)param1, (char *)param2);
		break;

		case SYSCALL8_OPCODE_GET_ACCESS:
		case SYSCALL8_OPCODE_REMOVE_ACCESS:
			return 0;//needed for mmCM
		break;
		#ifdef DO_PATCH_PSP
		case SYSCALL8_OPCODE_SET_PSP_UMDFILE:
			return sys_psp_set_umdfile((char *)param1, (char *)param2, param3);
		break;

		case SYSCALL8_OPCODE_SET_PSP_DECRYPT_OPTIONS:
			return sys_psp_set_decrypt_options(param1, param2, (uint8_t *)param3, param4, param5, (uint8_t *)param6, param7);
		break;

		case SYSCALL8_OPCODE_READ_PSP_HEADER:
			return sys_psp_read_header(param1, (char *)param2, param3, (uint64_t *)param4);
		break;

		case SYSCALL8_OPCODE_READ_PSP_UMD:
			return sys_psp_read_umd(param1, (void *)param2, param3, param4, param5);
		break;

		case SYSCALL8_OPCODE_PSP_PRX_PATCH:
			return sys_psp_prx_patch((uint32_t *)param1, (uint8_t *)param2, (void *)param3);
		break;

		case SYSCALL8_OPCODE_PSP_CHANGE_EMU:
			return 0; //sys_psp_set_emu_path((char *)param1);
		break;

		case SYSCALL8_OPCODE_PSP_POST_SAVEDATA_INITSTART:
			return sys_psp_post_savedata_initstart(param1, (void *)param2);
		break;

		case SYSCALL8_OPCODE_PSP_POST_SAVEDATA_SHUTDOWNSTART:
			return sys_psp_post_savedata_shutdownstart();
		break;
		#endif

		case SYSCALL8_OPCODE_COBRA_USB_COMMAND:
		case SYSCALL8_OPCODE_DRM_GET_DATA:
		case SYSCALL8_OPCODE_SEND_POWEROFF_EVENT:
		case SYSCALL8_OPCODE_VSH_SPOOF_VERSION:
			return ENOSYS;
		break;

		case SYSCALL8_OPCODE_LOAD_VSH_PLUGIN:
			return sys_prx_load_vsh_plugin(param1, (char *)param2, (void *)param3, param4);
		break;

		case SYSCALL8_OPCODE_UNLOAD_VSH_PLUGIN:
			return sys_prx_unload_vsh_plugin(param1);
		break;

        default:
		#ifdef PS3M_API
		if (1 <= ps3mapi_partial_disable_syscall8)	return ENOSYS;
		#endif
		if (extended_syscall8.addr)
		{
			// Lets handle a few hermes opcodes ourself, and let their payload handle the rest
			if (function == 2)
			{
				return (uint64_t)_sys_cfw_memcpy((void *)param1, (void *)param2, param3);
			}
			else if (function == 0xC)
			{
				#ifdef DEBUG
				DPRINTF("Hermes copy inst: %lx %lx %lx\n", param1, param2, param3);
				#endif
			}
			else if (function == 0xD)
			{
				#ifdef DEBUG
				DPRINTF("Hermes poke inst: %lx %lx\n", param1, param2);
				#endif
				_sys_cfw_new_poke((void *)param1, param2);
				return param1;
			}

			int64_t (* syscall8_hb)() = (void *)&extended_syscall8;

			#ifdef DEBUG
			DPRINTF("Handling control to HB syscall 8 (opcode=0x%lx)\n", function);
			#endif

			return syscall8_hb(function, param1, param2, param3, param4, param5, param6, param7);
		}
		else // if (function >= 0x9800) // AV: allow peek all other addresses
		{
			// Partial support for lv1_peek here
			return lv1_peekd(function);
		}
		break;
	}

	#ifdef DEBUG
	DPRINTF("Unsupported syscall8 opcode: 0x%lx\n", function);
	#endif

	return ENOSYS;
}

//----------------------------------------
//KERNEL PATCH
//----------------------------------------
#define DO_PATCH_KERNEL_PATCH
//----------------------------------------
#ifdef DO_PATCH_KERNEL_PATCH
typedef struct
{
	uint32_t address;
	uint32_t data;
} Patch;

static Patch kernel_patches[] =
{
#ifdef DO_PATCH_PS2
	// sys_sm_shutdown, for ps2 let's pass to copy_from_user a fourth parameter
	{ shutdown_patch_offset, MR(R6, R31) },
#endif
	// User thread prio hack (needed for netiso)
	{ user_thread_prio_patch, NOP },
	{ user_thread_prio_patch2, NOP },
};


#define N_KERNEL_PATCHES	(sizeof(kernel_patches) / sizeof(Patch))

static INLINE void apply_kernel_patches(void)
{
	for (int i = 0; i < N_KERNEL_PATCHES; i++)
	{
		uint32_t *addr= (uint32_t *)MKA(kernel_patches[i].address);
		*addr = kernel_patches[i].data;
		clear_icache(addr, 4);
	}
}

#endif

int vsh_type = 0x666;

//Only rebug
static INLINE void get_rebug_vsh()
{
	CellFsStat stat;

	if(cellFsStat("/dev_flash/vsh/module/vsh.self.cexsp", &stat) == 0)
		vsh_type = 0xDE;
	else if(cellFsStat("/dev_flash/vsh/module/vsh.self.dexsp", &stat) == 0)
		vsh_type = 0xCE;

	#ifdef DEBUG
	if(vsh_type != 0x666)
		DPRINTF("We are in CFW Rebug REX, VSH is %XX\n", vsh_type);
	#endif
}

uint64_t vsh_offset = 0;

static INLINE int get_vsh_offset()
{
	int i;

	//First try with static offset..
	if( (lv1_peekd(vsh_pos_in_ram + 0x200) == 0xF821FF917C0802A6ULL) &&
		(lv1_peekd(vsh_pos_in_ram + 0x208) == 0xF80100804800039DULL) &&
		(lv1_peekd(vsh_pos_in_ram + 0x210) == 0x6000000048000405ULL) )
	{
		vsh_offset = vsh_pos_in_ram;
		#ifdef DEBUG
		DPRINTF("Vsh.self found with static offset at address 0x%lx\n", vsh_offset);
		#endif
	}
	//..if that not work brute-force the address
	else
	{
		for(i = 0x10000; i < 0x3000000; i += 0x10000)
		{
			if(lv1_peekd(i + 0x200) == 0xF821FF917C0802A6ULL)
			{
				if(lv1_peekd(i + 0x208) == 0xF80100804800039DULL)
				{
					if(lv1_peekd(i + 0x210) == 0x6000000048000405ULL)
					{
						vsh_offset = i;
						#ifdef DEBUG
						DPRINTF("Vsh.self found with brute-force at address 0x%lx\n", vsh_offset);
						#endif
						break;
					}
				}
			}
		}
	}
	//Vsh not found
	if(vsh_offset == 0)
	{
		#ifdef DEBUG
		DPRINTF("Vsh.self not found!!\n");
		#endif
		return -1;
	}

	return 0;
}


#ifdef DO_PATCH_PS2
int ps2_patches_done = 0;

static INLINE int ps2_vsh_patches()
{
	if(condition_ps2softemu == 0)
		return 0;

	if(vsh_offset == 0)
		return EINVAL;

	uint64_t ps2tonet = ps2tonet_patch, ps2tonet_size = ps2tonet_size_patch;
	uint64_t value = 0, addr = 0, addr2 = 0;
	int i = 0, mv_offset = 0;

	if(vsh_type == 0xCE)
	{
		//REBUG REX lv2 DEX and vsh CEX
		#ifdef cex_ps2tonet_patch
		ps2tonet = cex_ps2tonet_patch;
		#endif
		#ifdef cex_ps2tonet_size_patch
		ps2tonet_size = cex_ps2tonet_size_patch;
		#endif
	}
	else if(vsh_type == 0xDE)
	{
		//REBUG REX lv2 CEX and vsh DEX
		#ifdef dex_ps2tonet_patch
		ps2tonet = dex_ps2tonet_patch;
		#endif
		#ifdef dex_ps2tonet_size_patch
		ps2tonet_size = dex_ps2tonet_size_patch;
		#endif
	}

	//Find ps2tonet_patch patches
	//First try with static offset..
	addr = (vsh_offset + ps2tonet_size);
	addr2 = (vsh_offset + ps2tonet);

	for(mv_offset = 0; mv_offset < 0x2000000; mv_offset += 0x100000)
	{
		value = lv1_peekd(addr + mv_offset);
		if(value == 0x3800004078640020ULL)
		{
			if(lv1_peekw(addr2 + mv_offset) == 0x60638204)
			{
				#ifdef DEBUG
				DPRINTF("Ps2tonet patches are always there, nothing to do!\n");
				#endif
				return 0;
			}
		}
		else if(value == 0x38A004F078640020ULL)
		{
			if(lv1_peekw(addr2 + mv_offset) == 0x60638202)
			{
				#ifdef DEBUG
				DPRINTF("Offset ps2tonet_size_patch found with static offset at address: 0x%lx\n", addr + mv_offset);
				DPRINTF("Offset ps2tonet_patch found with static offset at address: 0x%lx\n", addr2 + mv_offset);
				#endif

				lv1_pokew(addr + mv_offset, LI(R5, 0x40));
				lv1_pokew(addr2 + mv_offset, ORI(R3, R3, 0x8204));

				#ifdef DEBUG
				value = lv1_peekw(addr + mv_offset);
				DPRINTF("First poke: 0x%lx\n", value);
				value = lv1_peekw(addr2 + mv_offset);
				DPRINTF("Second poke: 0x%lx\n", value);
				DPRINTF("SUCCESS: all patches DONE!\n");
				#endif
				return 0;
			}
		}
	}

	//brute-force
	mv_offset = (vsh_offset + 0x700);

	for(i = 0; i < 0x2000000; i += 4)
	{
		if(lv1_peekd(mv_offset + i) == 0x3860000060638202ULL)
		{
			addr = (mv_offset + i + 4);
			#ifdef DEBUG
			DPRINTF("Offset ps2tonet_patch found with brute-force at address 0x%lx\n", addr);
			#endif

			addr2 = (addr - 12);
			if(lv1_peekd(addr2) == 0x38A004F078640020ULL)
			{
				#ifdef DEBUG
				DPRINTF("Offset ps2tonet_size_patch found with brute-force at address 0x%lx\n", addr2);
				#endif

				lv1_pokew(addr, ORI(R3, R3, 0x8204));
				lv1_pokew(addr2, LI(R5, 0x40));

				#ifdef DEBUG
				value = lv1_peekw(addr);
				DPRINTF("First poke: 0x%lx\n", value);
				value = lv1_peekw(addr2);
				DPRINTF("Second poke: 0x%lx\n", value);
				DPRINTF("SUCCESS: all ps2tonet patches DONE!\n");
				#endif
				return 0;
			}
			else
			{
				#ifdef DEBUG
				DPRINTF("WARNING: ps2tonet_size_patch not found!!\n");
				#endif
			}
		}
	}

	#ifdef DEBUG
	DPRINTF("WARNING: ps2tonet patches not found!!\n");
	#endif
	return EINVAL;
}

#endif

//----------------------------------------
//MAIN
//----------------------------------------

static uint8_t mamba_loaded = 0;

int main(void)
{
	if(mamba_loaded == 1) return 0;
    mamba_loaded = 1;
	#ifdef DEBUG
	debug_init();
	debug_install();
	extern uint64_t _start;
	extern uint64_t __self_end;
	DPRINTF("MAMBA says hello (load base = %p, end = %p) (version = %08X)\n", &_start, &__self_end, MAKE_VERSION(MAMBA_VERSION, FIRMWARE_VERSION, IS_CFW));
	#endif

    get_rebug_vsh();

    if (!vsh_process) vsh_process = get_vsh_process(); //NzV
    if(vsh_process) get_vsh_offset();

	//get_rebug_vsh();
	//get_vsh_offset();

	//if (!vsh_process) vsh_process = get_vsh_process(); //NzV

    storage_ext_init();
    modules_patch_init();

	apply_kernel_patches();
	map_path_patches(1);
	storage_ext_patches();
    region_patches();

    #ifdef DO_PATCH_PS2
    ps2_vsh_patches();
	#endif

	//Check if Iris (sky) payload is loaded
	extended_syscall8.addr = 0;
	uint64_t sys8_id = *((uint64_t *)MKA(0x4f0));
	if((sys8_id>>32) == 0x534B3145) //SK10 HEADER
	{
		isLoadedFromIrisManager = 1;
		sys8_id&= 0xffffffffULL;
		extended_syscall8.addr = (void *) *((uint64_t *)MKA(0x8000000000000000ULL + (sys8_id + 0x20ULL)));
		extended_syscall8.toc = (void *) *(uint64_t *)(MKA(0x3000));
		//Remove syscall40 used by Iris (sky) payload to load MAMBA
		uint64_t syscall_not_impl = *(uint64_t *)MKA(syscall_table_symbol);
		*(uint64_t *)MKA(syscall_table_symbol+ ( 8* 40)) = syscall_not_impl;
	}

	// find lv2 on lv1
	for(uint8_t lv2_offset = 1; lv2_offset < 0x10; lv2_offset++)
	{
		LV2_OFFSET_ON_LV1 = (uint64_t)lv2_offset * 0x1000000ULL;
		if(lv1_peekd(LV2_OFFSET_ON_LV1 + 0x3000ULL) == MKA(TOC)) break;
	}

	create_syscall2(8, syscall8);
	create_syscall2(6, sys_cfw_peek);
	create_syscall2(7, sys_cfw_poke);
	create_syscall2(9, sys_cfw_lv1_poke);
	create_syscall2(10, sys_cfw_lv1_call);
	create_syscall2(11, sys_cfw_lv1_peek);

	//map_path("/app_home", "/dev_usb000", 0);

	//CellFsStat stat;
	//if (cellFsStat("/dev_hdd0", &stat) == 0) read_mamba_config();

    return 0;
}
