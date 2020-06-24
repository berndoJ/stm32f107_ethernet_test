#include "syscalls.h"

#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/gpio.h>

ssize_t _write(int file, const char *ptr, ssize_t len)
{
    int i;

    // Check if the file that is being written to is actually stdout or stderr.
    if (file != STDOUT_FILENO && file != STDERR_FILENO)
    {
        errno = EIO;
        return -1;
    }

    // Print all chars to USART1.
    for (i = 0; i < len; i++)
    {
        // Send \r before any \n to avoid terminal problems.
        if (ptr[i] == '\n')
        {
            usart_send_blocking(USART1, '\r');
        }

        // Write the current char to USART.
        usart_send_blocking(USART1, ptr[i]);
    }

    return i;
}