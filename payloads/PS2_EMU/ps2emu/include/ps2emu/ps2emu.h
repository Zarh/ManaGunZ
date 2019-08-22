#ifndef __PS2EMU_H__
#define __PS2EMU_H__

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
#define LONGCALL extern "C" __attribute__((longcall))
#else
#define LONGCALL extern __attribute__((longcall))
#endif

#define PS2EMU_EXPORT LONGCALL
#define INLINE inline __attribute__((always_inline))


#define PS2EMU_STATIC_CONTEXT(ret, name, args) asm("" \
"	.section \".text\"\n" \
"	.align 2\n" \
"	.p2align 3,,7\n" \
"	.globl "#name"\n" \
"	.section \".opd\",\"aw\"\n" \
"	.align 3\n" \
#name": \n" \
"	.quad .L."#name",.TOC.@tocbase\n" \
"	.previous\n" \
"	.type   "#name", @function\n" \
".L."#name":\n" \
"	mflr 0\n" \
"	std 0, 32(1)\n" \
"	std 2, 40(1)\n" \
"	clrrdi 2, 2, 32\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_CONTEXT(ret, name, args) asm("" \
"	.section \".text\"\n" \
"	.align 2\n" \
"	.p2align 3,,7\n" \
"	.globl "#name"\n" \
"	.section \".opd\",\"aw\"\n" \
"	.align 3\n" \
#name": \n" \
"	.quad .L."#name",.TOC.@tocbase\n" \
"	.previous\n" \
"	.type   "#name", @function\n" \
".L."#name":\n" \
"	mflr 0\n" \
"	std 0, 32(1)\n" \
"	std 2, 40(1)\n" \
"	bl +4\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -16\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_CALLBACK PS2EMU_CONTEXT

#endif /* __LV2_H__ */




