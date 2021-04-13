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
#include <lv2/syscall.h>
#include <lv1/stor.h>
#include <lv1/patch.h>
#include <lv2/ctrl.h>
#include "common.h"
#include "syscall8.h"
#include "modulespatch.h"
#include "mappath.h"
#include "storage_ext.h"
#include "region.h"
#include "psp.h"
#include "config.h"
#include "sm_ext.h"
//#include "laboratory.h"

#ifdef PS3M_API
#include "ps3mapi_core.h"
#endif

#include "kernel_payload.h"
#include "lv2_patches.h"
#include "vsh_patches.h"
#include "peek_poke.h"
#ifdef FAN_CONTROL
#include "fan_control.h"
#endif
#ifdef DO_REACTPSN
#include "reactPSN.h"
#endif
#ifdef QA_FLAG
//#include "qa_flag.h"
#include "qa.h"
#endif
//----------------------------------------
//VERSION
//----------------------------------------

#define IS_CFW			1

#ifdef DO_PATCH_PS2
#define PS2PSP_CAPABILITY	2
#else
#define PS2PSP_CAPABILITY	0
#endif

#define MAMBA_VERSION		0x0F
#define MAMBA_VERSION_BCD	0x0840

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
//10 = 8.0

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
// HABIB FUNCTIONS FROM COBRA 8.x
//----------------------------------------
#define CB_LOCATION		"/dev_blind/rebug/cobra/stage2.cex"
#define CB_LOCATION_DEX	"/dev_blind/rebug/cobra/stage2.dex"

#ifdef cellFsRename_internal_symbol
int disable_cobra_stage()
{
	cellFsUtilMount_h("CELL_FS_IOS:BUILTIN_FLSH1", "CELL_FS_FAT", "/dev_blind", 0, 0, 0, 0, 0);

	cellFsRename(CB_LOCATION,     CB_LOCATION     ".bak");
	cellFsRename(CB_LOCATION_DEX, CB_LOCATION_DEX ".bak");

	uint64_t sce = 0x534345000000000; // SCE
	save_file("/dev_hdd0/tmp/loadoptical", (void*)sce, 4);

	return SUCCEEDED;
}
#else
int disable_cobra_stage()
{
	cellFsUtilMount_h("CELL_FS_IOS:BUILTIN_FLSH1", "CELL_FS_FAT", "/dev_blind", 0, 0, 0, 0, 0);

	uint64_t **table = (uint64_t **)MKA(syscall_table_symbol);
	f_desc_t *f = (f_desc_t *)table[SYS_CELLFSRENAME];
	uint64_t *sc = (uint64_t *)f->addr;

	f_desc_t fn;
	fn.addr = (void*)sc;
	fn.toc = (void*)MKA(TOC);
	int (*cellFsRename)(const char *, const char *) = (void *)&fn;

	cellFsRename(CB_LOCATION, CB_LOCATION ".bak");

//	CellFsStat stat;
//	cellFsStat(CB_LOCATION, &stat);
//	uint64_t len = stat.st_size;
//	uint8_t *buf;
//
//	page_allocate_auto(NULL, 0x40000, (void **)&buf);
//	if(read_file(CB_LOCATION, buf, len) == len)
//	{
//		save_file(CB_LOCATION ".bak", buf, len);
//		cellFsUnlink(CB_LOCATION);
//	}
//
//	free_page(NULL, buf);

	// force load optical ps2 disk
	uint64_t sce = 0x534345000000000; // SCE
	save_file("/dev_hdd0/tmp/loadoptical", (void*)sce, 4);

	return SUCCEEDED;
}
#endif

//----------------------------------------
//SYSCALL 8 MAMBA
//----------------------------------------

extern f_desc_t open_path_callback;

extern uint8_t allow_restore_sc; // homebrew_blocker.h

#ifdef DO_AUTO_MOUNT_DEV_BLIND
extern uint8_t auto_dev_blind;	// homebrew_blocker.h
#endif

#ifdef DO_PHOTO_GUI
extern uint8_t photo_gui;		// mappath.c
#endif

#ifdef DO_AUTO_EARTH
extern uint8_t auto_earth;		// mappath.c
extern uint8_t earth_id;		// mappath.c
#endif

#ifdef MAKE_RIF
extern uint8_t skip_existing_rif; // make_rif.h
#endif

#ifdef PS3M_API

static uint64_t ps3mapi_key = 0;
static uint8_t ps3mapi_access_tries = 0;
static uint8_t ps3mapi_access_granted = 1;

static int ps3mapi_partial_disable_syscall8 = 0;
static uint8_t disable_cobra = 0;

uint64_t LV2_OFFSET_ON_LV1 = 0; // 0x1000000 on 4.46, 0x8000000 on 4.76
uint64_t lv2_offset = 0;

#endif

LV2_SYSCALL2(int64_t, syscall8, (uint64_t function, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5, uint64_t param6, uint64_t param7))
{
	extend_kstack(0);

	#ifdef PS3ITA
	DPRINTF("Syscall 8 -> %lx\n", function);
	#endif

	// -- AV: temporary disable cobra syscall (allow dumpers peek 0x1000 to 0x9800)
	static uint8_t tmp_lv1peek = 0;

	if((ps3mapi_partial_disable_syscall8 == 0) && (extended_syscall8.addr == 0) && ps3mapi_access_granted)
	{
		if((function >= 0x9800) || (function & 3)) tmp_lv1peek = 0; else // normal syscall 8
		if( function <= 0x1000)
		{
			tmp_lv1peek = 1; // enable lv1 peek if lv1peek address <= 0x1000 (e.g. lv1 dump)
			if(function <= SYSCALL8_OPCODE_ENABLE_COBRA)
			{
				if(param1 >= SYSCALL8_DISABLE_COBRA_CAPABILITY)
					return (param1 == SYSCALL8_DISABLE_COBRA_CAPABILITY) ?
								SYSCALL8_DISABLE_COBRA_OK :  // <- syscall3(sycall8, 0, 2) can disable: returns 0x5555;
								disable_cobra;               // <- syscall3(sycall8, 0, 3) is disabled? returns 0/1
				else
					disable_cobra = ((function == SYSCALL8_OPCODE_DISABLE_COBRA) && (param1 == 1)); // <- syscall3(sycall8, 0, 1) = disable cobra (enable lv1peek)
																									// <- syscall3(sycall8, 1, 0) = enable cobra (disable lv1peek)
			}
		}

		if(tmp_lv1peek) return lv1_peekd(function); // return lv1peek(address)
	}
	else
		tmp_lv1peek = 0; // normal syscall 8
	// --

	// Some processsing to avoid crashes with lv1 dumpers

	static uint32_t pid_blocked = 0;
	uint32_t pid;

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
		if (function == SYSCALL8_OPCODE_PS3MAPI && ps3mapi_access_granted)
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
	if(disable_cobra)
		return lv1_peekd(function);

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
					return SUCCEEDED;
				break;
				case PS3MAPI_OPCODE_LV2_PEEK:
					return lv1_peekd(param2+LV2_OFFSET_ON_LV1);
				break;
				case PS3MAPI_OPCODE_LV2_POKE:
					lv1_poked(param2+LV2_OFFSET_ON_LV1, param3);
					return SUCCEEDED;
				break;

				//----------
				//SECURITY
				//----------
				case PS3MAPI_OPCODE_SET_ACCESS_KEY:
					ps3mapi_key = param2;
					ps3mapi_access_granted = 0;
					ps3mapi_access_tries = 0;
					return SUCCEEDED;

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
				case PS3MAPI_OPCODE_PROC_PAGE_ALLOCATE:
					#ifdef mmapper_flags_temp_patch
					return ps3mapi_process_page_allocate((process_id_t)param2, param3, param4, param5, param6, (uint64_t *)param7); // TheRouletteBoi
					#else
					return ENOSYS;
					#endif
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
				case PS3MAPI_OPCODE_GET_PROC_MODULE_INFO:
					return ps3mapi_get_process_module_info((process_t)param2, (sys_prx_id_t)param3, (char *)param4, (char *)param5);
				break;
				case PS3MAPI_OPCODE_GET_PROC_MODULE_SEGMENTS:
					return ps3mapi_get_process_module_segments((process_id_t)param2, (sys_prx_id_t)param3, (sys_prx_module_info_t *)param4); // TheRouletteBoi
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
				case PS3MAPI_OPCODE_GET_VSH_PLUGIN_BY_NAME:
					return ps3mapi_get_vsh_plugin_slot_by_name((char *)param2, (uint8_t)param3);
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
// 8.3
				case PS3MAPI_OPCODE_CREATE_CFW_SYSCALLS:
					create_syscalls();
					return SUCCEEDED;
				break;
				case PS3MAPI_OPCODE_ALLOW_RESTORE_SYSCALLS:
					allow_restore_sc = (uint8_t)param2; // 1 = allow, 0 = do not allow
					return SUCCEEDED;
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
// 8.3
				//----------
				//MISC
				//----------
				#ifdef DO_AUTO_MOUNT_DEV_BLIND
				case PS3MAPI_OPCODE_AUTO_DEV_BLIND:
					auto_dev_blind = (uint8_t)param2;
					return auto_dev_blind;
				break;
				#endif

				#ifdef MAKE_RIF
				case PS3MAPI_OPCODE_SKIP_EXISTING_RIF:
					skip_existing_rif = (uint8_t)param2;
					return skip_existing_rif;
				break;
				#endif

				#ifdef DO_AUTO_EARTH
				case PS3MAPI_OPCODE_AUTO_EARTH:
					auto_earth = (uint8_t)param2;
					earth_id   = (uint8_t)param3;
					return auto_earth;
				break;
				#endif

				#ifdef DO_PHOTO_GUI
				case PS3MAPI_OPCODE_PHOTO_GUI:
					photo_gui = (uint8_t)param2;
					return photo_gui;
				break;
				#endif

				#ifdef FAN_CONTROL
				case PS3MAPI_OPCODE_SET_FAN_SPEED:
					if(param2 == 1)
						do_fan_control();
					else
						fan_control_running = 0;

					return sm_set_fan_policy(0, (uint8_t)(param2 >= 0x33 ? 2 : 1), (uint8_t)(param2 >= 0x33 ? param2 : 0));
				break;

				case PS3MAPI_OPCODE_GET_FAN_SPEED:
					return sm_get_fan_speed();
				break;
				#endif

				#ifdef sm_ring_buzzer_symbol
				case PS3MAPI_OPCODE_RING_BUZZER:
					return sm_ring_buzzer((uint16_t)param2);
				break;
				#endif

				//----------
				//QA
				//----------
				#ifdef QA_FLAG
				case PS3MAPI_OPCODE_CHECK_QA:
					return read_qa_flag();
				break;
				case PS3MAPI_OPCODE_ENABLE_QA:
					return set_qa_flag(1);
				break;
				case PS3MAPI_OPCODE_DISABLE_QA:
					return set_qa_flag(0);
				break;
				#endif

				//----------
				//DEFAULT
				//----------
				default:
					#ifdef DEBUG
					DPRINTF("syscall8: Unsupported PS3M_API opcode: 0x%lx\n", function);
					#endif
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
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 8) = syscall_not_impl;
				#endif
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 9)  = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 10) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 11) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 15) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 35) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 36) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 38) = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 6)  = syscall_not_impl;
				*(uint64_t *)MKA(syscall_table_symbol + 8 * 7)  = syscall_not_impl;
			return SYSCALL8_STEALTH_OK;
		}
		break;
		#endif

		//--------------------------
		// DISC EMULATION
		//--------------------------
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
// 7.5
		case SYSCALL8_OPCODE_USE_PS2NETEMU:
			#ifdef ps2tonet_patch
			return bc_to_net((int)param1);
			#else
			return ENOSYS; // ps2tonet_patch not defined
			#endif
		break;
		#endif
		case SYSCALL8_OPCODE_MOUNT_DISCFILE_PROXY:
			return sys_storage_ext_mount_discfile_proxy(param1, param2, param3, param4, param5, param6, (ScsiTrackDescriptor *)param7);
		break;

		case SYSCALL8_OPCODE_UMOUNT_DISCFILE:
			return sys_storage_ext_umount_discfile();
		break;

		//--------------------------
		// PSP EMULATION
		//--------------------------
		#ifdef DO_PATCH_PSP
		case SYSCALL8_OPCODE_SET_PSP_UMDFILE:
			vsh_process = get_vsh_process(); //NzV
			if(vsh_process) get_vsh_offset();
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
			return SUCCEEDED; //sys_psp_set_emu_path((char *)param1); // deprecated
		break;

		case SYSCALL8_OPCODE_PSP_POST_SAVEDATA_INITSTART:
			return sys_psp_post_savedata_initstart(param1, (void *)param2);
		break;

		case SYSCALL8_OPCODE_PSP_POST_SAVEDATA_SHUTDOWNSTART:
			return sys_psp_post_savedata_shutdownstart();
		break;
		#endif

		case SYSCALL8_OPCODE_MOUNT_ENCRYPTED_IMAGE:
			return SUCCEEDED; // sys_storage_ext_mount_encrypted_image((char *)param1, (char *)param2, (char *)param3, param4);

		//--------------------------
		// CONFIG
		//--------------------------
		case SYSCALL8_OPCODE_READ_COBRA_CONFIG:
			return sys_read_mamba_config((MambaConfig *)param1);
		break;

		case SYSCALL8_OPCODE_WRITE_COBRA_CONFIG:
			return sys_write_mamba_config((MambaConfig *)param1);
		break;

		//--------------------------
		// MAP PATHS
		//--------------------------
		case SYSCALL8_OPCODE_MAP_PATHS:
			return sys_map_paths((char **)param1, (char **)param2, (unsigned int)param3);
		break;

		case SYSCALL8_OPCODE_AIO_COPY_ROOT:
			return sys_aio_copy_root((char *)param1, (char *)param2);
		break;

		case SYSCALL8_OPCODE_GET_MAP_PATH:
			return get_map_path((unsigned int)param1, (char *)param2, (char *)param3);
		break;

		case SYSCALL8_OPCODE_MAP_PATH_CALLBACK:
			open_path_callback.addr = (void*)MKA(param1);
			open_path_callback.toc = (void *)MKA(param2);
		break;

// 8.1
		//------------------------------
		// INSTALL & RUN KERNEL PAYLOAD
		//------------------------------
		case SYSCALL8_OPCODE_RUN_PAYLOAD:
			return inst_and_run_kernel((uint8_t *)param1, param2);
		break;

		case SYSCALL8_OPCODE_RUN_PAYLOAD_DYNAMIC:
			return inst_and_run_kernel_dynamic((uint8_t *)param1, param2, (uint64_t *)param3);
		break;

		case SYSCALL8_OPCODE_UNLOAD_PAYLOAD_DYNAMIC:
			return unload_plugin_kernel(param1);
		break;

		//--------------------------
		// VSH PLUGINS
		//--------------------------
		case SYSCALL8_OPCODE_LOAD_VSH_PLUGIN:
			return sys_prx_load_vsh_plugin(param1, (char *)param2, (void *)param3, param4);
		break;

		case SYSCALL8_OPCODE_UNLOAD_VSH_PLUGIN:
			return sys_prx_unload_vsh_plugin(param1);
		break;
		//--------------------------
		// ADVANCED POKE (syscall8)
		//--------------------------
// 8.1
		case SYSCALL8_OPCODE_POKE_LV2:
			*(uint64_t *)param1 = param2;
			clear_icache((void *)param1, 8);
			return SUCCEEDED;
		break;
// 8.3
		case SYSCALL8_OPCODE_POKE32_LV2:
			*(uint32_t *)param1 = (uint32_t)param2;
			clear_icache((void *)param1, 4);
			return SUCCEEDED;
		break;

		case SYSCALL8_OPCODE_POKE16_LV2:
			*(uint16_t *)param1 = (uint16_t)param2;
			clear_icache((void *)param1, 2);
			return SUCCEEDED;
		break;

		case SYSCALL8_OPCODE_POKE8_LV2:
			*(uint8_t *)param1 = (uint8_t)param2;
			clear_icache((void *)param1, 1);
			return SUCCEEDED;
		break;

		case SYSCALL8_OPCODE_POKE_LV1:
			lv1_poked(param1, param2);
			return SUCCEEDED;
		break;

		case SYSCALL8_OPCODE_POKE32_LV1:
			lv1_pokew(param1, (uint32_t)param2);
			return SUCCEEDED;
		break;

		case SYSCALL8_OPCODE_POKE16_LV1:
			lv1_pokeh(param1, (uint16_t)param2);
			return SUCCEEDED;
		break;

		case SYSCALL8_OPCODE_POKE8_LV1:
			lv1_pokeb(param1, (uint8_t)param2);
			return SUCCEEDED;
		break;

		//--------------------------
		// VERSION INFO
		//--------------------------
		case SYSCALL8_OPCODE_GET_VERSION:
			return sys_get_version((uint32_t *)param1);
		break;

		case SYSCALL8_OPCODE_GET_VERSION2:
			return sys_get_version2((uint16_t *)param1);
		break;

		case SYSCALL8_OPCODE_GET_MAMBA:
			return 0x666;
		break;

		case SYSCALL8_OPCODE_GET_ACCESS:
		case SYSCALL8_OPCODE_REMOVE_ACCESS:
			return SUCCEEDED; //needed for mmCM
		break;

		//--------------------------
		// PROCESS
		//--------------------------
		case SYSCALL8_OPCODE_PROC_CREATE_THREAD:
			return ps3mapi_create_process_thread((process_id_t)param1, (thread_t *)param2, (void *)param3, (uint64_t)param4, (int)param5, (size_t)param6, (char *)param7); // TheRouletteBoi
		break;

		//--------------------------
		// MISC
		//--------------------------
		case SYSCALL8_OPCODE_SEND_POWEROFF_EVENT:
			return sys_sm_ext_send_poweroff_event((int)param1);
		break;

		case SYSCALL8_OPCODE_DISABLE_COBRA_STAGE:
			return disable_cobra_stage();
		break;

#ifdef DEBUG
		case SYSCALL8_OPCODE_DUMP_STACK_TRACE:
			dump_stack_trace3((void *)param1, 16);
			return SUCCEEDED;
		break;

		case SYSCALL8_OPCODE_COBRA_USB_COMMAND:
		case SYSCALL8_OPCODE_DRM_GET_DATA:
		case SYSCALL8_OPCODE_VSH_SPOOF_VERSION:
			return ENOSYS; // deprecated opcodes
		break;

#endif
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

void create_syscalls(void)
{
	create_syscall2(8, syscall8);
	create_syscall2(6, sys_cfw_peek);
	create_syscall2(7, sys_cfw_poke);
	create_syscall2(9, sys_cfw_lv1_poke);
	create_syscall2(10, sys_cfw_lv1_call);
	create_syscall2(11, sys_cfw_lv1_peek);
	create_syscall2(15, sys_cfw_lv2_func);
}

//----------------------------------------
//MAIN
//----------------------------------------


int main(void)
{
	// exit if CFW syscall 11 already exists, used to prevent payload reload
	if((*(uint64_t *)MKA(syscall_table_symbol + 8 * 11)) != (*(uint64_t *)MKA(syscall_table_symbol))) return SUCCEEDED;

	#ifdef DEBUG
	debug_init();
	debug_install();
	extern uint64_t _start;
	extern uint64_t __self_end;
	DPRINTF("MAMBA loaded (load base = %p, end = %p) (version = %08X)\n", &_start, &__self_end, MAKE_VERSION(MAMBA_VERSION, FIRMWARE_VERSION, IS_CFW));
	#endif

	#ifdef DO_REACTPSN
	ecdsa_set_curve();
	ecdsa_set_pub();
//	ecdsa_set_priv();
	#endif
	vsh_process = get_vsh_process(); //NzV
	if(vsh_process) get_vsh_offset();

	storage_ext_init();
	modules_patch_init();

	apply_kernel_patches();
	map_path_patches(1);
	//storage_ext_patches(); // already called in modules_patch_init()
	//region_patches();      //

	#ifdef DO_PATCH_PS2
	ps2_vsh_patches();
	#endif
	#ifdef FAN_CONTROL
	fan_patches();
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
		*(uint64_t *)MKA(syscall_table_symbol + (8 * 40)) = syscall_not_impl;
	}

	// find lv2 on lv1
	for(uint8_t lv2_offset = 1; lv2_offset < 0x10; lv2_offset++)
	{
		LV2_OFFSET_ON_LV1 = (uint64_t)lv2_offset * 0x1000000ULL;
		if(lv1_peekd(LV2_OFFSET_ON_LV1 + 0x3000ULL) == MKA(TOC)) break;
	}

	create_syscalls();

	load_boot_plugins();
	load_boot_plugins_kernel();
	init_mount_hdd0();

	//map_path("/app_home", "/dev_usb000", 0);

#ifdef DEBUG
	// "Laboratory"
	//do_hook_all_syscalls();
	//do_dump_threads_info_test();
	//do_dump_processes_test();
	//do_hook_load_module();
	//do_hook_mutex_create();
	//do_ps2net_copy_test();
	//do_dump_modules_info_test();
	//do_pad_test();
#endif
	return SUCCEEDED;
}
