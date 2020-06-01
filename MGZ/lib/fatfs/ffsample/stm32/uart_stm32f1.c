/*------------------------------------------------------------------------/
/  STM32F100 USART control module
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2013, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include "uart_stm32f1.h"

#define F_PCLK1	24000000	/* APB1 clock for USART2/3  */
#define F_PCLK2	24000000	/* APB2 clock for USART1 */



#if USE_UART1

static volatile struct {
	uint16_t	tri, twi, tct;
	uint16_t	rri, rwi, rct;
	uint8_t		tbuf[UART1_TXB];
	uint8_t		rbuf[UART1_RXB];
} Fifo1;



void USART1_IRQHandler (void)
{
	uint32_t sr = USART1_SR;	/* Interrupt flags */
	uint8_t d;
	int i;


	if (sr & _BV(5)) {	/* RXNE is set: Rx ready */
		d = USART1_DR;	/* Get received byte */
		i = Fifo1.rct;
		if (i < UART1_RXB) {	/* Store it into the rx fifo if not full */
			Fifo1.rct = ++i;
			i = Fifo1.rwi;
			Fifo1.rbuf[i] = d;
			Fifo1.rwi = ++i % UART1_RXB;
		}
	}

	if (sr & _BV(7)) {	/* TXE is set: Tx ready */
		i = Fifo1.tct;
		if (i--) {	/* There is any data in the tx fifo */
			Fifo1.tct = (uint16_t)i;
			i = Fifo1.tri;
			USART1_DR = Fifo1.tbuf[i];
			Fifo1.tri = ++i % UART1_TXB;
		} else {	/* No data in the tx fifo */
			USART1_CR1 &= ~_BV(7);		/* Clear TXEIE - Disable TXE irq */
		}
	}
}



int uart1_test (void)
{
	return Fifo1.rct;
}



uint8_t uart1_getc (void)
{
	uint8_t d;
	int i;

	/* Wait while rx fifo is empty */
	while (!Fifo1.rct) ;

	i = Fifo1.rri;			/* Get a byte from rx fifo */
	d = Fifo1.rbuf[i];
	Fifo1.rri = ++i % UART1_RXB;
	__disable_irq();
	Fifo1.rct--;
	__enable_irq();

	return d;
}



void uart1_putc (uint8_t d)
{
	int i;

	/* Wait for tx fifo is not full */
	while (Fifo1.tct >= UART1_TXB) ;

	i = Fifo1.twi;		/* Put a byte into Tx fifo */
	Fifo1.tbuf[i] = d;
	Fifo1.twi = ++i % UART1_TXB;
	__disable_irq();
	Fifo1.tct++;
	USART1_CR1 |= _BV(7);	/* Set TXEIE - Enable TXE irq */
	__enable_irq();
}



void uart1_init (uint32_t bps)
{
	__disable_irqn(USART1_IRQn);	/* Disable USART1 interrupts */

	/* Attach USART1 module to I/O pads */
#if USE_UART1 == 1
	__enable_peripheral(IOPAEN);
	__gpio_conf_bit(GPIOA, 9, ALT_PP);
	__gpio_conf_bit(GPIOA, 10, IN_HIZ);
#else
	AFIO_MAPR |= _BV(2);
	__enable_peripheral(IOPBEN);
	__gpio_conf_bit(GPIOB, 6, ALT_PP);
	__gpio_conf_bit(GPIOB, 7, IN_HIZ);
#endif

	__enable_peripheral(USART1EN);	/* Enable USART module */
	__reset_peripheral(USART1EN);	/* Reset USART module */
	USART1_BRR = F_PCLK2 / bps;		/* Set bit rate */
	USART1_CR1 = 0x202C;			/* Enable USART in N81, Enable RXNE irq */

	/* Clear Tx/Rx fifo */
	Fifo1.tri = 0; Fifo1.twi = 0; Fifo1.tct = 0;
	Fifo1.rri = 0; Fifo1.rwi = 0; Fifo1.rct = 0;

	__enable_irqn(USART1_IRQn);	/* Enable USART1 interrupts */
}

#endif	/* USE_UART1 */



#if USE_UART2

static volatile struct {
	uint16_t	tri, twi, tct;
	uint16_t	rri, rwi, rct;
	uint8_t		tbuf[UART2_TXB];
	uint8_t		rbuf[UART2_RXB];
} Fifo2;



void USART2_IRQHandler (void)
{
	uint32_t sr = USART2_SR;
	uint8_t d;
	int i;


	if (sr & _BV(5)) {
		d = USART2_DR;
		i = Fifo2.rct;
		if (i < UART2_RXB) {
			Fifo2.rct = ++i;
			i = Fifo2.rwi;
			Fifo2.rbuf[i] = d;
			Fifo2.rwi = ++i % UART2_RXB;
		}
	}
	if (sr & _BV(7)) {
		i = Fifo2.tct;
		if (i--) {
			Fifo2.tct = (uint16_t)i;
			i = Fifo2.tri;
			USART2_DR = Fifo2.tbuf[i];
			Fifo2.tri = ++i % UART2_TXB;
		} else {
			USART2_CR1 &= ~_BV(7);
		}
	}
}



int uart2_test (void)
{
	return Fifo2.rct;
}



uint8_t uart2_getc (void)
{
	uint8_t d;
	int i;

	/* Wait while Rx fifo is empty */
	while (!Fifo2.rct) ;

	i = Fifo2.rri;			/* Get a byte from Rx fifo */
	d = Fifo2.rbuf[i];
	Fifo2.rri = ++i % UART2_RXB;
	__disable_irq();
	Fifo2.rct--;
	__enable_irq();

	return d;
}



void uart2_putc (uint8_t d)
{
	int i;

	/* Wait for Tx fifo ready */
	while (Fifo2.tct >= UART2_TXB) ;

	i = Fifo2.twi;		/* Put a byte into Tx fifo */
	Fifo2.tbuf[i] = d;
	Fifo2.twi = ++i % UART2_TXB;
	__disable_irq();
	Fifo2.tct++;
	USART2_CR1 |= _BV(7);
	__enable_irq();
}



void uart2_init (uint32_t bps)
{
	__disable_irqn(USART2_IRQn);

	/* Attach UART module to I/O pads */
#if USE_UART2 == 1
	__enable_peripheral(IOPAEN);
	__gpio_conf_bit(GPIOA, 2, ALT_PP);
	__gpio_conf_bit(GPIOA, 3, IN_HIZ);
#else
	AFIO_MAPR |= _BV(3);
	__enable_peripheral(IOPDEN);
	__gpio_conf_bit(GPIOD, 5, ALT_PP);
	__gpio_conf_bit(GPIOD, 6, IN_HIZ);
#endif

	/* Enable and initialize UART module */
	__enable_peripheral(USART2EN);
	__reset_peripheral(USART2EN);

	USART2_BRR = F_PCLK1 / bps;
	USART2_CR1 = 0x202C;	/* Enable UART in N81, Enable RXNE irq */

	/* Clear Tx/Rx fifo */
	Fifo2.tri = 0; Fifo2.twi = 0; Fifo2.tct = 0;
	Fifo2.rri = 0; Fifo2.rwi = 0; Fifo2.rct = 0;

	__enable_irqn(USART2_IRQn);
}

#endif	/* USE_UART2 */



#if USE_UART3

static volatile struct {
	uint16_t	tri, twi, tct;
	uint16_t	rri, rwi, rct;
	uint8_t		tbuf[UART3_TXB];
	uint8_t		rbuf[UART3_RXB];
} Fifo3;



void USART3_IRQHandler (void)
{
	uint32_t sr = USART3_SR;
	uint8_t d;
	int i;


	if (sr & _BV(5)) {
		d = USART3_DR;
		i = Fifo3.rct;
		if (i < UART3_RXB) {
			Fifo3.rct = ++i;
			i = Fifo3.rwi;
			Fifo3.rbuf[i] = d;
			Fifo3.rwi = ++i % UART3_RXB;
		}
	}
	if (sr & _BV(7)) {
		i = Fifo3.tct;
		if (i--) {
			Fifo3.tct = (uint16_t)i;
			i = Fifo3.tri;
			USART3_DR = Fifo3.tbuf[i];
			Fifo3.tri = ++i % UART3_TXB;
		} else {
			USART3_CR1 &= ~_BV(7);
		}
	}
}



int uart3_test (void)
{
	return Fifo3.rct;
}



uint8_t uart3_getc (void)
{
	uint8_t d;
	int i;

	/* Wait while Rx fifo is empty */
	while (!Fifo3.rct) ;

	i = Fifo3.rri;			/* Get a byte from Rx fifo */
	d = Fifo3.rbuf[i];
	Fifo3.rri = ++i % UART3_RXB;
	__disable_irq();
	Fifo3.rct--;
	__enable_irq();

	return d;
}



void uart3_putc (uint8_t d)
{
	int i;

	/* Wait for Tx firo ready */
	while (Fifo3.tct >= UART3_TXB) ;

	i = Fifo3.twi;		/* Put a byte into Tx byffer */
	Fifo3.tbuf[i] = d;
	Fifo3.twi = ++i % UART3_TXB;
	__disable_irq();
	Fifo3.tct++;
	USART3_CR1 |= _BV(7);
	__enable_irq();
}



void uart3_init (uint32_t bps)
{
	__disable_irqn(USART3_IRQn);

	/* Attach UART module to I/O pads */
#if USE_UART3 == 1
	__enable_peripheral(IOPBEN);
	__gpio_conf_bit(GPIOA, 10, ALT_PP);
	__gpio_conf_bit(GPIOA, 11, IN_HIZ);
#else
	AFIO_MAPR |= _BV(5) | _BV(4);
	__enable_peripheral(IOPDEN);
	__gpio_conf_bit(GPIOD, 8, ALT_PP);
	__gpio_conf_bit(GPIOD, 9, IN_HIZ);
#endif

	/* Enable and initialize UART module */
	__enable_peripheral(USART3EN);
	__reset_peripheral(USART3EN);

	USART3_BRR = F_PCLK1 / bps;
	USART3_CR1 = 0x202C;	/* Enable UART in N81, Enable RXNE irq */

	/* Clear Tx/Rx fifo */
	Fifo3.tri = 0; Fifo3.twi = 0; Fifo3.tct = 0;
	Fifo3.rri = 0; Fifo3.rwi = 0; Fifo3.rct = 0;

	__enable_irqn(USART3_IRQn);
}

#endif	/* USE_UART3 */


