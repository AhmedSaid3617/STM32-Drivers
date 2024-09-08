#ifndef SYSTICK_H
#define SYSTICK_H

#include "core_m3.h"
#include "utils.h"
#include "stm32f103c6.h"

/* Functions */

void SysTick_delay_ms(int ms);
void SysTick_interrupt_init(int ms);

// TODO: Systick_delay_us

#endif