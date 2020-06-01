#ifndef _UART_DEF
#define _UART_DEF

#include "LPC178x.h"

#define USE_UART0	1		/* Enable UART0 function */
#define UART0_BPS 	230400	/* UART0 bit rate */
#define UART0_TXB	128		/* Size of Tx buffer */
#define UART0_RXB	128		/* Size of Rx buffer */

#define USE_UART1	0		/* Enable UART1 function */
#define UART1_BPS 	38400
#define UART1_TXB	128
#define UART1_RXB	128

#define USE_UART2	0		/* Enable UART2 function */
#define UART2_BPS 	38400
#define UART2_TXB	128
#define UART2_RXB	128

#define USE_UART3	0		/* Enable UART3 function */
#define UART3_BPS 	38400
#define UART3_TXB	128
#define UART3_RXB	128

#define USE_UART4	0		/* Enable UART4 function */
#define UART4_BPS 	38400
#define UART4_TXB	128
#define UART4_RXB	128


#if USE_UART0
void uart0_init (void);
int uart0_test (void);
void uart0_putc (uint8_t);
uint8_t uart0_getc (void);
#endif
#if USE_UART1
void uart1_init (void);
int uart1_test (void);
void uart1_putc (uint8_t);
uint8_t uart1_getc (void);
#endif
#if USE_UART2
void uart2_init (void);
int uart2_test (void);
void uart2_putc (uint8_t);
uint8_t uart2_getc (void);
#endif
#if USE_UART3
void uart3_init (void);
int uart3_test (void);
void uart3_putc (uint8_t);
uint8_t uart3_getc (void);
#endif
#if USE_UART4
void uart4_init (void);
int uart4_test (void);
void uart4_putc (uint8_t);
uint8_t uart4_getc (void);
#endif

#endif
