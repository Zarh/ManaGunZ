/*------------------------------------------------------------------------*/
/* RX220: SCI in UART control module                                      */
/*------------------------------------------------------------------------*/

#ifndef _DEF_UART_SCI
#define _DEF_UART_SCI
#include <stdint.h>


void uart1_init (uint32_t bps, const char* fmt);
int uart1_test (void);
void uart1_putc (uint8_t dat);
uint8_t uart1_getc (void);

void uart5_init (uint32_t bps, const char* fmt);
int uart5_test (void);
void uart5_putc (uint8_t dat);
uint8_t uart5_getc (void);

void uart6_init (uint32_t bps, const char* fmt);
int uart6_test (void);
void uart6_putc (uint8_t dat);
uint8_t uart6_getc (void);

void uart9_init (uint32_t bps, const char* fmt);
int uart9_test (void);
void uart9_putc (uint8_t dat);
uint8_t uart9_getc (void);

#endif


