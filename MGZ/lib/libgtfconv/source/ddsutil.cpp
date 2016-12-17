#include "utils.h"

namespace gtfconv{

bool ddsCheckSpec(CellUtilDDSHeader ddsh)
{
	if(ddsh.magic != FOURCC_DDS) return false;
	
	PRINTF("  [DDS Spec]\n");
	if(ddsh.caps2 & DDSCAPS2_VOLUME){
		PRINTF("    Size: %dx%dx%d\n", ddsh.width, ddsh.height, ddsh.depth);
	}else{
		PRINTF("    Size: %dx%d\n", ddsh.width, ddsh.height);
	}
	{
		uint32_t mipmap = 0;
		if(ddsh.flags & DDSD_MIPMAPCOUNT){
			mipmap = ddsh.mipMapCount;
		}

		uint32_t cube = 0;
		if(ddsh.caps2 & DDSCAPS2_CUBEMAP){
			if(ddsh.caps2 & DDSCAPS2_CUBEMAP_POSITIVEX) ++cube;
			if(ddsh.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEX) ++cube;
			if(ddsh.caps2 & DDSCAPS2_CUBEMAP_POSITIVEY) ++cube;
			if(ddsh.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEY) ++cube;
			if(ddsh.caps2 & DDSCAPS2_CUBEMAP_POSITIVEZ) ++cube;
			if(ddsh.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEZ) ++cube;
		}

		if(ddsh.flags & DDSD_LINEARSIZE){
			PRINTF("    Info: mipmap=%d, cube=%d, linear_size=%d\n", mipmap, cube, ddsh.pitchOrLinearSize);
		}else{
			PRINTF("    Info: mipmap=%d, cube=%d, pitch=%d\n", mipmap, cube, ddsh.pitchOrLinearSize);			
		}
	}

	PRINTF("    Flags: ");
	if(ddsh.flags & DDSD_CAPS)	PRINTF("DDSD_CAPS, ");
	if(ddsh.flags & DDSD_PIXELFORMAT)	PRINTF("DDSD_PIXELFORMAT, ");
	if(ddsh.flags & DDSD_WIDTH)	PRINTF("DDSD_WIDTH, ");
	if(ddsh.flags & DDSD_HEIGHT)	PRINTF("DDSD_HEIGHT, ");
	if(ddsh.flags & DDSD_PITCH)	PRINTF("DDSD_PITCH, ");
	if(ddsh.flags & DDSD_MIPMAPCOUNT)	PRINTF("DDSD_MIPMAPCOUNT, ");
	if(ddsh.flags & DDSD_LINEARSIZE)	PRINTF("DDSD_LINEARSIZE, ");
	if(ddsh.flags & DDSD_DEPTH)	PRINTF("DDSD_DEPTH, ");

	PRINTF("\n    Caps1: ");
	if(ddsh.caps1 & DDSCAPS_ALPHA)	PRINTF("DDSCAPS_ALPHA, ");
	if(ddsh.caps1 & DDSCAPS_COMPLEX)	PRINTF("DDSCAPS_COMPLEX, ");
	if(ddsh.caps1 & DDSCAPS_TEXTURE)	PRINTF("DDSCAPS_TEXTURE, ");
	if(ddsh.caps1 & DDSCAPS_MIPMAP)	PRINTF("DDSCAPS_MIPMAP, ");

	PRINTF("\n    Caps2: ");
	if(ddsh.caps2 & DDSCAPS2_VOLUME)	PRINTF("DDSCAPS2_VOLUME, ");
	if(ddsh.caps2 & DDSCAPS2_CUBEMAP)	PRINTF("DDSCAPS2_CUBEMAP, ");

	PRINTF("\n    PixelFlag: ");
	if(ddsh.ddspf.flags & DDPF_ALPHAPIXELS)	PRINTF("DDPF_ALPHAPIXELS, ");
	if(ddsh.ddspf.flags & DDPF_ALPHA)	PRINTF("DDPF_ALPHA, ");
	if(ddsh.ddspf.flags & DDPF_FOURCC)	PRINTF("DDPF_FOURCC, ");
	if(ddsh.ddspf.flags & DDPF_RGB)	PRINTF("DDPF_RGB, ");
	if(ddsh.ddspf.flags & DDPF_PALETTEINDEXED1)	PRINTF("DDPF_PALETTEINDEXED1, ");
	if(ddsh.ddspf.flags & DDPF_PALETTEINDEXED2)	PRINTF("DDPF_PALETTEINDEXED2, ");
	if(ddsh.ddspf.flags & DDPF_PALETTEINDEXED4)	PRINTF("DDPF_PALETTEINDEXED4, ");
	if(ddsh.ddspf.flags & DDPF_PALETTEINDEXED8)	PRINTF("DDPF_PALETTEINDEXED8, ");
	if(ddsh.ddspf.flags & DDPF_LUMINANCE)	PRINTF("DDPF_LUMINANCE, ");
	if(ddsh.ddspf.flags & DDPF_ALPHAPREMULT)	PRINTF("DDPF_ALPHAPREMULT, ");
	if(ddsh.ddspf.flags & DDPF_NORMAL)	PRINTF("DDPF_NORMAL(NV Custom flag), ");

	if(ddsh.ddspf.flags & DDPF_FOURCC){
		PRINTF("\n    FOURCC: ");
		if(ddsh.ddspf.fourCC == FOURCC_DDS) PRINTF("FOURCC_DDS, ");
		if(ddsh.ddspf.fourCC == FOURCC_DXT1) PRINTF("FOURCC_DXT1, ");
		if(ddsh.ddspf.fourCC == FOURCC_DXT2) PRINTF("FOURCC_DXT2, ");
		if(ddsh.ddspf.fourCC == FOURCC_DXT3) PRINTF("FOURCC_DXT3, ");
		if(ddsh.ddspf.fourCC == FOURCC_DXT4) PRINTF("FOURCC_DXT4, ");
		if(ddsh.ddspf.fourCC == FOURCC_DXT5) PRINTF("FOURCC_DXT5, ");
		if(ddsh.ddspf.fourCC == FOURCC_RXGB) PRINTF("FOURCC_RXGB, ");
		if(ddsh.ddspf.fourCC == FOURCC_ATI1) PRINTF("FOURCC_ATI1, ");
		if(ddsh.ddspf.fourCC == FOURCC_ATI2) PRINTF("FOURCC_ATI2, ");

		if(ddsh.ddspf.fourCC == FOURCC_R16F) PRINTF("FOURCC_R16F, ");
		if(ddsh.ddspf.fourCC == FOURCC_G16R16F) PRINTF("FOURCC_G16R16F, ");
		if(ddsh.ddspf.fourCC == FOURCC_A16B16G16R16F) PRINTF("FOURCC_A16B16G16R16F, ");
		if(ddsh.ddspf.fourCC == FOURCC_R32F) PRINTF("FOURCC_R32F, ");
		if(ddsh.ddspf.fourCC == FOURCC_A32B32G32R32F) PRINTF("FOURCC_A32B32G32R32F, ");

		if(ddsh.ddspf.fourCC == FOURCC_YVYU) PRINTF("FOURCC_YVYU, ");
		if(ddsh.ddspf.fourCC == FOURCC_YUY2) PRINTF("FOURCC_YUY2, ");
		if(ddsh.ddspf.fourCC == FOURCC_R8G8_B8G8) PRINTF("FOURCC_R8G8_B8G8, ");
		if(ddsh.ddspf.fourCC == FOURCC_G8R8_G8B8) PRINTF("FOURCC_G8R8_G8B8, ");
	}

	PRINTF("\n    BitCount: %d\n", ddsh.ddspf.rgbBitCount);
	PRINTF("    Mask: A[%08x] R[%08x] G[%08x] B[%08x] \n", ddsh.ddspf.abitMask, ddsh.ddspf.rbitMask, ddsh.ddspf.gbitMask, ddsh.ddspf.bbitMask);	

	return true;
}

} // namespace gtfconv
