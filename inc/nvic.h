#ifndef NVIC_H
#define NVIC_H

#include "core_m3.h"

void _enable_irq();
void _disable_irq();

void NVIC_enable_IRQ(int IRQn);

#endif