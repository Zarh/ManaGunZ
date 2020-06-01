/*----------------------------------------------------------------------------/
/ TJpgDec - Tiny JPEG Decompressor include file               (C)ChaN, 2011
/----------------------------------------------------------------------------*/
#ifndef _TJPGDEC
#define _TJPGDEC
/*---------------------------------------------------------------------------*/
/* System Configurations */

#define	JD_SZBUF		2048	/* Size of stream input buffer (should be multiple of 512) */
#define JD_FORMAT		1	/* Output RGB format 0:RGB888 (3 BYTE/pix), 1:RGB565 (1 WORD/pix) */
#define	JD_USE_SCALE	1	/* Use descaling feature for output */

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>


/* Error code */
typedef enum {
	JDR_OK = 0,	/* 0: Succeeded */
	JDR_INTR,	/* 1: Interrupted by output function */	
	JDR_INP,	/* 2: Device error or wrong termination of input stream */
	JDR_MEM1,	/* 3: Insufficient memory pool for the image */
	JDR_MEM2,	/* 4: Insufficient stream input buffer */
	JDR_PAR,	/* 5: Parameter error */
	JDR_FMT1,	/* 6: Data format error (may be damaged data) */
	JDR_FMT2,	/* 7: Right format but not supported */
	JDR_FMT3	/* 8: Not supported JPEG standard */
} JRESULT;



/* Rectangular structure */
typedef struct {
	uint16_t left, right, top, bottom;
} JRECT;



/* Decompressor object structure */
typedef struct JDEC JDEC;
struct JDEC {
	uint16_t dctr;				/* Number of bytes available in the input buffer */
	uint8_t* dptr;				/* Current data read ptr */
	uint8_t* inbuf;				/* Bit stream input buffer */
	uint8_t dmsk;				/* Current bit in the current read byte */
	uint8_t scale;				/* Output scaling ratio */
	uint8_t msx, msy;			/* MCU size in unit of block (width, height) */
	uint8_t qtid[3];			/* Quantization table ID of each component */
	int16_t dcv[3];				/* Previous DC element of each component */
	uint16_t nrst;				/* Restart inverval */
	uint16_t width, height;		/* Size of the input image (pixel) */
	uint8_t* huffbits[2][2];	/* Huffman bit distribution tables [id][dcac] */
	uint16_t* huffcode[2][2];	/* Huffman code word tables [id][dcac] */
	uint8_t* huffdata[2][2];	/* Huffman decoded data tables [id][dcac] */
	int32_t* qttbl[4];			/* Dequaitizer tables [id] */
	void* workbuf;				/* Working buffer for IDCT and RGB output */
	uint8_t* mcubuf;			/* Working buffer for the MCU */
	void* pool;					/* Pointer to available memory pool */
	uint16_t sz_pool;			/* Size of momory pool (bytes available) */
	uint16_t (*infunc)(JDEC*, uint8_t*, uint16_t);/* Pointer to jpeg stream input function */
	uint16_t (*outfunc)(JDEC*, void*, JRECT*);	/* Pointer to RGB output function */
	void* device;				/* Pointer to I/O device identifiler for the session */
};



/* TJpgDec API functions */
JRESULT jd_prepare (JDEC*, uint16_t(*)(JDEC*,uint8_t*,uint16_t), void*, uint16_t, void*);
JRESULT jd_decomp (JDEC*, uint16_t(*)(JDEC*,void*,JRECT*), uint8_t);


#ifdef __cplusplus
}
#endif

#endif /* _TJPGDEC */
