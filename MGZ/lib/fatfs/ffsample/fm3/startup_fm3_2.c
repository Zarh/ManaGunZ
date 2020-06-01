/*--------------------------------------------------------------/
/  Startup Module for Fujitsu MB9BF Microcontrollers            /
/                                                               /
/ * This module defines vector table, startup code, default     /
/   exception handlers, main stack and miscellanous functions.  /
/ * This file is a non-copyrighted public domain software.      /
/--------------------------------------------------------------*/

#include "FM3_type2.h"


#define STACK_SIZE	4096		/* Size of Main stack (must be multiple of 8) */

#define	CLKMO		4000000		/* Main oscillator frequency */
#define PLL_K		1			/* PLL reference divider K */
#define PLL_M		2			/* PLL multiplier M */
#define PLL_N		36			/* PLL multiplier N */
#define	CLKPLL		144000000	/* Expected CLKPLL frequency = CLKMO / PLL_K * PLL_N */
#define HCLK		144000000	/* AHB clock frequency */
#define CLKAPB0		72000000	/* APB0 clock frequency */
#define CLKAPB1		72000000	/* APB1 clock frequency */
#define CLKAPB2		72000000	/* APB2 clock frequency */


#if CLKPLL != CLKMO / PLL_K * PLL_N
#error CLKPLL does not match calcurated value
#endif
#if CLKMO / PLL_K < 4000000 || CLKMO / PLL_K > 16000000
#error PLL input frequency is out of range (wrong PLL_K or CLKMO)
#endif
#if ((CLKPLL * PLL_M) < 200000000 || (CLKPLL * PLL_M) > 300000000)
#error PLL oscillation frequency is out of range (wrong PLL_M)
#endif
#if CLKPLL / HCLK * HCLK != CLKPLL
#error Wrong HCLK setting
#endif
#if CLKAPB0 > 72000000 || HCLK / CLKAPB0 * CLKAPB0 != HCLK
#error Wrong CLKAPB0 setting
#endif
#if CLKAPB1 > 72000000 || HCLK / CLKAPB1 * CLKAPB1 != HCLK
#error Wrong CLKAPB1 setting
#endif
#if CLKAPB2 > 72000000 || HCLK / CLKAPB2 * CLKAPB2 != HCLK
#error Wrong CLKAPB2 setting
#endif



/*--------------------------------------------------------------------/
/ Declareations                                                       /
/--------------------------------------------------------------------*/

/* Section address defined in linker script */
extern long _sidata[], _sdata[], _edata[], _sbss[], _ebss[];

extern int main (void);

/* Exception/IRQ Handlers */
void Reset_Handler (void)			__attribute__ ((noreturn, naked));
void NMI_Handler (void)				__attribute__ ((weak, alias ("Exception_Trap")));
void HardFault_Hander (void)		__attribute__ ((weak, alias ("Exception_Trap")));
void MemManage_Handler (void)		__attribute__ ((weak, alias ("Exception_Trap")));
void BusFault_Handler (void)		__attribute__ ((weak, alias ("Exception_Trap")));
void UsageFault_Handler (void)		__attribute__ ((weak, alias ("Exception_Trap")));
void SVC_Handler (void)				__attribute__ ((weak));
void DebugMon_Handler (void)		__attribute__ ((weak, alias ("Exception_Trap")));
void PendSV_Handler (void)			__attribute__ ((weak, alias ("Exception_Trap")));
void SysTick_Handler (void)			__attribute__ ((weak, alias ("Exception_Trap")));
void FCS_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void SWDT_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void LVD_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void MFT012_WFG_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EXTI0_7_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void EXTI8_31_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void QPRC012_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS0_RX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS0_TX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS1_RX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS1_TX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS2_RX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS2_TX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS3_RX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS3_TX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS4_RX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS4_TX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS5_RX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS5_TX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS6_RX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS6_TX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS7_RX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MFS7_TX_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void PPG_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void OSC_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void ADC0_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void ADC1_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void ADC2_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void MFT012_FR_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void MFT012_IC_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void MFT012_OC_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void BT0_7_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void CAN0_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void CAN1_IRQHandler (void)			__attribute__ ((weak, alias ("IRQ_Trap")));
void USB0_EP_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void USB0_CTL_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void USB1_EP_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void USB1_CTL_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void DMAC0_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void DMAC1_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void DMAC2_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void DMAC3_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void DMAC4_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void DMAC5_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void DMAC6_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void DMAC7_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void BT8_15_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));


/*--------------------------------------------------------------------/
/ Main Stack                                                          /
/--------------------------------------------------------------------*/

char mstk[STACK_SIZE] __attribute__ ((aligned(8), section(".STACK")));



/*--------------------------------------------------------------------/
/ Exception Vector Table for MB9BF616/617/618                         /
/--------------------------------------------------------------------*/

void* const vector[] __attribute__ ((section(".VECTOR"))) =
{
	&mstk[STACK_SIZE], Reset_Handler, NMI_Handler, HardFault_Hander,
	MemManage_Handler, BusFault_Handler, UsageFault_Handler, 0,
	0, 0, 0, SVC_Handler,
	DebugMon_Handler, 0, PendSV_Handler, SysTick_Handler,
	FCS_IRQHandler, SWDT_IRQHandler, LVD_IRQHandler, MFT012_WFG_IRQHandler,
	EXTI0_7_IRQHandler, EXTI8_31_IRQHandler, QPRC012_IRQHandler, MFS0_RX_IRQHandler,
	MFS0_TX_IRQHandler, MFS1_RX_IRQHandler, MFS1_TX_IRQHandler, MFS2_RX_IRQHandler,
	MFS2_TX_IRQHandler, MFS3_RX_IRQHandler, MFS3_TX_IRQHandler, MFS4_RX_IRQHandler,
	MFS4_TX_IRQHandler, MFS5_RX_IRQHandler, MFS5_TX_IRQHandler, MFS6_RX_IRQHandler,
	MFS6_TX_IRQHandler, MFS7_RX_IRQHandler, MFS7_TX_IRQHandler, PPG_IRQHandler,
	OSC_IRQHandler, ADC0_IRQHandler, ADC1_IRQHandler, ADC2_IRQHandler,
	MFT012_FR_IRQHandler, MFT012_IC_IRQHandler, MFT012_OC_IRQHandler, BT0_7_IRQHandler,
	CAN0_IRQHandler, CAN1_IRQHandler, USB0_EP_IRQHandler, USB0_CTL_IRQHandler,
	USB1_EP_IRQHandler, USB1_CTL_IRQHandler, DMAC0_IRQHandler, DMAC1_IRQHandler,
	DMAC2_IRQHandler, DMAC3_IRQHandler, DMAC4_IRQHandler, DMAC5_IRQHandler,
	DMAC6_IRQHandler, DMAC7_IRQHandler, BT8_15_IRQHandler
};



/*---------------------------------------------------------------------/
/ Reset_Handler is the start-up routine. It configures processor core, /
/ system clock generator, bus controller, then initialize .data        /
/ and .bss sections and then start main().                             /
/---------------------------------------------------------------------*/

void Reset_Handler (void)
{
	long *s, *d;


	/* Configure Clocking System */
	CSW_TMR = 0x0A;					/* SubDly=10.3ms, MainDly=4ms */
	SPSR |= 0x04;					/* Attach main osc to I/O pad */
	SCM_CTL = 0x02;					/* Enable main osc */
	while (!(SCM_STR & 0x02)) ;		/* Wait for main osc ready */

	PLL_CTL2 = PLL_N - 1;			/* Set PLL parameters */
	PLL_CTL1 = ((PLL_K - 1) << 4) | ((PLL_M - 1) << 0);
	PSW_TMR = 0x00;					/* PllDly=128us */
	SCM_CTL = 0x12;					/* Enable PLL osc */
	while (!(SCM_STR & 0x10)) ;		/* Wait for PLL ready */

	BSC_PSR = CLKPLL / HCLK - 1;		/* Configure base clock dividers */
	APBC0_PSR = HCLK / CLKAPB0 - 1;
	APBC1_PSR = (HCLK / CLKAPB1 - 1) | 0x80;
	APBC2_PSR = (HCLK / CLKAPB2 - 1) | 0x80;

	FRWTR = (HCLK > 72000000) ? 2 : 0;	/* Configure flash memory controller */

	SCM_CTL = 0x52;					/* Select CLKPLL as base clock */


	/* Configure External Bus Controller */
	/*
		*** Nothing to do in this project ***
	*/


	/* Initialize .data/.bss section and static objects get ready to use after this process */
	for (s = _sidata, d = _sdata; d < _edata; *d++ = *s++) ;
	for (d = _sbss; d < _ebss; *d++ = 0) ;


	/* Start main() with MSP and privileged mode */
	main();

	for (;;) ;
}



/*--------------------------------------------------------------------/
/ Unexpected Exception/IRQ Trap                                       /
/--------------------------------------------------------------------*/

void Exception_Trap (void)
{
	for (;;) ;
}


void IRQ_Trap (void)
{
	for (;;) ;
}



/*--------------------------------------------------------------------/
/ Default SVC Handler                                                 /
/--------------------------------------------------------------------*/

void SVC_Handler (void)
{
#if USE_SV_SERVICE
	asm (
	"    UBFX R3, LR, #0, #4\n"	/* Get the task SP into R3 */
	"    CMP R3, #13\n"
	"    ITE EQ\n"
	"    MRSEQ R3, PSP\n"
	"    MOVNE R3, SP\n"
	"    LDR R2, [R3, #24]\n"	/* Get stacked PC into R2 */
	"    LDRB R2, [R2, #-2]\n"	/* Get SVC number into R2 */
	"    TBB [PC, R2]\n"		/* Jump to the function specified by SVC number */
	"btbl:\n"
	"   .byte (cpsiei - btbl) / 2\n"
	"   .byte (cpsidi - btbl) / 2\n"
	"   .byte (cpsief - btbl) / 2\n"
	"   .byte (cpsidf - btbl) / 2\n"
	"   .byte (rd_scs - btbl) / 2\n"
	"   .byte (wr_scs - btbl) / 2\n"

	"cpsiei:\n"
	"   CPSIE i\n"
	"   BX LR\n"
	"cpsidi:\n"
	"   CPSID i\n"
	"   BX LR\n"
	"cpsief:\n"
	"   CPSIE f\n"
	"   BX LR\n"
	"cpsidf:\n"
	"   CPSID f\n"
	"   BX LR\n"
	"rd_scs:\n"
	"   LDR R1, [R0]\n"	/* Read scs register */
	"   STR R1, [R3]\n"	/* Set it into stacked R0 */
	"   BX LR\n"
	"wr_scs:\n"
	"   STR R1, [R0]\n"	/* Write scs register */
	"   BX LR\n"
	);
#else
	for (;;) ;
#endif
}


#if USE_SV_SERVICE

uint32_t __get_scs_reg (volatile uint32_t *reg)
{
	uint32_t res;

	asm (
	"@ MOV R0, %0\n"
	"SVC #4\n"
	"@ MOV %1, R0\n"
	"BX LR\n" : "=r" (res) : "r" (reg)
	);
	return res;
}

void __set_scs_reg (volatile uint32_t *reg, uint32_t val)
{
	asm (
	"@ MOV R0, %0\n"
	"@ MOV R1, %1\n"
	"SVC #5\n"
	"BX LR\n" : : "r" (reg), "r" (val)
	);
}

#endif
