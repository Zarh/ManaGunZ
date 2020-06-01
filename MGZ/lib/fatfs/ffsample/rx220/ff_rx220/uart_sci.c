/*------------------------------------------------------------------------*/
/* RX220 SCIe in UART control module                                      */
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


#define F_PCLK		32000000UL	/* PCLK frequency (configured by SCKCR.PCKB) */

#define USE_SCI1	1	/* Use SCI1 attached on 1=P26:P30, 2=P15:P16 */
#define TXBUF1		128	/* Tx FIFO size [byte]	*/
#define RXBUF1		128	/* Rx FIFO size [byte]	*/

#define USE_SCI5	0	/* Use SCI5 attached on 1=PA3:PA4, 2=PC2:PC3 */
#define TXBUF5		128	/* Tx FIFO size [byte]	*/
#define RXBUF5		128	/* Rx FIFO size [byte]	*/

#define USE_SCI6	0	/* Use SCI6 attached on 1=P32:P33, 2=PB0:PB1 */
#define TXBUF6		128	/* Tx FIFO size [byte]	*/
#define RXBUF6		128	/* Rx FIFO size [byte]	*/

#define USE_SCI9	0	/* Use SCI9 attached on 1=PB6:PB7 */
#define TXBUF9		128	/* Tx FIFO size [byte]	*/
#define RXBUF9		128	/* Rx FIFO size [byte]	*/


/*--------------------------------------------------*/


#include "iodefine.h"
#include "uart_sci.h"
#include "vect.h"

#define IODLY() {ICU.IR[0].BYTE; ICU.IR[0].BYTE; ICU.IR[0].BYTE;}




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
	MPC.PWPR.BYTE = 0x40; MPC.PWPR.BYTE = 0x40;	/* Unlock MPC */
#if USE_SCI1 == 1
	MPC.P26PFS.BYTE = 0x0A; PORT2.PMR.BIT.B6 = 1;
	MPC.P30PFS.BYTE = 0x0A; PORT3.PMR.BIT.B0 = 1;
#elif USE_SCI1 == 2
	MPC.P15PFS.BYTE = 0x0A; PORT1.PMR.BIT.B5 = 1;
	MPC.P16PFS.BYTE = 0x0A; PORT1.PMR.BIT.B6 = 1;
#endif
	MPC.PWPR.BYTE = 0x80;	/* Lock MPC */

	/* Enable SCI1 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP_SCI1 = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	/* Initialize SCI1 as UART */
	SCI1.SCR.BYTE = 0;
	f = 0;							/* CM=0, CHR=0, PE=0, PM=0, STOP=0, MP=0, CKS=0 */
	if (fmt[0] == 'o') f |= 0x30;	/* PE=1, PM=1 */
	if (fmt[0] == 'e') f |= 0x20;	/* PE=1 */
	if (fmt[1] == '7') f |= 0x40;	/* CHR=1 */
	if (fmt[2] == '2') f |= 0x08;	/* STOP=1 */
	d = F_PCLK / 32 / bps;			/* BRR value */
	while (d > 256) {
		d /= 4; f += 1;	/* CKS++ */
	}
	SCI1.SMR.BYTE = f;
	SCI1.BRR = d - 1;
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



#if USE_SCI5

static
volatile struct {
	uint16_t	rri, rwi, rct, tri, twi, tct, run;
	uint8_t		rbuf[RXBUF5], tbuf[TXBUF5];
} Fifo5;



/* Initialize SCI */

void uart5_init (
	uint32_t bps,
	const char* fmt
)
{
	uint32_t f, d;

	/* Attach SCI5 to I/O pad */
	MPC.PWPR.BYTE = 0x40; MPC.PWPR.BYTE = 0x40;	/* Unlock MPC */
#if USE_SCI5 == 1
	MPC.PA3PFS.BYTE = 0x0A; PORTA.PMR.BIT.B3 = 1;
	MPC.PA4PFS.BYTE = 0x0A; PORTA.PMR.BIT.B4 = 1;
#elif USE_SCI5 == 2
	MPC.PC2PFS.BYTE = 0x0A; PORTC.PMR.BIT.B2 = 1;
	MPC.PC3PFS.BYTE = 0x0A; PORTC.PMR.BIT.B3 = 1;
#endif
	MPC.PWPR.BYTE = 0x80;	/* Lock MPC */

	/* Enable SCI5 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP_SCI5 = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	SCI5.SCR.BYTE = 0;
	f = 0;							/* CM=0, CHR=0, PE=0, PM=0, STOP=0, MP=0, CKS=0 */
	if (fmt[0] == 'o') f |= 0x30;	/* PE=1, PM=1 */
	if (fmt[0] == 'e') f |= 0x20;	/* PE=1 */
	if (fmt[1] == '7') f |= 0x40;	/* CHR=1 */
	if (fmt[2] == '2') f |= 0x08;	/* STOP=1 */
	d = F_PCLK / 32 / bps;			/* BRR value */
	if (d > 256) {
		d /= 4; f |= 1;	/* CKS0=1 */
	}
	SCI5.SMR.BYTE = f;
	SCI5.BRR = d - 1;
	SCI5.SCR.BYTE = 0xF0;		/* Start SCI (TIE=1,RIE=1,TE=1,RE=1) */

	/* Clear Tx/Rx Buffer */
	Fifo5.tri = 0; Fifo5.twi = 0; Fifo5.tct = 0; Fifo5.run = 0;
	Fifo5.rri = 0; Fifo5.rwi = 0; Fifo5.rct = 0;

	/* Enable SCI interrupts */
	IPR(SCI5, ERI5) = 3; IEN(SCI5, ERI5) = 1;
	IPR(SCI5, RXI5) = 3; IEN(SCI5, RXI5) = 1;
	IPR(SCI5, TXI5) = 1; IEN(SCI5, TXI5) = 1;
}


/* Get number of bytes in the Rx Buffer */

int uart5_test (void)
{
	return Fifo5.rct;
}


/* Get a byte from Rx buffer */

uint8_t uart5_getc (void)
{
	uint8_t d;
	uint16_t i;


	while (!Fifo5.rct) ;		/* Wait for Rx data available */

	IEN(SCI5, RXI5) = 0; IEN(SCI5, ERI5) = 0;	/* Disable Rx Irq */
	IODLY();

	i = Fifo1.rri;
	d = Fifo1.rbuf[i++];		/* Get a byte from Rx buffer */
	Fifo5.rri = i % RXBUF5;
	Fifo5.rct--;

	IEN(SCI5, RXI5) = 1; IEN(SCI5, ERI5) = 1;	/* Enable Rx Irq */

	return d;
}


/* Put a byte into Tx buffer */

void uart5_putc (
	uint8_t dat
)
{
	uint16_t i;


	while (Fifo5.tct >= TXBUF5) ;	/* Wait for buffer ready */

	IEN(SCI5, TXI5) = 0;	/* Disable Tx Irq */
	IODLY();

	if (Fifo5.run) {
		i = Fifo5.twi;			/* Store the data into the Tx buffer */
		Fifo5.tbuf[i++] = dat;
		Fifo5.twi = i % TXBUF5;
		Fifo5.tct++;
	} else {
		Fifo5.run = 1;
		SCI5.TDR = dat;
	}

	IEN(SCI5, TXI5) = 1;	/* Enable Tx Irq */
}


/* RDR Ready ISR */

void Excep_SCI5_RXI5 (void)
{
	uint16_t i;
	uint8_t d;


	d = SCI5.RDR;	/* Get received byte */

	if (Fifo5.rct < RXBUF5) {	/* Store the byte if buffer is not full */
		i = Fifo5.rwi;
		Fifo5.rbuf[i++] = d;
		Fifo5.rwi = i % RXBUF5;
		Fifo5.rct++;
	}
}


/* Receive Error ISR */

void Excep_SCI5_ERI5 (void)
{
	/* Clear error status */
	SCI5.RDR;
	SCI5.SSR.BYTE = 0x84;
}


/* TDR ready ISR */

void Excep_SCI5_TXI5 (void)
{
	uint16_t i;


	if (Fifo5.tct) {	/* There is a data to be sent */
		i = Fifo5.tri;
		SCI5.TDR = Fifo5.tbuf[i++];
		Fifo5.tri = i % TXBUF5;
		Fifo5.tct--;
	} else {			/* No data to be sent */
		Fifo5.run = 0;
	}
}

#endif



#if USE_SCI6

static
volatile struct {
	uint16_t	rri, rwi, rct, tri, twi, tct, run;
	uint8_t		rbuf[RXBUF6], tbuf[TXBUF6];
} Fifo6;



/* Initialize SCI */

void uart6_init (
	uint32_t bps,
	const char* fmt
)
{
	uint32_t f, d;

	/* Attach SCI6 to I/O pad */
	MPC.PWPR.BYTE = 0x40; MPC.PWPR.BYTE = 0x40;
#if USE_SCI6 == 1
	MPC.P32PFS.BYTE = 0x0B; PORT3.PMR.BIT.B2 = 1;
	MPC.P33PFS.BYTE = 0x0B; PORT3.PMR.BIT.B3 = 1;
#elif USE_SCI6 == 2
	MPC.PB0PFS.BYTE = 0x0B; PORTB.PMR.BIT.B0 = 1;
	MPC.PB1PFS.BYTE = 0x0B; PORTB.PMR.BIT.B1 = 1;
#endif
	MPC.PWPR.BYTE = 0x80;

	/* Enable SCI6 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP_SCI6 = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	SCI6.SCR.BYTE = 0;
	f = 0;							/* CM=0, CHR=0, PE=0, PM=0, STOP=0, MP=0, CKS=0 */
	if (fmt[0] == 'o') f |= 0x30;	/* PE=1, PM=1 */
	if (fmt[0] == 'e') f |= 0x20;	/* PE=1 */
	if (fmt[1] == '7') f |= 0x40;	/* CHR=1 */
	if (fmt[2] == '2') f |= 0x08;	/* STOP=1 */
	d = F_PCLK / 32 / bps;			/* BRR value */
	if (d > 256) {
		d /= 4; f |= 1;	/* CKS0=1 */
	}
	SCI6.SMR.BYTE = f;
	SCI6.BRR = d - 1;
	SCI6.SCR.BYTE = 0xF0;		/* Start SCI (TIE=1,RIE=1,TE=1,RE=1) */

	/* Clear Tx/Rx Buffer */
	Fifo6.tri = 0; Fifo6.twi = 0; Fifo6.tct = 0; Fifo6.run = 0;
	Fifo6.rri = 0; Fifo6.rwi = 0; Fifo6.rct = 0;

	/* Enable SCI interrupts */
	IPR(SCI6, ERI6) = 3; IEN(SCI6, ERI6) = 1;
	IPR(SCI6, RXI6) = 3; IEN(SCI6, RXI6) = 1;
	IPR(SCI6, TXI6) = 1; IEN(SCI6, TXI6) = 1;
}


/* Get number of bytes in the Rx Buffer */

int uart6_test (void)
{
	return Fifo6.rct;
}


/* Get a byte from Rx buffer */

uint8_t uart6_getc (void)
{
	uint8_t d;
	uint16_t i;


	while (!Fifo6.rct) ;		/* Wait for Rx data available */

	IEN(SCI6, RXI6) = 0; IEN(SCI6, ERI6) = 0;	/* Disable Rx Irq */
	IODLY();

	i = Fifo6.rri;
	d = Fifo6.rbuf[i++];		/* Get a byte from Rx buffer */
	Fifo6.rri = i % RXBUF6;
	Fifo6.rct--;

	IEN(SCI6, RXI6) = 1; IEN(SCI6, ERI6) = 1;	/* Enable Rx Irq */

	return d;
}


/* Put a byte into Tx buffer */

void uart6_putc (
	uint8_t dat
)
{
	uint16_t i;


	while (Fifo6.tct >= TXBUF6) ;	/* Wait for buffer ready */

	IEN(SCI6, TXI6) = 0;	/* Disable Tx Irq */
	IODLY();

	if (Fifo6.run) {
		i = Fifo6.twi;			/* Store the data into the Tx buffer */
		Fifo6.tbuf[i++] = dat;
		Fifo6.twi = i % TXBUF6;
		Fifo6.tct++;
	} else {
		Fifo6.run = 1;
		SCI6.TDR = dat;
	}

	IEN(SCI6, TXI6) = 1;	/* Enable Tx Irq */
}


/* RDR Ready ISR */

void Excep_SCI6_RXI6 (void)
{
	uint16_t i;
	uint8_t d;


	d = SCI6.RDR;	/* Get received byte */

	if (Fifo6.rct < RXBUF6) {	/* Store the byte if buffer is not full */
		i = Fifo6.rwi;
		Fifo6.rbuf[i++] = d;
		Fifo6.rwi = i % RXBUF6;
		Fifo6.rct++;
	}
}


/* Receive Error ISR */

void Excep_SCI6_ERI6 (void)
{
	/* Clear error status */
	SCI6.RDR;
	SCI6.SSR.BYTE = 0x84;
}


/* TDR ready ISR */

void Excep_SCI6_TXI6 (void)
{
	uint16_t i;


	if (Fifo6.tct) {	/* There is a data to be sent */
		i = Fifo6.tri;
		SCI6.TDR = Fifo6.tbuf[i++];
		Fifo6.tri = i % TXBUF6;
		Fifo6.tct--;
	} else {			/* No data to be sent */
		Fifo6.run = 0;
	}
}

#endif



#if USE_SCI9

static
volatile struct {
	uint16_t	rri, rwi, rct, tri, twi, tct, run;
	uint8_t		rbuf[RXBUF9], tbuf[TXBUF9];
} Fifo9;



/* Initialize SCI */

void uart9_init (
	uint32_t bps,
	const char* fmt
)
{
	uint32_t f, d;

	/* Attach SCI9 to I/O pad */
	MPC.PWPR.BYTE = 0x40; MPC.PWPR.BYTE = 0x40;	/* Unlock MPC */
#if USE_SCI9 == 1
	MPC.PB6PFS.BYTE = 0x0A; PORTB.PMR.BIT.B6 = 1;
	MPC.PB7PFS.BYTE = 0x0A; PORTb.PMR.BIT.B7 = 1;
#endif
	MPC.PWPR.BYTE = 0x80;	/* Lock MPC */

	/* Enable SCI9 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP_SCI9 = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	SCI9.SCR.BYTE = 0;
	f = 0;							/* CM=0, CHR=0, PE=0, PM=0, STOP=0, MP=0, CKS=0 */
	if (fmt[0] == 'o') f |= 0x30;	/* PE=1, PM=1 */
	if (fmt[0] == 'e') f |= 0x20;	/* PE=1 */
	if (fmt[1] == '7') f |= 0x40;	/* CHR=1 */
	if (fmt[2] == '2') f |= 0x08;	/* STOP=1 */
	d = F_PCLK / 32 / bps;			/* BRR value */
	if (d > 256) {
		d /= 4; f |= 1;	/* CKS0=1 */
	}
	SCI9.SMR.BYTE = f;
	SCI9.BRR = d - 1;
	SCI9.SCR.BYTE = 0xF0;		/* Start SCI (TIE=1,RIE=1,TE=1,RE=1) */

	/* Clear Tx/Rx Buffer */
	Fifo9.tri = 0; Fifo9.twi = 0; Fifo9.tct = 0; Fifo9.run = 0;
	Fifo9.rri = 0; Fifo9.rwi = 0; Fifo9.rct = 0;

	/* Enable SCI interrupts */
	IPR(SCI9, ERI9) = 3; IEN(SCI9, ERI9) = 1;
	IPR(SCI9, RXI9) = 3; IEN(SCI9, RXI9) = 1;
	IPR(SCI9, TXI9) = 1; IEN(SCI9, TXI9) = 1;
}


/* Get number of bytes in the Rx Buffer */

int uart9_test (void)
{
	return Fifo9.rct;
}


/* Get a byte from Rx buffer */

uint8_t uart9_getc (void)
{
	uint8_t d;
	uint16_t i;


	while (!Fifo9.rct) ;		/* Wait for Rx data available */

	IEN(SCI9, RXI9) = 0; IEN(SCI9, ERI9) = 0;	/* Disable Rx Irq */
	IODLY();

	i = Fifo9.rri;
	d = Fifo9.rbuf[i++];		/* Get a byte from Rx buffer */
	Fifo9.rri = i % RXBUF9;
	Fifo9.rct--;

	IEN(SCI9, RXI9) = 1; IEN(SCI9, ERI9) = 1;	/* Enable Rx Irq */

	return d;
}


/* Put a byte into Tx buffer */

void uart9_putc (
	uint8_t dat
)
{
	uint16_t i;


	while (Fifo9.tct >= TXBUF9) ;	/* Wait for buffer ready */

	IEN(SCI9, TXI9) = 0;	/* Disable Tx Irq */
	IODLY();

	if (Fifo9.run) {
		i = Fifo9.twi;			/* Store the data into the Tx buffer */
		Fifo9.tbuf[i++] = dat;
		Fifo9.twi = i % TXBUF9;
		Fifo9.tct++;
	} else {
		Fifo9.run = 1;
		SCI9.TDR = dat;
	}

	IEN(SCI9, TXI9) = 1;	/* Enable Tx Irq */
}


/* RDR Ready ISR */

void Excep_SCI9_RXI9 (void)
{
	uint16_t i;
	uint8_t d;


	d = SCI9.RDR;	/* Get received byte */

	if (Fifo9.rct < RXBUF9) {	/* Store the byte if buffer is not full */
		i = Fifo9.rwi;
		Fifo9.rbuf[i++] = d;
		Fifo9.rwi = i % RXBUF9;
		Fifo9.rct++;
	}
}


/* Receive Error ISR */

void Excep_SCI9_ERI9 (void)
{
	/* Clear error status */
	SCI9.RDR;
	SCI9.SSR.BYTE = 0x84;
}


/* TDR ready ISR */

void Excep_SCI9_TXI9 (void)
{
	uint16_t i;


	if (Fifo9.tct) {	/* There is a data to be sent */
		i = Fifo9.tri;
		SCI9.TDR = Fifo9.tbuf[i++];
		Fifo9.tri = i % TXBUF9;
		Fifo9.tct--;
	} else {			/* No data to be sent */
		Fifo9.run = 0;
	}
}

#endif



