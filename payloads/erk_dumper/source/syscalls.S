#include "asm.h"
#include "symbols.h"

.section .text
.global sys_dbg_get_process_list
.type sys_dbg_get_process_list, @function
sys_dbg_get_process_list:
#if 1
	stdu %r1, -0xF0(%r1)
	mflr %r0
	std %r30, 0xE0(%r1)
	mr %r30, %r3
	li %r3, 0
	std %r27, 0xC8(%r1)
	std %r28, 0xD0(%r1)
	std %r22, 0xA0(%r1)
	std %r23, 0xA8(%r1)
	std %r24, 0xB0(%r1)
	std %r25, 0xB8(%r1)
	std %r26, 0xC0(%r1)
	std %r29, 0xD8(%r1)
	std %r31, 0xE8(%r1)
	std %r0, 0x100(%r1)
	mr %r28, %r4
	mr %r27, %r5
	bl extend_kstack
	mfsprg0 %r9
	ld %r3, 0x48(%r9)
	bl disable_interrupts
	bl get_current_proc_locked
	mr %r29, %r3
	mfsprg0 %r9
	ld %r3, 0x48(%r9)
	lis %r31, -0x7FFF
	bl enable_external_interrupt
	li %r0, 2
	lwz %r9, 0x28(%r29)
	addi %r3, %r1, 0x70
	ld %r4, -0x5BE8(%r2) // +0x1FC8
	addi %r5, %r1, 0x80
	addi %r6, %r1, 0x88
	stw %r9, 0x70(%r1)
	std %r0, 0x88(%r1)
	std %r0, 0x80(%r1)
	bl access_control_engine_check_capability
	clrlwi %r3, %r3, 24
	ori %r31, %r31, 3
	cmpwi cr7, %r3, 0
	bne cr7, loc_289164

loc_289128:
	ld %r0, 0x100(%r1)
	extsw %r3, %r31
	ld %r22, 0xA0(%r1)
	ld %r23, 0xA8(%r1)
	mtlr %r0
	ld %r24, 0xB0(%r1)
	ld %r25, 0xB8(%r1)
	ld %r26, 0xC0(%r1)
	ld %r27, 0xC8(%r1)
	ld %r28, 0xD0(%r1)
	ld %r29, 0xD8(%r1)
	ld %r30, 0xE0(%r1)
	ld %r31, 0xE8(%r1)
	addi %r1, %r1, 0xF0
	blr
# ---------------------------------------------------------------------------

loc_289164:
	cmpdi cr7, %r30, 0
	bne cr7, loc_289178

loc_28916C:
	lis %r31, -0x7FFF
	ori %r31, %r31, 0x409
	b loc_289128
# ---------------------------------------------------------------------------

loc_289178:
	cmpdi cr7, %r28, 0
	beq cr7, loc_28916C
	cmpdi cr7, %r27, 0
	beq cr7, loc_28916C
	mr %r3, %r28
	addi %r4, %r1, 0x90
	li %r5, 8
	bl copy_from_user_copyin
	cmpwi cr7, %r3, 0
	mr %r31, %r3
	bne cr7, loc_289128
	ld %r23, 0x90(%r1)
	cmpdi cr7, %r23, 0
	beq+ cr7, loc_28916C
	sldi %r3, %r23, 2
	li %r4, 0xD
	li %r5, 0
	lis %r31, -0x7FFF
	bl alloc
	cmpdi %r3, 0
	mr %r25, %r3
	ori %r31, %r31, 0x408
	beq loc_289128
	ld %r9, -0x5920(%r2) // +0x1FD0
	ld %r29, 0(%r9)
	cmpdi cr7, %r29, 0
	beq- cr7, loc_2892F4
	li %r4, 1
	mr %r3, %r29
	bl sub_8000000000011470
	li %r4, 0xD
	extsw %r31, %r3
	mr %r24, %r3
	li %r5, 0
	sldi %r3, %r31, 4
	std %r31, 0x78(%r1)
	bl alloc
	cmpdi %r3, 0
	mr %r26, %r3
	beq- loc_28938C
	mr %r3, %r29
	mr %r6, %r31
	li %r4, 1
	mr %r5, %r26
	bl sub_80000000000114E8
	cmpwi cr7, %r3, 0
	beq- cr7, loc_289368
	cmpwi cr7, %r24, 0
	mr %r31, %r25
	li %r22, 0
	li %r29, 0
	ble cr7, loc_289284

loc_289248:
	lwzx %r3, %r29, %r26
	bl sub_8000000000003B38
	cmpdi cr6, %r23, 0
	clrlwi %r3, %r3, 24
	cmpwi cr7, %r3, 0
	beq cr7, loc_289358
	addi %r23, %r23, -1
	beq cr6, loc_289308
	lwzx %r0, %r29, %r26
	stw %r0, 0(%r31)
	addi %r31, %r31, 4

loc_289274:
	addi %r22, %r22, 1
	addi %r29, %r29, 0x10
	cmpw cr7, %r24, %r22
	bne cr7, loc_289248

loc_289284:
	mr %r3, %r26
	li %r4, 0xD
	bl dealloc
	ld %r5, 0x78(%r1)
	mr %r4, %r30
	sldi %r5, %r5, 2
	mr %r3, %r25
	bl copy_to_user_copyout
	cmpwi cr7, %r3, 0
	mr %r31, %r3
	bne cr7, loc_2893A4
	mr %r3, %r25
	li %r4, 0xD
	addi %r30, %r1, 0x78
	bl dealloc
	mr %r4, %r27
	mr %r3, %r30
	li %r5, 8
	bl copy_to_user_copyout
	cmpwi cr7, %r3, 0
	mr %r31, %r3
	bne cr7, loc_289128
	mr %r3, %r30
	mr %r4, %r28
	li %r5, 8
	bl copy_to_user_copyout
	mr %r31, %r3
	b loc_289128
# ---------------------------------------------------------------------------

loc_2892F4:
	lis %r31, -0x7FFF
	li %r4, 0xD
	ori %r31, %r31, 0xD
	bl dealloc
	b loc_289128
# ---------------------------------------------------------------------------

loc_289308:
	mr %r3, %r26
	li %r4, 0xD
	bl dealloc
	ld %r5, 0x90(%r1)
	mr %r4, %r30
	sldi %r5, %r5, 2
	mr %r3, %r25
	bl copy_to_user_copyout
	cmpwi cr7, %r3, 0
	mr %r31, %r3
	bne cr7, loc_2893A4
	mr %r3, %r25
	li %r4, 0xD
	bl dealloc
	mr %r4, %r27
	addi %r3, %r1, 0x78
	li %r5, 8
	bl copy_to_user_copyout
	mr %r31, %r3
	b loc_289128
# ---------------------------------------------------------------------------

loc_289358:
	ld %r9, 0x78(%r1)
	addi %r9, %r9, -1
	std %r9, 0x78(%r1)
	b loc_289274
# ---------------------------------------------------------------------------

loc_289368:
	mr %r3, %r26
	li %r4, 0xD
	lis %r31, -0x7FFF
	bl dealloc
	mr %r3, %r25
	li %r4, 0xD
	ori %r31, %r31, 0xD
	bl dealloc
	b loc_289128
# ---------------------------------------------------------------------------

loc_28938C:
	lis %r31, -0x7FFF
	mr %r3, %r25
	li %r4, 0xD
	ori %r31, %r31, 0x408
	bl dealloc
	b loc_289128
# ---------------------------------------------------------------------------

loc_2893A4:
	mr %r3, %r25
	li %r4, 0xD
	bl dealloc
	b loc_289128
#else
	lis %r3, -0x7FFF
	ori %r3, %r3, 3
	blr
#endif