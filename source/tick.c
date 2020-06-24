#include "tick.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>

// Declare interrupt for systick.
void sys_tick_handler(void);

static volatile uint64_t _systick = 0;

void sys_tick_init(void)
{
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    STK_CVR = 0;
    systick_set_reload(rcc_ahb_frequency / 1000 - 1);
    systick_interrupt_enable();
    systick_counter_enable();
}

uint64_t sys_get_tick(void)
{
    return _systick;
}

void sys_tick_delay(uint64_t ms)
{
    const uint64_t wait = _systick + ms;
    while (_systick < wait);
}

void sys_tick_handler(void)
{
    _systick++;
}