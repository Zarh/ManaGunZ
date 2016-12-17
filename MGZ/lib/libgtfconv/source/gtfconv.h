#ifndef __GTFCONV_H__
#define __GTFCONV_H__

#include "version.h"
#include "utils.h"

#if defined(__cplusplus)
extern	"C" {
#endif


/* Macros for conversion option */
#define CELL_GTFCONV_FLAG_SWIZZLIZE     ( 1 << 0 )
#define CELL_GTFCONV_FLAG_UNNORMALIZE   ( 1 << 1 )
#define CELL_GTFCONV_FLAG_VERBOSE       ( 1 << 2 )
#define CELL_GTFCONV_FLAG_PACKED        ( 1 << 3 )

/* Error defined in this library */
#define CELL_GTFCONV_ERROR -1
#define CELL_GTFCONV_OK     0

typedef struct{
	uint8_t *addr;
	uint32_t size;
} GTF_BUFFER_T;

/* dds2gtf */
int32_t gtfconv_dds2gtf(GTF_BUFFER_T *gtfOutput, const GTF_BUFFER_T *ddsInput, uint8_t inputCount, uint32_t option);
int32_t gtfconv_dds2gtf_get_size(const GTF_BUFFER_T *ddsInput, uint8_t inputCount, uint32_t option);

/* gtf2dds */
int32_t gtfconv_gtf2dds(GTF_BUFFER_T *ddsOutput, const GTF_BUFFER_T *gtfInput, uint8_t index, uint32_t option);
int32_t gtfconv_gtf2dds_get_size(const GTF_BUFFER_T *gtfInput, uint8_t index, uint32_t option);
int16_t gtfconv_gtf2dds_get_texture_count(const GTF_BUFFER_T *gtfInput, uint32_t option);


#if defined(__cplusplus)
}
#endif

#endif /* __GTFCONV_H__ */
