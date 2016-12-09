#ifndef __GTF_H__
#define __GTF_H__

#if defined(__cplusplus)
extern	"C" {
#endif

bool gtf2dds(const char *gtf_fname, const char *dds_fname, uint8_t index, uint32_t option);

#if defined(__cplusplus)
}
#endif

#endif /* __GTF_H__ */
