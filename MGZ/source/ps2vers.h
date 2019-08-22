#ifndef _PS2VERS_H__
#define _PS2VERS_H__

#include "ps2crc.h"
#include "ps2data.h"

u8 get_hwemu(u32 crc, u8 **stage1, u32 *stage1_size, u8 **stage2, u32 *stage2_size);
u8 get_gxemu(u32 crc, u8 **stage1, u32 *stage1_size, u8 **stage2, u32 *stage2_size);
u8 get_netemu(u32 crc, u8 **stage2, u32 *stage2_size);

#endif /* __PS2VERS_H__ */