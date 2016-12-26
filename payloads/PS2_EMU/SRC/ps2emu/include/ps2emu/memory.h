#ifndef __PS2EMU_MEMORY_H__
#define __PS2EMU_MEMORY_H__

#include <stdlib.h>
#include <memory.h>
#include <ps2emu/ps2emu.h>

PS2EMU_EXPORT void *ps2emu_malloc(size_t size);
PS2EMU_EXPORT void ps2emu_free(void *p);
PS2EMU_EXPORT void *zeroalloc(size_t size);

#endif /* __PS2EMU_MEMORY_H__ */
