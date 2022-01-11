//---------------------------------------------------
// Advanced QA Flag & Debug Settings Enabler by habib
//---------------------------------------------------

// Improved by Evilnat

#include <stdlib.h>
#include <string.h>
#include <lv1/lv1.h>
#include <lv2/io.h>
#include <lv2/security.h>
#include <lv2/thread.h>
#include <lv2/patch.h>
#include <lv1/patch.h>
#include <lv1/mm.h>
#include "ps3mapi_core.h"
#include "common.h"
#include "storage_ext.h"
#include "qa.h"

u64 *idps;
u64 IDPS_1, IDPS_2;
u32 UM_ori_patch, DM_ori_patch1, DM_ori_patch2, DM_ori_patch3, DM_ori_patch4;

static u8 erk[0x20] =
{
	0x34, 0x18, 0x12, 0x37, 0x62, 0x91, 0x37, 0x1c,
	0x8b, 0xc7, 0x56, 0xff, 0xfc, 0x61, 0x15, 0x25,
	0x40, 0x3f, 0x95, 0xa8, 0xef, 0x9d, 0x0c, 0x99,
	0x64, 0x82, 0xee, 0xc2, 0x16, 0xb5, 0x62, 0xed
};

static u8 hmac[0x40] =
{
	0xcc, 0x30, 0xc4, 0x22, 0x91, 0x13, 0xdb, 0x25,
	0x73, 0x35, 0x53, 0xaf, 0xd0, 0x6e, 0x87, 0x62,
	0xb3, 0x72, 0x9d, 0x9e, 0xfa, 0xa6, 0xd5, 0xf3,
	0x5a, 0x6f, 0x58, 0xbf, 0x38, 0xff, 0x8b, 0x5f,
	0x58, 0xa2, 0x5b, 0xd9, 0xc9, 0xb5, 0x0b, 0x01,
	0xd1, 0xab, 0x40, 0x28, 0x67, 0x69, 0x68, 0xea,
	0xc7, 0xf8, 0x88, 0x33, 0xb6, 0x62, 0x93, 0x5d,
	0x75, 0x06, 0xa6, 0xb5, 0xe0, 0xf9, 0xd9, 0x7a
};

static u8 iv_qa[0x10] =
{
	0xe8, 0x66, 0x3a, 0x69, 0xcd, 0x1a, 0x5c, 0x45,
	0x4a, 0x76, 0x1e, 0x72, 0x8c, 0x7c, 0x25, 0x4e
};

/**
* Function to compute the digest
*
* @param k   Secret key
* @param lk  Length of the key in bytes
* @param d   Data
* @param ld  Length of data in bytes
* @param out Digest output
* @param t   Size of digest output
*/

static void hmac_sha1(const u8 *k, u8 lk, const u8 *d, size_t ld, u8 *out)
{
	SHACtx *ictx = malloc(0x100);

	if(!ictx)
		return;

	SHACtx *octx = malloc(0x100);

	if(!octx)
	{
		free(ictx);
		return;
	}

	u8 isha[SHA_DIGEST_LENGTH];
	u8 key[SHA_DIGEST_LENGTH];
	u8 buf[SHA_BLOCKSIZE];
	u8 i;

	if (lk > SHA_BLOCKSIZE)
	{
		SHACtx *tctx = malloc(0x100);
		sha1_init(tctx);
		sha1_update(tctx, k, lk);
		sha1_final(key, tctx);
		free(tctx);

		k = key;
		lk = SHA_DIGEST_LENGTH;
	}

	// Inner Digest
	sha1_init(ictx);

	// Pad the key for inner digest
	for (i = 0; i < lk; ++i)
		buf[i] = k[i] ^ 0x36;
	for (i = lk; i < SHA_BLOCKSIZE; ++i)
		buf[i] = 0x36;

	sha1_update(ictx, buf, SHA_BLOCKSIZE);
	sha1_update(ictx, d, ld);

	sha1_final(isha, ictx);

	// Outer Digest
	sha1_init(octx);

	// Pad the key for outter digest

	for (i = 0; i < lk; ++i)
		buf[i] = k[i] ^ 0x5c;
	for (i = lk; i < SHA_BLOCKSIZE; ++i)
		buf[i] = 0x5c;

	sha1_update(octx, buf, SHA_BLOCKSIZE);
	sha1_update(octx, isha, SHA_DIGEST_LENGTH);

	sha1_final(out, octx);

	free(ictx);
	free(octx);
}

static void lv1_patches()
{
	UM_ori_patch = lv1_peekw(UM_PATCH_OFFSET);
	DM_ori_patch1 = lv1_peekw(DM_PATCH1_OFFSET);
	DM_ori_patch2 = lv1_peekw(DM_PATCH2_OFFSET);
	DM_ori_patch3 = lv1_peekw(DM_PATCH3_OFFSET);
	DM_ori_patch4 = lv1_peekw(DM_PATCH4_OFFSET);

	lv1_pokew(UM_PATCH_OFFSET, LI(R0, 0));
	lv1_pokew(DM_PATCH1_OFFSET, NOP);
	lv1_pokew(DM_PATCH2_OFFSET, LI(R3, 1));
	lv1_pokew(DM_PATCH3_OFFSET, LI(R31, 1));
	lv1_pokew(DM_PATCH4_OFFSET, LI(R3, 0));
}

static void restore_patches()
{
	lv1_pokew(UM_PATCH_OFFSET, UM_ori_patch);
	lv1_pokew(DM_PATCH1_OFFSET, DM_ori_patch1);
	lv1_pokew(DM_PATCH2_OFFSET, DM_ori_patch2);
	lv1_pokew(DM_PATCH3_OFFSET, DM_ori_patch3);
	lv1_pokew(DM_PATCH4_OFFSET, DM_ori_patch4);
}

static int get_idps()
{
	u32 nread;
	u64 device;
	u64 start_flash_sector = 0x181;
	device_handle_t handle;

	page_allocate_auto(NULL, 4096, (void **)&idps);

	device = storage_get_flash_device();

	if(!device)
		start_flash_sector = 0x20D;

	DPRINTF("Flash Device: %016lX\n", device);

	if(storage_open(device, 0, &handle, 0))
		return 1;

	if(storage_map_io_memory(device, idps, 4096))
		return 1;

	if(call_hooked_function_7(emu_storage_read, (u64)handle, 0, start_flash_sector, 1, (u64)idps, (u64)&nread, 0))
		return 1;

	memcpy(&IDPS_1, (void *)&idps[0x3A], 8);
	memcpy(&IDPS_2, (void *)&idps[0x3B], 8);

	DPRINTF("IDPS from EID5: %016lX%016lX\n", IDPS_1, IDPS_2);

	storage_close(handle);
	storage_unmap_io_memory(device, idps);
	free_page(NULL, idps);

	return 0;
}

u8 read_qa_flag()
{
	u8 value = 0;
	update_mgr_read_eeprom(QA_FLAG_OFFSET, &value, LV2_AUTH_ID);
	return (value == 0x00);
}

int set_qa_flag(u8 value)
{
	u8 seed[TOKEN_SIZE];
	u8 token[TOKEN_SIZE];

	if(get_idps())
		return 2;

	memset(seed, 0, TOKEN_SIZE);
	memcpy(seed + 4, (void *)&IDPS_1, 8);
	memcpy(seed + 12, (void *)&IDPS_2, 8);

	if(seed[0x07] != 0x01)
	{
		DPRINTF("QA Flag: IDPS is not valid!!\n");
		return 1;
	}

	seed[3] = 1;

	if(value)
	{
		seed[39] |= 0x1; // QA_FLAG_EXAM_API_ENABLE
		seed[39] |= 0x2; // QA_FLAG_QA_MODE_ENABLE

		seed[47] |= 0x2; // checked by lv2_kernel.self and sys_init_osd.self
		seed[47] |= 0x4; // can run sys_init_osd.self from /app_home ?

		seed[51] |= 0x1; // QA_FLAG_ALLOW_NON_QA
		seed[51] |= 0x2; // QA_FLAG_FORCE_UPDATE
	}

	hmac_sha1(hmac, 0x40, seed, 60, seed + 60);
	aescbccfb_enc(token, seed, 0x50, erk, 0x100, iv_qa);

	DPRINTF("QA Flag: %s...\n", (value) ? "Enabling" : "Disabling");

	lv1_patches();

	struct ps3dm_scm_write_eeprom write_eeprom;
	int len;
	u8 *p = (u8*)&write_eeprom;
	u64 laid, paid, vuart_lpar_addr, muid, nwritten;

	if(lv1_allocate_memory(4096, 0x0C, 0, 0, &vuart_lpar_addr, &muid) != 0)
	{
		restore_patches();
		return 2;
	}

	if(mm_map_lpar_memory_region(vuart_lpar_addr, HV_BASE, HV_SIZE2, HV_PAGE_SIZE, 0) != 0)
	{
		restore_patches();
		return 2;
	}

	laid = 0x1070000002000001ULL;
	paid = 0x1070000033000001ULL;

	memset(&write_eeprom, 0, sizeof(write_eeprom));

	ps3dm_init_header(&write_eeprom.dm_hdr, 1, PS3DM_FID_SCM,
		sizeof(write_eeprom)	-	sizeof(struct ps3dm_header),
		sizeof(write_eeprom)	-	sizeof(struct ps3dm_header));

	ps3dm_init_ss_header(&write_eeprom.ss_hdr, PS3DM_PID_SCM_WRITE_EEPROM, laid, paid);
	write_eeprom.offset = 0x48D3E;
	write_eeprom.nwrite = 0x50;
	write_eeprom.buf_size = 0x50;
	memset(write_eeprom.buf, 0, sizeof(write_eeprom.buf));
	memcpy(write_eeprom.buf, token, 0x50);
	len = sizeof(write_eeprom);

	for(u16 n = 0; n < len ; n += 8)
	{
		static u64 value;
		memcpy(&value, &p[n], 8);
		lv1_poked2((u64) n, value);
		__asm__("sync");
		memcpy(&value, (void *)0x8000000000000000ULL, 8);
	}

	if(lv1_write_virtual_uart(10, vuart_lpar_addr, len, &nwritten) != 0)
	{
		restore_patches();
		return 2;
	}

	nwritten = len;

	update_mgr_write_eeprom(QA_FLAG_OFFSET, (value) ? 0x00 : 0xFF, LV2_AUTH_ID);

	DPRINTF("QA Flag: %s\n", (value) ? "Enabled (Value: 0x00)" : "Disabled (Value: 0xFF)");

	restore_patches();

	return 0;
}
