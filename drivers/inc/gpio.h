#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include "utils.h"
#include "stm32f103c6.h"

// Defining modules.

#define GPIOA ((GPIO_TypeDef*)(GPIOA_BASE))
#define GPIOB ((GPIO_TypeDef*)(GPIOB_BASE))
#define GPIOC ((GPIO_TypeDef*)(GPIOC_BASE))

typedef enum {
    GPIO_MODE_ANALOG,
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT_PP,
    GPIO_MODE_OUTPUT_OD,
    GPIO_MODE_AF_PP,
    GPIO_MODE_AF_OD
} GPIO_MODE;

typedef enum {
    GPIO_PULL_FLOATING,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} GPIO_PULL;

typedef enum {
    GPIO_SPEED_10MHZ = 1,
    GPIO_SPEED_2MHZ,
    GPIO_SPEED_50MHZ
} GPIO_SPEED;

void GPIO_Init(GPIO_TypeDef* GPIO_BASE, int pin, GPIO_MODE mode, GPIO_PULL pull);
uint32_t GPIO_read_pin(GPIO_TypeDef* gpio_base, uint8_t pin);
void GPIO_write_pin(GPIO_TypeDef* gpio_base, uint8_t pin, uint8_t value);

#endif