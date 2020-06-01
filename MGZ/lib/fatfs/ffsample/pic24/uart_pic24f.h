#ifndef _COMMFUNC
#define _COMMFUNC

void uart_init (unsigned long bps);
int uart_test (void);
void uart_putc (unsigned char d);
unsigned char uart_getc (void);

#endif

