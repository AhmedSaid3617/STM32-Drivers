#ifndef RCC_H
#define RCC_H

#include "stm32f103c6.h"

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;


} RCC_TypeDef;

// Defining modules.

#define RCC ((RCC_TypeDef*)(RCC_BASE))

// Function-like macros.

#define RCC_PORTA_ENABLE()  RCC->APB2ENR |= (1<<2)
#define RCC_PORTB_ENABLE()  RCC->APB2ENR |= (1<<3)
#define RCC_PORTC_ENABLE()  RCC->APB2ENR |= (1<<4)

#define RCC_AFIO_ENABLE()   RCC->APB2ENR |= (1<<0)

#define RCC_USART1_ENABLE() RCC->APB2ENR |= (1<<14)
#define RCC_USART2_ENABLE() RCC->APB1ENR |= (1<<17)
#define RCC_USART3_ENABLE() RCC->APB1ENR |= (1<<18)

#define RCC_I2C1_ENABLE()   RCC->APB1ENR |= (1<<21)
#define RCC_I2C2_ENABLE()   RCC->APB1ENR |= (1<<22)

#define RCC_ADC1_ENABLE()   RCC->APB2ENR |= (1<<9)
#define RCC_ADC2_ENABLE()   RCC->APB2ENR |= (1<<10)

#define RCC_TIM2_ENABLE()   RCC->APB1ENR |= (1<<0)

#define RCC_DMA1_ENABLE()   RCC->AHBENR |= (1<<0)

#endif