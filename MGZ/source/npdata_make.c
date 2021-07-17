// Copyright (C) 2014       Hykem <hykem@hotmail.com>
// Licensed under the terms of the GNU GPL, version 3
// http://www.gnu.org/licenses/gpl-3.0.txt

#include "mgz_io.h"
#include "npdata_make.h"
#include "extern.h"

unsigned char SDAT_KEY[] = {0x0D, 0x65, 0x5E, 0xF8, 0xE6, 0x74, 0xA9, 0x8A, 0xB8, 0x50, 0x5C, 0xFA, 0x7D, 0x01, 0x29, 0x33};
unsigned char EDAT_KEY_0[] = {0xBE, 0x95, 0x9C, 0xA8, 0x30, 0x8D, 0xEF, 0xA2, 0xE5, 0xE1, 0x80, 0xC6, 0x37, 0x12, 0xA9, 0xAE};
unsigned char EDAT_HASH_0[] = {0xEF, 0xFE, 0x5B, 0xD1, 0x65, 0x2E, 0xEB, 0xC1, 0x19, 0x18, 0xCF, 0x7C, 0x04, 0xD4, 0xF0, 0x11};
unsigned char EDAT_KEY_1[] = {0x4C, 0xA9, 0xC1, 0x4B, 0x01, 0xC9, 0x53, 0x09, 0x96, 0x9B, 0xEC, 0x68, 0xAA, 0x0B, 0xC0, 0x81};
unsigned char EDAT_HASH_1[] = {0x3D, 0x92, 0x69, 0x9B, 0x70, 0x5B, 0x07, 0x38, 0x54, 0xD8, 0xFC, 0xC6, 0xC7, 0x67, 0x27, 0x47};
unsigned char EDAT_IV[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char NPDRM_PSP_KEY_1[] = {0x2A, 0x6A, 0xFB, 0xCF, 0x43, 0xD1, 0x57, 0x9F, 0x7D, 0x73, 0x87, 0x41, 0xA1, 0x3B, 0xD4, 0x2E};
unsigned char NPDRM_PSP_KEY_2[] = {0x0D, 0xB8, 0x57, 0x32, 0x36, 0x6C, 0xD7, 0x34, 0xFC, 0x87, 0x9E, 0x74, 0x33, 0x43, 0xBB, 0x4F};
unsigned char NPDRM_PSX_KEY[] = {0x52, 0xC0, 0xB5, 0xCA, 0x76, 0xD6, 0x13, 0x4B, 0xB4, 0x5F, 0xC6, 0x6C, 0xA6, 0x37, 0xF2, 0xC1};
unsigned char NPDRM_KLIC_KEY[] = {0xF2, 0xFB, 0xCA, 0x7A, 0x75, 0xB0, 0x4E, 0xDC, 0x13, 0x90, 0x63, 0x8C, 0xCD, 0xFD, 0xD1, 0xEE};
unsigned char NPDRM_OMAC_KEY_1[] = {0x72, 0xF9, 0x90, 0x78, 0x8F, 0x9C, 0xFF, 0x74, 0x57, 0x25, 0xF0, 0x8E, 0x4C, 0x12, 0x83, 0x87};
unsigned char NPDRM_OMAC_KEY_2[] = {0x6B, 0xA5, 0x29, 0x76, 0xEF, 0xDA, 0x16, 0xEF, 0x3C, 0x33, 0x9F, 0xB2, 0x97, 0x1E, 0x25, 0x6B};
unsigned char NPDRM_OMAC_KEY_3[] = {0x9B, 0x51, 0x5F, 0xEA, 0xCF, 0x75, 0x06, 0x49, 0x81, 0xAA, 0x60, 0x4D, 0x91, 0xA5, 0x4E, 0x97};

unsigned char RAP_KEY[] = {0x86, 0x9F, 0x77, 0x45, 0xC1, 0x3F, 0xD8, 0x90, 0xCC, 0xF2, 0x91, 0x88, 0xE3, 0xCC, 0x3E, 0xDF};
unsigned char RAP_PBOX[] = {0x0C, 0x03, 0x06, 0x04, 0x01, 0x0B, 0x0F, 0x08, 0x02, 0x07, 0x00, 0x05, 0x0A, 0x0E, 0x0D, 0x09};
unsigned char RAP_E1[] = {0xA9, 0x3E, 0x1F, 0xD6, 0x7C, 0x55, 0xA3, 0x29, 0xB7, 0x5F, 0xDD, 0xA6, 0x2A, 0x95, 0xC7, 0xA5};
unsigned char RAP_E2[] = {0x67, 0xD4, 0x5D, 0xA3, 0x29, 0x6D, 0x00, 0x6A, 0x4E, 0x7C, 0x53, 0x7B, 0xF5, 0x53, 0x8C, 0x74};

unsigned char VSH_CURVE_P[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char VSH_CURVE_A[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC};
unsigned char VSH_CURVE_B[] = {0xA6, 0x8B, 0xED, 0xC3, 0x34, 0x18, 0x02, 0x9C, 0x1D, 0x3C, 0xE3, 0x3B, 0x9A, 0x32, 0x1F, 0xCC, 0xBB, 0x9E, 0x0F, 0x0B};
unsigned char VSH_CURVE_N[] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xB5, 0xAE, 0x3C, 0x52, 0x3E, 0x63, 0x94, 0x4F, 0x21, 0x27};
unsigned char VSH_CURVE_GX[] = {0x12, 0x8E, 0xC4, 0x25, 0x64, 0x87, 0xFD, 0x8F, 0xDF, 0x64, 0xE2, 0x43, 0x7B, 0xC0, 0xA1, 0xF6, 0xD5, 0xAF, 0xDE, 0x2C};
unsigned char VSH_CURVE_GY[] = {0x59, 0x58, 0x55, 0x7E, 0xB1, 0xDB, 0x00, 0x12, 0x60, 0x42, 0x55, 0x24, 0xDB, 0xC3, 0x79, 0xD5, 0xAC, 0x5F, 0x4A, 0xDF};

unsigned char VSH_PUB[] = {0x62, 0x27, 0xB0, 0x0A, 0x02, 0x85, 0x6F, 0xB0, 0x41, 0x08, 0x87, 0x67, 0x19, 0xE0, 0xA0, 0x18, 0x32, 0x91, 0xEE, 0xB9,
						   0x6E, 0x73, 0x6A, 0xBF, 0x81, 0xF7, 0x0E, 0xE9, 0x16, 0x1B, 0x0D, 0xDE, 0xB0, 0x26, 0x76, 0x1A, 0xFF, 0x7B, 0xC8, 0x5B};


// Main crypto functions.
void rap2rif(unsigned char* rap, unsigned char* rif)
{
	int i;
	int round;

	unsigned char key[0x10];
	unsigned char iv[0x10];
	memset(key, 0, 0x10);
	memset(iv, 0, 0x10);

	// Initial decrypt.
	aescbc128_decrypt(RAP_KEY, iv, rap, key, 0x10);

	// rap2rifkey round.
	for (round = 0; round < 5; ++round)
	{
		for (i = 0; i < 16; ++i)
		{
			int p = RAP_PBOX[i];
			key[p] ^= RAP_E1[p];
		}
		for (i = 15; i >= 1; --i)
		{
			int p = RAP_PBOX[i];
			int pp = RAP_PBOX[i - 1];
			key[p] ^= key[pp];
		}
		int o = 0;
		for (i = 0; i < 16; ++i)
		{
			int p = RAP_PBOX[i];
			unsigned char kc = key[p] - o;
			unsigned char ec2 = RAP_E2[p];
			if (o != 1 || kc != 0xFF)
			{
				o = kc < ec2 ? 1 : 0;
				key[p] = kc - ec2;
			}
			else if (kc == 0xFF)
			{
				key[p] = kc - ec2;
			}
			else
			{
				key[p] = kc;
			}
		}
	}

	memcpy(rif, key, 0x10);
}

void generate_key(int crypto_mode, int version, unsigned char *key_final, unsigned char *iv_final, unsigned char *key, unsigned char *iv)
{
	int mode = (int)(crypto_mode & 0xF0000000);
	switch (mode) {
	case 0x10000000:
		// Encrypted ERK.
		// Decrypt the key with EDAT_KEY + EDAT_IV and copy the original IV.
		aescbc128_decrypt(version ? EDAT_KEY_1 : EDAT_KEY_0, EDAT_IV, key, key_final, 0x10);
		memcpy(iv_final, iv, 0x10);
		break;
	case 0x20000000:
		// Default ERK.
		// Use EDAT_KEY and EDAT_IV.
		memcpy(key_final, version ? EDAT_KEY_1 : EDAT_KEY_0, 0x10);
		memcpy(iv_final, EDAT_IV, 0x10);
		break;
	case 0x00000000:
		// Unencrypted ERK.
		// Use the original key and iv.
		memcpy(key_final, key, 0x10);
		memcpy(iv_final, iv, 0x10);
		break;
	};
}

void generate_hash(int hash_mode, int version, unsigned char *hash_final, unsigned char *hash)
{
	int mode = (int)(hash_mode & 0xF0000000);
	switch (mode) {
	case 0x10000000:
		// Encrypted HASH.
		// Decrypt the hash with EDAT_KEY + EDAT_IV.
		aescbc128_decrypt(version ? EDAT_KEY_1 : EDAT_KEY_0, EDAT_IV, hash, hash_final, 0x10);
		break;
	case 0x20000000:
		// Default HASH.
		// Use EDAT_HASH.
		memcpy(hash_final, version ? EDAT_HASH_1 : EDAT_HASH_0, 0x10);
		break;
	case 0x00000000:
		// Unencrypted ERK.
		// Use the original hash.
		memcpy(hash_final, hash, 0x10);
		break;
	};
}

bool decrypt(int hash_mode, int crypto_mode, int version, unsigned char *in, unsigned char *out, int length, unsigned char *key, unsigned char *iv, unsigned char *hash, unsigned char *test_hash)
{
	// Setup buffers for key, iv and hash.
	unsigned char key_final[0x10] = {};
	unsigned char iv_final[0x10] = {};
	unsigned char hash_final_10[0x10] = {};
	unsigned char hash_final_14[0x14] = {};

	// Generate crypto key and hash.
	generate_key(crypto_mode, version, key_final, iv_final, key, iv);
	if ((hash_mode & 0xFF) == 0x01)
		generate_hash(hash_mode, version, hash_final_14, hash);
	else
		generate_hash(hash_mode, version, hash_final_10, hash);

	if ((crypto_mode & 0xFF) == 0x01)  // No algorithm.
	{
		memcpy(out, in, length);
	}
	else if ((crypto_mode & 0xFF) == 0x02)  // AES128-CBC
	{
		aescbc128_decrypt(key_final, iv_final, in, out, length);
	}
	else
	{
		printf("Error: Unknown crypto algorithm!");
		return false;
	}
	
	if ((hash_mode & 0xFF) == 0x01) // 0x14 SHA1-HMAC
	{
		return hmac_hash_compare(hash_final_14, 0x14, in, length, test_hash, 0x14);
	}
	else if ((hash_mode & 0xFF) == 0x02)  // 0x10 AES-CMAC
	{
		return cmac_hash_compare(hash_final_10, 0x10, in, length, test_hash, 0x10);
	}
	else if ((hash_mode & 0xFF) == 0x04) //0x10 SHA1-HMAC
	{
		return hmac_hash_compare(hash_final_10, 0x10, in, length, test_hash, 0x10);
	}
	else
	{
		printf("Error: Unknown hashing algorithm!");
		return false;
	}
}

bool encrypt(int hash_mode, int crypto_mode, int version, unsigned char *in, unsigned char *out, int length, unsigned char *key, unsigned char *iv, unsigned char *hash, unsigned char *test_hash)
{
	// Setup buffers for key, iv and hash.
	unsigned char key_final[0x10] = {};
	unsigned char iv_final[0x10] = {};
	unsigned char hash_final_10[0x10] = {};
	unsigned char hash_final_14[0x14] = {};

	// Generate crypto key and hash.
	generate_key(crypto_mode, version, key_final, iv_final, key, iv);
	if ((hash_mode & 0xFF) == 0x01)
		generate_hash(hash_mode, version, hash_final_14, hash);
	else
		generate_hash(hash_mode, version, hash_final_10, hash);

	if ((crypto_mode & 0xFF) == 0x01)  // No algorithm.
	{
		memcpy(out, in, length);
	}
	else if ((crypto_mode & 0xFF) == 0x02)  // AES128-CBC
	{
		aescbc128_encrypt(key_final, iv_final, in, out, length);
	}
	else
	{
		printf("Error: Unknown crypto algorithm!");
		return false;
	}

	if ((hash_mode & 0xFF) == 0x01) // 0x14 SHA1-HMAC
	{
		hmac_hash_forge(hash_final_14, 0x14, out, length, test_hash);
		return true;
	}
	else if ((hash_mode & 0xFF) == 0x02)  // 0x10 AES-CMAC
	{
		cmac_hash_forge(hash_final_10, 0x10, out, length, test_hash);
		return true;
	}
	else if ((hash_mode & 0xFF) == 0x04) //0x10 SHA1-HMAC
	{
		hmac_hash_forge(hash_final_10, 0x10, out, length, test_hash);
		return true;
	}
	else
	{
		printf("Error: Unknown hashing algorithm!");
		return false;
	}
}

// EDAT/SDAT functions.
unsigned char* dec_section(unsigned char* metadata)
{
	unsigned char *dec = (unsigned char *) malloc(0x10);
	dec[0x00] = (metadata[0xC] ^ metadata[0x8] ^ metadata[0x10]);
	dec[0x01] = (metadata[0xD] ^ metadata[0x9] ^ metadata[0x11]);
	dec[0x02] = (metadata[0xE] ^ metadata[0xA] ^ metadata[0x12]);
	dec[0x03] = (metadata[0xF] ^ metadata[0xB] ^ metadata[0x13]);
	dec[0x04] = (metadata[0x4] ^ metadata[0x8] ^ metadata[0x14]);
	dec[0x05] = (metadata[0x5] ^ metadata[0x9] ^ metadata[0x15]);
	dec[0x06] = (metadata[0x6] ^ metadata[0xA] ^ metadata[0x16]);
	dec[0x07] = (metadata[0x7] ^ metadata[0xB] ^ metadata[0x17]);
	dec[0x08] = (metadata[0xC] ^ metadata[0x0] ^ metadata[0x18]);
	dec[0x09] = (metadata[0xD] ^ metadata[0x1] ^ metadata[0x19]);
	dec[0x0A] = (metadata[0xE] ^ metadata[0x2] ^ metadata[0x1A]);
	dec[0x0B] = (metadata[0xF] ^ metadata[0x3] ^ metadata[0x1B]);
	dec[0x0C] = (metadata[0x4] ^ metadata[0x0] ^ metadata[0x1C]);
	dec[0x0D] = (metadata[0x5] ^ metadata[0x1] ^ metadata[0x1D]);
	dec[0x0E] = (metadata[0x6] ^ metadata[0x2] ^ metadata[0x1E]);
	dec[0x0F] = (metadata[0x7] ^ metadata[0x3] ^ metadata[0x1F]);
	return dec;
}

unsigned char* get_block_key(int block, NPD_HEADER *npd)
{
	unsigned char empty_key[0x10] = {};
	unsigned char *src_key = (npd->version <= 1) ? empty_key : npd->dev_hash;
	unsigned char *dest_key = (unsigned char *) malloc(0x10);
	memcpy(dest_key, src_key, 0xC);
	dest_key[0xC] = (block >> 24 & 0xFF);
	dest_key[0xD] = (block >> 16 & 0xFF);
	dest_key[0xE] = (block >> 8 & 0xFF);
	dest_key[0xF] = (block & 0xFF);
	return dest_key;
}

// EDAT/SDAT decryption.
int decrypt_data(FILE *in, FILE *out, EDAT_HEADER *edat, NPD_HEADER *npd, unsigned char* crypt_key)
{
	// Get metadata info and setup buffers.
	int block_num = (int)((edat->file_size + edat->block_size - 1) / edat->block_size);
	int metadata_section_size = ((edat->flags & EDAT_COMPRESSED_FLAG) != 0 || (edat->flags & EDAT_FLAG_0x20) != 0) ? 0x20 : 0x10;
	int metadata_offset = 0x100;

	unsigned char *enc_data;
	unsigned char *dec_data;
	unsigned char *b_key;
	unsigned char *iv;

	unsigned char hash[0x10];
	unsigned char key_result[0x10];
	unsigned char hash_result[0x14];
	memset(hash, 0, 0x10);
	memset(key_result, 0, 0x10);
	memset(hash_result, 0, 0x14);

	unsigned long long offset = 0;
	unsigned long long metadata_sec_offset = 0;
	int length = 0;
	int compression_end = 0;
	unsigned char empty_iv[0x10] = {};

	// Decrypt the metadata.
	int i;
	task_Init(block_num);
	for (i = 0; i < block_num; i++)
	{
		task_Update2(i);
		if(cancel || copy_cancel) {
			if( DEBUG ) printf("Warning : user canceled");
			task_End();
			return 1;
		}
		
		memset(hash_result, 0, 0x14);

		if ((edat->flags & EDAT_COMPRESSED_FLAG) != 0)
		{
			metadata_sec_offset = metadata_offset + (unsigned long long) i * metadata_section_size;
			fseek(in, metadata_sec_offset, SEEK_SET);

			unsigned char metadata[0x20];
			memset(metadata, 0, 0x20);
			fread(metadata, 0x20, 1, in);

			// If the data is compressed, decrypt the metadata.
			// NOTE: For NPD version 1 the metadata is not encrypted.
			if (npd->version <= 1)
			{
				offset = SWAP_BE(*(unsigned long long*)&metadata[0x10]);
				length = SWAP_BE(*(int*)&metadata[0x18]);
				compression_end = SWAP_BE(*(int*)&metadata[0x1C]);
			}
			else
			{
				unsigned char *result = dec_section(metadata);
				offset = SWAP_BE(*(unsigned long long*)&result[0]);
				length = SWAP_BE(*(int*)&result[8]);
				compression_end = SWAP_BE(*(int*)&result[12]);
				free(result);
			}

			memcpy(hash_result, metadata, 0x10);
		}
		else if ((edat->flags & EDAT_FLAG_0x20) != 0)
		{
			// If FLAG 0x20, the metadata precedes each data block.
			metadata_sec_offset = metadata_offset + (unsigned long long) i * (metadata_section_size + length);
			fseek(in, metadata_sec_offset, SEEK_SET);

			unsigned char metadata[0x20];
			memset(metadata, 0, 0x20);
			fread(metadata, 0x20, 1, in);
			memcpy(hash_result, metadata, 0x14);

			// If FLAG 0x20 is set, apply custom xor.
			int j;
			for (j = 0; j < 0x10; j++)
				hash_result[j] = (unsigned char)(metadata[j] ^ metadata[j + 0x10]);

			offset = metadata_sec_offset + 0x20;
			length = edat->block_size;

			if ((i == (block_num - 1)) && (edat->file_size % edat->block_size))
				length = (int)(edat->file_size % edat->block_size);
		}
		else
		{
			metadata_sec_offset = metadata_offset + (unsigned long long) i * metadata_section_size;
			fseek(in, metadata_sec_offset, SEEK_SET);

			fread(hash_result, 0x10, 1, in);
			offset = metadata_offset + (unsigned long long) i * edat->block_size + (unsigned long long) block_num * metadata_section_size;
			length = edat->block_size;

			if ((i == (block_num - 1)) && (edat->file_size % edat->block_size))
				length = (int)(edat->file_size % edat->block_size);
		}

		// Locate the real data.
		int pad_length = length;
		length = (int)((pad_length + 0xF) & 0xFFFFFFF0);

		// Setup buffers for decryption and read the data.
		enc_data = (unsigned char *) malloc(length);
		dec_data = (unsigned char *) malloc(length);
		memset(enc_data, 0, length);
		memset(dec_data, 0, length);
		memset(hash, 0, 0x10);
		memset(key_result, 0, 0x10);

		fseek(in, offset, SEEK_SET);
		fread(enc_data, length, 1, in);

		// Generate a key for the current block.
		b_key = get_block_key(i, npd);

		// Encrypt the block key with the crypto key.
		aesecb128_encrypt(crypt_key, b_key, key_result);
		if ((edat->flags & EDAT_FLAG_0x10) != 0)
			aesecb128_encrypt(crypt_key, key_result, hash);  // If FLAG 0x10 is set, encrypt again to get the final hash.
		else
			memcpy(hash, key_result, 0x10);

		// Setup the crypto and hashing mode based on the extra flags.
		int crypto_mode = ((edat->flags & EDAT_FLAG_0x02) == 0) ? 0x2 : 0x1;
		int hash_mode;

		if ((edat->flags  & EDAT_FLAG_0x10) == 0)
			hash_mode = 0x02;
		else if ((edat->flags & EDAT_FLAG_0x20) == 0)
			hash_mode = 0x04;
		else
			hash_mode = 0x01;

		if ((edat->flags  & EDAT_ENCRYPTED_KEY_FLAG) != 0)
		{
			crypto_mode |= 0x10000000;
			hash_mode |= 0x10000000;
		}

		if ((edat->flags  & EDAT_DEBUG_DATA_FLAG) != 0)
		{
			// Reset the flags.
			crypto_mode |= 0x01000000;
			hash_mode |= 0x01000000;
			// Simply copy the data without the header or the footer.
			memcpy(dec_data, enc_data, length);
		}
		else
		{
			// IV is null if NPD version is 1 or 0.
			iv = (npd->version <= 1) ? empty_iv : npd->digest;
			// Call main crypto routine on this data block.
			if (!decrypt(hash_mode, crypto_mode, (npd->version == 4), enc_data, dec_data, length, key_result, iv, hash, hash_result))
			{
				if (DEBUG)
					printf("WARNING: Block at offset 0x%llx has invalid hash!", offset);
					
				task_End();
				return 1;
			}
		}

		// Apply additional compression if needed and write the decrypted data.
		if (((edat->flags & EDAT_COMPRESSED_FLAG) != 0) && compression_end)
		{
			int decomp_size = (int)edat->file_size;
			unsigned char *decomp_data = (unsigned char *) malloc(decomp_size);
			memset(decomp_data, 0, decomp_size);

			if (DEBUG)
				printf("Decompressing data...");

			int res = decompress(decomp_data, dec_data, decomp_size);
			fwrite(decomp_data, res, 1, out);

			if (DEBUG)
			{
				printf("Compressed block size: %d", pad_length);
				printf("Decompressed block size: %d", res);
			}

			edat->file_size -= res;

			if (edat->file_size == 0)
			{
				if (res < 0)
				{
					printf("EDAT/SDAT decompression failed!");
					task_End();
					return 1;
				}
				else
					printf("EDAT/SDAT successfully decompressed!");
			}

			free(decomp_data);
		}
		else
		{
			fwrite(dec_data, pad_length, 1, out);
		}

		free(enc_data);
		free(dec_data);
	}
	
	task_End(i);
	return 0;
}

int check_data(unsigned char *key, EDAT_HEADER *edat, NPD_HEADER *npd, FILE *f)
{
	fseek(f, 0, SEEK_SET);
	unsigned char header[0xA0];
	unsigned char empty_header[0xA0];
	unsigned char header_hash[0x10];
	unsigned char metadata_hash[0x10];
	memset(header, 0, 0xA0);
	memset(empty_header, 0, 0xA0);
	memset(header_hash, 0, 0x10);
	memset(metadata_hash, 0, 0x10);

	// Check NPD version and flags.
	if ((npd->version == 0) || (npd->version == 1))
	{
		if (edat->flags & 0x7EFFFFFE)
		{
			printf("Error: Bad header flags!");
			return 1;
		}
	}
	else if (npd->version == 2)
	{
		if (edat->flags & 0x7EFFFFE0)
		{
			printf("Error: Bad header flags!");
			return 1;
		}
	}
	else if ((npd->version == 3) || (npd->version == 4))
	{
		if (edat->flags & 0x7EFFFFC0)
		{
			printf("Error: Bad header flags!");
			return 1;
		}
	}
	else
	{
		printf("Error: Unknown version!");
		return 1;
	}

	// Read in the file header.
	fread(header, 0xA0, 1, f);

	// Read in the header and metadata section hashes.
	fseek(f, 0x90, SEEK_SET);
	fread(metadata_hash, 0x10, 1, f);
	fread(header_hash, 0x10, 1, f);

	// Setup the hashing mode and the crypto mode used in the file.
	int crypto_mode = 0x1;
	int hash_mode = ((edat->flags & EDAT_ENCRYPTED_KEY_FLAG) == 0) ? 0x00000002 : 0x10000002;
	if ((edat->flags & EDAT_DEBUG_DATA_FLAG) != 0)
	{
		hash_mode |= 0x01000000;

		if (DEBUG)
			printf("DEBUG data detected!");
	}

	// Setup header key and iv buffers.
	unsigned char header_key[0x10];
	unsigned char header_iv[0x10];
	memset(header_key, 0, 0x10);
	memset(header_iv, 0, 0x10);

	// Test the header hash (located at offset 0xA0).
	if (!decrypt(hash_mode, crypto_mode, (npd->version == 4), header, empty_header, 0xA0, header_key, header_iv, key, header_hash))
	{
		if (DEBUG)
			printf("WARNING: Header hash is invalid!");

		// If the header hash test fails and the data is not DEBUG, then RAP/RIF/KLIC key is invalid.
		if ((edat->flags & EDAT_DEBUG_DATA_FLAG) != EDAT_DEBUG_DATA_FLAG)
		{
			printf("Error: RAP/RIF/KLIC key is invalid!");
			return 1;
		}
	}

	// Parse the metadata info.
	int metadata_section_size = ((edat->flags & EDAT_COMPRESSED_FLAG) != 0 || (edat->flags & EDAT_FLAG_0x20) != 0) ? 0x20 : 0x10;
	if (((edat->flags & EDAT_COMPRESSED_FLAG) != 0))
	{
		if (DEBUG)
			printf("COMPRESSED data detected!");
	}

	int block_num = (int)((edat->file_size + edat->block_size - 1) / edat->block_size);
	int metadata_offset = 0x100;
	int metadata_size = metadata_section_size * block_num;
	long long metadata_section_offset = metadata_offset;

	long bytes_read = 0;
	long bytes_to_read = metadata_size;
	unsigned char *metadata = (unsigned char *) malloc(metadata_size);
	unsigned char *empty_metadata = (unsigned char *) malloc(metadata_size);

	while (bytes_to_read > 0)
	{
		// Locate the metadata blocks.
		fseek(f, metadata_section_offset, SEEK_SET);

		// Read in the metadata.
		fread(metadata + bytes_read, metadata_section_size, 1, f);

		// Adjust sizes.
		bytes_read += metadata_section_size;
		bytes_to_read -= metadata_section_size;

		if (((edat->flags & EDAT_FLAG_0x20) != 0)) // Metadata block before each data block.
			metadata_section_offset += (metadata_section_size + edat->block_size);
		else
			metadata_section_offset += metadata_section_size;
	}

	// Test the metadata section hash (located at offset 0x90).
	if (!decrypt(hash_mode, crypto_mode, (npd->version == 4), metadata, empty_metadata, metadata_size, header_key, header_iv, key, metadata_hash))
	{
		if (DEBUG)
			printf("WARNING: Metadata section hash is invalid!");
	}

	// Checking ECDSA signatures.
	if ((edat->flags & EDAT_DEBUG_DATA_FLAG) == 0)
	{
		printf("Checking signatures...");

		// Setup buffers.
		unsigned char metadata_signature[0x28];
		unsigned char header_signature[0x28];
		unsigned char signature_hash[20];
		unsigned char signature_r[0x15];
		unsigned char signature_s[0x15];
		unsigned char zero_buf[0x15];
		memset(metadata_signature, 0, 0x28);
		memset(header_signature, 0, 0x28);
		memset(signature_hash, 0, 20);
		memset(signature_r, 0, 0x15);
		memset(signature_s, 0, 0x15);
		memset(zero_buf, 0, 0x15);

		// Setup ECDSA curve and public key.
		ecdsa_set_curve(VSH_CURVE_P, VSH_CURVE_A, VSH_CURVE_B, VSH_CURVE_N, VSH_CURVE_GX, VSH_CURVE_GY);
		ecdsa_set_pub(VSH_PUB);


		// Read in the metadata and header signatures.
		fseek(f, 0xB0, SEEK_SET);
		fread(metadata_signature, 0x28, 1, f);
		fseek(f, 0xD8, SEEK_SET);
		fread(header_signature, 0x28, 1, f);

		// Checking metadata signature.
		// Setup signature r and s.
		memcpy(signature_r + 01, metadata_signature, 0x14);
		memcpy(signature_s + 01, metadata_signature + 0x14, 0x14);
		if ((!memcmp(signature_r, zero_buf, 0x15)) || (!memcmp(signature_s, zero_buf, 0x15)))
			printf("Metadata signature is invalid!");
		else
		{
			// Setup signature hash.
			if ((edat->flags & EDAT_FLAG_0x20) != 0) //Sony failed again, they used buffer from 0x100 with half size of real metadata.
			{
				int metadata_buf_size = block_num * 0x10;
				unsigned char *metadata_buf = (unsigned char *) malloc(metadata_buf_size);
				fseek(f, metadata_offset, SEEK_SET);
				fread(metadata_buf, metadata_buf_size, 1, f);
				sha1(metadata_buf, metadata_buf_size, signature_hash);
				free(metadata_buf);
			}
			else
				sha1(metadata, metadata_size, signature_hash);

			if (!ecdsa_verify(signature_hash, signature_r, signature_s))
			{
				printf("Metadata signature is invalid!");
				if (((unsigned long long)edat->block_size * block_num) > 0x100000000)
					printf("*Due to large file size, metadata signature status may be incorrect!");
			}
			else
				printf("Metadata signature is valid!");
		}


		// Checking header signature.
		// Setup header signature r and s.
		memset(signature_r, 0, 0x15);
		memset(signature_s, 0, 0x15);
		memcpy(signature_r + 01, header_signature, 0x14);
		memcpy(signature_s + 01, header_signature + 0x14, 0x14);

		if ((!memcmp(signature_r, zero_buf, 0x15)) || (!memcmp(signature_s, zero_buf, 0x15)))
			printf("Header signature is invalid!");
		else
		{
			// Setup header signature hash.
			memset(signature_hash, 0, 20);
			unsigned char *header_buf = (unsigned char *) malloc(0xD8);
			fseek(f, 0x00, SEEK_SET);
			fread(header_buf, 0xD8, 1, f);
			sha1(header_buf, 0xD8, signature_hash );
			free(header_buf);

			if (ecdsa_verify(signature_hash, signature_r, signature_s))
				printf("Header signature is valid!");
			else
				printf("Header signature is invalid!");
		}
	}

	// Cleanup.
	free(metadata);
	free(empty_metadata);

	return 0;
}

int validate_npd_hashes(const char* file_name, unsigned char *klicensee, NPD_HEADER *npd)
{
	int title_hash_result = 0;
	int dev_hash_result = 0;

	int file_name_length = strlen(file_name);
	unsigned char *buf = (unsigned char *) malloc(0x30 + file_name_length);
	unsigned char dev[0x60];
	unsigned char key[0x10];
	memset(dev, 0, 0x60);
	memset(key, 0, 0x10);

	// Build the title buffer (content_id + file_name).
	memcpy(buf, npd->content_id, 0x30);
	memcpy(buf + 0x30, file_name, file_name_length);

	// Build the dev buffer (first 0x60 bytes of NPD header in big-endian).
	memcpy(dev, npd, 0x60);

	// Fix endianness.
	int version = SWAP_BE(npd->version);
	int license = SWAP_BE(npd->license);
	int type = SWAP_BE(npd->type);
	memcpy(dev + 0x4, &version, 4);
	memcpy(dev + 0x8, &license, 4);
	memcpy(dev + 0xC, &type, 4);

	// Hash with NPDRM_OMAC_KEY_3 and compare with title_hash.
	title_hash_result = cmac_hash_compare(NPDRM_OMAC_KEY_3, 0x10, buf, 0x30 + file_name_length, npd->title_hash, 0x10);

	if (DEBUG)
	{
		if (title_hash_result)
			printf("NPD title hash is valid!");
		else
			printf("WARNING: NPD title hash is invalid!");
	}

	// Check for an empty dev_hash (can't validate if devklic is NULL);
	bool isDevklicEmpty = true;
	int i;
	for (i = 0; i < 0x10; i++)
	{
		if (klicensee[i] != 0)
		{
			isDevklicEmpty = false;
			break;
		}
	}

	if (isDevklicEmpty)
	{
		if (DEBUG)
			printf("NPD dev hash is empty!");

		// Allow empty dev hash.
		dev_hash_result = 1;
	}
	else
	{
		// Generate klicensee xor key.
		xor(key, klicensee, NPDRM_OMAC_KEY_2, 0x10);

		// Hash with generated key and compare with dev_hash.
		dev_hash_result = cmac_hash_compare(key, 0x10, dev, 0x60, npd->dev_hash, 0x10);

		if (DEBUG)
		{
			if (dev_hash_result)
				printf("NPD dev hash is valid!");
			else
				printf("WARNING: NPD dev hash is invalid!");
		}
	}

	free(buf);

	return (title_hash_result && dev_hash_result);
}

bool extract_data(FILE *input, FILE *output, const char* input_file_name, unsigned char* devklic, unsigned char* rifkey)
{
	// Setup NPD and EDAT/SDAT structs.
	NPD_HEADER *NPD = (NPD_HEADER *) malloc(sizeof(NPD_HEADER));
	EDAT_HEADER *EDAT = (EDAT_HEADER *) malloc(sizeof(EDAT_HEADER));

	// Read in the NPD and EDAT/SDAT headers.
	char npd_header[0x80];
	char edat_header[0x10];
	fread(npd_header, sizeof(npd_header), 1, input);
	fread(edat_header, sizeof(edat_header), 1, input);

	memcpy(NPD->magic, npd_header, 4);
	NPD->version = SWAP_BE(*(int*)&npd_header[4]);
	NPD->license = SWAP_BE(*(int*)&npd_header[8]);
	NPD->type = SWAP_BE(*(int*)&npd_header[12]);
	memcpy(NPD->content_id, (unsigned char*)&npd_header[16], 0x30);
	memcpy(NPD->digest, (unsigned char*)&npd_header[64], 0x10);
	memcpy(NPD->title_hash, (unsigned char*)&npd_header[80], 0x10);
	memcpy(NPD->dev_hash, (unsigned char*)&npd_header[96], 0x10);
	NPD->unk1 = SWAP_BE(*(u64*)&npd_header[112]);
	NPD->unk2 = SWAP_BE(*(u64*)&npd_header[120]);

	unsigned char npd_magic[4] = {0x4E, 0x50, 0x44, 0x00};  //NPD0
	if (memcmp(NPD->magic, npd_magic, 4))
	{
		printf("Error: File has invalid NPD header.");
		return 1;
	}

	memcpy(&EDAT->flags, edat_header, 4); // avoid warning
	EDAT->flags = SWAP_BE(EDAT->flags);
	EDAT->block_size = SWAP_BE(*(int*)&edat_header[4]);
	EDAT->file_size = SWAP_BE(*(u64*)&edat_header[8]);

	printf("NPD HEADER");
	printf("NPD version: %d", NPD->version);
	printf("NPD license: %d", NPD->license);
	printf("NPD type: %x", NPD->type);
	printf("NPD content ID: %s", NPD->content_id);

	// Set decryption key.
	unsigned char key[0x10];
	memset(key, 0, 0x10);

	// Check EDAT/SDAT flag.
	if ((EDAT->flags & SDAT_FLAG) == SDAT_FLAG)
	{
		if( DEBUG ) {
			printf("SDAT HEADER");
			printf("SDAT flags: 0x%08X", EDAT->flags);
			printf("SDAT block size: 0x%08X", EDAT->block_size);
			printf("SDAT file size: 0x%llX", EDAT->file_size);
		}
		// Generate SDAT key.
		xor(key, NPD->dev_hash, SDAT_KEY, 0x10);
	}
	else
	{
		if( DEBUG ) {
			printf("EDAT HEADER");
			printf("EDAT flags: 0x%08X", EDAT->flags);
			printf("EDAT block size: 0x%08X", EDAT->block_size);
			printf("EDAT file size: 0x%llX", EDAT->file_size);
		}

		// Perform header validation (EDAT only).
		char real_file_name[MAX_PATH];
		extract_file_name(input_file_name, real_file_name);
		if (!validate_npd_hashes(real_file_name, devklic, NPD))
		{
			// Ignore header validation in DEBUG data.
			if ((EDAT->flags & EDAT_DEBUG_DATA_FLAG) != EDAT_DEBUG_DATA_FLAG)
			{
				printf("Error: NPD hash validation failed!");
				return 1;
			}
		}

		// Select EDAT key.
		if ((NPD->license & 0x3) == 0x3)           // Type 3: Use supplied devklic.
			memcpy(key, devklic, 0x10);
		else if (((NPD->license & 0x2) == 0x2)     // Type 2: Use key from RAP file (RIF key).
			|| ((NPD->license & 0x1) == 0x1))      // Type 1: Use network activation (RIF key).
		{
			memcpy(key, rifkey, 0x10);

			// Make sure we don't have an empty RIF key.
			int i, test = 0;
			for (i = 0; i < 0x10; i++)
			{
				if (key[i] != 0)
				{
					test = 1;
					break;
				}
			}
			
			if (!test)
			{
				printf("Error: A valid RAP/RIF file is needed for this EDAT file!");
				return 1;
			}
		}

		if (DEBUG)
		{
			printf("DEVKLIC: ");
			hex_print_load((char *)(char *)devklic, 0x10);
			printf("RIF KEY: ");
			hex_print_load((char *)rifkey, 0x10);
		}
	}

	if (DEBUG)
	{
		printf("DECRYPTION KEY: ");
		hex_print_load((char *)key, 0x10);
	}

	printf("Parsing data...");
	if (check_data(key, EDAT, NPD, input))
	{
		printf("Parsing failed!");
		return 1;
	}
	else
		printf("File successfully parsed!");

	printf("Decrypting data...");
	if(decrypt_data(input, output, EDAT, NPD, key))
	{
		printf("Decryption failed!");
		return 1;
	}
	else
		printf("File successfully decrypted!");

	free(NPD);
	free(EDAT);

	return 0;
}

// EDAT/SDAT encryption.
int encrypt_data(FILE *in, FILE *out, EDAT_HEADER *edat, NPD_HEADER *npd, unsigned char* crypt_key)
{
	// Set metadata info and setup buffers.
	int block_num = (int) ((edat->file_size + edat->block_size - 1) / edat->block_size);
	int metadata_offset = 0x100;

	unsigned char *enc_data;
	unsigned char *dec_data;
	unsigned char *b_key;
	unsigned char *iv;

	unsigned char hash[0x10];
	unsigned char key_result[0x10];
	unsigned char hash_result[0x14];
	long long offset = 0;
	int length = 0;
	int compression_end = 0;
	unsigned char empty_iv[0x10] = {};

	// Build special data footers for each version.
	unsigned char edat_footer_v1[0x10] = {0x45, 0x44, 0x41, 0x54, 0x41, 0x20, 0x70, 0x61, 0x63, 0x6B, 0x61, 0x67, 0x65, 0x72, 0x00, 0x00};
	unsigned char edat_footer_v2[0x10] = {0x45, 0x44, 0x41, 0x54, 0x41, 0x20, 0x32, 0x2E, 0x34, 0x2E, 0x30, 0x2E, 0x57, 0x00, 0x00, 0x00};
	unsigned char edat_footer_v3[0x10] = {0x45, 0x44, 0x41, 0x54, 0x41, 0x20, 0x33, 0x2E, 0x33, 0x2E, 0x30, 0x2E, 0x57, 0x00, 0x00, 0x00};
	unsigned char edat_footer_v4[0x10] = {0x45, 0x44, 0x41, 0x54, 0x41, 0x20, 0x34, 0x2E, 0x30, 0x2E, 0x30, 0x2E, 0x57, 0x00, 0x00, 0x00};
	unsigned char sdat_footer_v1[0x10] = {0x53, 0x44, 0x41, 0x54, 0x41, 0x20, 0x70, 0x61, 0x63, 0x6B, 0x61, 0x67, 0x65, 0x72, 0x00, 0x00};
	unsigned char sdat_footer_v2[0x10] = {0x53, 0x44, 0x41, 0x54, 0x41, 0x20, 0x32, 0x2E, 0x34, 0x2E, 0x30, 0x2E, 0x57, 0x00, 0x00, 0x00};
	unsigned char sdat_footer_v3[0x10] = {0x53, 0x44, 0x41, 0x54, 0x41, 0x20, 0x33, 0x2E, 0x33, 0x2E, 0x30, 0x2E, 0x57, 0x00, 0x00, 0x00};
	unsigned char sdat_footer_v4[0x10] = {0x53, 0x44, 0x41, 0x54, 0x41, 0x20, 0x34, 0x2E, 0x30, 0x2E, 0x30, 0x2E, 0x57, 0x00, 0x00, 0x00};

	// Encrypt the data and generate the metadata.
	task_Init(block_num);
	int i;
	for (i = 0; i < block_num; i++)
	{
		task_Update2(i);
		if(cancel || copy_cancel) {
			task_End();
			return 1;
			break;
		}
		
		memset(hash_result, 0, 0x14);

		offset = (unsigned long long)i * edat->block_size;
		length = edat->block_size;

		if ((i == (block_num - 1)) && (edat->file_size % edat->block_size))
			length = (int)(edat->file_size % edat->block_size);

		// Locate the real data.
		int pad_length = length;
		length = (int)((pad_length + 0xF) & 0xFFFFFFF0);
		fseek(in, offset, SEEK_SET);

		// Setup buffers for encryption and read the data.
		enc_data = (unsigned char *) malloc(length);
		dec_data = (unsigned char *) malloc(length);
		memset(enc_data, 0, length);
		memset(dec_data, 0, length);
		memset(hash, 0, 0x10);
		memset(key_result, 0, 0x10);
		fread(dec_data, pad_length, 1, in);

		// Generate a key for the current block.
		b_key = get_block_key(i, npd);

		// Encrypt the block key with the crypto key.
		aesecb128_encrypt(crypt_key, b_key, key_result);
		if ((edat->flags & EDAT_FLAG_0x10) != 0)
			aesecb128_encrypt(crypt_key, key_result, hash);  // If FLAG 0x10 is set, encrypt again to get the final hash.
		else
			memcpy(hash, key_result, 0x10);

		// Setup the crypto and hashing mode based on the extra flags.
		int crypto_mode = ((edat->flags & EDAT_FLAG_0x02) == 0) ? 0x2 : 0x1;
		int hash_mode;

		if ((edat->flags & EDAT_FLAG_0x10) == 0)
			hash_mode = 0x02;
		else if ((edat->flags & EDAT_FLAG_0x20) == 0)
			hash_mode = 0x04;
		else
			hash_mode = 0x01;

		if ((edat->flags & EDAT_ENCRYPTED_KEY_FLAG) != 0)
		{
			crypto_mode |= 0x10000000;
			hash_mode |= 0x10000000;
		}

		if ((edat->flags & EDAT_DEBUG_DATA_FLAG) != 0)
		{
			// Reset the flags.
			crypto_mode |= 0x01000000;
			hash_mode |= 0x01000000;
			// Simply copy the data.
			memcpy(enc_data, dec_data, length);
		}
		else
		{
			// IV is null if NPD version is 1 or 0.
			iv = (npd->version <= 1) ? empty_iv : npd->digest;
			// Call main crypto routine on this data block.
			if (!encrypt(hash_mode, crypto_mode, (npd->version == 4), dec_data, enc_data, length, key_result, iv, hash, hash_result))
			{
				if (DEBUG)
					printf("WARNING: Block at offset 0x%08x got invalid forged hash!", offset);
			}
		}

		// Write the metadata and the encrypted data.
		if ((edat->flags & EDAT_COMPRESSED_FLAG) != 0)
		{
			unsigned long long data_offset = metadata_offset + (unsigned long long) i * edat->block_size + (unsigned long long) block_num * 0x20;

			// If the data is compressed, encrypt the metadata.
			unsigned char dec_metadata[0x20];
			unsigned char enc_metadata[0x20];
			memset(dec_metadata, 0, 0x20);
			memset(enc_metadata, 0, 0x20);

			// Build the metadata section.
			u64 data_offset_be = SWAP_BE(data_offset);
			int length_be = SWAP_BE(pad_length);
			int compression_end_be = SWAP_BE(compression_end);
			memcpy(dec_metadata, hash_result, 0x10);
			memcpy(dec_metadata + 0x10, &data_offset_be, 8);
			memcpy(dec_metadata + 0x10 + 8, &length_be, 4);
			memcpy(dec_metadata + 0x10 + 12, &compression_end_be, 4);

			// Encrypt the metadata section.
			// NOTE: For NPD version 1 the metadata is not encrypted.
			if (npd->version <= 1)
			{
				memcpy(enc_metadata, dec_metadata, 0x20);
			}
			else
			{
				memcpy(enc_metadata, dec_metadata, 0x10);
				memcpy(enc_metadata + 0x10, dec_section(dec_metadata), 0x10);
			}

			// Write the encrypted metadata if DEBUG flag is not set.
			if ((edat->flags & EDAT_DEBUG_DATA_FLAG) == 0)
			{
				fseek(out, metadata_offset + (unsigned long long) i * 0x20, SEEK_SET);
				fwrite(enc_metadata, 0x20, 1, out);
			}

			// Write the encrypted data.
			fseek(out, data_offset, SEEK_SET);
			fwrite(enc_data, length, 1, out);
		}
		else if ((edat->flags & EDAT_FLAG_0x20) != 0)
		{
			unsigned long long data_offset = metadata_offset + (unsigned long long) i * edat->block_size + ((unsigned long long) i + 1) * 0x20;

			// If FLAG 0x20 is set, apply custom xor.
			unsigned char metadata[0x20];
			memset(metadata, 0, 0x20);

			// Use a fake XOR value and build the metadata.
			unsigned char hash_result_1[0x10];
			memset(hash_result_1, 0, 0x10);
			unsigned char hash_result_2[0x10];
			memset(hash_result_2, 0, 0x10);
			prng(hash_result_2, 0x10);
			memcpy(hash_result_2, hash_result + 0x10, 0x04);

			int j;
			for (j = 0; j < 0x10; j++)
				hash_result_1[j] = (unsigned char) (hash_result[j] ^ hash_result_2[j]);

			// Set the metadata.
			memcpy(metadata, hash_result_1, 0x10);
			memcpy(metadata + 0x10, hash_result_2, 0x10);

			// Write the encrypted metadata if DEBUG flag is not set.
			if ((edat->flags & EDAT_DEBUG_DATA_FLAG) == 0)
			{
				fseek(out, metadata_offset + (unsigned long long) i * 0x20 + offset, SEEK_SET);
				fwrite(metadata, 0x20, 1, out);
			}

			// Write the encrypted data.
			fseek(out, data_offset, SEEK_SET);
			fwrite(enc_data, length, 1, out);
		}
		else
		{
			unsigned long long data_offset = metadata_offset + (unsigned long long) i * edat->block_size + (unsigned long long) block_num * 0x10;

			// Write the encrypted metadata if DEBUG flag is not set.
			if ((edat->flags & EDAT_DEBUG_DATA_FLAG) == 0)
			{
				fseek(out, metadata_offset + (unsigned long long) i * 0x10, SEEK_SET);
				fwrite(hash_result, 0x10, 1, out);
			}

			// Write the encrypted data.
			fseek(out, data_offset, SEEK_SET);
			fwrite(enc_data, length, 1, out);
		}

		free(enc_data);
		free(dec_data);
	}
	task_End();
	
	// Before appending the footer, if the file is empty, seek to the metadata offset.
	if (edat->file_size == 0)
		fseek(out, metadata_offset, SEEK_SET);

	// Append the special version footer.
	if ((npd->version == 0) || (npd->version == 1))
	{
		if ((edat->flags & SDAT_FLAG) == SDAT_FLAG)
			fwrite(sdat_footer_v1, 0x10, 1, out);
		else
			fwrite(edat_footer_v1, 0x10, 1, out);
	}
	else if (npd->version == 2)
	{
		if ((edat->flags & SDAT_FLAG) == SDAT_FLAG)
			fwrite(sdat_footer_v2, 0x10, 1, out);
		else
			fwrite(edat_footer_v2, 0x10, 1, out);
	}
	else if (npd->version == 3)
	{
		if ((edat->flags & SDAT_FLAG) == SDAT_FLAG)
			fwrite(sdat_footer_v3, 0x10, 1, out);
		else
			fwrite(edat_footer_v3, 0x10, 1, out);
	}
	else if (npd->version == 4)
	{
		if ((edat->flags & SDAT_FLAG) == SDAT_FLAG)
			fwrite(sdat_footer_v4, 0x10, 1, out);
		else
			fwrite(edat_footer_v4, 0x10, 1, out);
	}

	return 0;
}

int forge_data(unsigned char *key, EDAT_HEADER *edat, NPD_HEADER *npd, FILE *f)
{
	unsigned char header[0xA0];
	unsigned char empty_header[0xA0];
	unsigned char header_hash[0x10];
	unsigned char metadata_hash[0x10];
	unsigned char header_signature[0x28];
	unsigned char metadata_signature[0x28];
	memset(header, 0, 0xA0);
	memset(empty_header, 0, 0xA0);
	memset(header_hash, 0, 0x10);
	memset(metadata_hash, 0, 0x10);
	memset(header_signature, 0, 0x28);
	memset(metadata_signature, 0, 0x28);

	// Setup the hashing mode and the crypto mode used in the file.
	int crypto_mode = 0x1;
	int hash_mode = ((edat->flags & EDAT_ENCRYPTED_KEY_FLAG) == 0) ? 0x00000002 : 0x10000002;
	if ((edat->flags & EDAT_DEBUG_DATA_FLAG) != 0)
		hash_mode |= 0x01000000;

	// Setup header key and iv buffers.
	unsigned char header_key[0x10];
	unsigned char header_iv[0x10];
	memset(header_key, 0, 0x10);
	memset(header_iv, 0, 0x10);

	// Parse the metadata info.
	int metadata_section_size = ((edat->flags & EDAT_COMPRESSED_FLAG) != 0 || (edat->flags & EDAT_FLAG_0x20) != 0) ? 0x20 : 0x10;
	int block_num = (int)((edat->file_size + edat->block_size - 1) / edat->block_size);
	int metadata_offset = 0x100;
	int metadata_size = metadata_section_size * block_num;
	long long metadata_section_offset = metadata_offset;

	long bytes_read = 0;
	long bytes_to_read = metadata_size;
	unsigned char *metadata = (unsigned char *) malloc(metadata_size);
	unsigned char *empty_metadata = (unsigned char *) malloc(metadata_size);

	while (bytes_to_read > 0)
	{
		// Locate the metadata blocks.
		fseek(f, metadata_section_offset, SEEK_SET);

		// Read in the metadata.
		fread(metadata + bytes_read, metadata_section_size, 1, f);

		// Adjust sizes.
		bytes_read += metadata_section_size;
		bytes_to_read -= metadata_section_size;

		if (((edat->flags & EDAT_FLAG_0x20) != 0)) // Metadata block before each data block.
			metadata_section_offset += (metadata_section_size + edat->block_size);
		else
			metadata_section_offset += metadata_section_size;
	}

	// Generate the metadata section hash (located at offset 0x90).
	encrypt(hash_mode, crypto_mode, (npd->version == 4), metadata, empty_metadata, metadata_size, header_key, header_iv, key, metadata_hash);

	// Write back the forged metadata section hash.
	fseek(f, 0x90, SEEK_SET);
	fwrite(metadata_hash, 0x10, 1, f);

	// Read in the file header.
	fseek(f, 0, SEEK_SET);
	fread(header, 0xA0, 1, f);

	// Generate the header hash (located at offset 0xA0).
	encrypt(hash_mode, crypto_mode, (npd->version == 4), header, empty_header, 0xA0, header_key, header_iv, key, header_hash);

	// Write back the forged header section hash.
	fseek(f, 0xA0, SEEK_SET);
	fwrite(header_hash, 0x10, 1, f);

	// ECDSA header signature (fill with random data for now).
	fseek(f, 0xB0, SEEK_SET);
	prng(header_signature, 0x28);
	fwrite(header_signature, 0x28, 1, f);

	// ECDSA metadata signature (fill with random data for now).
	fseek(f, 0xD8, SEEK_SET);
	prng(metadata_signature, 0x28);
	fwrite(metadata_signature, 0x28, 1, f);

	// Cleanup.
	free(metadata);
	free(empty_metadata);

	return 0;
}

void forge_npd_title_hash(const char* file_name, NPD_HEADER *npd)
{
	int file_name_length = strlen(file_name);
	unsigned char *buf = (unsigned char *) malloc(0x30 + file_name_length);
	unsigned char title_hash[0x10];
	memset(title_hash, 0, 0x10);

	// Build the title buffer (content_id + file_name).
	memcpy(buf, npd->content_id, 0x30);
	memcpy(buf + 0x30, file_name, file_name_length);

	// Forge with NPDRM_OMAC_KEY_3 and create the title hash.
	cmac_hash_forge(NPDRM_OMAC_KEY_3, 0x10, buf, 0x30 + file_name_length, title_hash);

	// Write the key in the NPD header.
	memcpy(npd->title_hash, title_hash, 0x10);

	free(buf);
}

void forge_npd_dev_hash(unsigned char *klicensee, NPD_HEADER *npd)
{
	unsigned char key[0x10];
	unsigned char dev[0x60];
	unsigned char dev_hash[0x10];
	memset(key, 0, 0x10);
	memset(dev, 0, 0x60);
	memset(dev_hash, 0, 0x10);

	// Build the dev buffer (first 0x60 bytes of NPD header in big-endian).
	memcpy(dev, npd, 0x60);

	// Fix endianness.
	int version = SWAP_BE(npd->version);
	int license = SWAP_BE(npd->license);
	int type = SWAP_BE(npd->type);
	memcpy(dev + 0x4, &version, 4);
	memcpy(dev + 0x8, &license, 4);
	memcpy(dev + 0xC, &type, 4);

	// Generate klicensee xor key.
	xor(key, klicensee, NPDRM_OMAC_KEY_2, 0x10);

	// Forge with the generated key and create the dev hash.
	cmac_hash_forge(key, 0x10, dev, 0x60, dev_hash);

	// Write the key in the NPD header.
	memcpy(npd->dev_hash, dev_hash, 0x10);
}

bool pack_data(FILE *input, FILE *output, const char* input_file_name, unsigned char* content_id, unsigned char* devklic, unsigned char* rifkey, int version, int license, int type, int block, bool useCompression, bool isEDAT, bool isFinalized)
{
	// Get file size.
	fseek(input, 0, SEEK_END);
	long long input_file_size = ftell(input);
	fseek(input, 0, SEEK_SET);

	// Setup NPD and EDAT/SDAT structs.
	NPD_HEADER *NPD = (NPD_HEADER *) malloc(sizeof(NPD_HEADER));
	EDAT_HEADER *EDAT = (EDAT_HEADER *) malloc(sizeof(EDAT_HEADER));

	// Forge NPD header.
	unsigned char npd_magic[4] = {0x4E, 0x50, 0x44, 0x00};  //NPD0
	unsigned char fake_digest[0x10];
	memset(fake_digest, 0, 0x10);
	prng(fake_digest, 0x10);
	memcpy(NPD->magic, npd_magic, 4);
	NPD->version = ((version == 1) && (!isFinalized)) ? 0 : version;

	// Check for debug or finalized data.
	if (isFinalized)
	{
		NPD->license = license;
		NPD->type = type;
		memcpy(NPD->content_id, content_id, 0x30);
		memcpy(NPD->digest, fake_digest, 0x10);
		char real_file_name[MAX_PATH];
		extract_file_name(input_file_name, real_file_name);
		forge_npd_title_hash(real_file_name, NPD);
		forge_npd_dev_hash(devklic, NPD);
		NPD->unk1 = 0;
		NPD->unk2 = 0;
	}

	// Forge EDAT/SDAT header with fixed values for flags and block size.
	if (version == 1)
	{
		// Version 1 is only valid for EDAT files.
		if (isEDAT)
		{
			EDAT->flags = 0x00;
			if (useCompression) EDAT->flags |= EDAT_COMPRESSED_FLAG;
			if (!isFinalized) EDAT->flags |= EDAT_DEBUG_DATA_FLAG;
		}
		else
		{
			printf("Error: Invalid version for SDAT!");
			return 1;
		}
	}
	else if (version == 2)
	{
		EDAT->flags = 0x0C;
		if (useCompression) EDAT->flags |= EDAT_COMPRESSED_FLAG;
		if (!isEDAT) EDAT->flags |= SDAT_FLAG;
		if (!isFinalized) EDAT->flags |= EDAT_DEBUG_DATA_FLAG;
	}
	else
	{
		// Version 3 and 4 use 0x3C and 0x0D flags (there is no 0x3D flag).
		EDAT->flags = 0x3C;
		if (useCompression) EDAT->flags = (0x0C | EDAT_COMPRESSED_FLAG);
		if (!isEDAT) EDAT->flags |= SDAT_FLAG;
		if (!isFinalized) EDAT->flags |= EDAT_DEBUG_DATA_FLAG;
	}

	EDAT->block_size = block * 1024;
	EDAT->file_size = input_file_size;

	printf("NPD HEADER");
	printf("NPD version: %d", NPD->version);
	printf("NPD license: %d", NPD->license);
	printf("NPD type: %x", NPD->type);
	printf("NPD content ID: %s", NPD->content_id);
	
	// Set encryption key.
	unsigned char key[0x10];
	memset(key, 0, 0x10);

	// Check EDAT/SDAT flag.
	if ((EDAT->flags & SDAT_FLAG) == SDAT_FLAG)
	{
		printf("SDAT HEADER");
		printf("SDAT flags: 0x%08X", EDAT->flags);
		printf("SDAT block size: 0x%08X", EDAT->block_size);
		printf("SDAT file size: 0x%llX", EDAT->file_size);

		// Generate SDAT key.
		xor(key, NPD->dev_hash, SDAT_KEY, 0x10);
	}
	else
	{
		printf("EDAT HEADER");
		printf("EDAT flags: 0x%08X", EDAT->flags);
		printf("EDAT block size: 0x%08X", EDAT->block_size);
		printf("EDAT file size: 0x%llX", EDAT->file_size);

		// Select EDAT key.
		if ((NPD->license & 0x3) == 0x3)        // Type 3: Use supplied devklic.
			memcpy(key, devklic, 0x10);
		else if ((NPD->license & 0x2) == 0x2)   // Type 2: Use key from RAP file (RIF key).
		{
			memcpy(key, rifkey, 0x10);

			// Make sure we don't have an empty RIF key.
			int i, test = 0;
			for (i = 0; i < 0x10; i++)
			{
				if (key[i] != 0)
				{
					test = 1;
					break;
				}
			}

			if (!test)
			{
				printf("Error: A valid RAP/RIF file is needed for this EDAT file!");
				return 1;
			}
		}
		else if ((NPD->license & 0x1) == 0x1)    // Type 1: Use network activation.
		{
			printf("Error: Network license not supported!");
			return 1;
		}

		if (DEBUG)
		{
			printf("DEVKLIC: ");
			hex_print_load((char *)devklic, 0x10);
			printf("RIF KEY: ");
			hex_print_load((char *)rifkey, 0x10);
		}
	}

	if (DEBUG)
	{
		printf("ENCRYPTION KEY: ");
		hex_print_load((char *)key, 0x10);
	}

	// Write forged NPD header.
	int version_be = SWAP_BE(NPD->version);
	int license_be = SWAP_BE(NPD->license);
	int type_be = SWAP_BE(NPD->type);
	u64 unk1_be = SWAP_BE(NPD->unk1);
	u64 unk2_be = SWAP_BE(NPD->unk2);
	fwrite(NPD->magic, sizeof(NPD->magic), 1, output);
	fwrite(&version_be, sizeof(version_be), 1, output);
	fwrite(&license_be, sizeof(license_be), 1, output);
	fwrite(&type_be, sizeof(type_be), 1, output);
	fwrite(NPD->content_id, sizeof(NPD->content_id), 1, output);
	fwrite(NPD->digest, sizeof(NPD->digest), 1, output);
	fwrite(NPD->title_hash, sizeof(NPD->title_hash), 1, output);
	fwrite(NPD->dev_hash, sizeof(NPD->dev_hash), 1, output);
	fwrite(&unk1_be, sizeof(unk1_be), 1, output);
	fwrite(&unk2_be, sizeof(unk2_be), 1, output);

	// Write forged EDAT/SDAT header.
	int flags_be = SWAP_BE(EDAT->flags);
	int block_size_be = SWAP_BE(EDAT->block_size);
	u64 file_size_be = SWAP_BE(EDAT->file_size);
	fwrite(&flags_be, sizeof(flags_be), 1, output);
	fwrite(&block_size_be, sizeof(block_size_be), 1, output);
	fwrite(&file_size_be, sizeof(file_size_be), 1, output);

	printf("Encrypting data...");
	if (encrypt_data(input, output, EDAT, NPD, key))
	{
		printf("Encryption failed!");
		return 1;
	}
	else
		printf("File successfully encrypted!");

	// Only forge finalized data.
	if (isFinalized)
	{
		printf("Forging data...");
		if (forge_data(key, EDAT, NPD, output))
		{
			printf("Forging failed!");
			return 1;
		}
		else
			printf("File successfully forged!");
	}

	free(NPD);
	free(EDAT);

	return 0;
}

// too slow !
u8 npdata_bruteforce_old(char *npdata_file, char *source_file, u8 mode, u8 *dev_klicensee)
{
	FILE* input = NULL;
	FILE* source = NULL;

	u8 found = NO;
	
	input = fopen(npdata_file, "rb");
	if (input == NULL)
	{
		printf("Error: Please check your input file : %s", npdata_file);
		goto end;
	}
	
	source = fopen(source_file, "rb");
	if (source == NULL)
	{
		printf("Error: Please check your source file : %s", source_file);
		goto end;
	}
	
	// Get the source file size.
	fseek(source, 0, SEEK_END);
	long long source_file_size = ftell(source);
	fseek(source, 0, SEEK_SET);

	// Set up testing keys and hash.
	unsigned char test_key[0x10];
	unsigned char test_dev_hash[0x10];
	memset(test_key, 0, 0x10);
	memset(dev_klicensee, 0, 0x10);
	memset(test_dev_hash, 0, 0x10);
	
	// Buffer to handle klicensee as text.
	char test_klicensee_text[0x20];
	memset(test_klicensee_text, 0, 0x20);

	// Buffer to handle klicensee as unicode text.
	char test_klicensee_unicode_text[0x40];
	memset(test_klicensee_unicode_text, 0, 0x40);

	// Read the file's header magic and seek back.
	unsigned char magic[0x4];
	fread(magic, 0x4, 1, input);
	fseek(input, 0, SEEK_SET);

	// If header starts with SCE, the file is a SELF or SPRX.
	// If not, assume regular EDAT/SDAT (NPD).
	unsigned char sce_magic[4] = { 0x53, 0x43, 0x45, 0x00 };  //SCE0
	if (!memcmp(magic, sce_magic, 4))
	{
		// File is SCE, read the NPD dev_hash offset from the
		// first 0x10 bytes of the SCE header and seek to the NPD area.	
		unsigned char sce_header[0x10];
		fread(sce_header, 0x10, 1, input);
		short npd_offset = SWAP_BE(*(short*)&sce_header[0xE]) - 0x60;
		fseek(input, npd_offset, SEEK_SET);

		if (DEBUG)
		{
			printf("SCE file detected!");
			printf("NPD offset inside SCE: 0x%08x", npd_offset);
		}
	}

	// Read the first 0x60 bytes of the NPD header.
	unsigned char npd_buf[0x60];
	fread(npd_buf, 0x60, 1, input);

	// Read the NPD header dev_hash.
	fread(test_dev_hash, 0x10, 1, input);
	
	task_Init(source_file_size);
	printf("Brute-forcing dev_klicensee, source %s", source_file);
	u64 i;
	for (i = 0; i < source_file_size; i++)
	{	
     	task_Update2(i);
		
		// Binary
		if( (mode & NPDATA_BF_MODE_BINARY) || (mode & NPDATA_BF_MODE_BINARY_STREAM))
		{
			if( mode & NPDATA_BF_MODE_BINARY ) fseek(source, i, SEEK_SET);
			
			memset(dev_klicensee, 0, 0x10);
			fread(dev_klicensee, 0x10, 1, source);
			
			//test
			xor(test_key, dev_klicensee, NPDRM_OMAC_KEY_2, 0x10);
			if (cmac_hash_compare(test_key, 0x10, npd_buf, 0x60, test_dev_hash, 0x10))
			{
				found = YES;
				goto end;
			}
			
			if( mode & NPDATA_BF_MODE_BINARY_STREAM ) {
				i=ftell(source);
				continue;
			}
		}
		
		// Text
		if( (mode & NPDATA_BF_MODE_TEXT) || (mode & NPDATA_BF_MODE_TEXT_STREAM) || (mode & NPDATA_BF_MODE_LINES_STREAM))
		{
			if( mode & NPDATA_BF_MODE_TEXT) fseek(source, i, SEEK_SET);
			
			memset(test_klicensee_text, 0, 0x20);
			if(mode & NPDATA_BF_MODE_LINES_STREAM) {
				char line[512]={0};
				if( fgets(line, 512, source)==NULL ) goto end;
				memcpy(test_klicensee_text, line, 0x20);
			} else {
				fread(test_klicensee_text, 0x20, 1, source);
			}
			
			if (is_hex(test_klicensee_text, 0x20)) {
				hex_to_bytes(dev_klicensee, test_klicensee_text, 0x20);
				
				//test
				xor(test_key, dev_klicensee, NPDRM_OMAC_KEY_2, 0x10);
				if (cmac_hash_compare(test_key, 0x10, npd_buf, 0x60, test_dev_hash, 0x10))
				{
					found = YES;
					goto end;
				}
			}
			
			if( (mode & NPDATA_BF_MODE_TEXT_STREAM) || (mode & NPDATA_BF_MODE_LINES_STREAM)) {
				i=ftell(source);
				continue;
			}
		}
		
		// Unicode mode
		if( (mode & NPDATA_BF_MODE_UNICODE) || (mode & NPDATA_BF_MODE_UNICODE_STREAM))
		{
			if(mode & NPDATA_BF_MODE_UNICODE) fseek(source, i, SEEK_SET);
			
			memset(test_klicensee_unicode_text, 0, 0x40);
			fread(test_klicensee_unicode_text, 0x40, 1, source);

			// Convert unicode fullwidth to plain text.
			int uni_count;
			int txt_count = 0;
			for (uni_count = 0; uni_count < 0x40; uni_count += 2)
				test_klicensee_text[txt_count++] = test_klicensee_unicode_text[uni_count + 1];

			if (is_hex(test_klicensee_text, 0x20)) {
				hex_to_bytes(dev_klicensee, test_klicensee_text, 0x20);
				
				//test
				xor(test_key, dev_klicensee, NPDRM_OMAC_KEY_2, 0x10);
				if (cmac_hash_compare(test_key, 0x10, npd_buf, 0x60, test_dev_hash, 0x10))
				{
					found = true;
					goto end;
				}
			}
			if(mode & NPDATA_BF_MODE_UNICODE_STREAM) {
				i=ftell(source);
				continue;
			}
		}
	}

end:
	task_End();
	
	if(found) {
		printf("Found valid dev_klicensee!");
	} else {
		printf("Failed to brute-force dev_klicensee!");
		memset(dev_klicensee, 0, 0x10);
	}
	
	// Cleanup.
	FCLOSE(input);
	FCLOSE(source);
	
	return found;
	
}

void read_double_mem(char *data, u64 size, u8 **buffer, s64 *buffer_s, u64 buffer_o, u8 swap)
{
	memset(data, 0, size);
	if( buffer_s[swap] < buffer_o ) return;
	
	if( buffer_o + size <= buffer_s[swap]){
		memcpy(data, buffer[swap] + buffer_o, size);
	} else
	if( buffer_s[swap] < buffer_o + size && buffer_o + size - buffer_s[swap] <= buffer_s[!swap]) {
		memcpy(data, buffer[swap] + buffer_o, buffer_s[swap] - buffer_o);
		memcpy(data + buffer_s[swap] - buffer_o, buffer[!swap], buffer_o + size - buffer_s[swap]);
	}
}

void getline_double_mem(char **data, u64 *size, u8 **buffer, s64 *buffer_s, u64 buffer_o, u8 swap)
{
	if( buffer_s[swap] < buffer_o ) return;
	
	*size = 0;
	char *pointer = strchr((char *) buffer[swap] + buffer_o, '\n');
	if( pointer ) {
		*size = pointer - ((char *) buffer[swap] + buffer_o) + 1;
		*data = (char *) malloc(*size+1);
		if(*data==NULL) {
			*size=0;
			return;
		}
		memset(*data, 0, *size+1);
		memcpy(*data, buffer[swap] + buffer_o, *size);
	} else {
		if( buffer_s[!swap] ) pointer = strchr((char *) buffer[!swap], '\n');
		if( pointer ) {
			*size = buffer_s[swap] - buffer_o + (pointer - ((char *) buffer[!swap])) + 1;
		} else {
			*size = buffer_s[swap] - buffer_o;
		}
		*data = (char *) malloc(*size+1);
		if(*data==NULL) {
			*size=0;
			return;
		}
		memset(*data, 0, *size+1);
		memcpy(*data, buffer[swap] + buffer_o, buffer_s[swap] - buffer_o);
		if( pointer ) {
			memcpy(*data + buffer_s[swap] - buffer_o, buffer[!swap], (pointer - ((char *)buffer[!swap])) + 1);
		}
	}
}

char *get_klic_from_line(char *line, u64 size)
{
	int i;
	for(i=0; i<size; i++) {
		if(is_hex(line+i, 0x20)) return line+i;
	}
	
	return NULL;
}

u8 is_empty(u8 *data, u32 size)
{
	u32 i;
	for(i=0; i<size; i++) {
		if(data[0]!=0) return NO;
	}
	return YES;
}

#define BUFFER_SIZE	0x200000 // 2048 KiB
u8 npdata_bruteforce(char *npdata_file, char *source_file, u8 mode, u8 *dev_klicensee)
{
	FILE* input = NULL;
	FILE* source = NULL;
	u8 **buffer=NULL;

	u8 found = NO;
	
	source = fopen(source_file, "rb");
	if (source == NULL)
	{
		if(DEBUG) printf("Please check your source file %s", source_file);
		goto end;
	}
	
	input = fopen(npdata_file, "rb");
	if (input == NULL)
	{
		printf("Error: Please check your input file : %s", npdata_file);
		goto end;
	}
	
	buffer = (u8 **) malloc( 2 * sizeof(u8 *));
	if( buffer==NULL) 
	{
		printf("Error: malloc buffer");
		goto end;
	}
	buffer[0] = (u8 *) malloc(BUFFER_SIZE);
	buffer[1] = (u8 *) malloc(BUFFER_SIZE);
	if( buffer[0] == NULL || buffer[1] == NULL) 
	{
		printf("Error: malloc buffer[0], buffer[1]");
		goto end;
	}
	
	// Get the source file size.
	fseek(source, 0, SEEK_END);
	long long source_file_size = ftell(source);
	fseek(source, 0, SEEK_SET);

	// Set up testing keys and hash.
	unsigned char test_key[0x10];
	unsigned char test_dev_hash[0x10];
	memset(test_key, 0, 0x10);
	memset(dev_klicensee, 0, 0x10);
	memset(test_dev_hash, 0, 0x10);
	
	// Buffer to handle klicensee as text.
	char test_klicensee_text[0x20];
	memset(test_klicensee_text, 0, 0x20);

	// Buffer to handle klicensee as unicode text.
	char test_klicensee_unicode_text[0x40];
	memset(test_klicensee_unicode_text, 0, 0x40);

	// Read the file's header magic and seek back.
	unsigned char magic[0x4];
	fread(magic, 0x4, 1, input);
	fseek(input, 0, SEEK_SET);

	// If header starts with SCE, the file is a SELF or SPRX.
	// If not, assume regular EDAT/SDAT (NPD).
	unsigned char sce_magic[4] = { 0x53, 0x43, 0x45, 0x00 };  //SCE0
	if (!memcmp(magic, sce_magic, 4))
	{
		// File is SCE, read the NPD dev_hash offset from the
		// first 0x10 bytes of the SCE header and seek to the NPD area.	
		unsigned char sce_header[0x10];
		fread(sce_header, 0x10, 1, input);
		short npd_offset = SWAP_BE(*(short*)&sce_header[0xE]) - 0x60;
		fseek(input, npd_offset, SEEK_SET);

		if (DEBUG)
		{
			printf("SCE file detected!");
			printf("NPD offset inside SCE: 0x%08x", npd_offset);
		}
	}

	// Read the first 0x60 bytes of the NPD header.
	unsigned char npd_buf[0x60];
	fread(npd_buf, 0x60, 1, input);

	// Read the NPD header dev_hash.
	fread(test_dev_hash, 0x10, 1, input);
	
	task_Init(source_file_size);
	printf("Brute-forcing dev_klicensee, source %s", source_file);
	
	u8 swap=0; 
	u64 buffer_p=0; // global buffer offset
	u64 buffer_o = 0; // local buffer offset
	s64 buffer_s[2] = {0}; // buffer sizes	
	u64 offset = 0; // global file offset
	
	buffer_s[0] = fread(buffer[0], BUFFER_SIZE, 1, source);
	buffer_s[1] = fread(buffer[1], BUFFER_SIZE, 1, source);
	
	while( 1 )
	{
		if( buffer_s[swap] <= 0) break;
		if( source_file_size <= offset) break;
		
		buffer_o = offset - buffer_p;
		
		if(	buffer_s[swap] <= buffer_o ) {
			buffer_p += buffer_s[swap];
			memset(buffer[swap], 0, BUFFER_SIZE);
			buffer_s[swap] = fread(buffer[swap], BUFFER_SIZE, 1, source);
			swap = !swap;
			continue;
		}
		
		if(cancel || copy_cancel) break;
		
     	task_Update2(offset);
		
		// Binary
		if( (mode & NPDATA_BF_MODE_BINARY) || (mode & NPDATA_BF_MODE_BINARY_STREAM))
		{
				
			read_double_mem((char *) dev_klicensee, 0x10, buffer, buffer_s, buffer_o, swap);
			
			if( !is_empty(dev_klicensee, 0x10) ) { // probably already tested from the db : "dev_klic.txt"
				//test
				xor(test_key, dev_klicensee, NPDRM_OMAC_KEY_2, 0x10);
				if (cmac_hash_compare(test_key, 0x10, npd_buf, 0x60, test_dev_hash, 0x10))
				{
					found = YES;
					goto end;
				}
			}
			
			if( mode & NPDATA_BF_MODE_BINARY_STREAM ) { offset+=0x10; continue; }
		}
		
		// Text
		if( (mode & NPDATA_BF_MODE_TEXT) || (mode & NPDATA_BF_MODE_TEXT_STREAM) || (mode & NPDATA_BF_MODE_LINES_STREAM))
		{
			u64 size=0x20;
			memset(test_klicensee_text, 0, 0x20);
			if(mode & NPDATA_BF_MODE_LINES_STREAM) {
				char *line=NULL;
				getline_double_mem(&line, &size, buffer, buffer_s, buffer_o, swap);
				if( line ) {
					char *klic = get_klic_from_line(line, size); // 1 per line
					if(klic == NULL) {
						offset+=size; 
						free(line);
						continue;
					}
					strncpy(test_klicensee_text, klic, 0x20);
					free(line);
				}
			} else {
				read_double_mem(test_klicensee_text, size, buffer, buffer_s, buffer_o, swap);
			}
			
			if(is_hex(test_klicensee_text, 0x20)) {
				hex_to_bytes(dev_klicensee, test_klicensee_text, 0x20);
				
				//test
				xor(test_key, dev_klicensee, NPDRM_OMAC_KEY_2, 0x10);
				if (cmac_hash_compare(test_key, 0x10, npd_buf, 0x60, test_dev_hash, 0x10))
				{
					found = YES;
					goto end;
				}
			}
			
			if((mode & NPDATA_BF_MODE_TEXT_STREAM) || (mode & NPDATA_BF_MODE_LINES_STREAM)) { offset+=size; continue; }
		}
		
		// Unicode mode
		if( (mode & NPDATA_BF_MODE_UNICODE) || (mode & NPDATA_BF_MODE_UNICODE_STREAM))
		{
			read_double_mem(test_klicensee_unicode_text, 0x40, buffer, buffer_s, buffer_o, swap);
	
			// Convert unicode fullwidth to plain text.
			int uni_count;
			int txt_count = 0;
			for (uni_count = 0; uni_count < 0x40; uni_count += 2)
				test_klicensee_text[txt_count++] = test_klicensee_unicode_text[uni_count + 1];

			if(is_hex(test_klicensee_text, 0x20)) {
				hex_to_bytes(dev_klicensee, test_klicensee_text, 0x20);
				
				//test
				xor(test_key, dev_klicensee, NPDRM_OMAC_KEY_2, 0x10);
				if (cmac_hash_compare(test_key, 0x10, npd_buf, 0x60, test_dev_hash, 0x10))
				{
					found = true;
					goto end;
				}
			}
			if(mode & NPDATA_BF_MODE_UNICODE_STREAM) { offset+=0x40; continue; }
		}
		offset+=1;
	}

end:
	task_End();
	
	if(found) {
		printf("Found valid dev_klicensee!");
	} else {
		printf("Failed to brute-force dev_klicensee!");
		memset(dev_klicensee, 0, 0x10);
	}
	
	// Cleanup.
	FCLOSE(input);
	FCLOSE(source);
	if(buffer) {
		FREE(buffer[0]);
		FREE(buffer[1]);
		FREE(buffer);
	}
	
	return found;
}

u8 get_rifkey(char *rif_file, char *rap_file, u8 *rifkey)
{
	// Read the RIF/RAP file
	if( rif_file != NULL) {
		FILE *rif = NULL;
		rif = fopen(rif_file, "rb");
		if (rif != NULL) {
			fread(rifkey, 0x10, 1, rif);
			fclose(rif);
			return 0;
		}
	}
	
	if (rap_file != NULL)
	{
		FILE* rap = NULL;
		rap = fopen(rap_file, "rb");
		if (rap != NULL) {
			u8 rapkey[0x10]={0};
			memset(rapkey, 0, 0x10);
			fread(rapkey, 0x10, 1, rap);
			fclose(rap);
			rap2rif(rapkey, rifkey);
			return 0;
		}
	}
	
	return 1;
}

u8 npdata_decrypt(char *npdata_file, char *output_file, u8 *dev_klicensee, u8 *rifkey)
{
	FILE* input = NULL;
	FILE* output = NULL;
	int ret = FAILED;
	
	input = fopen(npdata_file, "rb");
	if (input == NULL)
	{
		printf("Error: Please check your input file : %s", npdata_file);
		goto end;
	}
	
	output = fopen(output_file, "wb");
	if (output == NULL)
	{
		printf("Error: Please check your output file %s", output_file);
		goto end;
	}
	// Delete the bad output file if any errors arise.
	if(extract_data(input, output, npdata_file, dev_klicensee, rifkey))
	{
		remove(output_file);
		goto end;
	}
	
	ret = SUCCESS;
end:
	// Cleanup.
	FCLOSE(input);
	FCLOSE(output);
	
	return ret;	
}

u8 npdata_encrypt(char *input_file, char *npdata_file, u8 *dev_klicensee, char *rap_file, char *rif_file, u8 format, u8 data, u8 version, u8 compression, u8 block, u8 license, u8 type, char *cID)
{
	u8 ret=FAILED;
	FILE* input = NULL;
	FILE* output= NULL;
	
	input = fopen(input_file, "rb");
	if (input == NULL)
	{
		printf("Error: Please check your input file : %s", input_file);
		goto end;
	}

	// Check for invalid parameters.
	if (((format > 1) || (format < 0))
		|| ((data > 1) || (data < 0))
		|| ((version > 4) || (version < 1))
		|| ((compression > 1) || (compression < 0))
		|| (((block != 1) && (block != 2) && (block != 4) 
			&& (block != 8) && (block != 16) && (block != 32))))
	{
		printf("Error: Invalid parameters!");
		goto end;
	}
	
	unsigned char rifkey[0x10];
	memset(rifkey, 0, 0x10);

	// Finalized EDAT mode only.
	if (format==NPDATA_FORMAT_EDAT && data==NPDATA_DATA_FINALIZED && license==NPDATA_LICENSE_LOCAL)
	{
		if( get_rifkey(rif_file, rap_file, rifkey) ) {
			printf("Error: RIF/RAP file is missing");
			goto end;
		}
	}
	
	output = fopen(npdata_file, "wb+");
	if (output == NULL)
	{
		printf("Error: cannot fopen %s", npdata_file);
		goto end;
	}

	// Delete the bad output file if any errors arise.
	if (pack_data(input, output, npdata_file, (unsigned char *)cID, dev_klicensee, rifkey, version, license, type, block, compression ? true : false, format ? true : false, data ? true : false))
	{
		remove(npdata_file);
		goto end;
	}

	ret=SUCCESS;
end:
	
	// Cleanup.
	FCLOSE(input);
	FCLOSE(output);
	return ret;
}