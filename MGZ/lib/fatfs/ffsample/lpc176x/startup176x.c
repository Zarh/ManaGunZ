/*--------------------------------------------------------------/
/  Startup Module for NXP LPC176x Microcontrollers              /
/                                                               /
/ * This module defines vector table, startup code, default     /
/   exception handlers, main stack and miscellanous functions.  /
/ * This file is a non-copyrighted public domain software.      /
/--------------------------------------------------------------*/

#include "LPC176x.h"


#define STACK_SIZE	2048		/* Size of Main stack (must be multiple of 8) */

#define OSC_SEL		1			/* Oscillator selection = 0:IRC(4MHz), 1:Main, 2:RTC(32768Hz) */
#define	F_OSC		12000000	/* Oscillator frequency */
#define USE_PLL		1			/* Use PLL = 1(Yes), 0(Bypass PLL, PLL_N/M has no effect) */
#define PLL_N		12			/* PLL reference divider = 1..32 */
#define PLL_M		200			/* PLL multiplier = 6..32768 */
#define CCLK_SEL	4			/* pllclk divider = 1..256 */
#define	F_CCLK		100000000	/* Expected CCLK frequency = (USE_PLL ? F_OSC / PLL_N * PLL_M * 2 : F_OSC) / CCLK_SEL */


#define	F_PLLOUT	(F_OSC / PLL_N * PLL_M * 2)
#if USE_PLL && (F_PLLOUT < 275000000 || F_PLLOUT > 550000000)
#error PLL output frequency is out of range
#endif
#if F_CCLK != (USE_PLL ? F_PLLOUT : F_OSC) / CCLK_SEL
#error F_CCLK does not match calcurated value
#endif

#if   F_CCLK <= 20000000
#define FLASH_WAIT 0
#elif F_CCLK <= 40000000
#define FLASH_WAIT 1
#elif F_CCLK <= 60000000
#define FLASH_WAIT 2
#elif F_CCLK <= 80000000
#define FLASH_WAIT 3
#elif F_CCLK <= 120000000
#define FLASH_WAIT 4
#else
#define FLASH_WAIT 5
#endif


/*--------------------------------------------------------------------/
/ Declareations                                                       /
/--------------------------------------------------------------------*/

/* Section address defined in linker script */
extern long _sidata[], _sdata[], _edata[], _sbss[], _ebss[];

extern int main (void);

/* Exception/IRQ Handlers */
void Reset_Handler (void)		__attribute__ ((noreturn, naked));
void NMI_Handler (void)			__attribute__ ((weak, alias ("Exception_Trap")));
void HardFault_Hander (void)	__attribute__ ((weak, alias ("Exception_Trap")));
void MemManage_Handler (void)	__attribute__ ((weak, alias ("Exception_Trap")));
void BusFault_Handler (void)	__attribute__ ((weak, alias ("Exception_Trap")));
void UsageFault_Handler (void)	__attribute__ ((weak, alias ("Exception_Trap")));
void SVC_Handler (void)			__attribute__ ((weak));
void DebugMon_Handler (void)	__attribute__ ((weak, alias ("Exception_Trap")));
void PendSV_Handler (void)		__attribute__ ((weak, alias ("Exception_Trap")));
void SysTick_Handler (void)		__attribute__ ((weak, alias ("Exception_Trap")));
void WDT_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void TIMER0_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIMER1_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIMER2_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIMER3_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void UART0_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void UART1_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void UART2_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void UART3_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void PWM1_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void I2C0_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void I2C1_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void I2C2_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void SPI_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void SSP0_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void SSP1_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void PLL0_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void RTC_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void EINT0_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EINT1_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EINT2_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EINT3_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void ADC_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void BOD_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void USB_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void CAN_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void GPDMA_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void I2S_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void ETHER_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void RIT_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void MCPWM_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void QEI_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void PLL1_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void USBACT_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void CANACT_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));


/*--------------------------------------------------------------------/
/ Main Stack                                                          /
/--------------------------------------------------------------------*/

char mstk[STACK_SIZE] __attribute__ ((aligned(8), section(".STACK")));



/*--------------------------------------------------------------------/
/ Exception Vector Table for LPC1768                                  /
/--------------------------------------------------------------------*/

void* const vector[] __attribute__ ((section(".VECTOR"))) =
{
	&mstk[STACK_SIZE], Reset_Handler, NMI_Handler, HardFault_Hander,
	MemManage_Handler, BusFault_Handler, UsageFault_Handler, 0,
	0, 0, 0, SVC_Handler,
	DebugMon_Handler, 0, PendSV_Handler, SysTick_Handler,
	WDT_IRQHandler, TIMER0_IRQHandler, TIMER1_IRQHandler, TIMER2_IRQHandler,
	TIMER3_IRQHandler, UART0_IRQHandler, UART1_IRQHandler, UART2_IRQHandler,
	UART3_IRQHandler, PWM1_IRQHandler, I2C0_IRQHandler, I2C1_IRQHandler,
	I2C2_IRQHandler, SPI_IRQHandler, SSP0_IRQHandler, SSP1_IRQHandler,
	PLL0_IRQHandler, RTC_IRQHandler, EINT0_IRQHandler, EINT1_IRQHandler,
	EINT2_IRQHandler, EINT3_IRQHandler, ADC_IRQHandler, BOD_IRQHandler,
	USB_IRQHandler, CAN_IRQHandler, GPDMA_IRQHandler, I2S_IRQHandler,
	ETHER_IRQHandler, RIT_IRQHandler, MCPWM_IRQHandler, QEI_IRQHandler,
	PLL1_IRQHandler, USBACT_IRQHandler, CANACT_IRQHandler
};



/*---------------------------------------------------------------------/
/ Reset_Handler is the start-up code. It configures processor core,    /
/ system clock generator, memory controller, then initialize .data     /
/ and .bss sections and then start main().                             /
/---------------------------------------------------------------------*/

void Reset_Handler (void)
{
	long *s, *d;

	/* Configure system clock generator */

	FLASHCFG = (FLASHCFG & 0xFFFF0FFF) | (FLASH_WAIT << 12);	/* Configure flash accelerator */

	/* Set to PLL bypass mode if PLL is in use */
	PLL0CON = 1;
	PLL0FEED = 0xAA; PLL0FEED = 0x55;
	/* Disable PLL */
	PLL0CON = 0;
	PLL0FEED = 0xAA; PLL0FEED = 0x55;

	if (OSC_SEL == 1) {	/* Enable main oscillator */
		SCS = F_OSC >= 17500000 ? 0x30 : 0x20;
		while (!(SCS & 0x40)) ;	/* Wait for oscillation stable */
	} else {			/* Disable main oscillator */
		SCS = 0;
	}
	CLKSRCSEL = OSC_SEL;	/* Select specified oscillator as PLL input */
	CCLKCFG = CCLK_SEL - 1;	/* Set cclk divider (divide ratio of pllclk) */

	if (USE_PLL) {
		PLL0CFG = ((PLL_N - 1) << 16) | (PLL_M - 1);	/* Initialize PLL registers */
		PLL0FEED = 0xAA; PLL0FEED = 0x55;
		PLL0CON = 1;			/* Enable PLL */
		PLL0FEED = 0xAA; PLL0FEED = 0x55;
		while ((PLL0STAT & (1<<26)) == 0) ;	/* Wait for PLL locked */
		PLL0CON = 3;			/* Connect PLL output to the pllclk divider */
		PLL0FEED = 0xAA; PLL0FEED = 0x55;
	}

	/* Configure external memory controller */
	/*
		*** LPC176x has no EMC ***
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
