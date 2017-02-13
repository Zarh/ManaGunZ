#include <lv2/lv2.h>
#include <lv2/libc.h>
#include <lv2/interrupt.h>
#include <lv2/modules.h>
#include <lv2/process.h>
#include <lv2/memory.h>
#include <lv2/io.h>
#include <lv2/pad.h>
#include <lv2/symbols.h>
#include <lv2/patch.h>
#include <lv2/error.h>
#include <lv2/security.h>
#include <lv2/thread.h>
#include <lv2/syscall.h>
#include <lv1/patch.h>

#include "common.h"
#include "modulespatch.h"
#include "crypto.h"
#include "config.h"
#include "storage_ext.h"
#include "syscall8.h"
#include "self.h"
#include "psp.h"

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

KeySet sprx_keys_set1[] =
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

KeySet sprx_keys_set2[] =
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

LV2_HOOKED_FUNCTION_PRECALL_2(int, post_lv1_call_99_wrapper, (uint64_t *spu_obj, uint64_t *spu_args))
{
	// This replaces an original patch of psjailbreak, since we need to do more things

	saved_buf = (void *)spu_args[0x20/8];
	saved_sce_hdr = (void *)spu_args[8/8];

	#ifdef DEBUG
	process_t process = get_current_process();
	if (process) DPRINTF("caller_process = %08X\n", process->pid);
	#endif

	return 0;
}

LV2_HOOKED_FUNCTION_COND_POSTCALL_2(int, pre_modules_verification, (uint32_t *ret, uint32_t error))
{
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
	return 0;
}
#ifdef DEBUG
static char *hash_to_name(uint64_t trunc_hash)
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
	return "UNKNOWN";
}
#endif

#ifdef DO_PATCH
#ifdef DO_PATCH_PS2
uint8_t condition_ps2softemu = 0;

SprxPatch explore_plugin_patches[] =
{
	{ ps2_nonbw_offset, LI(0, 1), &condition_ps2softemu },
	{ 0 }
};

SprxPatch explore_category_game_patches[] =
{
	{ ps2_nonbw_offset2, LI(R0, 1), &condition_ps2softemu },
	{ 0 }
};

SprxPatch game_ext_plugin_patches[] =
{
	{ ps2_nonbw_offset3, LI(R0, 1), &condition_ps2softemu },
	{ 0 }
};

//REBUG REX
SprxPatch rebug_explore_plugin_patches[] =
{
	#ifdef dex_ps2_nonbw_offset
	{ dex_ps2_nonbw_offset, LI(0, 1), &condition_ps2softemu },
	#else
	{ ps2_nonbw_offset, LI(0, 1), &condition_ps2softemu },
	#endif
	{ 0 }
};

SprxPatch rebug_explore_category_game_patches[] =
{
	#ifdef dex_ps2_nonbw_offset2
	{ dex_ps2_nonbw_offset2, LI(R0, 1), &condition_ps2softemu },
	#else
	{ ps2_nonbw_offset2, LI(R0, 1), &condition_ps2softemu },
	#endif
	{ 0 }
};

SprxPatch rebug_game_ext_plugin_patches[] =
{
	#ifdef dex_ps2_nonbw_offset3
	{ dex_ps2_nonbw_offset3, LI(R0, 1), &condition_ps2softemu },
	#else
	{ ps2_nonbw_offset3, LI(R0, 1), &condition_ps2softemu },
	#endif
	{ 0 }
};
#endif

#ifdef DO_PATCH_PSP
uint8_t condition_psp_iso = 0;
uint8_t condition_psp_dec = 0;
uint8_t condition_psp_keys = 0;
//uint8_t condition_psp_change_emu = 0;   // sys_psp_set_emu_path has been deleted (BASIC_PLUGINS patch not needed)
uint8_t condition_psp_prometheus = 0;
SprxPatch psp_emulator_patches[] =
{
	// Sets psp mode as opossed to minis mode. Increases compatibility, removes text protection and makes most savedata work
	{ psp_set_psp_mode_offset, LI(R4, 0), &condition_psp_iso },
	{ 0 }
};

SprxPatch emulator_api_patches[] =
{
	// Read umd patches
	{ psp_read, STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_read+4, MFLR(R0), &condition_psp_iso },
	{ psp_read+8, STD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_read+0x0C, MR(R8, R7), &condition_psp_iso },
	{ psp_read+0x10, MR(R7, R6), &condition_psp_iso },
	{ psp_read+0x14, MR(R6, R5), &condition_psp_iso },
	{ psp_read+0x18, MR(R5, R4), &condition_psp_iso },
	{ psp_read+0x1C, MR(R4, R3), &condition_psp_iso },
	{ psp_read+0x20, LI(R3, SYSCALL8_OPCODE_READ_PSP_UMD), &condition_psp_iso },
	{ psp_read+0x24, LI(R11, 8), &condition_psp_iso },
	{ psp_read+0x28, SC, &condition_psp_iso },
	{ psp_read+0x2C, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_read+0x30, MTLR(R0), &condition_psp_iso },
	{ psp_read+0x34, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_read+0x38, BLR, &condition_psp_iso },
	// Read header patches
	{ psp_read+0x3C, STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_read+0x40, MFLR(R0), &condition_psp_iso },
	{ psp_read+0x44, STD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_read+0x48, MR(R7, R6), &condition_psp_iso },
	{ psp_read+0x4C, MR(R6, R5), &condition_psp_iso },
	{ psp_read+0x50, MR(R5, R4), &condition_psp_iso },
	{ psp_read+0x54, MR(R4, R3), &condition_psp_iso },
	{ psp_read+0x58, LI(R3, SYSCALL8_OPCODE_READ_PSP_HEADER), &condition_psp_iso },
	{ psp_read+0x5C, LI(R11, 8), &condition_psp_iso },
	{ psp_read+0x60, SC, &condition_psp_iso },
	{ psp_read+0x64, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_read+0x68, MTLR(R0), &condition_psp_iso },
	{ psp_read+0x6C, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_read+0x70, BLR, &condition_psp_iso },
	{ psp_read_header, MAKE_CALL_VALUE(psp_read_header, psp_read+0x3C), &condition_psp_iso },
	// Drm patches
	{ psp_drm_patch5, MAKE_JUMP_VALUE(psp_drm_patch5, psp_drm_patch6), &condition_psp_iso },
	{ psp_drm_patch7, LI(R6, 0), &condition_psp_iso },
	{ psp_drm_patch8, LI(R7, 0), &condition_psp_iso },
	{ psp_drm_patch9, NOP, &condition_psp_iso },
	{ psp_drm_patch11, LI(R6, 0), &condition_psp_iso },
	{ psp_drm_patch12, LI(R7, 0), &condition_psp_iso },
	// product id
	{ psp_product_id_patch1, NOP, &condition_psp_iso },
	{ psp_product_id_patch3, NOP, &condition_psp_iso },
	{ 0 }
};

SprxPatch pemucorelib_patches[] =
{
	{ psp_eboot_dec_patch, LI(R6, 0x110), &condition_psp_dec }, // -> makes unsigned psp eboot.bin run, 0x10 works too
	{ psp_prx_patch, STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_prx_patch+4, MFLR(R6), &condition_psp_iso },
	{ psp_prx_patch+8, STD(R6, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch+0x0C, LI(R11, 8), &condition_psp_iso },
	{ psp_prx_patch+0x10, MR(R5, R4), &condition_psp_iso },
	{ psp_prx_patch+0x14, MR(R4, R3), &condition_psp_iso },
	{ psp_prx_patch+0x18, LI(R3, SYSCALL8_OPCODE_PSP_PRX_PATCH), &condition_psp_iso },
	{ psp_prx_patch+0x1C, SC, &condition_psp_iso },
	{ psp_prx_patch+0x20, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch+0x24, MTLR(R0), &condition_psp_iso },
	{ psp_prx_patch+0x28, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_prx_patch+0x2C, BLR, &condition_psp_iso },
	// Patch for savedata binding
	{ psp_savedata_bind_patch1, MR(R5, R19), &condition_psp_iso },
	{ psp_savedata_bind_patch2, MAKE_JUMP_VALUE(psp_savedata_bind_patch2, psp_prx_patch+0x30), &condition_psp_iso },
	{ psp_prx_patch+0x30, LD(R19, 0xFF98, SP), &condition_psp_iso },
	{ psp_prx_patch+0x34, STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_prx_patch+0x38, MFLR(R0), &condition_psp_iso },
	{ psp_prx_patch+0x3C, STD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch+0x40, LI(R11, 8), &condition_psp_iso },
	{ psp_prx_patch+0x44, MR(R4, R3), &condition_psp_iso },
	{ psp_prx_patch+0x48, LI(R3, SYSCALL8_OPCODE_PSP_POST_SAVEDATA_INITSTART), &condition_psp_iso },
	{ psp_prx_patch+0x4C, SC, &condition_psp_iso },
	{ psp_prx_patch+0x50, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch+0x54, MTLR(R0), &condition_psp_iso },
	{ psp_prx_patch+0x58, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_prx_patch+0x5C, BLR, &condition_psp_iso },
	{ psp_savedata_bind_patch3, MAKE_JUMP_VALUE(psp_savedata_bind_patch3, psp_prx_patch+0x60), &condition_psp_iso },
	{ psp_prx_patch+0x60, STDU(SP, 0xFF90, SP), &condition_psp_iso },
	{ psp_prx_patch+0x64, MFLR(R0), &condition_psp_iso },
	{ psp_prx_patch+0x68, STD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch+0x6C, LI(R11, 8), &condition_psp_iso },
	{ psp_prx_patch+0x70, LI(R3, SYSCALL8_OPCODE_PSP_POST_SAVEDATA_SHUTDOWNSTART), &condition_psp_iso },
	{ psp_prx_patch+0x74, SC, &condition_psp_iso },
	{ psp_prx_patch+0x78, LD(R0, 0x80, SP), &condition_psp_iso },
	{ psp_prx_patch+0x7C, MTLR(R0), &condition_psp_iso },
	{ psp_prx_patch+0x80, ADDI(SP, SP, 0x70), &condition_psp_iso },
	{ psp_prx_patch+0x84, BLR, &condition_psp_iso },
	// Prometheus
	{ psp_prometheus_patch, '.OLD', &condition_psp_prometheus },
	// Extra save data patch required since some 3.60+ firmware
	{ psp_extra_savedata_patch, LI(R31, 1), &condition_psp_iso },
	{ 0 }
};

SprxPatch libsysutil_savedata_psp_patches[] =
{
	{ psp_savedata_patch1, MAKE_JUMP_VALUE(psp_savedata_patch1, psp_savedata_patch2), &condition_psp_iso },
	{ psp_savedata_patch3, NOP, &condition_psp_iso },
	{ psp_savedata_patch4, NOP, &condition_psp_iso },
	{ psp_savedata_patch5, NOP, &condition_psp_iso },
	{ psp_savedata_patch6, NOP, &condition_psp_iso },
	{ 0 }
};
#endif

uint8_t condition_apphome = 0; //JB format game

SprxPatch libfs_external_patches[] =
{
	// Redirect internal libfs function to kernel. If condition_apphome is 1, it means there is a JB game mounted
	{ aio_copy_root_offset, STDU(SP, 0xFF90, SP), &condition_apphome },
	{ aio_copy_root_offset+4, MFLR(R0), &condition_apphome },
	{ aio_copy_root_offset+8, STD(R0, 0x80, SP), &condition_apphome },
	{ aio_copy_root_offset+0x0C, MR(R5, R4), &condition_apphome },
	{ aio_copy_root_offset+0x10, MR(R4, R3), &condition_apphome },
	{ aio_copy_root_offset+0x14, LI(R3, SYSCALL8_OPCODE_AIO_COPY_ROOT), &condition_apphome },
	{ aio_copy_root_offset+0x18, LI(R11, 8), &condition_apphome },
	{ aio_copy_root_offset+0x1C, SC, &condition_apphome },
	{ aio_copy_root_offset+0x20, LD(R0, 0x80, SP), &condition_apphome },
	{ aio_copy_root_offset+0x24, MTLR(R0), &condition_apphome },
	{ aio_copy_root_offset+0x28, ADDI(SP, SP, 0x70), &condition_apphome },
	{ aio_copy_root_offset+0x2C, BLR, &condition_apphome },
	{ 0 }
};

#define N_PATCH_TABLE_ENTRIES	(sizeof(patch_table) / sizeof(PatchTableEntry))

PatchTableEntry patch_table[] =
{
	{ LIBFS_EXTERNAL_HASH, libfs_external_patches },
#ifdef DO_PATCH_PSP
	{ PSP_EMULATOR_HASH, psp_emulator_patches },
	{ EMULATOR_API_HASH, emulator_api_patches },
	{ PEMUCORELIB_HASH, pemucorelib_patches },
	{ LIBSYSUTIL_SAVEDATA_PSP_HASH, libsysutil_savedata_psp_patches },
#endif
#ifdef DO_PATCH_PS2
	{ EXPLORE_PLUGIN_HASH, explore_plugin_patches },
	{ EXPLORE_CATEGORY_GAME_HASH, explore_category_game_patches },
	{ GAME_EXT_PLUGIN_HASH, game_ext_plugin_patches },
#endif
};

PatchTableEntry patch_table_rebug[] =
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
	{ EXPLORE_CATEGORY_GAME_REBUG_HASH, rebug_explore_category_game_patches },
	{ GAME_EXT_PLUGIN_REBUG_HASH, rebug_game_ext_plugin_patches },
#endif
#endif
};

#endif

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
//	DPRINTF("Flags = %x      %x\n", self->flags, (p[0x30/4] >> 16));
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
		int dongle_decrypt = 0;

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
				uint8_t dif_keys[16];

				memset(dif_keys, 0, 16);

				if (!dongle_decrypt) memcpy(keys, extHdr->keys_mod, 16);

				for (int i = 0; i < 16; i++)
				{
					keys[i] ^= (keySet->keys[15-i] ^ dif_keys[15-i]);
				}

				nonce = keySet->nonce ^ extHdr->nonce_mod;
			}

			uint32_t num_blocks = chunk_size / 8;

			xtea_ctr(keys, nonce, enc_buf, num_blocks*8);
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
		if (last_chunk) DPRINTF("Total section size: %x\n", total+ptr32[4/4]);
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
		uint64_t hash = 0;

		for (int i = 0; i < 0x100; i++)
		{
			hash ^= buf[i];
		}

		hash = (hash << 32) | total;
		total = 0;
		#ifdef DEBUG
		DPRINTF("hash = %lx\n", hash);
		#endif

        #ifdef DO_PATCH
        uint64_t trunc_hash = (hash >> 16), plugin_trunc_hash = 0;
        #ifdef DO_PATCH_PSP
        //uint64_t pspemu_off = pspemu_path_offset, psptrans_off = psptrans_path_offset;

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
				memcpy(buf+((psp_drm_key_overwrite+8)/4), psp_keys, 16);
			}
		}
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

			if (plugin_trunc_hash == trunc_hash)
			{
				#ifdef DEBUG
				DPRINTF("Now patching %s %lx\n", hash_to_name(trunc_hash), hash);
				#endif

				int j = 0;
				SprxPatch *patch = &patch_table[i].patch_table[j];

				while (patch->offset != 0)
				{
					if (*patch->condition)
					{
						buf[patch->offset/4] = patch->data;
						#ifdef  DEBUG
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
	uint64_t *proc_list = *(uint64_t **)MKA(TOC+process_rtoc_entry_1);
	proc_list = *(uint64_t **)proc_list;
	proc_list = *(uint64_t **)proc_list;
	for (int i = 0; i < 16; i++)
	{
		process_t p = (process_t)proc_list[1];
		proc_list += 2;
		if ((((uint64_t)p) & 0xFFFFFFFF00000000ULL) != MKA(0)) continue;
		if (is_vsh_process(p)) return p;
	}
	return NULL;
}


LV2_HOOKED_FUNCTION_PRECALL_SUCCESS_8(int, load_process_hooked, (process_t process, int fd, char *path, int r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t sp_70))
{

	#ifdef DEBUG
	DPRINTF("PROCESS %s (%08X) loaded\n", path, process->pid);
	#endif
	//Get VSH process
	if (!vsh_process)
	{
        if(is_vsh_process(process->parent)) vsh_process = process->parent;
        else if (is_vsh_process(process)) vsh_process = process;
		else vsh_process = get_vsh_process();
		#ifndef DEBUG
		if (vsh_process) unhook_function_on_precall_success(load_process_symbol, load_process_hooked, 9);
		#endif

		if ((vsh_process) && (storage_ext_patches_done == 0))
		{
			storage_ext_patches_done = 1;
			storage_ext_patches();
		}
	}
	#ifndef DEBUG
	else unhook_function_on_precall_success(load_process_symbol, load_process_hooked, 9);
	#endif

	return 0;
}

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


#define MAX_VSH_PLUGINS				7
#define BOOT_PLUGINS_FILE			"/dev_hdd0/boot_plugins.txt"
#define BOOT_PLUGINS_FIRST_SLOT		1
#define MAX_BOOT_PLUGINS 			(MAX_VSH_PLUGINS-BOOT_PLUGINS_FIRST_SLOT)


sys_prx_id_t vsh_plugins[MAX_VSH_PLUGINS];
static int loading_vsh_plugin = 0;


// Kernel version of prx_load_vsh_plugin
int prx_load_vsh_plugin(unsigned int slot, char *path, void *arg, uint32_t arg_size)
{
	void *kbuf, *vbuf;
	sys_prx_id_t prx;
	int ret;
	if (!vsh_process) vsh_process = get_vsh_process(); //NzV
    if(!vsh_process) return ESRCH;

	if (slot >= MAX_VSH_PLUGINS || (arg != NULL && arg_size > KB(64)))
		return EINVAL;

	if (vsh_plugins[slot] != 0) return EKRESOURCE;

	CellFsStat stat;
	if (cellFsStat(path, &stat) != 0) return EINVAL;

	loading_vsh_plugin = 1;
	prx = prx_load_module(vsh_process, 0, 0, path);
	loading_vsh_plugin  = 0;

	if (prx < 0) return prx;

	if (arg && arg_size > 0)
	{
		page_allocate_auto(vsh_process, KB(64), 0x2F, &kbuf);
		page_export_to_proc(vsh_process, kbuf, 0x40000, &vbuf);
		memcpy(kbuf, arg, arg_size);
	}
	else vbuf = NULL;

	ret = prx_start_module_with_thread(prx, vsh_process, 0, (uint64_t)vbuf);

	if (vbuf)
	{
		page_unexport_from_proc(vsh_process, vbuf);
		page_free(vsh_process, kbuf, 0x2F);
	}

	if (ret == 0) vsh_plugins[slot] = prx;

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
	if (!vsh_process) vsh_process = get_vsh_process(); //NzV
    if(!vsh_process) return ESRCH;

	#ifdef DEBUG
	DPRINTF("Trying to unload vsh plugin %x\n", slot);
	#endif

	if (slot >= MAX_VSH_PLUGINS)
		return EINVAL;

	prx = vsh_plugins[slot];
	#ifdef DEBUG
	DPRINTF("Current plugin: %08X\n", prx);
	#endif

	if (prx == 0) return ENOENT;

	ret = prx_stop_module_with_thread(prx, vsh_process, 0, 0);
	if (ret == 0) ret = prx_unload_module(prx, vsh_process);
	#ifdef DEBUG
	else DPRINTF("Stop failed: %x!\n", ret);
	#endif
	if (ret == 0)
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

#ifdef PS3M_API

int ps3mapi_unload_vsh_plugin(char *name)
{
	if (!vsh_process) vsh_process = get_vsh_process();
    if (vsh_process <= 0) return ESRCH;
	for (unsigned int slot = 0; slot < MAX_VSH_PLUGINS; slot++)
	{
		if (vsh_plugins[slot] == 0) continue;
		char *filename = alloc(256, 0x35);
		if (!filename) return ENOMEM;
		sys_prx_segment_info_t *segments = alloc(sizeof(sys_prx_segment_info_t), 0x35);
		if (!segments) {dealloc(filename, 0x35); return ENOMEM;}
		sys_prx_module_info_t modinfo;
		memset(&modinfo, 0, sizeof(sys_prx_module_info_t));
		modinfo.filename_size = 256;
		modinfo.segments_num = 1;
		int ret = prx_get_module_info(vsh_process, vsh_plugins[slot], &modinfo, filename, segments);
		if (ret == SUCCEEDED)
		{
			if (strcmp(modinfo.name, get_secure_user_ptr(name)) == 0)
				{
					dealloc(filename, 0x35);
					dealloc(segments, 0x35);
					return prx_unload_vsh_plugin(slot);
				}
		}
		dealloc(filename, 0x35);
		dealloc(segments, 0x35);
	}
	return ESRCH;
}

int ps3mapi_get_vsh_plugin_info(unsigned int slot, char *name, char *filename)
{
	if (!vsh_process) vsh_process = get_vsh_process();
    if (vsh_process <= 0) return ESRCH;
	if (vsh_plugins[slot] == 0) return ENOENT;
	char *tmp_filename = alloc(256, 0x35);
	if (!tmp_filename) return ENOMEM;
	sys_prx_segment_info_t *segments = alloc(sizeof(sys_prx_segment_info_t), 0x35);
	if (!segments) {dealloc(tmp_filename, 0x35); return ENOMEM;}
	sys_prx_module_info_t modinfo;
	memset(&modinfo, 0, sizeof(sys_prx_module_info_t));
	modinfo.filename_size = 256;
	modinfo.segments_num = 1;
	int ret = prx_get_module_info(vsh_process, vsh_plugins[slot], &modinfo, tmp_filename, segments);
	if (ret == SUCCEEDED)
	{
			unsigned int len;
			char tmp_name[30], tmp_filename2[256];
			len = sprintf(tmp_name, "%s", modinfo.name);
			ret = copy_to_user(&tmp_name, get_secure_user_ptr(name), len);
			len = sprintf(tmp_filename2, "%s", tmp_filename);
			ret = copy_to_user(&tmp_filename2, get_secure_user_ptr(filename), len);
	}
	dealloc(tmp_filename, 0x35);
	dealloc(segments, 0x35);
	return ret;
}

#endif

//----------------------------------------
//INIT
//----------------------------------------

void modules_patch_init(void)
{
    int n;
    for(n = 0; n < MAX_VSH_PLUGINS; n++) vsh_plugins[n] = 0;

	hook_function_with_precall(lv1_call_99_wrapper_symbol, post_lv1_call_99_wrapper, 2);
	patch_call(patch_func2 + patch_func2_offset, modules_patching);

	hook_function_with_cond_postcall(modules_verification_symbol, pre_modules_verification, 2);
	#ifdef PS3M_API
	hook_function_with_postcall(map_process_memory_symbol, pre_map_process_memory, 7);
	#endif
	if (!vsh_process) vsh_process = get_vsh_process(); //NzV
	#ifndef DEBUG
	if (!vsh_process) hook_function_on_precall_success(load_process_symbol, load_process_hooked, 9);
	#else
	hook_function_on_precall_success(load_process_symbol, load_process_hooked, 9);
	//hook_function_on_precall_success(create_process_common_symbol, create_process_common_hooked, 16);
	//hook_function_with_postcall(create_process_common_symbol, create_process_common_hooked_pre, 8);
	#endif
}

#ifdef PS3M_API

void unhook_all_modules(void)
{
	suspend_intr();
	unhook_function_with_precall(lv1_call_99_wrapper_symbol, post_lv1_call_99_wrapper, 2);
	unhook_function_with_cond_postcall(modules_verification_symbol, pre_modules_verification, 2);
	unhook_function_with_postcall(map_process_memory_symbol, pre_map_process_memory, 7);
	#ifdef DEBUG
	unhook_function_on_precall_success(load_process_symbol, load_process_hooked, 9); //unhook it-self if not set to debug
	//unhook_function_on_precall_success(create_process_common_symbol, create_process_common_hooked, 16);
	//unhook_function_with_postcall(create_process_common_symbol, create_process_common_hooked_pre, 8);
	#endif
	resume_intr();
}

#endif

