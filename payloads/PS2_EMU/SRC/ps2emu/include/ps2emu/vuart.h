#ifndef __PS2EMU_VUART_H__
#define __PS2EMU_VUART_H__

#include <ps2emu/ps2emu.h>

#define VUART_PORT_AV		0
#define VUART_PORT_SYSMGGR	2
#define VUART_PORT_DISPMGR	10


PS2EMU_EXPORT int vuart_read(uint64_t port, void *buf, uint64_t size);
PS2EMU_EXPORT int vuart_write(uint64_t port, void *buf, uint64_t size);

#endif /* __PS2EMU_VUART_H__ */


