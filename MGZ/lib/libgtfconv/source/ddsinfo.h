#ifndef __GTFCONV_DDSINFO_H__
#define __GTFCONV_DDSINFO_H__

#include "utils.h"

typedef struct {
	uint32_t size;
	uint32_t flags;
	uint32_t fourCC;
	uint32_t rgbBitCount;
	uint32_t rbitMask;
	uint32_t gbitMask;
	uint32_t bbitMask;
	uint32_t abitMask;
} CellUtilDDSPixelFormat;

typedef struct {
	uint32_t magic;
	uint32_t size;
	uint32_t flags;
	uint32_t height;
	uint32_t width;
	uint32_t pitchOrLinearSize;
	uint32_t depth;
	uint32_t mipMapCount;
	uint32_t reserved1[11];
	CellUtilDDSPixelFormat ddspf;
	uint32_t caps1;
	uint32_t caps2;
	uint32_t reserved2[3];
} CellUtilDDSHeader;

// surface description flags
#define 	DDSF_MAX_MIPMAPS	16
#define 	DDSF_MAX_VOLUME	    512
#define 	DDSF_MAX_TEXTURES	16		

#define		DDSF_CAPS           0x00000001
#define 	DDSF_HEIGHT         0x00000002
#define 	DDSF_WIDTH          0x00000004
#define 	DDSF_PITCH          0x00000008
#define 	DDSF_PIXELFORMAT    0x00001000
#define 	DDSF_MIPMAPCOUNT    0x00020000
#define 	DDSF_LINEARSIZE     0x00080000
#define 	DDSF_DEPTH			0x00800000

// pixel format flags
#define		DDSF_ALPHAPIXELS	0x00000001
#define		DDSF_FOURCC			0x00000004
#define		DDSF_RGB			0x00000040
#define		DDSF_RGBA			0x00000041
#define		DDSF_LUMINANCE		0x00020000
#define		DDSF_BUMPDUDV		0x00080000

// dwCaps1 flags
#define DDSF_COMPLEX			0x00000008
#define DDSF_TEXTURE			0x00001000
#define DDSF_MIPMAP				0x00400000

// dwCaps2 flags
#define DDSF_CUBEMAP			0x00000200L
#define DDSF_CUBEMAP_POSITIVEX  0x00000400L
#define DDSF_CUBEMAP_NEGATIVEX  0x00000800L
#define DDSF_CUBEMAP_POSITIVEY  0x00001000L
#define DDSF_CUBEMAP_NEGATIVEY  0x00002000L
#define DDSF_CUBEMAP_POSITIVEZ  0x00004000L
#define DDSF_CUBEMAP_NEGATIVEZ  0x00008000L
#define DDSF_CUBEMAP_ALL_FACES  0x0000FC00L
#define DDSF_VOLUME				0x00200000L

#define FOURCC_R16F             0x6F
#define FOURCC_G16R16F          0x70
#define FOURCC_A16B16G16R16F    0x71
#define FOURCC_R32F             0x72
#define FOURCC_A32B32G32R32F    0x74

#define FOURCC_YVYU             0x59565955
#define FOURCC_YUY2             0x32595559
#define FOURCC_R8G8_B8G8        0x47424752
#define FOURCC_G8R8_G8B8        0x42475247

/******************************************************************************
 * copied & pasted & modified from NVIDIA Texture Tools
 */

#if !defined(MAKEFOURCC)
#      define MAKEFOURCC(ch0, ch1, ch2, ch3) \
              ((unsigned int)((char)(ch0)) | ((unsigned int)((char)(ch1)) << 8) | \
              ((unsigned int)((char)(ch2)) << 16) | ((unsigned int)((char)(ch3)) << 24 ))
#endif

static const unsigned int FOURCC_DDS = MAKEFOURCC('D', 'D', 'S', ' ');
static const unsigned int FOURCC_DXT1 = MAKEFOURCC('D', 'X', 'T', '1');
static const unsigned int FOURCC_DXT2 = MAKEFOURCC('D', 'X', 'T', '2');
static const unsigned int FOURCC_DXT3 = MAKEFOURCC('D', 'X', 'T', '3');
static const unsigned int FOURCC_DXT4 = MAKEFOURCC('D', 'X', 'T', '4');
static const unsigned int FOURCC_DXT5 = MAKEFOURCC('D', 'X', 'T', '5');
static const unsigned int FOURCC_RXGB = MAKEFOURCC('R', 'X', 'G', 'B');
static const unsigned int FOURCC_ATI1 = MAKEFOURCC('A', 'T', 'I', '1');
static const unsigned int FOURCC_ATI2 = MAKEFOURCC('A', 'T', 'I', '2');

/* RGB formats. */
static const unsigned int D3DFMT_R8G8B8 = 20;
static const unsigned int D3DFMT_A8R8G8B8 = 21;
static const unsigned int D3DFMT_X8R8G8B8 = 22;
static const unsigned int D3DFMT_R5G6B5 = 23;
static const unsigned int D3DFMT_X1R5G5B5 = 24;
static const unsigned int D3DFMT_A1R5G5B5 = 25;
static const unsigned int D3DFMT_A4R4G4B4 = 26;
static const unsigned int D3DFMT_R3G3B2 = 27;
static const unsigned int D3DFMT_A8 = 28;
static const unsigned int D3DFMT_A8R3G3B2 = 29;
static const unsigned int D3DFMT_X4R4G4B4 = 30;
static const unsigned int D3DFMT_A2B10G10R10 = 31;
static const unsigned int D3DFMT_A8B8G8R8 = 32;
static const unsigned int D3DFMT_X8B8G8R8 = 33;
static const unsigned int D3DFMT_G16R16 = 34;
static const unsigned int D3DFMT_A2R10G10B10 = 35;
static const unsigned int D3DFMT_A16B16G16R16 = 36;

/* Palette formats. */
static const unsigned int D3DFMT_A8P8 = 40;
static const unsigned int D3DFMT_P8 = 41;

/* Luminance formats. */
static const unsigned int D3DFMT_L8 = 50;
static const unsigned int D3DFMT_A8L8 = 51;
static const unsigned int D3DFMT_A4L4 = 52;

/* Floating point formats */
static const unsigned int D3DFMT_R16F = 111;
static const unsigned int D3DFMT_G16R16F = 112;
static const unsigned int D3DFMT_A16B16G16R16F = 113;
static const unsigned int D3DFMT_R32F = 114;
static const unsigned int D3DFMT_G32R32F = 115;
static const unsigned int D3DFMT_A32B32G32R32F = 116;

static const unsigned int DDSD_CAPS = 0x00000001U;
static const unsigned int DDSD_PIXELFORMAT = 0x00001000U;
static const unsigned int DDSD_WIDTH = 0x00000004U;
static const unsigned int DDSD_HEIGHT = 0x00000002U;
static const unsigned int DDSD_PITCH = 0x00000008U;
static const unsigned int DDSD_MIPMAPCOUNT = 0x00020000U;
static const unsigned int DDSD_LINEARSIZE = 0x00080000U;
static const unsigned int DDSD_DEPTH = 0x00800000U;

static const unsigned int DDSCAPS_ALPHA = 0x00000002U;
static const unsigned int DDSCAPS_COMPLEX = 0x00000008U;
static const unsigned int DDSCAPS_TEXTURE = 0x00001000U;
static const unsigned int DDSCAPS_MIPMAP = 0x00400000U;
static const unsigned int DDSCAPS2_VOLUME = 0x00200000U;
static const unsigned int DDSCAPS2_CUBEMAP = 0x00000200U;

static const unsigned int DDSCAPS2_CUBEMAP_POSITIVEX = 0x00000400U;
static const unsigned int DDSCAPS2_CUBEMAP_NEGATIVEX = 0x00000800U;
static const unsigned int DDSCAPS2_CUBEMAP_POSITIVEY = 0x00001000U;
static const unsigned int DDSCAPS2_CUBEMAP_NEGATIVEY = 0x00002000U;
static const unsigned int DDSCAPS2_CUBEMAP_POSITIVEZ = 0x00004000U;
static const unsigned int DDSCAPS2_CUBEMAP_NEGATIVEZ = 0x00008000U;
static const unsigned int DDSCAPS2_CUBEMAP_ALL_FACES = 0x0000FC00U;

static const unsigned int DDPF_ALPHAPIXELS = 0x00000001U;
static const unsigned int DDPF_ALPHA = 0x00000002U;
static const unsigned int DDPF_FOURCC = 0x00000004U;
static const unsigned int DDPF_RGB = 0x00000040U;
static const unsigned int DDPF_PALETTEINDEXED1 = 0x00000800U;
static const unsigned int DDPF_PALETTEINDEXED2 = 0x00001000U;
static const unsigned int DDPF_PALETTEINDEXED4 = 0x00000008U;
static const unsigned int DDPF_PALETTEINDEXED8 = 0x00000020U;
static const unsigned int DDPF_LUMINANCE = 0x00020000U;
static const unsigned int DDPF_ALPHAPREMULT = 0x00008000U;
static const unsigned int DDPF_NORMAL = 0x80000000U;   // @@ Custom nv flag.

#endif // __GTFCONV_DDSINFO_H__
