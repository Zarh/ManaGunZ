/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "config.h"
#include "util.h"
#include "sce.h"
#include "sce_inlines.h"
#include "self.h"
#include "elf.h"
#include "elf_inlines.h"
#include "tables.h"
#include "sha1.h"
#include "np.h"

static void _get_shdr_flags(char *str, unsigned long long int flags)
{
	memset(str, '-', 3);
	str[3] = 0;

	if(flags & SHF_WRITE)
		str[0] = 'W';
	if(flags & SHF_ALLOC)
		str[1] = 'A';
	if(flags & SHF_EXECINSTR)
		str[2] = 'E';
}

static void _get_phdr_flags(char *str, unsigned long long int flags)
{
	memset(str, '-', 3);
	str[3] = 0;

	if(flags & PF_X)
		str[0] = 'X';
	if(flags & PF_W)
		str[1] = 'W';
	if(flags & PF_R)
		str[2] = 'R';
}

void _print_self_header(FILE *fp, self_header_t *h)
{
	fprintf(fp, "[*] SELF Header:\n");
	fprintf(fp, " Header Type         0x%016llX\n", h->header_type);
	fprintf(fp, " App Info Offset     0x%016llX\n", h->app_info_offset);
	fprintf(fp, " ELF Offset          0x%016llX\n", h->elf_offset);
	fprintf(fp, " PH Offset           0x%016llX\n", h->phdr_offset);
	fprintf(fp, " SH Offset           0x%016llX\n", h->shdr_offset);
	fprintf(fp, " Section Info Offset 0x%016llX\n", h->section_info_offset);
	fprintf(fp, " SCE Version Offset  0x%016llX\n", h->sce_version_offset);
	fprintf(fp, " Control Info Offset 0x%016llX\n", h->control_info_offset);
	fprintf(fp, " Control Info Size   0x%016llX\n", h->control_info_size);
	//fprintf(fp, " padding             0x%016llX\n", h->padding);
}

void _print_app_info(FILE *fp, app_info_t *ai)
{
	const char *name;

	fprintf(fp, "[*] Application Info:\n");
	
	name = _get_name(_auth_ids, ai->auth_id);
	if(name != NULL)
	{
		fprintf(fp, " Auth-ID   ");
		_PRINT_RAW(fp, "0x%016llX ", ai->auth_id);
		fprintf(fp, "[%s]\n", name);
	}
	else
		fprintf(fp, " Auth-ID   0x%016llX\n", ai->auth_id);
	
	name = _get_name(_vendor_ids, ai->vendor_id);
	if(name != NULL)
	{
		fprintf(fp, " Vendor-ID ");
		_PRINT_RAW(fp, "0x%08X ", ai->vendor_id);
		fprintf(fp, "[%s]\n", name);
	}
	else
		fprintf(fp, " Vendor-ID 0x%08X\n", ai->vendor_id);

	name = _get_name(_self_types, ai->self_type);
	if(name != NULL)
		fprintf(fp, " SELF-Type [%s]\n", name);
	else
		fprintf(fp, " SELF-Type 0x%08X\n", ai->self_type);

	fprintf(fp, " Version   %s\n", sce_version_to_str(ai->version));
	//fprintf(fp, " padding   0x%016llX\n", ai->padding);
}

void _print_section_info_header(FILE *fp)
{
	fprintf(fp, "[*] Section Infos:\n");
	fprintf(fp, " Idx Offset   Size     Compressed unk0     unk1     Encrypted\n");
}

void _print_section_info(FILE *fp, section_info_t *si, unsigned int idx)
{
	fprintf(fp, " %03d %08X %08X %s      %08X %08X %s\n", 
		idx, (unsigned int)si->offset, (unsigned int)si->size, si->compressed == 2 ? "[YES]" : "[NO ]", 
		si->unknown_0, si->unknown_1, si->encrypted == 1 ? "[YES]" : "[NO ]");
}

void _print_sce_version(FILE *fp, sce_version_t *sv)
{
	fprintf(fp, "[*] SCE Version:\n");
	fprintf(fp, " Header Type 0x%08X\n", sv->header_type);
	fprintf(fp, " Present     [%s]\n", sv->present == SCE_VERSION_PRESENT ? "TRUE" : "FALSE");
	fprintf(fp, " Size        0x%08X\n", sv->size);
	fprintf(fp, " unknown_3   0x%08X\n", sv->unknown_3);
}

void _print_control_info(FILE *fp, control_info_t *ci)
{
	const char *name;

	fprintf(fp, "[*] Control Info\n");

	name = _get_name(_control_info_types, ci->type);
	if(name != NULL)
		fprintf(fp, " Type      %s\n", name);
	else
		fprintf(fp, " Type      0x%08X\n", ci->type);

	fprintf(fp, " Size      0x%08X\n", ci->size);
	fprintf(fp, " Next      [%s]\n", ci->next == 1 ? "TRUE" : "FALSE");

	switch(ci->type)
	{
	case CONTROL_INFO_TYPE_FLAGS:
		_hexdump(fp, " Flags", 0, (unsigned char *)ci + sizeof(control_info_t), ci->size - sizeof(control_info_t), FALSE);
		break;
	case CONTROL_INFO_TYPE_DIGEST:
		if(ci->size == 0x30)
		{
			ci_data_digest_30_t *dig = (ci_data_digest_30_t *)((unsigned char *)ci + sizeof(control_info_t));
			_hexdump(fp, " Digest", 0, dig->digest, 20, FALSE);
		}
		else if(ci->size == 0x40)
		{
			ci_data_digest_40_t *dig = (ci_data_digest_40_t *)((unsigned char *)ci + sizeof(control_info_t));
			_es_ci_data_digest_40(dig);
			_hexdump(fp, " Digest 1  ", 0, dig->digest1, 20, FALSE);
			_hexdump(fp, " Digest 2  ", 0, dig->digest2, 20, FALSE);
			if(dig->fw_version != 0)
				fprintf(fp, " FW Version %d [%02d.%02d]\n", (unsigned int)dig->fw_version, ((unsigned int)dig->fw_version)/10000, (((unsigned int)dig->fw_version)%10000)/100);
		}
		break;
	case CONTROL_INFO_TYPE_NPDRM:
		{
			ci_data_npdrm_t *np = (ci_data_npdrm_t *)((unsigned char *)ci + sizeof(control_info_t));
			//Was already fixed in decrypt_header.
			//_es_ci_data_npdrm(np);
			fprintf(fp, " Magic        0x%08X [%s]\n", np->magic, (np->magic == NP_CI_MAGIC ? "OK" : "ERROR"));
			fprintf(fp, " unknown_0    0x%08X\n", np->unknown_0);
			fprintf(fp, " Licence Type 0x%08X\n", np->license_type);
			fprintf(fp, " App Type     0x%08X\n", np->app_type);
			fprintf(fp, " ContentID    %s\n", np->content_id);
			_hexdump(fp, " Random Pad  ", 0, np->rndpad, 0x10, FALSE);
			_hexdump(fp, " CID_FN Hash ", 0, np->hash_cid_fname, 0x10, FALSE);
			_hexdump(fp, " CI Hash     ", 0, np->hash_ci, 0x10, FALSE);
			fprintf(fp, " unknown_1    0x%016llX\n", np->unknown_1);
			fprintf(fp, " unknown_2    0x%016llX\n", np->unknown_2);
		}
		break;
	}
}

static void _print_cap_flags_flags(FILE *fp, oh_data_cap_flags_t *cf)
{
	if(cf->flags & 0x01)
		fprintf(fp, "0x01 ");
	if(cf->flags & 0x02)
		fprintf(fp, "0x02 ");
	if(cf->flags & 0x04)
		fprintf(fp, "0x04 ");
	if(cf->flags & CAP_FLAG_REFTOOL)
		fprintf(fp, "REFTOOL ");
	if(cf->flags & CAP_FLAG_DEBUG)
		fprintf(fp, "DEBUG ");
	if(cf->flags & CAP_FLAG_RETAIL)
		fprintf(fp, "RETAIL ");
	if(cf->flags & CAP_FLAG_SYSDBG)
		fprintf(fp, "SYSDBG ");
}

void _print_opt_header(FILE *fp, opt_header_t *oh)
{
	const char *name;

	fprintf(fp, "[*] Optional Header\n");

	name = _get_name(_optional_header_types, oh->type);
	if(name != NULL)
		fprintf(fp, " Type      %s\n", name);
	else
		fprintf(fp, " Type      0x%08X\n", oh->type);

	fprintf(fp, " Size      0x%08X\n", oh->size);
	fprintf(fp, " Next      [%s]\n", oh->next == 1 ? "TRUE" : "FALSE");

	switch(oh->type)
	{
	case OPT_HEADER_TYPE_CAP_FLAGS:
		{
			oh_data_cap_flags_t *cf = (oh_data_cap_flags_t *)((unsigned char *)oh + sizeof(opt_header_t));

			_IF_RAW(_hexdump(fp, " Flags", 0, (unsigned char *)cf, sizeof(oh_data_cap_flags_t), FALSE));

			_es_oh_data_cap_flags(cf);

			fprintf(fp, " unknown_3 0x%016llX\n", cf->unk3);
			fprintf(fp, " unknown_4 0x%016llX\n", cf->unk4);

			fprintf(fp, " Flags     0x%016llX [ ", cf->flags);
			_print_cap_flags_flags(fp, cf);
			fprintf(fp, "]\n");
	
			fprintf(fp, " unknown_6 0x%08X\n", cf->unk6);
			fprintf(fp, " unknown_7 0x%08X\n", cf->unk7);
		}
		break;
#ifdef CONFIG_DUMP_INDIV_SEED
	case OPT_HEADER_TYPE_INDIV_SEED:
		{
			unsigned char *is = (unsigned char *)oh + sizeof(opt_header_t);
			_hexdump(fp, " Seed", 0, is, oh->size - sizeof(opt_header_t), TRUE);
		}
		break;
#endif
	}
}

void _print_elf32_ehdr(FILE *fp, Elf32_Ehdr *h)
{
	const char *name;

	fprintf(fp, "[*] ELF32 Header:\n");

	name = _get_name(_e_types, h->e_type);
	if(name != NULL)
		fprintf(fp, " Type                   [%s]\n", name);
	else
		fprintf(fp, " Type                   0x%04X\n", h->e_type);

	name = _get_name(_e_machines, h->e_machine);
	if(name != NULL)
		fprintf(fp, " Machine                [%s]\n", name);
	else
		fprintf(fp, " Machine                0x%04X\n", h->e_machine);
	
	fprintf(fp, " Version                0x%08X\n", h->e_version);
	fprintf(fp, " Entry                  0x%08X\n", h->e_entry);
	fprintf(fp, " Program Headers Offset 0x%08X\n", h->e_phoff);
	fprintf(fp, " Section Headers Offset 0x%08X\n", h->e_shoff);
	fprintf(fp, " Flags                  0x%08X\n", h->e_flags);
	fprintf(fp, " Program Headers Count  %04d\n", h->e_phnum);
	fprintf(fp, " Section Headers Count  %04d\n", h->e_shnum);
	fprintf(fp, " SH String Index        %04d\n", h->e_shstrndx);
}

void _print_elf64_ehdr(FILE *fp, Elf64_Ehdr *h)
{
	const char *name;

	fprintf(fp, "[*] ELF64 Header:\n");

	name = _get_name(_e_types, h->e_type);
	if(name != NULL)
		fprintf(fp, " Type                   [%s]\n", name);
	else
		fprintf(fp, " Type                   0x%04X\n", h->e_type);

	name = _get_name(_e_machines, h->e_machine);
	if(name != NULL)
		fprintf(fp, " Machine                [%s]\n", name);
	else
		fprintf(fp, " Machine                0x%04X\n", h->e_machine);
	
	fprintf(fp, " Version                0x%08X\n", h->e_version);
	fprintf(fp, " Entry                  0x%016llX\n", h->e_entry);
	fprintf(fp, " Program Headers Offset 0x%016llX\n", h->e_phoff);
	fprintf(fp, " Section Headers Offset 0x%016llX\n", h->e_shoff);
	fprintf(fp, " Flags                  0x%08X\n", h->e_flags);
	fprintf(fp, " Program Headers Count  %04d\n", h->e_phnum);
	fprintf(fp, " Section Headers Count  %04d\n", h->e_shnum);
	fprintf(fp, " SH String Index        %04d\n", h->e_shstrndx);
}

void _print_elf32_shdr_header(FILE *fp)
{
	fprintf(fp, "[*] ELF32 Section Headers:\n");
	fprintf(fp, " Idx Name Type          Flags Address Offset Size  ES Align LK\n");
}

void _print_elf32_shdr(FILE *fp, Elf32_Shdr *h, unsigned int idx)
{
	const char *name;
	char flags[4];

	_get_shdr_flags(flags, h->sh_flags);

	fprintf(fp, " %03d %04X ", idx, h->sh_name);

	name = _get_name(_sh_types, h->sh_type);
	if(name != NULL)
		fprintf(fp, "%-13s ", name);
	else
		fprintf(fp, "%08X      ", h->sh_type);

	fprintf(fp, "%s   %05X   %05X  %05X %02X %05X %03d\n", 
		flags, h->sh_addr, h->sh_offset, h->sh_size, h->sh_entsize, h->sh_addralign, h->sh_link);
}

void _print_elf64_shdr_header(FILE *fp)
{
	fprintf(fp, "[*] ELF64 Section Headers:\n");
	fprintf(fp, " Idx Name Type          Flags Address    Offset   Size     ES   Align    LK\n");
}

void _print_elf64_shdr(FILE *fp, Elf64_Shdr *h, unsigned int idx)
{
	const char *name;
	char flags[4];

	_get_shdr_flags(flags, h->sh_flags);

	fprintf(fp, " %03d %04X ", idx, h->sh_name);

	name = _get_name(_sh_types, h->sh_type);
	if(name != NULL)
		fprintf(fp, "%-13s ", name);
	else
		fprintf(fp, "%08X      ", h->sh_type);

	fprintf(fp, "%s   %08X   %08X %08X %04X %08X %03d\n", 
		flags, (unsigned int)h->sh_addr, (unsigned int)h->sh_offset, (unsigned int)h->sh_size, (unsigned int)h->sh_entsize, (unsigned int)h->sh_addralign, h->sh_link);
}

void _print_elf32_phdr_header(FILE *fp)
{
	fprintf(fp, "[*] ELF32 Program Headers:\n");
	fprintf(fp, " Idx Type     Offset VAddr PAddr FileSize MemSize Flags Align\n");
}

void _print_elf32_phdr(FILE *fp, Elf32_Phdr *h, unsigned int idx)
{
	const char *name;

	char flags[4];

	_get_phdr_flags(flags, h->p_flags);

	fprintf(fp, " %03d ", idx);

	name = _get_name(_ph_types, h->p_type);
	if(name != NULL)
		fprintf(fp, "%-7s  ", name);
	else
		fprintf(fp, "0x%08X ", h->p_type);

	fprintf(fp, "%05X  %05X %05X %05X    %05X   %s   %05X\n",
		h->p_offset, h->p_vaddr, h->p_paddr, h->p_filesz, h->p_memsz, flags, h->p_align);
}

void _print_elf64_phdr_header(FILE *fp)
{
	fprintf(fp, "[*] ELF64 Program Headers:\n");
	fprintf(fp, " Idx Type     Offset   VAddr    PAddr    FileSize MemSize  PPU SPU RSX Align\n");
}

void _print_elf64_phdr(FILE *fp, Elf64_Phdr *h, unsigned int idx)
{
	const char *name;

	char ppu[4], spu[4], rsx[4];

	_get_phdr_flags(ppu, h->p_flags);
	_get_phdr_flags(spu, h->p_flags >> 20);
	_get_phdr_flags(rsx, h->p_flags >> 24);

	fprintf(fp, " %03d ", idx);

	name = _get_name(_ph_types, h->p_type);
	if(name != NULL)
		fprintf(fp, "%-8s ", name);
	else
		fprintf(fp, "%08X ", h->p_type);

	fprintf(fp, "%08X %08X %08X %08X %08X %s %s %s %08X\n", 
		(unsigned int)h->p_offset, (unsigned int)h->p_vaddr, (unsigned int)h->p_paddr, (unsigned int)h->p_filesz, (unsigned int)h->p_memsz, ppu, spu, rsx, (unsigned int)h->p_align);
}

BOOL self_print_info(FILE *fp, sce_buffer_ctxt_t *ctxt)
{
	unsigned int i, self_type;
	const unsigned char *eident;

	//Check for SELF.
	if(ctxt->sceh->header_type != SCE_HEADER_TYPE_SELF)
		return FALSE;

	//Print SELF infos.
	_print_self_header(fp, ctxt->self.selfh);
	_print_app_info(fp, ctxt->self.ai);
	if(ctxt->self.sv != NULL)
		_print_sce_version(fp, ctxt->self.sv);

	//Print control infos.
	if(ctxt->self.cis != NULL)
		LIST_FOREACH(iter, ctxt->self.cis)
			_print_control_info(fp, (control_info_t *)iter->value);

	//Print optional headers.
	if(ctxt->mdec == TRUE)
	{
		LIST_FOREACH(iter, ctxt->self.ohs)
		{
#ifndef CONFIG_DUMP_INDIV_SEED
			if(((opt_header_t *)iter->value)->type != OPT_HEADER_TYPE_INDIV_SEED)
				_print_opt_header(fp, (opt_header_t *)iter->value);
#else
			_print_opt_header(fp, (opt_header_t *)iter->value);
#endif
		}
	}

	self_type = ctxt->self.ai->self_type;
	eident = ctxt->scebuffer + ctxt->self.selfh->elf_offset;

	//SPU is 32 bit.
	if(self_type == SELF_TYPE_LDR || self_type == SELF_TYPE_ISO || eident[EI_CLASS] == ELFCLASS32)
	{
		//32 bit ELF.
		Elf32_Ehdr *eh = (Elf32_Ehdr *)(ctxt->scebuffer + ctxt->self.selfh->elf_offset);
		_es_elf32_ehdr(eh);

		//Print section infos.
		_print_section_info_header(fp);
		for(i = 0; i < eh->e_phnum; i++)
		{
			_es_section_info(&ctxt->self.si[i]);
			_print_section_info(fp, &ctxt->self.si[i], i);
		}

		//Print ELF header.
		_print_elf32_ehdr(fp, eh);

		Elf32_Phdr *ph = (Elf32_Phdr *)(ctxt->scebuffer + ctxt->self.selfh->phdr_offset);

		//Print program headers.
		_print_elf32_phdr_header(fp);
		for(i = 0; i < eh->e_phnum; i++)
		{
			_es_elf32_phdr(&ph[i]);
			_print_elf32_phdr(fp, &ph[i], i);
		}

		if(eh->e_shnum > 0)
		{
			Elf32_Shdr *sh = (Elf32_Shdr *)(ctxt->scebuffer + ctxt->self.selfh->shdr_offset);

			//Print section headers.
			_print_elf32_shdr_header(fp);
			for(i = 0; i < eh->e_shnum; i++)
			{
				_es_elf32_shdr(&sh[i]);
				_print_elf32_shdr(fp, &sh[i], i);
			}
		}
	}
	else
	{
		//64 bit ELF.
		Elf64_Ehdr *eh = (Elf64_Ehdr *)(ctxt->scebuffer + ctxt->self.selfh->elf_offset);
		_es_elf64_ehdr(eh);

		//Print section infos.
		_print_section_info_header(fp);
		for(i = 0; i < eh->e_phnum; i++)
		{
			_es_section_info(&ctxt->self.si[i]);
			_print_section_info(fp, &ctxt->self.si[i], i);
		}

		//Print ELF header.
		_print_elf64_ehdr(stdout, eh);

		Elf64_Phdr *ph = (Elf64_Phdr *)(ctxt->scebuffer + ctxt->self.selfh->phdr_offset);

		//Print program headers.
		_print_elf64_phdr_header(fp);
		for(i = 0; i < eh->e_phnum; i++)
		{
			_es_elf64_phdr(&ph[i]);
			_print_elf64_phdr(fp, &ph[i], i);
		}

		if(eh->e_shnum > 0)
		{
			Elf64_Shdr *sh = (Elf64_Shdr *)(ctxt->scebuffer + ctxt->self.selfh->shdr_offset);

			//Print section headers.
			_print_elf64_shdr_header(fp);
			for(i = 0; i < eh->e_shnum; i++)
			{
				_es_elf64_shdr(&sh[i]);
				_print_elf64_shdr(fp, &sh[i], i);
			}
		}
	}

	return TRUE;
}

//TODO: maybe implement better.
BOOL self_write_to_elf(sce_buffer_ctxt_t *ctxt, const char *elf_out)
{
	FILE *fp;
	unsigned int i, self_type;

	const unsigned char *eident;

	//Check for SELF.
	if(ctxt->sceh->header_type != SCE_HEADER_TYPE_SELF)
		return FALSE;

	if((fp = fopen(elf_out, "wb")) == NULL)
		return FALSE;

	self_type = ctxt->self.ai->self_type;
	eident = ctxt->scebuffer + ctxt->self.selfh->elf_offset;

	//SPU is 32 bit.
	if(self_type == SELF_TYPE_LDR || self_type == SELF_TYPE_ISO || eident[EI_CLASS] == ELFCLASS32)
	{
#ifdef CONFIG_DUMP_INDIV_SEED
		/*
		//Print individuals seed.
		if(self_type == SELF_TYPE_ISO)
		{
			unsigned char *indiv_seed = (unsigned char *)ctxt->self.ish + sizeof(iseed_header_t);
			char ifile[256];
			sprintf(ifile, "%s.indiv_seed.bin", elf_out);
			FILE *ifp = fopen(ifile, "wb");
			fwrite(indiv_seed, sizeof(unsigned char), ctxt->self.ish->size - sizeof(iseed_header_t), ifp);
			fclose(ifp);
		}
		*/
#endif

		//32 bit ELF.
		Elf32_Ehdr ceh, *eh = (Elf32_Ehdr *)(ctxt->scebuffer + ctxt->self.selfh->elf_offset);
		_copy_es_elf32_ehdr(&ceh, eh);

		//Write ELF header.
		fwrite(eh, sizeof(Elf32_Ehdr), 1, fp);

		//Write program headers.
		Elf32_Phdr *ph = (Elf32_Phdr *)(ctxt->scebuffer + ctxt->self.selfh->phdr_offset);
		fwrite(ph, sizeof(Elf32_Phdr), ceh.e_phnum, fp);

		//Write program data.
		metadata_section_header_t *msh = ctxt->metash;
		for(i = 0; i < ctxt->metah->section_count; i++)
		{
			if(msh[i].type == METADATA_SECTION_TYPE_PHDR)
			{
				_es_elf32_phdr(&ph[msh[i].index]);
				fseek(fp, ph[msh[i].index].p_offset, SEEK_SET);
				fwrite(ctxt->scebuffer + msh[i].data_offset, sizeof(unsigned char), msh[i].data_size, fp);
			}
		}		

		//Write section headers.
		if(ctxt->self.selfh->shdr_offset != 0)
		{
			Elf32_Shdr *sh = (Elf32_Shdr *)(ctxt->scebuffer + ctxt->self.selfh->shdr_offset);
			fseek(fp, ceh.e_shoff, SEEK_SET);
			fwrite(sh, sizeof(Elf32_Shdr), ceh.e_shnum, fp);
		}
	}
	else
	{
		//64 bit ELF.
		Elf64_Ehdr ceh, *eh = (Elf64_Ehdr *)(ctxt->scebuffer + ctxt->self.selfh->elf_offset);
		_copy_es_elf64_ehdr(&ceh, eh);

		//Write ELF header.
		fwrite(eh, sizeof(Elf64_Ehdr), 1, fp);

		//Write program headers.
		Elf64_Phdr *ph = (Elf64_Phdr *)(ctxt->scebuffer + ctxt->self.selfh->phdr_offset);
		fwrite(ph, sizeof(Elf64_Phdr), ceh.e_phnum, fp);

		//Write program data.
		metadata_section_header_t *msh = ctxt->metash;
		for(i = 0; i < ctxt->metah->section_count; i++)
		{
			if(msh[i].type == METADATA_SECTION_TYPE_PHDR)
			{
				if(msh[i].compressed == METADATA_SECTION_COMPRESSED)
				{
					_es_elf64_phdr(&ph[msh[i].index]);
					unsigned char *data = (unsigned char *)malloc(ph[msh[i].index].p_filesz);

					_zlib_inflate(ctxt->scebuffer + msh[i].data_offset, msh[i].data_size, data, ph[msh[i].index].p_filesz);
					fseek(fp, ph[msh[i].index].p_offset, SEEK_SET);
					fwrite(data, sizeof(unsigned char), ph[msh[i].index].p_filesz, fp);

					free(data);
				}
				else
				{
					_es_elf64_phdr(&ph[msh[i].index]);
					fseek(fp, ph[msh[i].index].p_offset, SEEK_SET);
					fwrite(ctxt->scebuffer + msh[i].data_offset, sizeof(unsigned char), msh[i].data_size, fp);
				}
			}
		}		

		//Write section headers.
		if(ctxt->self.selfh->shdr_offset != 0)
		{
			Elf64_Shdr *sh = (Elf64_Shdr *)(ctxt->scebuffer + ctxt->self.selfh->shdr_offset);
			fseek(fp, ceh.e_shoff, SEEK_SET);
			fwrite(sh, sizeof(Elf64_Shdr), ceh.e_shnum, fp);
		}
	}

	fclose(fp);

	return TRUE;
}

/*! Static zero control flags. */
static unsigned char _static_control_flags[0x20] = 
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*! Static control digest1. */
static unsigned char _static_control_digest[0x14] = 
{
	0x62, 0x7C, 0xB1, 0x80, 0x8A, 0xB9, 0x38, 0xE3, 0x2C, 0x8C, 0x09, 0x17, 0x08, 0x72, 0x6A, 0x57, 0x9E, 0x25, 0x86, 0xE4
};

static BOOL _create_control_infos(sce_buffer_ctxt_t *ctxt, self_config_t *sconf)
{
	control_info_t *ci;
	unsigned int self_type = ctxt->self.ai->self_type;

	//Step 1.
	switch(self_type)
	{
	case SELF_TYPE_LV0:
	case SELF_TYPE_LV1:
	case SELF_TYPE_LV2:
	case SELF_TYPE_APP:
	case SELF_TYPE_ISO:
	case SELF_TYPE_LDR:
	case SELF_TYPE_NPDRM: //TODO: <-- figure more out.
		{
			//Add control flags.
			ci = (control_info_t *)malloc(sizeof(control_info_t) + sizeof(ci_data_flags_t));
			ci->type = CONTROL_INFO_TYPE_FLAGS;
			ci->size = sizeof(control_info_t) + sizeof(ci_data_flags_t);
			ci->next = 1;

			ci_data_flags_t *cif = (ci_data_flags_t *)((unsigned char *)ci + sizeof(control_info_t));

			//Add default flags.
			if(sconf->ctrl_flags == NULL)
				memcpy(cif->data, _static_control_flags, 0x20);
			else
				memcpy(cif->data, sconf->ctrl_flags, 0x20);

			list_add_back(ctxt->self.cis, ci);
		}
		break;
	}

	//Step 2.
	switch(self_type)
	{
	case SELF_TYPE_LV0:
	case SELF_TYPE_LV1:
	case SELF_TYPE_LV2:
	case SELF_TYPE_APP:
	case SELF_TYPE_ISO:
	case SELF_TYPE_LDR:
	case SELF_TYPE_NPDRM:
		{
			//Add digest 0x40.
			ci = (control_info_t *)malloc(sizeof(control_info_t) + sizeof(ci_data_digest_40_t));
			ci->type = CONTROL_INFO_TYPE_DIGEST;
			ci->size = sizeof(control_info_t) + sizeof(ci_data_digest_40_t);
			if(self_type == SELF_TYPE_NPDRM)
				ci->next = 1;
			else
				ci->next = 0;

			ci_data_digest_40_t *cid = (ci_data_digest_40_t *)((unsigned char *)ci + sizeof(control_info_t));
			memcpy(cid->digest1, _static_control_digest, 0x14);
			memset(cid->digest2, 0, 0x14);
			sha1(ctxt->makeself->elf, ctxt->makeself->elf_len, cid->digest2);

			//TODO: check that.
			if(self_type == SELF_TYPE_NPDRM)
				cid->fw_version = sce_hexver_to_decver(sconf->fw_version);
			else
				cid->fw_version = 0;

			//Fixup.
			_es_ci_data_digest_40(cid);
			
			list_add_back(ctxt->self.cis, ci);
		}
		break;
	}

	//Step 3.
	switch(self_type)
	{
	case SELF_TYPE_NPDRM:
		{
			//Add NPDRM control info.
			if(sconf->npdrm_config == NULL)
				return FALSE;

			ci = (control_info_t *)malloc(sizeof(control_info_t) + sizeof(ci_data_npdrm_t));
			ci->type = CONTROL_INFO_TYPE_NPDRM;
			ci->size = sizeof(control_info_t) + sizeof(ci_data_npdrm_t);
			ci->next = 0;

			ci_data_npdrm_t *cinp = (ci_data_npdrm_t *)((unsigned char *)ci + sizeof(control_info_t));

			//Create NPDRM control info.
			if(np_create_ci(sconf->npdrm_config, cinp) == FALSE)
			{
				free(ci);
				return FALSE;
			}

			list_add_back(ctxt->self.cis, ci);
		}
		break;
	}

	return TRUE;
}

static void _set_cap_flags(unsigned int self_type, oh_data_cap_flags_t *capf)
{
	switch(self_type)
	{
	case SELF_TYPE_LV0:
		capf->flags = CAP_FLAG_SYSDBG | CAP_FLAG_RETAIL | CAP_FLAG_DEBUG | CAP_FLAG_REFTOOL | 0x3; //0x7B;
		capf->unk6 = 1;
		break;
	case SELF_TYPE_LV1:
		capf->flags = CAP_FLAG_SYSDBG | CAP_FLAG_RETAIL | CAP_FLAG_DEBUG | CAP_FLAG_REFTOOL | 0x3; //0x7B;
		capf->unk6 = 1;
		break;
	case SELF_TYPE_LV2:
		capf->flags = CAP_FLAG_SYSDBG | CAP_FLAG_RETAIL | CAP_FLAG_DEBUG | CAP_FLAG_REFTOOL | 0x3; //0x7B;
		capf->unk6 = 1;
		break;
	case SELF_TYPE_APP:
		capf->flags = CAP_FLAG_SYSDBG | CAP_FLAG_RETAIL | CAP_FLAG_DEBUG | CAP_FLAG_REFTOOL | 0x3; //0x7B;
		capf->unk6 = 1;
		capf->unk7 = 0x20000;
		break;
	case SELF_TYPE_ISO:
		capf->flags = CAP_FLAG_SYSDBG | CAP_FLAG_RETAIL | CAP_FLAG_DEBUG | CAP_FLAG_REFTOOL; //0x78;
		break;
	case SELF_TYPE_LDR:
		capf->flags = CAP_FLAG_SYSDBG | CAP_FLAG_RETAIL | CAP_FLAG_DEBUG | CAP_FLAG_REFTOOL; //0x78;
		break;
	case SELF_TYPE_NPDRM:
		capf->flags = CAP_FLAG_RETAIL | CAP_FLAG_DEBUG | CAP_FLAG_REFTOOL | 0x3; //0x3B;
		capf->unk6 = 1;
		capf->unk7 = 0x2000;
		break;
	}

	_es_oh_data_cap_flags(capf);
}

static BOOL _create_optional_headers(sce_buffer_ctxt_t *ctxt, self_config_t *sconf)
{
	opt_header_t *oh;
	unsigned int self_type = ctxt->self.ai->self_type;

	//Step 1.
	switch(self_type)
	{
	case SELF_TYPE_LV0:
	case SELF_TYPE_LV1:
	case SELF_TYPE_LV2:
	case SELF_TYPE_APP:
	case SELF_TYPE_ISO:
	case SELF_TYPE_LDR:
	case SELF_TYPE_NPDRM:
		{
			//Add capability flags.
			oh = (opt_header_t *)malloc(sizeof(opt_header_t) + sizeof(oh_data_cap_flags_t));
			oh->type = OPT_HEADER_TYPE_CAP_FLAGS;
			oh->size = sizeof(opt_header_t) + sizeof(oh_data_cap_flags_t);
			if(self_type == SELF_TYPE_ISO)
				oh->next = 1;
			else
				oh->next = 0;

			oh_data_cap_flags_t *capf = (oh_data_cap_flags_t *)((unsigned char *)oh + sizeof(opt_header_t));

			//Add default flags.
			if(sconf->cap_flags == NULL)
				_set_cap_flags(self_type, capf);
			else
				memcpy(capf, sconf->cap_flags, 0x20);
			
			list_add_back(ctxt->self.ohs, oh);
		}
		break;
	}

	//Step 2.
	switch(self_type)
	{
	case SELF_TYPE_ISO:
		{
			//Add individuals seed.
			oh = (opt_header_t *)malloc(sizeof(opt_header_t) + 0x100);
			oh->type = OPT_HEADER_TYPE_INDIV_SEED;
			oh->size = sizeof(opt_header_t) + 0x100;
			oh->next = 0;

			unsigned char *is = (unsigned char *)oh + sizeof(opt_header_t);
			memset(is, 0, 0x100);
#ifdef CONFIG_CUSTOM_INDIV_SEED
			if(sconf->indiv_seed != NULL)
				memcpy(is, sconf->indiv_seed, sconf->indiv_seed_size);
#endif
			
			list_add_back(ctxt->self.ohs, oh);
		}
		break;
	}

	return TRUE;
}

static void _fill_sce_version(sce_buffer_ctxt_t *ctxt)
{
	ctxt->self.sv->header_type = SUB_HEADER_TYPE_SCEVERSION;
	ctxt->self.sv->present = SCE_VERSION_NOT_PRESENT;
	ctxt->self.sv->size = sizeof(sce_version_t);
	ctxt->self.sv->unknown_3 = 0x00000000;
}

static void _add_phdr_section(sce_buffer_ctxt_t *ctxt, unsigned int p_type, unsigned int size, unsigned int idx)
{
	//Offset gets set later.
	ctxt->self.si[idx].offset = 0;
	ctxt->self.si[idx].size = size;

	if(p_type == PT_LOAD || p_type == PT_PS3_PRX_RELOC || p_type == 0x700000A8)
		ctxt->self.si[idx].encrypted = 1; //Encrypted LOAD (?).
	else
		ctxt->self.si[idx].encrypted = 0; //No LOAD (?).

	ctxt->self.si[idx].compressed = SECTION_INFO_NOT_COMPRESSED;
	ctxt->self.si[idx].unknown_0 = 0; //Unknown.
	ctxt->self.si[idx].unknown_1 = 0; //Unknown.
}

static BOOL _add_shdrs_section(sce_buffer_ctxt_t *ctxt, unsigned int idx)
{
	//Add a section for the section headers.
	if(ctxt->makeself->shdrs != NULL)
	{
		unsigned int shsize = ctxt->makeself->shsize;
		void *sec = _memdup(ctxt->makeself->shdrs, shsize);
		sce_add_data_section(ctxt, sec, shsize, FALSE);

		//Fill metadata section header.
		sce_set_metash(ctxt, METADATA_SECTION_TYPE_SHDR, FALSE, idx);

		return TRUE;
	}

	return FALSE;
}

static BOOL _build_self_32(sce_buffer_ctxt_t *ctxt, self_config_t *sconf)
{
	unsigned int i;

	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdrs;
	//Elf32_Shdr *shdrs;

	//Copy ELF header.
	ctxt->makeself->ehdr = (Elf32_Ehdr *)_memdup(ctxt->makeself->elf, sizeof(Elf32_Ehdr));
	ctxt->makeself->ehsize = sizeof(Elf32_Ehdr);
	ehdr = (Elf32_Ehdr *)_memdup(ctxt->makeself->elf, sizeof(Elf32_Ehdr));
	_es_elf32_ehdr(ehdr);

	//Copy program headers.
	ctxt->makeself->phdrs = (Elf32_Phdr *)_memdup(ctxt->makeself->elf + ehdr->e_phoff, sizeof(Elf32_Phdr) * ehdr->e_phnum);
	ctxt->makeself->phsize = sizeof(Elf32_Phdr) * ehdr->e_phnum;
	phdrs = (Elf32_Phdr *)_memdup(ctxt->makeself->elf + ehdr->e_phoff, sizeof(Elf32_Phdr) * ehdr->e_phnum);

	//Copy section headers.
	if(ehdr->e_shnum != 0)
	{
		ctxt->makeself->shdrs = (Elf32_Shdr *)_memdup(ctxt->makeself->elf + ehdr->e_shoff, sizeof(Elf32_Shdr) * ehdr->e_shnum);
		ctxt->makeself->shsize = sizeof(Elf32_Shdr) * ehdr->e_shnum;
		//shdrs = (Elf32_Shdr *)_memdup(ctxt->makeself->elf + ehdr->e_shoff, sizeof(Elf32_Shdr) * ehdr->e_shnum);
	}

	//Allocate metadata section headers (one for each program header and one for the section headers).
	ctxt->metash = (metadata_section_header_t *)malloc(sizeof(metadata_section_header_t) * (ehdr->e_phnum + 1));

	//Copy sections, fill section infos and metadata section headers.
	ctxt->self.si = (section_info_t *)malloc(sizeof(section_info_t) * ehdr->e_phnum);
	for(i = 0; i < ehdr->e_phnum; i++)
	{
		_es_elf32_phdr(&phdrs[i]);
		void *sec = _memdup(ctxt->makeself->elf + phdrs[i].p_offset, phdrs[i].p_filesz);
		//Never compress sections on SPU SELFs.
		sce_add_data_section(ctxt, sec, phdrs[i].p_filesz, FALSE);

		//Add section info.
		_add_phdr_section(ctxt, phdrs[i].p_type, phdrs[i].p_filesz, i);
		//Fill metadata section header.
		sce_set_metash(ctxt, METADATA_SECTION_TYPE_PHDR, phdrs[i].p_type == PT_LOAD ? TRUE : FALSE, i);
	}

	//Section info count.
	ctxt->makeself->si_cnt = ehdr->e_phnum;
	//Number of section infos that are present as data sections.
	ctxt->makeself->si_sec_cnt = ehdr->e_phnum;

	//Add a section for the section headers.
	if(sconf->add_shdrs == TRUE)
		if(_add_shdrs_section(ctxt, i) == TRUE)
			i++;

	//Metadata.
	ctxt->metah->section_count = i;

	return TRUE;
}

static BOOL _build_self_64(sce_buffer_ctxt_t *ctxt, self_config_t *sconf)
{
	unsigned int i;
	
	Elf64_Ehdr *ehdr;
	Elf64_Phdr *phdrs=NULL;
	//Elf64_Shdr *shdrs;

	//Copy ELF header.
	ctxt->makeself->ehdr = (Elf64_Ehdr *)_memdup(ctxt->makeself->elf, sizeof(Elf64_Ehdr));
	ctxt->makeself->ehsize = sizeof(Elf64_Ehdr);
	ehdr = (Elf64_Ehdr *)_memdup(ctxt->makeself->elf, sizeof(Elf64_Ehdr));
	_es_elf64_ehdr(ehdr);
	
	//Copy program headers.
	ctxt->makeself->phdrs = (Elf64_Phdr *)_memdup(ctxt->makeself->elf + ehdr->e_phoff , sizeof(Elf64_Phdr) * ehdr->e_phnum);
	ctxt->makeself->phsize = sizeof(Elf64_Phdr) * ehdr->e_phnum;
	phdrs = (Elf64_Phdr *)_memdup(ctxt->makeself->elf + ehdr->e_phoff, sizeof(Elf64_Phdr) * ehdr->e_phnum);
	
	//Copy section headers.
	if(ehdr->e_shnum != 0)
	{
		ctxt->makeself->shdrs = (Elf64_Shdr *)_memdup(ctxt->makeself->elf + ehdr->e_shoff , sizeof(Elf64_Shdr) * ehdr->e_shnum);
		ctxt->makeself->shsize = sizeof(Elf64_Shdr) * ehdr->e_shnum;
		//shdrs = (Elf64_Shdr *)_memdup(ctxt->makeself->elf + ehdr->e_shoff, sizeof(Elf64_Shdr) * ehdr->e_shnum);
	}
	
	//Allocate metadata section headers (one for each program header and one for the section headers).
	ctxt->metash = (metadata_section_header_t *)malloc(sizeof(metadata_section_header_t) * (ehdr->e_phnum + 1));
	
	//Copy sections, fill section infos and metadata section headers.
	ctxt->self.si = (section_info_t *)malloc(sizeof(section_info_t) * ehdr->e_phnum);
	unsigned int loff = 0xFFFFFFFF, skip = 0;
	for(i = 0; i < ehdr->e_phnum; i++)
	{
		//_es_elf64_phdr(&phdrs[i]);

		//Add section info.
		_add_phdr_section(ctxt, phdrs[i].p_type, phdrs[i].p_filesz, i);

		//TODO: what if the size differs, why skip other program headers?
		//Fill metadata section header but skip identical program header offsets.
		if(sconf->skip_sections == TRUE && (phdrs[i].p_offset == loff || !(phdrs[i].p_type == PT_LOAD || phdrs[i].p_type == PT_PS3_PRX_RELOC || phdrs[i].p_type == 0x700000A8)))
		{
			const char *name = _get_name(_ph_types, phdrs[i].p_type);
			if(name != NULL)
				_LOG_VERBOSE("Skipped program header %-8s @ 0x%08X (0x%08X)\n", name, (unsigned int) phdrs[i].p_offset, (unsigned int) phdrs[i].p_filesz);
			else
				_LOG_VERBOSE("Skipped program header 0x%08X @ 0x%08X (0x%08X)\n", (unsigned int) phdrs[i].p_type,(unsigned int) phdrs[i].p_offset,(unsigned int) phdrs[i].p_filesz);
			skip++;
		}
		else
		{
			void *sec = _memdup(ctxt->makeself->elf + phdrs[i].p_offset, phdrs[i].p_filesz);
			//PPU sections may be compressed.
			sce_add_data_section(ctxt, sec, phdrs[i].p_filesz, TRUE);
			sce_set_metash(ctxt, METADATA_SECTION_TYPE_PHDR, TRUE /*(phdrs[i].p_type == PT_LOAD || phdrs[i].p_type == PT_PS3_PRX_RELOC || phdrs[i].p_type == 0x700000A8) ? TRUE : FALSE*/, i - skip);
		}

		loff = phdrs[i].p_offset;
	}
	
	//Section info count.
	ctxt->makeself->si_cnt = ehdr->e_phnum;
	//Number of section infos that are present as data sections.
	ctxt->makeself->si_sec_cnt = i - skip;
	
	//Add a section for the section headers.
	if(sconf->add_shdrs == TRUE)
		if(_add_shdrs_section(ctxt, i - skip) == TRUE)
			i++;
	//Metadata.
	i -= skip;
	ctxt->metah->section_count = i;
	
	return TRUE;
}

BOOL self_build_self(sce_buffer_ctxt_t *ctxt, self_config_t *sconf)
{
	//const unsigned char *eident;

	//Fill config values.
	ctxt->sceh->key_revision = sconf->key_revision;
	ctxt->self.ai->auth_id = sconf->auth_id;
	ctxt->self.ai->vendor_id = sconf->vendor_id;
	ctxt->self.ai->self_type = sconf->self_type;
	ctxt->self.ai->version = sconf->app_version;

	//Create control infos.
	if(_create_control_infos(ctxt, sconf) == FALSE)
	{
		printf("[*] Error: Could not create SELF control infos.\n");
		return FALSE;
	}

#ifdef CONFIG_CUSTOM_INDIV_SEED
	if(sconf->indiv_seed != NULL && sconf->self_type != SELF_TYPE_ISO)
		printf("[*] Warning: Skipping individuals seed for non-ISO SELF.\n");
#endif

	//Create optional headers.
	if(_create_optional_headers(ctxt, sconf) == FALSE)
	{
		printf("[*] Error: Could not create SELF optional headers.\n");
		return FALSE;
	}

	//Set SCE version.
	_fill_sce_version(ctxt);
	
	//Check for 32 bit or 64 bit ELF.
	//eident = (const unsigned char*)ctxt->makeself->elf;
	if(sconf->self_type == SELF_TYPE_LDR || sconf->self_type == SELF_TYPE_ISO /*|| eident[EI_CLASS] == ELFCLASS32*/) 	return _build_self_32(ctxt, sconf);
	return _build_self_64(ctxt, sconf);
}
