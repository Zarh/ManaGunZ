/* Stub functions for SWI service */

#include "interrupt.h"


/* Disable/Enable Irq */
void IrqDisable (void)
{
	asm ("swi 0\n");
}

void IrqEnable (void)
{
	asm ("swi 1\n");
}


/* Unregister all ISRs */
void ClearVector (void)
{
	asm ("swi 2\n");
}


/* Register an ISR */
void RegisterIrq (
	int irq,
	void(*isr)(void),
	int pri
)
{
	asm (
	"@ MOV R0, %0\n"
	"@ MOV R1, %1\n"
	"@ MOV R2, %2\n"
	"swi 3\n" : : "r" (irq), "r" (isr), "r" (pri)
	);
}


/* Switch an interrtupt source as FIQ */
void SelectFiq (
	int irq
)
{
	asm (
	"@ MOV R0, %0\n"
	"swi 4\n" : : "r" (irq)
	);
}


/* Load shadow regs R8-R12 from memory */
void LoadFiqRegs (
	long *regs
)
{
	asm (
	"@ MOV R0, %0\n"
	"swi 5\n" : : "r" (regs)
	);
}


/* Store shadow regs R8-R12 to memory */
void StoreFiqRegs (
	long *regs
)
{
	asm (
	"@ MOV R0, %0\n"
	"swi 6\n" : : "r" (regs)
	);
}

