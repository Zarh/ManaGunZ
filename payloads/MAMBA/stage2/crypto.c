#include <lv2/lv2.h>
#include <lv2/libc.h>

#include "common.h"
#include "crypto.h"

// For whatever reason, if this function gets inlined automatically, it fucks everything
// Stupid compiler
static __attribute__ ((noinline)) void xtea_encrypt_block(u32 *k, u32 *in, u32 *out)
{
	u32 sum, y, z;
	unsigned char i;

	sum = 0;
	y = in[0];
	z = in[1];

	for (i = 0; i < 32; i++)
	{
		y += (((z<<4) ^ (z>>5)) + z) ^ (sum + k[sum & 3]);
		sum += 0x9e3779b9;
		z += (((y<<4) ^ (y>>5)) + y) ^ (sum + k[sum>>11 & 3]);
	}

	out[0] = y;
	out[1] = z;
}

static inline void xor64(void *in, void *out)
{
	u8 *in8 = (u8 *)in;
	u8 *out8 = (u8 *)out;

	for (int i = 0; i < 8; i++)
		out8[i] ^= in8[i];
}

void xtea_ctr(u8 *key, u64 nounce, u8 *buf, int size)
{
	u8 ct[8];

	for (int i = 0; i < size; i += 8, ++nounce)
	{
		xtea_encrypt_block((u32 *)key, (u32 *)&nounce, (u32 *)ct);
		xor64(ct, buf + i);
	}
}
