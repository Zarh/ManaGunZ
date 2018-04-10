#include <lv2/macros.h.S>
#include <lv2/symbols.h>

#ifdef alloc_symbol
LV2_FUNCTION(alloc, alloc_symbol)
#endif

#ifdef dealloc_symbol
LV2_FUNCTION(dealloc, dealloc_symbol)
#endif

#ifdef copy_to_user_symbol
LV2_FUNCTION(copy_to_user, copy_to_user_symbol)
#endif

#ifdef copy_from_user_symbol
LV2_FUNCTION(copy_from_user, copy_from_user_symbol)
#endif

#ifdef copy_to_process_symbol
LV2_FUNCTION(copy_to_process, copy_to_process_symbol)
#endif

#ifdef copy_from_process_symbol
LV2_FUNCTION(copy_from_process, copy_from_process_symbol)
#endif

#ifdef page_allocate_symbol
LV2_FUNCTION(page_allocate, page_allocate_symbol)
#endif

#ifdef page_free_symbol
LV2_FUNCTION(page_free, page_free_symbol)
#endif

#ifdef page_export_to_proc_symbol
LV2_FUNCTION(page_export_to_proc, page_export_to_proc_symbol)
#endif

#ifdef page_unexport_from_proc_symbol
LV2_FUNCTION(page_unexport_from_proc, page_unexport_from_proc_symbol)
#endif

#ifdef kernel_ea_to_lpar_addr_symbol
LV2_FUNCTION(kernel_ea_to_lpar_addr, kernel_ea_to_lpar_addr_symbol)
#endif

#ifdef process_ea_to_lpar_addr_ex_symbol
LV2_FUNCTION(process_ea_to_lpar_addr_ex, process_ea_to_lpar_addr_ex_symbol)
#endif

#ifdef set_pte_symbol
LV2_FUNCTION(set_pte, set_pte_symbol)
#endif



