#ifndef RCC_H
#define RCC_H

#include "stm32f103c6.h"

// Register addresses.

#define RCC_CFGR        *((volatile uint32_t*)(RCC_BASE+0x04))
#define RCC_APB2ENR     *((volatile uint32_t*)(RCC_BASE+0x18))
#define RCC_APB1ENR     *((volatile uint32_t*)(RCC_BASE+0x1C))

// Function-like macros.

#define RCC_PORTA_ENABLE()  RCC_APB2ENR |= (1<<2)
#define RCC_PORTB_ENABLE()  RCC_APB2ENR |= (1<<3)
#define RCC_PORTC_ENABLE()  RCC_APB2ENR |= (1<<4)

#define RCC_AFIO_ENABLE()   RCC_APB2ENR |= (1<<0)

#define RCC_USART1_ENABLE() RCC_APB2ENR |= (1<<14)
#define RCC_USART2_ENABLE() RCC_APB1ENR |= (1<<17)
#define RCC_USART3_ENABLE() RCC_APB1ENR |= (1<<18)

#define RCC_I2C1_ENABLE()   RCC_APB1ENR |= (1<<21)
#define RCC_I2C2_ENABLE()   RCC_APB1ENR |= (1<<22)

#define RCC_ADC1_ENABLE()   RCC_APB2ENR |= (1<<9)
#define RCC_ADC2_ENABLE()   RCC_APB2ENR |= (1<<10)

#endif