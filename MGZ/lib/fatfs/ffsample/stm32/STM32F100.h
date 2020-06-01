/*-----------------------------------------------------------------------*/
/* STM31F100 Register Definitions and Cortex-M3 Supplement Definitions   */
/*       This file is a non-copyrighted public domain software           */
/*-----------------------------------------------------------------------*/

#ifndef __STM32F100
#define __STM32F100
#include <stdint.h>

#define	USE_SV_SERVICE	0	/* Enable supervisor service for user mode task */


/* CRC calculation unit */
#define CRC_DR		(*(volatile uint32_t*)0x40023000)
#define CRC_IDR		(*(volatile uint32_t*)0x40023004)
#define CRC_CR		(*(volatile uint32_t*)0x40023008)


/* Reset and clock control RCC */
#define RCC_CR			(*(volatile uint32_t*)0x40021000)
#define RCC_CFGR		(*(volatile uint32_t*)0x40021004)
#define RCC_CIR			(*(volatile uint32_t*)0x40021008)
#define RCC_APB2RSTR	(*(volatile uint32_t*)0x4002100C)
#define RCC_APB1RSTR	(*(volatile uint32_t*)0x40021010)
#define RCC_AHBENR		(*(volatile uint32_t*)0x40021014)
#define RCC_APB2ENR		(*(volatile uint32_t*)0x40021018)
#define RCC_APB1ENR		(*(volatile uint32_t*)0x4002101C)
#define RCC_BDCR		(*(volatile uint32_t*)0x40021020)
#define RCC_CSR			(*(volatile uint32_t*)0x40021024)
#define RCC_CFGR2		(*(volatile uint32_t*)0x4002102C)


/* DMA1 */
#define DMA1_ISR		(*(volatile uint32_t*)0x40020000)
#define DMA1_IFCR		(*(volatile uint32_t*)0x40020004)
#define DMA1_CCR1		(*(volatile uint32_t*)0x40020008)
#define DMA1_CNDTR1		(*(volatile uint32_t*)0x4002000C)
#define DMA1_CPAR1		(*(volatile uint32_t*)0x40020010)
#define DMA1_CMAR1		(*(volatile uint32_t*)0x40020014)
#define DMA1_CCR2		(*(volatile uint32_t*)0x4002001C)
#define DMA1_CNDTR2		(*(volatile uint32_t*)0x40020020)
#define DMA1_CPAR2		(*(volatile uint32_t*)0x40020024)
#define DMA1_CMAR2		(*(volatile uint32_t*)0x40020028)
#define DMA1_CCR3		(*(volatile uint32_t*)0x40020030)
#define DMA1_CNDTR3		(*(volatile uint32_t*)0x40020034)
#define DMA1_CPAR3		(*(volatile uint32_t*)0x40020038)
#define DMA1_CMAR3		(*(volatile uint32_t*)0x4002003C)
#define DMA1_CCR4		(*(volatile uint32_t*)0x40020044)
#define DMA1_CNDTR4		(*(volatile uint32_t*)0x40020048)
#define DMA1_CPAR4		(*(volatile uint32_t*)0x4002004C)
#define DMA1_CMAR4		(*(volatile uint32_t*)0x40020050)
#define DMA1_CCR5		(*(volatile uint32_t*)0x40020058)
#define DMA1_CNDTR5		(*(volatile uint32_t*)0x4002005C)
#define DMA1_CPAR5		(*(volatile uint32_t*)0x40020060)
#define DMA1_CMAR5		(*(volatile uint32_t*)0x40020064)
#define DMA1_CCR6		(*(volatile uint32_t*)0x4002006C)
#define DMA1_CNDTR6		(*(volatile uint32_t*)0x40020070)
#define DMA1_CPAR6		(*(volatile uint32_t*)0x40020074)
#define DMA1_CMAR6		(*(volatile uint32_t*)0x40020078)
#define DMA1_CCR7		(*(volatile uint32_t*)0x40020080)
#define DMA1_CNDTR7		(*(volatile uint32_t*)0x40020084)
#define DMA1_CPAR7		(*(volatile uint32_t*)0x40020088)
#define DMA1_CMAR7		(*(volatile uint32_t*)0x4002008C)


/* DMA2 */
#define DMA2_ISR		(*(volatile uint32_t*)0x40020400)
#define DMA2_IFCR		(*(volatile uint32_t*)0x40020404)
#define DMA2_CCR1		(*(volatile uint32_t*)0x40020408)
#define DMA2_CNDTR1		(*(volatile uint32_t*)0x4002040C)
#define DMA2_CPAR1		(*(volatile uint32_t*)0x40020410)
#define DMA2_CMAR1		(*(volatile uint32_t*)0x40020414)
#define DMA2_CCR2		(*(volatile uint32_t*)0x4002041C)
#define DMA2_CNDTR2		(*(volatile uint32_t*)0x40020420)
#define DMA2_CPAR2		(*(volatile uint32_t*)0x40020424)
#define DMA2_CMAR2		(*(volatile uint32_t*)0x40020428)
#define DMA2_CCR3		(*(volatile uint32_t*)0x40020430)
#define DMA2_CNDTR3		(*(volatile uint32_t*)0x40020434)
#define DMA2_CPAR3		(*(volatile uint32_t*)0x40020438)
#define DMA2_CMAR3		(*(volatile uint32_t*)0x4002043C)
#define DMA2_CCR4		(*(volatile uint32_t*)0x40020444)
#define DMA2_CNDTR4		(*(volatile uint32_t*)0x40020448)
#define DMA2_CPAR4		(*(volatile uint32_t*)0x4002044C)
#define DMA2_CMAR4		(*(volatile uint32_t*)0x40020450)
#define DMA2_CCR5		(*(volatile uint32_t*)0x40020458)
#define DMA2_CNDTR5		(*(volatile uint32_t*)0x4002045C)
#define DMA2_CPAR5		(*(volatile uint32_t*)0x40020460)
#define DMA2_CMAR5		(*(volatile uint32_t*)0x40020464)


/* TIM1 */
#define TIM1_CR1	(*(volatile uint16_t*)0x40012C00)
#define TIM1_CR2	(*(volatile uint16_t*)0x40012C04)
#define TIM1_SMCR	(*(volatile uint16_t*)0x40012C08)
#define TIM1_DIER	(*(volatile uint16_t*)0x40012C0C)
#define TIM1_SR		(*(volatile uint16_t*)0x40012C10)
#define TIM1_EGR	(*(volatile uint16_t*)0x40012C14)
#define TIM1_CCMR1	(*(volatile uint16_t*)0x40012C18)
#define TIM1_CCMR2	(*(volatile uint16_t*)0x40012C1C)
#define TIM1_CCER	(*(volatile uint16_t*)0x40012C20)
#define TIM1_CNT	(*(volatile uint16_t*)0x40012C24)
#define TIM1_PSC	(*(volatile uint16_t*)0x40012C28)
#define TIM1_ARR	(*(volatile uint16_t*)0x40012C2C)
#define TIM1_RCR	(*(volatile uint16_t*)0x40012C30)
#define TIM1_CCR1	(*(volatile uint16_t*)0x40012C34)
#define TIM1_CCR2	(*(volatile uint16_t*)0x40012C38)
#define TIM1_CCR3	(*(volatile uint16_t*)0x40012C3C)
#define TIM1_CCR4	(*(volatile uint16_t*)0x40012C40)
#define TIM1_BDTR	(*(volatile uint16_t*)0x40012C44)
#define TIM1_DCR	(*(volatile uint16_t*)0x40012C48)
#define TIM1_DMAR	(*(volatile uint16_t*)0x40012C4C)


/* TIM2 */
#define TIM2_CR1	(*(volatile uint16_t*)0x40000000)
#define TIM2_CR2	(*(volatile uint16_t*)0x40000004)
#define TIM2_SMCR	(*(volatile uint16_t*)0x40000008)
#define TIM2_DIER	(*(volatile uint16_t*)0x4000000C)
#define TIM2_SR		(*(volatile uint16_t*)0x40000010)
#define TIM2_EGR	(*(volatile uint16_t*)0x40000014)
#define TIM2_CCMR1	(*(volatile uint16_t*)0x40000018)
#define TIM2_CCMR2	(*(volatile uint16_t*)0x4000001C)
#define TIM2_CCER	(*(volatile uint16_t*)0x40000020)
#define TIM2_CNT	(*(volatile uint16_t*)0x40000024)
#define TIM2_PSC	(*(volatile uint16_t*)0x40000028)
#define TIM2_ARR	(*(volatile uint16_t*)0x4000002C)
#define TIM2_CCR1	(*(volatile uint16_t*)0x40000034)
#define TIM2_CCR2	(*(volatile uint16_t*)0x40000038)
#define TIM2_CCR3	(*(volatile uint16_t*)0x4000003C)
#define TIM2_CCR4	(*(volatile uint16_t*)0x40000040)
#define TIM2_DCR	(*(volatile uint16_t*)0x40000048)
#define TIM2_DMAR	(*(volatile uint16_t*)0x4000004C)


/* TIM3 */
#define TIM3_CR1	(*(volatile uint16_t*)0x40000400)
#define TIM3_CR2	(*(volatile uint16_t*)0x40000404)
#define TIM3_SMCR	(*(volatile uint16_t*)0x40000408)
#define TIM3_DIER	(*(volatile uint16_t*)0x4000040C)
#define TIM3_SR		(*(volatile uint16_t*)0x40000410)
#define TIM3_EGR	(*(volatile uint16_t*)0x40000414)
#define TIM3_CCMR1	(*(volatile uint16_t*)0x40000418)
#define TIM3_CCMR2	(*(volatile uint16_t*)0x4000041C)
#define TIM3_CCER	(*(volatile uint16_t*)0x40000420)
#define TIM3_CNT	(*(volatile uint16_t*)0x40000424)
#define TIM3_PSC	(*(volatile uint16_t*)0x40000428)
#define TIM3_ARR	(*(volatile uint16_t*)0x4000042C)
#define TIM3_CCR1	(*(volatile uint16_t*)0x40000434)
#define TIM3_CCR2	(*(volatile uint16_t*)0x40000438)
#define TIM3_CCR3	(*(volatile uint16_t*)0x4000043C)
#define TIM3_CCR4	(*(volatile uint16_t*)0x40000440)
#define TIM3_DCR	(*(volatile uint16_t*)0x40000448)
#define TIM3_DMAR	(*(volatile uint16_t*)0x4000044C)


/* TIM4 */
#define TIM4_CR1	(*(volatile uint16_t*)0x40000800)
#define TIM4_CR2	(*(volatile uint16_t*)0x40000804)
#define TIM4_SMCR	(*(volatile uint16_t*)0x40000808)
#define TIM4_DIER	(*(volatile uint16_t*)0x4000080C)
#define TIM4_SR		(*(volatile uint16_t*)0x40000810)
#define TIM4_EGR	(*(volatile uint16_t*)0x40000814)
#define TIM4_CCMR1	(*(volatile uint16_t*)0x40000818)
#define TIM4_CCMR2	(*(volatile uint16_t*)0x4000081C)
#define TIM4_CCER	(*(volatile uint16_t*)0x40000820)
#define TIM4_CNT	(*(volatile uint16_t*)0x40000824)
#define TIM4_PSC	(*(volatile uint16_t*)0x40000828)
#define TIM4_ARR	(*(volatile uint16_t*)0x4000082C)
#define TIM4_CCR1	(*(volatile uint16_t*)0x40000834)
#define TIM4_CCR2	(*(volatile uint16_t*)0x40000838)
#define TIM4_CCR3	(*(volatile uint16_t*)0x4000083C)
#define TIM4_CCR4	(*(volatile uint16_t*)0x40000840)
#define TIM4_DCR	(*(volatile uint16_t*)0x40000848)
#define TIM4_DMAR	(*(volatile uint16_t*)0x4000084C)


/* TIM5 */
#define TIM5_CR1	(*(volatile uint16_t*)0x40000C00)
#define TIM5_CR2	(*(volatile uint16_t*)0x40000C04)
#define TIM5_SMCR	(*(volatile uint16_t*)0x40000C08)
#define TIM5_DIER	(*(volatile uint16_t*)0x40000C0C)
#define TIM5_SR		(*(volatile uint16_t*)0x40000C10)
#define TIM5_EGR	(*(volatile uint16_t*)0x40000C14)
#define TIM5_CCMR1	(*(volatile uint16_t*)0x40000C18)
#define TIM5_CCMR2	(*(volatile uint16_t*)0x40000C1C)
#define TIM5_CCER	(*(volatile uint16_t*)0x40000C20)
#define TIM5_CNT	(*(volatile uint16_t*)0x40000C24)
#define TIM5_PSC	(*(volatile uint16_t*)0x40000C28)
#define TIM5_ARR	(*(volatile uint16_t*)0x40000C2C)
#define TIM5_CCR1	(*(volatile uint16_t*)0x40000C34)
#define TIM5_CCR2	(*(volatile uint16_t*)0x40000C38)
#define TIM5_CCR3	(*(volatile uint16_t*)0x40000C3C)
#define TIM5_CCR4	(*(volatile uint16_t*)0x40000C40)
#define TIM5_DCR	(*(volatile uint16_t*)0x40000C48)
#define TIM5_DMAR	(*(volatile uint16_t*)0x40000C4C)


/* TIM6 */
#define TIM6_CR1	(*(volatile uint16_t*)0x40001000)
#define TIM6_CR2	(*(volatile uint16_t*)0x40001004)
#define TIM6_DIER	(*(volatile uint16_t*)0x4000100C)
#define TIM6_SR		(*(volatile uint16_t*)0x40001010)
#define TIM6_EGR	(*(volatile uint16_t*)0x40001014)
#define TIM6_CNT	(*(volatile uint16_t*)0x40001024)
#define TIM6_PSC	(*(volatile uint16_t*)0x40001028)
#define TIM6_ARR	(*(volatile uint16_t*)0x4000102C)
#define TIM6_CCR1	(*(volatile uint16_t*)0x40001034)
#define TIM6_CCR2	(*(volatile uint16_t*)0x40001038)
#define TIM6_CCR3	(*(volatile uint16_t*)0x4000103C)
#define TIM6_CCR4	(*(volatile uint16_t*)0x40001040)
#define TIM6_DCR	(*(volatile uint16_t*)0x40001048)
#define TIM6_DMAR	(*(volatile uint16_t*)0x4000104C)


/* TIM7 */
#define TIM7_CR1	(*(volatile uint16_t*)0x40001400)
#define TIM7_CR2	(*(volatile uint16_t*)0x40001404)
#define TIM7_DIER	(*(volatile uint16_t*)0x4000140C)
#define TIM7_SR		(*(volatile uint16_t*)0x40001410)
#define TIM7_EGR	(*(volatile uint16_t*)0x40001414)
#define TIM7_CNT	(*(volatile uint16_t*)0x40001424)
#define TIM7_PSC	(*(volatile uint16_t*)0x40001428)
#define TIM7_ARR	(*(volatile uint16_t*)0x4000142C)
#define TIM7_CCR1	(*(volatile uint16_t*)0x40001434)
#define TIM7_CCR2	(*(volatile uint16_t*)0x40001438)
#define TIM7_CCR3	(*(volatile uint16_t*)0x4000143C)
#define TIM7_CCR4	(*(volatile uint16_t*)0x40001440)
#define TIM7_DCR	(*(volatile uint16_t*)0x40001448)
#define TIM7_DMAR	(*(volatile uint16_t*)0x4000144C)


/* TIM12 */
#define TIM12_CR1	(*(volatile uint16_t*)0x40001800)
#define TIM12_CR2	(*(volatile uint16_t*)0x40001804)
#define TIM12_SMCR	(*(volatile uint16_t*)0x40001808)
#define TIM12_DIER	(*(volatile uint16_t*)0x4000180C)
#define TIM12_SR	(*(volatile uint16_t*)0x40001810)
#define TIM12_EGR	(*(volatile uint16_t*)0x40001814)
#define TIM12_CCMR1	(*(volatile uint16_t*)0x40001818)
#define TIM12_CCER	(*(volatile uint16_t*)0x40001820)
#define TIM12_CNT	(*(volatile uint16_t*)0x40001824)
#define TIM12_PSC	(*(volatile uint16_t*)0x40001828)
#define TIM12_ARR	(*(volatile uint16_t*)0x4000182C)
#define TIM12_CCR1	(*(volatile uint16_t*)0x40001834)
#define TIM12_CCR2	(*(volatile uint16_t*)0x40001838)


/* TIM13 */
#define TIM13_CR1	(*(volatile uint16_t*)0x40001C00)
#define TIM13_DIER	(*(volatile uint16_t*)0x40001C0C)
#define TIM13_SR	(*(volatile uint16_t*)0x40001C10)
#define TIM13_EGR	(*(volatile uint16_t*)0x40001C14)
#define TIM13_CCMR1	(*(volatile uint16_t*)0x40001C18)
#define TIM13_CCER	(*(volatile uint16_t*)0x40001C20)
#define TIM13_CNT	(*(volatile uint16_t*)0x40001C24)
#define TIM13_PSC	(*(volatile uint16_t*)0x40001C28)
#define TIM13_ARR	(*(volatile uint16_t*)0x40001C2C)
#define TIM13_CCR1	(*(volatile uint16_t*)0x40001C34)


/* TIM14 */
#define TIM14_CR1	(*(volatile uint16_t*)0x40002000)
#define TIM14_DIER	(*(volatile uint16_t*)0x4000200C)
#define TIM14_SR	(*(volatile uint16_t*)0x40002010)
#define TIM14_EGR	(*(volatile uint16_t*)0x40002014)
#define TIM14_CCMR1	(*(volatile uint16_t*)0x40002018)
#define TIM14_CCER	(*(volatile uint16_t*)0x40002020)
#define TIM14_CNT	(*(volatile uint16_t*)0x40002024)
#define TIM14_PSC	(*(volatile uint16_t*)0x40002028)
#define TIM14_ARR	(*(volatile uint16_t*)0x4000202C)
#define TIM14_CCR1	(*(volatile uint16_t*)0x40002034)


/* TIM15 */
#define TIM15_CR1	(*(volatile uint16_t*)0x40014000)
#define TIM15_CR2	(*(volatile uint16_t*)0x40014004)
#define TIM15_SMCR	(*(volatile uint16_t*)0x40014008)
#define TIM15_DIER	(*(volatile uint16_t*)0x4001400C)
#define TIM15_SR	(*(volatile uint16_t*)0x40014010)
#define TIM15_EGR	(*(volatile uint16_t*)0x40014014)
#define TIM15_CCMR1	(*(volatile uint16_t*)0x40014018)
#define TIM15_CCER	(*(volatile uint16_t*)0x40014020)
#define TIM15_CNT	(*(volatile uint16_t*)0x40014024)
#define TIM15_PSC	(*(volatile uint16_t*)0x40014028)
#define TIM15_ARR	(*(volatile uint16_t*)0x4001402C)
#define TIM15_CCR1	(*(volatile uint16_t*)0x40014034)
#define TIM15_CCR2	(*(volatile uint16_t*)0x40014038)
#define TIM15_BDTR	(*(volatile uint16_t*)0x40014044)
#define TIM15_DCR	(*(volatile uint16_t*)0x40014048)
#define TIM15_DMAR	(*(volatile uint16_t*)0x4001404C)


/* TIM16 */
#define TIM16_CR1	(*(volatile uint16_t*)0x40014400)
#define TIM16_CR2	(*(volatile uint16_t*)0x40014404)
#define TIM16_SMCR	(*(volatile uint16_t*)0x40014408)
#define TIM16_DIER	(*(volatile uint16_t*)0x4001440C)
#define TIM16_SR	(*(volatile uint16_t*)0x40014410)
#define TIM16_EGR	(*(volatile uint16_t*)0x40014414)
#define TIM16_CCMR1	(*(volatile uint16_t*)0x40014418)
#define TIM16_CCER	(*(volatile uint16_t*)0x40014420)
#define TIM16_CNT	(*(volatile uint16_t*)0x40014424)
#define TIM16_PSC	(*(volatile uint16_t*)0x40014428)
#define TIM16_ARR	(*(volatile uint16_t*)0x4001442C)
#define TIM16_RCR	(*(volatile uint16_t*)0x40014430)
#define TIM16_CCR1	(*(volatile uint16_t*)0x40014434)
#define TIM16_BDTR	(*(volatile uint16_t*)0x40014444)
#define TIM16_DCR	(*(volatile uint16_t*)0x40014448)
#define TIM16_DMAR	(*(volatile uint16_t*)0x4001444C)


/* TIM17 */
#define TIM17_CR1	(*(volatile uint16_t*)0x40014800)
#define TIM17_CR2	(*(volatile uint16_t*)0x40014804)
#define TIM17_SMCR	(*(volatile uint16_t*)0x40014808)
#define TIM17_DIER	(*(volatile uint16_t*)0x4001480C)
#define TIM17_SR	(*(volatile uint16_t*)0x40014810)
#define TIM17_EGR	(*(volatile uint16_t*)0x40014814)
#define TIM17_CCMR1	(*(volatile uint16_t*)0x40014818)
#define TIM17_CCER	(*(volatile uint16_t*)0x40014820)
#define TIM17_CNT	(*(volatile uint16_t*)0x40014824)
#define TIM17_PSC	(*(volatile uint16_t*)0x40014828)
#define TIM17_ARR	(*(volatile uint16_t*)0x4001482C)
#define TIM17_RCR	(*(volatile uint16_t*)0x40014830)
#define TIM17_CCR1	(*(volatile uint16_t*)0x40014834)
#define TIM17_BDTR	(*(volatile uint16_t*)0x40014844)
#define TIM17_DCR	(*(volatile uint16_t*)0x40014848)
#define TIM17_DMAR	(*(volatile uint16_t*)0x4001484C)


/* RTC */
#define RTC_CRH		(*(volatile uint16_t*)0x40002800)
#define RTC_CRL		(*(volatile uint16_t*)0x40002804)
#define RTC_PRLH	(*(volatile uint16_t*)0x40002808)
#define RTC_PRLL	(*(volatile uint16_t*)0x4000280C)
#define RTC_DIVH	(*(volatile uint16_t*)0x40002810)
#define RTC_DIVL	(*(volatile uint16_t*)0x40002814)
#define RTC_CNTH	(*(volatile uint16_t*)0x40002818)
#define RTC_CNTL	(*(volatile uint16_t*)0x4000281C)
#define RTC_ALRH	(*(volatile uint16_t*)0x40002820)
#define RTC_ALRL	(*(volatile uint16_t*)0x40002824)


/* Window watchdog */
#define WWDG_CR		(*(volatile uint16_t*)0x40002C00)
#define WWDG_CFR	(*(volatile uint16_t*)0x40002C04)
#define WWDG_SR		(*(volatile uint16_t*)0x40002C08)


/* Independent watchdog */
#define IWDG_KR		(*(volatile uint16_t*)0x40003000)
#define IWDG_PR		(*(volatile uint16_t*)0x40003004)
#define IWDG_RLR	(*(volatile uint16_t*)0x40003008)
#define IWDG_SR		(*(volatile uint16_t*)0x4000300C)


/* USART1 */
#define USART1_SR	(*(volatile uint16_t*)0x40013800)
#define USART1_DR	(*(volatile uint16_t*)0x40013804)
#define USART1_BRR	(*(volatile uint16_t*)0x40013808)
#define USART1_CR1	(*(volatile uint16_t*)0x4001380C)
#define USART1_CR2	(*(volatile uint16_t*)0x40013810)
#define USART1_CR3	(*(volatile uint16_t*)0x40013814)
#define USART1_GTPR	(*(volatile uint16_t*)0x40013818)


/* USART2 */
#define USART2_SR	(*(volatile uint16_t*)0x40004400)
#define USART2_DR	(*(volatile uint16_t*)0x40004404)
#define USART2_BRR	(*(volatile uint16_t*)0x40004408)
#define USART2_CR1	(*(volatile uint16_t*)0x4000440C)
#define USART2_CR2	(*(volatile uint16_t*)0x40004410)
#define USART2_CR3	(*(volatile uint16_t*)0x40004414)
#define USART2_GTPR	(*(volatile uint16_t*)0x40004418)


/* USART3 */
#define USART3_SR	(*(volatile uint16_t*)0x40004800)
#define USART3_DR	(*(volatile uint16_t*)0x40004804)
#define USART3_BRR	(*(volatile uint16_t*)0x40004808)
#define USART3_CR1	(*(volatile uint16_t*)0x4000480C)
#define USART3_CR2	(*(volatile uint16_t*)0x40004810)
#define USART3_CR3	(*(volatile uint16_t*)0x40004814)
#define USART3_GTPR	(*(volatile uint16_t*)0x40004818)


/* UART4 */
#define UART4_SR	(*(volatile uint16_t*)0x40004C00)
#define UART4_DR	(*(volatile uint16_t*)0x40004C04)
#define UART4_BRR	(*(volatile uint16_t*)0x40004C08)
#define UART4_CR1	(*(volatile uint16_t*)0x40004C0C)
#define UART4_CR2	(*(volatile uint16_t*)0x40004C10)
#define UART4_CR3	(*(volatile uint16_t*)0x40004C14)
#define UART4_GTPR	(*(volatile uint16_t*)0x40004C18)


/* UART5 */
#define UART5_SR	(*(volatile uint16_t*)0x40005000)
#define UART5_DR	(*(volatile uint16_t*)0x40005004)
#define UART5_BRR	(*(volatile uint16_t*)0x40005008)
#define UART5_CR1	(*(volatile uint16_t*)0x4000500C)
#define UART5_CR2	(*(volatile uint16_t*)0x40005010)
#define UART5_CR3	(*(volatile uint16_t*)0x40005014)
#define UART5_GTPR	(*(volatile uint16_t*)0x40005018)


/* I2C1 */
#define I2C1_CR1	(*(volatile uint16_t*)0x40005400)
#define I2C1_CR2	(*(volatile uint16_t*)0x40005404)
#define I2C1_OAR1	(*(volatile uint16_t*)0x40005408)
#define I2C1_OAR2	(*(volatile uint16_t*)0x4000540C)
#define I2C1_DR		(*(volatile uint16_t*)0x40005410)
#define I2C1_SR1	(*(volatile uint16_t*)0x40005414)
#define I2C1_SR2	(*(volatile uint16_t*)0x40005418)
#define I2C1_CCR	(*(volatile uint16_t*)0x4000541C)
#define I2C1_TRISE	(*(volatile uint16_t*)0x40005420)


/* I2C2 */
#define I2C2_CR1	(*(volatile uint16_t*)0x40005800)
#define I2C2_CR2	(*(volatile uint16_t*)0x40005804)
#define I2C2_OAR1	(*(volatile uint16_t*)0x40005808)
#define I2C2_OAR2	(*(volatile uint16_t*)0x4000580C)
#define I2C2_DR		(*(volatile uint16_t*)0x40005810)
#define I2C2_SR1	(*(volatile uint16_t*)0x40005814)
#define I2C2_SR2	(*(volatile uint16_t*)0x40005818)
#define I2C2_CCR	(*(volatile uint16_t*)0x4000581C)
#define I2C2_TRISE	(*(volatile uint16_t*)0x40005820)


/* SPI1 */
#define SPI1_CR1	(*(volatile uint16_t*)0x40013000)
#define SPI1_CR2	(*(volatile uint16_t*)0x40013004)
#define SPI1_SR		(*(volatile uint16_t*)0x40013008)
#define SPI1_DR		(*(volatile uint16_t*)0x4001300C)
#define SPI1_CRCPR	(*(volatile uint16_t*)0x40013010)
#define SPI1_RXCRCR	(*(volatile uint16_t*)0x40013014)
#define SPI1_TXCRCR	(*(volatile uint16_t*)0x40013018)


/* SPI2 */
#define SPI2_CR1	(*(volatile uint16_t*)0x40003800)
#define SPI2_CR2	(*(volatile uint16_t*)0x40003804)
#define SPI2_SR		(*(volatile uint16_t*)0x40003808)
#define SPI2_DR		(*(volatile uint16_t*)0x4000380C)
#define SPI2_CRCPR	(*(volatile uint16_t*)0x40003810)
#define SPI2_RXCRCR	(*(volatile uint16_t*)0x40003814)
#define SPI2_TXCRCR	(*(volatile uint16_t*)0x40003818)


/* SPI3 */
#define SPI3_CR1	(*(volatile uint16_t*)0x40003C00)
#define SPI3_CR2	(*(volatile uint16_t*)0x40003C04)
#define SPI3_SR		(*(volatile uint16_t*)0x40003C08)
#define SPI3_DR		(*(volatile uint16_t*)0x40003C0C)
#define SPI3_CRCPR	(*(volatile uint16_t*)0x40003C10)
#define SPI3_RXCRCR	(*(volatile uint16_t*)0x40003C14)
#define SPI3_TXCRCR	(*(volatile uint16_t*)0x40003C18)


/* ADC1 */
#define ADC1_SR		(*(volatile uint32_t*)0x40012400)
#define ADC1_CR1	(*(volatile uint32_t*)0x40012404)
#define ADC1_CR2	(*(volatile uint32_t*)0x40012408)
#define ADC1_SMPR1	(*(volatile uint32_t*)0x4001240C)
#define ADC1_SMPR2	(*(volatile uint32_t*)0x40012410)
#define ADC1_JOFR1	(*(volatile uint32_t*)0x40012414)
#define ADC1_JOFR2	(*(volatile uint32_t*)0x40012418)
#define ADC1_JOFR3	(*(volatile uint32_t*)0x4001241C)
#define ADC1_JOFR4	(*(volatile uint32_t*)0x40012420)
#define ADC1_HTR	(*(volatile uint32_t*)0x40012424)
#define ADC1_LTR	(*(volatile uint32_t*)0x40012428)
#define ADC1_SQR1	(*(volatile uint32_t*)0x4001242C)
#define ADC1_SQR2	(*(volatile uint32_t*)0x40012430)
#define ADC1_SQR3	(*(volatile uint32_t*)0x40012434)
#define ADC1_JSQR	(*(volatile uint32_t*)0x40012438)
#define ADC1_JDR1	(*(volatile uint32_t*)0x4001243C)
#define ADC1_JDR2	(*(volatile uint32_t*)0x40012440)
#define ADC1_JDR3	(*(volatile uint32_t*)0x40012444)
#define ADC1_JDR4	(*(volatile uint32_t*)0x40012448)
#define ADC1_JR		(*(volatile uint32_t*)0x4001244C)


/* DAC */
#define DAC_CR		(*(volatile uint32_t*)0x40007400)
#define DAC_SWTRIGR	(*(volatile uint32_t*)0x40007404)
#define DAC_DHR12R1	(*(volatile uint32_t*)0x40007408)
#define DAC_DHR12L1	(*(volatile uint32_t*)0x4000740C)
#define DAC_DHR8R1	(*(volatile uint32_t*)0x40007410)
#define DAC_DHR12R2	(*(volatile uint32_t*)0x40007414)
#define DAC_DHR12L2	(*(volatile uint32_t*)0x40007418)
#define DAC_DHR8R2	(*(volatile uint32_t*)0x4000741C)
#define DAC_DHR12RD	(*(volatile uint32_t*)0x40007420)
#define DAC_DHR12LD	(*(volatile uint32_t*)0x40007424)
#define DAC_DHR8RD	(*(volatile uint32_t*)0x40007428)
#define DAC_DOR1	(*(volatile uint32_t*)0x4000742C)
#define DAC_DOR2	(*(volatile uint32_t*)0x40007430)
#define DAC_SR		(*(volatile uint32_t*)0x40007434)


/* PWR */
#define PWR_CR		(*(volatile uint32_t*)0x40007000)
#define PWR_CSR		(*(volatile uint32_t*)0x40007004)


/* Backup register */
#define BKP_DR1		(*(volatile uint16_t*)0x40006C04)
#define BKP_DR2		(*(volatile uint16_t*)0x40006C08)
#define BKP_DR3		(*(volatile uint16_t*)0x40006C0C)
#define BKP_DR4		(*(volatile uint16_t*)0x40006C10)
#define BKP_DR5		(*(volatile uint16_t*)0x40006C14)
#define BKP_DR6		(*(volatile uint16_t*)0x40006C18)
#define BKP_DR7		(*(volatile uint16_t*)0x40006C1C)
#define BKP_DR8		(*(volatile uint16_t*)0x40006C20)
#define BKP_DR9		(*(volatile uint16_t*)0x40006C24)
#define BKP_DR10	(*(volatile uint16_t*)0x40006C28)
#define BKP_RTCCR	(*(volatile uint16_t*)0x40006C2C)
#define BKP_CR		(*(volatile uint16_t*)0x40006C30)
#define BKP_CSR		(*(volatile uint16_t*)0x40006C34)


/* CEC */
#define CEC_CFGR	(*(volatile uint16_t*)0x40007800)
#define CEC_OAR		(*(volatile uint16_t*)0x40007804)
#define CEC_PRE		(*(volatile uint16_t*)0x40007808)
#define CEC_ESR		(*(volatile uint16_t*)0x4000780C)
#define CEC_CSR		(*(volatile uint16_t*)0x40007810)
#define CEC_TXD		(*(volatile uint16_t*)0x40007814)
#define CEC_RXD		(*(volatile uint16_t*)0x40007818)


/* AFIO */
#define AFIO_MAPR		(*(volatile uint32_t*)0x40010004)
#define AFIO_EXTICR1	(*(volatile uint32_t*)0x40010008)
#define AFIO_EXTICR2	(*(volatile uint32_t*)0x4001000C)
#define AFIO_EXTICR3	(*(volatile uint32_t*)0x40010010)
#define AFIO_EXTICR4	(*(volatile uint32_t*)0x40010014)
#define AFIO_MAPR2		(*(volatile uint32_t*)0x40010018)


/* EXTI */
#define EXTI_IMR	(*(volatile uint32_t*)0x40010400)
#define EXTI_EMR	(*(volatile uint32_t*)0x40010400)
#define EXTI_RTSR	(*(volatile uint32_t*)0x40010400)
#define EXTI_FTSR	(*(volatile uint32_t*)0x40010400)
#define EXTI_SWIER	(*(volatile uint32_t*)0x40010400)
#define EXTI_PR		(*(volatile uint32_t*)0x40010400)


/* GPIOA */
#define GPIOA		( (volatile uint32_t*)0x40010800)
#define GPIOA_CRL	(*(volatile uint32_t*)0x40010800)
#define GPIOA_CRH	(*(volatile uint32_t*)0x40010804)
#define GPIOA_IDR	(*(volatile uint32_t*)0x40010808)
#define GPIOA_ODR	(*(volatile uint32_t*)0x4001080C)
#define GPIOA_BSRR	(*(volatile uint32_t*)0x40010810)
#define GPIOA_BRR	(*(volatile uint32_t*)0x40010814)
#define GPIOA_LCKR	(*(volatile uint32_t*)0x40010818)


/* GPIOB */
#define GPIOB		( (volatile uint32_t*)0x40010C00)
#define GPIOB_CRL	(*(volatile uint32_t*)0x40010C00)
#define GPIOB_CRH	(*(volatile uint32_t*)0x40010C04)
#define GPIOB_IDR	(*(volatile uint32_t*)0x40010C08)
#define GPIOB_ODR	(*(volatile uint32_t*)0x40010C0C)
#define GPIOB_BSRR	(*(volatile uint32_t*)0x40010C10)
#define GPIOB_BRR	(*(volatile uint32_t*)0x40010C14)
#define GPIOB_LCKR	(*(volatile uint32_t*)0x40010C18)


/* GPIOC */
#define GPIOC		( (volatile uint32_t*)0x40011000)
#define GPIOC_CRL	(*(volatile uint32_t*)0x40011000)
#define GPIOC_CRH	(*(volatile uint32_t*)0x40011004)
#define GPIOC_IDR	(*(volatile uint32_t*)0x40011008)
#define GPIOC_ODR	(*(volatile uint32_t*)0x4001100C)
#define GPIOC_BSRR	(*(volatile uint32_t*)0x40011010)
#define GPIOC_BRR	(*(volatile uint32_t*)0x40011014)
#define GPIOC_LCKR	(*(volatile uint32_t*)0x40011018)


/* GPIOD */
#define GPIOD		( (volatile uint32_t*)0x40011400)
#define GPIOD_CRL	(*(volatile uint32_t*)0x40011400)
#define GPIOD_CRH	(*(volatile uint32_t*)0x40011404)
#define GPIOD_IDR	(*(volatile uint32_t*)0x40011408)
#define GPIOD_ODR	(*(volatile uint32_t*)0x4001140C)
#define GPIOD_BSRR	(*(volatile uint32_t*)0x40011410)
#define GPIOD_BRR	(*(volatile uint32_t*)0x40011414)
#define GPIOD_LCKR	(*(volatile uint32_t*)0x40011418)


/* GPIOE */
#define GPIOE		( (volatile uint32_t*)0x40011800)
#define GPIOE_CRL	(*(volatile uint32_t*)0x40011800)
#define GPIOE_CRH	(*(volatile uint32_t*)0x40011804)
#define GPIOE_IDR	(*(volatile uint32_t*)0x40011808)
#define GPIOE_ODR	(*(volatile uint32_t*)0x4001180C)
#define GPIOE_BSRR	(*(volatile uint32_t*)0x40011810)
#define GPIOE_BRR	(*(volatile uint32_t*)0x40011814)
#define GPIOE_LCKR	(*(volatile uint32_t*)0x40011818)


/* GPIOF */
#define GPIOF		( (volatile uint32_t*)0x40011C00)
#define GPIOF_CRL	(*(volatile uint32_t*)0x40011C00)
#define GPIOF_CRH	(*(volatile uint32_t*)0x40011C04)
#define GPIOF_IDR	(*(volatile uint32_t*)0x40011C08)
#define GPIOF_ODR	(*(volatile uint32_t*)0x40011C0C)
#define GPIOF_BSRR	(*(volatile uint32_t*)0x40011C10)
#define GPIOF_BRR	(*(volatile uint32_t*)0x40011C14)
#define GPIOF_LCKR	(*(volatile uint32_t*)0x40011C18)


/* GPIOG */
#define	GPIOG		( (volatile uint32_t*)0x40012000)
#define GPIOG_CRL	(*(volatile uint32_t*)0x40012000)
#define GPIOG_CRH	(*(volatile uint32_t*)0x40012004)
#define GPIOG_IDR	(*(volatile uint32_t*)0x40012008)
#define GPIOG_ODR	(*(volatile uint32_t*)0x4001200C)
#define GPIOG_BSRR	(*(volatile uint32_t*)0x40012010)
#define GPIOG_BRR	(*(volatile uint32_t*)0x40012014)
#define GPIOG_LCKR	(*(volatile uint32_t*)0x40012018)


/* Flash Interface */
#define FLASH_ACR		(*(volatile uint32_t*)0x40022000)
#define FLASH_KEYR		(*(volatile uint32_t*)0x40022004)
#define FLASH_OPTKEYR	(*(volatile uint32_t*)0x40022008)
#define FLASH_SR		(*(volatile uint32_t*)0x4002200C)
#define FLASH_CR		(*(volatile uint32_t*)0x40022010)
#define FLASH_AR		(*(volatile uint32_t*)0x40022014)
#define FLASH_OBR		(*(volatile uint32_t*)0x4002201C)
#define FLASH_WRPR		(*(volatile uint32_t*)0x40022020)


/* Cortex-M3 System timer */
#define	SYST_CSR	(*(volatile uint32_t*)0xE000E010)
#define	SYST_RVR	(*(volatile uint32_t*)0xE000E014)
#define	SYST_CVR	(*(volatile uint32_t*)0xE000E018)
#define	SYST_CALIB	(*(volatile uint32_t*)0xE000E01C)

/* Cortex-M3 NVIC */
#define	ISER		( (volatile uint32_t*)0xE000E100)
#define	ICER		( (volatile uint32_t*)0xE000E180)
#define	ISPR		( (volatile uint32_t*)0xE000E200)
#define	ICPR		( (volatile uint32_t*)0xE000E280)
#define	IABR		( (volatile uint32_t*)0xE000E300)
#define	IPR			( (volatile uint8_t *)0xE000E400)
#define	STIR		(*(volatile uint32_t*)0xE000EF00)

/* Cortex-M3 SCB */
#define	ACTLR		(*(volatile uint32_t*)0xE000E008)
#define	CPUID		(*(volatile uint32_t*)0xE000ED00)
#define	ICSR		(*(volatile uint32_t*)0xE000ED04)
#define	VTOR		(*(volatile uint32_t*)0xE000ED08)
#define	AIRCR		(*(volatile uint32_t*)0xE000ED0C)
#define	SCR			(*(volatile uint32_t*)0xE000ED10)
#define	CCR			(*(volatile uint32_t*)0xE000ED14)
#define	SHPR		( (volatile uint8_t *)0xE000ED14)
#define	CFSR		(*(volatile uint32_t*)0xE000ED28)
#define	MMSR		(*(volatile uint32_t*)0xE000ED28)
#define	BFSR		(*(volatile uint32_t*)0xE000ED29)
#define	UFSR		(*(volatile uint32_t*)0xE000ED2A)
#define	HFSR		(*(volatile uint32_t*)0xE000ED2C)
#define	MMFAR		(*(volatile uint32_t*)0xE000ED34)
#define	BFAR		(*(volatile uint32_t*)0xE000ED38)



/*--------------------------------------------------------------*/
/* Cortex-M3 core/peripheral access macros                      */
/*--------------------------------------------------------------*/

/* These are for only privileged mode */
#define __enable_irq() asm volatile ("CPSIE i\n")
#define __disable_irq() asm volatile ("CPSID i\n")
#define __enable_irqn(n) ISER[(n) / 32] = 1 << ((n) % 32)
#define __disable_irqn(n) ICER[(n) / 32] = 1 << ((n) % 32)
#define __test_irqn_enabled(n) (ISER[(n) / 32] & (1 << ((n) % 32)))
#define __set_irqn(n) ISPR[(n) / 32] = 1 << ((n) % 32)
#define __clear_irqn(n) ICPR[(n) / 32] = 1 << ((n) % 32)
#define __test_irqn(n) (ICPR[(n) / 32] & (1 << ((n) % 32)))
#define __test_irqn_active(n) (IABR[n / 32] & (1 << ((n) % 32)))
#define __set_irqn_priority(n,v) IPR[n] = (v)
#define __set_faultn_priority(n,v) SHPR[(n) + 16] = (v)
#define __get_MSP()			({uint32_t __rv; asm ("MRS %0, MSP\n"		: "=r" (__rv)); __rv;})
#define __get_PSP()			({uint32_t __rv; asm ("MRS %0, PSP\n"		: "=r" (__rv)); __rv;})
#define __get_PRIMASK() 	({uint32_t __rv; asm ("MRS %0, PRIMASK\n"	: "=r" (__rv)); __rv;})
#define __get_FAULTMASK()	({uint32_t __rv; asm ("MRS %0, FAULTMASK\n"	: "=r" (__rv)); __rv;})
#define __get_BASEPRI() 	({uint32_t __rv; asm ("MRS %0, BASEPRI\n"	: "=r" (__rv)); __rv;})
#define __get_CONTROL()		({uint32_t __rv; asm ("MRS %0, CONTROL\n"	: "=r" (__rv)); __rv;})
#define __set_MSP(arg)		{uint32_t __v=arg; asm ("MSR MSP, %0\n" 		:: "r" (__v));}
#define __set_PSP(arg)		{uint32_t __v=arg; asm ("MSR PSP, %0\n" 		:: "r" (__v));}
#define __set_PRIMASK(arg)	{uint32_t __v=arg; asm ("MSR PRIMASK, %0\n" 	:: "r" (__v));}
#define __set_FAULTMASK(arg) {uint32_t __v=arg; asm ("MSR FAULTMASK, %0\n" 	:: "r" (__v));}
#define __set_BASEPRI(arg)	{uint32_t __v=arg; asm ("MSR BASEPRI, %0\n" 	:: "r" (__v));}
#define __set_CONTORL(arg)	{uint32_t __v=arg; asm ("MSR CONTROL, %0\nISB\n" :: "r" (__v));}

/* These functions and macros are alternative of above for user mode */
#if USE_SV_SERVICE
#define __enable_irq_user()		asm volatile ("SVC #0\n")	/* CPSIE i */
#define __disable_irq_user()	asm volatile ("SVC #1\n")	/* CPSID i */
#define __enable_irq_user()		asm volatile ("SVC #2\n")	/* CPSIE f */
#define __disable_irq_user()	asm volatile ("SVC #3\n")	/* CPSID f */
uint32_t __get_scs_reg (volatile uint32_t* reg);			/* Read a register in SCS */
void __set_scs_reg (volatile uint32_t* reg, uint32_t val);	/* Write a register in SCS */
#define __enable_irqn_user(n) __set_scs_reg(&ISER[((n) / 32)], 1 << ((n) % 32))
#define __disable_irqn_user(n) __set_scs_reg(&ISCR[((n) / 32)], 1 << ((n) % 32))
#define __test_irqn_enabled_user(n) (__get_scs_reg(&ISCR[(n) / 32]) & (1 << ((n) % 32)))
#define __set_irqn_user(n) __set_scs_reg(&ISPR[((n) / 32)], 1 << ((n) % 32))
#define __clear_irqn_user(n) __set_scs_reg(&ICPR[((n) / 32)], 1 << ((n) % 32))
#define __test_irqn_user(n) (__get_scs_reg(&ICPR[(n) / 32]) & (1 << ((n) % 32)))
#define __test_active_irqn_user(n) (__get_scs_reg(&IABR[(n) / 32]) & (1 << ((n) % 32)))
#define __set_irqn_priority_user(n,v) __set_scs_reg(&IPR[n], (v))
#define __set_faultn_priority_user(n,v) __set_scs_reg(&SHPR[(n) + 16], (v))
#endif

/* These functions/macros can be used at user/privileged mode */
#define __REV(arg)		({uint32_t __r, __v=arg; asm ("REV %0,%1\n"   : "=r" (__r) : "r" (__v) ); __r;})
#define __REV16(arg)	({uint32_t __r, __v=arg; asm ("REV16 %0,%1\n" : "=r" (__r) : "r" (__v) ); __r;})
#define __REVSH(arg)	({uint32_t __r, __v=arg; asm ("REVSH %0,%1\n" : "=r" (__r) : "r" (__v) ); __r;})
#define __RBIT(arg)		({uint32_t __r, __v=arg; asm ("RBIT %0,%1\n"  : "=r" (__r) : "r" (__v) ); __r;})
#define __LDREXB(p)		({uint8_t __r;	asm ("LDREXB %0,[%1]\n" : "=r" (__r) : "r" (p)); __r;})
#define __LDREXH(p)		({uint16_t __r;	asm ("LDREXH %0,[%1]\n" : "=r" (__r) : "r" (p)); __r;})
#define __LDREXW(p)		({uint32_t __r;	asm ("LDREX  %0,[%1]\n" : "=r" (__r) : "r" (p)); __r;})
#define __STREXB(d,p)	({register uint32_t __r asm("r2"); register uint8_t __d asm("r1") = d; register volatile uint8_t *__p asm("r0") = p; asm ("STREXB %0,%2,[%1]\n" : "=r" (__r) : "r" (__p), "r" (__d)); __r;})
#define __STREXH(d,p)	({register uint32_t __r asm("r2"); register uint16_t __d asm("r1") = d; register volatile uint16_t *__p asm("r0") = p; asm ("STREXH %0,%2,[%1]\n" : "=r" (__r) : "r" (p), "r" (__d)); __r;})
#define __STREXW(d,p)	({register uint32_t __r asm("r2"); register uint32_t __d asm("r1") = d; register volatile uint32_t *__p asm("r0") = p; asm ("STREX  %0,%2,[%1]\n" : "=r" (__r) : "r" (p), "r" (__d)); __r;})
#define __CLREX() asm volatile ("CLREX\n")
#define __SEV() asm volatile ("SEV\n")
#define __WFE() asm volatile ("WFE\n")
#define __WFI() asm volatile ("WFI\n")

/* STM32F100 IRQ number */
#define MemManage_IRQn			(-12)
#define BusFault_IRQn			(-11)
#define UsageFault_IRQn			(-10)
#define SVC_IRQn				(-5)
#define DebugMon_IRQn			(-4)
#define PendSV_IRQn				(-2)
#define SysTick_IRQn			(-1)
#define WWDG_IRQn				0
#define PVD_IRQn				1
#define TAMPER_STAMP_IRQn		2
#define RTC_WKUP_IRQn			3
#define FLASH_IRQn				4
#define RCC_IRQn				5
#define EXTI0_IRQn				6
#define EXIT1_IRQn				7
#define EXTI2_IRQn				8
#define EXTI3_IRQn				9
#define EXTI4_IRQn				10
#define DMA1_CH1_IRQn			11
#define DMA1_CH2_IRQn			12
#define DMA1_CH3_IRQn			13
#define DMA1_CH4_IRQn			14
#define DMA1_CH5_IRQn			15
#define DMA1_CH6_IRQn			16
#define DMA1_CH7_IRQn			17
#define ADC1_IRQn				18
#define EXTI9_5_IRQn			23
#define TIM1_BRK_TIM15_IRQn		24
#define TIM1_UP_TIM16_IRQn		25
#define TIM1_TRG_COM_TIM17_IRQn	26
#define TIM1_CC_IRQn			27
#define TIM2_IRQn				28
#define TIM3_IRQn				29
#define TIM4_IRQn				30
#define I2C1_EV_IRQn			31
#define I2C1_ER_IRQn			32
#define I2C2_EV_IRQn			33
#define I2C2_ER_IRQn			34
#define SPI1_IRQn				35
#define SPI2_IRQn				36
#define USART1_IRQn				37
#define USART2_IRQn				38
#define USART3_IRQn				39
#define EXTI15_10_IRQn			40
#define RTC_Alarm_IRQn			41
#define CEC_IRQn				42
#define TIM12_IRQn				43
#define TIM13_IRQn				44
#define TIM14_IRQn				45
#define FSMC_IRQn				48
#define TIM5_IRQn				50
#define SPI3_IRQn				51
#define UART4_IRQn				52
#define UART5_IRQn				53
#define TIM6_DAC_IRQn			54
#define TIM7_IRQn				55
#define DMA2_CH1_IRQn			56
#define DMA2_CH2_IRQn			57
#define DMA2_CH3_IRQn			58
#define DMA2_CH4_IRQn			59
#define DMA2_CH5_IRQn			60


/* STM32F100 GPIO contorls */
#define __gpio_conf_bit(p,b,f)	p[b/8] = (p[b/8] & ~(0xF << ((b % 8) * 4))) | (f << ((b % 8) * 4))
#define __gpio_conf_lo8(p,f7,f6,f5,f4,f3,f2,f1,f0)	p[0] = f7<<28|f6<<24|f5<<20|f4<<16|f3<<12|f2<<8|f1<<4|f0
#define __gpio_conf_hi8(p,ff,fe,fd,fc,fb,fa,f9,f8)	p[1] = ff<<28|fe<<24|fd<<20|fc<<16|fb<<12|fa<<8|f9<<4|f8
#define IN_ANA	0x0
#define IN_HIZ	0x4
#define IN_PUL	0x8
#define OUT_PP	0x3
#define OUT_OD	0x7
#define ALT_PP	0xB
#define ALT_OD	0xF


/* STM32F100 peripheral contorls */
#define __enable_peripheral(p)	(&RCC_AHBENR)[p/32] |= 1 << (p % 32)
#define __disable_peripheral(p)	(&RCC_AHBENR)[p/32] &= ~(1 << (p % 32))
#define __reset_peripheral(p)	{(&RCC_CIR)[p/32] |= 1 << (p % 32); (&RCC_CIR)[p/32] &= ~(1 << (p % 32)); }
#define DMA1EN		0
#define DMA2EN		1
#define SRAMEN		2
#define FLITFEN		4
#define CRCEN		6
#define FSMCEN		8
#define AFIOEN		32
#define IOPAEN		34
#define IOPBEN		35
#define IOPCEN		36
#define IOPDEN		37
#define IOPEEN		38
#define IOPFEN		39
#define IOPGEN		40
#define ADC1EN		41
#define TIM1EN		43
#define SPI1EN		44
#define USART1EN	46
#define TIM15EN		48
#define TIM16EN		49
#define TIM17EN		50
#define TIM2EN		64
#define TIM3EN		65
#define TIM4EN		66
#define TIM5EN		67
#define TIM6EN		68
#define TIM7EN		69
#define TIM12EN		70
#define TIM13EN		71
#define TIM14EN		72
#define WWDGEN		75
#define SPI2EN		78
#define SPI3EN		79
#define USART2EN	81
#define USART3EN	82
#define UART4EN		83
#define UART5EN		84
#define I2C1EN		85
#define I2C2EN		86
#define BKPEN		91
#define PWREN		92
#define DACEN		93
#define CECEN		94



/*--------------------------------------------------------------*/
/* Misc Macros                                                  */
/*--------------------------------------------------------------*/

/* Bit definitions */
#define	_BV(bit) (1<<(bit))

/* Import a binary file */
#define	IMPORT_BIN(sect, file, sym) asm (\
		".section " #sect "\n"                  /* Change section */\
		".balign 4\n"                           /* Word alignment */\
		".global " #sym "\n"                    /* Export the object address to other modules */\
		#sym ":\n"                              /* Define the object label */\
		".incbin \"" file "\"\n"                /* Import the file */\
		".global _sizeof_" #sym "\n"            /* Export the object size to oher modules */\
		".set _sizeof_" #sym ", . - " #sym "\n" /* Define the object size */\
		".balign 4\n"                           /* Word alignment */\
		".section \".text\"\n")                 /* Restore section */

/* Import a part of binary file */
#define	IMPORT_BIN_PART(sect, file, ofs, siz, sym) asm (\
		".section " #sect "\n"\
		".balign 4\n"\
		".global " #sym "\n"\
		#sym ":\n"\
		".incbin \"" file "\"," #ofs "," #siz "\n"\
		".global _sizeof_" #sym "\n"\
		".set _sizeof_" #sym ", . - " #sym "\n"\
		".balign 4\n"\
		".section \".text\"\n")

/* Jump to secondary application */
#define JUMP_APP(appvt) asm (\
		"LDR SP, [%0]\n"          /* Initialize SP */\
		"LDR PC, [%0, #4]\n"      /* Go to reset vector */\
        : : "r" (appvt))


#endif /* __LPC176x */
