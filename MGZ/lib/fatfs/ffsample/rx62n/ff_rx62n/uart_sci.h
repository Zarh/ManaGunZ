/*------------------------------------------------------------------------*/
/* FRK-RX62N: SCI in UART control module                                  */
/*------------------------------------------------------------------------*/

#ifndef _DEF_UART_SCI
#define _DEF_UART_SCI
#include <stdint.h>

#define _UART_SCI0	0
#define _UART_SCI1	1
#define _UART_SCI2	0
#define _UART_SCI3	0


void uart0_init (uint32_t bps, const char* fmt);
int uart0_test (void);
void uart0_putc (uint8_t dat);
uint8_t uart0_getc (void);

void uart1_init (uint32_t bps, const char* fmt);
int uart1_test (void);
void uart1_putc (uint8_t dat);
uint8_t uart1_getc (void);

void uart2_init (uint32_t bps, const char* fmt);
int uart2_test (void);
void uart2_putc (uint8_t dat);
uint8_t uart2_getc (void);

void uart3_init (uint32_t bps, const char* fmt);
int uart3_test (void);
void uart3_putc (uint8_t dat);
uint8_t uart3_getc (void);

#endif


