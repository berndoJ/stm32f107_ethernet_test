#if !defined(__SYSTICK_H)
#define __SYSTICK_H

#include <stdint.h>

void sys_tick_init(void);
uint64_t sys_get_tick(void);
void sys_tick_delay(uint64_t ms);

#endif // __SYSTICK_H