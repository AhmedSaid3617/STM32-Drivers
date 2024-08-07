#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>
#include "stm32f103c6.h"

// Module definitions.

#define EXTI ((EXTI_TypeDef*)EXTI_BASE)

// Function-like macros.

// Clear the pending status for interrupts at this EXTI line.
#define EXTI_CLEAR_PENDING(pin) EXTI->PR |= 1<<pin

typedef enum {
    EXTI_PORTA,
    EXTI_PORTB,
    EXTI_PORTC
} EXTI_Port;

void EXTI_enable(EXTI_Port port, uint8_t pin, uint8_t rising_edge, uint8_t falling_edge);

#endif