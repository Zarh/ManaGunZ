#include <ps2emu/macros.h.S>
#include <ps2emu/symbols.h>

#ifdef snprintf_symbol
PS2EMU_FUNCTION(ps2emu_snprintf, snprintf_symbol)
#endif

PS2EMU_FUNCTION(ps2emu_strcpy, strcpy_symbol)
PS2EMU_FUNCTION(ps2emu_strlen, strlen_symbol)
PS2EMU_FUNCTION(ps2emu_strcat, strcat_symbol)
PS2EMU_FUNCTION(ps2emu_memcpy, memcpy_symbol)
PS2EMU_FUNCTION(ps2emu_memset, memset_symbol)

/* For compatibility with apps that don't import ps2emu/libc.h */
#ifdef snprintf_symbol
PS2EMU_FUNCTION2(snprintf, snprintf_symbol)
#endif

PS2EMU_FUNCTION2(strcpy, strcpy_symbol)
PS2EMU_FUNCTION2(strlen, strlen_symbol)
PS2EMU_FUNCTION2(strcat, strcat_symbol)
PS2EMU_FUNCTION2(memcpy, memcpy_symbol)
PS2EMU_FUNCTION2(memset, memset_symbol)

