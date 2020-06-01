/*------------------------------------------------------------------------/
/  LPC178x UART control module
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

#include "uart178x.h"

/* F_PCLK    8/16M  9/18M 10/20M 12/24M 12.5/25M 15/30M */
/* DIVADD       1     5      1      1      1       5    */
/* MULVAL      12     8     12     12      8       8    */
/* Error[%]   0.15  0.16   0.15   0.15   0.47    0.16   */

#define F_PCLK		30000000	/* PCLK frequency for the UART module */
#define	DIVADD		5			/* See below */
#define	MULVAL		8

#define	DLVAL0		((uint32_t)((double)F_PCLK / UART0_BPS / 16 / (1 + (double)DIVADD / MULVAL)))
#define	DLVAL1		((uint32_t)((double)F_PCLK / UART1_BPS / 16 / (1 + (double)DIVADD / MULVAL)))
#define	DLVAL2		((uint32_t)((double)F_PCLK / UART2_BPS / 16 / (1 + (double)DIVADD / MULVAL)))
#define	DLVAL3		((uint32_t)((double)F_PCLK / UART3_BPS / 16 / (1 + (double)DIVADD / MULVAL)))
#define	DLVAL4		((uint32_t)((double)F_PCLK / UART4_BPS / 16 / (1 + (double)DIVADD / MULVAL)))



#if USE_UART0

static volatile struct {
	uint16_t	ri, wi, ct, act;
	uint8_t		buff[UART0_TXB];
} TxBuff0;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART0_RXB];
} RxBuff0;

void UART0_IRQHandler (void)
{
	uint8_t iir, d;
	int i, cnt;


	for (;;) {
		iir = U0IIR;			/* Get interrupt ID */
		if (iir & 1) break;		/* Exit if there is no interrupt */
		switch (iir & 7) {
		case 4:			/* Rx FIFO is half filled or timeout occured */
			i = RxBuff0.wi;
			cnt = RxBuff0.ct;
			while (U0LSR & 0x01) {	/* Get all data in the Rx FIFO */
				d = U0RBR;
				if (cnt < UART0_RXB) {	/* Store data if Rx buffer is not full */
					RxBuff0.buff[i++] = d;
					i %= UART0_RXB;
					cnt++;
				}
			}
			RxBuff0.wi = i;
			RxBuff0.ct = cnt;
			break;

		case 2:			/* Tx FIFO empty */
			cnt = TxBuff0.ct;
			if (cnt) {		/* There is one or more byte to send */
				i = TxBuff0.ri;
				for (d = 16; d && cnt; d--, cnt--) {	/* Fill Tx FIFO */
					U0THR = TxBuff0.buff[i++];
					i %= UART0_TXB;
				}
				TxBuff0.ri = i;
				TxBuff0.ct = cnt;
			} else {
				TxBuff0.act = 0; /* When no data to send, next putc must trigger Tx sequense */
			}
			break;

		default:		/* Data error or break detected */
			U0LSR;
			U0RBR;
			break;
		}
	}
}


int uart0_test (void)
{
	return RxBuff0.ct;
}


uint8_t uart0_getc (void)
{
	uint8_t d;
	int i;

	/* Wait while Rx buffer is empty */
	while (!RxBuff0.ct) ;

	i = RxBuff0.ri;			/* Get a byte from Rx buffer */
	d = RxBuff0.buff[i++];
	RxBuff0.ri = i % UART0_RXB;
	__disable_irq();
	RxBuff0.ct--;
	__enable_irq();

	return d;
}


void uart0_putc (uint8_t d)
{
	int i;

	/* Wait for Tx buffer ready */
	while (TxBuff0.ct >= UART0_TXB) ;

	__disable_irq();
	if (TxBuff0.act) {
		i = TxBuff0.wi;		/* Put a byte into Tx byffer */
		TxBuff0.buff[i++] = d;
		TxBuff0.wi = i % UART0_TXB;
		TxBuff0.ct++;
	} else {
		U0THR = d;		/* Trigger Tx sequense */
		TxBuff0.act = 1;
	}
	__enable_irq();
}


void uart0_init (void)
{
	__disable_irqn(UART0_IRQn);

	/* Enable UART0 module */
	__set_PCONP(PCUART0, 1);

	/* Initialize UART */
	U0LCR = 0x83;			/* Select baud rate divisor latch */
	U0DLM = DLVAL0 / 256;	/* Set BRG dividers */
	U0DLL = DLVAL0 % 256;
	U0FDR = (MULVAL << 4) | DIVADD;
	U0LCR = 0x03;			/* Set serial format N81 and deselect divisor latch */
	U0FCR = 0x87;			/* Enable FIFO */
	U0TER = 0x80;			/* Enable Tansmission */

	/* Clear Tx/Rx buffers */
	TxBuff0.ri = 0; TxBuff0.wi = 0; TxBuff0.ct = 0; TxBuff0.act = 0;
	RxBuff0.ri = 0; RxBuff0.wi = 0; RxBuff0.ct = 0;

	/* Attach UART0 to I/O pad */
	IOCON_P0[3] = 0x031;	/* P0.3: RXD0 */\
	IOCON_P0[2] = 0x001;	/* P0.2: TXD0 */\

	/* Enable Tx/Rx/Error interrupts */
	U0IER = 0x07;
	__enable_irqn(UART0_IRQn);
}

#endif	/* USE_UART0 */



#if USE_UART1

static volatile struct {
	uint16_t	ri, wi, ct, act;
	uint8_t		buff[UART1_TXB];
} TxBuff1;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART1_RXB];
} RxBuff1;

void UART1_IRQHandler (void)
{
	uint8_t iir, d;
	int i, cnt;


	for (;;) {
		iir = U1IIR;			/* Get interrupt ID */
		if (iir & 1) break;		/* Exit if there is no interrupt */
		switch (iir & 7) {
		case 4:			/* Rx FIFO is half filled or timeout occured */
			i = RxBuff1.wi;
			cnt = RxBuff1.ct;
			while (U1LSR & 0x01) {	/* Get all data in the Rx FIFO */
				d = U1RBR;
				if (cnt < UART1_RXB) {	/* Store data if Rx buffer is not full */
					RxBuff1.buff[i++] = d;
					i %= UART1_RXB;
					cnt++;
				}
			}
			RxBuff1.wi = i;
			RxBuff1.ct = cnt;
			break;

		case 2:			/* Tx FIFO empty */
			cnt = TxBuff1.ct;
			if (cnt) {		/* There is one or more byte to send */
				i = TxBuff1.ri;
				for (d = 16; d && cnt; d--, cnt--) {	/* Fill Tx FIFO */
					U1THR = TxBuff1.buff[i++];
					i %= UART1_TXB;
				}
				TxBuff1.ri = i;
				TxBuff1.ct = cnt;
			} else {
				TxBuff1.act = 0; /* When no data to send, next putc must trigger Tx sequense */
			}
			break;

		default:		/* Data error or break detected */
			U1LSR;
			U1RBR;
			break;
		}
	}
}


int uart1_test (void)
{
	return RxBuff1.ct;
}


uint8_t uart1_getc (void)
{
	uint8_t d;
	int i;

	/* Wait while Rx buffer is empty */
	while (!RxBuff1.ct) ;

	i = RxBuff1.ri;			/* Get a byte from Rx buffer */
	d = RxBuff1.buff[i++];
	RxBuff1.ri = i % UART1_RXB;
	__disable_irq();
	RxBuff1.ct--;
	__enable_irq();

	return d;
}


void uart1_putc (uint8_t d)
{
	int i;

	/* Wait for Tx buffer ready */
	while (TxBuff1.ct >= UART1_TXB) ;

	__disable_irq();
	if (TxBuff1.act) {
		i = TxBuff1.wi;		/* Put a byte into Tx byffer */
		TxBuff1.buff[i++] = d;
		TxBuff1.wi = i % UART1_TXB;
		TxBuff1.ct++;
	} else {
		U1THR = d;		/* Trigger Tx sequense */
		TxBuff1.act = 1;
	}
	__enable_irq();
}


void uart1_init (void)
{
	__disable_irqn(UART1_IRQn);

	/* Enable UART1 module */
	__set_PCONP(PCUART1, 1);

	/* Initialize UART */
	U1LCR = 0x83;			/* Select baud rate divisor latch */
	U1DLM = DLVAL1 / 256;	/* Set BRG dividers */
	U1DLL = DLVAL1 % 256;
	U1FDR = (MULVAL << 4) | DIVADD;
	U1LCR = 0x03;			/* Set serial format N81 and deselect divisor latch */
	U1FCR = 0x87;			/* Enable FIFO */
	U1TER = 0x80;			/* Enable Tansmission */

	/* Clear Tx/Rx buffers */
	TxBuff1.ri = 0; TxBuff1.wi = 0; TxBuff1.ct = 0; TxBuff1.act = 0;
	RxBuff1.ri = 0; RxBuff1.wi = 0; RxBuff1.ct = 0;

	/* Attach UART1 to I/O pad */
	IOCON_P0[16] = 0x031;	/* P0.16: RXD1 */\
	IOCON_P0[15] = 0x001;	/* P0.15: TXD1 */\

	/* Enable Tx/Rx/Error interrupts */
	U1IER = 0x07;
	__enable_irqn(UART1_IRQn);
}

#endif	/* USE_UART1 */



#if USE_UART2

static volatile struct {
	uint16_t	ri, wi, ct, act;
	uint8_t		buff[UART2_TXB];
} TxBuff2;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART2_RXB];
} RxBuff2;

void UART2_IRQHandler (void)
{
	uint8_t iir, d;
	int i, cnt;


	for (;;) {
		iir = U2IIR;			/* Get interrupt ID */
		if (iir & 1) break;		/* Exit if there is no interrupt */
		switch (iir & 7) {
		case 4:			/* Rx FIFO is half filled or timeout occured */
			i = RxBuff2.wi;
			cnt = RxBuff2.ct;
			while (U2LSR & 0x01) {	/* Get all data in the Rx FIFO */
				d = U2RBR;
				if (cnt < UART2_RXB) {	/* Store data if Rx buffer is not full */
					RxBuff2.buff[i++] = d;
					i %= UART2_RXB;
					cnt++;
				}
			}
			RxBuff2.wi = i;
			RxBuff2.ct = cnt;
			break;

		case 2:			/* Tx FIFO empty */
			cnt = TxBuff2.ct;
			if (cnt) {		/* There is one or more byte to send */
				i = TxBuff2.ri;
				for (d = 16; d && cnt; d--, cnt--) {	/* Fill Tx FIFO */
					U2THR = TxBuff2.buff[i++];
					i %= UART2_TXB;
				}
				TxBuff2.ri = i;
				TxBuff2.ct = cnt;
			} else {
				TxBuff2.act = 0; /* When no data to send, next putc must trigger Tx sequense */
			}
			break;

		default:		/* Data error or break detected */
			U2LSR;
			U2RBR;
			break;
		}
	}
}


int uart2_test (void)
{
	return RxBuff2.ct;
}


uint8_t uart2_getc (void)
{
	uint8_t d;
	int i;

	/* Wait while Rx buffer is empty */
	while (!RxBuff2.ct) ;

	i = RxBuff2.ri;			/* Get a byte from Rx buffer */
	d = RxBuff2.buff[i++];
	RxBuff2.ri = i % UART2_RXB;
	__disable_irq();
	RxBuff2.ct--;
	__enable_irq();

	return d;
}


void uart2_putc (uint8_t d)
{
	int i;

	/* Wait for Tx buffer ready */
	while (TxBuff2.ct >= UART2_TXB) ;

	__disable_irq();
	if (TxBuff2.act) {
		i = TxBuff2.wi;		/* Put a byte into Tx byffer */
		TxBuff2.buff[i++] = d;
		TxBuff2.wi = i % UART2_TXB;
		TxBuff2.ct++;
	} else {
		U2THR = d;		/* Trigger Tx sequense */
		TxBuff2.act = 1;
	}
	__enable_irq();
}


void uart2_init (void)
{
	__disable_irqn(UART2_IRQn);

	/* Enable UART2 module */
	__set_PCONP(PCUART2, 1);

	/* Initialize UART */
	U2LCR = 0x83;			/* Select baud rate divisor latch */
	U2DLM = DLVAL2 / 256;	/* Set BRG dividers */
	U2DLL = DLVAL2 % 256;
	U2FDR = (MULVAL << 4) | DIVADD;
	U2LCR = 0x03;			/* Set serial format N81 and deselect divisor latch */
	U2FCR = 0x87;			/* Enable FIFO */
	U2TER = 0x80;			/* Enable Tansmission */

	/* Clear Tx/Rx buffers */
	TxBuff2.ri = 0; TxBuff2.wi = 0; TxBuff2.ct = 0; TxBuff2.act = 0;
	RxBuff2.ri = 0; RxBuff2.wi = 0; RxBuff2.ct = 0;

	/* Attach UART2 to I/O pad */
	IOCON_P0[11] = 0x031;	/* P0.11: RXD2 */\
	IOCON_P0[10] = 0x001;	/* P0.10: TXD2 */\

	/* Enable Tx/Rx/Error interrupts */
	U2IER = 0x07;
	__enable_irqn(UART2_IRQn);
}

#endif	/* USE_UART2 */



#if USE_UART3

static volatile struct {
	uint16_t	ri, wi, ct, act;
	uint8_t		buff[UART3_TXB];
} TxBuff3;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART3_RXB];
} RxBuff3;

void UART3_IRQHandler (void)
{
	uint8_t iir, d;
	int i, cnt;


	for (;;) {
		iir = U3IIR;			/* Get interrupt ID */
		if (iir & 1) break;		/* Exit if there is no interrupt */
		switch (iir & 7) {
		case 4:			/* Rx FIFO is half filled or timeout occured */
			i = RxBuff3.wi;
			cnt = RxBuff3.ct;
			while (U3LSR & 0x01) {	/* Get all data in the Rx FIFO */
				d = U3RBR;
				if (cnt < UART3_RXB) {	/* Store data if Rx buffer is not full */
					RxBuff3.buff[i++] = d;
					i %= UART3_RXB;
					cnt++;
				}
			}
			RxBuff3.wi = i;
			RxBuff3.ct = cnt;
			break;

		case 2:			/* Tx FIFO empty */
			cnt = TxBuff3.ct;
			if (cnt) {		/* There is one or more byte to send */
				i = TxBuff3.ri;
				for (d = 16; d && cnt; d--, cnt--) {	/* Fill Tx FIFO */
					U3THR = TxBuff3.buff[i++];
					i %= UART3_TXB;
				}
				TxBuff3.ri = i;
				TxBuff3.ct = cnt;
			} else {
				TxBuff3.act = 0; /* When no data to send, next putc must trigger Tx sequense */
			}
			break;

		default:		/* Data error or break detected */
			U3LSR;
			U3RBR;
			break;
		}
	}
}


int uart3_test (void)
{
	return RxBuff3.ct;
}


uint8_t uart3_getc (void)
{
	uint8_t d;
	int i;

	/* Wait while Rx buffer is empty */
	while (!RxBuff3.ct) ;

	i = RxBuff3.ri;			/* Get a byte from Rx buffer */
	d = RxBuff3.buff[i++];
	RxBuff3.ri = i % UART3_RXB;
	__disable_irq();
	RxBuff3.ct--;
	__enable_irq();

	return d;
}


void uart3_putc (uint8_t d)
{
	int i;

	/* Wait for Tx buffer ready */
	while (TxBuff3.ct >= UART3_TXB) ;

	__disable_irq();
	if (TxBuff3.act) {
		i = TxBuff3.wi;		/* Put a byte into Tx byffer */
		TxBuff3.buff[i++] = d;
		TxBuff3.wi = i % UART3_TXB;
		TxBuff3.ct++;
	} else {
		U3THR = d;		/* Trigger Tx sequense */
		TxBuff3.act = 1;
	}
	__enable_irq();
}


void uart3_init (void)
{
	__disable_irqn(UART3_IRQn);

	/* Enable UART3 module */
	__set_PCONP(PCUART3, 1);

	/* Initialize UART */
	U3LCR = 0x83;			/* Select baud rate divisor latch */
	U3DLM = DLVAL3 / 256;	/* Set BRG dividers */
	U3DLL = DLVAL3 % 256;
	U3FDR = (MULVAL << 4) | DIVADD;
	U3LCR = 0x03;			/* Set serial format N81 and deselect divisor latch */
	U3FCR = 0x87;			/* Enable FIFO */
	U3TER = 0x80;			/* Enable Tansmission */

	/* Clear Tx/Rx buffers */
	TxBuff3.ri = 0; TxBuff3.wi = 0; TxBuff3.ct = 0; TxBuff3.act = 0;
	RxBuff3.ri = 0; RxBuff3.wi = 0; RxBuff3.ct = 0;

	/* Attach UART3 to I/O pad */
	IOCON_P4[29] = 0x032;	/* P4.29: RXD3 */\
	IOCON_P4[28] = 0x002;	/* P4.28: TXD3 */\

	/* Enable Tx/Rx/Error interrupts */
	U3IER = 0x07;
	__enable_irqn(UART3_IRQn);
}

#endif	/* USE_UART3 */



#if USE_UART4

static volatile struct {
	uint16_t	ri, wi, ct, act;
	uint8_t		buff[UART4_TXB];
} TxBuff4;

static volatile struct {
	uint16_t	ri, wi, ct;
	uint8_t		buff[UART4_RXB];
} RxBuff4;

void UART4_IRQHandler (void)
{
	uint8_t iir, d;
	int i, cnt;


	for (;;) {
		iir = U4IIR;			/* Get interrupt ID */
		if (iir & 1) break;		/* Exit if there is no interrupt */
		switch (iir & 7) {
		case 4:			/* Rx FIFO is half filled or timeout occured */
			i = RxBuff4.wi;
			cnt = RxBuff4.ct;
			while (U4LSR & 0x01) {	/* Get all data in the Rx FIFO */
				d = U4RBR;
				if (cnt < UART4_RXB) {	/* Store data if Rx buffer is not full */
					RxBuff4.buff[i++] = d;
					i %= UART4_RXB;
					cnt++;
				}
			}
			RxBuff4.wi = i;
			RxBuff4.ct = cnt;
			break;

		case 2:			/* Tx FIFO empty */
			cnt = TxBuff4.ct;
			if (cnt) {		/* There is one or more byte to send */
				i = TxBuff4.ri;
				for (d = 16; d && cnt; d--, cnt--) {	/* Fill Tx FIFO */
					U4THR = TxBuff4.buff[i++];
					i %= UART4_TXB;
				}
				TxBuff4.ri = i;
				TxBuff4.ct = cnt;
			} else {
				TxBuff4.act = 0; /* When no data to send, next putc must trigger Tx sequense */
			}
			break;

		default:		/* Data error or break detected */
			U4LSR;
			U4RBR;
			break;
		}
	}
}


int uart4_test (void)
{
	return RxBuff4.ct;
}


uint8_t uart4_getc (void)
{
	uint8_t d;
	int i;

	/* Wait while Rx buffer is empty */
	while (!RxBuff4.ct) ;

	i = RxBuff4.ri;			/* Get a byte from Rx buffer */
	d = RxBuff4.buff[i++];
	RxBuff4.ri = i % UART4_RXB;
	__disable_irq();
	RxBuff4.ct--;
	__enable_irq();

	return d;
}


void uart4_putc (uint8_t d)
{
	int i;

	/* Wait for Tx buffer ready */
	while (TxBuff4.ct >= UART4_TXB) ;

	__disable_irq();
	if (TxBuff4.act) {
		i = TxBuff4.wi;		/* Put a byte into Tx byffer */
		TxBuff4.buff[i++] = d;
		TxBuff4.wi = i % UART4_TXB;
		TxBuff4.ct++;
	} else {
		U4THR = d;		/* Trigger Tx sequense */
		TxBuff4.act = 1;
	}
	__enable_irq();
}


void uart4_init (void)
{
	__disable_irqn(UART4_IRQn);

	/* Enable UART4 module */
	__set_PCONP(PCUART4, 1);

	/* Initialize UART */
	U4LCR = 0x83;			/* Select baud rate divisor latch */
	U4DLM = DLVAL4 / 256;	/* Set BRG dividers */
	U4DLL = DLVAL4 % 256;
	U4FDR = (MULVAL << 4) | DIVADD;
	U4LCR = 0x03;			/* Set serial format N81 and deselect divisor latch */
	U4FCR = 0x87;			/* Enable FIFO */
	U4TER = 0x80;			/* Enable Tansmission */

	/* Clear Tx/Rx buffers */
	TxBuff4.ri = 0; TxBuff4.wi = 0; TxBuff4.ct = 0; TxBuff4.act = 0;
	RxBuff4.ri = 0; RxBuff4.wi = 0; RxBuff4.ct = 0;

	/* Attach UART4 to I/O pad */
	IOCON_P2[9] = 0x033;	/* P2.9: RXD4 */\
	IOCON_P0[22] = 0x003;	/* P0.22: TXD4 */\

	/* Enable Tx/Rx/Error interrupts */
	U4IER = 0x07;
	__enable_irqn(UART4_IRQn);
}

#endif	/* USE_UART4 */


