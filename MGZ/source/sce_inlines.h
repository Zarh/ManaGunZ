/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#ifndef _SCE_INLINES_H_
#define _SCE_INLINES_H_

#include <string.h>

#include "types.h"
#include "sce.h"

static inline void _es_sce_header(sce_header_t *h)
{
	h->magic = _ES32(h->magic);
	h->version = _ES32(h->version);
	h->key_revision = _ES16(h->key_revision);
	h->header_type = _ES16(h->header_type);
	h->metadata_offset = _ES32(h->metadata_offset);
	h->header_len = _ES64(h->header_len);
	h->data_len = _ES64(h->data_len);
}

static inline void _copy_es_sce_header(sce_header_t *dst, sce_header_t *src)
{
	memcpy(dst, src, sizeof(sce_header_t)); 
	_es_sce_header(dst);
}

static inline void _es_metadata_header(metadata_header_t *h)
{
	h->sig_input_length = _ES64(h->sig_input_length);
	h->unknown_0 = _ES32(h->unknown_0);
	h->section_count = _ES32(h->section_count);
	h->key_count = _ES32(h->key_count);
	h->opt_header_size = _ES32(h->opt_header_size);
	h->unknown_1 = _ES32(h->unknown_1);
	h->unknown_2 = _ES32(h->unknown_2);
}

static inline void _copy_es_metadata_header(metadata_header_t *dst, metadata_header_t *src)
{
	memcpy(dst, src, sizeof(metadata_header_t)); 
	_es_metadata_header(dst);
}

static inline void _es_metadata_section_header(metadata_section_header_t *h)
{
	h->data_offset = _ES64(h->data_offset);
	h->data_size = _ES64(h->data_size);
	h->type = _ES32(h->type);
	h->index = _ES32(h->index);
	h->hashed = _ES32(h->hashed);
	h->sha1_index = _ES32(h->sha1_index);
	h->encrypted = _ES32(h->encrypted);
	h->key_index = _ES32(h->key_index);
	h->iv_index = _ES32(h->iv_index);
	h->compressed = _ES32(h->compressed);
}

static inline void _copy_es_metadata_section_header(metadata_section_header_t *dst, metadata_section_header_t *src)
{
	memcpy(dst, src, sizeof(metadata_section_header_t)); 
	_es_metadata_section_header(dst);
}

static inline void _es_self_header(self_header_t *h)
{
	h->header_type = _ES64(h->header_type);
	h->app_info_offset = _ES64(h->app_info_offset);
	h->elf_offset = _ES64(h->elf_offset);
	h->phdr_offset = _ES64(h->phdr_offset);
	h->shdr_offset = _ES64(h->shdr_offset);
	h->section_info_offset = _ES64(h->section_info_offset);
	h->sce_version_offset = _ES64(h->sce_version_offset);
	h->control_info_offset = _ES64(h->control_info_offset);
	h->control_info_size = _ES64(h->control_info_size);
	h->padding = _ES64(h->padding);
}

static inline void _copy_es_self_header(self_header_t *dst, self_header_t *src)
{
	memcpy(dst, src, sizeof(self_header_t)); 
	_es_self_header(dst);
}

static inline void _es_section_info(section_info_t *si)
{
	si->offset = _ES64(si->offset);
	si->size = _ES64(si->size);
	si->compressed = _ES32(si->compressed);
	si->unknown_0 = _ES32(si->unknown_0);
	si->unknown_1 = _ES32(si->unknown_1);
	si->encrypted = _ES32(si->encrypted);
}

static inline void _copy_es_section_info(section_info_t *dst, section_info_t *src)
{
	memcpy(dst, src, sizeof(section_info_t)); 
	_es_section_info(dst);
}

static inline void _es_sce_version(sce_version_t *sv)
{
	sv->header_type = _ES32(sv->header_type);
	sv->present = _ES32(sv->present);
	sv->size = _ES32(sv->size);
	sv->unknown_3 = _ES32(sv->unknown_3);
}

static inline void _copy_es_sce_version(sce_version_t *dst, sce_version_t *src)
{
	memcpy(dst, src, sizeof(sce_version_t)); 
	_es_sce_version(dst);
}

static inline void _es_app_info(app_info_t *ai)
{
	ai->auth_id = _ES64(ai->auth_id);
	ai->vendor_id = _ES32(ai->vendor_id);
	ai->self_type = _ES32(ai->self_type);
	ai->version = _ES64(ai->version);
	ai->padding = _ES64(ai->padding);
}

static inline void _copy_es_app_info(app_info_t *dst, app_info_t *src)
{
	memcpy(dst, src, sizeof(app_info_t)); 
	_es_app_info(dst);
}

static inline void _es_control_info(control_info_t *ci)
{
	ci->type = _ES32(ci->type);
	ci->size = _ES32(ci->size);
	ci->next = _ES64(ci->next);
}

static inline void _copy_es_control_info(control_info_t *dst, control_info_t *src)
{
	memcpy(dst, src, sizeof(control_info_t)); 
	_es_control_info(dst);
}

static inline void _es_ci_data_digest_40(ci_data_digest_40_t *dig)
{
	dig->fw_version = _ES64(dig->fw_version);
}

static inline void _copy_es_ci_data_digest_40(ci_data_digest_40_t *dst, ci_data_digest_40_t *src)
{
	memcpy(dst, src, sizeof(ci_data_digest_40_t)); 
	_es_ci_data_digest_40(dst);
}

static inline void _es_ci_data_npdrm(ci_data_npdrm_t *np)
{
	np->magic = _ES32(np->magic);
	np->unknown_0 = _ES32(np->unknown_0);
	np->license_type = _ES32(np->license_type);
	np->app_type = _ES32(np->app_type);
	np->unknown_1 = _ES64(np->unknown_1);
	np->unknown_2 = _ES64(np->unknown_2);
}

static inline void _copy_es_ci_data_npdrm(ci_data_npdrm_t *dst, ci_data_npdrm_t *src)
{
	memcpy(dst, src, sizeof(ci_data_npdrm_t)); 
	_es_ci_data_npdrm(dst);
}

static inline void _es_opt_header(opt_header_t *oh)
{
	oh->type = _ES32(oh->type);
	oh->size = _ES32(oh->size);
	oh->next = _ES64(oh->next);
}

static inline void _copy_es_opt_header(opt_header_t *dst, opt_header_t *src)
{
	memcpy(dst, src, sizeof(opt_header_t)); 
	_es_opt_header(dst);
}

static inline void _es_oh_data_cap_flags(oh_data_cap_flags_t *cf)
{
	cf->unk3 = _ES64(cf->unk3);
	cf->unk4 = _ES64(cf->unk4);
	cf->flags = _ES64(cf->flags);
	cf->unk6 = _ES32(cf->unk6);
	cf->unk7 = _ES32(cf->unk7);
}

static inline void _copy_es_cap_flags(oh_data_cap_flags_t *dst, oh_data_cap_flags_t *src)
{
	memcpy(dst, src, sizeof(oh_data_cap_flags_t)); 
	_es_oh_data_cap_flags(dst);
}

#endif
