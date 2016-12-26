#include <ps2emu/macros.h.S>
#include <ps2emu/symbols.h>

PS2EMU_FUNCTION(ufs_open, ufs_open_symbol)
PS2EMU_FUNCTION(ufs_close, ufs_close_symbol)
PS2EMU_FUNCTION(ufs_read, ufs_read_symbol)
PS2EMU_FUNCTION(ufs_write, ufs_write_symbol)

#ifdef ufs_fstat_symbol
PS2EMU_FUNCTION(ufs_fstat, ufs_fstat_symbol)
#endif






