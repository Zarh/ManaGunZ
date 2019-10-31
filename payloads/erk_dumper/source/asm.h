#ifndef __ASM_H__
#define __ASM_H__

#include "macros.h"

#define GLOBAL(name) \
	.section .text, "ax"; \
	.align 2; \
	.global .name; \
	.type .name, @function; \
.name: \

#endif