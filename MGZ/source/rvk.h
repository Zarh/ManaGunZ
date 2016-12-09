/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#ifndef _RVK_H_
#define _RVK_H_

#include "types.h"
#include "sce.h"

/*
header:
 00000200   00 00 00 04 00 00 00 01 00 03 00 41 00 00 00 00
 00000210   00 00 00 06 00 00 00 00 00 00 00 00 00 00 00 00
body:
 00000220   00 00 00 03 00 00 00 01 00 03 00 41 00 00 00 00 00 00 00 00 00 00 00 02 FF FF FF FF FF FF FF FF
 00000240   00 00 00 04 00 00 00 01 00 03 00 41 00 00 00 00 10 70 00 05 FF 00 00 01 FF FF FF FF FF FF FF FF
 00000260   00 00 00 04 00 00 00 01 00 03 00 41 00 00 00 00 10 70 00 05 FE 00 00 01 FF FF FF FF FF FF FF FF
 00000280   00 00 00 04 00 00 00 01 00 03 00 41 00 00 00 00 10 70 00 05 FD 00 00 01 FF FF FF FF FF FF FF FF
 000002A0   00 00 00 04 00 00 00 01 00 03 00 41 00 00 00 00 10 70 00 05 FC 00 00 01 FF FF FF FF FF FF FF FF
 000002C0   00 00 00 04 00 00 00 03 00 01 00 00 00 00 00 00 10 70 00 04 00 00 00 01 FF FF FF FF FF FF FF FF
*/

/*
0 self != rvk
1 self == rvk
2 !(rvk <= self) -> self < rvk
3 self <= rvk
4 !(self <= rvk) -> self > rvk
5 rvk <= self -> self >= rvk
*/
#define CHECK_SELF_NEQU_RVK 0
#define CHECK_SELF_EQU_RVK 1
#define CHECK_SELF_LT_RVK 2
#define CHECK_SELF_LTEQU_RVK 3
#define CHECK_SELF_GT_RVK 4
#define CHECK_SELF_GTEQU_RVK 5

/*! RVK header. */
typedef struct _rvk_header
{
	unsigned int type_0;
	unsigned int type_1;
	unsigned long long int opaque; //Program revoke: version, Package revoke: unknown.
	unsigned int entcnt;
	unsigned char padding[12];
} rvk_header_t;

static inline void _es_rvk_header(rvk_header_t *h)
{
	h->type_0 = _ES32(h->type_0);
	h->type_1 = _ES32(h->type_1);
	h->opaque = _ES64(h->opaque);
	h->entcnt = _ES32(h->entcnt);
}

/*! Program revoke list entry. */
typedef struct _prg_rvk_entry
{
	unsigned int self_type; //3, 4
	unsigned int check_type;
	unsigned long long int version;
	union
	{
		unsigned long long int auth_id;
		unsigned long long int unk_3;
	};
	unsigned long long int mask;
} prg_rvk_entry_t;

static inline void _es_prg_rvk_entry(prg_rvk_entry_t *e)
{
	e->self_type = _ES32(e->self_type);
	e->check_type = _ES32(e->check_type);
	e->version = _ES64(e->version);
	e->auth_id = _ES64(e->auth_id);
	e->mask = _ES64(e->mask);
}

/*! Print RVK infos. */
void rvk_print(FILE *fp, sce_buffer_ctxt_t *ctxt);

#endif
