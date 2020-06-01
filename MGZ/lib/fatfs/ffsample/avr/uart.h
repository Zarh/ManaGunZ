#ifndef UART_DEFINED
#define UART_DEFINED

#include <stdint.h>

void uart_init (uint32_t bps);	/* Initialize UART and Flush FIFOs */
uint16_t uart_test (void);		/* Check number of data in UART Rx FIFO */
uint8_t uart_getc (void);		/* Get a byte from UART Rx FIFO */
void uart_putc (uint8_t d);		/* Put a byte into UART Tx FIFO */

#endif
