#ifndef UART_DEFINED
#define UART_DEFINED
#include <stdint.h>

#define USE_UART0	0		/* Enable MFS0 as UART */
#define	UART0_LOC	0		/* Pin relocation number */
#define UART0_BPS 	38400	/* Bit rate */
#define UART0_TXB	128		/* Size of Tx buffer */
#define UART0_RXB	128		/* Size of Rx buffer */

#define USE_UART1	0		/* Enable MFS1 as UART */
#define	UART1_LOC	0
#define UART1_BPS 	38400
#define UART1_TXB	128
#define UART1_RXB	128

#define USE_UART2	0		/* Enable MFS2 as UART */
#define	UART2_LOC	0
#define UART2_BPS 	38400
#define UART2_TXB	128
#define UART2_RXB	128

#define USE_UART3	1		/* Enable MFS3 as UART */
#define	UART3_LOC	2
#define UART3_BPS 	115200
#define UART3_TXB	128
#define UART3_RXB	128

#define USE_UART4	0		/* Enable MFS4 as UART */
#define	UART4_LOC	0
#define UART4_BPS 	38400
#define UART4_TXB	128
#define UART4_RXB	128

#define USE_UART5	0		/* Enable MFS5 as UART */
#define	UART5_LOC	0
#define UART5_BPS 	38400
#define UART5_TXB	128
#define UART5_RXB	128

#define USE_UART7	0		/* Enable MFS6 as UART */
#define	UART6_LOC	0
#define UART6_BPS 	38400
#define UART6_TXB	128
#define UART6_RXB	128

#define USE_UART7	0		/* Enable MFS7 as UART */
#define	UART7_LOC	0
#define UART7_BPS 	38400
#define UART7_TXB	128
#define UART7_RXB	128


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
#if USE_UART5
void uart5_init (void);
int uart5_test (void);
void uart5_putc (uint8_t);
uint8_t uart5_getc (void);
#endif
#if USE_UART6
void uart6_init (void);
int uart6_test (void);
void uart6_putc (uint8_t);
uint8_t uart6_getc (void);
#endif
#if USE_UART7
void uart7_init (void);
int uart7_test (void);
void uart7_putc (uint8_t);
uint8_t uart7_getc (void);
#endif

#endif
