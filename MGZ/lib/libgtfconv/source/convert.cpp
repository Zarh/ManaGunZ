#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

using namespace gtfconv;

namespace gtfconv{

inline void* convertMoveMemory(void* gtfptr, void* ddsptr, size_t size, bool bDds2Gtf)
{
	return (bDds2Gtf? memmove(gtfptr, ddsptr, size): memmove(ddsptr, gtfptr, size));
}

inline void convertMoveMemoryWithInvertEndian16(void* gtfptr, void* ddsptr, size_t size, bool bDds2Gtf)
{
	return (bDds2Gtf? memmove_with_invert_endian16(gtfptr, ddsptr, size): memmove_with_invert_endian16(ddsptr, gtfptr, size));
}

inline void convertMoveMemoryWithInvertEndian32(void* gtfptr, void* ddsptr, size_t size, bool bDds2Gtf)
{
	return (bDds2Gtf? memmove_with_invert_endian32(gtfptr, ddsptr, size): memmove_with_invert_endian32(ddsptr, gtfptr, size));
}

enum CellGtfconvEndianFlag{
	CELL_GTFCONV_ENDIAN_NOINVERT,
    CELL_GTFCONV_ENDIAN_INVERT32,
	CELL_GTFCONV_ENDIAN_INVERT16,
	CELL_GTFCONV_ENDIAN_INVERT32_EVEN
};

uint32_t getInvertFlag(CellGcmTexture tex)
{
	uint32_t invert_flag = CELL_GTFCONV_ENDIAN_INVERT32;

	uint8_t raw_format = gtfGetRawFormat(tex.format);
	bool is_dxt = gtfIsDxtn(raw_format);
	uint16_t depth = gtfGetDepth(raw_format);

	if(is_dxt){
		invert_flag = CELL_GTFCONV_ENDIAN_NOINVERT;
	}

	if(depth == 2){
		invert_flag = CELL_GTFCONV_ENDIAN_INVERT16;
	}

	if(depth == 4){
		invert_flag = CELL_GTFCONV_ENDIAN_INVERT32;
	}

	if(raw_format == CELL_GCM_TEXTURE_X16 || 
		raw_format == CELL_GCM_TEXTURE_Y16_X16 || 
		raw_format == CELL_GCM_TEXTURE_Y16_X16_FLOAT || 
		raw_format == CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT)
	{
		invert_flag = CELL_GTFCONV_ENDIAN_INVERT16;
	}

	if(raw_format == CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT || 
		raw_format == CELL_GCM_TEXTURE_X32_FLOAT)
	{
		invert_flag = CELL_GTFCONV_ENDIAN_INVERT32;
	}

	if(raw_format == CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW ||
		raw_format == CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW)
	{
		invert_flag = CELL_GTFCONV_ENDIAN_INVERT32_EVEN;
	}

	return invert_flag;
}

bool convertLayOutBuffer(layout_t *playout, CellGcmTexture tex, CellUtilDDSHeader ddsh)
{
	PRINTF("  [Layout]\n");

	uint8_t raw_format = gtfGetRawFormat(tex.format);
	bool is_dxt = gtfIsDxtn(raw_format);
	bool is_comp = (raw_format == CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW || 
				raw_format == CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW);

	uint16_t width = tex.width;
	uint16_t height = tex.height;
	uint16_t depth = tex.depth;
	uint32_t gtf_pitch = tex.pitch;
	uint8_t cube = 1;
	if(tex.cubemap == CELL_GCM_TRUE){
		cube = 6;
	}

	bool is_cube = (cube == 6);
	bool is_volume = (depth > 1);
	bool is_mip = (tex.mipmap > 1);

	if(gtf_pitch == 0){
        gtf_pitch = gtfGetPitch(raw_format, width);
	}
	uint16_t color_depth = gtfGetDepth(raw_format);

	// convert to different color_depth
	uint16_t dds_color_depth = 0;
	if(ddsh.ddspf.rgbBitCount == 24){
		dds_color_depth = 3;
	}
	if(ddsh.ddspf.fourCC == FOURCC_R16F){
		dds_color_depth = 2;
	}

	layout_t *ptr = playout;

	layout_t latest;
	memset(&latest, 0, sizeof(layout_t));

	// cubemap
	for(uint32_t n = 0; n < cube; ++n){
		bool new_face = true;
		uint16_t w = width;
		uint16_t h = height;
		uint16_t v = depth;
		uint16_t m = 0;
		
		// mipmap
		while( m < tex.mipmap ){
			layout_t layout;
			memset(&layout, 0, sizeof(layout_t));

			layout.width = w;
			layout.height = h;
			layout.depth = v;
			layout.pitch = gtf_pitch;
			layout.color_depth = color_depth;
			layout.dds_depth = dds_color_depth;
			layout.dds_expand = (dds_color_depth != 0);

			if(is_dxt){
				// dxtn
				layout.dds_size = ((w + 3) / 4) * ((h + 3) / 4) * color_depth;
			}else if(is_comp){
				// B8R8_G8R8, R8B8_R8G8
				layout.dds_size = ((w + 1) / 2) * h * 4;
			}else{
				layout.dds_size = w * h * color_depth;
			}

			// swizzle gtf size
			layout.gtf_swizzle_size = layout.dds_size;

			if(dds_color_depth != 0){
				layout.dds_pitch = w * dds_color_depth;
				layout.dds_size = layout.dds_pitch * h;
			}

			// linear gtf size
			if(is_dxt){
				// not power of 2 dxtn
				layout.gtf_linear_size = ((h + 3) / 4) * gtf_pitch;
			}else{
				layout.gtf_linear_size = h * gtf_pitch;
			}

			// volume
			if(is_volume){
				layout.dds_size *= v;
				layout.gtf_swizzle_size *= v;
				layout.gtf_linear_size *= v;
			}

			// offset
			layout.dds_offset = latest.dds_offset + latest.dds_size;
			layout.gtf_swizzle_offset = latest.gtf_swizzle_offset + latest.gtf_swizzle_size;
			if(is_cube && new_face){
				// when swizzle cubemap, each face must be aligned on a 128-byte boundary
				layout.gtf_swizzle_offset = utilGetAlign(layout.gtf_swizzle_offset, 128);
				new_face = false;
			}
			layout.gtf_linear_offset = latest.gtf_linear_offset + latest.gtf_linear_size;

			// update layout
			*ptr = layout;
			++ptr;
			latest = layout;


			PRINTF("    ");
			if(is_cube){
				PRINTF("face[%d] ", n);
			}
			if(is_volume){
				PRINTF("%dx%dx%d: %d * %d = %d\n", w, h, v, layout.dds_size / v, v, layout.dds_size);
			}else{
				PRINTF("%dx%d: %d\n", w, h, layout.dds_size);
			}

			// next miplevel
			if(!is_mip)	break;

			w >>= 1;
			h >>= 1;
			v >>= 1;
			if(w == 0 && h == 0 && v == 0) break;
			if(w == 0) w = 1;
			if(h == 0) h = 1;
			if(v == 0) v = 1;
			++m;
		}
	}

	return true;
}

bool convertBufferByLayout(uint8_t *gtf_image, uint8_t *dds_image, layout_t *playout, uint32_t layout_num, CellGcmTexture tex, bool bDds2Gtf)
{
	bool is_swizzle = gtfIsSwizzle(tex.format);

	uint8_t raw_format = gtfGetRawFormat(tex.format);
	bool is_dxt = gtfIsDxtn(raw_format);

	PRINTF("  [Convert Info]\n");
	for(uint32_t i = 0; i < layout_num; ++i, ++playout){
		layout_t layout = *playout;

		PRINTF("    %dx%dx%d\n", layout.width, layout.height, layout.depth);

		if(is_dxt){
			// dxtn format

			// get ptr
			uint8_t *ddsptr = reinterpret_cast<uint8_t*>(dds_image + layout.dds_offset);
			uint8_t *gtfptr = reinterpret_cast<uint8_t*>(gtf_image + layout.gtf_linear_offset);
			if(is_swizzle){
				gtfptr = reinterpret_cast<uint8_t*>(gtf_image + layout.gtf_swizzle_offset);
			}

			uint32_t block_size = 16;
			if(raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT1){
				block_size = 8;
			}

			uint32_t block_width = ((layout.width + 3) / 4);
			uint32_t block_height = ((layout.height + 3) / 4);
			uint32_t block_depth = ((layout.depth + 3) / 4);
			uint32_t block_pitch = block_width * block_size;

			uint32_t image_size = block_width * block_height * block_size;

			if(is_swizzle) {
				// powor of 2 dxtn
				if(tex.dimension == CELL_GCM_TEXTURE_DIMENSION_3){
					// VTC
					for(uint32_t z = 0; z < block_depth; ++z){
						for(uint32_t y = 0; y < block_height; ++y){
							for(uint32_t x = 0; x < block_width; ++x)
							{
								uint32_t depth_block_num = layout.depth % 4;
								if(depth_block_num == 0) depth_block_num = 4;

								for(uint32_t d_scan = 0; d_scan < depth_block_num; ++d_scan){
									uint8_t *ddsptr2 = ddsptr + image_size * (z * 4 + d_scan);
									ddsptr2 += block_size * (x + y * block_width);

									convertMoveMemory(gtfptr, ddsptr2, block_size, bDds2Gtf);
									gtfptr += block_size;
								}
							}
						}
					}
				}else{
					// not VTC & powor of 2
					convertMoveMemory(gtfptr, ddsptr, image_size, bDds2Gtf);
				}
			}else{
				// not powor of 2 dxtn
				uint32_t dxt_pitch = gtfGetPitch(raw_format, tex.width);
				for(int32_t d = 0; d < layout.depth; ++d){
					for(uint32_t block_line = 0; block_line < block_height; ++block_line){
						convertMoveMemory(gtfptr + dxt_pitch * block_height * d + dxt_pitch * block_line, ddsptr + image_size * d + block_pitch * block_line, block_pitch, bDds2Gtf);
					}
				}
			}		
		}else{
			// not dxtn format

			uint32_t invert_flag = getInvertFlag(tex);

			if(is_swizzle){
				// 64 bit and 128 bit fat texel swizzled memory layout can be described as "not quite swizzled."
				if(raw_format == CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT){
					// A swizzled 128 bit texture is treated as a 32-bit texture that happens to be four times as wide.
					layout.width = layout.width * 4;
					layout.color_depth = 4;
				}else if(raw_format == CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT){
					// A swizzled 64 bit texture is treated as a 32-bit texture that happens to be twice as wide.
					layout.width = layout.width * 2;
					layout.color_depth = 4;
				}
			}
			
			if(raw_format == CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW ||
				raw_format == CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW)
			{
				layout.width = ((layout.width + 1) / 2) * 2;
			}

			if(!layout.dds_expand){
				layout.dds_depth = layout.color_depth;
				layout.dds_pitch = layout.width * layout.dds_depth;
			}

			for(int32_t d = 0; d < layout.depth; ++d){
				for(uint32_t line = 0; line < layout.height; ++line){
					
					for(uint32_t x = 0; x < layout.width; ++x){

						// get ptr
						uint8_t *ddsptr = dds_image + layout.dds_offset + d * layout.dds_pitch * layout.height + line * layout.dds_pitch + x * layout.dds_depth;
						uint8_t *gtfptr = gtf_image + layout.gtf_linear_offset + d * layout.height * layout.pitch + line * layout.pitch + x * layout.color_depth;
						if(is_swizzle) {
							gtfptr = gtf_image + layout.gtf_swizzle_offset + utilToSwizzle(x, line, d, log2d(layout.width), log2d(layout.height), log2d(layout.depth)) * layout.color_depth;
						}

						if(bDds2Gtf && layout.dds_expand){
							// only dds2gtf
							if(layout.dds_depth == 2){
								// FOURCC_R16F -> Y16_X16_FLOAT

								// copy to Y16 and invert endian16
								gtfptr[0] = ddsptr[1];
								gtfptr[1] = ddsptr[0];

								// copy to X16 and invert endian16
								gtfptr[2] = ddsptr[1];
								gtfptr[3] = ddsptr[0];
							}else if(layout.dds_depth == 3){
								// 24bit RGB -> 32bit ARGB

								// copy and invert endian & padding A value
								gtfptr[0] = 0xFF;      // A
								gtfptr[1] = ddsptr[2]; // R
								gtfptr[2] = ddsptr[1]; // G
								gtfptr[3] = ddsptr[0]; // B
							}
						}else if(invert_flag == CELL_GTFCONV_ENDIAN_INVERT16){
							// 16bit
							convertMoveMemoryWithInvertEndian16(gtfptr, ddsptr, layout.color_depth, bDds2Gtf);
						}else if(invert_flag == CELL_GTFCONV_ENDIAN_INVERT32_EVEN){
							// B8R8_G8R8, R8B8_R8G8
							if((x & 0x01) == 0){
								// even pixel
								convertMoveMemoryWithInvertEndian32(gtfptr, ddsptr, 4, bDds2Gtf);						
							}
						}else if(invert_flag == CELL_GTFCONV_ENDIAN_INVERT32){
							// 32bit
							convertMoveMemoryWithInvertEndian32(gtfptr, ddsptr, layout.color_depth, bDds2Gtf);
						}
					}
				}
			}
		}
	}

	return true;
}

} // namespace gtfconv
