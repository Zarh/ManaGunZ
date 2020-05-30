#ifndef __GTF_H__
#define __GTF_H__

#if defined(__cplusplus)
extern	"C" {
#endif

bool gtf2dds(const char *gtf_fname, const char *dds_fname, uint8_t index, uint32_t option);
bool gtf2ddsFromBuffer(uint8_t *gtf_data_in, uint32_t gtf_size_in, uint8_t **dds_data_out, uint32_t *dds_size_out, uint8_t index, uint32_t option);

#if defined(__cplusplus)
}
#endif

#endif /* __GTF_H__ */
