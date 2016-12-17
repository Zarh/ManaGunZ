#include "utils.h"

namespace gtfconv{

uint8_t gtfGetRawFormat(uint8_t texture_format)
{
	return texture_format & ~(CELL_GCM_TEXTURE_LN | CELL_GCM_TEXTURE_UN);
}

bool gtfIsSwizzle(uint8_t format)
{
	return !(format & CELL_GCM_TEXTURE_LN);
}

uint32_t gtfGetPitch(uint8_t format, uint32_t width)
{
	uint32_t depth = 0;
	uint32_t raw_format = gtfGetRawFormat(format);
	switch(raw_format){
		case CELL_GCM_TEXTURE_B8:
			depth = 1;
			break;
		case CELL_GCM_TEXTURE_A1R5G5B5:
		case CELL_GCM_TEXTURE_A4R4G4B4:
		case CELL_GCM_TEXTURE_R5G6B5:
		case CELL_GCM_TEXTURE_G8B8:
		case CELL_GCM_TEXTURE_R6G5B5:
		case CELL_GCM_TEXTURE_DEPTH16:
		case CELL_GCM_TEXTURE_DEPTH16_FLOAT:
		case CELL_GCM_TEXTURE_X16:
		case CELL_GCM_TEXTURE_D1R5G5B5:
		case CELL_GCM_TEXTURE_R5G5B5A1:
		case CELL_GCM_TEXTURE_COMPRESSED_HILO8:
		case CELL_GCM_TEXTURE_COMPRESSED_HILO_S8:
		case CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW:
		case CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW:
			depth = 2;
			break;
		case CELL_GCM_TEXTURE_A8R8G8B8:
		case CELL_GCM_TEXTURE_DEPTH24_D8:
		case CELL_GCM_TEXTURE_DEPTH24_D8_FLOAT:
		case CELL_GCM_TEXTURE_Y16_X16:
		case CELL_GCM_TEXTURE_X32_FLOAT:
		case CELL_GCM_TEXTURE_D8R8G8B8:
		case CELL_GCM_TEXTURE_Y16_X16_FLOAT:
			depth = 4;
			break;
		case CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT:
			depth = 8;
			break;
		case CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT:
			depth = 16;
			break;
		case CELL_GCM_TEXTURE_COMPRESSED_DXT1:
		case CELL_GCM_TEXTURE_COMPRESSED_DXT23:
		case CELL_GCM_TEXTURE_COMPRESSED_DXT45:
			depth = 0;
			break;
		default:
			depth = 4;
	}

	uint32_t pitch = width * depth;
	if(raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT1){
		pitch = ((width + 3) / 4) * 8;
	}else if(raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT23 || raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT45){
		pitch = ((width + 3) / 4) * 16;
	}else if(raw_format == CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW ||
		raw_format == CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW)
	{
		pitch = ((width + 1) / 2) * 4;
	}

	return pitch;
}

uint16_t gtfGetDepth(uint8_t format)
{
	uint16_t depth = 0;
	uint8_t raw_format = gtfGetRawFormat(format);
	switch(raw_format){
		case CELL_GCM_TEXTURE_B8:
			depth = 1;
			break;
		case CELL_GCM_TEXTURE_A1R5G5B5:
		case CELL_GCM_TEXTURE_A4R4G4B4:
		case CELL_GCM_TEXTURE_R5G6B5:
		case CELL_GCM_TEXTURE_G8B8:
		case CELL_GCM_TEXTURE_R6G5B5:
		case CELL_GCM_TEXTURE_DEPTH16:
		case CELL_GCM_TEXTURE_DEPTH16_FLOAT:
		case CELL_GCM_TEXTURE_X16:
		case CELL_GCM_TEXTURE_D1R5G5B5:
		case CELL_GCM_TEXTURE_R5G5B5A1:
		case CELL_GCM_TEXTURE_COMPRESSED_HILO8:
		case CELL_GCM_TEXTURE_COMPRESSED_HILO_S8:
		case CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW:
		case CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW:
			depth = 2;
			break;
		case CELL_GCM_TEXTURE_A8R8G8B8:
		case CELL_GCM_TEXTURE_DEPTH24_D8:
		case CELL_GCM_TEXTURE_DEPTH24_D8_FLOAT:
		case CELL_GCM_TEXTURE_Y16_X16:
		case CELL_GCM_TEXTURE_X32_FLOAT:
		case CELL_GCM_TEXTURE_D8R8G8B8:
		case CELL_GCM_TEXTURE_Y16_X16_FLOAT:
			depth = 4;
			break;
		case CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT:
			depth = 8;
			break;
		case CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT:
			depth = 16;
			break;
		case CELL_GCM_TEXTURE_COMPRESSED_DXT1:
			depth = 8;
			break;
		case CELL_GCM_TEXTURE_COMPRESSED_DXT23:
		case CELL_GCM_TEXTURE_COMPRESSED_DXT45:
			depth = 16;
			break;
		default:
			depth = 4;
	}

	return depth;
}

const char* gtfGetFormatName(uint8_t format)
{
	const struct {
		uint8_t format;
		const char* string;
	} sFormatString[] = {
		{ 0xFF, "Unknown Format" },
		{ 0x81, "CELL_GCM_TEXTURE_B8" }, 
		{ 0x82, "CELL_GCM_TEXTURE_A1R5G5B5" }, 
		{ 0x83, "CELL_GCM_TEXTURE_A4R4G4B4" }, 
		{ 0x84, "CELL_GCM_TEXTURE_R5G6B5" }, 
		{ 0x85, "CELL_GCM_TEXTURE_A8R8G8B8" }, 
		{ 0x86, "CELL_GCM_TEXTURE_COMPRESSED_DXT1" }, 
		{ 0x87, "CELL_GCM_TEXTURE_COMPRESSED_DXT23" }, 
		{ 0x88, "CELL_GCM_TEXTURE_COMPRESSED_DXT45" }, 
		{ 0x8B, "CELL_GCM_TEXTURE_G8B8" }, 
		{ 0x8D, "CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8" },
		{ 0x8E, "CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8" },
		{ 0x8F, "CELL_GCM_TEXTURE_R6G5B5" }, 
		{ 0x90, "CELL_GCM_TEXTURE_DEPTH24_D8" }, 
		{ 0x91, "CELL_GCM_TEXTURE_DEPTH24_D8_FLOAT" }, 
		{ 0x92, "CELL_GCM_TEXTURE_DEPTH16" }, 
		{ 0x93, "CELL_GCM_TEXTURE_DEPTH16_FLOAT" }, 
		{ 0x94, "CELL_GCM_TEXTURE_X16" }, 
		{ 0x95, "CELL_GCM_TEXTURE_Y16_X16" }, 
		{ 0x97, "CELL_GCM_TEXTURE_R5G5B5A1" }, 
		{ 0x98, "CELL_GCM_TEXTURE_COMPRESSED_HILO8" }, 
		{ 0x99, "CELL_GCM_TEXTURE_COMPRESSED_HILO_S8" }, 
		{ 0x9A, "CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT" }, 
		{ 0x9B, "CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT" }, 
		{ 0x9C, "CELL_GCM_TEXTURE_X32_FLOAT" }, 
		{ 0x9D, "CELL_GCM_TEXTURE_D1R5G5B5" }, 
		{ 0x9E, "CELL_GCM_TEXTURE_D8R8G8B8" }, 
		{ 0x9F, "CELL_GCM_TEXTURE_Y16_X16_FLOAT" },
	};

	const int FORMAT_NUM = sizeof(sFormatString)/sizeof(sFormatString[0]);

	for(int i = 0; i < FORMAT_NUM; ++i){
		if(gtfGetRawFormat(format) != sFormatString[i].format) continue;

		return &sFormatString[i].string[17];
	}

	return sFormatString[0].string;
}

void gtfCheckSpec(CellGcmTexture tex)
{
	PRINTF("  [GTF Spec]\n");

	uint32_t raw_format = gtfGetRawFormat(tex.format);
	bool is_dxt = (
		raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT1 || 
		raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT23 || 
		raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT45);

	if(tex.dimension == CELL_GCM_TEXTURE_DIMENSION_3){
		PRINTF("    Size: %dx%dx%d\n", tex.width, tex.height, tex.depth);
	}else{
		PRINTF("    Size: %dx%d\n", tex.width, tex.height);
	}
	PRINTF("    Info: mipmap=%d, cube=%d, pitch=%d, normalized=%d\n", tex.mipmap, tex.cubemap, tex.pitch, (tex.format & CELL_GCM_TEXTURE_UN? 0: 1));
	PRINTF("    Format: %s\n", gtfGetFormatName(tex.format));

	PRINTF("    Layout: ");
	if(is_dxt){
		if(tex.format & CELL_GCM_TEXTURE_LN){
			PRINTF("Not Power of 2\n");
		}else{
			PRINTF("Power of 2\n");
		}
	}else{
		if(tex.format & CELL_GCM_TEXTURE_LN){
			PRINTF("Linear\n");
		}else{
			PRINTF("Swizzle\n");
		}
	}

	PRINTF("    Remap: %s (0x%04x)\n", utilRemap2Str(tex.remap), tex.remap);
}

bool gtfIsDxtn(uint8_t format)
{
	uint8_t raw_format = gtfGetRawFormat(format);
	return (raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT1 || 
			raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT23 || 
			raw_format == CELL_GCM_TEXTURE_COMPRESSED_DXT45);
}

bool gtfIsSwizzlable(CellGcmTexture tex)
{
	bool ret = true;

	uint32_t raw_format = gtfGetRawFormat(tex.format);

	if( raw_format == CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW || 
		raw_format == CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW)
	{
		return false;
	}

	if(tex.dimension == CELL_GCM_TEXTURE_DIMENSION_3){
		ret = is_pow2(tex.width) && is_pow2(tex.height) && is_pow2(tex.depth);
	}else{
		ret = is_pow2(tex.width) && is_pow2(tex.height);
	}

	return ret;
}

} // namespace gtfconv
