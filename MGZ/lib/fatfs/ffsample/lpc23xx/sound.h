#ifndef SOUND_DEFINED
#define SOUND_DEFINED
#include "LPC2300.h"

#define USE_WAVPLAYER	1	/* Enable RIFF-WAV file player */


typedef struct {		/* Sound FIFO control block */
	uint32_t mode;		/* Data format b0: mono(0)/stereo(1), b1: 8bit(0)/16bit(1) */
	volatile uint32_t ri, wi, ct;	/* FIFO read/write index and counter */
	uint8_t *buff;		/* Pointer to FIFO buffer (must be 4-byte aligned) */
	uint32_t sz_buff;	/* Size of FIFO buffer (must be power of 2) */
} WAVFIFO;


int sound_start (WAVFIFO* fcb, uint32_t fs);
void sound_stop (void);
#if USE_WAVPLAYER
#include "ff.h"
int load_wav (FIL* fp, const char* title, void* work, uint32_t sz_work);
void load_m3u (FIL fp[], void* work, UINT sz_work);
#endif

#endif /* SOUND_DEFINED */
