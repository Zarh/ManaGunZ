#ifndef __PS2EMU_LIBC_H__
#define __PS2EMU_LIBC_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <ps2emu/ps2emu.h>
#include <ps2emu/memory.h>

PS2EMU_EXPORT int ps2emu_snprintf(char *str, size_t size, const char *format, ...) __attribute__ ((format (printf, 3, 4)));
PS2EMU_EXPORT char *ps2emu_strcpy(char *s1, const char *s2);
PS2EMU_EXPORT char *ps2emu_strcat(char *s1, const char *s2);
PS2EMU_EXPORT size_t ps2emu_strlen (const char * str);
PS2EMU_EXPORT void *ps2emu_memcpy(void *dest, const void *src, size_t n);
PS2EMU_EXPORT void *ps2emu_memset(void *s, int c, size_t n);

#define snprintf	ps2emu_snprintf
#define strcpy		ps2emu_strcpy
#define strcat		ps2emu_strcat
#define strlen		ps2emu_strlen
#define memcpy		ps2emu_memcpy
#define memset		ps2emu_memset
#define malloc		ps2emu_malloc
#define free		ps2emu_free


#endif /* _PS2EMU_LIBC_H__ */
