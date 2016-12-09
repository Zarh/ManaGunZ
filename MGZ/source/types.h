/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define BOOL int
#define TRUE 1
#define FALSE 0

//Align.
#define ALIGN(x, a) (((x) + (a) - 1) & ~((a) - 1))

//Bits <-> bytes conversion.
#define BITS2BYTES(x) ((x) / 8)
#define BYTES2BITS(x) ((x) * 8)

//Endian swap for unsigned short.
#define _ES16(val) val
	/*((unsigned short)(((((unsigned short)val) & 0xff00) >> 8) | \
	       ((((unsigned short)val) & 0x00ff) << 8)))
	*/
//Endian swap for unsigned int.
#define _ES32(val) val
/*	((unsigned int)(((((unsigned int)val) & 0xff000000) >> 24) | \
	       ((((unsigned int)val) & 0x00ff0000) >> 8 ) | \
	       ((((unsigned int)val) & 0x0000ff00) << 8 ) | \
	       ((((unsigned int)val) & 0x000000ff) << 24)))
		*/

//Endian swap for unsigned long long int.
#define _ES64(val) val 
/*	((unsigned long long int)(((((unsigned long long int)val) & 0xff00000000000000ull) >> 56) | \
	       ((((unsigned long long int)val) & 0x00ff000000000000ull) >> 40) | \
	       ((((unsigned long long int)val) & 0x0000ff0000000000ull) >> 24) | \
	       ((((unsigned long long int)val) & 0x000000ff00000000ull) >> 8 ) | \
	       ((((unsigned long long int)val) & 0x00000000ff000000ull) << 8 ) | \
	       ((((unsigned long long int)val) & 0x0000000000ff0000ull) << 24) | \
	       ((((unsigned long long int)val) & 0x000000000000ff00ull) << 40) | \
	       ((((unsigned long long int)val) & 0x00000000000000ffull) << 56)))
*/


#include <stdint.h>

#include <ppu-types.h>

#define noop16(x) (x)
#define noop32(x) (x)
#define noop64(x) (x)

#define swap16(x) ((((uint16_t)(x) & 0xff00) >> 8) | \
                  (((uint16_t)(x) & 0x00ff) << 8))
#define swap32(x) ((((uint32_t)(x) & 0xff000000) >> 24) | \
                  (((uint32_t)(x) & 0x00ff0000) >> 8)  | \
                  (((uint32_t)(x) & 0x0000ff00) << 8)  | \
                  (((uint32_t)(x) & 0x000000ff) << 24))
#define swap64(x) \
     ((((uint64_t)(x) & 0xff00000000000000ull) >> 56)  | \
       ((uint64_t)((x) & 0x00ff000000000000ull) >> 40) | \
       ((uint64_t)((x) & 0x0000ff0000000000ull) >> 24) | \
       ((uint64_t)((x) & 0x000000ff00000000ull) >> 8)  | \
       ((uint64_t)((x) & 0x00000000ff000000ull) << 8)  | \
       ((uint64_t)((x) & 0x0000000000ff0000ull) << 24) | \
       ((uint64_t)((x) & 0x000000000000ff00ull) << 40) | \
       ((uint64_t)((x) & 0x00000000000000ffull) << 56))

#ifdef __BIG_ENDIAN__
#define TO_BE(b, x) noop##b (x)
#define TO_LE(b, x) swap##b (x)
#define FROM_BE(b, x) noop##b (x)
#define FROM_LE(b, x) swap##b (x)
#else
#define TO_BE(b, x) swap##b (x)
#define TO_LE(b, x) noop##b (x)
#define FROM_BE(b, x) swap##b (x)
#define FROM_LE(b, x) noop##b (x)
#endif

struct elf_phdr {
	u32 p_type;
	u64 p_off;
	u64 p_vaddr;
	u64 p_paddr;
	u64 p_filesz;
	u64 p_memsz;
	u32 p_flags;
	u64 p_align;

	void *ptr;
};

struct elf_shdr {
	u32 sh_name;
	u32 sh_type;
	u32 sh_flags;
	u64 sh_addr;
	u64 sh_offset;
	u32 sh_size;
	u32 sh_link;
	u32 sh_info;
	u32 sh_addralign;
	u32 sh_entsize;
};

#define	ET_NONE		0
#define ET_REL		1
#define	ET_EXEC		2
#define	ET_DYN		3
#define	ET_CORE		4
#define	ET_LOOS		0xfe00
#define	ET_HIOS		0xfeff
#define ET_LOPROC	0xff00
#define	ET_HIPROC	0xffff
struct elf_hdr {
	char e_ident[16];
	u16 e_type;
	u16 e_machine;
	u32 e_version;
	u64 e_entry;
	u64 e_phoff;
	u64 e_shoff;
	u32 e_flags;
	u16 e_ehsize;
	u16 e_phentsize;
	u16 e_phnum;
	u16 e_shentsize;
	u16 e_shnum;
	u16 e_shtrndx;
};


struct id2name_tbl {
	u32 id;
	const char *name;
};

struct key {
	u8 key[32];
	u8 iv[16];

	int pub_avail;
	int priv_avail;
	u8 pub[40];
	u8 priv[21];
	u32 ctype;
};

struct keylist {
	u32 n;
	struct key *keys;
    struct key *idps;
    struct key *klic;
    struct key *rif;
    struct key *npdrm_const;
    struct key *free_klicensee;
};

struct rif {
    u8 unk1[0x10]; //version, license type and user number
    u8 titleid[0x30]; //Content ID
    u8 padding[0xC]; //Padding for randomness
    u32 actDatIndex; //Key index on act.dat between 0x00 and 0x7F
    u8 key[0x10]; //encrypted klicensee
    u64 unk2; //timestamp??
    u64 unk3; //Always 0
    u8 rs[0x28];
} __attribute__ ((packed));

struct actdat {
    u8 unk1[0x10]; //Version, User number
    u8 keyTable[0x800]; //Key Table
    u8 unk2[0x800];
    u8 signature[0x28];
} __attribute__ ((packed));

static inline u8 be8(u8 *p)
{
	return *p;
}

static inline u16 be16(u8 *p)
{
	u16 a;

	a  = p[0] << 8;
	a |= p[1];

	return a;
}

static inline u32 be32(u8 *p)
{
	u32 a;

	a  = p[0] << 24;
	a |= p[1] << 16;
	a |= p[2] <<  8;
	a |= p[3] <<  0;

	return a;
}

static inline u64 be64(u8 *p)
{
	u32 a, b;

	a = be32(p);
	b = be32(p + 4);

	return ((u64)a<<32) | b;
}

static inline void wbe16(u8 *p, u16 v)
{
	p[0] = v >>  8;
	p[1] = v;
}

static inline void wbe32(u8 *p, u32 v)
{
	p[0] = v >> 24;
	p[1] = v >> 16;
	p[2] = v >>  8;
	p[3] = v;
}

static inline void wbe64(u8 *p, u64 v)
{
	wbe32(p + 4, v);
	v >>= 32;
	wbe32(p, v);
}

#ifdef __cplusplus
}
#endif

