/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#ifndef _SELF_H_
#define _SELF_H_

#include "types.h"
#include "config.h"
#include "np.h"

/*! PS3 specific ELF constants. */
/*! LV2 OS ABI. */
#define ELFOSABI_CELL_LV2 0x66
/*! PRX ELF type. */
#define ET_PS3PRX 0xFFA4
/*! PS3 Params. */
#define PT_PS3_PARAMS 0x60000001
/*! PS3 PRX. */
#define PT_PS3_PRX 0x60000002
/*! PRX Relocations. */
#define PT_PS3_PRX_RELOC 0x700000A4

/*! SELF config. */
typedef struct _self_config
{
	/*! Add section headers. */
	BOOL add_shdrs;
	/*! Compress data. */
	BOOL compress_data;
	/*! Skip sections. */
	BOOL skip_sections;

	/*! Key revision. */
	unsigned short key_revision;
	/*! Auth ID. */
	unsigned long long int auth_id;
	/*! Vendor ID. */
	unsigned int vendor_id;
	/*! SELF type. */
	unsigned int self_type;
	/*! Application version. */
	unsigned long long int app_version;
	/*! Firmware version. */
	unsigned long long int fw_version;

	/*! Control flags. */
	unsigned char *ctrl_flags;
	/*! Capability flags. */
	unsigned char *cap_flags;
#ifdef CONFIG_CUSTOM_INDIV_SEED
	/*! Individuals seed. */
	unsigned char *indiv_seed;
	/*! Individuals seed size. */
	unsigned int indiv_seed_size;
#endif

	/*! NPDRM config (used if not NULL). */
	npdrm_config_t *npdrm_config;
} self_config_t;

/*! Print SELF info. */
BOOL self_print_info(FILE *fp, sce_buffer_ctxt_t *ctxt);

/*! Create ELF from SELF. */
BOOL self_write_to_elf(sce_buffer_ctxt_t *ctxt, const char *elf_out);

/*! Create SELF from ELF. */
BOOL self_build_self(sce_buffer_ctxt_t *ctxt, self_config_t *sconf);

#endif
