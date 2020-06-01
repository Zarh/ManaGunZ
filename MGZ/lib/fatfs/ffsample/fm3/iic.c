/*------------------------------------------------------------------------/
/  MB9BF616/617/618 I2C master control module
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2012, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include "FM3_type2.h"
#include "iic.h"


#define I2C_MFS		1			/* MFS channel to be used as I2C (0-7) */
#define I2C_LOC		0			/* Pin relocation number (0-2) */
#define I2C_BPS 	400000		/* I2C bit rate */
#define F_PCLK		72000000	/* Bus clock for the MFS module */


/*--------------------------------------------------------------------------

   Module Private Functions and Macros

---------------------------------------------------------------------------*/

#if   I2C_MFS == 0
#define MFS_TX_IRQHandler MFS0_TX_IRQHandler
#define MFS_TX_IRQn MFS0_TX_IRQn
#define MFS_IBCR  MFS0_IBCR
#define MFS_SMR   MFS0_SMR
#define MFS_SSR   MFS0_SSR
#define MFS_TDR   MFS0_TDR
#define MFS_RDR   MFS0_RDR
#define MFS_BGR   MFS0_BGR
#define MFS_ISBA  MFS0_ISBA
#define MFS_ISMK  MFS0_ISMK
#if   UART_LOC == 0
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 6)) | (5 << 6); PFR2 |= 3 << 2; }
#elif UART_LOC == 1
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 6)) | (10 << 6); PFR1 |= 3 << 5; }
#elif UART_LOC == 2
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 6)) | (15 << 6); PFRB |= 3 << 5; }
#endif

#elif I2C_MFS == 1
#define MFS_TX_IRQHandler MFS1_TX_IRQHandler
#define MFS_TX_IRQn MFS1_TX_IRQn
#define MFS_IBCR  MFS1_IBCR
#define MFS_IBSR  MFS1_IBSR
#define MFS_SMR   MFS1_SMR
#define MFS_SSR   MFS1_SSR
#define MFS_TDR   MFS1_TDR
#define MFS_RDR   MFS1_RDR
#define MFS_BGR   MFS1_BGR
#define MFS_ISBA  MFS1_ISBA
#define MFS_ISMK  MFS1_ISMK
#if   UART_LOC == 0
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 12)) | (5 << 12); PFR5 |= 3 << 7; }
#elif UART_LOC == 1
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 12)) | (10 << 12); PFR1 |= 3 << 21; }
#elif UART_LOC == 2
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 12)) | (15 << 12); PFRF |= 3 << 1; }
#endif

#elif I2C_MFS == 2
#define MFS_TX_IRQHandler MFS2_TX_IRQHandler
#define MFS_TX_IRQn MFS2_TX_IRQn
#define MFS_IBCR  MFS2_IBCR
#define MFS_IBSR  MFS2_IBSR
#define MFS_SMR   MFS2_SMR
#define MFS_SSR   MFS2_SSR
#define MFS_TDR   MFS2_TDR
#define MFS_RDR   MFS2_RDR
#define MFS_BGR   MFS2_BGR
#define MFS_ISBA  MFS2_ISBA
#define MFS_ISMK  MFS2_ISMK
#if   UART_LOC == 0
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 18)) | (5 << 18); PFR7 |= 3 << 3; }
#elif UART_LOC == 1
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 18)) | (10 << 18); PFR2 |= 3 << 5; }
#elif UART_LOC == 2
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 18)) | (15 << 18); PFR1 |= 3 << 8; }
#endif

#elif I2C_MFS == 3
#define MFS_TX_IRQHandler MFS3_TX_IRQHandler
#define MFS_TX_IRQn MFS3_TX_IRQn
#define MFS_IBCR  MFS3_IBCR
#define MFS_IBSR  MFS3_IBSR
#define MFS_SMR   MFS3_SMR
#define MFS_SSR   MFS3_SSR
#define MFS_TDR   MFS3_TDR
#define MFS_RDR   MFS3_RDR
#define MFS_BGR   MFS3_BGR
#define MFS_ISBA  MFS3_ISBA
#define MFS_ISMK  MFS3_ISMK
#if   UART_LOC == 0
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 24)) | (5 << 24); PFR7 |= 3 << 6; }
#elif UART_LOC == 1
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 24)) | (10 << 24); PFR5 |= 3 << 1; }
#elif UART_LOC == 2
#define ATTACH_MFS() { EPFR07 = (EPFR07 & ~(15 << 24)) | (15 << 24); PFR4 |= 3 << 9; }
#endif

#elif I2C_MFS == 4
#define MFS_TX_IRQHandler MFS4_TX_IRQHandler
#define MFS_TX_IRQn MFS4_TX_IRQn
#define MFS_IBCR  MFS4_IBCR
#define MFS_IBSR  MFS4_IBSR
#define MFS_SMR   MFS4_SMR
#define MFS_SSR   MFS4_SSR
#define MFS_TDR   MFS4_TDR
#define MFS_RDR   MFS4_RDR
#define MFS_BGR   MFS4_BGR
#define MFS_ISBA  MFS4_ISBA
#define MFS_ISMK  MFS4_ISMK
#if   UART_LOC == 0
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 6)) | (5 << 6); PFRD |= 3 << 0; }
#elif UART_LOC == 1
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 6)) | (10 << 6); PFR1 |= 3 << 11; }
#elif UART_LOC == 2
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 6)) | (15 << 6); PFR0 |= 3 << 6; }
#endif

#elif I2C_MFS == 5
#define MFS_TX_IRQHandler MFS5_TX_IRQHandler
#define MFS_TX_IRQn MFS5_TX_IRQn
#define MFS_IBCR  MFS5_IBCR
#define MFS_IBSR  MFS5_IBSR
#define MFS_SMR   MFS5_SMR
#define MFS_SSR   MFS5_SSR
#define MFS_TDR   MFS5_TDR
#define MFS_RDR   MFS5_RDR
#define MFS_BGR   MFS5_BGR
#define MFS_ISBA  MFS5_ISBA
#define MFS_ISMK  MFS5_ISMK
#if   UART_LOC == 0
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 12)) | (5 << 12); PFR6 |= 3 << 1; }
#elif UART_LOC == 1
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 12)) | (10 << 12); PFR9 |= 3 << 3; }
#elif UART_LOC == 2
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 12)) | (15 << 12); PFR3 |= 3 << 7; }
#endif

#elif I2C_MFS == 6
#define MFS_TX_IRQHandler MFS6_TX_IRQHandler
#define MFS_TX_IRQn MFS6_TX_IRQn
#define MFS_IBCR  MFS6_IBCR
#define MFS_IBSR  MFS6_IBSR
#define MFS_SMR   MFS6_SMR
#define MFS_SSR   MFS6_SSR
#define MFS_TDR   MFS6_TDR
#define MFS_RDR   MFS6_RDR
#define MFS_BGR   MFS6_BGR
#define MFS_ISBA  MFS6_ISBA
#define MFS_ISMK  MFS6_ISMK
#if   UART_LOC == 0
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 18)) | (5 << 18); PFR5 |= 3 << 4; }
#elif UART_LOC == 1
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 18)) | (10 << 18); PFR3 |= 3 << 1; }
#elif UART_LOC == 2
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 18)) | (15 << 18); PFRF |= 3 << 4; }
#endif

#elif I2C_MFS == 7
#define MFS_TX_IRQHandler MFS7_TX_IRQHandler
#define MFS_TX_IRQn MFS7_TX_IRQn
#define MFS_IBCR  MFS7_IBCR
#define MFS_IBSR  MFS7_IBSR
#define MFS_SMR   MFS7_SMR
#define MFS_SSR   MFS7_SSR
#define MFS_TDR   MFS7_TDR
#define MFS_RDR   MFS7_RDR
#define MFS_BGR   MFS7_BGR
#define MFS_ISBA  MFS7_ISBA
#define MFS_ISMK  MFS7_ISMK
#if   UART_LOC == 0
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 24)) | (5 << 24); PFR5 |= 3 << 10; }
#elif UART_LOC == 1
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 24)) | (10 << 24); PFR4 |= 3 << 12; }
#elif UART_LOC == 2
#define ATTACH_MFS() { EPFR08 = (EPFR08 & ~(15 << 24)) | (15 << 24); PFRB |= 3 << 1; }
#endif

#endif


enum { S_SLA_W, S_CMD_W, S_DAT_W, S_SLA_R, S_DAT_R };	/* State of transaction Ctrl0->phase */


static
volatile I2CCTRL *Ctrl0;	/* Current I2C control structure */


/*------------------------*/
/* Initialize I2C Module  */
/*------------------------*/

void i2c_init (void)
{
	__disable_irqn(MFS_TX_IRQn);

	MFS_ISMK = 0;		/* Disable I2C function */

	/* Bus reset sequence may be required here to make all slaves inactive */

	/* Initialize MFS in I2C mode */
	MFS_SMR = 0x80;		/* Set I2C mode */
	MFS_SSR = 0;
	MFS_BGR = F_PCLK / I2C_BPS - 1;
	MFS_ISBA = 0;		/* No address detection */
	MFS_ISMK = 0xFF;	/* Enable I2C function */

	/* Attach MFS module to I/O pads */
	ATTACH_MFS();

	/* Enable MFS status interrupt */
	__enable_irqn(MFS_TX_IRQn);
}



/*--------------------------*/
/* Start an I2C Transaction */
/*--------------------------*/

int i2c_start (
	volatile I2CCTRL *ctrl	/* Pointer to the initialized I2C control structure */
)
{
	if (Ctrl0) return 0;	/* Reject if an I2C transaction is in progress */

	Ctrl0 = ctrl;				/* Register the I2C control strucrure as current transaction */
	ctrl->status = I2C_BUSY;	/* An I2C transaction is in progress */
	MFS_TDR = ctrl->sla << 1;	/* Data to be sent as 1st byte = SLA+W */
	ctrl->phase = S_SLA_W;
	MFS_IBCR = 0x85;			/* Wait for bus-free and then generate start condition */

	return 1;
}



/*--------------------------*/
/* Abort I2C Transaction    */
/*--------------------------*/

void i2c_abort (void)
{
	MFS_IBCR = 0;		/* Disable I2C function */
	MFS_ISMK = 0;
	Ctrl0 = 0;			/* Discard I2C control structure */
	__disable_irqn(MFS_TX_IRQn);
}



/*-------------------------*/
/* I2C Background Process  */
/*-------------------------*/

void MFS_TX_IRQHandler (void)
{
	volatile I2CCTRL *ctrl;
	uint8_t ibcr, ibsr, eot = 0;
	uint16_t n;


	ctrl = Ctrl0;
	if (!ctrl) {		/* Spurious Interrupt */
		MFS_IBCR = 0;	/* Disable I2C function */
		MFS_ISMK = 0;
		__disable_irqn(MFS_TX_IRQn);
		return;
	}

	ibcr = MFS_IBCR;
	ibsr = MFS_IBSR;
	if (!(ibcr & 0x80) || (ibsr & 0x20)) {	/* Bus error, Arbitration lost or Reserved address */
		eot = I2C_ERROR;

	} else {
		switch (ctrl->phase) {
		case S_SLA_W:	/* S+SLA+W sent */
			if (ibsr & 0x40) {	/* ACK not received (slave not responded) */
				n = ctrl->retry;
				if (n) {
					ctrl->retry = n - 1;
					MFS_TDR = ctrl->sla << 1;	/* Send Sr+SLA+W */
					MFS_IBCR = 0xC5;
				} else {
					eot = I2C_TIMEOUT;
				}
			} else {			/* ACK received (slave responded) */
				ctrl->ncmd--;
				MFS_TDR = ctrl->cmd[0];	/* Sent command byte */
				ctrl->icmd = 1;
				MFS_IBCR = 0x84;
				ctrl->phase = S_CMD_W;
			}
			break;

		case S_CMD_W:	/* Command byte sent */
			if (ibsr & 0x40) {	/* ACK not received */
				eot = I2C_ABORTED;
			} else {			/* ACK received */
				n = ctrl->ncmd;
				if (n) {	/* There is command byte to be sent */
					ctrl->ncmd = n - 1;
					MFS_TDR = ctrl->cmd[ctrl->icmd++];	/* Send next command byte */
					MFS_IBCR = 0x84;
				} else {	/* All command byte has been sent */
					n = ctrl->ndata;
					if (n) {
						if (ctrl->dir == I2C_WRITE) {	/* There is data to be written */
							ctrl->ndata = n - 1;
							ctrl->phase = S_DAT_W;
							MFS_TDR = *ctrl->data++;	/* Send data */
							MFS_IBCR = 0x84;
							ctrl->phase = S_DAT_W;
						} else {						/* There is data to be read */
							MFS_TDR = (ctrl->sla << 1) + 1;	/* Send Sr+SLA+R */
							MFS_IBCR = 0xC5;
							ctrl->phase = S_SLA_R;
						}
					} else {	/* No data to be written/read */
						eot = I2C_SUCCEEDED;
					}
				}
			}
			break;

		case S_DAT_W:	/* Data sent */
			if (ibsr & 0x40) {	/* ACK not received */
				eot = I2C_ABORTED;
			} else {			/* ACK received */
				n = ctrl->ndata;
				if (n) {		/* There is any data to be written */
					ctrl->ndata = n - 1;
					MFS_TDR = *ctrl->data++;	/* Send data */
					MFS_IBCR = 0x84;
				} else {		/* All data has been sent */
					eot = I2C_SUCCEEDED;
				}
			}
			break;

		case S_SLA_R:	/* Sr+SLA+R sent */
			if (ibsr & 0x40) {	/* ACK not received (slave not responded) */
				eot = I2C_ABORTED;
			} else {			/* ACK received (slave responded) */
				MFS_IBCR = (ctrl->ndata > 1) ? 0xA4 : 0x84;
				ctrl->phase = S_DAT_R;
			}
			break;

		case S_DAT_R:	/* Data received */
			*ctrl->data++ = MFS_RDR;	/* Store read data */
			n = ctrl->ndata - 1;
			if (n) {	/* There is any data to be read */
				ctrl->ndata = n;
				MFS_IBCR = (n > 1) ? 0xA4 : 0x84;
			} else {	/* All data has been read */
				eot = I2C_SUCCEEDED;
			}
			break;

		default:
			eot = I2C_ERROR;
		}
	}

	if (eot) {	/* End of I2C transaction? */
		MFS_IBCR = 0x00;
		Ctrl0 = 0;			/* Release I2C control structure */
		ctrl->status = eot;	/* Set result code */
		if (ctrl->eotfunc) ctrl->eotfunc(eot);	/* Notify EOT if call-back function is specified */
	}
}


