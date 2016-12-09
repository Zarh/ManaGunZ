/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#ifndef _ELF_INLINES_H_
#define _ELF_INLINES_H_

#include <string.h>

#include "types.h"
#include "elf.h"

static inline void _es_elf32_ehdr(Elf32_Ehdr *h)
{
	h->e_type = _ES16(h->e_type);
	h->e_machine = _ES16(h->e_machine);
	h->e_version = _ES32(h->e_version);
	h->e_entry = _ES32(h->e_entry);
	h->e_phoff = _ES32(h->e_phoff);
	h->e_shoff = _ES32(h->e_shoff);
	h->e_flags = _ES32(h->e_flags);
	h->e_ehsize = _ES16(h->e_ehsize);
	h->e_phentsize = _ES16(h->e_phentsize);
	h->e_phnum = _ES16(h->e_phnum);
	h->e_shentsize = _ES16(h->e_shentsize);
	h->e_shnum = _ES16(h->e_shnum);
	h->e_shstrndx = _ES16(h->e_shstrndx);
}

static inline void _copy_es_elf32_ehdr(Elf32_Ehdr *dst, Elf32_Ehdr *src)
{
	memcpy(dst, src, sizeof(Elf32_Ehdr)); 
	_es_elf32_ehdr(dst);
}

static inline void _es_elf64_ehdr(Elf64_Ehdr *h)
{
	h->e_type = _ES16(h->e_type);
	h->e_machine = _ES16(h->e_machine);
	h->e_version = _ES32(h->e_version);
	h->e_entry = _ES64(h->e_entry);
	h->e_phoff = _ES64(h->e_phoff);
	h->e_shoff = _ES64(h->e_shoff);
	h->e_flags = _ES32(h->e_flags);
	h->e_ehsize = _ES16(h->e_ehsize);
	h->e_phentsize = _ES16(h->e_phentsize);
	h->e_phnum = _ES16(h->e_phnum);
	h->e_shentsize = _ES16(h->e_shentsize);
	h->e_shnum = _ES16(h->e_shnum);
	h->e_shstrndx = _ES16(h->e_shstrndx);
}

static inline void _copy_es_elf64_ehdr(Elf64_Ehdr *dst, Elf64_Ehdr *src)
{
	memcpy(dst, src, sizeof(Elf64_Ehdr)); 
	_es_elf64_ehdr(dst);
}

static inline void _es_elf32_shdr(Elf32_Shdr *h)
{
	h->sh_name = _ES32(h->sh_name);
	h->sh_type = _ES32(h->sh_type);
	h->sh_flags = _ES32(h->sh_flags);
	h->sh_addr = _ES32(h->sh_addr);
	h->sh_offset = _ES32(h->sh_offset);
	h->sh_size = _ES32(h->sh_size);
	h->sh_link = _ES32(h->sh_link);
	h->sh_info = _ES32(h->sh_info);
	h->sh_addralign = _ES32(h->sh_addralign);
	h->sh_entsize = _ES32(h->sh_entsize);
}

static inline void _copy_es_elf32_shdr(Elf32_Shdr *dst, Elf32_Shdr *src)
{
	memcpy(dst, src, sizeof(Elf32_Shdr)); 
	_es_elf32_shdr(dst);
}

static inline void _es_elf64_shdr(Elf64_Shdr *h)
{
	h->sh_name = _ES32(h->sh_name);
	h->sh_type = _ES32(h->sh_type);
	h->sh_flags = _ES64(h->sh_flags);
	h->sh_addr = _ES64(h->sh_addr);
	h->sh_offset = _ES64(h->sh_offset);
	h->sh_size = _ES64(h->sh_size);
	h->sh_link = _ES32(h->sh_link);
	h->sh_info = _ES32(h->sh_info);
	h->sh_addralign = _ES64(h->sh_addralign);
	h->sh_entsize = _ES64(h->sh_entsize);
}

static inline void _copy_es_elf64_shdr(Elf64_Shdr *dst, Elf64_Shdr *src)
{
	memcpy(dst, src, sizeof(Elf64_Shdr)); 
	_es_elf64_shdr(dst);
}

static inline void _es_elf32_phdr(Elf32_Phdr *h)
{
	h->p_type = _ES32(h->p_type);
	h->p_offset = _ES32(h->p_offset);
	h->p_vaddr = _ES32(h->p_vaddr);
	h->p_paddr = _ES32(h->p_paddr);
	h->p_filesz = _ES32(h->p_filesz);
	h->p_memsz = _ES32(h->p_memsz);
	h->p_flags = _ES32(h->p_flags);
	h->p_align = _ES32(h->p_align);
}

static inline void _copy_es_elf32_phdr(Elf32_Phdr *dst, Elf32_Phdr *src)
{
	memcpy(dst, src, sizeof(Elf32_Phdr)); 
	_es_elf32_phdr(dst);
}

static inline void _es_elf64_phdr(Elf64_Phdr *h)
{
	h->p_type = _ES32(h->p_type);
	h->p_flags = _ES32(h->p_flags);
	h->p_offset = _ES64(h->p_offset);
	h->p_vaddr = _ES64(h->p_vaddr);
	h->p_paddr = _ES64(h->p_paddr);
	h->p_filesz = _ES64(h->p_filesz);
	h->p_memsz = _ES64(h->p_memsz);
	h->p_align = _ES64(h->p_align);
}

static inline void _copy_es_elf64_phdr(Elf64_Phdr *dst, Elf64_Phdr *src)
{
	memcpy(dst, src, sizeof(Elf64_Phdr)); 
	_es_elf64_phdr(dst);
}

#endif
