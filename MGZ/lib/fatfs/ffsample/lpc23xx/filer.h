#ifndef _FILER_DEF
#define _FILER_DEF

#include "ff.h"

void load_file (const char* fn, FIL fil[], void* work, UINT sz_work);
void filer (FIL* fil, void* work, UINT sz_work);

/* Filer control command */
#define KEY_UP		'\x05'	/* ^[E] */
#define KEY_DOWN	'\x18'	/* ^[X] */
#define KEY_LEFT	'\x13'	/* ^[S] */
#define KEY_RIGHT	'\x04'	/* ^[D] */
#define KEY_OK		'\x0D'	/* [Enter] */
#define KEY_CAN		'\x1B'	/* [Esc] */
#define KEY_BS		'\x08'	/* [BS] */
#define KEY_SPC		' '		/* [Space] */
#define KEY_MKDIR	'K'		/* [K] */
#define KEY_DRIVE	'D'		/* [D] */
#define KEY_COPY	'C'		/* [C] */
#define KEY_REMOVE	'U'		/* [U] */
#define KEY_RENAME	'N'		/* [N] */
#define KEY_ALL		'A'		/* [A] */
#define KEY_ATTRIB	'T'		/* [T] */

#endif
