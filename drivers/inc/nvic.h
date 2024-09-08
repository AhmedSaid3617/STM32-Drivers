#ifndef NVIC_H
#define NVIC_H

#include "core_m3.h"
#include "stm32f103c6.h"

// Function-like macros

// Clear the pending interrupt request (IRQn).
#define NVIC_CLEAR_PENDING(IRQn) NVIC->ICPR[IRQn >> 5] = 1 << (IRQn & 32UL)

void _enable_irq();
void _disable_irq();

extern inline void NVIC_enable_IRQ(IRQn_Type IRQn, uint8_t priority);
extern inline void NVIC_disable_IRQ(IRQn_Type IRQn);

#endif