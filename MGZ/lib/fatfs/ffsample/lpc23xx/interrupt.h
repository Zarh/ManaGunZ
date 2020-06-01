#ifndef __INTERRUPT_H
#define __INTERRUPT_H


/* Interrupt related service functions */

void IrqDisable (void);				/* Disable all IRQ */
void IrqEnable (void); 				/* Enable all IRQ */
void ClearVector (void);			/* Unregister all ISRs */
void RegisterIrq (int irq, void(*isr)(void), int pri);	/* Register an ISR as IRQ */
void SelectFiq (int irq);			/* Switch an interrtupt source as FIQ */
void LoadFiqRegs (long *regs);		/* Load shadow regs R8-R12 from memory */
void StoreFiqRegs (long *regs);		/* Store shadow regs R8-R12 to memory */



/* LPC23xx interrupt number */

#define	WDT_IRQn		0
#define RES1_IRQn		1
#define ARM_CORE0_IRQn	2
#define	ARM_CORE1_IRQn	3
#define	TIMER0_IRQn		4
#define TIMER1_IRQn		5
#define UART0_IRQn		6
#define	UART1_IRQn		7
#define	PWM0_1_IRQn		8
#define I2C0_IRQn		9
#define SPI0_IRQn		10
#define SSP0_IRQn		10
#define	SSP1_IRQn		11
#define	PLL_IRQn		12
#define RTC_IRQn		13
#define EINT0_IRQn		14
#define EINT1_IRQn		15
#define EINT2_IRQn		16
#define EINT3_IRQn		17
#define	ADC0_IRQn		18
#define I2C1_IRQn		19
#define BOD_IRQn		20
#define EMAC_IRQn		21
#define USB_IRQn		22
#define CAN_IRQn		23
#define MCI_IRQn		24
#define GPDMA_IRQn		25
#define TIMER2_IRQn		26
#define TIMER3_IRQn		27
#define UART2_IRQn		28
#define UART3_IRQn		29
#define I2C2_IRQn		30
#define I2S_IRQn		31

#define PRI_LOWEST		15
#define PRI_HIGHEST		0


#endif /* __INTERRUPT_H */
