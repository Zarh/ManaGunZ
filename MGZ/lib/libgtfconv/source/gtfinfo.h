#ifndef __GTFCONV_GTFINFO_H__
#define __GTFCONV_GTFINFO_H__

#include "utils.h"

// Texture File Header
typedef struct
{
	uint32_t  version;      // Version (Correspond to dds2gtf converter version)
	uint32_t  size;         // Total size of Texture. (Excluding size of header & attribute)
	uint32_t  numTexture;   // Number of textures in this file.

} CellGtfFileHeader;

typedef struct
{
	uint8_t format;
	uint8_t mipmap;
	uint8_t dimension;
	uint8_t cubemap;
	uint32_t remap;
	uint16_t width;
	uint16_t height;
	uint16_t depth;
	uint8_t location;
	uint8_t _padding;
	uint32_t pitch;
	uint32_t offset;
} CellGcmTexture;

// 
// Attribute for Texture data 
//
// NOTE:
//  It is always true that the number of textures in GTF file 
//  equals the number of CellGtfTextureAttribute in header.
//
typedef struct
{         
	uint32_t id;            // Texture ID.  
	uint32_t offsetToTex;   // Offset to texture from begining of file.
	uint32_t textureSize;	// Size of texture.
	CellGcmTexture tex;		// Texture structure defined in GCM library.

} CellGtfTextureAttribute;

// CellGcmEnum declaration from gcm.h
typedef enum {
	//	Enable
	CELL_GCM_FALSE	= (0),
	CELL_GCM_TRUE	= (1),

	// Location
	CELL_GCM_LOCATION_LOCAL	= (0),
	CELL_GCM_LOCATION_MAIN	= (1),

	// SetTexture
	CELL_GCM_TEXTURE_B8						= (0x81),
	CELL_GCM_TEXTURE_A1R5G5B5				= (0x82),
	CELL_GCM_TEXTURE_A4R4G4B4				= (0x83),
	CELL_GCM_TEXTURE_R5G6B5					= (0x84),
	CELL_GCM_TEXTURE_A8R8G8B8				= (0x85),
	CELL_GCM_TEXTURE_COMPRESSED_DXT1		= (0x86),
	CELL_GCM_TEXTURE_COMPRESSED_DXT23		= (0x87),
	CELL_GCM_TEXTURE_COMPRESSED_DXT45		= (0x88),
	CELL_GCM_TEXTURE_G8B8					= (0x8B),
	CELL_GCM_TEXTURE_R6G5B5					= (0x8F),
	CELL_GCM_TEXTURE_DEPTH24_D8				= (0x90),
	CELL_GCM_TEXTURE_DEPTH24_D8_FLOAT		= (0x91),
	CELL_GCM_TEXTURE_DEPTH16				= (0x92),
	CELL_GCM_TEXTURE_DEPTH16_FLOAT			= (0x93),
	CELL_GCM_TEXTURE_X16					= (0x94),
	CELL_GCM_TEXTURE_Y16_X16				= (0x95),
	CELL_GCM_TEXTURE_R5G5B5A1				= (0x97),
	CELL_GCM_TEXTURE_COMPRESSED_HILO8		= (0x98),
	CELL_GCM_TEXTURE_COMPRESSED_HILO_S8		= (0x99),
	CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT	= (0x9A),
	CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT	= (0x9B),
	CELL_GCM_TEXTURE_X32_FLOAT				= (0x9C),
	CELL_GCM_TEXTURE_D1R5G5B5				= (0x9D),
	CELL_GCM_TEXTURE_D8R8G8B8				= (0x9E),
	CELL_GCM_TEXTURE_Y16_X16_FLOAT			= (0x9F),
	CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8	= (0xAD),
	CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8	= (0xAE),
	CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8_RAW = (0x8D),
	CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8_RAW = (0x8E),

	CELL_GCM_TEXTURE_SZ	= (0x00),
	CELL_GCM_TEXTURE_LN	= (0x20),
	CELL_GCM_TEXTURE_NR	= (0x00),
	CELL_GCM_TEXTURE_UN	= (0x40),

	CELL_GCM_TEXTURE_DIMENSION_1		= (1),
	CELL_GCM_TEXTURE_DIMENSION_2		= (2),
	CELL_GCM_TEXTURE_DIMENSION_3		= (3),

	CELL_GCM_TEXTURE_REMAP_ORDER_XYXY	= (0),
	CELL_GCM_TEXTURE_REMAP_ORDER_XXXY	= (1),
	CELL_GCM_TEXTURE_REMAP_FROM_A		= (0),
	CELL_GCM_TEXTURE_REMAP_FROM_R		= (1),
	CELL_GCM_TEXTURE_REMAP_FROM_G		= (2),
	CELL_GCM_TEXTURE_REMAP_FROM_B		= (3),
	CELL_GCM_TEXTURE_REMAP_ZERO			= (0),
	CELL_GCM_TEXTURE_REMAP_ONE			= (1),
	CELL_GCM_TEXTURE_REMAP_REMAP		= (2),

}CellGcmEnumForGtf;

#endif // __GTFCONV_GTFINFO_H__
