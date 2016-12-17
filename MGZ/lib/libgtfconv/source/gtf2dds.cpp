#include "utils.h"
#include "convert.h"
#include "gtfconv.h"

using namespace gtfconv;

namespace gtfconv{

bool gtf2ddsConvHeader(CellUtilDDSHeader *pddsh, CellGcmTexture texture)
{
	if(!pddsh) return false;

	uint8_t raw_format = gtfGetRawFormat(texture.format);
	bool is_dxt = gtfIsDxtn(raw_format);

	CellUtilDDSHeader &ddsh = *pddsh;

	switch(raw_format){
		case CELL_GCM_TEXTURE_B8:
			ddsh.ddspf.flags = DDSF_LUMINANCE;
			ddsh.ddspf.rgbBitCount = 8;
			ddsh.ddspf.rbitMask = 0x000000ff;
			break;
		case CELL_GCM_TEXTURE_A1R5G5B5:
			ddsh.ddspf.flags = DDPF_RGB | DDPF_ALPHAPIXELS;
			ddsh.ddspf.rgbBitCount = 16;
			ddsh.ddspf.abitMask = 0x00008000;
			ddsh.ddspf.rbitMask = 0x00007c00;
			ddsh.ddspf.gbitMask = 0x000003e0;
			ddsh.ddspf.bbitMask = 0x0000001f;
			break;
		case CELL_GCM_TEXTURE_A4R4G4B4:
			ddsh.ddspf.flags = DDPF_RGB | DDPF_ALPHAPIXELS;
			ddsh.ddspf.rgbBitCount = 16;
			ddsh.ddspf.abitMask = 0x0000f000;
			ddsh.ddspf.rbitMask = 0x00000f00;
			ddsh.ddspf.gbitMask = 0x000000f0;
			ddsh.ddspf.bbitMask = 0x0000000f;
			break;
		case CELL_GCM_TEXTURE_R5G6B5:
			ddsh.ddspf.flags = DDPF_RGB;
			ddsh.ddspf.rgbBitCount = 16;
			ddsh.ddspf.abitMask = 0x00000000;
			ddsh.ddspf.rbitMask = 0x0000f800;
			ddsh.ddspf.gbitMask = 0x000007e0;
			ddsh.ddspf.bbitMask = 0x0000001f;
			break;
		case CELL_GCM_TEXTURE_R6G5B5:
			ddsh.ddspf.flags = DDPF_RGB;
			ddsh.ddspf.rgbBitCount = 16;
			ddsh.ddspf.abitMask = 0x00000000;
			ddsh.ddspf.rbitMask = 0x0000fc00;
			ddsh.ddspf.gbitMask = 0x000003e0;
			ddsh.ddspf.bbitMask = 0x0000001f;
			break;
		case CELL_GCM_TEXTURE_R5G5B5A1:
			ddsh.ddspf.flags = DDPF_RGB;
			ddsh.ddspf.rgbBitCount = 16;
			ddsh.ddspf.abitMask = 0x00000001;
			ddsh.ddspf.rbitMask = 0x0000f800;
			ddsh.ddspf.gbitMask = 0x000007c0;
			ddsh.ddspf.bbitMask = 0x0000003e;
			break;
		case CELL_GCM_TEXTURE_D1R5G5B5:
			ddsh.ddspf.flags = DDPF_RGB;
			ddsh.ddspf.rgbBitCount = 16;
			ddsh.ddspf.abitMask = 0x00008000;
			ddsh.ddspf.rbitMask = 0x00007c00;
			ddsh.ddspf.gbitMask = 0x000003e0;
			ddsh.ddspf.bbitMask = 0x0000001f;
			break;
		case CELL_GCM_TEXTURE_A8R8G8B8:
			ddsh.ddspf.flags = DDPF_RGB | DDPF_ALPHAPIXELS;
			ddsh.ddspf.rgbBitCount = 32;
			ddsh.ddspf.abitMask = 0xff000000;
			ddsh.ddspf.rbitMask = 0x00ff0000;
			ddsh.ddspf.gbitMask = 0x0000ff00;
			ddsh.ddspf.bbitMask = 0x000000ff;
			
			break;
		case CELL_GCM_TEXTURE_D8R8G8B8:
			ddsh.ddspf.flags = DDPF_RGB;
			ddsh.ddspf.rgbBitCount = 32;
			ddsh.ddspf.abitMask = 0xff000000;
			ddsh.ddspf.rbitMask = 0x00ff0000;
			ddsh.ddspf.gbitMask = 0x0000ff00;
			ddsh.ddspf.bbitMask = 0x000000ff;
			break;
		case CELL_GCM_TEXTURE_G8B8:
			// A8L8
			ddsh.ddspf.flags = DDSF_LUMINANCE | DDPF_ALPHAPIXELS;
			ddsh.ddspf.rgbBitCount = 16;
			ddsh.ddspf.abitMask = 0x0000ff00;
			ddsh.ddspf.rbitMask = 0x000000ff;
			break;
		case CELL_GCM_TEXTURE_X16:
			// L16
			ddsh.ddspf.flags = DDSF_LUMINANCE;
			ddsh.ddspf.rgbBitCount = 16;
			ddsh.ddspf.rbitMask = 0x0000ffff;
			break;
		case CELL_GCM_TEXTURE_Y16_X16:
			// G16R16
			ddsh.ddspf.flags = DDPF_RGB;
			ddsh.ddspf.rgbBitCount = 32;
			ddsh.ddspf.abitMask = 0x00000000;
			ddsh.ddspf.rbitMask = 0x0000ffff;
			ddsh.ddspf.gbitMask = 0xffff0000;
			ddsh.ddspf.bbitMask = 0x00000000;
			break;
		case CELL_GCM_TEXTURE_COMPRESSED_DXT1:
			ddsh.ddspf.flags = DDPF_FOURCC;
			ddsh.ddspf.fourCC = FOURCC_DXT1;
			break;
		case CELL_GCM_TEXTURE_COMPRESSED_DXT23:
			ddsh.ddspf.flags = DDPF_FOURCC;
			ddsh.ddspf.fourCC = FOURCC_DXT3;
			break;
		case CELL_GCM_TEXTURE_COMPRESSED_DXT45:
			ddsh.ddspf.flags = DDPF_FOURCC;
			ddsh.ddspf.fourCC = FOURCC_DXT5;
			break;
		case CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT:
			ddsh.ddspf.flags = DDPF_FOURCC;
			ddsh.ddspf.fourCC = FOURCC_A16B16G16R16F;
			break;
		case CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT:
			ddsh.ddspf.flags = DDPF_FOURCC;
			ddsh.ddspf.fourCC = FOURCC_A32B32G32R32F;
			break;
		case CELL_GCM_TEXTURE_X32_FLOAT:
			ddsh.ddspf.flags = DDPF_FOURCC;
			ddsh.ddspf.fourCC = FOURCC_R32F;
			break;
		case CELL_GCM_TEXTURE_Y16_X16_FLOAT:
			ddsh.ddspf.flags = DDPF_FOURCC;
			ddsh.ddspf.fourCC = FOURCC_G16R16F;
			break;
		case CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW:
			ddsh.ddspf.flags = DDPF_FOURCC;
			ddsh.ddspf.fourCC = FOURCC_R8G8_B8G8;
			break;
		case CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW:
			ddsh.ddspf.flags = DDPF_FOURCC;
			ddsh.ddspf.fourCC = FOURCC_G8R8_G8B8;
			break;

		// unsupported
		case CELL_GCM_TEXTURE_COMPRESSED_HILO8:
		case CELL_GCM_TEXTURE_COMPRESSED_HILO_S8:
		default:
			return false;
	}

	ddsh.magic = FOURCC_DDS;
	ddsh.size = 124;
	ddsh.flags |= DDSD_CAPS;
	ddsh.flags |= DDSD_PIXELFORMAT;
	ddsh.flags |= DDSD_WIDTH;
	ddsh.flags |= DDSD_HEIGHT;
	ddsh.caps1 |= DDSCAPS_TEXTURE;

	if(texture.mipmap != 1){
		ddsh.flags |= DDSD_MIPMAPCOUNT;
		ddsh.caps1 |= DDSCAPS_MIPMAP;
		ddsh.caps1 |= DDSCAPS_COMPLEX;
		ddsh.mipMapCount = texture.mipmap;
	}

	if(texture.dimension == CELL_GCM_TEXTURE_DIMENSION_3){
		ddsh.flags |= DDSD_DEPTH;
		ddsh.caps1 |= DDSCAPS2_VOLUME;
		ddsh.caps1 |= DDSCAPS_COMPLEX;
		ddsh.depth = texture.depth;
	}

	if(texture.cubemap == CELL_GCM_TRUE){
		ddsh.caps1 |= DDSCAPS2_CUBEMAP;
		ddsh.caps1 |= DDSCAPS_COMPLEX;

		ddsh.caps2 |= DDSCAPS2_CUBEMAP_POSITIVEX;
		ddsh.caps2 |= DDSCAPS2_CUBEMAP_NEGATIVEX;
		ddsh.caps2 |= DDSCAPS2_CUBEMAP_POSITIVEY;
		ddsh.caps2 |= DDSCAPS2_CUBEMAP_NEGATIVEY;
		ddsh.caps2 |= DDSCAPS2_CUBEMAP_POSITIVEZ;
		ddsh.caps2 |= DDSCAPS2_CUBEMAP_NEGATIVEZ;
	}

	if(ddsh.ddspf.flags & DDPF_ALPHAPIXELS){
		ddsh.caps1 |= DDSCAPS_ALPHA;
	}

	ddsh.ddspf.size = 32;
	

	ddsh.width = texture.width;
	ddsh.height = texture.height;

	bool bLinearSize = false;
	bool bNoPitchOrLinearSize = false;
	if(raw_format == CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW || 
		raw_format == CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW)
	{
		bNoPitchOrLinearSize = true;
	}

	if(bNoPitchOrLinearSize){
		ddsh.pitchOrLinearSize = 0;
	}else if(is_dxt){
		uint16_t color_depth = gtfGetDepth(raw_format);
		ddsh.pitchOrLinearSize = ((texture.width + 3) / 4) * ((texture.height + 3) / 4) * color_depth;

		ddsh.flags |= DDSD_LINEARSIZE;
	}else if(bLinearSize){
		uint32_t pitch = gtfGetPitch(raw_format, texture.width);
		ddsh.pitchOrLinearSize = texture.height * pitch;

		ddsh.flags |= DDSD_LINEARSIZE;
	}else if(texture.pitch != 0){
		ddsh.pitchOrLinearSize = texture.pitch;

		ddsh.flags |= DDSD_PITCH;
	}
	
	return true;
}

int32_t gtfconv_gtf2dds_image(GTF_BUFFER_T *ddsOutput, const GTF_CONV_T *gtfInput, uint32_t option)
{
	(void)option;
	if(!gtfInput) return CELL_GTFCONV_ERROR;
	if(gtfInput->size == 0) return CELL_GTFCONV_ERROR;

	CellGcmTexture texture = gtfInput->gcmt;

	// gtf spec
	gtfCheckSpec(texture);

	CellUtilDDSHeader ddsh;
	memset(&ddsh, 0, sizeof(CellUtilDDSHeader));
	if(gtf2ddsConvHeader(&ddsh, texture) == false){
		return CELL_GTFCONV_ERROR;
	}

	// dds spec
	if(!ddsCheckSpec(ddsh)){
		return CELL_GTFCONV_ERROR;
	}

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

	if(gtfInput->size < gtf_image_size){
		return CELL_GTFCONV_ERROR;
	}

	uint32_t dds_image_size = layout_array[layout_num - 1].dds_offset + layout_array[layout_num - 1].dds_size;
	uint32_t dds_file_size = dds_image_size + sizeof(CellUtilDDSHeader);

	if(!ddsOutput || ddsOutput->size < dds_file_size)
	{
		if(layout_array) delete [] layout_array, layout_array = 0;
		return static_cast<int32_t>(dds_file_size);
	}
	
	
	ddsh.magic = from_little_endian32(ddsh.magic);
	ddsh.size = from_little_endian32(ddsh.size);
	ddsh.flags = from_little_endian32(ddsh.flags);
	ddsh.height = from_little_endian32(ddsh.height);
	ddsh.width = from_little_endian32(ddsh.width);
	ddsh.pitchOrLinearSize = from_little_endian32(ddsh.pitchOrLinearSize);
	ddsh.depth = from_little_endian32(ddsh.depth);
	ddsh.mipMapCount = from_little_endian32(ddsh.mipMapCount);
	
	ddsh.ddspf.size = from_little_endian32(ddsh.ddspf.size);
	ddsh.ddspf.flags = from_little_endian32(ddsh.ddspf.flags );
	ddsh.ddspf.fourCC = from_little_endian32(ddsh.ddspf.fourCC );
	ddsh.ddspf.rgbBitCount = from_little_endian32(ddsh.ddspf.rgbBitCount);
	ddsh.ddspf.rbitMask = from_little_endian32(ddsh.ddspf.rbitMask);
	ddsh.ddspf.gbitMask = from_little_endian32(ddsh.ddspf.gbitMask);
	ddsh.ddspf.bbitMask = from_little_endian32(ddsh.ddspf.bbitMask);
	ddsh.ddspf.abitMask = from_little_endian32(ddsh.ddspf.abitMask);
	
	ddsh.caps1 = from_little_endian32(ddsh.caps1);
	ddsh.caps2 = from_little_endian32(ddsh.caps2);
	
	memset(ddsOutput->addr, 0, dds_file_size);
	memmove(ddsOutput->addr, &ddsh, sizeof(CellUtilDDSHeader));
    uint8_t *out_image = ddsOutput->addr + sizeof(CellUtilDDSHeader);

	// convert!!
	convertBufferByLayout(gtfInput->addr, out_image, layout_array, layout_num, texture, false);
	if(layout_array) delete [] layout_array, layout_array = 0;

	return CELL_GTFCONV_OK;
}

} // namespace gtfconv

int32_t gtfconv_gtf2dds(GTF_BUFFER_T *ddsOutput, const GTF_BUFFER_T *gtfInput, uint8_t index, uint32_t option)
{
	if(!gtfInput) return CELL_GTFCONV_ERROR;
	if(gtfInput->size < sizeof(CellGtfFileHeader)) return CELL_GTFCONV_ERROR;

	bool bVerbose = (option & CELL_GTFCONV_FLAG_VERBOSE) == CELL_GTFCONV_FLAG_VERBOSE;
	bool bVerbPrep = (ddsOutput == 0) && bVerbose;

	CellGtfFileHeader gtf_header;
	memmove(&gtf_header, gtfInput->addr, sizeof(CellGtfFileHeader));

	gtf_header.version = from_big_endian32(gtf_header.version);
	gtf_header.size = from_big_endian32(gtf_header.size);
	gtf_header.numTexture = from_big_endian32(gtf_header.numTexture);

	uint8_t tex_num = static_cast<uint8_t>(gtf_header.numTexture);

	if(gtfInput->size < sizeof(CellGtfFileHeader) + sizeof(CellGtfTextureAttribute) * tex_num){
		return CELL_GTFCONV_ERROR;
	}

	CellGtfTextureAttribute *gtf_attr = new CellGtfTextureAttribute[tex_num];
	memmove(gtf_attr, gtfInput->addr + sizeof(CellGtfFileHeader), sizeof(CellGtfTextureAttribute) * tex_num);

	for(uint8_t i = 0; i < tex_num; ++i){
		gtf_attr[i].id = from_big_endian32(gtf_attr[i].id);
		gtf_attr[i].offsetToTex = from_big_endian32(gtf_attr[i].offsetToTex);
		gtf_attr[i].textureSize = from_big_endian32(gtf_attr[i].textureSize);
		gtf_attr[i].tex.remap = from_big_endian32(gtf_attr[i].tex.remap);
		gtf_attr[i].tex.pitch = from_big_endian32(gtf_attr[i].tex.pitch);
		gtf_attr[i].tex.width = from_big_endian16(gtf_attr[i].tex.width);
		gtf_attr[i].tex.height = from_big_endian16(gtf_attr[i].tex.height);
		gtf_attr[i].tex.depth = from_big_endian16(gtf_attr[i].tex.depth);
	}

	bool bFound = false;
	CellGtfTextureAttribute gtf_target_attr;
	memset(&gtf_target_attr, 0, sizeof(CellGtfTextureAttribute));

	for(uint8_t i = 0; i < tex_num; ++i){
		if(gtf_attr[i].id != index) continue;

		gtf_target_attr = gtf_attr[i];
		bFound = true;
		break;
	}

	if(gtf_attr){
		delete [] gtf_attr, gtf_attr = 0;
	}

	if(!bFound){
		return CELL_GTFCONV_ERROR;
	}

	if(gtfInput->size < gtf_target_attr.offsetToTex + gtf_target_attr.textureSize){
		return CELL_GTFCONV_ERROR;
	}

	GTF_CONV_T gtfConv;
	gtfConv.gcmt = gtf_target_attr.tex;
	gtfConv.addr = gtfInput->addr + gtf_target_attr.offsetToTex;
	gtfConv.size = gtf_target_attr.textureSize;

	SET_PRINTF_MODE(bVerbPrep);
	int32_t dds_file_size = gtfconv_gtf2dds_image(0, &gtfConv, option);

	if(!ddsOutput || static_cast<int32_t>(ddsOutput->size) < dds_file_size)
	{
		return dds_file_size;
	}

	return gtfconv_gtf2dds_image(ddsOutput, &gtfConv, option);
}

int32_t gtfconv_gtf2dds_get_size(const GTF_BUFFER_T *gtfInput, uint8_t index, uint32_t option)
{
	return gtfconv_gtf2dds(0, gtfInput, index, option);
}

int16_t gtfconv_gtf2dds_get_texture_count(const GTF_BUFFER_T *gtfInput, uint32_t option)
{
	(void)option;
	if(!gtfInput) return CELL_GTFCONV_ERROR;

	if(gtfInput->size < sizeof(CellGtfFileHeader)) return CELL_GTFCONV_ERROR;

	CellGtfFileHeader gtf_header;
	memmove(&gtf_header, gtfInput->addr, sizeof(CellGtfFileHeader));

	gtf_header.version = from_big_endian32(gtf_header.version);
	gtf_header.size = from_big_endian32(gtf_header.size);
	gtf_header.numTexture = from_big_endian32(gtf_header.numTexture);

	uint8_t tex_num = static_cast<uint8_t>(gtf_header.numTexture);

	if(gtfInput->size < sizeof(CellGtfFileHeader) + sizeof(CellGtfTextureAttribute) * tex_num){
		return CELL_GTFCONV_ERROR;
	}

	return static_cast<int16_t>(tex_num);
}
