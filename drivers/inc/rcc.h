#ifndef RCC_H
#define RCC_H

#include "stm32f103c6.h"

// Register addresses.

#define RCC_CFGR        *((volatile uint32_t*)(RCC_BASE+0x04))
#define RCC_APB2ENR     *((volatile uint32_t*)(RCC_BASE+0x18)) 

// Function-like macros.
#define RCC_PORTA_ENABLE()  RCC_APB2ENR |= (1<<2)
#define RCC_PORTB_ENABLE()  RCC_APB2ENR |= (1<<3)
#define RCC_PORTC_ENABLE()  RCC_APB2ENR |= (1<<4)
#define RCC_AFIO_ENABLE()   RCC_APB2ENR |= (1<<0)


#endif