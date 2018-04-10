#include <lv2/macros.h.S>
#include <lv2/symbols.h>

#ifdef cellFsOpen_symbol
LV2_FUNCTION(cellFsOpen, cellFsOpen_symbol)
#endif

#ifdef cellFsClose_symbol
LV2_FUNCTION(cellFsClose, cellFsClose_symbol)
#endif

#ifdef cellFsRead_symbol
LV2_FUNCTION(cellFsRead, cellFsRead_symbol)
#endif

#ifdef cellFsWrite_symbol
LV2_FUNCTION(cellFsWrite, cellFsWrite_symbol)
#endif

#ifdef cellFsLseek_symbol
LV2_FUNCTION(cellFsLseek, cellFsLseek_symbol)
#endif

#ifdef cellFsStat_symbol
LV2_FUNCTION(cellFsStat, cellFsStat_symbol)
#endif

#ifdef cellFsUtime_symbol
LV2_FUNCTION(cellFsUtime, cellFsUtime_symbol)
#endif

#ifdef cellFsUnlink_internal_symbol
LV2_FUNCTION(cellFsUnlink_internal, cellFsUnlink_internal_symbol)
#endif

#ifdef cellFsUtilMount_symbol
LV2_FUNCTION(cellFsUtilMount, cellFsUtilMount_symbol) 
LV2_FUNCTION3(cellFsUtilMount_h, cellFsUtilMount_symbol) /* We need to call this but it is hooked */
#endif

#ifdef cellFsUtilUmount_symbol
LV2_FUNCTION(cellFsUtilUmount, cellFsUtilUmount_symbol)
#endif

#ifdef cellFsUtilNewfs_symbol
LV2_FUNCTION(cellFsUtilNewfs, cellFsUtilNewfs_symbol)
#endif

#ifdef pathdup_from_user_symbol
LV2_FUNCTION(pathdup_from_user, pathdup_from_user_symbol)
#endif

#ifdef open_fs_object_symbol
LV2_FUNCTION(open_fs_object, open_fs_object_symbol)
#endif

#ifdef close_fs_object_symbol
LV2_FUNCTION(close_fs_object, close_fs_object_symbol)
#endif




