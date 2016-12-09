#include "mt19937.h"

void mt19937_init(mt19937_ctxt_t *ctxt, unsigned int seed)
{
	ctxt->state[0] = seed;

	for(ctxt->idx = 1; ctxt->idx < MT_N; ctxt->idx++)
		ctxt->state[ctxt->idx] = (1812433253 * (ctxt->state[ctxt->idx - 1] ^ (ctxt->state[ctxt->idx - 1] >> 30)) + ctxt->idx);

	ctxt->idx = MT_M + 1;
}

unsigned int mt19937_update(mt19937_ctxt_t *ctxt)
{
	unsigned int y, k;
	static unsigned int mag01[2] = {0, MT_MATRIX_A};

	if(ctxt->idx >= MT_N)
	{
		for(k = 0; k < MT_N - MT_M; k++)
		{
			y = (ctxt->state[k] & MT_UPPER_MASK) |
				(ctxt->state[k + 1] & MT_LOWER_MASK);
			ctxt->state[k] = ctxt->state[k + MT_M] ^ (y >> 1) ^ mag01[y & 1];
		}

		for(; k < MT_N - 1; k++)
		{
			y = (ctxt->state[k] & MT_UPPER_MASK) |
				(ctxt->state[k + 1] & MT_LOWER_MASK);
			ctxt->state[k] = ctxt->state[k + (MT_M - MT_N)] ^ (y >> 1) ^ mag01[y & 1];
		}

		y = (ctxt->state[MT_N - 1] & MT_UPPER_MASK) |
			(ctxt->state[0] & MT_LOWER_MASK);
		ctxt->state[MT_N - 1] = ctxt->state[MT_M - 1] ^ (y >> 1) ^ mag01[y & 1];

		ctxt->idx = 0;
	}

	y = ctxt->state[ctxt->idx++];

	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}
