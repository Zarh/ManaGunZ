#include <lv2/macros.h.S>
#include <lv2/symbols.h>

#ifdef printf_symbol
LV2_FUNCTION(lv2_printf, printf_symbol)
#endif

#ifdef sprintf_symbol
LV2_FUNCTION(lv2_sprintf, sprintf_symbol)
#endif

#ifdef snprintf_symbol
LV2_FUNCTION(lv2_snprintf, snprintf_symbol)
#endif

#ifdef strcpy_symbol
LV2_FUNCTION(lv2_strcpy, strcpy_symbol)
#endif

#ifdef strncpy_symbol
LV2_FUNCTION(lv2_strncpy, strncpy_symbol)
#endif

#ifdef strlen_symbol
LV2_FUNCTION(lv2_strlen, strlen_symbol)
#endif

#ifdef strcat_symbol
LV2_FUNCTION(lv2_strcat, strcat_symbol)
#endif

#ifdef strcmp_symbol
LV2_FUNCTION(lv2_strcmp, strcmp_symbol)
#endif

#ifdef strncmp_symbol
LV2_FUNCTION(lv2_strncmp, strncmp_symbol)
#endif

#ifdef strchr_symbol
LV2_FUNCTION(lv2_strchr, strchr_symbol)
#endif

#ifdef strrchr_symbol
LV2_FUNCTION(lv2_strrchr, strrchr_symbol)
#endif

#ifdef memcpy_symbol
LV2_FUNCTION(lv2_memcpy, memcpy_symbol)
#endif

#ifdef memset_symbol
LV2_FUNCTION(lv2_memset, memset_symbol)
#endif

#ifdef memcmp_symbol
LV2_FUNCTION(lv2_memcmp, memcmp_symbol)
#endif

#ifdef memchr_symbol
LV2_FUNCTION(lv2_memchr, memchr_symbol)
#endif

/* For compatibility with apps that don't import lv2/libc.h */

#ifdef printf_symbol
LV2_FUNCTION3(printf, printf_symbol) /* We use LV2_FUNCTION3 to allow calls from non-sce functions if the function is hooked */
#endif

#ifdef sprintf_symbol
LV2_FUNCTION2(sprintf, sprintf_symbol)
#endif

#ifdef snprintf_symbol
LV2_FUNCTION2(snprintf, snprintf_symbol)
#endif

#ifdef strcpy_symbol
LV2_FUNCTION2(strcpy, strcpy_symbol)
#endif

#ifdef strncpy_symbol
LV2_FUNCTION2(strncpy, strncpy_symbol)
#endif

#ifdef strlen_symbol
LV2_FUNCTION2(strlen, strlen_symbol)
#endif

#ifdef strcat_symbol
LV2_FUNCTION2(strcat, strcat_symbol)
#endif

#ifdef strcmp_symbol
LV2_FUNCTION2(strcmp, strcmp_symbol)
#endif

#ifdef strncmp_symbol
LV2_FUNCTION2(strncmp, strncmp_symbol)
#endif

#ifdef strchr_symbol
LV2_FUNCTION2(strchr, strchr_symbol)
#endif

#ifdef strrchr_symbol
LV2_FUNCTION2(strrchr, strrchr_symbol)
#endif

#ifdef memcpy_symbol
LV2_FUNCTION2(memcpy, memcpy_symbol)
#endif

#ifdef memset_symbol
LV2_FUNCTION2(memset, memset_symbol)
#endif

#ifdef memcmp_symbol
LV2_FUNCTION2(memcmp, memcmp_symbol)
#endif

#ifdef memchr_symbol
LV2_FUNCTION2(memchr, memchr_symbol)
#endif

