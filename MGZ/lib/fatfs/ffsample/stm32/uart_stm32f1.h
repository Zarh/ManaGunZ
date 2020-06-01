#ifndef _UART_DEFS
#define _UART_DEFS

#include "STM32F100.h"

#define USE_UART1	1		/* 0:Disable, 1:Enable, 2:Enable w/remap */
#define UART1_RXB	128		/* Size of Rx buffer */
#define UART1_TXB	128		/* Size of Tx buffer */

#define USE_UART2	0		/* 0:Disable, 1:Enable, 2:Enable w/remap */
#define UART2_RXB	128		/* Size of Rx buffer */
#define UART2_TXB	128		/* Size of Tx buffer */

#define USE_UART3	0		/* 0:Disable, 1:Enable, 2:Enable w/remap */
#define UART3_RXB	128		/* Size of Rx buffer */
#define UART3_TXB	128		/* Size of Tx buffer */



#if USE_UART1
void uart1_init (uint32_t bps);
int uart1_test (void);
void uart1_putc (uint8_t d);
uint8_t uart1_getc (void);
#endif
#if USE_UART2
void uart2_init (uint32_t bps);
int uart2_test (void);
void uart2_putc (uint8_t);
uint8_t uart2_getc (void);
#endif
#if USE_UART3
void uart3_init (uint32_t bps);
int uart3_test (void);
void uart3_putc (uint8_t);
uint8_t uart3_getc (void);
#endif

#endif
