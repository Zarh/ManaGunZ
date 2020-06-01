/*--------------------------------------------------------------/
/  Startup Module for STM32F100 Microcontrollers                /
/                                                               /
/ * This module defines vector table, startup code, default     /
/   exception handlers, main stack and miscellanous functions.  /
/ * This file is a non-copyrighted public domain software.      /
/--------------------------------------------------------------*/

#include "STM32F100.h"


#define STACK_SIZE	0		/* Size of Main stack (must be multiple of 8, If zero, MSP is set to last RAM address) */

#define	SYSCLK		24000000	/* SYSCLK frequency */
#define	AHBDIV		0			/* AHB prescaler = 2^n */
#define	AHBCLK		24000000	/* Expected AHB clock frequency, SYSCLK >> AHBDIV */
#define	F_OSC		8000000		/* Oscillator frequency, HSI or HSE */
#define SYS_SRC		2			/* SYSCLK source = 0:HSI(8M), 1:HSE(4M-24M), 2:PLL */
#define	HSECFG		0			/* HSE = 0:Off, 1:Xtal, 2:External */
#define PLLSRC		0			/* PLL clock source = 0:HSI/2, 1..16:HSE/n */


#if SYSCLK >> AHBDIV != AHBCLK
  #error Invalid combination of SYSCLK, AHBDIV and AHBCLK.
#endif
#if HSECFG == 1
  #define RCCCR_HSE	0x00010000
#elif HSECFG == 2
  #define RCCCR_HSE	0x00050000
#else
  #define RCCCR_HSE	0
#endif
#if SYS_SRC == 0
  #define RCCCF (((AHBDIV + 7) << 4) | 0x00000000)
  #define RCCCR_PLL 0
  #if F_OSC != 8000000 || SYSCLK != F_OSC
    #error Invalid combination of SYSCLK and F_OSC.
  #endif
#elif SYS_SRC == 1
  #define RCCCF (((AHBDIV + 7) << 4) | 0x00000001)
  #define RCCCR_PLL 0
  #if HSECFG == 0
    #error HSECFG must be on.
  #endif
  #if F_OSC < 4000000 || F_OSC > 24000000
    #error Invalid F_OSC is out of range.
  #endif
  #if SYSCLK != F_OSC
    #error Invalid combination of SYSCLK and F_OSC.
  #endif
#elif SYS_SRC == 2
  #define RCCCR_PLL 0x01000000
  #if PLLSRC == 0
    #define PLLMUL	(SYSCLK / 4000000)
    #define RCCCF (((PLLMUL - 2) << 18) | ((AHBDIV + 7) << 4) | 0x00000000)
    #if SYSCLK < 16000000 || SYSCLK > 24000000
      #error PLL frequency is out of range.
    #endif
    #if SYSCLK != 4000000 * PLLMUL
      #error Invalid combination of SYSCLK and PLLMUL.
    #endif
  #else
    #define PLLMUL	(SYSCLK / (F_OSC / PLLSRC))
    #define RCCCF (((PLLMUL - 2) << 18) | (((PLLSRC - 1) & 1) << 17) | ((AHBDIV + 7) << 4) | 0x00010000)
    #if HSECFG == 0
      #error HSECFG must be on.
    #endif
	#if PLLMUL < 2 || PLLMUL > 16
      #error PLLMUL is out of range.
    #endif
    #if F_OSC < 4000000 || F_OSC > 24000000
      #error F_OSC frequency is out of range.
    #endif
    #if SYSCLK != F_OSC / PLLSRC * PLLMUL
      #error Invalid combination of SYSCLK, F_OSC and PLLMUL.
    #endif
  #endif
#endif



/*--------------------------------------------------------------------/
/ Declareations                                                       /
/--------------------------------------------------------------------*/

/* Section address defined in linker script */
extern long _sidata[], _sdata[], _edata[], _sbss[], _ebss[], _endof_sram[];
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
void WWDG_IRQHandler (void)		__attribute__ ((weak, alias ("IRQ_Trap")));
void PVD_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TAMPER_STAMP_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void RTC_WKUP_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void FLASH_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void RCC_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EXTI0_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EXIT1_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EXTI2_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EXTI3_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EXTI4_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA1_CH1_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA1_CH2_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA1_CH3_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA1_CH4_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA1_CH5_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA1_CH6_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA1_CH7_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void ADC1_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EXTI9_5_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM1_BRK_TIM15_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM1_UP_TIM16_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM1_TRG_COM_TIM17_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM1_CC_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM2_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM3_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM4_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void I2C1_EV_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void I2C1_ER_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void I2C2_EV_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void I2C2_ER_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void SPI1_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void SPI2_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void USART1_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void USART2_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void USART3_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void EXTI15_10_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void RTC_Alarm_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void CEC_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM12_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM13_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM14_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void FSMC_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM5_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void SPI3_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void UART4_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void UART5_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM6_DAC_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void TIM7_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA2_CH1_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA2_CH2_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA2_CH3_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA2_CH4_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));
void DMA2_CH5_IRQHandler (void)	__attribute__ ((weak, alias ("IRQ_Trap")));



/*--------------------------------------------------------------------/
/ Main Stack                                                          /
/--------------------------------------------------------------------*/

#if STACK_SIZE > 0
static
char mstack[STACK_SIZE] __attribute__ ((aligned(8), section(".STACK")));
#define INITIAL_MSP	&mstack[STACK_SIZE]
#else
#define INITIAL_MSP	_endof_sram
#endif



/*--------------------------------------------------------------------/
/ Exception Vector Table for STM32F100                                /
/--------------------------------------------------------------------*/

void* const vector[] __attribute__ ((section(".VECTOR"))) =
{
	INITIAL_MSP, Reset_Handler, NMI_Handler, HardFault_Hander,
	MemManage_Handler, BusFault_Handler, UsageFault_Handler, 0,
	0, 0, 0, SVC_Handler,
	DebugMon_Handler, 0, PendSV_Handler, SysTick_Handler,
	WWDG_IRQHandler, PVD_IRQHandler, TAMPER_STAMP_IRQHandler, RTC_WKUP_IRQHandler,
	FLASH_IRQHandler, RCC_IRQHandler, EXTI0_IRQHandler, EXIT1_IRQHandler,
	EXTI2_IRQHandler, EXTI3_IRQHandler, EXTI4_IRQHandler, DMA1_CH1_IRQHandler,
	DMA1_CH2_IRQHandler, DMA1_CH3_IRQHandler, DMA1_CH4_IRQHandler, DMA1_CH5_IRQHandler,
	DMA1_CH6_IRQHandler, DMA1_CH7_IRQHandler, ADC1_IRQHandler, 0,
	0, 0, 0, EXTI9_5_IRQHandler,
	TIM1_BRK_TIM15_IRQHandler, TIM1_UP_TIM16_IRQHandler, TIM1_TRG_COM_TIM17_IRQHandler,
	TIM1_CC_IRQHandler, TIM2_IRQHandler,
	TIM3_IRQHandler, TIM4_IRQHandler, I2C1_EV_IRQHandler, I2C1_ER_IRQHandler,
	I2C2_EV_IRQHandler, I2C2_ER_IRQHandler, SPI1_IRQHandler, SPI2_IRQHandler,
	USART1_IRQHandler, USART2_IRQHandler, USART3_IRQHandler, EXTI15_10_IRQHandler,
	RTC_Alarm_IRQHandler, CEC_IRQHandler, TIM12_IRQHandler, TIM13_IRQHandler,
	TIM14_IRQHandler, 0, 0, FSMC_IRQHandler,
	0, TIM5_IRQHandler, SPI3_IRQHandler, UART4_IRQHandler,
	UART5_IRQHandler, TIM6_DAC_IRQHandler, TIM7_IRQHandler, DMA2_CH1_IRQHandler,
	DMA2_CH2_IRQHandler, DMA2_CH3_IRQHandler, DMA2_CH4_IRQHandler, DMA2_CH5_IRQHandler
};



/*---------------------------------------------------------------------/
/ Reset_Handler is the start-up code. It configures processor core,    /
/ system clock generator, memory controller, then initialize .data     /
/ and .bss sections and then start main().                             /
/---------------------------------------------------------------------*/


void Reset_Handler (void)
{
	long *s, *d;

	/* Set interrupt vector table address */
	VTOR = (uint32_t)vector;

	/* Configure system clock generator */
	if (PLLSRC) RCC_CFGR2 = PLLSRC - 1;
	RCC_CFGR = RCCCF;
	RCC_CR = RCCCR_HSE | RCCCR_PLL | 0x83;
	while (RCCCR_HSE && !(RCC_CR & 0x00020000)) ;
	if (RCCCR_PLL) {
		while (!(RCC_CR & 0x02000000)) ;
		RCC_CFGR |= 2;
	}

	/* Configure FSMC */
	/*
		*** Nothing to do ***
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
