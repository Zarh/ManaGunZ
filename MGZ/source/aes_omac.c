#include "types.h"
#include "aes.h"

void _gf_mul(unsigned char *pad)
{
	unsigned int i;
	unsigned cxor = (pad[0] & 0x80) ? 0x87 : 0;

	for(i = 0; i < 15; i++)
		pad[i] = (pad[i] << 1) | (pad[i + 1] >> 7);
	pad[15] = (pad[15] << 1) ^ cxor;
}

void aes_omac1(unsigned char *digest, unsigned char *input, unsigned int length, unsigned char *key, unsigned int keybits)
{
	unsigned int i = 0, j = 0;
	unsigned int overflow;
	aes_context ctxt;
	unsigned char buffer1[16], buffer2[16], dbuf[16];

	memset(buffer1, 0, 16);

	aes_setkey_enc(&ctxt, key, keybits);

	aes_crypt_ecb(&ctxt, AES_ENCRYPT, buffer1, buffer2);
	_gf_mul(buffer2);

	if(length > 16)
	{
		for(i = 0; i < length - 16; i += 16)
		{
			for(j = 0; j < 16; j++)
				dbuf[j] = buffer1[j] ^ input[i + j];
			aes_crypt_ecb(&ctxt, AES_ENCRYPT, dbuf, buffer1);
		}
	}

	overflow = length & 0xf;
	if(length % 16 == 0)
		overflow = 16;

	memset(dbuf, 0, 16);
	memcpy(dbuf, &(input[i]), overflow);

	if(overflow != 16)
	{
		dbuf[overflow] = 0x80;
		_gf_mul(buffer2);
	}

	for(i = 0; i < 16; i++)
		dbuf[i] ^= buffer1[i] ^ buffer2[i];

	aes_crypt_ecb(&ctxt, AES_ENCRYPT, dbuf, digest);
}
