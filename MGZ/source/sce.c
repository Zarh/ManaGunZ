/*
* Copyright (c) 2011-2013 by naehrwert
* Copyright (c) 2011-2012 by Youness Alaoui <kakaroto@kakaroto.homelinux.net>
* This file is released under the GPLv2.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "util.h"
#include "elf.h"
#include "sce.h"
#include "sce_inlines.h"
#include "keys.h"
#include "aes.h"
#include "sha1.h"
#include "ecdsa.h"
#include "tables.h"
#include "config.h"
#include "zlib.h"
#include "np.h"

void _print_sce_header(FILE *fp, sce_header_t *h)
{
	const char *name;
	//const char *key_revision;

	fprintf(fp, "[*] SCE Header:\n");
	fprintf(fp, " Magic           0x%08X [%s]\n", h->magic, (h->magic == SCE_HEADER_MAGIC ? "OK" : "ERROR"));
	fprintf(fp, " Version         0x%08X\n", h->version);
	
	if(h->key_revision == KEY_REVISION_DEBUG)
		fprintf(fp, " Key Revision    [DEBUG]\n");
	else
		fprintf(fp, " Key Revision    0x%04X\n", h->key_revision);
	
	name = _get_name(_sce_header_types, h->header_type);
	if(name != NULL)
		fprintf(fp, " Header Type     [%s]\n", name);
	else
		fprintf(fp, " Header Type     0x%04X\n", h->header_type);

	fprintf(fp, " Metadata Offset 0x%08X\n", h->metadata_offset);
	fprintf(fp, " Header Length   0x%016llX\n", h->header_len);
	fprintf(fp, " Data Length     0x%016llX\n", h->data_len);
}

void _print_metadata_info(FILE *fp, metadata_info_t *mi)
{
	fprintf(fp, "[*] Metadata Info:\n");
	_hexdump(fp, " Key", 0, mi->key, METADATA_INFO_KEY_LEN, FALSE);
	_hexdump(fp, " IV ", 0, mi->iv, METADATA_INFO_IV_LEN, FALSE);
}

void _print_metadata_header(FILE *fp, metadata_header_t *mh)
{
	fprintf(fp, "[*] Metadata Header:\n");
	fprintf(fp, " Signature Input Length 0x%016llX\n", mh->sig_input_length);
	fprintf(fp, " unknown_0              0x%08X\n", mh->unknown_0);
	fprintf(fp, " Section Count          0x%08X\n", mh->section_count);
	fprintf(fp, " Key Count              0x%08X\n", mh->key_count);
	fprintf(fp, " Optional Header Size   0x%08X\n", mh->opt_header_size);
	fprintf(fp, " unknown_1              0x%08X\n", mh->unknown_1);
	fprintf(fp, " unknown_2              0x%08X\n", mh->unknown_2);
}

static void _print_metadata_section_header_header(FILE *fp)
{
	fprintf(fp, "[*] Metadata Section Headers:\n");
	fprintf(fp, " Idx Offset   Size     Type Index Hashed SHA1 Encrypted Key IV Compressed\n");
}

void _print_metadata_section_header(FILE *fp, metadata_section_header_t *msh, unsigned int idx)
{
	fprintf(fp, " %03d %08llX %08llX %02X   %02X    ", 
		idx, msh->data_offset, msh->data_size, msh->type, msh->index);

	if(msh->hashed == METADATA_SECTION_HASHED)
		fprintf(fp, "[YES]  %02X   ", msh->sha1_index);
	else
		fprintf(fp, "[NO ]  --   ");

	if(msh->encrypted == METADATA_SECTION_ENCRYPTED)
		fprintf(fp, "[YES]     %02X  %02X ", msh->key_index, msh->iv_index);
	else
		fprintf(fp, "[NO ]     --  -- ");

	if(msh->compressed == METADATA_SECTION_COMPRESSED)
		fprintf(fp, "[YES]\n");
	else
		fprintf(fp, "[NO ]\n");
}

void _print_sce_file_keys(FILE *fp, sce_buffer_ctxt_t *ctxt)
{
	unsigned int i;

	//Get start of keys.
	unsigned char *keys = (unsigned char *)ctxt->metash + sizeof(metadata_section_header_t) * ctxt->metah->section_count;

	fprintf(fp, "[*] SCE File Keys:\n");
	for(i = 0; i < ctxt->metah->key_count; i++)
	{
		fprintf(fp, " %02X:", i);
		_hexdump(fp, "", i, keys+i*0x10, 0x10, FALSE);
	}
}

static sce_buffer_ctxt_t *_sce_create_ctxt()
{
	sce_buffer_ctxt_t *res;

	if((res = (sce_buffer_ctxt_t *)malloc(sizeof(sce_buffer_ctxt_t))) == NULL)
		return NULL;

	memset(res, 0, sizeof(sce_buffer_ctxt_t));

	res->scebuffer = NULL;
	res->mdec = TRUE;

	//Allocate SCE header.
	res->sceh = (sce_header_t *)malloc(sizeof(sce_header_t));
	memset(res->sceh, 0, sizeof(sce_header_t));

	//Allocate metadata info (with random key/iv).
	res->metai = (metadata_info_t *)malloc(sizeof(metadata_info_t));
	_fill_rand_bytes(res->metai->key, 0x10);
	memset(res->metai->key_pad, 0, 0x10);
	_fill_rand_bytes(res->metai->iv, 0x10);
	memset(res->metai->iv_pad, 0, 0x10);
	//Allocate metadata header.
	res->metah = (metadata_header_t *)malloc(sizeof(metadata_header_t));
	//memset(res->metah, 0, sizeof(metadata_header_t));
	//Allocate signature.
	res->sig = (signature_t *)malloc(sizeof(signature_t));

	res->makeself = NULL;

	return res;
}

sce_buffer_ctxt_t *sce_create_ctxt_from_buffer(unsigned char *scebuffer)
{
	sce_buffer_ctxt_t *res;

	if((res = (sce_buffer_ctxt_t *)malloc(sizeof(sce_buffer_ctxt_t))) == NULL)
		return NULL;

	memset(res, 0, sizeof(sce_buffer_ctxt_t));

	res->scebuffer = scebuffer;
	res->mdec = FALSE;

	//Set pointer to SCE header.
	res->sceh = (sce_header_t *)scebuffer;
	_es_sce_header(res->sceh);

	//Set pointers to file type specific headers.
	switch(res->sceh->header_type)
	{
		case SCE_HEADER_TYPE_SELF:
		{
			//SELF header.
			res->self.selfh = (self_header_t *)(res->scebuffer + sizeof(sce_header_t));
			_es_self_header(res->self.selfh);

			//Application info.
			res->self.ai = (app_info_t *)(res->scebuffer + res->self.selfh->app_info_offset);
			_es_app_info(res->self.ai);

			//Section infos.
			res->self.si = (section_info_t *)(res->scebuffer + res->self.selfh->section_info_offset);

			//SCE version.
			if(res->self.selfh->sce_version_offset != 0)
			{
				res->self.sv = (sce_version_t *)(res->scebuffer + res->self.selfh->sce_version_offset);
				_es_sce_version(res->self.sv);
			}
			else
				res->self.sv = 0;

			//Get pointers to all control infos.
			unsigned int len = (unsigned int)res->self.selfh->control_info_size;
			if(len > 0)
			{
				unsigned char *ptr = res->scebuffer + res->self.selfh->control_info_offset;
				res->self.cis = list_create();

				while(len > 0)
				{
					control_info_t *tci = (control_info_t *)ptr;
					_es_control_info(tci);
					ptr += tci->size;
					len -= tci->size;
					list_add_back(res->self.cis, tci);
				}
			}
			else
				res->self.cis = NULL;
		}
		break;
	case SCE_HEADER_TYPE_RVK:
		//TODO
		break;
	case SCE_HEADER_TYPE_PKG:
		//TODO
		break;
	case SCE_HEADER_TYPE_SPP:
		//TODO
		break;
	default:
		free(res);
		return NULL;
		break;
	}

	//Set pointers to metadata headers.
	res->metai = (metadata_info_t *)(scebuffer + sizeof(sce_header_t) + res->sceh->metadata_offset);
	res->metah = (metadata_header_t *)((unsigned char *)res->metai + sizeof(metadata_info_t));
	res->metash = (metadata_section_header_t *)((unsigned char *)res->metah + sizeof(metadata_header_t));

	return res;
}

sce_buffer_ctxt_t *sce_create_ctxt_build_self(unsigned char *elf, unsigned int elf_len)
{
	sce_buffer_ctxt_t *res;

	if((res = _sce_create_ctxt()) == NULL)
		return NULL;

	res->sceh->magic = SCE_HEADER_MAGIC;
	res->sceh->version = SCE_HEADER_VERSION_2;
	res->sceh->header_type = SCE_HEADER_TYPE_SELF;

	//Allocate SELF header.
	res->self.selfh = (self_header_t *)malloc(sizeof(self_header_t));
	memset(res->self.selfh, 0, sizeof(self_header_t));
	res->self.selfh->header_type = SUB_HEADER_TYPE_SELF;
	//Allocate application info.
	res->self.ai = (app_info_t *)malloc(sizeof(app_info_t));
	memset(res->self.ai, 0, sizeof(app_info_t));
	//SCE version.
	res->self.sv = (sce_version_t *)malloc(sizeof(sce_version_t));
	//Create control info list.
	res->self.cis = list_create();
	//Create optional headers list.
	res->self.ohs = list_create();

	//Makeself context.
	res->makeself = (makeself_ctxt_t *)malloc(sizeof(makeself_ctxt_t));
	memset(res->makeself, 0, sizeof(makeself_ctxt_t));
	//ELF buffer.
	res->makeself->elf = elf;
	res->makeself->elf_len = elf_len;

	//Section list.
	res->secs = list_create();

	return res;
}

void sce_add_data_section(sce_buffer_ctxt_t *ctxt, void *buffer, unsigned int size, BOOL may_compr)
{
	sce_section_ctxt_t *sctxt = (sce_section_ctxt_t *)malloc(sizeof(sce_section_ctxt_t));
	sctxt->buffer = buffer;
	sctxt->size = size;
	sctxt->may_compr = may_compr;
	list_add_back(ctxt->secs, sctxt);
}

void sce_set_metash(sce_buffer_ctxt_t *ctxt, unsigned int type, BOOL encrypted, unsigned int idx)
{
	ctxt->metash[idx].type = type;
	ctxt->metash[idx].index = (type == METADATA_SECTION_TYPE_PHDR ? idx : type == METADATA_SECTION_TYPE_SHDR ? idx + 1 : idx);
	ctxt->metash[idx].hashed = METADATA_SECTION_HASHED;
	ctxt->metash[idx].encrypted = (encrypted == TRUE ? METADATA_SECTION_ENCRYPTED : METADATA_SECTION_NOT_ENCRYPTED);
	ctxt->metash[idx].compressed = METADATA_SECTION_NOT_COMPRESSED;
}

void sce_compress_data(sce_buffer_ctxt_t *ctxt)
{
	unsigned int i = 0;
	uLongf size_comp, size_bound;

	LIST_FOREACH(iter, ctxt->secs)
	{
		sce_section_ctxt_t *sec = (sce_section_ctxt_t *)iter->value;
		
		//Check if the section may be compressed.
		if(sec->may_compr == TRUE)
		{
			if(sec->size > 0)
			{
				size_comp = size_bound = compressBound(sec->size);
				unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * size_bound);
				compress(buf, &size_comp, (const unsigned char *)sec->buffer, sec->size);

				if(size_comp < sec->size)
				{
					//Set compressed buffer and size.
					sec->buffer = buf;
					sec->size = size_comp;

					//Set compression in section info.
					if(ctxt->sceh->header_type == SCE_HEADER_TYPE_SELF && i < ctxt->makeself->si_sec_cnt)
					{
						ctxt->self.si[i].compressed = SECTION_INFO_COMPRESSED;
						//Update size too.
						ctxt->self.si[i].size = size_comp;
					}

					//Set compression in maetadata section header.
					ctxt->metash[i].compressed = METADATA_SECTION_COMPRESSED;
				}
				else
				{
					free(buf);
					_LOG_VERBOSE("Skipped compression of section %03d (0x%08X >= 0x%08X)\n", i, (unsigned int) size_comp, (unsigned int) sec->size);
				}
			}
			else
				_LOG_VERBOSE("Skipped compression of section %03d (size is zero)\n", i);
		}

		i++;
	}
}

static unsigned int _sce_get_ci_len(sce_buffer_ctxt_t *ctxt)
{
	unsigned int res = 0;

	LIST_FOREACH(iter, ctxt->self.cis)
		res += ((control_info_t *)iter->value)->size;

	return res;
}

static unsigned int _sce_get_oh_len(sce_buffer_ctxt_t *ctxt)
{
	unsigned int res = 0;

	LIST_FOREACH(iter, ctxt->self.ohs)
		res += ((opt_header_t *)iter->value)->size;

	return res;
}

void _sce_fixup_ctxt(sce_buffer_ctxt_t *ctxt)
{
	unsigned int i = 0, base_off, last_off = 0;

	//Set section info data.
	base_off = ctxt->sceh->header_len;
	LIST_FOREACH(iter, ctxt->secs)
	{
		//Save last offset.
		last_off = base_off;

		//Section offsets.
		sce_section_ctxt_t *sec = (sce_section_ctxt_t *)iter->value;
		sec->offset = base_off;

		//Section infos for SELF (that are present as data sections).
		if(ctxt->sceh->header_type == SCE_HEADER_TYPE_SELF && i < ctxt->makeself->si_sec_cnt)
		//{
			ctxt->self.si[i].offset = base_off;
		//	ctxt->self.si[i].size = sec->size;
		//}

		//Metadata section headers.
		ctxt->metash[i].data_offset = base_off;
		ctxt->metash[i].data_size = sec->size;

		//Update offset and data length.
		base_off += sec->size;
		ctxt->sceh->data_len = base_off - ctxt->sceh->header_len;
		base_off = ALIGN(base_off, SCE_ALIGN);

		i++;
	}

	//Set metadata offset (counted from after SCE header).
	ctxt->sceh->metadata_offset = ctxt->off_metai - sizeof(sce_header_t);

	//Set metadata header values.
	ctxt->metah->sig_input_length = ctxt->off_sig;
	ctxt->metah->unknown_0 = 1;
	ctxt->metah->opt_header_size = _sce_get_oh_len(ctxt);
	ctxt->metah->unknown_1 = 0;
	ctxt->metah->unknown_2 = 0;

	switch(ctxt->sceh->header_type)
	{
	case SCE_HEADER_TYPE_SELF:
		{
			//Set header offsets.
			ctxt->self.selfh->app_info_offset = ctxt->off_self.off_ai;
			ctxt->self.selfh->elf_offset = ctxt->off_self.off_ehdr;
			ctxt->self.selfh->phdr_offset = ctxt->off_self.off_phdr;
			ctxt->self.selfh->section_info_offset = ctxt->off_self.off_si;
			ctxt->self.selfh->sce_version_offset = ctxt->off_self.off_sv;
			ctxt->self.selfh->control_info_offset = ctxt->off_self.off_cis;
			ctxt->self.selfh->control_info_size = _sce_get_ci_len(ctxt);

			//Set section headers offset in SELF header (last data section) if available.
			if(ctxt->makeself->shdrs != NULL)
				ctxt->self.selfh->shdr_offset = last_off;
			else
				ctxt->self.selfh->shdr_offset = 0;
		}
		break;
	case SCE_HEADER_TYPE_RVK:
		//TODO
		break;
	case SCE_HEADER_TYPE_PKG:
		//TODO
		break;
	case SCE_HEADER_TYPE_SPP:
		//TODO
		break;
	default:
		//TODO
		break;
	}
}

void _sce_fixup_keys(sce_buffer_ctxt_t *ctxt)
{
	unsigned int i;

	//Build keys array.
	ctxt->keys_len = 0;
	ctxt->metah->key_count = 0;
	for(i = 0; i < ctxt->metah->section_count; i++)
	{
		if(ctxt->metash[i].encrypted == METADATA_SECTION_ENCRYPTED)
		{
			ctxt->keys_len += 0x80; //0x60 HMAC, 0x20 key/iv
			ctxt->metah->key_count += 8;
			ctxt->metash[i].sha1_index = ctxt->metah->key_count - 8;
			ctxt->metash[i].key_index = ctxt->metah->key_count - 2;
			ctxt->metash[i].iv_index = ctxt->metah->key_count - 1;
		}
		else
		{
			ctxt->keys_len += 0x60; //0x60 HMAC
			ctxt->metah->key_count += 6;
			ctxt->metash[i].sha1_index = ctxt->metah->key_count - 6;
			ctxt->metash[i].key_index = 0xFFFFFFFF;
			ctxt->metash[i].iv_index = 0xFFFFFFFF;
		}
	}

	//Allocate and fill keys array.
	ctxt->keys = (unsigned char *)malloc(sizeof(unsigned char) * ctxt->keys_len);
	_fill_rand_bytes(ctxt->keys, ctxt->keys_len);

#ifndef CONFIG_PRIVATE_BUILD
	time_t rawtime;
	struct tm *ti;
	char buf[16+1];

	time(&rawtime);
	ti = localtime(&rawtime);
	sprintf(buf, "%02d%02d%02d::%02d%02d%04d", 
		ti->tm_hour, ti->tm_min, ti->tm_sec, 
		ti->tm_mday, ti->tm_mon, ti->tm_year+1900);

	memcpy(ctxt->keys + 0x20, "SURPRIZE :D "/**/, 12);
	memcpy(ctxt->keys + 0x30, "IM IN UR KEYZ !!", 16);
	unsigned char foo[16] = {0x09, 0xB8, 0xBE, 0xAE, 0x83, 0xC0, 0x17, 0xA6, 0x3B, 0x11, 0xB0, 0x50, 0xC4, 0xCE, 0xED, 0xF9};
	memcpy(ctxt->keys + 0x40, foo, 16);
	memcpy(ctxt->keys + 0x50, buf, 16);
#endif
}

/*! Increase offset and align it. */
#define _INC_OFF_TYPE(off, type) off; \
	off += sizeof(type); \
	off = ALIGN(off, SCE_ALIGN)
#define _INC_OFF_SIZE(off, size) off; \
	off += (size); \
	off = ALIGN(off, SCE_ALIGN)

void sce_layout_ctxt(sce_buffer_ctxt_t *ctxt)
{
	unsigned int coff = 0;

	//SCE header.
	ctxt->off_sceh = _INC_OFF_TYPE(coff, sce_header_t);

	switch(ctxt->sceh->header_type)
	{
	case SCE_HEADER_TYPE_SELF:
		{
			//SELF header.
			ctxt->off_self.off_selfh = _INC_OFF_TYPE(coff, self_header_t);
			//Application info.
			ctxt->off_self.off_ai = _INC_OFF_TYPE(coff, app_info_t);
			//ELF header.
			ctxt->off_self.off_ehdr = _INC_OFF_SIZE(coff, ctxt->makeself->ehsize);
			//ELF Program headers.
			ctxt->off_self.off_phdr = _INC_OFF_SIZE(coff, ctxt->makeself->phsize);
			//Section info.
			ctxt->off_self.off_si = _INC_OFF_SIZE(coff, sizeof(section_info_t) * ctxt->makeself->si_cnt);
			//SCE version.
			ctxt->off_self.off_sv = _INC_OFF_TYPE(coff, sce_version_t);
			//Control infos.
			ctxt->off_self.off_cis = _INC_OFF_SIZE(coff, _sce_get_ci_len(ctxt));
		}
		break;
	case SCE_HEADER_TYPE_RVK:
		//TODO
		break;
	case SCE_HEADER_TYPE_PKG:
		//TODO
		break;
	case SCE_HEADER_TYPE_SPP:
		//TODO
		break;
	default:
		//TODO
		break;
	}

	//Metadata info.
	ctxt->off_metai = _INC_OFF_TYPE(coff, metadata_info_t);
	//Metadata header.
	ctxt->off_metah = _INC_OFF_TYPE(coff, metadata_header_t);
	//Metadata section headers.
	ctxt->off_metash = _INC_OFF_SIZE(coff, ctxt->metah->section_count * sizeof(metadata_section_header_t));
	//Keys.
	_sce_fixup_keys(ctxt);
	ctxt->off_keys = _INC_OFF_SIZE(coff, ctxt->keys_len);

	//SELF only headers.
	if(ctxt->sceh->header_type == SCE_HEADER_TYPE_SELF)
	{
		//Optional headers.
		ctxt->off_self.off_ohs = _INC_OFF_SIZE(coff, _sce_get_oh_len(ctxt));
	}

	//Signature.
	ctxt->off_sig = _INC_OFF_TYPE(coff, signature_t);

	//Header padding.
	ctxt->off_hdrpad = coff;
	coff = ALIGN(coff, HEADER_ALIGN);
	
	//Set header length.
	ctxt->sceh->header_len = coff;

	//Set missing values, etc.
	_sce_fixup_ctxt(ctxt);
}

static void _sce_build_header(sce_buffer_ctxt_t *ctxt)
{
	unsigned int i;

	//Allocate header buffer.
	ctxt->scebuffer = (unsigned char*)malloc(sizeof(unsigned char) * ctxt->sceh->header_len);
	memset(ctxt->scebuffer, 0, sizeof(unsigned char) * ctxt->sceh->header_len);

	//SCE header.
	_copy_es_sce_header((sce_header_t *)(ctxt->scebuffer + ctxt->off_sceh), ctxt->sceh);

	//File type dependent headers.
	switch(ctxt->sceh->header_type)
	{
	case SCE_HEADER_TYPE_SELF:
		{
			//SELF header.
			_copy_es_self_header((self_header_t *)(ctxt->scebuffer + ctxt->off_self.off_selfh), ctxt->self.selfh);
			//Application info.
			_copy_es_app_info((app_info_t *)(ctxt->scebuffer + ctxt->off_self.off_ai), ctxt->self.ai);
			//ELF header.
			memcpy(ctxt->scebuffer + ctxt->off_self.off_ehdr, ctxt->makeself->ehdr, ctxt->makeself->ehsize);
			//ELF program headers.
			memcpy(ctxt->scebuffer + ctxt->off_self.off_phdr, ctxt->makeself->phdrs, ctxt->makeself->phsize);

			//Section info.
			unsigned int i;
			for(i = 0; i < ctxt->makeself->si_cnt; i++)
				_copy_es_section_info((section_info_t *)(ctxt->scebuffer + ctxt->off_self.off_si + sizeof(section_info_t) * i), &ctxt->self.si[i]);

			//SCE version.
			_copy_es_sce_version((sce_version_t *)(ctxt->scebuffer + ctxt->off_self.off_sv), ctxt->self.sv);

			//Control infos.
			unsigned int ci_base = ctxt->off_self.off_cis;
			LIST_FOREACH(iter, ctxt->self.cis)
			{
				control_info_t *ci = (control_info_t *)iter->value;

				//Copy control info header.
				_copy_es_control_info((control_info_t *)(ctxt->scebuffer + ci_base), ci);
				//Copy data.
				memcpy(ctxt->scebuffer + ci_base + sizeof(control_info_t), ((unsigned char *)ci) + sizeof(control_info_t), ci->size - sizeof(control_info_t));

				ci_base += ci->size;
			}
		}
		break;
	case SCE_HEADER_TYPE_RVK:
		//TODO
		break;
	case SCE_HEADER_TYPE_PKG:
		//TODO
		break;
	case SCE_HEADER_TYPE_SPP:
		//TODO
		break;
	default:
		//TODO
		break;
	}

	//Metadata info.
	memcpy(ctxt->scebuffer + ctxt->off_metai, ctxt->metai, sizeof(metadata_info_t));
	//Metadata header.
	_copy_es_metadata_header((metadata_header_t *)(ctxt->scebuffer + ctxt->off_metah), ctxt->metah);
	//Metadata section headers.
	for(i = 0; i < ctxt->metah->section_count; i++)
		_copy_es_metadata_section_header((metadata_section_header_t *)(ctxt->scebuffer + ctxt->off_metash + sizeof(metadata_section_header_t) * i), &ctxt->metash[i]);

	//Keys.
	//memcpy(ctxt->scebuffer + ctxt->off_keys, ctxt->keys, ctxt->keys_len);

	//SELF only headers.
	if(ctxt->sceh->header_type == SCE_HEADER_TYPE_SELF)
	{
		//Optional headers.
		unsigned int oh_base = ctxt->off_self.off_ohs;
		LIST_FOREACH(iter, ctxt->self.ohs)
		{
			opt_header_t *oh = (opt_header_t *)iter->value;

			//Copy optional header.
			_copy_es_opt_header((opt_header_t *)(ctxt->scebuffer + oh_base), oh);
			//Copy data.
			memcpy(ctxt->scebuffer + oh_base + sizeof(opt_header_t), ((unsigned char *)oh) + sizeof(opt_header_t), oh->size - sizeof(opt_header_t));

			oh_base += oh->size;
		}
	}
}

static BOOL _sce_sign_header(sce_buffer_ctxt_t *ctxt, keyset_t *ks)
{
	unsigned char hash[0x14];

	//Well...
	if(ks->priv == NULL || ks->pub == NULL)
		return FALSE;

	//Generate header hash.
	sha1(ctxt->scebuffer, ctxt->metah->sig_input_length, hash);

	//Generate signature.
	ecdsa_set_curve(ks->ctype);
	ecdsa_set_pub(ks->pub);
	ecdsa_set_priv(ks->priv);
	ecdsa_sign(hash, ctxt->sig->r, ctxt->sig->s);

	//Copy Signature.
	memcpy(ctxt->scebuffer + ctxt->off_sig, ctxt->sig, sizeof(signature_t));

	return TRUE;
}

static void _sce_calculate_hashes(sce_buffer_ctxt_t *ctxt)
{
	unsigned int i = 0, sha1_idx;

	LIST_FOREACH(iter, ctxt->secs)
	{
		sce_section_ctxt_t *sec = (sce_section_ctxt_t *)iter->value;

		sha1_idx = ctxt->metash[i].sha1_index;
		memset(ctxt->keys + sha1_idx * 0x10, 0, 0x20);
		sha1_hmac(ctxt->keys + (sha1_idx + 2) * 0x10, 0x40, (unsigned char *)sec->buffer, sec->size, ctxt->keys + sha1_idx * 0x10);

		i++;
	}
}

static BOOL _sce_encrypt_header(sce_buffer_ctxt_t *ctxt, unsigned char *keyset)
{
	unsigned char *ptr;
	size_t nc_off;
	unsigned char sblk[0x10], iv[0x10];
	keyset_t *ks;
	aes_context aes_ctxt;

	//Check if a keyset is provided.
	if(keyset == NULL)
	{
		//Try to find keyset.
		if((ks = keyset_find(ctxt)) == NULL)
			return FALSE;
	}
	else
	{
		//Use the provided keyset.
		ks = keyset_from_buffer(keyset);
	}

	//Calculate hashes.
	_sce_calculate_hashes(ctxt);

	//Copy keys.
	memcpy(ctxt->scebuffer + ctxt->off_keys, ctxt->keys, ctxt->keys_len);

	//Sign header.
	_sce_sign_header(ctxt, ks);

	//Encrypt metadata header, metadata section headers and keys.
	nc_off = 0;
	ptr = ctxt->scebuffer + ctxt->off_metah;
	aes_setkey_enc(&aes_ctxt, ctxt->metai->key, METADATA_INFO_KEYBITS);
	memcpy(iv, ctxt->metai->iv, 0x10);
	aes_crypt_ctr(&aes_ctxt, 
		ctxt->sceh->header_len - (sizeof(sce_header_t) + ctxt->sceh->metadata_offset + sizeof(metadata_info_t)), 
		&nc_off, iv, sblk, ptr, ptr);

	//Encrypt metadata info.
	aes_setkey_enc(&aes_ctxt, ks->erk, KEYBITS(ks->erklen));
	ptr = ctxt->scebuffer + ctxt->off_metai;
	aes_crypt_cbc(&aes_ctxt, AES_ENCRYPT, sizeof(metadata_info_t), ks->riv, ptr, ptr);

	//Add NPDRM layer.
	if(ctxt->sceh->header_type == SCE_HEADER_TYPE_SELF && ctxt->self.ai->self_type == SELF_TYPE_NPDRM)
		if(np_encrypt_npdrm(ctxt) == FALSE)
			return FALSE;

	return TRUE;
}

static void _sce_encrypt_data(sce_buffer_ctxt_t *ctxt)
{
	unsigned int i = 0;
	aes_context aes_ctxt;

	LIST_FOREACH(iter, ctxt->secs)
	{
		sce_section_ctxt_t *sec = (sce_section_ctxt_t *)iter->value;

		size_t nc_off = 0;
		unsigned char buf[16];
		unsigned char iv[16];

		if(ctxt->metash[i].encrypted == METADATA_SECTION_ENCRYPTED)
		{
			memcpy(iv, ctxt->keys + ctxt->metash[i].iv_index * 0x10, 0x10);
			aes_setkey_enc(&aes_ctxt, ctxt->keys + ctxt->metash[i].key_index * 0x10, 128);
			aes_crypt_ctr(&aes_ctxt, sec->size, &nc_off, iv, buf, (unsigned char *)sec->buffer, (unsigned char *)sec->buffer);
		}

		i++;
	}
}

BOOL sce_encrypt_ctxt(sce_buffer_ctxt_t *ctxt, unsigned char *keyset)
{
	//Build SCE file header.
	_sce_build_header(ctxt);

	//Encrypt header.
	if(_sce_encrypt_header(ctxt, keyset) == FALSE)
		return FALSE;

	//Encrypt data.
	_sce_encrypt_data(ctxt);

	return TRUE;
}

BOOL sce_write_ctxt(sce_buffer_ctxt_t *ctxt, char *fname)
{
	FILE *fp;

	if((fp = fopen(fname, "wb")) == NULL)
		return FALSE;

	//Write SCE file header.
	fwrite(ctxt->scebuffer, sizeof(unsigned char), ctxt->sceh->header_len, fp);

	//Write SCE file sections.
	LIST_FOREACH(iter, ctxt->secs)
	{
		sce_section_ctxt_t *sec = (sce_section_ctxt_t *)iter->value;
		fseek(fp, sec->offset, SEEK_SET);
		fwrite(sec->buffer, sizeof(unsigned char), sec->size, fp);
	}

	fclose(fp);

	return TRUE;
}

BOOL sce_decrypt_header(sce_buffer_ctxt_t *ctxt, unsigned char *metadata_info, unsigned char *keyset)
{
	unsigned int i;
	size_t nc_off;
	unsigned char sblk[0x10], iv[0x10];
	keyset_t *ks;
	aes_context aes_ctxt;

	//Check if provided metadata info should be used.
	if(metadata_info == NULL)
	{
		//Check if a keyset is provided.
		if(keyset == NULL)
		{
			//Try to find keyset.
			if((ks = keyset_find(ctxt)) == NULL)
				return FALSE;

			_LOG_VERBOSE("Using keyset [%s 0x%04X %s]\n", ks->name, ks->key_revision, sce_version_to_str(ks->version));
		}
		else
		{
			//Use the provided keyset.
			ks = keyset_from_buffer(keyset);
		}

		//Remove NPDRM layer.
		if(ctxt->sceh->header_type == SCE_HEADER_TYPE_SELF && ctxt->self.ai->self_type == SELF_TYPE_NPDRM)
			if(np_decrypt_npdrm(ctxt) == FALSE)
				return FALSE;

		//Decrypt metadata info.
		aes_setkey_dec(&aes_ctxt, ks->erk, KEYBITS(ks->erklen));
		memcpy(iv, ks->riv, 0x10); //!!!
		aes_crypt_cbc(&aes_ctxt, AES_DECRYPT, sizeof(metadata_info_t), iv, (unsigned char *)ctxt->metai, (unsigned char *)ctxt->metai);
	}
	else
	{
		//Copy provided metadata info over SELF metadata.
		memcpy((unsigned char *)ctxt->metai, metadata_info, sizeof(metadata_info));
	}

	if(ctxt->metai->key_pad[0] != 0x00 || ctxt->metai->iv_pad[0] != 0x00)
		return FALSE;

	//Decrypt metadata header, metadata section headers and keys.
	nc_off = 0;
	aes_setkey_enc(&aes_ctxt, ctxt->metai->key, METADATA_INFO_KEYBITS);
	aes_crypt_ctr(&aes_ctxt, 
		ctxt->sceh->header_len - (sizeof(sce_header_t) + ctxt->sceh->metadata_offset + sizeof(metadata_info_t)), 
		&nc_off, ctxt->metai->iv, sblk, (unsigned char *)ctxt->metah, (unsigned char *)ctxt->metah);

	//Fixup headers.
	_es_metadata_header(ctxt->metah);
	for(i = 0; i < ctxt->metah->section_count; i++)
		_es_metadata_section_header(&ctxt->metash[i]);

	//Metadata decrypted.
	ctxt->mdec = TRUE;

	//Set start of SCE file keys.
	ctxt->keys = (unsigned char *)ctxt->metash + sizeof(metadata_section_header_t) * ctxt->metah->section_count;
	ctxt->keys_len = ctxt->metah->key_count * 0x10;

	//Set SELF only headers.
	if(ctxt->sceh->header_type == SCE_HEADER_TYPE_SELF)
	{
		//Get pointers to all optional headers.
		ctxt->self.ohs = list_create();
		opt_header_t *oh = (opt_header_t *)(ctxt->keys + ctxt->metah->key_count * 0x10);
		_es_opt_header(oh);
		list_add_back(ctxt->self.ohs, oh);
		while(oh->next != 0)
		{
			oh = (opt_header_t *)((unsigned char *)oh + oh->size);
			_es_opt_header(oh);
			list_add_back(ctxt->self.ohs, oh);
		}

		//Signature.
		ctxt->sig = (signature_t *)((unsigned char *)oh + oh->size);
	}
	else
		ctxt->sig = (signature_t *)(ctxt->keys + ctxt->metah->key_count * 0x10);

	return TRUE;
}

BOOL sce_decrypt_data(sce_buffer_ctxt_t *ctxt)
{
	unsigned int i;
	aes_context aes_ctxt;

	//Decrypt sections.
	for(i = 0; i < ctxt->metah->section_count; i++)
	{
		size_t nc_off = 0;
		unsigned char buf[16];
		unsigned char iv[16];

		//Only decrypt encrypted sections.
		if(ctxt->metash[i].encrypted == METADATA_SECTION_ENCRYPTED)
		{
			if(ctxt->metash[i].key_index > ctxt->metah->key_count - 1 || ctxt->metash[i].iv_index > ctxt->metah->key_count)
				printf("[*] Warning: Skipped decryption of section %03d (marked encrypted but key/iv index out of range)\n", i);
			else
			{
				memcpy(iv, ctxt->keys + ctxt->metash[i].iv_index * 0x10, 0x10);
				aes_setkey_enc(&aes_ctxt, ctxt->keys + ctxt->metash[i].key_index * 0x10, 128);
				unsigned char *ptr = ctxt->scebuffer + ctxt->metash[i].data_offset;
				aes_crypt_ctr(&aes_ctxt, ctxt->metash[i].data_size, &nc_off, iv, buf, ptr, ptr);
			}
		}
	}

	return TRUE;
}

void sce_print_info(FILE *fp, sce_buffer_ctxt_t *ctxt)
{
	unsigned int i;

	//Print SCE header.
	_print_sce_header(fp, ctxt->sceh);

	//Check if the metadata was decrypted.
	if(ctxt->mdec == FALSE)
		return;

	//Print metadata infos.
	_print_metadata_info(fp, ctxt->metai);
	_print_metadata_header(fp, ctxt->metah);

	//Print section infos.
	_print_metadata_section_header_header(fp);
	for(i = 0; i < ctxt->metah->section_count; i++)
		_print_metadata_section_header(fp, &ctxt->metash[i], i);

	//Print keys.
	_print_sce_file_keys(fp, ctxt);
}

static char _sce_tmp_vstr[16];
char *sce_version_to_str(unsigned long long int version)
{
	unsigned int v = version >> 32;
	sprintf(_sce_tmp_vstr, "%02X.%02X", (v & 0xFFFF0000) >> 16, v & 0x0000FFFF);
	return _sce_tmp_vstr;
}

unsigned long long int sce_str_to_version(char *version)
{
	unsigned short h, l;
	sscanf(version, "%02X.%02X", (unsigned int *) &h, (unsigned int *) &l);
	return ((unsigned long long int)(h << 16 | l)) << 32;
}

unsigned long long int sce_hexver_to_decver(unsigned long long int version)
{
	//TODO: hackity hack.
	char tmp[16];
	unsigned int v = version >> 32;
	unsigned long long int res;

	sprintf(tmp, "%02X%02X", (v & 0xFFFF0000) >> 16, v & 0x0000FFFF);
	sscanf(tmp, "%d", &v);
	res = v*100;

	return res;
}

control_info_t *sce_get_ctrl_info(sce_buffer_ctxt_t *ctxt, unsigned int type)
{
	LIST_FOREACH(iter, ctxt->self.cis)
	{
		control_info_t *ci = (control_info_t *)iter->value;
		if(ci->type == type)
			return ci;
	}

	return NULL;
}

opt_header_t *sce_get_opt_header(sce_buffer_ctxt_t *ctxt, unsigned int type)
{
	LIST_FOREACH(iter, ctxt->self.ohs)
	{
		opt_header_t *oh = (opt_header_t *)iter->value;
		if(oh->type == type)
			return oh;
	}

	return NULL;
}
