#ifndef SOUND_DEFINED
#define SOUND_DEFINED

#include "ff.h"

typedef struct {		/* Sound FIFO control block */
	UINT mode;			/* Data format b0: mono(0)/stereo(1), b1: 8bit(0)/16bit(1) */
	volatile UINT ri, wi, ct;	/* FIFO read/write index and counter */
	BYTE *buff;			/* Pointer to FIFO buffer (must be 4-byte aligned) */
	UINT sz_buff;		/* Size of FIFO buffer (must be power of 2) */
} WAVFIFO;


int sound_start (WAVFIFO* fcb, DWORD fs);
void sound_stop (void);

int load_wav (FIL* fp, const char* title, void *work, UINT sz_work);

#endif
