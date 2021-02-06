//---------------------------------------------------
// Advanced QA Flag & Debug Settings Enabler by habib
//---------------------------------------------------

/////// 2.1.2 Encryption fix & hmac hash validation ///// START
#define SHA_BLOCKSIZE		(64)
#define SHA_DIGEST_LENGTH	(20)

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

static void hmac_sha1(const u8 *k,	/* secret key */
					  u8 lk,		/* length of the key in bytes */
					  const u8 *d,	/* data */
					  size_t ld,		/* length of data in bytes */
					  u8 *out)		/* output buffer */
{
	SHACtx *ictx = malloc(0x100); if(!ictx) return;
	SHACtx *octx = malloc(0x100); if(!octx) {free(ictx); return;}

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

	/**** Inner Digest ****/

	sha1_init(ictx);

	/* Pad the key for inner digest */
	for (i = 0; i < lk; ++i)
	{
		buf[i] = k[i] ^ 0x36;
	}
	for (i = lk; i < SHA_BLOCKSIZE; ++i)
	{
		buf[i] = 0x36;
	}

	sha1_update(ictx, buf, SHA_BLOCKSIZE);
	sha1_update(ictx, d, ld);

	sha1_final(isha, ictx);

	/**** Outer Digest ****/

	sha1_init(octx);

	/* Pad the key for outter digest */

	for (i = 0; i < lk; ++i)
	{
		buf[i] = k[i] ^ 0x5c;
	}
	for (i = lk; i < SHA_BLOCKSIZE; ++i)
	{
		buf[i] = 0x5c;
	}

	sha1_update(octx, buf, SHA_BLOCKSIZE);
	sha1_update(octx, isha, SHA_DIGEST_LENGTH);

	sha1_final(out, octx);

	free(ictx);
	free(octx);
}

static u8 erk[0x20] = {
	0x34, 0x18, 0x12, 0x37, 0x62, 0x91, 0x37, 0x1c,
	0x8b, 0xc7, 0x56, 0xff, 0xfc, 0x61, 0x15, 0x25,
	0x40, 0x3f, 0x95, 0xa8, 0xef, 0x9d, 0x0c, 0x99,
	0x64, 0x82, 0xee, 0xc2, 0x16, 0xb5, 0x62, 0xed
};

static u8 hmac[0x40] = {
	0xcc, 0x30, 0xc4, 0x22, 0x91, 0x13, 0xdb, 0x25,
	0x73, 0x35, 0x53, 0xaf, 0xd0, 0x6e, 0x87, 0x62,
	0xb3, 0x72, 0x9d, 0x9e, 0xfa, 0xa6, 0xd5, 0xf3,
	0x5a, 0x6f, 0x58, 0xbf, 0x38, 0xff, 0x8b, 0x5f,
	0x58, 0xa2, 0x5b, 0xd9, 0xc9, 0xb5, 0x0b, 0x01,
	0xd1, 0xab, 0x40, 0x28, 0x67, 0x69, 0x68, 0xea,
	0xc7, 0xf8, 0x88, 0x33, 0xb6, 0x62, 0x93, 0x5d,
	0x75, 0x06, 0xa6, 0xb5, 0xe0, 0xf9, 0xd9, 0x7a
};

static u8 iv_qa[0x10] = {
	0xe8, 0x66, 0x3a, 0x69, 0xcd, 0x1a, 0x5c, 0x45,
	0x4a, 0x76, 0x1e, 0x72, 0x8c, 0x7c, 0x25, 0x4e
};
/////// 2.1.2 Encryption fix & hmac hash validation ///// END

LV2_HOOKED_FUNCTION_COND_POSTCALL_5(int,um_if_get_token,(u8 *token,uint32_t token_size,u8 *seed,uint32_t seed_size))
{
	if(seed != 0 && token != 0 && token_size == 0x50 && seed_size == 0x50)
	{
		memcpy(seed + 4, (void *)PS3MAPI_IDPS_2, 0x10);
		seed[3] = 1;
		seed[39] |= 0x1; /* QA_FLAG_EXAM_API_ENABLE */
		seed[39] |= 0x2; /* QA_FLAG_QA_MODE_ENABLE */
		seed[47] |= 0x2;
		seed[47] |= 0x4; /* checked by lv2_kernel.self and sys_init_osd.self */
						 /* can run sys_init_osd.self from /app_home ? */
		seed[51] |= 0x1; /* QA_FLAG_ALLOW_NON_QA */
		seed[51] |= 0x2; /* QA_FLAG_FORCE_UPDATE */

		/// 2.1.2 QA flag - hmac hash check - START
		hmac_sha1(hmac, 0x40, seed, 60, seed + 60);
		aescbccfb_enc(token,  seed, token_size, erk, 0x100, iv_qa);
		DPRINT_HEX_C(seed, 60);
		/// 2.1.2 QA flag - hmac hash check - END
		return 0;
	}

	return DO_POSTCALL;
}

LV2_HOOKED_FUNCTION_COND_POSTCALL_3(int,read_eeprom_by_offset,(uint32_t offset, u8 *value, uint64_t auth_id))
{
	if(offset == qa_eeprom_offset)
	{
		*value = 0;
		return 0;
	}
	return DO_POSTCALL;
}
