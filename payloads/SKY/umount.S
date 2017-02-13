/*
 * umount.S -- umount syscall 838 patch
 *
 * Copyright (C) (Estwald)
 * Copyright (C) (D_Skywalk)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 ********************************************************************************
 */

#include "firmware_symbols.h"

#define ABS(target) ((target) - (BASE2) - .)

// Dynamic macros to load a label into a register
#define MEM_BASE(dest) \
    li dest, 1; \
    rldicr dest, dest, 63, 0;
#define LOAD_LABEL(base, dest, source, address) \
    oris    dest, source, ((base) + (address))@h; \
    ori    dest, dest, ((base) + (address))@l;
#define LOAD_LABEL2(dest, source, address) \
    LOAD_LABEL(BASE2, dest, source, address)
#define LOADI_LABEL2(dest, address) \
    LOAD_LABEL2(dest, dest, address)

#define PATHSTR_LEN    0x9

.org 0

umount_sys_patch: // 0x1B509C
    std      %r0, 0x110(%sp)
    std      %r3, 0xD0(%sp)
    std      %r4, 0xD8(%sp)
    std      %r5, 0xE0(%sp)
    std      %r29, 0xE8(%sp)
    std      %r31, 0xF8(%sp)

    MEM_BASE(%r31)
    LOAD_LABEL2(%r4, %r31, aDev_bdvd)

    oris   %r29, %r31, 0x7E    // 0x7EF000 -> backup of /dev_bdvd
    ori    %r29, %r29, 0xF000

    li      %r5, PATHSTR_LEN
    mflr    %r31
    bl      ABS(strncmp)
    cmpldi  %r3, 0
    bne     umount_normally
    ld      %r3, 0(%r29)
    cmpldi  %r3, 0
    beq     umount_normally
    li      %r0, 0
    std     %r0, 0(%r29)
    ld      %r4, 8(%r29)
    lwz     %r5, 16(%r29)
    stw     %r5, 0(%r4)
    addi    %r4, %r29, 0x20
    lwz     %r5, 20(%r29)
    bl       ABS(memcpy)

umount_normally:
    mtlr    %r31
    ld      %r0, 0x110(%sp)
    ld      %r3, 0xD0(%sp)
    ld      %r4, 0xD8(%sp)
    ld      %r5, 0xE0(%sp)
    ld      %r29, 0xE8(%sp)
    ld      %r31, 0xF8(%sp)
    sync
    blr

aDev_bdvd:    .string    "/dev_bdvd"

.org 160
