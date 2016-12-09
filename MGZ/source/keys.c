/*
* Copyright (c) 2011-2013 by naehrwert
* Copyright (c) 2012 by flatz
* This file is released under the GPLv2.
*/

#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include "config.h"
#include "types.h"
#include "list.h"
#include "sce.h"
#include "keys.h"
#include "util.h"
#include "tables.h"
#include "aes.h"

extern char ManaGunZ_id[10];

/*
[keyname]
type={SELF, RVK, PKG, SPP, OTHER}
revision={00, ..., 18, 8000}
version={..., 0001000000000000, ...}
self_type={LV0, LV1, LV2, APP, ISO, LDR, UNK_7, NPDRM}
key=...
erk=...
riv=...
pub=...
priv=...
ctype=...
*/

/*! Loaded keysets. */
list_t *_keysets;
/*! Loaded curves. */
curve_t *_curves;
/*! Loaded VSH curves. */
vsh_curve_t *_vsh_curves;

static unsigned char rap_init_key[0x10] = 
{
	0x86, 0x9F, 0x77, 0x45, 0xC1, 0x3F, 0xD8, 0x90, 0xCC, 0xF2, 0x91, 0x88, 0xE3, 0xCC, 0x3E, 0xDF
};

static unsigned char rap_pbox[0x10] = 
{
	0x0C, 0x03, 0x06, 0x04, 0x01, 0x0B, 0x0F, 0x08, 0x02, 0x07, 0x00, 0x05, 0x0A, 0x0E, 0x0D, 0x09
};

static unsigned char rap_e1[0x10] = 
{
	0xA9, 0x3E, 0x1F, 0xD6, 0x7C, 0x55, 0xA3, 0x29, 0xB7, 0x5F, 0xDD, 0xA6, 0x2A, 0x95, 0xC7, 0xA5
};

static unsigned char rap_e2[0x10] = 
{
	0x67, 0xD4, 0x5D, 0xA3, 0x29, 0x6D, 0x00, 0x6A, 0x4E, 0x7C, 0x53, 0x7B, 0xF5, 0x53, 0x8C, 0x74
};

static void _fill_property(keyset_t *ks, char *prop, char *value)
{
	if(strcmp(prop, "type") == 0)
	{
		if(strcmp(value, "SELF") == 0)
			ks->type = KEYTYPE_SELF;
		else if(strcmp(value, "RVK") == 0)
			ks->type = KEYTYPE_RVK;
		else if(strcmp(value, "PKG") == 0)
			ks->type = KEYTYPE_PKG;
		else if(strcmp(value, "SPP") == 0)
			ks->type = KEYTYPE_SPP;
		else if(strcmp(value, "OTHER") == 0)
			ks->type = KEYTYPE_OTHER;
		else
			printf("[*] Error: Unknown type '%s'.\n", value);
	}
	else if(strcmp(prop, "revision") == 0)
		ks->key_revision = (unsigned short)_x_to_u64(value);
	else if(strcmp(prop, "version") == 0)
		ks->version = _x_to_u64(value);
	else if(strcmp(prop, "self_type") == 0)
	{
		if(strcmp(value, "LV0") == 0)
			ks->self_type = SELF_TYPE_LV0;
		else if(strcmp(value, "LV1") == 0)
			ks->self_type = SELF_TYPE_LV1;
		else if(strcmp(value, "LV2") == 0)
			ks->self_type = SELF_TYPE_LV2;
		else if(strcmp(value, "APP") == 0)
			ks->self_type = SELF_TYPE_APP;
		else if(strcmp(value, "ISO") == 0)
			ks->self_type = SELF_TYPE_ISO;
		else if(strcmp(value, "LDR") == 0)
			ks->self_type = SELF_TYPE_LDR;
		else if(strcmp(value, "UNK_7") == 0)
			ks->self_type = SELF_TYPE_UNK_7;
		else if(strcmp(value, "NPDRM") == 0)
			ks->self_type = SELF_TYPE_NPDRM;
		else
			printf("[*] Error: unknown SELF type '%s'.\n", value);
	}
	else if(strcmp(prop, "erk") == 0 || strcmp(prop, "key") == 0)
	{
		ks->erk = _x_to_u8_buffer(value);
		ks->erklen = strlen(value) / 2;
	}
	else if(strcmp(prop, "riv") == 0)
	{
		ks->riv = _x_to_u8_buffer(value);
		ks->rivlen = strlen(value) / 2;
	}
	else if(strcmp(prop, "pub") == 0)
		ks->pub = _x_to_u8_buffer(value);
	else if(strcmp(prop, "priv") == 0)
		ks->priv = _x_to_u8_buffer(value);
	else if(strcmp(prop, "ctype") == 0)
		ks->ctype = (unsigned char)_x_to_u64(value);
	else
		printf("[*] Error: Unknown keyfile property '%s'.\n", prop);
}

static long long int _compare_keysets(keyset_t *ks1, keyset_t *ks2)
{
	long long int res;

	if((res = (long long int)ks1->version - (long long int)ks2->version) == 0)
		res = (long long int)ks1->key_revision - (long long int)ks2->key_revision;

	return res;
}

static void _sort_keysets()
{
	unsigned int i, to = _keysets->count;
	lnode_t *max;

	list_t *tmp = list_create();

	for(i = 0; i < to; i++)
	{
		max = _keysets->head;
		LIST_FOREACH(iter, _keysets)
		{
			if(_compare_keysets((keyset_t *)max->value, (keyset_t *)iter->value) < 0)
				max = iter;
		}
		list_push(tmp, max->value);
		list_remove_node(_keysets, max);
	}

	list_destroy(_keysets);
	_keysets = tmp;
}

void _print_key_list(FILE *fp)
{
	const char *name;
	int len = 0, tmp;

	LIST_FOREACH(iter, _keysets)
		if((tmp = strlen(((keyset_t *)iter->value)->name)) > len)
			len = tmp;

	fprintf(fp, " Name");
	_print_align(fp, " ", len, 4);
	fprintf(fp, " Type  Revision Version SELF-Type\n");

	LIST_FOREACH(iter, _keysets)
	{
		keyset_t *ks = (keyset_t *)iter->value;
		fprintf(fp, " %s", ks->name);
		_print_align(fp, " ", len, strlen(ks->name));
		fprintf(fp, " %-5s 0x%04X   %s   ", _get_name(_key_types, ks->type), ks->key_revision, sce_version_to_str(ks->version));
		if(ks->type == KEYTYPE_SELF)
		{
			name = _get_name(_self_types, ks->self_type);
			if(name != NULL)
				fprintf(fp, "[%s]\n", name);
			else
				fprintf(fp, "0x%08X\n", ks->self_type);
		}
		else
			fprintf(fp, "\n");
	}
}

#define LINEBUFSIZE 512
BOOL keys_load(const char *kfile)
{
	unsigned int i = 0, lblen;
	FILE *fp;
	char lbuf[LINEBUFSIZE];
	keyset_t *cks = NULL;

	if((_keysets = list_create()) == NULL)
		return FALSE;

	if((fp = fopen(kfile, "r")) == NULL)
	{
		list_destroy(_keysets);
		return FALSE;
	}

	do
	{
		//Get next line.
		lbuf[0] = 0;
		fgets(lbuf, LINEBUFSIZE, fp);
		lblen = strlen(lbuf);

		//Don't parse empty lines (ignore '\n') and comment lines (starting with '#').
		if(lblen > 1 && lbuf[0] != '#')
		{
			//Remove '\n'.
			lbuf[lblen-1] = 0;

			//Check for keyset entry.
			if(lblen > 2 && lbuf[0] == '[')
			{
				if(cks != NULL)
				{
					//Add to keyset list.
					list_push(_keysets, cks);
					cks = NULL;
				}

				//Find name end.
				for(i = 0; lbuf[i] != ']' && lbuf[i] != '\n' && i < lblen; i++);
				lbuf[i] = 0;

				//Allocate keyset and fill name.
				cks = (keyset_t *)malloc(sizeof(keyset_t));
				memset(cks, 0, sizeof(keyset_t));
				cks->name = strdup(&lbuf[1]);
			}
			else if(cks != NULL)
			{
				//Find property name end.
				for(i = 0; lbuf[i] != '=' && lbuf[i] != '\n' && i < lblen; i++);
				lbuf[i] = 0;

				//Fill property.
				_fill_property(cks, &lbuf[0], &lbuf[i+1]);
			}
		}
	} while(!feof(fp));

	//Add last keyset to keyset list.
	if(cks != NULL)
		list_push(_keysets, cks);

	//Sort keysets.
	_sort_keysets();

	return TRUE;
}
#undef LINEBUFSIZE

static keyset_t *_keyset_find_for_self(unsigned int self_type, unsigned short key_revision, unsigned long long int version)
{
	LIST_FOREACH(iter, _keysets)
	{
		keyset_t *ks = (keyset_t *)iter->value;

		if(ks->self_type == self_type)
		{
			switch(self_type)
			{
			case SELF_TYPE_LV0:
				return ks;
				break;
			case SELF_TYPE_LV1:
				if(version <= ks->version)
					return ks;
				break;
			case SELF_TYPE_LV2:
				if(version <= ks->version)
					return ks;
				break;
			case SELF_TYPE_APP:
				if(key_revision == ks->key_revision)
					return ks;
				break;
			case SELF_TYPE_ISO:
				if(version <= ks->version && key_revision == ks->key_revision)
					return ks;
				break;
			case SELF_TYPE_LDR:
				return ks;
				break;
			case SELF_TYPE_NPDRM:
				if(key_revision == ks->key_revision)
					return ks;
				break;
			}
		}
	}

	return NULL;
}

static keyset_t *_keyset_find_for_rvk(unsigned int key_revision)
{
	LIST_FOREACH(iter, _keysets)
	{
		keyset_t *ks = (keyset_t *)iter->value;

		if(ks->type == KEYTYPE_RVK && key_revision <= ks->key_revision)
			return ks;
	}

	return NULL;
}

static keyset_t *_keyset_find_for_pkg(unsigned short key_revision)
{
	LIST_FOREACH(iter, _keysets)
	{
		keyset_t *ks = (keyset_t *)iter->value;

		if(ks->type == KEYTYPE_PKG && key_revision <= ks->key_revision)
			return ks;
	}

	return NULL;
}

static keyset_t *_keyset_find_for_spp(unsigned short key_revision)
{
	LIST_FOREACH(iter, _keysets)
	{
		keyset_t *ks = (keyset_t *)iter->value;

		if(ks->type == KEYTYPE_SPP && key_revision <= ks->key_revision)
			return ks;
	}

	return NULL;
}

keyset_t *keyset_find(sce_buffer_ctxt_t *ctxt)
{
	keyset_t *res = NULL;

	switch(ctxt->sceh->header_type)
	{
	case SCE_HEADER_TYPE_SELF:
		res = _keyset_find_for_self(ctxt->self.ai->self_type, ctxt->sceh->key_revision, ctxt->self.ai->version);
		break;
	case SCE_HEADER_TYPE_RVK:
		res = _keyset_find_for_rvk(ctxt->sceh->key_revision);
		break;
	case SCE_HEADER_TYPE_PKG:
		res = _keyset_find_for_pkg(ctxt->sceh->key_revision);
		break;
	case SCE_HEADER_TYPE_SPP:
		res = _keyset_find_for_spp(ctxt->sceh->key_revision);
		break;
	}

	if(res == NULL)
		printf("[*] Error: Could not find keyset for %s.\n", _get_name(_sce_header_types, ctxt->sceh->header_type));

	return res;
}

keyset_t *keyset_find_by_name(const char *name)
{
	LIST_FOREACH(iter, _keysets)
	{
		keyset_t *ks = (keyset_t *)iter->value;
		if(strcmp(ks->name, name) == 0)
			return ks;
	}

	printf("[*] Error: Could not find keyset '%s'.\n", name);

	return NULL;
}

BOOL curves_load(const char *cfile)
{
	unsigned int len = 0;
	_curves = NULL;
	_curves = (curve_t *)_read_buffer(cfile, &len);
	
	if(_curves == NULL)
		return FALSE;
	
	if(len != CURVES_LENGTH)
	{
		free(_curves);
		return FALSE;
	}
	
	return TRUE;
}

curve_t *curve_find(unsigned char ctype)
{
	if(ctype > CTYPE_MAX)
		return NULL;
	return &_curves[ctype];
}

BOOL vsh_curves_load(const char *cfile)
{
	unsigned int len = 0;
	_vsh_curves = NULL;
	_vsh_curves = (vsh_curve_t *)_read_buffer(cfile, &len);
	
	if(_vsh_curves == NULL) return FALSE;
	
	if(len != VSH_CURVES_LENGTH)
	{
		free(_vsh_curves);
		return FALSE;
	}
	
	return TRUE;
}

static curve_t _tmp_curve;
curve_t *vsh_curve_find(unsigned char ctype)
{
	if(ctype > VSH_CTYPE_MAX)
		return NULL;

	_memcpy_inv(_tmp_curve.p, _vsh_curves[ctype].p, 20);
	_memcpy_inv(_tmp_curve.a, _vsh_curves[ctype].a, 20);
	_memcpy_inv(_tmp_curve.b, _vsh_curves[ctype].b, 20);
	_tmp_curve.N[0] = ~0x00;
	_memcpy_inv(_tmp_curve.N+1, _vsh_curves[ctype].N, 20);
	_memcpy_inv(_tmp_curve.Gx, _vsh_curves[ctype].Gx, 20);
	_memcpy_inv(_tmp_curve.Gy, _vsh_curves[ctype].Gx, 20);

	return &_tmp_curve;
}

static unsigned char *idps_load()
{
	char path[256];
	unsigned char *idps;
	unsigned int len = 0;
	
	sprintf(path, "/dev_hdd0/game/%s/USRDIR/launcher/data/%s", ManaGunZ_id, CONFIG_IDPS_FILE);
	
	idps = (unsigned char *)_read_buffer(path, &len);
	
	if(idps == NULL)
		return NULL;
	
	if(len != IDPS_LENGTH)
	{
		free(idps);
		return NULL;
	}
	
	return idps;
}

static act_dat_t *act_dat_load()
{
	char path[256];
	act_dat_t *act_dat;
	unsigned int len = 0;
	
	sprintf(path, "/dev_hdd0/game/%s/USRDIR/launcher/data/%s", ManaGunZ_id, CONFIG_ACT_DAT_FILE);
	
	act_dat = (act_dat_t *)_read_buffer(path, &len);
	
	if(act_dat == NULL)
		return NULL;
	
	if(len != ACT_DAT_LENGTH)
	{
		free(act_dat);
		return NULL;
	}
	
	return act_dat;
}

static rif_t *rif_load(const char *content_id)
{
	char path[256];
	rif_t *rif;
	unsigned int len = 0;
	
	sprintf(path, "/dev_hdd0/game/%s/USRDIR/launcher/data/%s%s", ManaGunZ_id, content_id, CONFIG_RIF_FILE_EXT );
	
	rif = (rif_t *)_read_buffer(path, &len);
	if(rif == NULL)
		return NULL;
	
	if(len < RIF_LENGTH)
	{
		free(rif);
		return NULL;
	}
	
	return rif;
}

static unsigned char *rap_load(const char *content_id)
{
	char path[256];
	unsigned char *rap;
	unsigned int len = 0;
	
	sprintf(path, "/dev_hdd0/game/%s/USRDIR/launcher/data/%s%s", ManaGunZ_id, content_id, CONFIG_RAP_FILE_EXT);
	
	rap = (unsigned char *)_read_buffer(path, &len);
	
	if(rap == NULL)
		return NULL;
	
	if(len != RAP_LENGTH)
	{
		free(rap);
		return NULL;
	}
	
	return rap;
}

static BOOL rap_to_klicensee(const char *content_id, unsigned char *klicensee)
{
	unsigned char *rap;
	aes_context aes_ctxt;
	int round_num;
	int i;

	rap = rap_load(content_id);
	if(rap == NULL)
		return FALSE;

	aes_setkey_dec(&aes_ctxt, rap_init_key, RAP_KEYBITS);
	aes_crypt_ecb(&aes_ctxt, AES_DECRYPT, rap, rap);

	for (round_num = 0; round_num < 5; ++round_num)
	{
		for (i = 0; i < 16; ++i)
		{
			int p = rap_pbox[i];
			rap[p] ^= rap_e1[p];
		}
		for (i = 15; i >= 1; --i)
		{
			int p = rap_pbox[i];
			int pp = rap_pbox[i - 1];
			rap[p] ^= rap[pp];
		}
		int o = 0;
		for (i = 0; i < 16; ++i)
		{
			int p = rap_pbox[i];
			unsigned char kc = rap[p] - o;
			unsigned char ec2 = rap_e2[p];
			if (o != 1 || kc != 0xFF)
			{
				o = kc < ec2 ? 1 : 0;
				rap[p] = kc - ec2;
			}
			else if (kc == 0xFF)
				rap[p] = kc - ec2;
			else
				rap[p] = kc;
		}
	}

	memcpy(klicensee, rap, RAP_LENGTH);
	free(rap);

	return TRUE;
}

BOOL klicensee_by_content_id(const char *content_id, unsigned char *klicensee)
{
	aes_context aes_ctxt;

	if(rap_to_klicensee(content_id, klicensee) == FALSE)
	{
		keyset_t *ks_np_idps_const, *ks_np_rif_key;
		rif_t *rif;
		unsigned char idps_const[0x10];
		unsigned char act_dat_key[0x10];
		unsigned int act_dat_key_index;
		unsigned char *idps;
		act_dat_t *act_dat;

		if((idps = idps_load()) == NULL)
		{
			printf("[*] Error: Could not load IDPS.\n");
			return FALSE;
		}
		else
			_LOG_VERBOSE("IDPS loaded.\n");

		if((act_dat = act_dat_load()) == NULL)
		{
			printf("[*] Error: Could not load act.dat.\n");
			return FALSE;
		}
		else
			_LOG_VERBOSE("act.dat loaded.\n");

		ks_np_idps_const = keyset_find_by_name(CONFIG_NP_IDPS_CONST_KNAME);
		if(ks_np_idps_const == NULL)
			return FALSE;
		memcpy(idps_const, ks_np_idps_const->erk, 0x10);

		ks_np_rif_key = keyset_find_by_name(CONFIG_NP_RIF_KEY_KNAME);
		if(ks_np_rif_key == NULL)
			return FALSE;

		rif = rif_load(content_id);
		if(rif == NULL)
		{
			printf("[*] Error: Could not obtain klicensee for '%s'.\n", content_id);
			return FALSE;
		}

		aes_setkey_dec(&aes_ctxt, ks_np_rif_key->erk, RIF_KEYBITS);
		aes_crypt_ecb(&aes_ctxt, AES_DECRYPT, rif->act_key_index, rif->act_key_index);

		act_dat_key_index = _ES32(*(unsigned int *)(rif->act_key_index + 12));
		if(act_dat_key_index > 127)
		{
			printf("[*] Error: act.dat key index out of bounds.\n");
			return FALSE;
		}

		memcpy(act_dat_key, act_dat->primary_key_table + act_dat_key_index * BITS2BYTES(ACT_DAT_KEYBITS), BITS2BYTES(ACT_DAT_KEYBITS));

		aes_setkey_enc(&aes_ctxt, idps, IDPS_KEYBITS);
		aes_crypt_ecb(&aes_ctxt, AES_ENCRYPT, idps_const, idps_const);

		aes_setkey_dec(&aes_ctxt, idps_const, IDPS_KEYBITS);
		aes_crypt_ecb(&aes_ctxt, AES_DECRYPT, act_dat_key, act_dat_key);

		aes_setkey_dec(&aes_ctxt, act_dat_key, ACT_DAT_KEYBITS);
		aes_crypt_ecb(&aes_ctxt, AES_DECRYPT, rif->klicensee, klicensee);

		free(rif);

		_LOG_VERBOSE("klicensee decrypted.\n");
	}
	else
		_LOG_VERBOSE("klicensee converted from %s.rap.\n", content_id);

	return TRUE;
}

keyset_t *keyset_from_buffer(unsigned char *keyset)
{
	keyset_t *ks;

	if((ks = (keyset_t *)malloc(sizeof(keyset_t))) == NULL)
		return NULL;

	ks->erk = (unsigned char *)_memdup(keyset, 0x20);
	ks->erklen = 0x20;
	ks->riv = (unsigned char *)_memdup(keyset + 0x20, 0x10);
	ks->rivlen = 0x10;
	ks->pub = (unsigned char *)_memdup(keyset + 0x20 + 0x10, 0x28);
	ks->priv = (unsigned char *)_memdup(keyset + 0x20 + 0x10 + 0x28, 0x15);
	ks->ctype = (unsigned char)*(keyset + 0x20 + 0x10 + 0x28 + 0x15);

	return ks;
}
