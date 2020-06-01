#include "ff.h"
#ifndef _SCI3_DEF
#define _SCI3_DEF

void sci3_init (void);	/* Initialize UART and Flush FIFOs */
BYTE sci3_get (void);	/* Get a byte from UART Rx FIFO */
BYTE sci3_test(void);	/* Check number of data in UART Rx FIFO */
void sci3_put (BYTE);	/* Put a byte into UART Tx FIFO */

#endif
