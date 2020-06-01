/*------------------------------------------------*/
/* SCI contorl functions                          */
/*------------------------------------------------*/


#include <machine.h>
#include "iodefine.h"
#include "sci.h"


static volatile struct {
	BYTE wp;
	BYTE rp;
	BYTE ctr;
	BYTE buff[64];
} TxFifo, RxFifo;



/* Initialize SCI3 */

void sci3_init (void)
{
	WORD n;


	RxFifo.rp = 0;
	RxFifo.wp = 0;
	RxFifo.ctr = 0;
	TxFifo.rp = 0;
	TxFifo.wp = 0;
	TxFifo.ctr = 0;

	SCI3.SCR3.BYTE = 0;
	SCI3.SMR.BYTE = 0;		/* N81 */
	SCI3.BRR = 15;			/* 38400bps @ 20MHz */
	IO.PMR1.BIT.TXD = 1;
	for (n = 0; n < 10000; n++) ;
	SCI3.SCR3.BYTE = 0xF0;	/* TE = TIE = RE = RIE = 1; */
}



/* Gut a character  */

BYTE sci3_get (void)
{
	BYTE d, i;


	while (RxFifo.ctr == 0) ;

	i = RxFifo.rp;
	d = RxFifo.buff[i++];
	RxFifo.rp = i % sizeof RxFifo.buff;
	set_imask_ccr(1);
	RxFifo.ctr--;
	set_imask_ccr(0);

	return d;
}



/* Put a character  */

void sci3_put (BYTE d)
{
	BYTE i;


	while (TxFifo.ctr >= sizeof TxFifo.buff) ;

	i = TxFifo.wp;
	TxFifo.buff[i++] = d;
	TxFifo.wp = i % sizeof TxFifo.buff;
	set_imask_ccr(1);
	TxFifo.ctr++;
	SCI3.SCR3.BIT.TIE = 1;
	set_imask_ccr(0);
}



/* SCI3 interrupt */

void int_SCI3 (void)
{
	BYTE stat, d, n, i;


	stat = SCI3.SSR.BYTE;
	if (stat & 0x38) {
		stat &= ~0x38;
		SCI3.SSR.BYTE = stat;
	}
	if (stat & 0x40) {
		d = SCI3.RDR;
		n = RxFifo.ctr;
		if(n < sizeof RxFifo.buff) {
			RxFifo.ctr = n + 1;
			i = RxFifo.wp;
			RxFifo.buff[i++] = d;
			RxFifo.wp = i % sizeof RxFifo.buff;
		}
	}
	if (stat & 0x80) {
		n = TxFifo.ctr;
		if(n) {
			TxFifo.ctr = n - 1;
			i = TxFifo.rp;
			SCI3.TDR = TxFifo.buff[i++];
			TxFifo.rp = i % sizeof TxFifo.buff;
		}
		if(n == 0)
			SCI3.SCR3.BIT.TIE = 0;
	}
}

