#include "exti.h"
#include "afio.h"

/**
 * @brief Connects a pin to the External Interrupt module through AFIO and enables interrupts from it.
 * @param port GPIO port for the pin.
 * @param pin Pin number.
 * @param rising_edge Must be either 1 (rising edge triggers interrupt) or 0 (doesn't trigger interrupts).
 * @param falling_edge Must be either 1 (falling edge triggers interrupt) or 0 (doesn't trigger interrupts). 
 */
void EXTI_enable(EXTI_Port port, uint8_t pin, uint8_t rising_edge, uint8_t falling_edge){
    AFIO->EXTICR[pin/4] |= (port & 0xF) << (pin%4)*4;
    EXTI->IMR |= 1<<pin;
    EXTI->FTSR |= falling_edge << pin;
    EXTI->RTSR |= rising_edge << pin;
}