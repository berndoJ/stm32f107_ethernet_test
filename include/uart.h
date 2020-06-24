// uart.h

#if !defined(__UART_H)
#define __UART_H

#include <stdint.h>

void sys_uart_init(void);
void sys_uart_puts(uint32_t usart, char *str);

#endif // __UART_H