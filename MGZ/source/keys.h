/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#ifndef _KEYS_H_
#define _KEYS_H_

#include "types.h"
#include "sce.h"

#define KEYBITS(klen) BYTES2BITS(klen)

#define KEYTYPE_SELF 1
#define KEYTYPE_RVK 2
#define KEYTYPE_PKG 3
#define KEYTYPE_SPP 4
#define KEYTYPE_OTHER 5

/*! Flag to use VSH curve. */
#define USE_VSH_CURVE 0x40

/*! Length of whole curves file. */
#define CURVES_LENGTH 0x1E40
#define CTYPE_MIN 0
#define CTYPE_MAX 63

/*! Length of the whole VSH curves file. */
#define VSH_CURVES_LENGTH 0x168
#define VSH_CTYPE_MIN 0
#define VSH_CTYPE_MAX 2

/*! Length of the idps, act.dat, .rif and .rap files. */
#define IDPS_LENGTH 0x10
#define ACT_DAT_LENGTH 0x1038
#define RIF_LENGTH 0x98
#define RAP_LENGTH 0x10

/*! IDPS, RIF, act.dat key lengths. */
#define IDPS_KEYBITS 128
#define ACT_DAT_KEYBITS 128
#define RIF_KEYBITS 128
#define RAP_KEYBITS 128

/*! Keyset. */
typedef struct _keyset
{
	/*! Name. */
	char *name;
	/*! Type. */
	unsigned int type;
	/*! Key revision. */
	unsigned short key_revision;
	/*! Version. */
	unsigned long long int version;
	/*! SELF type. */
	unsigned int self_type;
	/*! Key length. */
	unsigned int erklen;
	/*! Key. */
	unsigned char *erk;
	/*! IV length. */
	unsigned int rivlen;
	/*! IV. */
	unsigned char *riv;
	/*! Pub. */
	unsigned char *pub;
	/*! Priv. */
	unsigned char *priv;
	/*! Curve type. */
	unsigned char ctype;
} keyset_t;

/*! Curve entry. */
typedef struct _curve
{
	unsigned char p[20];
	unsigned char a[20];
	unsigned char b[20];
	unsigned char N[21];
	unsigned char Gx[20];
	unsigned char Gy[20];
} curve_t;

/*! VSH Curve entry. */
typedef struct _vsh_curve
{
	unsigned char a[20];
	unsigned char b[20];
	unsigned char N[20];
	unsigned char p[20];
	unsigned char Gx[20];
	unsigned char Gy[20];
} vsh_curve_t;

/*! act.dat. */
typedef struct _act_dat
{
	unsigned char account_info[16];
    unsigned char primary_key_table[2048];
    unsigned char secondary_key_table[2048];
    unsigned char signature[40];
} act_dat_t;

/*! RIF. */
typedef struct _rif
{
	unsigned char account_info[16];
	unsigned char content_id[48];
	unsigned char act_key_index[16];
	unsigned char klicensee[16];
	unsigned long long int timestamp;
	unsigned long long int zero;
	unsigned char signature[40];
} rif_t;

void _print_key_list(FILE *fp);

BOOL keys_load(const char *kfile);
keyset_t *keyset_find(sce_buffer_ctxt_t *ctxt);
keyset_t *keyset_find_by_name(const char *name);

BOOL curves_load(const char *cfile);
curve_t *curve_find(unsigned char ctype);

BOOL vsh_curves_load(const char *cfile);
curve_t *vsh_curve_find(unsigned char ctype);

BOOL klicensee_by_content_id(const char *content_id, unsigned char *klicensee);

keyset_t *keyset_from_buffer(unsigned char *keyset);

#endif
