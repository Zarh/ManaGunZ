@-----------------------------------------------------------@
@ LPC2300 startup code and asm functions
@-----------------------------------------------------------@


.equ UND_Stack_Size,	0	@ Nou used
.equ SVC_Stack_Size,	256	@ Used by ISRs and SWIs
.equ ABT_Stack_Size,	0	@ Nou used
.equ FIQ_Stack_Size,	16	@ Used by FIQ handler
.equ IRQ_Stack_Size,	256	@ Requires ISR nesting level * 28 bytes
.equ USR_Stack_Size,	2048	@ Used by user mode programs
.equ Stack_Size,	(UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
			FIQ_Stack_Size + IRQ_Stack_Size + USR_Stack_Size)

.equ Heap_Size,		0

.equ B_Irq,	0x80
.equ B_Fiq,	0x40
.equ B_Thumb,	0x20
.equ M_USR,	0x10
.equ M_FIQ,	0x11
.equ M_IRQ,	0x12
.equ M_SVC,	0x13
.equ M_ABT,	0x17
.equ M_UND,	0x1B
.equ M_SYS,	0x1F



@-----------------------------------------------------------@
@ Stack area (located in RAM)
@-----------------------------------------------------------@

.section .STACK, "w"
.arm
.align
stack_top:
.space Stack_Size
stack_end:



@-----------------------------------------------------------@
@ Heap area (located in RAM)
@-----------------------------------------------------------@

.section .HEAP, "w"
.align
HeapMem:
.if (Heap_Size > 0)
.space Heap_Size
.endif



@-----------------------------------------------------------@
@ Exception entries (located in ROM, address 0x00000000)
@-----------------------------------------------------------@

.section .VECTOR, "ax"
.arm

	LDR	PC, =reset_handler	@ Reset entry
	LDR	PC, =trap		@ Undef entry
	LDR	PC, =swi_handler	@ SWI entry
	LDR	PC, =trap		@ PAbt entry
	LDR	PC, =trap		@ DAbt entry
	.word	0			@ Check sum (set by flash programmer)
	LDR	PC, =irq_handler	@ IRQ entry
	LDR     PC, =fiq_handler	@ FIQ entry

.pool



@-----------------------------------------------------------@
@ Reset Handler
@-----------------------------------------------------------@

.section .text, "ax"
.arm

reset_handler:

@.extern TargetResetInit
@	LDR	SP, =stack_end    @ Temporary stack for TargetResetInit()
@	LDR	R0, =TargetResetInit
@	MOV	LR, PC
@	BX	R0

@ Setup Stack for each mode
	LDR	R0, =stack_end

@ Enter Undefined Instruction Mode and set its Stack Pointer
	MSR	CPSR_c, #M_UND | B_Irq | B_Fiq
	MOV	SP, R0
	SUB	R0, R0, #UND_Stack_Size

@ Enter Abort Mode and set its Stack Pointer
	MSR	CPSR_c, #M_ABT | B_Irq | B_Fiq
	MOV	SP, R0
	SUB	R0, R0, #ABT_Stack_Size

@ Enter FIQ Mode and set its Stack Pointer
	MSR	CPSR_c, #M_FIQ | B_Irq | B_Fiq
	MOV	SP, R0
	SUB	R0, R0, #FIQ_Stack_Size

@ Enter IRQ Mode and set its Stack Pointer
	MSR	CPSR_c, #M_IRQ | B_Irq | B_Fiq
	MOV	SP, R0
	SUB	R0, R0, #IRQ_Stack_Size

@ Enter Supervisor Mode and set its Stack Pointer
	MSR	CPSR_c, #M_SVC | B_Irq | B_Fiq
	MOV	SP, R0
	SUB	R0, R0, #SVC_Stack_Size

@ Enter User Mode and set its Stack Pointer
	MSR	CPSR_c, #M_USR | B_Irq | B_Fiq
	MOV	SP, R0
	SUB	SL, SP, #USR_Stack_Size

@ Initialize .data section (Copy ROM data)
	LDR	R1, =_sidata
	LDR	R2, =_sdata
	LDR	R3, =_edata
1:	CMP	R2, R3
	LDRLO	R0, [R1], #4
	STRLO	R0, [R2], #4
	BLO	1b

@ Initialize .bss section (Fill with 0)
	MOV	R0, #0
	LDR	R1, =_sbss
	LDR	R2, =_ebss
3:	CMP	R1, R2
	STRLO	R0, [R1], #4
	BLO	3b

@ Start main()
.extern main
	LDR	R0, =main
	MOV	LR, PC
	BX	R0

@ Trap (infinite loop)
trap:
	B	trap

.pool


@-----------------------------------------------------------@
@ IRQ Handler
@ Prologue and Epilog for all ISRs are handled here
@-----------------------------------------------------------@

.equ LPC_BASE_VIC,	0xFFFFF000
.equ VIC_IntSelect,	0x00C
.equ VIC_IntEnable,	0x010
.equ VIC_IntEnClear,	0x014
.equ VIC_Protection,	0x020
.equ VIC_SWPriorityMask,0x024
.equ VIC_VectAddr0,	0x100
.equ VIC_VectPriority0,	0x200
.equ VIC_VectAddr,	0xF00

irq_handler:
	SUB	LR, LR, #4		@ Adjust LR_irq and push it
	STMFD	SP!, {LR}

	MRS	LR, SPSR		@ Save SPSR need to be saved for nested interrupt
	STMFD	SP!, {R0-R3,IP,LR}	@ Push scratch/used registers and SPSR
	LDR	R0, =LPC_BASE_VIC	@ Get the ISR address pointed by VIC_VectAddr
	LDR	R0, [R0, #VIC_VectAddr]
	MSR	CPSR_c, #M_SVC		@ Enter SVC mode and enable Irq and Fiq

	STMFD	SP!, {LR}		@ Call the ISR
	MOV	LR, PC
	BX	R0
	LDMIA	SP!, {LR}

	MSR	CPSR_c, #M_IRQ | B_Irq	@ Enter IRQ mode and disable Irq
	LDMIA	SP!, {R0-R3,IP,LR}	@ Restore scratch/used registers and SPSR
	MSR	SPSR_cxsf, LR		@ Restore SPSR_irq

	LDR	LR, =LPC_BASE_VIC	@ Issue EOI command to the VIC
	STR	LR, [LR, #VIC_VectAddr]

	LDMIA	SP!, {PC}^		@ Reruen from the IRQ handler

.pool


@-----------------------------------------------------------@
@ FIQ Handler
@ FIQ routine is typically written in assembler
@-----------------------------------------------------------@

fiq_handler:
	SUB	LR, LR, #4		@ Adjust LR_fiq

	@ Put the FIQ service here

	MOVS	PC, LR			@ Return from FIQ



@-----------------------------------------------------------@
@ SWI Service (declared in interrupt.h)
@-----------------------------------------------------------@

swi_handler:
	MRS	IP, SPSR
	TST	IP, #B_Thumb		@ Check caller's state, ARM or Thumb
	LDRNEH	IP, [LR, #-2]		@ Get swi instruction code (on Thumb state)
	LDREQ	IP, [LR, #-4]		@ Get swi instruction code (on ARM state)
	AND	IP, #0xFF		@ Get swi comment field (lower 8 bit)
	CMP	IP, #7			@ Check range
	LDRLO	PC, [PC, IP, LSL #2]	@ Jump to each service function when code is valid
	MOVS	PC, LR			@ Otherwise return
	.word	irq_disable	@ 0 Disable IRQ
	.word	irq_enable	@ 1 Enable IRQ
	.word	clear_vect	@ 2 Clear ISRs
	.word	reg_irq		@ 3 Register vector address for IRQ
	.word	sel_fiq		@ 4 Select FIQ interrupt
	.word	load_fiq	@ 5 Load FIQ shadow regs from memory
	.word	store_fiq	@ 6 Store FIQ shadow regs to memory

irq_disable:
	MRS	R0, SPSR
	ORR	R0, R0, #B_Irq | B_Fiq
	MSR	SPSR_c, R0
	MOVS	PC, LR

irq_enable:
	MRS	R0, SPSR
	BIC	R0, R0, #B_Irq | B_Fiq
	MSR	SPSR_c, R0
	MOVS	PC, LR

clear_vect:
	LDR	IP, =LPC_BASE_VIC
	MVN	R0, #0				@ Disable all interrupts
	STR	R0, [IP, #VIC_IntEnClear]
	MOV	R0, R0, LSR #16			@ Unmask all interrupt levels
	STR	R0, [IP, #VIC_SWPriorityMask]
	MOV	R0, #1				@ Enable protection
	STR	R0, [IP, #VIC_Protection]
	STR	R0, [IP, #VIC_VectAddr]		@ Issule EOI command
	MOVS	PC, LR

reg_irq:
	CMP	R0, #32				@ Range check
	MOVCSS	PC, LR
	LDR	IP, =(LPC_BASE_VIC+VIC_VectAddr0)
	STR	R1, [IP, R0, LSL #2]		@ Set VICVectVectAddr<n>
	LDR	IP, =(LPC_BASE_VIC+VIC_VectPriority0)
	STR	R2, [IP, R0, LSL #2]		@ Set VICVectPriority<n>
	MOV	R1, #1
	MOV	R1, R1, LSL R0
	LDR	IP, =LPC_BASE_VIC
	LDR	R2, [IP, #VIC_IntSelect]	@ Clear corresponding bit in the VICIntSelect
	BIC	R2, R1
	STR	R2, [IP, #VIC_IntSelect]
	STR	R1, [IP, #VIC_IntEnable]	@ Enable corresponding interrupt
	MOVS	PC, LR

sel_fiq:
	CMP	R0, #32				@ Range check
	MOVCSS	PC, LR
	LDR	IP, =LPC_BASE_VIC
	MOV	R1, #1				@ Set corresponding bit in the VICIntSelect
	MOV	R1, R1, LSL R0
	STR	R1, [IP, #VIC_IntSelect]
	STR	R1, [IP, #VIC_IntEnable]	@ Enable corresponding interrupt
	MOVS	PC, LR

load_fiq:
	MSR	CPSR_c, #M_FIQ | B_Fiq
	LDMIA	R0!, {R8-R12}			@ Load the memory to five shadow registers
	MSR	CPSR_c, #M_SVC
	MOVS	PC, LR

store_fiq:
	MSR	CPSR_c, #M_FIQ | B_Fiq
	STMIA	R0!, {R8-R12}			@ Store five shadow registers to the memory
	MSR	CPSR_c, #M_SVC
	MOVS	PC, LR

.pool


@-----------------------------------------------------------@
@ Fast Unaligned Block Copy (used in disk functions)
@-----------------------------------------------------------@

@ void Copy_un2al (DWORD *dst, const BYTE *src, int count);
.global Copy_un2al
.type Copy_un2al, %function
.func Copy_un2al
Copy_un2al:
	STMFD	SP!, {R4-R8}
	ANDS	IP, R1, #3
	BEQ	lb_align

	BIC	R1, #3
	MOV	IP, IP, LSL #3
	RSB	R8, IP, #32
	LDMIA	R1!, {R7}
1:	MOV	R3, R7
	LDMIA	R1!, {R4-R7}
	MOV	R3, R3, LSR IP
	ORR	R3, R3, R4, LSL R8
	MOV	R4, R4, LSR IP
	ORR	R4, R4, R5, LSL R8
	MOV	R5, R5, LSR IP
	ORR	R5, R5, R6, LSL R8
	MOV	R6, R6, LSR IP
	ORR	R6, R6, R7, LSL R8
	SUBS	R2, R2, #16
	STMIA	R0!, {R3-R6}
	BNE	1b
	LDMFD	SP!, {R4-R8}
	BX	LR

lb_align:
	LDMIA	R1!, {R3-R6}
	SUBS	R2, R2, #16
	STMIA	R0!, {R3-R6}
	BNE	lb_align
	LDMFD	SP!, {R4-R8}
	BX	LR
.endfunc


@ void Copy_al2un (BYTE *dst, const DWORD *src, int count);
.global Copy_al2un
.type Copy_al2un, %function
.func Copy_al2un
Copy_al2un:
	STMFD	SP!, {R4-R8}
	ANDS	IP, R0, #3
	BEQ	sb_align

	MOV	IP, IP, LSL #3
	RSB	R8, IP, #32

	LDMIA	R1!, {R4-R7}
1:	STRB	R4, [R0], #1
	MOV	R4, R4, LSR #8
	TST	R0, #3
	BNE	1b
	ORR	R4, R4, R5, LSL IP
	MOV	R5, R5, LSR R8
	ORR	R5, R5, R6, LSL IP
	MOV	R6, R6, LSR R8
	ORR	R6, R6, R7, LSL IP
	SUBS	R2, R2, #16
	STMIA	R0!, {R4-R6}

2:	MOV	R3, R7
	LDMIA	R1!, {R4-R7}
	MOV	R3, R3, LSR R8
	ORR	R3, R3, R4, LSL IP
	MOV	R4, R4, LSR R8
	ORR	R4, R4, R5, LSL IP
	MOV	R5, R5, LSR R8
	ORR	R5, R5, R6, LSL IP
	MOV	R6, R6, LSR R8
	ORR	R6, R6, R7, LSL IP
	SUBS	R2, R2, #16
	STMIA	R0!, {R3-R6}
	BNE	2b

	MOV	R7, R7, LSR R8
3:	SUBS	IP, IP, #8
	STRB	R7, [R0], #1
	MOV	R7, R7, LSR #8
	BNE	3b

	LDMFD	SP!, {R4-R8}
	BX	LR

sb_align:
	LDMIA	R1!, {R3-R6}
	SUBS	R2, #16
	STMIA	R0!, {R3-R6}
	BNE	sb_align
	LDMFD	SP!, {R4-R8}
	BX	LR
.endfunc


.end

