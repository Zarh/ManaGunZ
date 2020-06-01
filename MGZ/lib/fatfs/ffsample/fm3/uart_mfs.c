/*------------------------------------------------------------------------/
/  MB9BF616/617/618 UART(MFS) control module
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

#include "FM3_type2.h"
#include "uart_mfs.h"

#define F_PCLK		72000000	/* Bus clock for the MFS module */


#if USE_UART0

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART0_TXB];
} TxFifo0;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART0_RXB];
} RxFifo0;


void MFS0_TX_IRQHandler (void)
{
	uint16_t i, n;


	n = TxFifo0.ct;
	if (n) {		/* There is one or more byte in the Tx buffer */
		TxFifo0.ct = --n;
		i = TxFifo0.ri;
		MFS0_TDR = TxFifo0.buff[i++];
		TxFifo0.ri = i % UART0_TXB;
	}
	if (!n) MFS0_SCR &= ~0x08;	/* Clear TIE (disable Tx ready irq if no data to transmit) */
}


void MFS0_RX_IRQHandler (void)
{
	uint8_t d;
	uint16_t i, n;


	if (MFS0_SSR & 0x38) {	/* Error occured */
		MFS0_SSR = 0x80;
	}

	if (MFS0_SSR & 0x04) {	/* Data arrived */
		d = MFS0_RDR;	/* Get received data */
		n = RxFifo0.ct;
		if (n < UART0_RXB) {	/* Store it into the Rx buffer if not full */
			RxFifo0.ct = ++n;
			i = RxFifo0.wi;
			RxFifo0.buff[i++] = d;
			RxFifo0.wi = i % UART0_RXB;
		}
	}

}


int uart0_test (void)	/* 0:Empty, >0:Not empty */
{
	return RxFifo0.ct;
}


uint8_t uart0_getc (void)
{
	uint8_t d;
	uint16_t i;

	/* Wait for Rx FIFO ready */
	while (!RxFifo0.ct) ;

	i = RxFifo0.ri;
	d = RxFifo0.buff[i++];
	RxFifo0.ri = i % UART0_RXB;
	__disable_irq();
	RxFifo0.ct--;
	__enable_irq();

	return d;
}


void uart0_putc (uint8_t d)
{
	uint16_t i, n;

	/* Wait for Tx FIFO ready */
	while (TxFifo0.ct >= UART0_TXB) ;

	i = TxFifo0.wi;
	TxFifo0.buff[i++] = d;	/* Put a byte into Tx byffer */
	TxFifo0.wi = i % UART0_TXB;
	__disable_irq();
	TxFifo0.ct++;
	MFS0_SCR |= 0x08;	/* Set TIE (enable TX ready irq) */
	__enable_irq();
}


void uart0_init (void)
{
	__disable_irqn(MFS0_RX_IRQn);
	__disable_irqn(MFS0_TX_IRQn);

	/* Initialize MFS (UART mode, N81)*/
	MFS0_SCR = 0x80;		/* Disable MFS */
	MFS0_SMR = 0x01;		/* Enable SOT output */
	MFS0_ESCR = 0;
	MFS0_BGR = F_PCLK / UART0_BPS - 1;
	MFS0_SCR = 0x13;		/* Enable MFS: Set RIE/RXE/TXE */

	/* Clear Tx/Rx buffers */
	TxFifo0.ri = 0; TxFifo0.wi = 0; TxFifo0.ct = 0;
	RxFifo0.ri = 0; RxFifo0.wi = 0; RxFifo0.ct = 0;

	/* Attach MFS module to I/O pads */
#if   UART0_LOC == 0
	EPFR07 = (EPFR07 & ~(15 << 4)) | (4 << 4);
	PFR2 |= 3 << 1;
#elif UART0_LOC == 1
	EPFR07 = (EPFR07 & ~(15 << 4)) | (10 << 4);
	PFR1 |= 3 << 4;
#elif UART0_LOC == 2
	EPFR07 = (EPFR07 & ~(15 << 4)) | (15 << 4);
	PFRB |= 3 << 4;
#endif

	/* Enable Tx/Rx/Error interrupts */
	__enable_irqn(MFS0_RX_IRQn);
	__enable_irqn(MFS0_TX_IRQn);
}

#endif



#if USE_UART1

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART1_TXB];
} TxFifo1;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART1_RXB];
} RxFifo1;


void MFS1_TX_IRQHandler (void)
{
	uint16_t i, n;


	n = TxFifo1.ct;
	if (n) {		/* There is one or more byte in the Tx buffer */
		TxFifo1.ct = --n;
		i = TxFifo1.ri;
		MFS1_TDR = TxFifo1.buff[i++];
		TxFifo1.ri = i % UART1_TXB;
	}
	if (!n) MFS1_SCR &= ~0x08;	/* Clear TIE (disable Tx ready irq if no data to transmit) */
}


void MFS1_RX_IRQHandler (void)
{
	uint8_t d;
	uint16_t i, n;


	if (MFS1_SSR & 0x38) {	/* Error occured */
		MFS1_SSR = 0x80;
	}

	if (MFS1_SSR & 0x04) {	/* Data arrived */
		d = MFS1_RDR;	/* Get received data */
		n = RxFifo1.ct;
		if (n < UART1_RXB) {	/* Store it into the Rx buffer if not full */
			RxFifo1.ct = ++n;
			i = RxFifo1.wi;
			RxFifo1.buff[i++] = d;
			RxFifo1.wi = i % UART1_RXB;
		}
	}

}


int uart1_test (void)	/* 0:Empty, >0:Not empty */
{
	return RxFifo1.ct;
}


uint8_t uart1_getc (void)
{
	uint8_t d;
	uint16_t i;

	/* Wait for Rx FIFO ready */
	while (!RxFifo1.ct) ;

	i = RxFifo1.ri;
	d = RxFifo1.buff[i++];
	RxFifo1.ri = i % UART1_RXB;
	__disable_irq();
	RxFifo1.ct--;
	__enable_irq();

	return d;
}


void uart1_putc (uint8_t d)
{
	uint16_t i, n;

	/* Wait for Tx FIFO ready */
	while (TxFifo1.ct >= UART1_TXB) ;

	i = TxFifo1.wi;
	TxFifo1.buff[i++] = d;	/* Put a byte into Tx byffer */
	TxFifo1.wi = i % UART1_TXB;
	__disable_irq();
	TxFifo1.ct++;
	MFS1_SCR |= 0x08;	/* Set TIE (enable TX ready irq) */
	__enable_irq();
}


void uart1_init (void)
{
	__disable_irqn(MFS1_RX_IRQn);
	__disable_irqn(MFS1_TX_IRQn);

	/* Initialize MFS (UART mode, N81)*/
	MFS1_SCR = 0x80;		/* Disable MFS */
	MFS1_SMR = 0x01;		/* Enable SOT output */
	MFS1_ESCR = 0;
	MFS1_BGR = F_PCLK / UART1_BPS - 1;
	MFS1_SCR = 0x13;		/* Enable MFS: Set RIE/RXE/TXE */

	/* Clear Tx/Rx buffers */
	TxFifo1.ri = 0; TxFifo1.wi = 0; TxFifo1.ct = 0;
	RxFifo1.ri = 0; RxFifo1.wi = 0; RxFifo1.ct = 0;

	/* Attach MFS module to I/O pads */
#if   UART1_LOC == 0
	EPFR07 = (EPFR07 & ~(15 << 10)) | (4 << 10);
	PFR5 |= 3 << 6;
#elif UART1_LOC == 1
	EPFR07 = (EPFR07 & ~(15 << 10)) | (10 << 10);
	PFR1 |= 3 << 1;
#elif UART1_LOC == 2
	EPFR07 = (EPFR07 & ~(15 << 10)) | (15 << 10);
	PFRF |= 3 << 0;
#endif

	/* Enable Tx/Rx/Error interrupts */
	__enable_irqn(MFS1_RX_IRQn);
	__enable_irqn(MFS1_TX_IRQn);
}

#endif



#if USE_UART2

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART2_TXB];
} TxFifo2;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART2_RXB];
} RxFifo2;


void MFS2_TX_IRQHandler (void)
{
	uint16_t i, n;


	n = TxFifo2.ct;
	if (n) {		/* There is one or more byte in the Tx buffer */
		TxFifo2.ct = --n;
		i = TxFifo2.ri;
		MFS2_TDR = TxFifo2.buff[i++];
		TxFifo2.ri = i % UART2_TXB;
	}
	if (!n) MFS2_SCR &= ~0x08;	/* Clear TIE (disable Tx ready irq if no data to transmit) */
}


void MFS2_RX_IRQHandler (void)
{
	uint8_t d;
	uint16_t i, n;


	if (MFS2_SSR & 0x38) {	/* Error occured */
		MFS2_SSR = 0x80;
	}

	if (MFS2_SSR & 0x04) {	/* Data arrived */
		d = MFS2_RDR;	/* Get received data */
		n = RxFifo2.ct;
		if (n < UART2_RXB) {	/* Store it into the Rx buffer if not full */
			RxFifo2.ct = ++n;
			i = RxFifo2.wi;
			RxFifo2.buff[i++] = d;
			RxFifo2.wi = i % UART2_RXB;
		}
	}

}


int uart2_test (void)	/* 0:Empty, >0:Not empty */
{
	return RxFifo2.ct;
}


uint8_t uart2_getc (void)
{
	uint8_t d;
	uint16_t i;

	/* Wait for Rx FIFO ready */
	while (!RxFifo2.ct) ;

	i = RxFifo2.ri;
	d = RxFifo2.buff[i++];
	RxFifo2.ri = i % UART2_RXB;
	__disable_irq();
	RxFifo2.ct--;
	__enable_irq();

	return d;
}


void uart2_putc (uint8_t d)
{
	uint16_t i, n;

	/* Wait for Tx FIFO ready */
	while (TxFifo2.ct >= UART2_TXB) ;

	i = TxFifo2.wi;
	TxFifo2.buff[i++] = d;	/* Put a byte into Tx byffer */
	TxFifo2.wi = i % UART2_TXB;
	__disable_irq();
	TxFifo2.ct++;
	MFS2_SCR |= 0x08;	/* Set TIE (enable TX ready irq) */
	__enable_irq();
}


void uart2_init (void)
{
	__disable_irqn(MFS2_RX_IRQn);
	__disable_irqn(MFS2_TX_IRQn);

	/* Initialize MFS (UART mode, N81)*/
	MFS2_SCR = 0x80;		/* Disable MFS */
	MFS2_SMR = 0x01;		/* Enable SOT output */
	MFS2_ESCR = 0;
	MFS2_BGR = F_PCLK / UART2_BPS - 1;
	MFS2_SCR = 0x13;		/* Enable MFS: Set RIE/RXE/TXE */

	/* Clear Tx/Rx buffers */
	TxFifo2.ri = 0; TxFifo2.wi = 0; TxFifo2.ct = 0;
	RxFifo2.ri = 0; RxFifo2.wi = 0; RxFifo2.ct = 0;

	/* Attach MFS module to I/O pads */
#if   UART2_LOC == 0
	EPFR07 = (EPFR07 & ~(15 << 16)) | (4 << 16);
	PFR7 |= 3 << 2;
#elif UART2_LOC == 1
	EPFR07 = (EPFR07 & ~(15 << 16)) | (10 << 16);
	PFR2 |= 3 << 4;
#elif UART2_LOC == 2
	EPFR07 = (EPFR07 & ~(15 << 16)) | (15 << 16);
	PFR1 |= 3 << 7;
#endif

	/* Enable Tx/Rx/Error interrupts */
	__enable_irqn(MFS2_RX_IRQn);
	__enable_irqn(MFS2_TX_IRQn);
}

#endif



#if USE_UART3

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART3_TXB];
} TxFifo3;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART3_RXB];
} RxFifo3;


void MFS3_TX_IRQHandler (void)
{
	uint16_t i, n;


	n = TxFifo3.ct;
	if (n) {		/* There is one or more byte in the Tx buffer */
		TxFifo3.ct = --n;
		i = TxFifo3.ri;
		MFS3_TDR = TxFifo3.buff[i++];
		TxFifo3.ri = i % UART3_TXB;
	}
	if (!n) MFS3_SCR &= ~0x08;	/* Clear TIE (disable Tx ready irq if no data to transmit) */
}


void MFS3_RX_IRQHandler (void)
{
	uint8_t d;
	uint16_t i, n;


	if (MFS3_SSR & 0x38) {	/* Error occured */
		MFS3_SSR = 0x80;
	}

	if (MFS3_SSR & 0x04) {	/* Data arrived */
		d = MFS3_RDR;	/* Get received data */
		n = RxFifo3.ct;
		if (n < UART3_RXB) {	/* Store it into the Rx buffer if not full */
			RxFifo3.ct = ++n;
			i = RxFifo3.wi;
			RxFifo3.buff[i++] = d;
			RxFifo3.wi = i % UART3_RXB;
		}
	}

}


int uart3_test (void)	/* 0:Empty, >0:Not empty */
{
	return RxFifo3.ct;
}



uint8_t uart3_getc (void)
{
	uint8_t d;
	uint16_t i;

	/* Wait for Rx FIFO ready */
	while (!RxFifo3.ct) ;

	i = RxFifo3.ri;
	d = RxFifo3.buff[i++];
	RxFifo3.ri = i % UART3_RXB;
	__disable_irq();
	RxFifo3.ct--;
	__enable_irq();

	return d;
}



void uart3_putc (uint8_t d)
{
	uint16_t i;

	/* Wait for Tx FIFO ready */
	while (TxFifo3.ct >= UART3_TXB) ;

	i = TxFifo3.wi;
	TxFifo3.buff[i++] = d;	/* Put a byte into Tx byffer */
	TxFifo3.wi = i % UART3_TXB;
	__disable_irq();
	TxFifo3.ct++;
	MFS3_SCR |= 0x08;	/* Set TIE (enable TX ready irq) */
	__enable_irq();
}



void uart3_init (void)
{
	__disable_irqn(MFS3_RX_IRQn);
	__disable_irqn(MFS3_TX_IRQn);

	/* Initialize MFS (UART mode, N81)*/
	MFS3_SCR = 0x80;		/* Disable MFS */
	MFS3_SMR = 0x01;		/* Enable SOT output */
	MFS3_ESCR = 0;
	MFS3_BGR = F_PCLK / UART3_BPS - 1;
	MFS3_SCR = 0x13;		/* Enable MFS: Set RIE/RXE/TXE */

	/* Clear Tx/Rx buffers */
	TxFifo3.ri = 0; TxFifo3.wi = 0; TxFifo3.ct = 0;
	RxFifo3.ri = 0; RxFifo3.wi = 0; RxFifo3.ct = 0;

	/* Attach MFS module to I/O pads */
#if   UART3_LOC == 0
	EPFR07 = (EPFR07 & ~(15 << 22)) | (4 << 22);
	PFR7 |= 3 << 5;
#elif UART3_LOC == 1
	EPFR07 = (EPFR07 & ~(15 << 22)) | (10 << 22);
	PFR5 |= 3 << 0;
#elif UART3_LOC == 2
	EPFR07 = (EPFR07 & ~(15 << 22)) | (15 << 22);
	PFR4 |= 3 << 8;
#endif

	/* Enable Tx/Rx/Error interrupts */
	__enable_irqn(MFS3_RX_IRQn);
	__enable_irqn(MFS3_TX_IRQn);
}

#endif



#if USE_UART4

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART4_TXB];
} TxFifo4;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART4_RXB];
} RxFifo4;


void MFS4_TX_IRQHandler (void)
{
	uint16_t i, n;


	n = TxFifo4.ct;
	if (n) {		/* There is one or more byte in the Tx buffer */
		TxFifo4.ct = --n;
		i = TxFifo4.ri;
		MFS4_TDR = TxFifo4.buff[i++];
		TxFifo4.ri = i % UART4_TXB;
	}
	if (!n) MFS4_SCR &= ~0x08;	/* Clear TIE (disable Tx ready irq if no data to transmit) */
}


void MFS4_RX_IRQHandler (void)
{
	uint8_t d;
	uint16_t i, n;


	if (MFS4_SSR & 0x38) {	/* Error occured */
		MFS4_SSR = 0x80;
	}

	if (MFS4_SSR & 0x04) {	/* Data arrived */
		d = MFS4_RDR;	/* Get received data */
		n = RxFifo4.ct;
		if (n < UART4_RXB) {	/* Store it into the Rx buffer if not full */
			RxFifo4.ct = ++n;
			i = RxFifo4.wi;
			RxFifo4.buff[i++] = d;
			RxFifo4.wi = i % UART4_RXB;
		}
	}

}


int uart4_test (void)	/* 0:Empty, >0:Not empty */
{
	return RxFifo4.ct;
}


uint8_t uart4_getc (void)
{
	uint8_t d;
	uint16_t i;

	/* Wait for Rx FIFO ready */
	while (!RxFifo4.ct) ;

	i = RxFifo4.ri;
	d = RxFifo4.buff[i++];
	RxFifo4.ri = i % UART4_RXB;
	__disable_irq();
	RxFifo4.ct--;
	__enable_irq();

	return d;
}


void uart4_putc (uint8_t d)
{
	uint16_t i, n;

	/* Wait for Tx FIFO ready */
	while (TxFifo4.ct >= UART4_TXB) ;

	i = TxFifo4.wi;
	TxFifo4.buff[i++] = d;	/* Put a byte into Tx byffer */
	TxFifo4.wi = i % UART4_TXB;
	__disable_irq();
	TxFifo4.ct++;
	MFS4_SCR |= 0x08;	/* Set TIE (enable TX ready irq) */
	__enable_irq();
}


void uart4_init (void)
{
	__disable_irqn(MFS4_RX_IRQn);
	__disable_irqn(MFS4_TX_IRQn);

	/* Initialize MFS (UART mode, N81)*/
	MFS4_SCR = 0x80;		/* Disable MFS */
	MFS4_SMR = 0x01;		/* Enable SOT output */
	MFS4_ESCR = 0;
	MFS4_BGR = F_PCLK / UART4_BPS - 1;
	MFS4_SCR = 0x13;		/* Enable MFS: Set RIE/RXE/TXE */

	/* Clear Tx/Rx buffers */
	TxFifo4.ri = 0; TxFifo4.wi = 0; TxFifo4.ct = 0;
	RxFifo4.ri = 0; RxFifo4.wi = 0; RxFifo4.ct = 0;

	/* Attach MFS module to I/O pads */
#if   UART4_LOC == 0
	EPFR08 = (EPFR08 & ~(15 << 4)) | (4 << 4);
	PFRD |= 3 << 1;
#elif UART4_LOC == 1
	EPFR08 = (EPFR08 & ~(15 << 4)) | (10 << 4);
	PFR1 |= 3 << 10;
#elif UART4_LOC == 2
	EPFR08 = (EPFR08 & ~(15 << 4)) | (15 << 4);
	PFR0 |= 3 << 5;
#endif

	/* Enable Tx/Rx/Error interrupts */
	__enable_irqn(MFS4_RX_IRQn);
	__enable_irqn(MFS4_TX_IRQn);
}

#endif



#if USE_UART5

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART5_TXB];
} TxFifo5;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART5_RXB];
} RxFifo5;


void MFS5_TX_IRQHandler (void)
{
	uint16_t i, n;


	n = TxFifo5.ct;
	if (n) {		/* There is one or more byte in the Tx buffer */
		TxFifo5.ct = --n;
		i = TxFifo5.ri;
		MFS5_TDR = TxFifo5.buff[i++];
		TxFifo5.ri = i % UART5_TXB;
	}
	if (!n) MFS5_SCR &= ~0x08;	/* Clear TIE (disable Tx ready irq if no data to transmit) */
}


void MFS5_RX_IRQHandler (void)
{
	uint8_t d;
	uint16_t i, n;


	if (MFS5_SSR & 0x38) {	/* Error occured */
		MFS5_SSR = 0x80;
	}

	if (MFS5_SSR & 0x04) {	/* Data arrived */
		d = MFS5_RDR;	/* Get received data */
		n = RxFifo5.ct;
		if (n < UART5_RXB) {	/* Store it into the Rx buffer if not full */
			RxFifo5.ct = ++n;
			i = RxFifo5.wi;
			RxFifo5.buff[i++] = d;
			RxFifo5.wi = i % UART5_RXB;
		}
	}

}


int uart5_test (void)	/* 0:Empty, >0:Not empty */
{
	return RxFifo5.ct;
}


uint8_t uart5_getc (void)
{
	uint8_t d;
	uint16_t i;

	/* Wait for Rx FIFO ready */
	while (!RxFifo5.ct) ;

	i = RxFifo5.ri;
	d = RxFifo5.buff[i++];
	RxFifo5.ri = i % UART5_RXB;
	__disable_irq();
	RxFifo5.ct--;
	__enable_irq();

	return d;
}


void uart5_putc (uint8_t d)
{
	uint16_t i, n;

	/* Wait for Tx FIFO ready */
	while (TxFifo5.ct >= UART5_TXB) ;

	i = TxFifo5.wi;
	TxFifo5.buff[i++] = d;	/* Put a byte into Tx byffer */
	TxFifo5.wi = i % UART5_TXB;
	__disable_irq();
	TxFifo5.ct++;
	MFS5_SCR |= 0x08;	/* Set TIE (enable TX ready irq) */
	__enable_irq();
}


void uart5_init (void)
{
	__disable_irqn(MFS5_RX_IRQn);
	__disable_irqn(MFS5_TX_IRQn);

	/* Initialize MFS (UART mode, N81)*/
	MFS5_SCR = 0x80;		/* Disable MFS */
	MFS5_SMR = 0x01;		/* Enable SOT output */
	MFS5_ESCR = 0;
	MFS5_BGR = F_PCLK / UART5_BPS - 1;
	MFS5_SCR = 0x13;		/* Enable MFS: Set RIE/RXE/TXE */

	/* Clear Tx/Rx buffers */
	TxFifo5.ri = 0; TxFifo5.wi = 0; TxFifo5.ct = 0;
	RxFifo5.ri = 0; RxFifo5.wi = 0; RxFifo5.ct = 0;

	/* Attach MFS module to I/O pads */
#if   UART5_LOC == 0
	EPFR08 = (EPFR08 & ~(15 << 10)) | (4 << 10);
	PFR6 |= 3 << 0;
#elif UART5_LOC == 1
	EPFR08 = (EPFR08 & ~(15 << 10)) | (10 << 10);
	PFR9 |= 3 << 2;
#elif UART5_LOC == 2
	EPFR08 = (EPFR08 & ~(15 << 10)) | (15 << 10);
	PFR3 |= 3 << 6;
#endif

	/* Enable Tx/Rx/Error interrupts */
	__enable_irqn(MFS5_RX_IRQn);
	__enable_irqn(MFS5_TX_IRQn);
}

#endif



#if USE_UART6

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART6_TXB];
} TxFifo6;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART6_RXB];
} RxFifo6;


void MFS6_TX_IRQHandler (void)
{
	uint16_t i, n;


	n = TxFifo6.ct;
	if (n) {		/* There is one or more byte in the Tx buffer */
		TxFifo6.ct = --n;
		i = TxFifo6.ri;
		MFS6_TDR = TxFifo6.buff[i++];
		TxFifo6.ri = i % UART6_TXB;
	}
	if (!n) MFS6_SCR &= ~0x08;	/* Clear TIE (disable Tx ready irq if no data to transmit) */
}


void MFS6_RX_IRQHandler (void)
{
	uint8_t d;
	uint16_t i, n;


	if (MFS6_SSR & 0x38) {	/* Error occured */
		MFS6_SSR = 0x80;
	}

	if (MFS6_SSR & 0x04) {	/* Data arrived */
		d = MFS6_RDR;	/* Get received data */
		n = RxFifo6.ct;
		if (n < UART6_RXB) {	/* Store it into the Rx buffer if not full */
			RxFifo6.ct = ++n;
			i = RxFifo6.wi;
			RxFifo6.buff[i++] = d;
			RxFifo6.wi = i % UART6_RXB;
		}
	}

}


int uart6_test (void)	/* 0:Empty, >0:Not empty */
{
	return RxFifo6.ct;
}


uint8_t uart6_getc (void)
{
	uint8_t d;
	uint16_t i;

	/* Wait for Rx FIFO ready */
	while (!RxFifo6.ct) ;

	i = RxFifo6.ri;
	d = RxFifo6.buff[i++];
	RxFifo6.ri = i % UART6_RXB;
	__disable_irq();
	RxFifo6.ct--;
	__enable_irq();

	return d;
}


void uart6_putc (uint8_t d)
{
	uint16_t i, n;

	/* Wait for Tx FIFO ready */
	while (TxFifo6.ct >= UART6_TXB) ;

	i = TxFifo6.wi;
	TxFifo6.buff[i++] = d;	/* Put a byte into Tx byffer */
	TxFifo6.wi = i % UART6_TXB;
	__disable_irq();
	TxFifo6.ct++;
	MFS6_SCR |= 0x08;	/* Set TIE (enable TX ready irq) */
	__enable_irq();
}


void uart6_init (void)
{
	__disable_irqn(MFS6_RX_IRQn);
	__disable_irqn(MFS6_TX_IRQn);

	/* Initialize MFS (UART mode, N81)*/
	MFS6_SCR = 0x80;		/* Disable MFS */
	MFS6_SMR = 0x01;		/* Enable SOT output */
	MFS6_ESCR = 0;
	MFS6_BGR = F_PCLK / UART6_BPS - 1;
	MFS6_SCR = 0x13;		/* Enable MFS: Set RIE/RXE/TXE */

	/* Clear Tx/Rx buffers */
	TxFifo6.ri = 0; TxFifo6.wi = 0; TxFifo6.ct = 0;
	RxFifo6.ri = 0; RxFifo6.wi = 0; RxFifo6.ct = 0;

	/* Attach MFS module to I/O pads */
#if   UART6_LOC == 0
	EPFR08 = (EPFR08 & ~(15 << 16)) | (4 << 16);
	PFR5 |= 3 << 3;
#elif UART6_LOC == 1
	EPFR08 = (EPFR08 & ~(15 << 16)) | (10 << 16);
	PFR3 |= 3 << 2;
#elif UART6_LOC == 2
	EPFR08 = (EPFR08 & ~(15 << 16)) | (15 << 16);
	PFRF |= 3 << 3;
#endif

	/* Enable Tx/Rx/Error interrupts */
	__enable_irqn(MFS6_RX_IRQn);
	__enable_irqn(MFS6_TX_IRQn);
}

#endif



#if USE_UART7

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART7_TXB];
} TxFifo7;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART7_RXB];
} RxFifo7;


void MFS7_TX_IRQHandler (void)
{
	uint16_t i, n;


	n = TxFifo7.ct;
	if (n) {		/* There is one or more byte in the Tx buffer */
		TxFifo7.ct = --n;
		i = TxFifo7.ri;
		MFS7_TDR = TxFifo7.buff[i++];
		TxFifo7.ri = i % UART7_TXB;
	}
	if (!n) MFS7_SCR &= ~0x08;	/* Clear TIE (disable Tx ready irq if no data to transmit) */
}


void MFS7_RX_IRQHandler (void)
{
	uint8_t d;
	uint16_t i, n;


	if (MFS7_SSR & 0x38) {	/* Error occured */
		MFS7_SSR = 0x80;
	}

	if (MFS7_SSR & 0x04) {	/* Data arrived */
		d = MFS7_RDR;	/* Get received data */
		n = RxFifo7.ct;
		if (n < UART7_RXB) {	/* Store it into the Rx buffer if not full */
			RxFifo7.ct = ++n;
			i = RxFifo7.wi;
			RxFifo7.buff[i++] = d;
			RxFifo7.wi = i % UART7_RXB;
		}
	}

}


int uart7_test (void)	/* 0:Empty, >0:Not empty */
{
	return RxFifo7.ct;
}


uint8_t uart7_getc (void)
{
	uint8_t d;
	uint16_t i;

	/* Wait for Rx FIFO ready */
	while (!RxFifo7.ct) ;

	i = RxFifo7.ri;
	d = RxFifo7.buff[i++];
	RxFifo7.ri = i % UART7_RXB;
	__disable_irq();
	RxFifo7.ct--;
	__enable_irq();

	return d;
}


void uart7_putc (uint8_t d)
{
	uint16_t i, n;

	/* Wait for Tx FIFO ready */
	while (TxFifo7.ct >= UART7_TXB) ;

	i = TxFifo7.wi;
	TxFifo7.buff[i++] = d;	/* Put a byte into Tx byffer */
	TxFifo7.wi = i % UART7_TXB;
	__disable_irq();
	TxFifo7.ct++;
	MFS7_SCR |= 0x08;	/* Set TIE (enable TX ready irq) */
	__enable_irq();
}


void uart7_init (void)
{
	__disable_irqn(MFS7_RX_IRQn);
	__disable_irqn(MFS7_TX_IRQn);

	/* Initialize MFS (UART mode, N81)*/
	MFS7_SCR = 0x80;		/* Disable MFS */
	MFS7_SMR = 0x01;		/* Enable SOT output */
	MFS7_ESCR = 0;
	MFS7_BGR = F_PCLK / UART7_BPS - 1;
	MFS7_SCR = 0x13;		/* Enable MFS: Set RIE/RXE/TXE */

	/* Clear Tx/Rx buffers */
	TxFifo7.ri = 0; TxFifo7.wi = 0; TxFifo7.ct = 0;
	RxFifo7.ri = 0; RxFifo7.wi = 0; RxFifo7.ct = 0;

	/* Attach MFS module to I/O pads */
#if   UART7_LOC == 0
	EPFR08 = (EPFR08 & ~(15 << 22)) | (4 << 22);
	PFR5 |= 3 << 9; 
#elif UART7_LOC == 1
	EPFR08 = (EPFR08 & ~(15 << 22)) | (10 << 22);
	PFR4 |= 3 << 13;
#elif UART7_LOC == 2
	EPFR08 = (EPFR08 & ~(15 << 22)) | (15 << 22);
	PFRB |= 3 << 0;
#endif

	/* Enable Tx/Rx/Error interrupts */
	__enable_irqn(MFS7_RX_IRQn);
	__enable_irqn(MFS7_TX_IRQn);
}

#endif
