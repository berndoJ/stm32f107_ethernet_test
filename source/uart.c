#include "uart.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

void sys_uart_init(void)
{
    // Setup USART1
    usart_set_baudrate(USART1, 115200);
    usart_set_databits(USART1, 8);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_mode(USART1, USART_MODE_TX_RX);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
    usart_enable(USART1);
}

void sys_uart_puts(uint32_t usart, char *str)
{
    while (*str)
    {
        usart_send_blocking(usart, *str);
        str++;
    }
}