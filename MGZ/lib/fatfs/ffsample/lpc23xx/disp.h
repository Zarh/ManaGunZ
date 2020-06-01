#ifndef _DISPLAY
#define _DISPLAY
#include <stdint.h>


#define _USE_FILE_LOADER	1	/* Enable file loaders */


/* Dot screen size */
#define DISP_XS	128
#define DISP_YS	128

/* Text screen size */
#define TS_WIDTH	26
#define TS_HEIGHT	13

/* RGB pixel data format (Create RGB565 from RGB888) */
#define RGB16(r,g,b)	(uint16_t)(((r) & 0xF8) << 8 | ((g) & 0xFC) << 3 | (b) >> 3)

#if _USE_FILE_LOADER
#include "ff.h"
#endif

extern const uint8_t FontH24[], FontH10[], FontZ10[];
extern volatile long TmrFrm;	/* Timer: to be increased 1000 in interval of 1ms */

void disp_init (void);

/* Grafix functions */
void disp_setmask (int left, int right, int top, int bottom);
void disp_rectfill (int left, int right, int top, int bottom, uint16_t color);
void disp_rect (int left, int right, int top, int bottom, uint16_t color);
void disp_moveto (int x, int y);
void disp_lineto (int x, int y, uint16_t color);
void disp_blt (int left, int right, int top, int bottom, const uint16_t *pat);

/* Text functions */
void disp_font_face (const uint8_t *font);
void disp_font_color (uint32_t color);
void disp_locate (int col, int row);
void disp_putc (uint8_t chr);

/* File loaders */
#if _USE_FILE_LOADER
void load_txt (FIL* fil, void* work, UINT sz_work);
void load_bmp (FIL* fil, void* work, UINT sz_work);
void load_jpg (FIL* fil, void* work, UINT sz_work);
void load_img (FIL* fil, void* work, UINT sz_work);
#endif


/* Color values */
#define	C_BLACK		RGB16(0,0,0)
#define	C_BLUE		RGB16(0,0,255)
#define	C_RED		RGB16(255,0,0)
#define	C_MAGENTA	RGB16(255,0,255)
#define	C_GREEN		RGB16(0,255,0)
#define	C_CYAN		RGB16(0,255,255)
#define	C_YELLOW	RGB16(255,255,0)
#define	C_WHITE		RGB16(255,255,255)
#define	C_LGRAY		RGB16(160,160,160)
#define	C_GRAY		RGB16(128,128,128)


/* File loader control buttons */
#define BTN_UP		'\x05'	/* (Up) ^[E] */
#define BTN_DOWN	'\x18'	/* (Down) ^[X] */
#define BTN_LEFT	'\x13'	/* (Left) ^[S] */
#define BTN_RIGHT	'\x04'	/* (Right) ^[D] */
#define BTN_OK		'\x0D'	/* (Ok) [Enter] */
#define BTN_CAN		'\x1B'	/* (Cancel) [Esc] */
#define BTN_PAUSE	' '		/* (Pause) [Space] */

#endif

