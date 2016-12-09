#ifndef __7Z_H
#define __7Z_H

#ifdef __cplusplus
extern "C" {
#endif

int compress_deflate_7z(const unsigned char* in_data, unsigned in_size, unsigned char* out_data, unsigned *out_size, unsigned num_passes, unsigned num_fast_bytes);


#ifdef __cplusplus
}
#endif

#endif

