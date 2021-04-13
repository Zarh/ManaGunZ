#include <lv2/lv2.h>
#include <lv2/libc.h>
#include <lv2/interrupt.h>
#include <lv2/modules.h>
#include <lv2/process.h>
#include <lv2/memory.h>
//#include <lv2/time.h>
#include <lv2/io.h>
#include <lv2/pad.h>
#include <lv2/symbols.h>
#include <lv2/patch.h>
#include <lv2/error.h>
#include <lv2/security.h>
#include <lv2/thread.h>
#include <lv2/syscall.h>
//#include <lv1/patch.h>
#include "common.h"
#include "modulespatch.h"
#include "crypto.h"
#include "config.h"
#include "storage_ext.h"
#include "psp.h"
#include "self.h"
#include "syscall8.h"
#include "mappath.h"
#include "region.h"
#include "ps3mapi_core.h"

#undef APPLY_KERNEL_PATCHES

#ifdef DO_CFW2OFW_FIX
extern uint8_t CFW2OFW_game; // homebrew_blocker.h
#endif

static inline void enable_kernel_patches(void)
{
#ifdef DO_PATCH_COBRA810
	do_patch32(MKA(module_sdk_version_patch_offset), NOP);
	do_patch32(MKA(patch_func8_offset1),     0x38600000);
	do_patch32(MKA(patch_func8_offset2),     0x60000000);
	do_patch32(MKA(user_thread_prio_patch),  0x60000000); // for netiso
	do_patch32(MKA(user_thread_prio_patch2), 0x60000000); // for netiso
	do_patch32(MKA(ECDSA_1),                 0x38600000);
	do_patch32(MKA(lic_patch),               0x38600001); // ignore LIC.DAT check
	do_patch32(MKA(patch_func9_offset),      0x60000000);
	do_patch32(MKA(fix_80010009),            0x60000000); // fix 80010009 error
	do_patch(MKA(ode_patch),         0x38600000F8690000); // fix 0x8001002B / 80010017 errors
	do_patch(MKA(ECDSA_2),           0x386000004e800020);
	do_patch(MKA(mem_base2),         0x386000014e800020); // psjailbreak, PL3, etc destroy this function to copy their code there.
	do_patch(MKA(fix_8001003D),      0x63FF003D60000000); // fix 8001003D error
	do_patch(MKA(fix_8001003E),      0x3FE080013BE00000); // fix 8001003E error
	do_patch(MKA(PATCH_JUMP),        0x2F84000448000098);
	*(uint64_t *)MKA(ECDSA_FLAG) = 0;
#endif
}

//----------------------------------------
//DYNAMIC MODULES PATCH
//----------------------------------------
#define DO_PATCH //libfs.sprx

/* If you want only PS2 ISO support set in the Makefile_x.xx EMU_SUPPORT to ps2
   If you want only PSP ISO support set in the Makefile_x.xx EMU_SUPPORT to psp
   If you want PSP and PS2 ISO support set in the Makefile_x.xx EMU_SUPPORT to full
//----------------------------------------*/

LV2_EXPORT int decrypt_func(uint64_t *, uint32_t *);

typedef struct
{
	uint64_t hash;
	SprxPatch *patch_table;
} PatchTableEntry;

typedef struct
{
	uint8_t keys[16];
	uint64_t nonce;
} KeySet;

#define N_SPRX_KEYS_1 (sizeof(sprx_keys_set1)/sizeof(KeySet))

static KeySet sprx_keys_set1[] =
{
	{
		{
			0xD6, 0xFD, 0xD2, 0xB9, 0x2C, 0xCC, 0x04, 0xDD,
			0x77, 0x3C, 0x7C, 0x96, 0x09, 0x5D, 0x7A, 0x3B
		},

		0xBA2624B2B2AA7461ULL
	},
};

// Keyset for pspemu, and for future vsh plugins or whatever is added later

#define N_SPRX_KEYS_2 (sizeof(sprx_keys_set2)/sizeof(KeySet))

static KeySet sprx_keys_set2[] =
{
	{
		{
			0x7A, 0x9E, 0x0F, 0x7C, 0xE3, 0xFB, 0x0C, 0x09,
			0x4D, 0xE9, 0x6A, 0xEB, 0xA2, 0xBD, 0xF7, 0x7B
		},

		0x8F8FEBA931AF6A19ULL
	},

	{
		{
			0xDB, 0x54, 0x44, 0xB3, 0xC6, 0x27, 0x82, 0xB6,
			0x64, 0x36, 0x3E, 0xFF, 0x58, 0x20, 0xD9, 0x83
		},

		0xE13E0D15EF55C307ULL
	},
};

static uint8_t *saved_buf;
static void *saved_sce_hdr;

#ifndef APPLY_KERNEL_PATCHES

LV2_HOOKED_FUNCTION_PRECALL_2(int, post_lv1_call_99_wrapper, (uint64_t *spu_obj, uint64_t *spu_args))
{
	saved_buf = (void *)spu_args[0x20/8];
	saved_sce_hdr = (void *)spu_args[8/8];

	#ifdef DEBUG
	process_t process = get_current_process();
	if (process)
	{
		DPRINTF("caller_process = %08X %s\n", process->pid, get_process_name(process));
		DPRINTF("saved sce hdr ptr:%p\n", saved_sce_hdr);
	}
	#endif

	return SUCCEEDED;
}

#else

static void disable_kernel_patches(void)
{
#ifdef DO_PATCH_COBRA810
	
	#ifdef patch_func8_offset2_restore
		do_patch32(MKA(patch_func8_offset2),     patch_func8_offset2_restore);
	#endif

	#ifdef patch_func8_offset2_restore
		do_patch32(MKA(lic_patch),               lic_patch_restore); // ignore LIC.DAT check
	#endif

	#ifdef ECDSA_FLAG
		do_patch32(MKA(module_sdk_version_patch_offset), 0x419D0008);
		do_patch32(MKA(patch_func8_offset1),     0x7FE307B4);
	 //	do_patch32(MKA(patch_func8_offset2),     0x48216FB5);
		do_patch32(MKA(user_thread_prio_patch),  0x419DFF84); // for netiso
		do_patch32(MKA(user_thread_prio_patch2), 0x419D0258); // for netiso
		do_patch32(MKA(ECDSA_1),                 0x7FE307B4);
	 //	do_patch32(MKA(lic_patch),               0x48240EED); // ignore LIC.DAT check
		do_patch32(MKA(patch_func9_offset),      0x419E00AC);
		do_patch32(MKA(fix_80010009),            0x419E00AC); // fix 80010009 error
		do_patch(MKA(ode_patch),         0xE86900007C6307B4); // fix 0x8001002B / 80010017 errors
		do_patch(MKA(ECDSA_2),           0xF821FE617CE802A6);
		do_patch(MKA(mem_base2),         0xF821FEB17C0802A6); // psjailbreak, PL3, etc destroy this function to copy their code there.
		do_patch(MKA(fix_8001003D),      0x63FF003D419EFFD4); // fix 8001003D error
		do_patch(MKA(fix_8001003E),      0x3FE0800163FF003E); // fix 8001003E error
		do_patch(MKA(PATCH_JUMP),        0x2F840004409C0048);
		*(uint64_t *)MKA(ECDSA_FLAG) = 0;
	#endif
#endif

}

LV2_HOOKED_FUNCTION_PRECALL_2(int, post_lv1_call_99_wrapper, (uint64_t *spu_obj, uint64_t *spu_args))
{
	apply_kernel_patches_call99();

//	ps3mapi_unhook_all();

	#ifdef DEBUG
	debug_uninstall();
	#endif

	saved_buf = (void *)spu_args[0x20/8];
	saved_sce_hdr = (void *)spu_args[8/8];

	#ifdef	DEBUG
	process_t process = get_current_process();
	if (process)
	{
		DPRINTF("caller_process = %08X %s\n", process->pid, get_process_name(process));
		DPRINTF("saved sce hdr ptr:%p\n", saved_sce_hdr);
	}
	#endif

	uint8_t is_ptr = (((uint64_t)saved_sce_hdr & 0xff00000000000000)>>56); //new
	#ifdef	DEBUG
	DPRINTF("IS_PTR:%x\n", is_ptr);
	#endif

	if(is_ptr == 0x80) //new -> if(is_ptr>=0x8000000000000000)
	{
		// self types: 0x180 = sprx, 0x210 = self, 0x130 = spu
		if((*(uint64_t *)(saved_sce_hdr+0x48) >= 0x200) || (*(uint64_t *)(saved_sce_hdr+0x48) == 0x130))
		{
			#ifdef DEBUG
			DPRINTF("SELF loading!\n");
			#endif
			timer_usleep(700000);
		}
	}

	enable_kernel_patches();

	#ifdef DEBUG
	debug_hook();
	#endif

//	modules_patch_init();
//	map_path_patches(0);

	return SUCCEEDED;
}
#endif

LV2_HOOKED_FUNCTION_COND_POSTCALL_2(int, pre_modules_verification, (uint32_t *ret, uint32_t error))
{
	#ifdef FIRMWARE_CEX
	/* Patch original from psjailbreak. Needs some tweaks to fix some games */
/*	#ifdef DEBUG
	DPRINTF("err = %x\n", error);
	#endif */

	/* if (error == 0x13)
	{
		//dump_stack_trace2(10);
		//return DO_POSTCALL; //Fixes Mortal Kombat
	} */

	*ret = 0;
	return SUCCEEDED;
	#else
		return DO_POSTCALL;  //Fixes fucking DEX issue, no more crying bitches  //
	#endif
}
#ifdef DEBUG
static char *hash_to_name(uint64_t trunc_hash, uint64_t hash2)
{
	if(trunc_hash == (LIBFS_EXTERNAL_HASH >> 16))
		return "libfs.sprx";
#ifdef DO_PATCH_PSP
	else if(trunc_hash == (PSP_EMULATOR_HASH >> 16))
		return "psp_emulator.self";
	else if(trunc_hash == (EMULATOR_API_HASH >> 16))
		return "emulator_api.sprx";
	else if(trunc_hash == (PEMUCORELIB_HASH >> 16))
		return "PEmuCoreLib.sprx";
	else if(trunc_hash == (LIBSYSUTIL_SAVEDATA_PSP_HASH >> 16))
		return "libsysutil_savedata_psp.sprx";
/*
	else if(trunc_hash == (BASIC_PLUGINS_HASH >> 16))
		return "basic_plugins.sprx";
	#ifdef BASIC_PLUGINS_REBUG_HASH
	else if(trunc_hash == (BASIC_PLUGINS_REBUG_HASH >> 16))
		return "basic_plugins.sprx";
	#endif
*/
#endif
#ifdef DO_PATCH_PS2
	else if(trunc_hash == (EXPLORE_PLUGIN_HASH >> 16))
		return "explore_plugin.sprx";
	else if(trunc_hash == (EXPLORE_CATEGORY_GAME_HASH >> 16))
		return "explore_category_game.sprx";
	else if(trunc_hash == (GAME_EXT_PLUGIN_HASH >> 16))
		return "game_ext_plugin.sprx";
	#ifdef EXPLORE_PLUGIN_REBUG_HASH
	else if(trunc_hash == (EXPLORE_PLUGIN_REBUG_HASH >> 16))
		return "explore_plugin.sprx";
	#endif
	#ifdef EXPLORE_CATEGORY_GAME_REBUG_HASH
	else if(trunc_hash == (EXPLORE_CATEGORY_GAME_REBUG_HASH >> 16))
		return "explore_category_game.sprx";
	#endif
	#ifdef GAME_EXT_PLUGIN_REBUG_HASH
	else if(trunc_hash == (GAME_EXT_PLUGIN_REBUG_HASH >> 16))
		return "game_ext_plugin.sprx";
	#endif
#endif

	switch(hash2)
	{
#ifdef DO_PATCH_COBRA810
		case VSH_HASH:
			return "vsh.self";
		break;
#endif
		case EXPLORE_PLUGIN_HASH:
			return "explore_plugin.sprx";
		break;

		case EXPLORE_CATEGORY_GAME_HASH:
			return "explore_category_game.sprx";
		break;

		case GAME_EXT_PLUGIN_HASH:
			return "game_ext_plugin.sprx";
		break;

		case PSP_EMULATOR_HASH:
			return "psp_emulator.self";
		break;

		case EMULATOR_API_HASH:
			return "emulator_api.sprx";
		break;

		case PEMUCORELIB_HASH:
			return "PEmuCoreLib.sprx";
		break;

		case LIBFS_EXTERNAL_HASH:
			return "libfs.sprx";
		break;

		case LIBSYSUTIL_SAVEDATA_PSP_HASH:
			return "libsysutil_savedata_psp.sprx";
		break;

		/*case BASIC_PLUGINS_HASH:
			return "basic_plugins.sprx";
		break;*/
#ifdef EXT_AUDIO
		case LIBAUDIO_HASH:
			return "libaudio.sprx";
		break;
#endif
#ifdef DO_PATCH_COBRA810

		case BDP_DISC_CHECK_PLUGIN_HASH:
			return "bdp_disccheck_plugin.sprx";
		break;

		case PS1_EMU_HASH:
			return "ps1_emu.self";
		break;

		case PS1_NETEMU_HASH:
			return "ps1_netemu.self";
		break;

		case NAS_PLUGIN_HASH:
			return "nas_plugin.sprx";
		break;

		case AUTODOWNLOAD_PLUGIN_HASH:
			return "autodownload_plugin.sprx";
		break;

		case DOWNLOAD_PLUGIN_HASH:
			return "download_plugin.sprx";
		break;

		case BDP_BDMV_HASH:
			return "bdp_BDMV.self";
		break;

		case BDP_BDVD_HASH:
			return "bdp_BDVD.self";
		break;

		case PREMO_PLUGIN_HASH:
			return "premo_plugin.sprx";
		break;

		case PREMO_GAME_PLUGIN_HASH:
			return "premo_game_plugin.sprx";
		break;
#endif // #ifdef DO_PATCH_COBRA810
		default:
			return "UNKNOWN";
		break;
	}

	return "UNKNOWN";
}
#endif //#ifdef DEBUG

#ifdef DO_PATCH

#ifdef DO_PATCH_COBRA810
static uint8_t condition_true = 1;
#endif

#ifdef DO_PATCH_PS2
uint8_t condition_ps2softemu = 0;

///////////////////
#ifdef ps2tonet_patch
static uint8_t condition_false = 0;
static uint64_t vsh_check = 0;
static int bc_to_net_status = 0;

static SprxPatch main_vsh_patches[] =
{
	{ ps2tonet_patch, ORI(R3, R3, 0x8204), &condition_ps2softemu },
	{ ps2tonet_size_patch, LI(R5, 0x40), &condition_ps2softemu },
	{ ps2tonet_patch, ORI(R3, R3, 0x8202), &condition_false },
	{ ps2tonet_size_patch, LI(R5, 0x4f0), &condition_false },
	//{ game_update_offset, LI(R3, -1), &condition_disable_gameupdate }, [DISABLED by DEFAULT since 4.46]
	//{ psp_newdrm_patch, LI(R3, 0), &condition_true }, // Fixes the issue (80029537) with PSP Pkg games
	{ 0 }
};
#endif

static SprxPatch game_ext_plugin_patches[] =
{
	{ ps2_nonbw_offset3, LI(R0, 1), &condition_ps2softemu },
#ifdef DO_PATCH_COBRA810
	{ sfo_check_offset, NOP, &condition_true },
	{ ps_region_error_offset, NOP, &condition_true }, // Needed sometimes...
	{ remote_play_offset, 0x419e0028, &condition_true },
	//{ ps_video_error_offset, LI(R3, 0), &condition_game_ext_psx },
	//{ ps_video_error_offset+4, BLR, &condition_game_ext_psx }, // experimental, disabled due to its issue with remote play
#endif
	{ 0 }
};

/*
static SprxPatch basic_plugins_patches[] =
{
	//{ ps1emu_type_check_offset, NOP, &condition_true }, // Loads ps1_netemu.self
	//{ ps1emu_type_check_offset, 0x409E000C, &condition_true }, // Loads original ps1_emu.self
	{ 0 }
};
*/
///////////////////

static SprxPatch explore_plugin_patches[] =
{
#ifdef DO_PATCH_COBRA810
 #ifdef app_home_offset
	{ app_home_offset,   0x2f646576, &condition_apphome },
	{ app_home_offset+4, 0x5f626476, &condition_apphome },
	{ app_home_offset+8, 0x642f5053, &condition_apphome },
 #endif
 #ifdef ps2_nonbw_offset
 	{ ps2_nonbw_offset, LI(0, 1), &condition_ps2softemu },
 #endif
 #ifdef whatsnew_offset
	//// Devil303's What's New ///
	{ whatsnew_offset,        0x68747470, &condition_true },
	{ whatsnew_offset + 0x04, 0x3A2F2F77, &condition_true },
	{ whatsnew_offset + 0x08, 0x77772E78, &condition_true },
	{ whatsnew_offset + 0x0C, 0x6D626D6F, &condition_true },
	{ whatsnew_offset + 0x10, 0x64732E63, &condition_true },
	{ whatsnew_offset + 0x14, 0x6F2F7768, &condition_true },
	{ whatsnew_offset + 0x18, 0x6174735F, &condition_true },
	{ whatsnew_offset + 0x1C, 0x6E65772E, &condition_true },
	{ whatsnew_offset + 0x20, 0x786D6C00, &condition_true },
	{ whatsnew_offset + 0x24, 0x00000000, &condition_true },
 #endif
#endif
	{ 0 }
};

static SprxPatch explore_category_game_patches[] =
{
	{ ps2_nonbw_offset2, LI(R0, 1), &condition_ps2softemu },
	{ 0 }
};

//REBUG REX
#ifdef EXPLORE_PLUGIN_REBUG_HASH
static SprxPatch rebug_explore_plugin_patches[] =
{
	#ifdef dex_ps2_nonbw_offset
	{ dex_ps2_nonbw_offset, LI(0, 1), &condition_ps2softemu },
	#else
	{ ps2_nonbw_offset, LI(0, 1), &condition_ps2softemu },
	#endif
	{ 0 }
};
#endif
#ifdef EXPLORE_CATEGORY_GAME_REBUG_HASH
static SprxPatch rebug_explore_category_game_patches[] =
{
	#ifdef dex_ps2_nonbw_offset2
	{ dex_ps2_nonbw_offset2, LI(R0, 1), &condition_ps2softemu },
	#else
	{ ps2_nonbw_offset2, LI(R0, 1), &condition_ps2softemu },
	#endif
	{ 0 }
};
#endif
#ifdef GAME_EXT_PLUGIN_REBUG_HASH
static SprxPatch rebug_game_ext_plugin_patches[] =
{
	#ifdef dex_ps2_nonbw_offset3
	{ dex_ps2_nonbw_offset3, LI(R0, 1), &condition_ps2softemu },
	#else
	{ ps2_nonbw_offset3, LI(R0, 1), &condition_ps2softemu },
	#endif
	{ 0 }
};
#endif
#endif //#ifdef DO_PATCH_PS2

#ifdef DO_PATCH_COBRA810
static SprxPatch bdp_disc_check_plugin_patches[] =
{
	{ dvd_video_region_check_offset, LI(R3, 1), &condition_true }, /* Kills standard dvd-video region protection (not RCE one) */
	{ 0 }
};

static SprxPatch ps1_emu_patches[] =
{
	{ ps1_emu_get_region_offset, LI(R29, 0x82), &condition_true }, /* regions 0x80-0x82 bypass region check. */
	{ 0 }
};

static SprxPatch ps1_netemu_patches[] =
{
	// Some rare titles such as Langrisser Final Edition are launched through ps1_netemu!
	{ ps1_netemu_get_region_offset, LI(R3, 0x82), &condition_true },
	{ 0 }
};

static SprxPatch nas_plugin_patches[] =
{
	{patch1_nas, NOP, &condition_true},
	{patch2_nas, NOP, &condition_true},
	{patch3_nas, 0x48000044, &condition_true},	// Install All Packages
	{0}
};

static SprxPatch bdp_bdmv_patches[] =
{
	{bdp_cinavia_patch,  0x4e800020, &condition_true},
	{bdp_cinavia1_patch, 0x4e800020, &condition_true},
	{0}
};

static SprxPatch bdp_bdvd_patches[] =
{
	{bdp_cinavia_patch,  0x4e800020, &condition_true},
	{bdp_cinavia1_patch, 0x4e800020, &condition_true},
	{0}
};

static SprxPatch download_plugin_patches[] =
{
	{elf_patch1_download,        0x409C017C, &condition_true},
	{elf_patch2_download,        0x48000010, &condition_true},
	// Devil303's extended download plugin patches
	{elf_patch3_download,        0x78000000, &condition_true},
	{elf_patch3_download + 0x9A, 0x78000000, &condition_true}, // allow XML files to be downloaded
	{elf_patch4_download,        0x78787800, &condition_true},
//	{elf_patch5_download,        0x00000000, &condition_true}, // patches /tmp & /downloader
//	{elf_patch5_download + 8,    0x00000000, &condition_true}, //
//	{elf_patch5_download + 0x0C, 0x00000000, &condition_true}, //
//	{elf_patch5_download + 0x10, 0x00000000, &condition_true}, //
	{elf_patch6_download,        0x6F637465, &condition_true},
	{elf_patch6_download + 0x04, 0x742D7374, &condition_true},
	{elf_patch6_download + 0x08, 0x7265616D, &condition_true},
	{elf_patch6_download + 0x48, 0x6F637465, &condition_true},
	{elf_patch6_download + 0x4C, 0x742D7374, &condition_true},
	{elf_patch6_download + 0x50, 0x7265616D, &condition_true},
	{0}
};

static SprxPatch autodownload_plugin_patches[] =
{
	{elf_patch1_autodownload,0x409C017C , &condition_true},
	{elf_patch2_autodownload,0x48000010 , &condition_true},
	{0}
};

static SprxPatch premo_plugin_patches[] =
{
	{pcremote_play_offset1,0x38000001 , &condition_true},
	{0}
};

static SprxPatch premo_game_plugin_patches[] =
{
	{pcremote_play_offset2,0x38000001 , &condition_true},
	{0}
};
#endif //#ifdef DO_PATCH_COBRA810
#ifdef EXT_AUDIO
	static SprxPatch libaudio_patches[] =
{
	{ bt_usb_audio_offset,        0x38000001, &condition_true },
	{ bt_usb_audio_offset + 4,    0xF81E0010, &condition_true },
	{ bt_usb_audio_offset + 8,    0xE8030000, &condition_true },
	{ bt_usb_audio_offset + 0x0C, 0x2FA00000, &condition_true },
	{ bt_usb_audio_offset + 0x10, 0x419E0028, &condition_true },
	{ 0 }
};
#endif // EXT_AUDIO

#ifdef DO_PATCH_PSP
uint8_t condition_psp_iso = 0;
uint8_t condition_psp_dec = 0;
uint8_t condition_psp_keys = 0;
//uint8_t condition_psp_change_emu = 0;   // sys_psp_set_emu_path has been deleted (BASIC_PLUGINS patch not needed)
uint8_t condition_psp_prometheus = 0;

static SprxPatch psp_emulator_patches[] =
{
	// Sets psp mode as opossed to minis mode. Increases compatibility, removes text protection and makes most savedata work
	{ psp_set_psp_mode_offset, LI(R4, 0), &condition_psp_iso },
	{ 0 }
};

static SprxPatch emulator_api_patches[] =
{
	// Read umd patches
	{ psp_read,      STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_read + 0x04, MFLR(R0), &condition_psp_iso },
	{ psp_read + 0x08, STD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_read + 0x0C, MR(R8, R7), &condition_psp_iso },
	{ psp_read + 0x10, MR(R7, R6), &condition_psp_iso },
	{ psp_read + 0x14, MR(R6, R5), &condition_psp_iso },
	{ psp_read + 0x18, MR(R5, R4), &condition_psp_iso },
	{ psp_read + 0x1C, MR(R4, R3), &condition_psp_iso },
	{ psp_read + 0x20, LI(R3, SYSCALL8_OPCODE_READ_PSP_UMD), &condition_psp_iso },
	{ psp_read + 0x24, LI(R11, 8), &condition_psp_iso },
	{ psp_read + 0x28, SC, &condition_psp_iso },
	{ psp_read + 0x2C, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_read + 0x30, MTLR(R0), &condition_psp_iso },
	{ psp_read + 0x34, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_read + 0x38, BLR, &condition_psp_iso },
	// Read header patches
	{ psp_read + 0x3C, STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_read + 0x40, MFLR(R0), &condition_psp_iso },
	{ psp_read + 0x44, STD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_read + 0x48, MR(R7, R6), &condition_psp_iso },
	{ psp_read + 0x4C, MR(R6, R5), &condition_psp_iso },
	{ psp_read + 0x50, MR(R5, R4), &condition_psp_iso },
	{ psp_read + 0x54, MR(R4, R3), &condition_psp_iso },
	{ psp_read + 0x58, LI(R3, SYSCALL8_OPCODE_READ_PSP_HEADER), &condition_psp_iso },
	{ psp_read + 0x5C, LI(R11, 8), &condition_psp_iso },
	{ psp_read + 0x60, SC, &condition_psp_iso },
	{ psp_read + 0x64, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_read + 0x68, MTLR(R0), &condition_psp_iso },
	{ psp_read + 0x6C, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_read + 0x70, BLR, &condition_psp_iso },
	{ psp_read_header, MAKE_CALL_VALUE(psp_read_header, psp_read + 0x3C), &condition_psp_iso },
	// Drm patches
	{ psp_drm_patch5,  MAKE_JUMP_VALUE(psp_drm_patch5, psp_drm_patch6), &condition_psp_iso },
	{ psp_drm_patch7,  LI(R6, 0), &condition_psp_iso },
	{ psp_drm_patch8,  LI(R7, 0), &condition_psp_iso },
	{ psp_drm_patch9,  NOP, &condition_psp_iso },
	{ psp_drm_patch11, LI(R6, 0), &condition_psp_iso },
	{ psp_drm_patch12, LI(R7, 0), &condition_psp_iso },
	// product id
	{ psp_product_id_patch1, NOP, &condition_psp_iso },
	{ psp_product_id_patch3, NOP, &condition_psp_iso },
	{ 0 }
};

static SprxPatch pemucorelib_patches[] =
{
	{ psp_eboot_dec_patch, LI(R6, 0x110), &condition_psp_dec }, // -> makes unsigned psp eboot.bin run, 0x10 works too
	{ psp_prx_patch, STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_prx_patch+4, MFLR(R6), &condition_psp_iso },
	{ psp_prx_patch+8, STD(R6, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch + 0x0C, LI(R11, 8), &condition_psp_iso },
	{ psp_prx_patch + 0x10, MR(R5, R4), &condition_psp_iso },
	{ psp_prx_patch + 0x14, MR(R4, R3), &condition_psp_iso },
	{ psp_prx_patch + 0x18, LI(R3, SYSCALL8_OPCODE_PSP_PRX_PATCH), &condition_psp_iso },
	{ psp_prx_patch + 0x1C, SC, &condition_psp_iso },
	{ psp_prx_patch + 0x20, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch + 0x24, MTLR(R0), &condition_psp_iso },
	{ psp_prx_patch + 0x28, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_prx_patch + 0x2C, BLR, &condition_psp_iso },
	// Patch for savedata binding
	{ psp_savedata_bind_patch1, MR(R5, R19), &condition_psp_iso },
	{ psp_savedata_bind_patch2, MAKE_JUMP_VALUE(psp_savedata_bind_patch2, psp_prx_patch + 0x30), &condition_psp_iso },
	{ psp_prx_patch + 0x30, LD(R19, 0xFF98, SP), &condition_psp_iso },
	{ psp_prx_patch + 0x34, STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_prx_patch + 0x38, MFLR(R0), &condition_psp_iso },
	{ psp_prx_patch + 0x3C, STD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch + 0x40, LI(R11, 8), &condition_psp_iso },
	{ psp_prx_patch + 0x44, MR(R4, R3), &condition_psp_iso },
	{ psp_prx_patch + 0x48, LI(R3, SYSCALL8_OPCODE_PSP_POST_SAVEDATA_INITSTART), &condition_psp_iso },
	{ psp_prx_patch + 0x4C, SC, &condition_psp_iso },
	{ psp_prx_patch + 0x50, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch + 0x54, MTLR(R0), &condition_psp_iso },
	{ psp_prx_patch + 0x58, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_prx_patch + 0x5C, BLR, &condition_psp_iso },
	{ psp_savedata_bind_patch3, MAKE_JUMP_VALUE(psp_savedata_bind_patch3, psp_prx_patch + 0x60), &condition_psp_iso },
	{ psp_prx_patch + 0x60, STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_prx_patch + 0x64, MFLR(R0), &condition_psp_iso },
	{ psp_prx_patch + 0x68, STD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch + 0x6C, LI(R11, 8), &condition_psp_iso },
	{ psp_prx_patch + 0x70, LI(R3, SYSCALL8_OPCODE_PSP_POST_SAVEDATA_SHUTDOWNSTART), &condition_psp_iso },
	{ psp_prx_patch + 0x74, SC, &condition_psp_iso },
	{ psp_prx_patch + 0x78, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch + 0x7C, MTLR(R0), &condition_psp_iso },
	{ psp_prx_patch + 0x80, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_prx_patch + 0x84, BLR, &condition_psp_iso },
	// Prometheus
	{ psp_prometheus_patch, '.OLD', &condition_psp_prometheus },

#ifdef psp_extra_savedata_patch
	// Extra save data patch required since some 3.60+ firmware
	//{ psp_extra_savedata_patch, LI(R31, 1), &condition_psp_iso },
#endif

	{ 0 }
};

static SprxPatch libsysutil_savedata_psp_patches[] =
{
	{ psp_savedata_patch1, MAKE_JUMP_VALUE(psp_savedata_patch1, psp_savedata_patch2), &condition_psp_iso },
	{ psp_savedata_patch3, NOP, &condition_psp_iso },
	{ psp_savedata_patch4, NOP, &condition_psp_iso },
	{ psp_savedata_patch5, NOP, &condition_psp_iso },
	{ psp_savedata_patch6, NOP, &condition_psp_iso },
	{ 0 }
};
#endif //#ifdef DO_PATCH_PSP

uint8_t condition_apphome = 0; //JB format game

static SprxPatch libfs_external_patches[] =
{
	// Redirect internal libfs function to kernel. If condition_apphome is 1, it means there is a JB game mounted
	{ aio_copy_root_offset,        STDU(SP, 0xFF90, SP), &condition_apphome },
	{ aio_copy_root_offset + 0x04, MFLR(R0), &condition_apphome },
	{ aio_copy_root_offset + 0x08, STD(R0, 0x80, SP), &condition_apphome },
	{ aio_copy_root_offset + 0x0C, MR(R5, R4), &condition_apphome },
	{ aio_copy_root_offset + 0x10, MR(R4, R3), &condition_apphome },
	{ aio_copy_root_offset + 0x14, LI(R3, SYSCALL8_OPCODE_AIO_COPY_ROOT), &condition_apphome },
	{ aio_copy_root_offset + 0x18, LI(R11, 8), &condition_apphome },
	{ aio_copy_root_offset + 0x1C, SC, &condition_apphome },
	{ aio_copy_root_offset + 0x20, LD(R0, 0x80, SP), &condition_apphome },
	{ aio_copy_root_offset + 0x24, MTLR(R0), &condition_apphome },
	{ aio_copy_root_offset + 0x28, ADDI(SP, SP, 0x70), &condition_apphome },
	{ aio_copy_root_offset + 0x2C, BLR, &condition_apphome },
	{ 0 }
};

#define N_PATCH_TABLE_ENTRIES	(sizeof(patch_table) / sizeof(PatchTableEntry))

static PatchTableEntry patch_table[] =
{
	{ LIBFS_EXTERNAL_HASH, libfs_external_patches },
#ifdef DO_PATCH_PSP
	{ PSP_EMULATOR_HASH, psp_emulator_patches },
	{ EMULATOR_API_HASH, emulator_api_patches },
	{ PEMUCORELIB_HASH, pemucorelib_patches },
	{ LIBSYSUTIL_SAVEDATA_PSP_HASH, libsysutil_savedata_psp_patches },
#endif
#ifdef DO_PATCH_PS2
#ifdef ps2tonet_patch
	{ VSH_HASH, main_vsh_patches },
#endif
	{ EXPLORE_PLUGIN_HASH, explore_plugin_patches },
	{ EXPLORE_CATEGORY_GAME_HASH, explore_category_game_patches },
	{ GAME_EXT_PLUGIN_HASH, game_ext_plugin_patches },
#endif
#ifdef EXT_AUDIO
	{ LIBAUDIO_HASH, libaudio_patches },
#endif
#ifdef DO_PATCH_COBRA810
	{ BDP_DISC_CHECK_PLUGIN_HASH, bdp_disc_check_plugin_patches },
	{ PS1_EMU_HASH, ps1_emu_patches },
	{ PS1_NETEMU_HASH, ps1_netemu_patches },
	{ LIBFS_EXTERNAL_HASH, libfs_external_patches },
	{ NAS_PLUGIN_HASH, nas_plugin_patches },
	{ BDP_BDMV_HASH, bdp_bdmv_patches },
	{ BDP_BDVD_HASH, bdp_bdvd_patches },
	{ DOWNLOAD_PLUGIN_HASH, download_plugin_patches },
	{ AUTODOWNLOAD_PLUGIN_HASH, autodownload_plugin_patches },
	{ PREMO_PLUGIN_HASH, premo_plugin_patches },
	{ PREMO_GAME_PLUGIN_HASH, premo_game_plugin_patches },
#endif
};

static PatchTableEntry patch_table_rebug[] =
{
	{ LIBFS_EXTERNAL_HASH, libfs_external_patches },
#ifdef DO_PATCH_PSP
	{ PSP_EMULATOR_HASH, psp_emulator_patches },
	{ EMULATOR_API_HASH, emulator_api_patches },
	{ PEMUCORELIB_HASH, pemucorelib_patches },
	{ LIBSYSUTIL_SAVEDATA_PSP_HASH, libsysutil_savedata_psp_patches },
#endif
#ifdef DO_PATCH_PS2
#ifdef EXPLORE_PLUGIN_REBUG_HASH
	{ EXPLORE_PLUGIN_REBUG_HASH, rebug_explore_plugin_patches },
#else
	{ EXPLORE_PLUGIN_HASH, explore_plugin_patches },
#endif
#ifdef EXPLORE_CATEGORY_GAME_REBUG_HASH
	{ EXPLORE_CATEGORY_GAME_REBUG_HASH, rebug_explore_category_game_patches },
#else
	{ EXPLORE_CATEGORY_GAME_HASH, explore_category_game_patches },
#endif
#ifdef GAME_EXT_PLUGIN_REBUG_HASH
	{ GAME_EXT_PLUGIN_REBUG_HASH, rebug_game_ext_plugin_patches },
#else
	{ GAME_EXT_PLUGIN_HASH, game_ext_plugin_patches },
#endif
#endif
#ifdef DO_PATCH_COBRA810
	{ BDP_DISC_CHECK_PLUGIN_HASH, bdp_disc_check_plugin_patches },
	{ PS1_EMU_HASH, ps1_emu_patches },
	{ PS1_NETEMU_HASH, ps1_netemu_patches },
	{ NAS_PLUGIN_HASH, nas_plugin_patches },
	{ BDP_BDMV_HASH, bdp_bdmv_patches },
	{ BDP_BDVD_HASH, bdp_bdvd_patches },
	{ DOWNLOAD_PLUGIN_HASH, download_plugin_patches },
	{ AUTODOWNLOAD_PLUGIN_HASH, autodownload_plugin_patches },
	{ PREMO_PLUGIN_HASH, premo_plugin_patches },
	{ PREMO_GAME_PLUGIN_HASH, premo_game_plugin_patches },
#endif
};

#endif //#ifdef DO_PATCH

void clear_key(void *key);

LV2_PATCHED_FUNCTION(int, modules_patching, (uint64_t *arg1, uint32_t *arg2))
{
	static unsigned int total = 0;
	static uint32_t *buf;
	static uint8_t keys[16];
	static uint64_t nonce = 0;

	SELF *self;
	uint64_t *ptr;
	uint32_t *ptr32;
	uint8_t *sce_hdr;

	ptr = (uint64_t *)(*(uint64_t *)MKA(TOC+decrypt_rtoc_entry_2));
	ptr = (uint64_t *)ptr[0x68/8];
	ptr = (uint64_t *)ptr[0x18/8];
	ptr32 = (uint32_t *)ptr;
	sce_hdr = (uint8_t *)saved_sce_hdr;
	self = (SELF *)sce_hdr;

	uint32_t *p = (uint32_t *)arg1[0x18/8];

	#ifdef DEBUG
	DPRINTF("Flags = %x      %x\n", self->flags, (p[0x30/4] >> 16));
	#endif

	// +4.30 -> 0x13 (exact firmware since it happens is unknown)
	// 3.55 -> 0x29
#if defined(FIRMWARE_3_55) || defined(FIRMWARE_3_41)
	if ((p[0x30/4] >> 16) == 0x29)
#else
	if ((p[0x30/4] >> 16) == 0x13)
#endif
	{
		#ifdef DEBUG
		DPRINTF("We are in decrypted module or in cobra encrypted\n");
		#endif

		int last_chunk = 0;
		KeySet *keySet = NULL;

		if (((ptr[0x10/8] << 24) >> 56) == 0xFF)
		{
			ptr[0x10/8] |= 2;
			*arg2 = 0x2C;
			last_chunk = 1;
		}
		else
		{
			ptr[0x10/8] |= 3;
			*arg2 = 6;
		}

		uint8_t *enc_buf = (uint8_t *)ptr[8/8];
		uint32_t chunk_size = ptr32[4/4];
		SPRX_EXT_HEADER *extHdr = (SPRX_EXT_HEADER *)(sce_hdr+self->metadata_offset+0x20);
		uint64_t magic = extHdr->magic&SPRX_EXT_MAGIC_MASK;
		uint8_t keyIndex = extHdr->magic&0xFF;

		if (magic == SPRX_EXT_MAGIC)
		{
			if (keyIndex >= N_SPRX_KEYS_1)
			{
				#ifdef DEBUG
				DPRINTF("This key is not implemented yet: %lx:%x\n", magic, keyIndex);
				#endif
			}
			else
			{
				keySet = &sprx_keys_set1[keyIndex];
			}

		}
		else if (magic == SPRX_EXT_MAGIC2)
		{
			if (keyIndex >= N_SPRX_KEYS_2)
			{
				#ifdef DEBUG
				DPRINTF("This key is not implemented yet: %lx:%x\n", magic, keyIndex);
				#endif
			}
			else
			{
				keySet = &sprx_keys_set2[keyIndex];
			}
		}

		if (keySet)
		{
			if (total == 0)
			{
				uint8_t dif_keys[0x10];

				clear_key(dif_keys);

				memcpy(keys, extHdr->keys_mod, 0x10);

				for (int i = 0; i < 16; i++)
				{
					keys[i] ^= (keySet->keys[15-i] ^ dif_keys[15-i]);
				}

				nonce = keySet->nonce ^ extHdr->nonce_mod;
			}

			uint32_t num_blocks = chunk_size / 8;

			xtea_ctr(keys, nonce, enc_buf, num_blocks * 8);
			nonce += num_blocks;

			if (last_chunk)
			{
				get_pseudo_random_number(keys, sizeof(keys));
				nonce = 0;
			}
		}

		memcpy(saved_buf, (void *)ptr[8/8], ptr32[4/4]);

		if (total == 0)
		{
			buf = (uint32_t *)saved_buf;
		}

		#ifdef DEBUG
		if (last_chunk)
		{
				DPRINTF("Total section size: %x\n", total+ptr32[4/4]);
		}
		#endif

		saved_buf += ptr32[4/4];
	}
	else
	{
		decrypt_func(arg1, arg2);
		buf = (uint32_t *)saved_buf;
	}

	total += ptr32[4/4];

	if (((ptr[0x10/8] << 24) >> 56) == 0xFF)
	{
		uint64_t hash = 0, hash2 = 0;

		for (int i = 0; i < 0x100; i++)
		{
			hash ^= buf[i];
		}

		hash = (hash << 32) | total;

		///////////////////
		for(int i = 0; i < 0x8; i++)  //0x20 bytes only
			hash2 ^= buf[i+0xb0];  //unique location in all files+static hashes between firmware

		if((total & 0xff0000)==0)
			total = (total & 0xfff000); //if size is less than 0x10000 then check for next 4 bits
		else
			total = (total & 0xff0000); //copy third byte

		hash2 = ((hash2 << 32) & 0xfffff00000000000) | (total);  //20 bits check, prevent diferent hash just because of minor changes
		///////////////////

		total = 0;
		#ifdef DEBUG
		DPRINTF("hash = %lx\n", hash);
		#endif

		#ifdef DO_PATCH
		uint64_t trunc_hash = (hash >> 16), plugin_trunc_hash = 0;
		//uint64_t pspemu_off = pspemu_path_offset, psptrans_off = psptrans_path_offset;

		#ifdef ps2tonet_patch
		if(trunc_hash == (VSH_HASH >> 16))
		{
			vsh_check = VSH_HASH;
		}
		#endif
		#ifdef DO_PATCH_PSP
		if(trunc_hash == (EMULATOR_DRM_HASH >> 16))
		{
			if (condition_psp_keys)
				buf[psp_drm_tag_overwrite/4] = LI(R5, psp_code);
		}
		else if(trunc_hash == (EMULATOR_DRM_DATA_HASH >> 16))
		{
			if (condition_psp_keys)
			{
				buf[psp_drm_key_overwrite/4] = psp_tag;
				memcpy(buf + ((psp_drm_key_overwrite + 8)/4), psp_keys, 16);
			}
		}
/*
		else if(trunc_hash == (PEMUCORELIB_HASH >> 16))
		{
			if (condition_pemucorelib)
			{

				if (pad_get_data(&data) >= ((PAD_BTN_OFFSET_DIGITAL+1)*2)){

					if((data.button[PAD_BTN_OFFSET_DIGITAL] & (PAD_CTRL_CROSS|PAD_CTRL_R1)) == (PAD_CTRL_CROSS|PAD_CTRL_R1))
					{
						DPRINTF("Button Shortcut detected! Applying pemucorelib Extra Savedata Patch...\n");
						DPRINTF("Now patching %s %lx\n", hash_to_name(hash), hash);

						uint32_t data = LI(R31, 1);
						buf[psp_extra_savedata_patch/4] = data;

						DPRINTF("Offset: 0x%08X | Data: 0x%08X\n", psp_extra_savedata_patch, data);
					}
				}
			}
		}
*/
/*
		else if(trunc_hash == (BASIC_PLUGINS_HASH >> 16)
		#ifdef BASIC_PLUGINS_REBUG_HASH
		|| trunc_hash == (BASIC_PLUGINS_REBUG_HASH >> 16)
		#endif
		)
		{
			if(condition_psp_change_emu)
			{
				//rebug rex
				if(vsh_type != 0x666)
				{
					#ifdef dex_pspemu_path_offset
					pspemu_off = dex_pspemu_path_offset;
					psptrans_off = dex_psptrans_path_offset;
					//weird rebug 4.30 drex with basic_plugins CEX
					#elif cex_pspemu_path_offset
					pspemu_off = cex_pspemu_path_offset;
					psptrans_off = cex_psptrans_path_offset;
					#endif
				}
				#ifdef DEBUG
				DPRINTF("pspemu_path_offset: 0x%lx\npsptrans_path_offset: 0x%lx\n", pspemu_off, psptrans_off);
				#endif

				memcpy(((char *)buf)+pspemu_off, pspemu_path, sizeof(pspemu_path));
				memcpy(((char *)buf)+psptrans_off, psptrans_path, sizeof(psptrans_path));
			}
		}
*/
		#endif

		if(vsh_type != 0x666)
			memcpy(patch_table, patch_table_rebug, sizeof(patch_table));


		for (int i = 0; i < N_PATCH_TABLE_ENTRIES; i++)
		{
			plugin_trunc_hash = (patch_table[i].hash >> 16);

			if (plugin_trunc_hash == trunc_hash || patch_table[i].hash == hash2)
			{
				#ifdef DEBUG
				DPRINTF("Now patching %s %lx (%lx)\n", hash_to_name(trunc_hash, hash2), hash, hash2);
				#endif

				int j = 0;
				SprxPatch *patch = &patch_table[i].patch_table[j];

				while (patch->offset)
				{
					if (*patch->condition)
					{
						buf[patch->offset/4] = patch->data;
						#ifdef DEBUG
						DPRINTF("Offset: 0x%08X | Data: 0x%08X\n", (uint32_t)patch->offset, (uint32_t)patch->data);
						#endif
					}

					j++;
					patch = &patch_table[i].patch_table[j];
				}
				break;
			}
		}
	}
		#endif

	return 0;
}

//----------------------------------------
//PROCESS
//----------------------------------------

process_t vsh_process;

process_t get_vsh_process(void) //NzV
{
	uint64_t *proc_list = *(uint64_t **)MKA(TOC + process_rtoc_entry_1);
	proc_list = *(uint64_t **)proc_list;
	proc_list = *(uint64_t **)proc_list;
	for (int i = 0; i < 16; i++)
	{
		process_t process = (process_t)proc_list[1];
		proc_list += 2;
		if ((((uint64_t)process) & 0xFFFFFFFF00000000ULL) != MKA(0)) continue;
		if (is_vsh_process(process)) return process;
	}
	return NULL;
}

LV2_HOOKED_FUNCTION_PRECALL_SUCCESS_8(int, load_process_hooked, (process_t process, int fd, char *path, int r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t sp_70))
{
	#ifdef DEBUG
	DPRINTF("PROCESS %s (%08X) loaded\n", path, process->pid);
	#endif

	// CFW2OFW fix by Evilnat
	// Restores disc in BD drive, this fixes leftovers of previous game mounted
	#ifdef DO_CFW2OFW_FIX
	if (CFW2OFW_game && !strcmp(path, "/dev_flash/vsh/module/mcore.self"))
	{
		#ifdef DEBUG
			DPRINTF("Resetting BD Drive after CFW2OFW game...\n");
		#endif

		restore_BD();
		CFW2OFW_game =  0;
	}
	#endif

	//Get VSH process
	if (!vsh_process)
	{
		if(is_vsh_process(process->parent)) vsh_process = process->parent;
		else if (is_vsh_process(process)) vsh_process = process;
		else vsh_process = get_vsh_process();

		if ((vsh_process) && (storage_ext_patches_done == 0))
		{
			storage_ext_patches_done = 1;
			storage_ext_patches();
		}
	}
	#ifndef DO_CEX2OFW_FIX
	if (vsh_process)
		unhook_function_on_precall_success(load_process_symbol, load_process_hooked, 9);
	#endif

	return 0;
}

#ifdef ps2tonet_patch
int bc_to_net(int param)
{
	//returns:
	//0=disabled
	//1=enabled
	//-1=its not a bc/semi-bc console

	if(condition_ps2softemu)
		return -1;

	if (!vsh_process) {vsh_process = get_vsh_process(); //NzV
	if (!vsh_process) return ESRCH;}

	if(param == 1) //enable netemu
	{
		switch(vsh_check)
		{
			case VSH_HASH:
			copy_to_process(vsh_process, &main_vsh_patches[0].data, (void *)(uint64_t)(0x10000 + main_vsh_patches[0].offset), 4);
			copy_to_process(vsh_process, &main_vsh_patches[1].data, (void *)(uint64_t)(0x10000 + main_vsh_patches[1].offset), 4);
			break;
		}

		bc_to_net_status = 1;
		return 1;
	}

	if(param == 0) //restore
	{
		switch(vsh_check)
		{
			case VSH_HASH:
			copy_to_process(vsh_process, &main_vsh_patches[2].data, (void *)(uint64_t)(0x10000 + main_vsh_patches[2].offset), 4);
			copy_to_process(vsh_process, &main_vsh_patches[3].data, (void *)(uint64_t)(0x10000 + main_vsh_patches[3].offset), 4);
			break;
		}

		bc_to_net_status = 0;
		return 0;
	}

	if(param == 2)
		return bc_to_net_status;

	return -2;
}
#endif

#ifdef PS3M_API
void pre_map_process_memory(void *object, uint64_t process_addr, uint64_t size, uint64_t flags, void *unk, void *elf, uint64_t *out);

LV2_HOOKED_FUNCTION_POSTCALL_7(void, pre_map_process_memory, (void *object, uint64_t process_addr, uint64_t size, uint64_t flags, void *unk, void *elf, uint64_t *out))
{
	#ifdef DEBUG
	DPRINTF("Map %lx %lx %s %lx\n", process_addr, size, get_current_process() ? get_process_name(get_current_process())+8 : "KERNEL", flags);
	#endif
	// Not the call address, but the call to the caller (process load code for .self)
	if (get_call_address(1) == (void *)MKA(process_map_caller_call))
	{
		if (flags != 0x2004004) set_patched_func_param(4, 0x2004004); // Change flags to RWX, make all process memory writable.
		//if (flags == 0x2008004) set_patched_func_param(4, 0x2004004); // Change flags, RX -> RWX, make all process memory writable.
	}
}
#endif


#ifdef DEBUG
LV2_HOOKED_FUNCTION_PRECALL_SUCCESS_8(int, create_process_common_hooked, (process_t parent, uint32_t *pid, int fd, char *path, int r7, uint64_t r8,
									  uint64_t r9, void *argp, uint64_t args, void *argp_user, uint64_t sp_80,
									 void **sp_88, uint64_t *sp_90, process_t *process, uint64_t *sp_A0,
									  uint64_t *sp_A8))
{
	char *parent_name = get_process_name(parent);
	DPRINTF("PROCESS %s (%s) (%08X) created from parent process: %s\n", path, get_process_name(*process), *pid, ((int64_t)parent_name < 0) ? parent_name : "");

	return 0;
}

LV2_HOOKED_FUNCTION_POSTCALL_8(void, create_process_common_hooked_pre, (process_t parent, uint32_t *pid, int fd, char *path, int r7, uint64_t r8,
									  uint64_t r9, void *argp, uint64_t args, void *argp_user, uint64_t sp_80,
									 void **sp_88, uint64_t *sp_90, process_t *process, uint64_t *sp_A0,
									  uint64_t *sp_A8))
{

	DPRINTF("Pre-process\n");
}

#endif


//----------------------------------------
//VSH PLUGINS
//----------------------------------------
#define BOOT_PLUGINS_FILE1			"/dev_usb000/mamba_plugins.txt"
#define BOOT_PLUGINS_FILE2			"/dev_usb001/mamba_plugins.txt"
#define BOOT_PLUGINS_FILE3			"/dev_hdd0/mamba_plugins.txt"

#define BOOT_PLUGINS_KERNEL_FILE1	"/dev_usb000/mamba_plugins_kernel.txt"
#define BOOT_PLUGINS_KERNEL_FILE2	"/dev_usb001/mamba_plugins_kernel.txt"
#define BOOT_PLUGINS_KERNEL_FILE3	"/dev_hdd0/mamba_plugins_kernel.txt"

#define BOOT_PLUGINS_FIRST_SLOT		1
#define MAX_BOOT_PLUGINS			(MAX_VSH_PLUGINS-BOOT_PLUGINS_FIRST_SLOT)
#define MAX_BOOT_PLUGINS_KERNEL		5

#define MAX_VSH_PLUGINS				7

static sys_prx_id_t vsh_plugins[MAX_VSH_PLUGINS];
static int loading_vsh_plugin = 0;

// Kernel version of prx_load_vsh_plugin
int prx_load_vsh_plugin(unsigned int slot, char *path, void *arg, uint32_t arg_size)
{
	void *kbuf, *vbuf;
	sys_prx_id_t prx;
	int ret;
	if (!vsh_process) {vsh_process = get_vsh_process(); //NzV
	if (!vsh_process) return ESRCH;}

	if (slot >= MAX_VSH_PLUGINS || (arg != NULL && arg_size > KB(64)))
		return EINVAL;

	if (vsh_plugins[slot])
		return EKRESOURCE;

	CellFsStat stat;
	if ((cellFsStat(path, &stat) != CELL_OK) || (stat.st_size < 0x230)) return EINVAL; // prevent a semi-brick (black screen on start up) if the sprx is 0 bytes (due a bad ftp transfer).

	uint8_t sprx_check[0x20];
	if(read_file(path, sprx_check, 0x20))
	{
		uint64_t header_len = *(uint64_t *)(sprx_check + 0x10);
		uint64_t data_len   = *(uint64_t *)(sprx_check + 0x18);

		if(stat.st_size < (header_len + data_len))
		{
			return EINVAL;
		}
	}
	else
	{
		return EINVAL;
	}

	loading_vsh_plugin = 1;
	prx = prx_load_module(vsh_process, 0, 0, path);
	loading_vsh_plugin  = 0;

	if (prx < 0)
		return prx;

	if (arg && arg_size > 0)
	{
		page_allocate_auto(vsh_process, KB(64), &kbuf);
		page_export_to_proc(vsh_process, kbuf, 0x40000, &vbuf);
		memcpy(kbuf, arg, arg_size);
	}
	else
		vbuf = NULL;

	ret = prx_start_module_with_thread(prx, vsh_process, 0, (uint64_t)vbuf);

	if (vbuf)
	{
		page_unexport_from_proc(vsh_process, vbuf);
		free_page(vsh_process, kbuf);
	}

	if (ret == SUCCEEDED)
		vsh_plugins[slot] = prx;
	else
	{
		prx_stop_module_with_thread(prx, vsh_process, 0, 0);
		prx_unload_module(prx, vsh_process);
	}

	#ifdef DEBUG
	DPRINTF("Vsh plugin load: %x\n", ret);
	#endif

	return ret;
}

// User version of prx_load_vsh_plugin
int sys_prx_load_vsh_plugin(unsigned int slot, char *path, void *arg, uint32_t arg_size)
{
	if (slot >= MAX_VSH_PLUGINS) for(slot = BOOT_PLUGINS_FIRST_SLOT; slot < MAX_VSH_PLUGINS; slot++) if(!vsh_plugins[slot]) break;

	return prx_load_vsh_plugin(slot, get_secure_user_ptr(path), get_secure_user_ptr(arg), arg_size);
}

// Kernel version of prx_unload_vsh_plugin
int prx_unload_vsh_plugin(unsigned int slot)
{
	int ret;
	sys_prx_id_t prx;

	#ifdef DEBUG
	DPRINTF("Trying to unload vsh plugin %x\n", slot);
	#endif

	if (slot >= MAX_VSH_PLUGINS)
		return EINVAL;

	prx = vsh_plugins[slot];
	#ifdef DEBUG
	DPRINTF("Current plugin: %08X\n", prx);
	#endif

	if (prx == 0)
		return ENOENT;

	if (!vsh_process) {vsh_process = get_vsh_process(); //NzV
	if (!vsh_process) return ESRCH;}
	ret = prx_stop_module_with_thread(prx, vsh_process, 0, 0);
	if (ret == SUCCEEDED)
		ret = prx_unload_module(prx, vsh_process);
	#ifdef DEBUG
	else DPRINTF("Stop failed: %x!\n", ret);
	#endif
	if (ret == SUCCEEDED)
	{
		vsh_plugins[slot] = 0;
		#ifdef DEBUG
		DPRINTF("Vsh plugin unloaded succesfully!\n");
		#endif
	}
	#ifdef DEBUG
	else DPRINTF("Unload failed : %x!\n", ret);
	#endif

	return ret;
}

// User version of prx_unload_vsh_plugin. Implementation is same.
int sys_prx_unload_vsh_plugin(unsigned int slot)
{
	return prx_unload_vsh_plugin(slot);
}

// static int was removed to support cfg implementation for homebrew blocker by KW & AV
int read_text_line(int fd, char *line, unsigned int size, int *eof)
{
	if (size == 0)
		return FAILED;
	size--;

	*eof = 0;

	int i = 0;
	int line_started = 0;

	while (i < size)
	{
		uint8_t ch;
		uint64_t r;

		if ((cellFsRead(fd, &ch, 1, &r) != CELL_FS_SUCCEEDED) || (r != 1))
		{
			*eof = 1;
			break;
		}

		if (!line_started)
		{
			if (ch > ' ')
			{
				line[i++] = (char)ch;
				line_started = 1;
			}
		}
		else
		{
			if (ch == '\n' || ch == '\r')
				break;

			line[i++] = (char)ch;
		}
	}

	line[i] = 0;

	// Remove space chars at end
	for (int j = i - 1; j >= 0; j--)
	{
		if (line[j] <= ' ')
		{
			line[j] = 0;
			i = j;
		}
		else
			break;
	}

	return i;
}

static int load_plugin_kernel(char *path)
{
	if (!vsh_process) {vsh_process = get_vsh_process(); //NzV
	if (vsh_process <= 0) return ESRCH;}

	CellFsStat stat;
	if(cellFsStat(path, &stat) == CELL_FS_SUCCEEDED)
	{
		if(stat.st_size & 0x7) return EINVAL; // check payload is aligned to 8 / 16

		if(stat.st_size > 0x230)
		{
			void *skprx = malloc(stat.st_size);

			if(skprx)
			{
				if(read_file(path, skprx, stat.st_size))
				{
					f_desc_t f;
					f.addr = skprx;
					f.toc = (void *)MKA(TOC);

					int (* func)(void);
					func = (void *)&f;
					func();

					return 1;
				}
				else
				{
					free(skprx);
				}
			}
		}
	}
	return 0;
}

static void locate_file(char *path, const char *file)
{
	CellFsStat stat;
	sprintf(path, "/dev_usb000/%s", file);
	if (cellFsStat(path, &stat) /* != CELL_FS_SUCCEEDED */) path[10] = '1';
	if (cellFsStat(path, &stat) /* != CELL_FS_SUCCEEDED */) sprintf(path, "/dev_hdd0/%s", file);
}

void load_boot_plugins_kernel(void)
{
	if (!vsh_process) {vsh_process = get_vsh_process(); //NzV
	if (vsh_process <= 0) return;} // lets wait till vsh so we dont brick the console perma!

	char *path = kalloc(MAX_FILE_LEN);

	if(path)
	{
		locate_file(path, "mamba_plugins_kernel.txt");

		int fd;
		if (cellFsOpen(path, CELL_FS_O_RDONLY, &fd, 0, NULL, 0) == CELL_FS_SUCCEEDED)
		{
			int num_loaded_kernel = 0;

			while (num_loaded_kernel < MAX_BOOT_PLUGINS_KERNEL)
			{
				int eof;

				if (read_text_line(fd, path, MAX_FILE_LEN, &eof) > 0)
				{
					if (load_plugin_kernel(path))
					{
						DPRINTF("Load boot plugin %s -> %x\n", path, num_loaded_kernel);
						num_loaded_kernel++;
					}
				}

				if (eof) break;
			}
			cellFsClose(fd);
		}

		kfree(path);
	}
}

void load_boot_plugins(void)
{
	for(unsigned int n = 0; n < MAX_VSH_PLUGINS; n++) vsh_plugins[n] = 0;

	// KW / Special thanks to KW/EVILNAT for providing an awesome source
	// Improving initial KW's code
	// If it does not exist in '/dev_usb000' or '/dev_usb001' will load it from '/dev_hdd0'
	char *path = kalloc(MAX_FILE_LEN);

	if(path)
	{
		locate_file(path, "mamba_plugins.txt");

		int fd;
		if (cellFsOpen(path, CELL_FS_O_RDONLY, &fd, 0, NULL, 0) == CELL_FS_SUCCEEDED)
		{
			int current_slot = BOOT_PLUGINS_FIRST_SLOT;
			int num_loaded = 0;

			while (num_loaded < MAX_BOOT_PLUGINS)
			{
				int eof;

				if (read_text_line(fd, path, MAX_FILE_LEN, &eof) > 0)
				{
					int ret = prx_load_vsh_plugin(current_slot, path, NULL, 0);

					if (ret >= SUCCEEDED)
					{
						DPRINTF("Load boot plugin %s -> %x\n", path, current_slot);
						current_slot++;
						num_loaded++;
					}
				}

				if (eof) break;
			}
			cellFsClose(fd);
		}
		kfree(path);
	}
}

//----------------------------------------
//INIT
//----------------------------------------

void modules_patch_init(void)
{
	if (!vsh_process) vsh_process = get_vsh_process(); //NzV

	hook_function_with_precall(lv1_call_99_wrapper_symbol, post_lv1_call_99_wrapper, 2);

	patch_call(patch_func2 + patch_func2_offset, modules_patching);

	hook_function_with_cond_postcall(modules_verification_symbol, pre_modules_verification, 2);
	#ifdef PS3M_API
	hook_function_with_postcall(map_process_memory_symbol, pre_map_process_memory, 7);
	#endif
	#ifndef DEBUG
	if (!vsh_process) hook_function_on_precall_success(load_process_symbol, load_process_hooked, 9);
	#else
	hook_function_on_precall_success(load_process_symbol, load_process_hooked, 9);
	//hook_function_on_precall_success(create_process_common_symbol, create_process_common_hooked, 16);
	//hook_function_with_postcall(create_process_common_symbol, create_process_common_hooked_pre, 8);
	#endif

	#ifdef DO_REACTPSN
	hook_function_with_precall(get_syscall_address(801), sys_fs_open,  6);
	hook_function_with_precall(get_syscall_address(802), sys_fs_read,  4);
	hook_function_with_precall(get_syscall_address(804), sys_fs_close, 1);
	#endif

	storage_ext_patches();
	region_patches();
}

#ifdef PS3M_API

//----------------------------------------
// UNHOOK (PS3M_API)
//----------------------------------------

void unhook_all_modules(void)
{
	suspend_intr();


#ifdef patch_func2_offset_restore
	*(uint32_t *)MKA(patch_func2 + patch_func2_offset) = patch_func2_offset_restore;
	clear_icache((void *)MKA(patch_func2 + patch_func2_offset), 4);
#endif

	unhook_function_with_precall(lv1_call_99_wrapper_symbol, post_lv1_call_99_wrapper, 2);
	unhook_function_with_cond_postcall(modules_verification_symbol, pre_modules_verification, 2);
	unhook_function_with_postcall(map_process_memory_symbol, pre_map_process_memory, 7);

	#ifdef DO_CEX2OFW_FIX
	unhook_function_on_precall_success(load_process_symbol, load_process_hooked, 9);
	#endif

	#ifdef DEBUG
	//unhook_function_on_precall_success(create_process_common_symbol, create_process_common_hooked, 16);
	//unhook_function_with_postcall(create_process_common_symbol, create_process_common_hooked_pre, 8);
	#endif

	#ifdef DO_REACTPSN
	unhook_function_with_precall(get_syscall_address(801), sys_fs_open,  6);
	unhook_function_with_precall(get_syscall_address(802), sys_fs_read,  4);
	unhook_function_with_precall(get_syscall_address(804), sys_fs_close, 1);
	#endif

	enable_kernel_patches();

	resume_intr();
}

void ps3mapi_unhook_all(void)
{
	unhook_all_modules();
	unhook_all_region();
	unhook_all_map_path();
	unhook_all_storage_ext();
//	unhook_all_permissions();
	#ifdef FAN_CONTROL
	unhook_all_fan_patches();
	#endif
}

//----------------------------------------
// VSH PLUGIN INFO (PS3M_API)
//----------------------------------------
int ps3mapi_get_process_module_info(process_t process, sys_prx_id_t prx_id, char *name, char *filename);

int ps3mapi_get_vsh_plugin_info(unsigned int slot, char *name, char *filename)
{
	if (!vsh_process) {vsh_process = get_vsh_process(); //NzV
	if (vsh_process <= 0) return ESRCH;}

	if (vsh_plugins[slot] == 0)
		return ENOENT;

	return ps3mapi_get_process_module_info(vsh_process, vsh_plugins[slot], name, filename);
}

//----------------------------------------
// UNLOAD VSH PLUGIN BY NAME (PS3M_API)
//----------------------------------------
int ps3mapi_unload_vsh_plugin(char *name)
{
	if (!vsh_process) {vsh_process = get_vsh_process(); //NzV
	if (vsh_process <= 0) return ESRCH;}

	char *filename = kalloc(MAX_FILE_LEN);
	if (!filename)
		return ENOMEM;

	for (unsigned int slot = 0; slot < MAX_VSH_PLUGINS; slot++)
	{
		if (vsh_plugins[slot] == 0)
			continue;

		int ret = ps3mapi_get_process_module_info(vsh_process, vsh_plugins[slot], NULL, filename);
		if (ret == SUCCEEDED)
		{
			if (strcmp(filename, get_secure_user_ptr(name)) == SUCCEEDED)
			{
				kfree(filename);
				return prx_unload_vsh_plugin(slot);
			}
		}
	}

	kfree(filename);
	return ESRCH;
}
#endif
