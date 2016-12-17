#ifndef __GTFCONV_GTFUTIL_H__
#define __GTFCONV_GTFUTIL_H__

#include "gtfinfo.h"
#include "utils.h"

namespace gtfconv{

uint8_t gtfGetRawFormat(uint8_t format);
uint32_t gtfGetPitch(uint8_t format, uint32_t width);
uint16_t gtfGetDepth(uint8_t format);
uint32_t gtfGetNumComponent(uint8_t format);
const char* gtfGetFormatName(uint8_t format);
void gtfCheckSpec(CellGcmTexture tex);
bool gtfIsDxtn(uint8_t format);
bool gtfIsSwizzle(uint8_t format);
bool gtfIsSwizzlable(CellGcmTexture tex);

} // namespace gtfconv

#endif // __GTFCONV_GTFUTIL_H__
