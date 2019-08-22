#ifndef __PS2EMU_PATCH_H__
#define __PS2EMU_PATCH_H__

#include <ps2emu/ps2emu.h>
#include <ps2emu/symbols.h>

#define MAKE_JUMP(addr, to) *(uint32_t *)(addr) = (0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2)
#define MAKE_CALL(addr, to) *(uint32_t *)(addr) = (0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xffffff) << 2) | 1

#define MAKE_JUMP_VALUE(addr, to) ((0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2))
#define MAKE_CALL_VALUE(addr, to) ((0x12 << 26) | ((((to-(uint64_t)(addr))>>2)&0xFFFFFF) << 2)) | 1

#define BLR	0x4E800020
#define BLRL	0x4E800021
#define BCTR	0x4E800420
#define BCTRL	0x4E800421
#define NOP	0x60000000

#define MFSPR(SPR, RS) ((31 << 26) | (RS << 21) | (SPR << 16) | (339 << 1))
#define MFLR(RS) MFSPR(8, RS)
#define MFCTR(RS) MFSPR(9, RS)

#define MTSPR(SPR, RS) ((31 << 26) | (RS << 21) | (SPR << 16) | (467 << 1))
#define MTLR(RS) MTSPR(8, RS)
#define MTCTR(RS) MTSPR(9, RS)

#define OR(RA, RS, RB) (31 << 26) | (RS << 21) | (RA << 16) | (RB << 11) | (444 << 1)
#define ORI(RA, RS, UI) (24 << 26) | (RS << 21) | (RA << 16) | (UI&0xFFFF)
#define ORIS(RA, RS, UI) (25 << 26) | (RS << 21) | (RA << 16) | (UI&0xFFFF)
#define MR(RS, RA) OR(RS, RA, RA)

#define ADDI(RT, RA, SI) (14 << 26) | (RT << 21) | (RA << 16) | (SI&0xFFFF)
#define LI(RA, UI) ADDI(RA, 0, UI)

#define ADDIS(RT, RA, SI) (15 << 26) | (RT << 21) | (RA << 16) | (SI&0xFFFF)
#define LIS(RA, UI) ADDIS(RA, 0, UI)

#define LD(RT, DS, RA) (58 << 26) | (RT << 21) | (RA << 16) | ((DS >> 2) << 2)
#define STD(RS, DS, RA) (62 << 26) | (RS << 21) | (RA << 16) | ((DS >> 2) << 2)

#define STW(RS, D, RA) (36 << 26) | (RS << 21) | (RA << 16) | D

/* DO NOT CHANGE */
#define DO_POSTCALL		0xFFFFC561
#define DO_POSTCALL_64		0xFFFFFFFFFFFFC561

#define PS2EMU_PATCHED_FUNCTION	PS2EMU_CONTEXT

#define PS2EMU_HOOKED_FUNCTION(ret, name, args) asm("" \
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
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_0(ret, name, args) asm("" \
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
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	std 2, 40(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -44\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_1(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -48\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_2(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -52\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_3(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -56\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_4(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -60\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_5(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -64\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_6(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -68\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_7(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	std 9, 96(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	ld 9, 96(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -72\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_8(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	std 9, 96(1)\n" \
"	std 10, 104(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	ld 9, 96(1)\n" \
"	ld 10, 104(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -76\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_SUCCESS_0(ret, name, args) asm("" \
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
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	cmpwi 3, 0\n" \
"	bne 1f\n" \
"	std 2, 40(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -44\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"1:\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_SUCCESS_1(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	cmpwi 3, 0\n" \
"	bne 1f\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -48\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"1:\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_SUCCESS_2(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	cmpwi 3, 0\n" \
"	bne 1f\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -52\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"1:\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_SUCCESS_3(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	cmpwi 3, 0\n" \
"	bne 1f\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -56\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"1:\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_SUCCESS_4(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	cmpwi 3, 0\n" \
"	bne 1f\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -60\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"1:\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_SUCCESS_5(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	cmpwi 3, 0\n" \
"	bne 1f\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -64\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"1:\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_SUCCESS_6(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	cmpwi 3, 0\n" \
"	bne 1f\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -68\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"1:\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_SUCCESS_7(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	std 9, 96(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	cmpwi 3, 0\n" \
"	bne 1f\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	ld 9, 96(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -72\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"1:\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_PRECALL_SUCCESS_8(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	std 9, 96(1)\n" \
"	std 10, 104(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	cmpwi 3, 0\n" \
"	bne 1f\n" \
"	std 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	ld 9, 96(1)\n" \
"	ld 10, 104(1)\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -76\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"1:\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_POSTCALL_0(ret, name, args) asm("" \
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
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_POSTCALL_1(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_POSTCALL_2(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_POSTCALL_3(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_POSTCALL_4(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_POSTCALL_5(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_POSTCALL_6(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_POSTCALL_7(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	std 9, 96(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	ld 9, 96(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_POSTCALL_8(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	std 9, 96(1)\n" \
"	std 10, 104(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	ld 9, 96(1)\n" \
"	ld 10, 104(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_0(ret, name, args) asm("" \
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
"	extsw 4, 3\n" \
"	cmpwi 4, -15007\n" \
"	bne +40\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_1(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	extsw 4, 3\n" \
"	cmpwi 4, -15007\n" \
"	bne +44\n" \
"	ld 3, 48(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_2(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	extsw 4, 3\n" \
"	cmpwi 4, -15007\n" \
"	bne +48\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_3(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	extsw 4, 3\n" \
"	cmpwi 4, -15007\n" \
"	bne +52\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_4(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	extsw 4, 3\n" \
"	cmpwi 4, -15007\n" \
"	bne +56\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_5(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	extsw 4, 3\n" \
"	cmpwi 4, -15007\n" \
"	bne +60\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_6(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	extsw 4, 3\n" \
"	cmpwi 4, -15007\n" \
"	bne +64\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_7(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	std 9, 96(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	extsw 4, 3\n" \
"	cmpwi 4, -15007\n" \
"	bne +68\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	ld 9, 96(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

#define PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_8(ret, name, args) asm("" \
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
"	std 3, 48(1)\n" \
"	std 4, 56(1)\n" \
"	std 5, 64(1)\n" \
"	std 6, 72(1)\n" \
"	std 7, 80(1)\n" \
"	std 8, 88(1)\n" \
"	std 9, 96(1)\n" \
"	std 10, 104(1)\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	extsw 4, 3\n" \
"	cmpwi 4, -15007\n" \
"	bne +72\n" \
"	ld 3, 48(1)\n" \
"	ld 4, 56(1)\n" \
"	ld 5, 64(1)\n" \
"	ld 6, 72(1)\n" \
"	ld 7, 80(1)\n" \
"	ld 8, 88(1)\n" \
"	ld 9, 96(1)\n" \
"	ld 10, 104(1)\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

typedef struct function_descriptor 
{
	void	*addr;
	void    *toc;	
} f_desc_t;

void 	clear_icache(void *addr, uint64_t size);
void 	*get_call_address(int level);
void	*get_patched_func_call_address(void);

static INLINE void *get_function_ptr(uint64_t addr, f_desc_t *f)
{
	f->addr = (void *)addr;
	f->toc = (void *)TOC;
	return f;
}

static INLINE void make_long_jump(void *addr, uint64_t to)
{
	uint32_t *ins = (uint32_t *)addr;
	
	ins[0] = LIS(0, ((to>>16)&0xFFFF));
	ins[1] = ORI(0, 0, (to&0xFFFF));
	ins[2] = MTCTR(0);
	ins[3] = BCTR;
}

static INLINE void make_long_call(void *addr, uint64_t to)
{
	uint32_t *ins = (uint32_t *)addr;
	
	ins[0] = LIS(0, ((to>>16)&0xFFFF));
	ins[1] = ORI(0, 0, (to&0xFFFF));
	ins[2] = MTCTR(0);
	ins[3] = BCTRL;
}

static INLINE void make_long_jump_with_inst(void *addr, uint64_t to, uint32_t *inst)
{
	uint32_t *ins = (uint32_t *)addr;
		
	ins[0] = LIS(0, ((to>>16)&0xFFFF));
	ins[1] = ORI(0, 0, (to&0xFFFF));
	ins[2] = MTCTR(0);
	
	for (int i = 0, j = 3; i < 4; i++, j++)
	{
		if (inst[i] == MFLR(0))
		{
			ins[j] = LIS(0, (((uint64_t)(ins+9)>>16)&0xFFFF));
			j++;
			ins[j] = ORI(0, 0, ((uint64_t)(ins+9)&0xFFFF));
		}
		else
		{			
			ins[j] = inst[i];
		}
		
		if (i == 3 && j == 6)
		{
			ins[7] = NOP;
		}
	}
		
	ins[8] = BCTR;
}

static INLINE void make_long_jump_with_inst2(void *addr, uint64_t to, uint32_t *inst)
{
	uint32_t *ins = (uint32_t *)addr;
		
	ins[0] = LIS(0, ((to>>16)&0xFFFF));
	ins[1] = ORI(0, 0, (to&0xFFFF));
	ins[2] = MTCTR(0);
	
	for (int i = 0, j = 3; i < 4; i++, j++)
	{
		ins[j] = inst[i];		
	}
		
	ins[7] = BCTR;
}

static INLINE void make_long_call_with_inst(void *addr, uint64_t to, uint32_t *inst)
{
	uint32_t *ins = (uint32_t *)addr;
	
	ins[0] = LIS(0, ((to>>16)&0xFFFF));
	ins[1] = ORI(0, 0, (to&0xFFFF));
	ins[2] = MTCTR(0);
	
	for (int i = 0, j = 3; i < 4; i++, j++)
	{
		if (inst[i] == MFLR(0))
		{
			ins[j] = LIS(0, (((uint64_t)(ins+9)>>16)&0xFFFF));
			j++;
			ins[j] = ORI(0, 0, ((uint64_t)(ins+9)&0xFFFF));
		}
		else if (inst[i] == MFLR(11))
		{			
			ins[j] = LIS(11, (((uint64_t)(ins+9)>>16)&0xFFFF));
			j++;
			ins[j] = ORI(11, 11, ((uint64_t)(ins+9)&0xFFFF));
		}
		else
		{			
			ins[j] = inst[i];
		}
		
		if (i == 3 && j == 6)
		{
			ins[7] = NOP;
		}
	}
	
	ins[8] = BCTRL;
}

static INLINE void change_function(uint64_t func_addr, void *newfunc)
{
	f_desc_t *f = (f_desc_t *)newfunc;
	make_long_jump((void *)func_addr, (uint64_t)f->addr);
	clear_icache((void *)func_addr, 16);
}

static INLINE void *hook_function(uint64_t func_addr, void *newfunc, f_desc_t *f)
{
	f_desc_t *g = (f_desc_t *)newfunc;
	uint32_t *inst = (uint32_t *)func_addr;
	uint32_t *orig_call = &((uint32_t *)g->addr)[19]; // WARNING: relies on HOOKED_FUNCTION not being changed
		
	make_long_jump_with_inst2(&orig_call[0], func_addr+16, inst);
	clear_icache(orig_call, 36);
	change_function(func_addr, newfunc);
	f->addr = orig_call;
	f->toc = (void *)TOC;
	return f;
}

static INLINE void hook_function_with_precall(uint64_t func_addr, void *newfunc, unsigned int nparams)
{
	if (nparams > 8)
		return;
	
	f_desc_t *f = (f_desc_t *)newfunc;
	uint32_t *inst = (uint32_t *)func_addr;
	uint32_t *orig_call = &((uint32_t *)f->addr)[2+nparams]; // WARNING: relies on HOOKED_FUNCTION_PRECALL_N not being changed	
	
	make_long_call_with_inst(&orig_call[0], func_addr+16, inst);
	clear_icache(orig_call, 36);
	change_function(func_addr, newfunc);
}

static INLINE void hook_function_on_precall_success(uint64_t func_addr, void *newfunc, unsigned int nparams)
{
	hook_function_with_precall(func_addr, newfunc, nparams);
}

static INLINE void hook_function_with_postcall(uint64_t func_addr, void *newfunc, unsigned int nparams)
{
	if (nparams > 8)
		return;
	
	f_desc_t *f = (f_desc_t *)newfunc;
	uint32_t *inst = (uint32_t *)func_addr;
	uint32_t *orig_call = &((uint32_t *)f->addr)[16+(nparams*2)]; // WARNING: relies on HOOKED_FUNCTION_POST_CALL_N not being changed	
	
	make_long_call_with_inst(&orig_call[0], func_addr+16, inst);
	clear_icache(orig_call, 36);
	change_function(func_addr, newfunc);
}

static INLINE void hook_function_with_cond_postcall(uint64_t func_addr, void *newfunc, unsigned int nparams)
{
	if (nparams > 8)
		return;
	
	f_desc_t *f = (f_desc_t *)newfunc;
	uint32_t *inst = (uint32_t *)func_addr;
	uint32_t *orig_call = &((uint32_t *)f->addr)[19+(nparams*2)]; // WARNING: relies on HOOKED_FUNCTION_COND_POST_CALL_N not being changed	
	
	make_long_call_with_inst(&orig_call[0], func_addr+16, inst);
	clear_icache(orig_call, 36);
	change_function(func_addr, newfunc);
}

/* Only to call pre/postcall hooked functions, not normal hooked or patched */
uint64_t call_hooked_function(void *func, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6, uint64_t a7);

#define call_hooked_function_0(func) call_hooked_function(func, 0, 0, 0, 0, 0, 0, 0)
#define call_hooked_function_1(func, a1) call_hooked_function(func, a1, 0, 0, 0, 0, 0, 0)
#define call_hooked_function_2(func, a1, a2) call_hooked_function(func, a1, a2, 0, 0, 0, 0, 0)
#define call_hooked_function_3(func, a1, a2, a3) call_hooked_function(func, a1, a2, a3, 0, 0, 0, 0)
#define call_hooked_function_4(func, a1, a2, a3, a4) call_hooked_function(func, a1, a2, a3, a4, 0, 0, 0)
#define call_hooked_function_5(func, a1, a2, a3, a4, a5) call_hooked_function(func, a1, a2, a3, a4, a5, 0, 0)
#define call_hooked_function_6(func, a1, a2, a3, a4, a5, a6) call_hooked_function(func, a1, a2, a3, a4, a5, a6, 0)
#define call_hooked_function_7(func, a1, a2, a3, a4, a5, a6, a7) call_hooked_function(func, a1, a2, a3, a4, a5, a6, a7)


#endif /* __PS2EMU_PATCH_H__ */

