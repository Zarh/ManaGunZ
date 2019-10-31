#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

#include "macros.h"

#define INLINE inline __attribute__ ((always_inline))
#define NO_INLINE __attribute__ ((noinline))

#define LONGCALL extern __attribute__ ((longcall))

#define countof(x) (sizeof(x) / sizeof(x[0]))

#endif