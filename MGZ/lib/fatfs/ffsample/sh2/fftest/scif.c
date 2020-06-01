/*----------------------------------------------*/
/* SCIF Control Module                          */
/*----------------------------------------------*/

#include "iodefine.h"
#include "scif.h"
#include "vect.h"


#define BUFFER_SIZE 128

#define F_PCLK		24000000UL
#define BPS 		115200


/* Tx/Rx buffer  */
static volatile struct {
	int		ri, wi, ct;
	unsigned char	buff[BUFFER_SIZE];
} TxFifo, RxFifo;



/*---------------------------------------*/
/* Initialize SCIF ch2                   */
/*---------------------------------------*/

void scif2_init (unsigned long bps)
{
	SCIF2.SCSCR.WORD = 0x0000;	/* Stop SCIF */

	/* Attach SCIF2 unit (TxD2/RxD2) to I/O pad */
	PORT.PFCR0.WORD = (PORT.PFCR0.WORD & 0xF00F) | 0x0440;

	/* Initialize SCIF2 */
	SCIF2.SCEMR.WORD = 0x0000;						/* Bit rate */
	SCIF2.SCBRR.BYTE = F_PCLK / 1 / bps / 32 - 1;
	SCIF2.SCSMR.WORD = 0x0000;						/* Data format (N81) */
	SCIF2.SCFCR.WORD = 0x00B6; SCIF2.SCFCR.WORD = 0x00B0;	/* Clear Tx/Rx FIFO */

	/* Clear Tx/Rx Buffer */
	TxFifo.ri = 0; TxFifo.wi = 0; TxFifo.ct = 0;
	RxFifo.ri = 0; RxFifo.wi = 0; RxFifo.ct = 0;

	/* Set SCIF2 interrupt level */
	INTC.IPR17.WORD = (INTC.IPR17.WORD & 0xFF0F) | 0x0010;	/* level 1 */

	SCIF2.SCSCR.WORD = 0x0070;	/* Start SCIF2 (Set TE,RE,RIE) */
}



/*---------------------------------------*/
/* Get number of bytes in the Rx Buffer  */
/*---------------------------------------*/

int scif2_test (void)
{
	return RxFifo.ct;
}



/*---------------------------------------*/
/* Get a byte from Rx buffer             */
/*---------------------------------------*/

unsigned char scif2_getc (void)
{
	unsigned char d;
	int i;

	/* Wait while Rx buffer is empty */
	while (!RxFifo.ct) ;

	SCIF2.SCSCR.BIT.RIE = 0;		/* Disable Rx interrupt */

	i = RxFifo.ri;
	d = RxFifo.buff[i++];			/* Get a byte from Rx buffer */
	RxFifo.ri = i % BUFFER_SIZE;
	RxFifo.ct--;

	SCIF2.SCSCR.BIT.RIE = 1;		/* Enable Rx interrupt */

	return d;
}



/*---------------------------------------*/
/* Put a byte into Tx buffer             */
/*---------------------------------------*/

void scif2_putc (unsigned char d)
{
	int i;


	while (TxFifo.ct >= BUFFER_SIZE) ;	/* Wait for buffer ready */

	SCIF2.SCSCR.BIT.TIE = 0;		/* Disable Tx interrupt */

	i = TxFifo.wi;					/* Store the data into the Tx buffer */
	TxFifo.buff[i++] = d;
	TxFifo.wi = i % BUFFER_SIZE;
	TxFifo.ct++;

	SCIF2.SCSCR.BIT.TIE = 1;		/* Enable Tx interrupt */
}



/*---------------------------------------*/
/* ISR for data receive event            */
/*---------------------------------------*/

void INT_SCIF_SCIF2_RXI2 (void)	/* ISR: requires vect.h */
{
	int i, cnt;
	unsigned char d;


	i = RxFifo.wi;
	cnt = RxFifo.ct;
	do {							/* Read all data from FIFO */
		d = SCIF2.SCFRDR.BYTE;
		if (cnt < BUFFER_SIZE) {	/* Store the byte if buffer is not full */
			RxFifo.buff[i++] = d;
			i %= BUFFER_SIZE;
			cnt++;
		}
	} while (SCIF2.SCFDR.BIT.R);

	SCIF2.SCFSR.WORD &= ~0x0083;	/* Clear interrupt flags */

	RxFifo.wi = i;
	RxFifo.ct = cnt;
}



/*---------------------------------------*/
/* ISR for data transimit event          */
/*---------------------------------------*/

void INT_SCIF_SCIF2_TXI2 (void)	/* ISR: requires vect.h */
{
	int i, cnt;


	cnt = TxFifo.ct;
	if (cnt) {
		i = TxFifo.ri;
		do {					/* Fill SCIF Tx FIFO */
			SCIF2.SCFTDR.BYTE = TxFifo.buff[i++];
			i %= BUFFER_SIZE;
			cnt--;
		} while (cnt && SCIF2.SCFDR.BIT.T < 16);
		TxFifo.ri = i;
		TxFifo.ct = cnt;
		SCIF2.SCFSR.BIT.TDFE = 0;		/* Clear Tx interrupt flag */
	}
	if (!cnt)	/* Disable Tx interrupt if no data in the buffer */
		SCIF2.SCSCR.BIT.TIE = 0;
}



