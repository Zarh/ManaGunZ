/*------------------------------------------------------------------------*/
/* FRK-RX62N: SCI in UART control module                                  */
/*------------------------------------------------------------------------*/
/*
/  Copyright (C) 2016, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/


#define F_PCLK		96000000UL	/* PCLK frequency (configured by SCKCR.PCK) */

#define USE_SCI0	0	/* Use SCI0 */
#define TXBUF0		128	/* Tx FIFO size [byte]	*/
#define RXBUF0		128	/* Rx FIFO size [byte]	*/

#define USE_SCI1	1	/* Use SCI1 */
#define TXBUF1		128	/* Tx FIFO size [byte]	*/
#define RXBUF1		128	/* Rx FIFO size [byte]	*/

#define USE_SCI2	0	/* Use SCI2 */
#define TXBUF2		128	/* Tx FIFO size [byte]	*/
#define RXBUF2		128	/* Rx FIFO size [byte]	*/

#define USE_SCI3	0	/* Use SCI3 */
#define TXBUF3		128	/* Tx FIFO size [byte]	*/
#define RXBUF3		128	/* Rx FIFO size [byte]	*/


/*--------------------------------------------------*/


#include "iodefine.h"
#include "uart_sci.h"
#include "vect.h"

extern void delay_ms(unsigned int);	/* Defined in main.c */

#define IODLY() {ICU.IR[0].BYTE; ICU.IR[0].BYTE; ICU.IR[0].BYTE;}




#if USE_SCI0

static
volatile struct {
	uint16_t	rri, rwi, rct, tri, twi, tct, run;
	uint8_t		rbuf[RXBUF0], tbuf[TXBUF0];
} Fifo0;



/* Initialize SCI */

void uart0_init (
	uint32_t bps,
	const char* fmt
)
{
	uint32_t f, d;

	/* Attach SCI0 to I/O pad */
	MSTP_SCI0 = 0;
	PORT2.ICR.BIT.B1 = 1;

	SCI0.SCR.BYTE = 0;
	f = 0;							/* CM=0, CHR=0, PE=0, PM=0, STOP=0, MP=0, CKS=0 */
	if (fmt[0] == 'o') f |= 0x30;	/* PE=1, PM=1 */
	if (fmt[0] == 'e') f |= 0x20;	/* PE=1 */
	if (fmt[1] == '7') f |= 0x40;	/* CHR=1 */
	if (fmt[2] == '2') f |= 0x08;	/* STOP=1 */
	d = F_PCLK / 32 / bps - 1;
	if (d >= 256) {
		d /= 4; f |= 1;	/* CKS0=1 */
	}
	SCI0.SMR.BYTE = f;
	SCI0.BRR = d;
	delay_ms(2);
	SCI0.SCR.BYTE = 0xF0;		/* Start SCI (TIE=1,RIE=1,TE=1,RE=1) */

	/* Clear Tx/Rx Buffer */
	Fifo0.tri = 0; Fifo0.twi = 0; Fifo0.tct = 0; Fifo0.run = 0;
	Fifo0.rri = 0; Fifo0.rwi = 0; Fifo0.rct = 0;

	/* Enable SCI interrupts */
	IPR(SCI0, ERI0) = 3; IEN(SCI0, ERI0) = 1;
	IPR(SCI0, RXI0) = 3; IEN(SCI0, RXI0) = 1;
	IPR(SCI0, TXI0) = 1; IEN(SCI0, TXI0) = 1;
}


/* Get number of bytes in the Rx Buffer */

int uart0_test (void)
{
	return Fifo0.rct;
}


/* Get a byte from Rx buffer */

uint8_t uart0_getc (void)
{
	uint8_t d;
	uint16_t i;


	while (!Fifo0.rct) ;		/* Wait for Rx data available */

	IEN(SCI0, RXI0) = 0; IEN(SCI0, ERI0) = 0;	/* Disable Rx Irq */
	IODLY();

	i = Fifo0.rri;
	d = Fifo0.rbuf[i++];		/* Get a byte from Rx buffer */
	Fifo0.rri = i % RXBUF0;
	Fifo0.rct--;

	IEN(SCI0, RXI0) = 1; IEN(SCI0, ERI0) = 1;	/* Enable Rx Irq */

	return d;
}


/* Put a byte into Tx buffer */

void uart0_putc (
	uint8_t dat
)
{
	uint16_t i;


	while (Fifo0.tct >= TXBUF0) ;	/* Wait for buffer ready */

	IEN(SCI0, TXI0) = 0;	/* Disable Tx Irq */
	IODLY();

	if (Fifo0.run) {
		i = Fifo0.twi;			/* Store the data into the Tx buffer */
		Fifo0.tbuf[i++] = dat;
		Fifo0.twi = i % TXBUF0;
		Fifo0.tct++;
	} else {
		Fifo0.run = 1;
		SCI0.TDR = dat;
	}

	IEN(SCI0, TXI0) = 1;	/* Enable Tx Irq */
}


/* RDR Ready ISR */

void Excep_SCI0_RXI0 (void)
{
	uint16_t i;
	uint8_t d;


	d = SCI0.RDR;	/* Get received byte */

	if (Fifo0.rct < RXBUF0) {	/* Store the byte if buffer is not full */
		i = Fifo0.rwi;
		Fifo0.rbuf[i++] = d;
		Fifo0.rwi = i % RXBUF0;
		Fifo0.rct++;
	}
}


/* Receive Error ISR */

void Excep_SCI0_ERI0 (void)
{
	/* Clear error status */
	SCI0.RDR;
	SCI0.SSR.BYTE = 0x84;
}


/* TDR ready ISR */

void Excep_SCI0_TXI0 (void)
{
	uint16_t i;


	if (Fifo0.tct) {	/* There is a data to be sent */
		i = Fifo0.tri;
		SCI0.TDR = Fifo0.tbuf[i++];
		Fifo0.tri = i % TXBUF0;
		Fifo0.tct--;
	} else {			/* No data to be sent */
		Fifo0.run = 0;
	}
}

#endif



#if USE_SCI1

static
volatile struct {
	uint16_t	rri, rwi, rct, tri, twi, tct, run;
	uint8_t		rbuf[RXBUF1], tbuf[TXBUF1];
} Fifo1;



/* Initialize SCI */

void uart1_init (
	uint32_t bps,
	const char* fmt
)
{
	uint32_t f, d;

	/* Attach SCI1 to I/O pad */
	MSTP_SCI1 = 0;
	PORT3.ICR.BIT.B0 = 1;

	SCI1.SCR.BYTE = 0;
	f = 0;							/* CM=0, CHR=0, PE=0, PM=0, STOP=0, MP=0, CKS=0 */
	if (fmt[0] == 'o') f |= 0x30;	/* PE=1, PM=1 */
	if (fmt[0] == 'e') f |= 0x20;	/* PE=1 */
	if (fmt[1] == '7') f |= 0x40;	/* CHR=1 */
	if (fmt[2] == '2') f |= 0x08;	/* STOP=1 */
	d = F_PCLK / 32 / bps - 1;
	if (d >= 256) {
		d /= 4; f |= 1;	/* CKS0=1 */
	}
	SCI1.SMR.BYTE = f;
	SCI1.BRR = d;
	delay_ms(2);
	SCI1.SCR.BYTE = 0xF0;		/* Start SCI (TIE=1,RIE=1,TE=1,RE=1) */

	/* Clear Tx/Rx Buffer */
	Fifo1.tri = 0; Fifo1.twi = 0; Fifo1.tct = 0; Fifo1.run = 0;
	Fifo1.rri = 0; Fifo1.rwi = 0; Fifo1.rct = 0;

	/* Enable SCI interrupts */
	IPR(SCI1, ERI1) = 3; IEN(SCI1, ERI1) = 1;
	IPR(SCI1, RXI1) = 3; IEN(SCI1, RXI1) = 1;
	IPR(SCI1, TXI1) = 1; IEN(SCI1, TXI1) = 1;
}


/* Get number of bytes in the Rx Buffer */

int uart1_test (void)
{
	return Fifo1.rct;
}


/* Get a byte from Rx buffer */

uint8_t uart1_getc (void)
{
	uint8_t d;
	uint16_t i;


	while (!Fifo1.rct) ;		/* Wait for Rx data available */

	IEN(SCI1, RXI1) = 0; IEN(SCI1, ERI1) = 0;	/* Disable Rx Irq */
	IODLY();

	i = Fifo1.rri;
	d = Fifo1.rbuf[i++];		/* Get a byte from Rx buffer */
	Fifo1.rri = i % RXBUF1;
	Fifo1.rct--;

	IEN(SCI1, RXI1) = 1; IEN(SCI1, ERI1) = 1;	/* Enable Rx Irq */

	return d;
}


/* Put a byte into Tx buffer */

void uart1_putc (
	uint8_t dat
)
{
	uint16_t i;


	while (Fifo1.tct >= TXBUF1) ;	/* Wait for buffer ready */

	IEN(SCI1, TXI1) = 0;	/* Disable Tx Irq */
	IODLY();

	if (Fifo1.run) {
		i = Fifo1.twi;			/* Store the data into the Tx buffer */
		Fifo1.tbuf[i++] = dat;
		Fifo1.twi = i % TXBUF1;
		Fifo1.tct++;
	} else {
		Fifo1.run = 1;
		SCI1.TDR = dat;
	}

	IEN(SCI1, TXI1) = 1;	/* Enable Tx Irq */
}


/* RDR Ready ISR */

void Excep_SCI1_RXI1 (void)
{
	uint16_t i;
	uint8_t d;


	d = SCI1.RDR;	/* Get received byte */

	if (Fifo1.rct < RXBUF1) {	/* Store the byte if buffer is not full */
		i = Fifo1.rwi;
		Fifo1.rbuf[i++] = d;
		Fifo1.rwi = i % RXBUF1;
		Fifo1.rct++;
	}
}


/* Receive Error ISR */

void Excep_SCI1_ERI1 (void)
{
	/* Clear error status */
	SCI1.RDR;
	SCI1.SSR.BYTE = 0x84;
}


/* TDR ready ISR */

void Excep_SCI1_TXI1 (void)
{
	uint16_t i;


	if (Fifo1.tct) {	/* There is a data to be sent */
		i = Fifo1.tri;
		SCI1.TDR = Fifo1.tbuf[i++];
		Fifo1.tri = i % TXBUF1;
		Fifo1.tct--;
	} else {			/* No data to be sent */
		Fifo1.run = 0;
	}
}

#endif



#if USE_SCI2

static
volatile struct {
	uint16_t	rri, rwi, rct, tri, twi, tct, run;
	uint8_t		rbuf[RXBUF2], tbuf[TXBUF2];
} Fifo2;



/* Initialize SCI */

void uart2_init (
	uint32_t bps,
	const char* fmt
)
{
	uint32_t f, d;

	/* Attach SCI2 to I/O pad */
	IOPORT.PFFSCI.BIT.SCI2S = 0;
	MSTP_SCI2 = 0;
	PORT1.ICR.BIT.B2 = 1;

	SCI2.SCR.BYTE = 0;
	f = 0;							/* CM=0, CHR=0, PE=0, PM=0, STOP=0, MP=0, CKS=0 */
	if (fmt[0] == 'o') f |= 0x30;	/* PE=1, PM=1 */
	if (fmt[0] == 'e') f |= 0x20;	/* PE=1 */
	if (fmt[1] == '7') f |= 0x40;	/* CHR=1 */
	if (fmt[2] == '2') f |= 0x08;	/* STOP=1 */
	d = F_PCLK / 32 / bps - 1;
	if (d >= 256) {
		d /= 4; f |= 1;	/* CKS0=1 */
	}
	SCI2.SMR.BYTE = f;
	SCI2.BRR = d;
	delay_ms(2);
	SCI2.SCR.BYTE = 0xF0;		/* Start SCI (TIE=1,RIE=1,TE=1,RE=1) */

	/* Clear Tx/Rx Buffer */
	Fifo2.tri = 0; Fifo2.twi = 0; Fifo2.tct = 0; Fifo2.run = 0;
	Fifo2.rri = 0; Fifo2.rwi = 0; Fifo2.rct = 0;

	/* Enable SCI interrupts */
	IPR(SCI2, ERI2) = 3; IEN(SCI2, ERI2) = 1;
	IPR(SCI2, RXI2) = 3; IEN(SCI2, RXI2) = 1;
	IPR(SCI2, TXI2) = 1; IEN(SCI2, TXI2) = 1;
}


/* Get number of bytes in the Rx Buffer */

int uart2_test (void)
{
	return Fifo2.rct;
}


/* Get a byte from Rx buffer */

uint8_t uart2_getc (void)
{
	uint8_t d;
	uint16_t i;


	while (!Fifo2.rct) ;		/* Wait for Rx data available */

	IEN(SCI2, RXI2) = 0; IEN(SCI2, ERI2) = 0;	/* Disable Rx Irq */
	IODLY();

	i = Fifo2.rri;
	d = Fifo2.rbuf[i++];		/* Get a byte from Rx buffer */
	Fifo2.rri = i % RXBUF2;
	Fifo2.rct--;

	IEN(SCI2, RXI2) = 1; IEN(SCI2, ERI2) = 1;	/* Enable Rx Irq */

	return d;
}


/* Put a byte into Tx buffer */

void uart2_putc (
	uint8_t dat
)
{
	uint16_t i;


	while (Fifo2.tct >= TXBUF2) ;	/* Wait for buffer ready */

	IEN(SCI2, TXI2) = 0;	/* Disable Tx Irq */
	IODLY();

	if (Fifo2.run) {
		i = Fifo2.twi;			/* Store the data into the Tx buffer */
		Fifo2.tbuf[i++] = dat;
		Fifo2.twi = i % TXBUF2;
		Fifo2.tct++;
	} else {
		Fifo2.run = 1;
		SCI2.TDR = dat;
	}

	IEN(SCI2, TXI2) = 1;	/* Enable Tx Irq */
}


/* RDR Ready ISR */

void Excep_SCI2_RXI2 (void)
{
	uint16_t i;
	uint8_t d;


	d = SCI2.RDR;	/* Get received byte */

	if (Fifo2.rct < RXBUF2) {	/* Store the byte if buffer is not full */
		i = Fifo2.rwi;
		Fifo2.rbuf[i++] = d;
		Fifo2.rwi = i % RXBUF2;
		Fifo2.rct++;
	}
}


/* Receive Error ISR */

void Excep_SCI2_ERI2 (void)
{
	/* Clear error status */
	SCI2.RDR;
	SCI2.SSR.BYTE = 0x84;
}


/* TDR ready ISR */

void Excep_SCI2_TXI2 (void)
{
	uint16_t i;


	if (Fifo2.tct) {	/* There is a data to be sent */
		i = Fifo2.tri;
		SCI2.TDR = Fifo2.tbuf[i++];
		Fifo2.tri = i % TXBUF2;
		Fifo2.tct--;
	} else {			/* No data to be sent */
		Fifo2.run = 0;
	}
}

#endif



#if USE_SCI3

static
volatile struct {
	uint16_t	rri, rwi, rct, tri, twi, tct, run;
	uint8_t		rbuf[RXBUF3], tbuf[TXBUF3];
} Fifo3;



/* Initialize SCI */

void uart3_init (
	uint32_t bps,
	const char* fmt
)
{
	uint32_t f, d;

	/* Attach SCI3 to I/O pad */
	IOPORT.PFFSCI.BIT.SCI3S = 0;
	MSTP_SCI3 = 0;
	PORT1.ICR.BIT.B2 = 1;

	SCI3.SCR.BYTE = 0;
	f = 0;							/* CM=0, CHR=0, PE=0, PM=0, STOP=0, MP=0, CKS=0 */
	if (fmt[0] == 'o') f |= 0x30;	/* PE=1, PM=1 */
	if (fmt[0] == 'e') f |= 0x20;	/* PE=1 */
	if (fmt[1] == '7') f |= 0x40;	/* CHR=1 */
	if (fmt[2] == '2') f |= 0x08;	/* STOP=1 */
	d = F_PCLK / 32 / bps - 1;
	if (d >= 256) {
		d /= 4; f |= 1;	/* CKS0=1 */
	}
	SCI3.SMR.BYTE = f;
	SCI3.BRR = d;
	delay_ms(2);
	SCI3.SCR.BYTE = 0xF0;		/* Start SCI (TIE=1,RIE=1,TE=1,RE=1) */

	/* Clear Tx/Rx Buffer */
	Fifo3.tri = 0; Fifo3.twi = 0; Fifo3.tct = 0; Fifo3.run = 0;
	Fifo3.rri = 0; Fifo3.rwi = 0; Fifo3.rct = 0;

	/* Enable SCI interrupts */
	IPR(SCI3, ERI3) = 3; IEN(SCI3, ERI3) = 1;
	IPR(SCI3, RXI3) = 3; IEN(SCI3, RXI3) = 1;
	IPR(SCI3, TXI3) = 1; IEN(SCI3, TXI3) = 1;
}


/* Get number of bytes in the Rx Buffer */

int uart3_test (void)
{
	return Fifo3.rct;
}


/* Get a byte from Rx buffer */

uint8_t uart3_getc (void)
{
	uint8_t d;
	uint16_t i;


	while (!Fifo3.rct) ;		/* Wait for Rx data available */

	IEN(SCI3, RXI3) = 0; IEN(SCI3, ERI3) = 0;	/* Disable Rx Irq */
	IODLY();

	i = Fifo3.rri;
	d = Fifo3.rbuf[i++];		/* Get a byte from Rx buffer */
	Fifo3.rri = i % RXBUF3;
	Fifo3.rct--;

	IEN(SCI3, RXI3) = 1; IEN(SCI3, ERI3) = 1;	/* Enable Rx Irq */

	return d;
}


/* Put a byte into Tx buffer */

void uart3_putc (
	uint8_t dat
)
{
	uint16_t i;


	while (Fifo3.tct >= TXBUF3) ;	/* Wait for buffer ready */

	IEN(SCI3, TXI3) = 0;	/* Disable Tx Irq */
	IODLY();

	if (Fifo3.run) {
		i = Fifo3.twi;			/* Store the data into the Tx buffer */
		Fifo3.tbuf[i++] = dat;
		Fifo3.twi = i % TXBUF3;
		Fifo3.tct++;
	} else {
		Fifo3.run = 1;
		SCI3.TDR = dat;
	}

	IEN(SCI3, TXI3) = 1;	/* Enable Tx Irq */
}


/* RDR Ready ISR */

void Excep_SCI3_RXI3 (void)
{
	uint16_t i;
	uint8_t d;


	d = SCI3.RDR;	/* Get received byte */

	if (Fifo3.rct < RXBUF3) {	/* Store the byte if buffer is not full */
		i = Fifo3.rwi;
		Fifo3.rbuf[i++] = d;
		Fifo3.rwi = i % RXBUF3;
		Fifo3.rct++;
	}
}


/* Receive Error ISR */

void Excep_SCI3_ERI3 (void)
{
	/* Clear error status */
	SCI3.RDR;
	SCI3.SSR.BYTE = 0x84;
}


/* TDR ready ISR */

void Excep_SCI3_TXI3 (void)
{
	uint16_t i;


	if (Fifo3.tct) {	/* There is a data to be sent */
		i = Fifo3.tri;
		SCI3.TDR = Fifo3.tbuf[i++];
		Fifo3.tri = i % TXBUF3;
		Fifo3.tct--;
	} else {			/* No data to be sent */
		Fifo3.run = 0;
	}
}

#endif



