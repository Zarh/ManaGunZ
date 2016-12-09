/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#include "types.h"
#include "config.h"
#include "util.h"
#include "sce.h"
#include "elf.h"
#include "self.h"
#include "keys.h"
#include <stdio.h> 


/*! SELF types. */
id_to_name_t _self_types[] = 
{
	{SELF_TYPE_LV0, "lv0"},
	{SELF_TYPE_LV1, "lv1"},
	{SELF_TYPE_LV2, "lv2"},
	{SELF_TYPE_APP, "Application"},
	{SELF_TYPE_ISO, "Isolated SPU Module"},
	{SELF_TYPE_LDR, "Secure Loader"},
	{SELF_TYPE_UNK_7, "Unknown 7"},
	{SELF_TYPE_NPDRM, "NPDRM Application"},
	{0, NULL}
};

/*! SELF types as parameter. */
id_to_name_t _self_types_params[] = 
{
	{SELF_TYPE_LV0, "LV0"},
	{SELF_TYPE_LV1, "LV1"},
	{SELF_TYPE_LV2, "LV2"},
	{SELF_TYPE_APP, "APP"},
	{SELF_TYPE_ISO, "ISO"},
	{SELF_TYPE_LDR, "LDR"},
	//{SELF_TYPE_UNK_7, "UNK7"},
	{SELF_TYPE_NPDRM, "NPDRM"},
	{0, NULL}
};

/* Control info types. */
id_to_name_t _control_info_types[] = 
{
	{CONTROL_INFO_TYPE_FLAGS, "Flags"},
	{CONTROL_INFO_TYPE_DIGEST, "Digest"},
	{CONTROL_INFO_TYPE_NPDRM, "NPDRM"},
	{0, NULL}
};

/*! Optional header types. */
id_to_name_t _optional_header_types[] = 
{
	{OPT_HEADER_TYPE_CAP_FLAGS, "Capability Flags"},
#ifdef CONFIG_DUMP_INDIV_SEED
	{OPT_HEADER_TYPE_INDIV_SEED, "Individuals Seed"},
#endif
	{0, NULL}
};

/*! NPDRM application types. */
id_to_name_t _np_app_types[] = 
{
	{NP_TYPE_SPRX, "SPRX"},
	{NP_TYPE_EXEC, "EXEC"},
	{NP_TYPE_USPRX, "USPRX"},
	{NP_TYPE_UEXEC, "UEXEC"},
	{0, NULL},
};

/*! Auth IDs. */
id_to_name_t _auth_ids[] = 
{
	{0x1010000001000003, "retail game/update"},
	{0x1020000401000001, "ps2emu"},
	{0x1050000003000001, "lv2_kernel"},
	{0x1070000001000002, "onicore_child"},
	{0x1070000002000002, "mcore"},
	{0x1070000003000002, "mgvideo"},
	{0x1070000004000002, "swagner, swreset"},
	{0x1070000017000001, "ss_init (lv1)"},
	{0x107000001A000001, "ss_sc_init_pu (lv1)"},
	{0x107000001C000001, "updater_frontend (lv1)"},
	{0x107000001D000001, "sysmgr_ss (lv1)"},
	{0x107000001F000001, "sb_iso_spu_module"},
	{0x1070000020000001, "sc_iso, sc_iso_factory"},
	{0x1070000021000001, "spp_verifier"},
	{0x1070000022000001, "spu_pkg_rvk_verifier"},
	{0x1070000023000001, "spu_token_processor"},
	{0x1070000024000001, "sv_iso_spu_module"},
	{0x1070000025000001, "aim_spu_module"},
	{0x1070000026000001, "ss_sc_init"},
	{0x1070000028000001, "factory_data_mngr_server (lv1)"},
	{0x1070000029000001, "fdm_spu_module"},
	{0x1070000032000001, "ss_server1 (lv1)"},
	{0x1070000033000001, "ss_server2 (lv1)"},
	{0x1070000034000001, "ss_server3 (lv1)"},
	{0x1070000037000001, "mc_iso_spu_module"},
	{0x1070000039000001, "bdp_bdmv"},
	{0x107000003A000001, "bdj"},
	{0x1070000040000001, "sys/external modules"},
	{0x1070000041000001, "ps1emu"},
	{0x1070000043000001, "me_iso_spu_module"},
	{0x1070000046000001, "spu_mode_auth"},
	{0x107000004C000001, "spu_utoken_processor"},
	{0x1070000052000001, "sys/internal + vsh/module modules"},
	{0x1070000055000001, "manu_info_spu_module"},
	{0x1070000058000001, "me_iso_for_ps2emu"},
	{0x1070000059000001, "sv_iso_for_ps2emu"},
	{0x1070000300000001, "Lv2diag BD Remarry"},
	{0x10700003FC000001, "emer_init"},
	{0x10700003FD000001, "ps3swu"},
	{0x10700003FF000001, "Lv2diag FW Stuff"},
	{0x1070000409000001, "pspemu"},
	{0x107000040A000001, "psp_translator"},
	{0x107000040B000001, "pspemu modules"},
	{0x107000040C000001, "pspemu drm"},
	{0x1070000500000001, "cellftp"},
	{0x1070000501000001, "hdd_copy"},
	{0x10700005FC000001, "sys_audio"},
	{0x10700005FD000001, "sys_init_osd"},
	{0x10700005FF000001, "vsh"},
	{0x1FF0000001000001, "lv0"},
	{0x1FF0000002000001, "lv1"},
	{0x1FF0000008000001, "lv1ldr"},
	{0x1FF0000009000001, "lv2ldr"},
	{0x1FF000000A000001, "isoldr"},
	{0x1FF000000C000001, "appldr"},
	{0, NULL}
};

/*! Vendor IDs. */
id_to_name_t _vendor_ids[] = 
{
	{0xFF000000, "hv"},
	{0x07000001, "system"},
	{0x01000002, "normal"},
	{0x05000002, "lv2"},
	{0x02000003, "ps2emu"},
	{0, NULL}
};

/*! ELF machines. */
id_to_name_t _e_machines[] = 
{
	{EM_PPC, "PPC"},
	{EM_PPC64, "PPC64"},
	{EM_SPU, "SPU"},
	{0, NULL}
};

/*! ELF types. */
id_to_name_t _e_types[] = 
{
	{ET_EXEC, "EXEC"},
	{ET_PS3PRX, "PRX"},
	{0, NULL}
};

/*! Section header types. */
id_to_name_t _sh_types[] = 
{
	{SHT_NULL, "NULL"},
	{SHT_PROGBITS, "PROGBITS"},
	{SHT_SYMTAB, "SYMTAB"},
	{SHT_STRTAB, "STRTAB"},
	{SHT_RELA, "RELA"},
	{SHT_HASH, "HASH"},
	{SHT_DYNAMIC, "DYNAMIC"},
	{SHT_NOTE, "NOTE"},
	{SHT_NOBITS, "NOBITS"},
	{SHT_REL, "REL"},
	{SHT_SHLIB, "SHLIB"},
	{SHT_DYNSYM, "DYNSYM"},
	{SHT_INIT_ARRAY, "INIT_ARRAY"},
	{SHT_FINI_ARRAY, "FINI_ARRAY"},
	{SHT_PREINIT_ARRAY, "PREINIT_ARRAY"},
	{SHT_GROUP, "GROUP"},
	{SHT_SYMTAB_SHNDX, "SYMTAB_SHNDX"},
	{0, NULL}
};

/*! Program header types. */
id_to_name_t _ph_types[] = 
{
	{PT_NULL, "NULL"},
	{PT_LOAD, "LOAD"},
	{PT_DYNAMIC, "DYNAMIC"},
	{PT_INTERP, "INTERP"},
	{PT_NOTE, "NOTE"},
	{PT_SHLIB, "SHLIB"},
	{PT_PHDR, "PHDR"},
	{PT_TLS, "TLS"},
	{PT_NUM, "NUM"},
	{PT_PS3_PARAMS, "PARAMS"},
	{PT_PS3_PRX, "PRX"},
	{PT_PS3_PRX_RELOC, "PRXRELOC"},
	{0, NULL}
};

/*! Key types. */
id_to_name_t _key_types[] = 
{
	{KEYTYPE_SELF, "SELF"},
	{KEYTYPE_RVK, "RVK"},
	{KEYTYPE_PKG, "PKG"},
	{KEYTYPE_SPP, "SPP"},
	{KEYTYPE_OTHER, "OTHER"},
	{0, NULL}
};

/*! Key revisions. */
/*
const char *_key_revisions[] = 
{
	"Revision 0", 
	"0.92 - 3.30", 
	"NP 0x02", 
	"NP 0x03", 
	"3.40 - 3.42", 
	"NP 0x05", 
	"NP 0x06", 
	"3.50", 
	"NP 0x08", 
	"NP 0x09", 
	"3.55", 
	"NP 0x0b", 
	"NP 0x0c", 
	"3.56", 
	"NP 0x0e", 
	"NP 0x0f", 
	"3.60 - 3.61", 
	"NP 0x11", 
	"NP 0x12", 
	"3.65", 
	"NP 0x14", 
	"NP 0x15", 
	"3.70 - 3.73", 
	"NP 0x17", 
	"NP 0x18", 
	"0x19",
	"0x1A",
	"0x1B",
	"0x1C",
	"0x1D",
	"0x1E",
	"0x1F"
};
*/

/*! SCE header types. */
id_to_name_t _sce_header_types[] = 
{
	{SCE_HEADER_TYPE_SELF, "SELF"},
	{SCE_HEADER_TYPE_RVK, "RVK"},
	{SCE_HEADER_TYPE_PKG, "PKG"},
	{SCE_HEADER_TYPE_SPP, "SPP"},
	{0, NULL}
};
