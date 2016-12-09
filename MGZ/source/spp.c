/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#include <stdio.h>

#include "types.h"
#include "sce.h"
#include "spp.h"
#include "util.h"

static void _print_spp_header(FILE *fp, spp_header_t *h)
{
	fprintf(fp, "[*] SPP Header:\n");
	fprintf(fp, " unk1        0x%04X\n", h->unk1);
	fprintf(fp, " unk2        0x%04X\n", h->unk2);
	fprintf(fp, " SPP Size    0x%08X\n", h->spp_size);
	fprintf(fp, " unk3        0x%08X\n", h->unk3);
	fprintf(fp, " unk4        0x%08X\n", h->unk4);
	fprintf(fp, " unk5        0x%016llX\n", h->unk5);
	fprintf(fp, " Entry Count 0x%08X\n", h->entcnt);
	fprintf(fp, " unk7        0x%08X\n", h->unk7);
}

static void _print_spp_entry_header(FILE *fp, spp_entry_header_t *h, unsigned int idx)
{
	fprintf(fp, "[*] SPP Entry %02d:\n", idx);
	fprintf(fp, " Size            0x%08X\n", h->entry_size);
	fprintf(fp, " Type            0x%08X\n", h->type);
	fprintf(fp, " LPAR Auth-ID    0x%016llX\n", h->laid);
	fprintf(fp, " Program Auth-ID 0x%016llX\n", h->paid);
	fprintf(fp, " Name            %s\n", h->name);
}

void spp_print(FILE *fp, sce_buffer_ctxt_t *ctxt)
{
	unsigned int i;

	//First section contains the SPP header.
	spp_header_t *header = (spp_header_t *)(ctxt->scebuffer + ctxt->metash[0].data_offset);
	_es_spp_header(header);

	//Second section contains the entries.
	unsigned char *ent = ctxt->scebuffer + ctxt->metash[1].data_offset;

	_print_spp_header(fp, header);

	for(i = 0; i < header->entcnt; i++)
	{
		//Get current entry header.
		spp_entry_header_t *eh = (spp_entry_header_t *)ent;
		_es_spp_entry_header(eh);

		//Print header.
		_print_spp_entry_header(fp, eh, i);

		//Print data.
		_hexdump(fp, " Data", 0, ent + sizeof(spp_entry_header_t), eh->entry_size - sizeof(spp_entry_header_t), TRUE);

		/*
		switch(eh->type)
		{
		case SPP_ENTRY_TYPE_1:
			break;
		case SPP_ENTRY_TYPE_2:
			break;
		default:
			printf("[*] Error: Unknown entry type 0x%08X (entry %02d)\n", eh->type, i);
		}
		*/

		//Move pointer to next entry.
		ent += eh->entry_size;
	}
}
