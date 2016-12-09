/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#include <stdio.h>

#include "types.h"
#include "util.h"
#include "sce.h"
#include "rvk.h"
#include "tables.h"

static void _print_rvk_header(FILE *fp, rvk_header_t *h)
{
	fprintf(fp, "[*] Revoke List Header:\n");
	fprintf(fp, " type_0      0x%08X\n", h->type_0);
	fprintf(fp, " type_1      0x%08X\n", h->type_1);

	if(h->type_0 == 4)
		fprintf(fp, " Version     %s\n", sce_version_to_str(h->opaque));
	else
		fprintf(fp, " Opaque      0x%016llX\n", h->opaque);

	fprintf(fp, " Entry Count 0x%08X\n", h->entcnt);
}

/*
typedef struct _prg_rvk_entry
{
	unsigned int self_type; //3, 4
	unsigned int unk_1; //1, 3
	union
	{
		unsigned long long int version; //unk_1 == 1
		unsigned long long int unk_2; //unk_1 == 3
	};
	union
	{
		unsigned long long int auth_id;
		unsigned long long int unk_3;
	};
	unsigned char unk_4[8];
} prg_rvk_entry_t;
*/

static void _print_prg_rvk_entry_header(FILE *fp)
{
	fprintf(fp, "[*] Program Revoke List Entries:\n");
	fprintf(fp, " Type                Check    Version Auth-ID/unk_3    Mask\n");
}

static id_to_name_t _check_type_values[] = 
{
	{CHECK_SELF_NEQU_RVK, "!="},
	{CHECK_SELF_EQU_RVK, "=="},
	{CHECK_SELF_LT_RVK, "<"},
	{CHECK_SELF_LTEQU_RVK, "<="},
	{CHECK_SELF_GT_RVK, ">"},
	{CHECK_SELF_GTEQU_RVK, ">="},
	{0, NULL}
};

static void _print_prg_rvk_entry(FILE *fp, prg_rvk_entry_t *e)
{
	const char *name;

	name = _get_name(_self_types, e->self_type);
	if(name != NULL)
		fprintf(fp, " %-19s ", name);
	else
		fprintf(fp, " 0x%08X          ", e->self_type);

	name = _get_name(_check_type_values, e->check_type);
	if(name != NULL)
		fprintf(fp, "%-2s       ", name);
	else
		fprintf(fp, "%08X ", e->check_type);

	fprintf(fp, "%s   ", sce_version_to_str(e->version));

	name = _get_name(_auth_ids, e->auth_id);
	if(name != NULL)
		fprintf(fp, "%-16s ", name);
	else
		fprintf(fp, "%016llX ", e->auth_id);

	fprintf(fp, "%016llX ", e->mask);

	fprintf(fp, "\n");
}

void rvk_print(FILE *fp, sce_buffer_ctxt_t *ctxt)
{
	unsigned int i;

	rvk_header_t *rvkh = (rvk_header_t *)(ctxt->scebuffer + ctxt->metash[0].data_offset);
	_es_rvk_header(rvkh);

	_print_rvk_header(fp, rvkh);

	//Program revoke.
	if(rvkh->type_0 == 4)
	{
		prg_rvk_entry_t *ent = (prg_rvk_entry_t *)(ctxt->scebuffer + ctxt->metash[1].data_offset);
		_print_prg_rvk_entry_header(fp);
		for(i = 0; i < rvkh->entcnt; i++)
		{
			_es_prg_rvk_entry(&ent[i]);
			_print_prg_rvk_entry(fp, &ent[i]);
		}
	}
	else if(rvkh->type_0 == 3)
	{
		fprintf(fp, "[*] Package Revoke List Entries:\n");
		unsigned char *ent = (unsigned char *)(ctxt->scebuffer + ctxt->metash[1].data_offset);
		for(i = 0; i < rvkh->entcnt; i++)
		{
			_hexdump(fp, " ent", i*0x20, ent, 0x20, TRUE);
			ent += 0x20;
		}
	}
}
