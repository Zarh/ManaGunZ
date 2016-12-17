#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "convert.h"
#include "gtfconv.h"

using namespace gtfconv;

namespace gtfconv{

#ifdef NDEBUG
// for release
const uint8_t HEADER_PAD_CHAR = 0;
const uint8_t IMAGE_PAD_CHAR = 0;
#else
// for debug
const uint8_t HEADER_PAD_CHAR = 'P';
const uint8_t IMAGE_PAD_CHAR = 0xEE;
#endif

const unsigned int REMAP_FLAG = (CELL_GCM_TEXTURE_REMAP_REMAP << 14 | CELL_GCM_TEXTURE_REMAP_REMAP << 12 | CELL_GCM_TEXTURE_REMAP_REMAP << 10 | CELL_GCM_TEXTURE_REMAP_REMAP << 8);
#define REMAP_MASK(x, y, z, w) ((w) << 14 | (z) << 12 | (y) << 10 | (x) << 8)
#define REMAP_FROM(x, y, z, w) ((w) << 6 | (z) << 4 | (y) << 2 | (x))

const unsigned int _A = CELL_GCM_TEXTURE_REMAP_FROM_A;
const unsigned int _R = CELL_GCM_TEXTURE_REMAP_FROM_R;
const unsigned int _G = CELL_GCM_TEXTURE_REMAP_FROM_G;
const unsigned int _B = CELL_GCM_TEXTURE_REMAP_FROM_B;
const unsigned int _E = CELL_GCM_TEXTURE_REMAP_REMAP;
const unsigned int _1 = CELL_GCM_TEXTURE_REMAP_ONE;
const unsigned int _0 = CELL_GCM_TEXTURE_REMAP_ZERO;

#define GCM_REMAP_ARGB (REMAP_MASK(_E, _E, _E, _E) | REMAP_FROM(_A, _R, _G, _B))
#define GCM_REMAP_BGRA (REMAP_MASK(_E, _E, _E, _E) | REMAP_FROM(_B, _G, _R, _A))
#define GCM_REMAP_ABGR (REMAP_MASK(_E, _E, _E, _E) | REMAP_FROM(_A, _B, _G, _R))
#define GCM_REMAP_AGRB (REMAP_MASK(_E, _E, _E, _E) | REMAP_FROM(_A, _G, _R, _B))
#define GCM_REMAP_ARBG (REMAP_MASK(_E, _E, _E, _E) | REMAP_FROM(_A, _R, _B, _G))
#define GCM_REMAP_1RGB (REMAP_MASK(_1, _E, _E, _E) | REMAP_FROM(_A, _R, _G, _B))
#define GCM_REMAP_1BBB (REMAP_MASK(_1, _E, _E, _E) | REMAP_FROM(_B, _B, _B, _B))
#define GCM_REMAP_B000 (REMAP_MASK(_E, _0, _0, _0) | REMAP_FROM(_B, _B, _B, _B))
#define GCM_REMAP_ARGB_WITH_ORDER_XYXY (GCM_REMAP_ARGB | (CELL_GCM_TEXTURE_REMAP_ORDER_XYXY << (16)))

int countBit( uint32_t bits )
{
	int ret = 0;
	int i;

	for( i=0; i<32; i++ ) {
		if( (bits>>i) & 0x1 ) ret++;
	}
	return ret;
}

static uint32_t getRemapFromBitMask( CellUtilDDSPixelFormat* pf ) 
{
	uint32_t remap = 0;

	// order
	uint32_t mask[4];
	char c[4] = {'\0'};
	int order[4] = {0};

	//struct rgba_set rgba[4];

	mask[0] = pf->abitMask; c[0] = 'a';
	mask[1] = pf->rbitMask; c[1] = 'r';
	mask[2] = pf->gbitMask; c[2] = 'g';
	mask[3] = pf->bbitMask; c[3] = 'b';

	// find biggest bitmask among rgba bit flag.
	// The color of the biggest one is the one on the most left side in bit order.
	//

	if( ! (pf->flags & 0x01)) {	
		// no alpha is contained. So need to figure out pixel format by looking at 
		// bit mask.
		// We have two cases here, 16 bit texels and 32 bit texels. 
		// And usually alpha bits are put at most-left or most-right side.
		//
		// TODO: handle alpha bits located at unusual bit location.
		//
		// if other rgb color bits covers LSB, then we assume 
		// alpha bits to use them. 
		if( (pf->rbitMask & 1) |
			(pf->gbitMask & 1) |
			(pf->bbitMask & 1) )
		{
			//mask[0] = 1 << (pf->rgbBitCount-1);
			mask[0] = 1U << 31;
		}
		else {
			mask[0] = 0;
		}
	}

	// NOTE: only need the order of rgba element. 
	//       no sorting required.
	//
	for( int i=0; i<4; i++ ) { // each rgba
		for( int j=0; j<4; j++ ) {
			if( i != j ) {
				if( mask[i] < mask[j] )
					order[i] += 1;
			}
		}
	}

	#ifdef DEBUG // {
	printf( "==========================>>\n" );
	for( int i=0; i<4; i++ ) {
		printf( "Color '%c' (mask=0x%08X): %d\n", c[i], mask[i], order[i] );
	}
	printf( "<<==========================\n" );
	#endif  // } DEBUG

	remap |= 
		CELL_GCM_TEXTURE_REMAP_REMAP << (6 + 8) |   // remap
		CELL_GCM_TEXTURE_REMAP_REMAP << (4 + 8) | 
		CELL_GCM_TEXTURE_REMAP_REMAP << (2 + 8) | 
		CELL_GCM_TEXTURE_REMAP_REMAP << (0 + 8);

	for( int i=0; i<4; i++ ) {
		switch(order[i]) {
		case 0:
			remap |= (CELL_GCM_TEXTURE_REMAP_FROM_A << (i*2));

			// if 'no alpha' flag is on, we set REMAP_ONE to remap.
			if( ! (pf->flags & 0x01)) {	

				// zero clear on alpha bits field
				remap &= ~(0x3 << (i*2+8));

				// put REMAP_ONE to alpha bits field
				remap |= (CELL_GCM_TEXTURE_REMAP_ONE << (i*2+8));
			}
			break;
		case 1:
			remap |= (CELL_GCM_TEXTURE_REMAP_FROM_R << (i*2));
			break;
		case 2:
			remap |= (CELL_GCM_TEXTURE_REMAP_FROM_G << (i*2));
			break;
		case 3:
			remap |= (CELL_GCM_TEXTURE_REMAP_FROM_B << (i*2));
			break;
		default:
			//assert(0);
			break;
		}
	}

	#if 0 // {
	// overwrite temporary remap setting
	remap = 
		CELL_GCM_TEXTURE_REMAP_REMAP << (6 + 8) |   // remap
		CELL_GCM_TEXTURE_REMAP_REMAP << (4 + 8) | 
		CELL_GCM_TEXTURE_REMAP_REMAP << (2 + 8) | 
		CELL_GCM_TEXTURE_REMAP_ZERO << (0 + 8) |
		CELL_GCM_TEXTURE_REMAP_FROM_R << 6 | 
		CELL_GCM_TEXTURE_REMAP_FROM_G << 4 | 
		CELL_GCM_TEXTURE_REMAP_FROM_B << 2 | 
		CELL_GCM_TEXTURE_REMAP_FROM_A; 

	#endif // }
	
	return remap;
}

bool dds2gtfConvFormat(CellUtilDDSHeader ddsh, uint8_t *pformat, uint32_t *premap)
{
	uint8_t format = 0;
	uint32_t remap = GCM_REMAP_ARGB;

	uint8_t a_bits = utilCountBit(ddsh.ddspf.abitMask);
	uint8_t r_bits = utilCountBit(ddsh.ddspf.rbitMask);
	uint8_t g_bits = utilCountBit(ddsh.ddspf.gbitMask);
	uint8_t b_bits = utilCountBit(ddsh.ddspf.bbitMask);

	// ignore Custom nv flag
	ddsh.ddspf.flags &= 0x7FFFFFFFF;

	switch(ddsh.ddspf.flags)
	{
	case DDPF_FOURCC:
	case DDPF_FOURCC | DDPF_NORMAL:
		{
			if(ddsh.ddspf.fourCC == FOURCC_DXT1) format = CELL_GCM_TEXTURE_COMPRESSED_DXT1;
			if(ddsh.ddspf.fourCC == FOURCC_DXT2) format = CELL_GCM_TEXTURE_COMPRESSED_DXT23;
			if(ddsh.ddspf.fourCC == FOURCC_DXT3) format = CELL_GCM_TEXTURE_COMPRESSED_DXT23;
			if(ddsh.ddspf.fourCC == FOURCC_DXT4) format = CELL_GCM_TEXTURE_COMPRESSED_DXT45;
			if(ddsh.ddspf.fourCC == FOURCC_DXT5) format = CELL_GCM_TEXTURE_COMPRESSED_DXT45;

			if(ddsh.ddspf.fourCC == FOURCC_R16F)			format = CELL_GCM_TEXTURE_Y16_X16_FLOAT;
			if(ddsh.ddspf.fourCC == FOURCC_G16R16F)			format = CELL_GCM_TEXTURE_Y16_X16_FLOAT;
			if(ddsh.ddspf.fourCC == FOURCC_A16B16G16R16F)	format = CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT;
			if(ddsh.ddspf.fourCC == FOURCC_R32F)			format = CELL_GCM_TEXTURE_X32_FLOAT;
			if(ddsh.ddspf.fourCC == FOURCC_A32B32G32R32F)	format = CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT;

			if(ddsh.ddspf.fourCC == FOURCC_R8G8_B8G8)	format = CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8, remap = GCM_REMAP_AGRB;
			if(ddsh.ddspf.fourCC == FOURCC_G8R8_G8B8)	format = CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8, remap = GCM_REMAP_AGRB;
			if(ddsh.ddspf.fourCC == FOURCC_YVYU)		format = CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8, remap = GCM_REMAP_ARBG;
			if(ddsh.ddspf.fourCC == FOURCC_YUY2)		format = CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8, remap = GCM_REMAP_ARBG;

			// unsupported
			if(ddsh.ddspf.fourCC == FOURCC_DDS)	 format = 0;
			if(ddsh.ddspf.fourCC == FOURCC_RXGB) format = 0;
			if(ddsh.ddspf.fourCC == FOURCC_ATI1) format = 0;
			if(ddsh.ddspf.fourCC == FOURCC_ATI2) format = 0;
		}
		break;

	case DDPF_RGB:							// dwRGBBitCount, RGBBitMask are defined
	case DDPF_RGB | DDPF_ALPHAPIXELS:		// alpha is also defined
	case DDPF_ALPHA:						// Only Alpha (1 component)
	case DDPF_LUMINANCE:					// expand 1 ch data to RGB      
	case DDPF_LUMINANCE | DDPF_ALPHAPIXELS:	// contains alpha        
	case 0x00040000:						// r6g5b5
	case DDSF_BUMPDUDV:						// X16Y16 bumpmap
		{
			// in case of any of color bits is more than 8 bits long.
			if( a_bits == 16 || r_bits == 16 || g_bits == 16 || b_bits == 16 ) 
			{
				// TODO: Remap order.... Allow user to pick XXXY and XYXY?
				remap = GCM_REMAP_ARGB_WITH_ORDER_XYXY;
			}
			else if( ddsh.ddspf.rgbBitCount == 8 )
			{
				format = CELL_GCM_TEXTURE_B8;

				if(ddsh.ddspf.rbitMask)
				{
					// L8 format 
					remap = GCM_REMAP_1BBB;
				}
				else
				{
					// A8 format
					remap = GCM_REMAP_B000;
				}

			}
			// if rgb bits are not null (defined)
			else if ( ddsh.ddspf.rbitMask | ddsh.ddspf.gbitMask | ddsh.ddspf.bbitMask | ddsh.ddspf.abitMask ) {
				remap = getRemapFromBitMask( &ddsh.ddspf );
			}
			else {
				remap = GCM_REMAP_BGRA; // raw bitmap
			}
		}
		break;
	default:
#if 0
		printf( "ERROR: Pixel format not supported: dwPfFlags\n" );
		printf( "	ddsh.ddspf.size:        %d\n", ddsh.ddspf.size );
		printf( "	ddsh.ddspf.flags:       0x%x\n", ddsh.ddspf.flags );
		printf( "	ddsh.ddspf.fourCC:      0x%x ('%c%c%c%c')\n", ddsh.ddspf.fourCC,
					  (ddsh.ddspf.fourCC >> 24) & 0xFF, 
					  (ddsh.ddspf.fourCC >> 16) & 0xFF, 
					  (ddsh.ddspf.fourCC >>  8) & 0xFF, 
					  (ddsh.ddspf.fourCC >>  0) & 0xFF );
		printf( "	ddsh.ddspf.rgbBitCount: %d\n", ddsh.ddspf.rgbBitCount );
		printf( "	ddsh.ddspf.rbitMask:    0x%08x\n", ddsh.ddspf.rbitMask );
		printf( "	ddsh.ddspf.gbitMask:    0x%08x\n", ddsh.ddspf.gbitMask );
		printf( "	ddsh.ddspf.bbitMask:    0x%08x\n", ddsh.ddspf.bbitMask );
		printf( "	ddsh.ddspf.abitMask:    0x%08x\n", ddsh.ddspf.abitMask );
#endif
		return false;
	}

	// format conv
	if(ddsh.ddspf.flags & DDPF_RGB){
		if(ddsh.ddspf.rgbBitCount == 8){
			// 8bit
			format = CELL_GCM_TEXTURE_B8;

		}else if(ddsh.ddspf.rgbBitCount == 16){
			// 16bit
			if(a_bits == 0){
				if(r_bits == 5 && g_bits == 6 && b_bits == 5){
					format = CELL_GCM_TEXTURE_R5G6B5;
					remap = GCM_REMAP_1RGB;
				}else if(r_bits == 6 && g_bits == 5 && b_bits == 5){
					format = CELL_GCM_TEXTURE_R6G5B5;
					remap = GCM_REMAP_1RGB;
				}else if(r_bits == 5 && g_bits == 5 && b_bits == 5){
						format = CELL_GCM_TEXTURE_D1R5G5B5;
						remap = GCM_REMAP_1RGB;
				}else if(r_bits == 4 && g_bits == 4 && b_bits == 4){
						format = CELL_GCM_TEXTURE_A4R4G4B4;
						remap = GCM_REMAP_1RGB;
				}
			}else if(a_bits == 1){
				if(ddsh.ddspf.abitMask == 0x00008000){
					format = CELL_GCM_TEXTURE_A1R5G5B5;
				}else if(ddsh.ddspf.abitMask == 0x00000001){
					format = CELL_GCM_TEXTURE_R5G5B5A1;
				}
			}else if(a_bits == 4){
				format = CELL_GCM_TEXTURE_A4R4G4B4;
			}else if((a_bits == 8 && r_bits == 8) || (g_bits == 8 && b_bits == 8)){
				format = CELL_GCM_TEXTURE_G8B8;
			}else if(a_bits == 16 || r_bits == 16 || g_bits == 16 || b_bits == 16){
				format = CELL_GCM_TEXTURE_X16;
			}
		}else if(ddsh.ddspf.rgbBitCount == 24){
			// 24bit
			format = CELL_GCM_TEXTURE_D8R8G8B8;
			remap = GCM_REMAP_1RGB;
		}else if(ddsh.ddspf.rgbBitCount == 32){
			// 32bit
			if(r_bits == 8){
				if(ddsh.ddspf.flags & DDPF_ALPHAPIXELS){
					format = CELL_GCM_TEXTURE_A8R8G8B8;
				}else{
					format = CELL_GCM_TEXTURE_D8R8G8B8;
					remap = GCM_REMAP_1RGB;
				}
			}else if((a_bits == 16 && r_bits == 16) || (g_bits == 16 && b_bits == 16) ||
				(a_bits == 16 && g_bits == 16) || (a_bits == 16 && b_bits == 16) || 
				(r_bits == 16 && g_bits == 16) || (r_bits == 16 && b_bits == 16)){
				format = CELL_GCM_TEXTURE_Y16_X16;
			}
		}

	}else if(ddsh.ddspf.flags & DDSF_LUMINANCE){
		if(ddsh.ddspf.rgbBitCount == 16){
			if(r_bits == 16){
				format = CELL_GCM_TEXTURE_X16;
			}else if((a_bits == 8 && r_bits == 8) || (g_bits == 8 && b_bits == 8)){
				format = CELL_GCM_TEXTURE_G8B8;
			}
		}
	}else if(ddsh.ddspf.flags & DDSF_BUMPDUDV){
		if(ddsh.ddspf.rgbBitCount == 16){
			format = CELL_GCM_TEXTURE_Y16_X16;
		}else if(ddsh.ddspf.rgbBitCount == 32){
			format = CELL_GCM_TEXTURE_A8R8G8B8;
		}
	}

	if(format == 0){
		if(ddsh.ddspf.rgbBitCount == 8){
			format = CELL_GCM_TEXTURE_B8;
		}else if(ddsh.ddspf.rgbBitCount == 16){
			format = CELL_GCM_TEXTURE_X16;
		}else if(ddsh.ddspf.rgbBitCount == 32){
			format = CELL_GCM_TEXTURE_A8R8G8B8;
		}else if(ddsh.ddspf.rgbBitCount == 64){
			format = CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT;
		}else if(ddsh.ddspf.rgbBitCount == 128){
			format = CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT;
		}else{
			return false;
		}
	}

	if(pformat){
		*pformat = format;
	}

	if(premap){
		*premap = remap;
	}

	return true;
}

bool dds2gtfConvHeader(CellGcmTexture *texture, CellUtilDDSHeader ddsh, bool bSwizzle, bool bUnNorm)
{
	if(ddsh.magic != FOURCC_DDS) return false;
	if(ddsh.size != 124) return false;
	if(!(ddsh.flags & DDSD_CAPS)) return false;
	if(!(ddsh.flags & DDSD_PIXELFORMAT)) return false;
	if(!(ddsh.flags & DDSD_WIDTH)) return false;
	if(!(ddsh.flags & DDSD_HEIGHT)) return false;
	if((ddsh.flags & DDSD_PITCH) && (ddsh.flags & DDSD_LINEARSIZE)) return false;
	if(!(ddsh.caps1 & DDSCAPS_TEXTURE)) return false;

	/*
	if(ddsh.caps1 & DDSCAPS_MIPMAP){
		if(!(ddsh.caps1 & DDSCAPS_COMPLEX)) return false;
	}
	if(ddsh.caps1 & DDSCAPS2_VOLUME){
		if(!(ddsh.caps1 & DDSCAPS_COMPLEX)) return false;
	}
	if(ddsh.caps1 & DDSCAPS2_CUBEMAP){
		if(!(ddsh.caps1 & DDSCAPS_COMPLEX)) return false;
	}
	*/

	if(ddsh.ddspf.size != 32) return false;


	CellGcmTexture tex;
	dds2gtfConvFormat(ddsh, &tex.format, &tex.remap);
	tex.width = static_cast<uint16_t>(ddsh.width);
	tex.height = static_cast<uint16_t>(ddsh.height);
	tex.mipmap = 1;
	tex.depth = 1;
	tex.dimension = CELL_GCM_TEXTURE_DIMENSION_2;
	tex.cubemap = CELL_GCM_FALSE;
	tex.pitch = 0;
	tex.location = 0;
	tex.offset = 0;
	tex._padding = 0;

	if(ddsh.caps2 & DDSCAPS2_VOLUME){
		if(ddsh.flags & DDSD_DEPTH){
			tex.depth = static_cast<uint16_t>(ddsh.depth);
			tex.dimension = CELL_GCM_TEXTURE_DIMENSION_3;
		}
	}

	if(ddsh.flags & DDSD_MIPMAPCOUNT){
		uint8_t mipmap = utilGetMipmapSize(tex.width, tex.height, tex.depth);
		
		if(mipmap < ddsh.mipMapCount){
			return false;
		}

		tex.mipmap = static_cast<uint8_t>(ddsh.mipMapCount);
	}

	if(ddsh.caps2 & DDSCAPS2_CUBEMAP){
		uint8_t cube = 0;
		if(ddsh.caps2 & DDSCAPS2_CUBEMAP_POSITIVEX) ++cube;
		if(ddsh.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEX) ++cube;
		if(ddsh.caps2 & DDSCAPS2_CUBEMAP_POSITIVEY) ++cube;
		if(ddsh.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEY) ++cube;
		if(ddsh.caps2 & DDSCAPS2_CUBEMAP_POSITIVEZ) ++cube;
		if(ddsh.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEZ) ++cube;

		if(cube != 6){
			return false;
		}
		tex.cubemap = CELL_GCM_TRUE;
	}

	if(tex.dimension == CELL_GCM_TEXTURE_DIMENSION_3){
		if(tex.width > 512 || tex.height > 512 || tex.depth > 512){
			return false;
		}
	}else if(tex.dimension == CELL_GCM_TEXTURE_DIMENSION_2){
		if(tex.width > 4096 || tex.height > 4096){
			return false;
		}
	}

	// swizzle check
	uint8_t raw_format = gtfGetRawFormat(tex.format);
	bool is_dxt = gtfIsDxtn(raw_format);
	bool is_swizzle = gtfIsSwizzlable(tex);
	if(!is_dxt){
		is_swizzle = is_swizzle && bSwizzle;
	}

	if(is_swizzle){
		tex.format = static_cast<uint8_t>(tex.format & ~CELL_GCM_TEXTURE_LN);
		tex.pitch = 0;
	}else{
		tex.format = static_cast<uint8_t>(tex.format | CELL_GCM_TEXTURE_LN);
		tex.pitch = gtfGetPitch(tex.format, tex.width);
	}

	// normalize check
	if(bUnNorm){
		tex.format = static_cast<uint8_t>(tex.format | CELL_GCM_TEXTURE_UN);
	}

	*texture = tex;

	return true;
}

int32_t gtfconv_dds2gtf_image(GTF_CONV_T *gtfOutput, const GTF_BUFFER_T *ddsInput, uint32_t option)
{
	if(!ddsInput) return CELL_GTFCONV_ERROR;
	if(ddsInput->size < sizeof(CellUtilDDSHeader)) return CELL_GTFCONV_ERROR;

	bool bSwizzle = (option & CELL_GTFCONV_FLAG_SWIZZLIZE) == CELL_GTFCONV_FLAG_SWIZZLIZE;
	bool bUnNorm = (option & CELL_GTFCONV_FLAG_UNNORMALIZE) == CELL_GTFCONV_FLAG_UNNORMALIZE;

	CellUtilDDSHeader ddsh;
	memmove(&ddsh, ddsInput->addr, sizeof(CellUtilDDSHeader));

	if(ddsCheckSpec(ddsh) == false){
		return CELL_GTFCONV_ERROR;
	}

	PRINTF("    DDS Size: file=%d, image=%d\n", ddsInput->size, ddsInput->size - sizeof(CellUtilDDSHeader));

	uint8_t *in_image = ddsInput->addr + sizeof(CellUtilDDSHeader);
	
	CellGcmTexture texture;
	if(dds2gtfConvHeader(&texture, ddsh, bSwizzle, bUnNorm) == false){
		return CELL_GTFCONV_ERROR;
	}

	// gtf spec
	gtfCheckSpec(texture);

	// calc layout num
	uint8_t cube = 1;
	if(texture.cubemap == CELL_GCM_TRUE){
		cube = 6;
	}
	uint32_t layout_num = cube * texture.mipmap;

	layout_t *layout_array = new layout_t[layout_num];
	memset(layout_array, 0, sizeof(layout_t) * layout_num);

	convertLayOutBuffer(layout_array, texture, ddsh);

	uint32_t gtf_image_size = 0;
	bool is_swizzle = gtfIsSwizzle(texture.format);
	if(is_swizzle){
		gtf_image_size = layout_array[layout_num - 1].gtf_swizzle_offset + layout_array[layout_num - 1].gtf_swizzle_size;
	}else{
		gtf_image_size = layout_array[layout_num - 1].gtf_linear_offset + layout_array[layout_num - 1].gtf_linear_size;
	}

	uint32_t dds_image_size = layout_array[layout_num - 1].dds_offset + layout_array[layout_num - 1].dds_size;
	if(ddsInput->size - sizeof(CellUtilDDSHeader) < dds_image_size){
		if(layout_array) delete [] layout_array, layout_array = 0;
		return CELL_GTFCONV_ERROR;
	}

	if(!gtfOutput || gtfOutput->size < gtf_image_size)
	{
		if(layout_array) delete [] layout_array, layout_array = 0;
		return static_cast<int32_t>(gtf_image_size);
	}

	// init image
	memset(gtfOutput->addr, IMAGE_PAD_CHAR, gtf_image_size);
	
	// convert!!
	convertBufferByLayout(gtfOutput->addr, in_image, layout_array, layout_num, texture, true);
	if(layout_array) delete [] layout_array, layout_array = 0;

	gtfOutput->gcmt = texture;

	return CELL_GTFCONV_OK;
}

} // namespace gtfconv

int32_t gtfconv_dds2gtf(GTF_BUFFER_T *gtfOutput, const GTF_BUFFER_T *ddsInput, uint8_t inputCount, uint32_t option)
{
	const uint32_t GTF_TEXTURE_ALIGN = 128;
	bool bVerbose = (option & CELL_GTFCONV_FLAG_VERBOSE) == CELL_GTFCONV_FLAG_VERBOSE;
	bool bVerbPrep = (gtfOutput == 0) && bVerbose;
	bool bVerbPacked = (inputCount != 1) && bVerbose;

	if(bVerbPacked){
		bVerbPrep = false;
	}	

	uint32_t gtf_header_size = sizeof(CellGtfFileHeader) + sizeof(CellGtfTextureAttribute) * inputCount;
	gtf_header_size = utilGetAlign(gtf_header_size, GTF_TEXTURE_ALIGN);

	// init header
	uint8_t *gtf_header_buffer = new uint8_t[gtf_header_size];
	memset(gtf_header_buffer, HEADER_PAD_CHAR, gtf_header_size);

	CellGtfFileHeader *gtf_header = reinterpret_cast<CellGtfFileHeader*>(gtf_header_buffer);
	CellGtfTextureAttribute *gtf_attr = reinterpret_cast<CellGtfTextureAttribute*>(gtf_header_buffer + sizeof(CellGtfFileHeader));

	if(gtfOutput){
		memset(gtfOutput->addr, IMAGE_PAD_CHAR, gtfOutput->size);
	}

	for(uint8_t i = 0; i < inputCount; ++i)
	{
		SET_PRINTF_MODE(bVerbPrep);
		int32_t gtf_image_size = gtfconv_dds2gtf_image(0, &ddsInput[i], option);

		gtf_attr[i].id = i;
		if(i == 0){
            gtf_attr[i].offsetToTex = gtf_header_size;
		}else{
			gtf_attr[i].offsetToTex = gtf_attr[i - 1].offsetToTex + gtf_attr[i - 1].textureSize;
			gtf_attr[i].offsetToTex = utilGetAlign(gtf_attr[i].offsetToTex, GTF_TEXTURE_ALIGN);
		}
		if(gtf_image_size < 0){
			if(gtf_header_buffer){
				delete [] gtf_header_buffer, gtf_header_buffer = 0;
			}
			return CELL_GTFCONV_ERROR;
		}

		GTF_CONV_T gtf_conv;
		memset(&gtf_conv, 0, sizeof(GTF_CONV_T));
		
		gtf_conv.size = gtf_image_size;
		gtf_attr[i].textureSize = gtf_image_size;

		if(gtfOutput){
			gtf_conv.addr = gtfOutput->addr + gtf_attr[i].offsetToTex;

            gtfconv_dds2gtf_image(&gtf_conv, &ddsInput[i], option);

			gtf_attr[i].tex = gtf_conv.gcmt;


			SET_PRINTF_MODE(bVerbPacked);
			if(i == 0) PRINTF("  PackageInfo:\n");
			PRINTF("    [%02x] offset=%08x, size=%08x\n", i, gtf_attr[i].offsetToTex, gtf_image_size);
		}
	}

	uint32_t total_size = gtf_attr[inputCount - 1].offsetToTex + gtf_attr[inputCount - 1].textureSize;
	total_size = utilGetAlign(total_size, GTF_TEXTURE_ALIGN);

	if(!gtfOutput || gtfOutput->size < total_size)
	{
		if(gtf_header_buffer){
			delete [] gtf_header_buffer, gtf_header_buffer = 0;
		}
		return static_cast<int32_t>(total_size);
	}

	// file header
	{
		gtf_header->version = to_big_endian32(GTF_VERSION);
		gtf_header->size = to_big_endian32(total_size - gtf_header_size);
		gtf_header->numTexture = to_big_endian32(inputCount);

		for(uint8_t i = 0; i < inputCount; ++i){
			gtf_attr[i].id = to_big_endian32(gtf_attr[i].id);
			gtf_attr[i].offsetToTex = to_big_endian32(gtf_attr[i].offsetToTex);
			gtf_attr[i].textureSize = to_big_endian32(gtf_attr[i].textureSize);
			gtf_attr[i].tex.remap = to_big_endian32(gtf_attr[i].tex.remap);
			gtf_attr[i].tex.pitch = to_big_endian32(gtf_attr[i].tex.pitch);
			gtf_attr[i].tex.width = to_big_endian16(gtf_attr[i].tex.width);
			gtf_attr[i].tex.height = to_big_endian16(gtf_attr[i].tex.height);
			gtf_attr[i].tex.depth = to_big_endian16(gtf_attr[i].tex.depth);
		}

		// init header
		memset(gtfOutput->addr, HEADER_PAD_CHAR, gtf_header_size);
		memmove(gtfOutput->addr, gtf_header_buffer, gtf_header_size);
		if(gtf_header_buffer){
			delete [] gtf_header_buffer, gtf_header_buffer = 0;
		}
	}

	return CELL_GTFCONV_OK;
}

int32_t gtfconv_dds2gtf_get_size(const GTF_BUFFER_T *ddsInput, uint8_t inputCount, uint32_t option)
{
	return gtfconv_dds2gtf(0, ddsInput, inputCount, option);
}
