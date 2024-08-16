#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include "utils.h"
#include "stm32f103c6.h"

// Defining modules.

#define GPIOA ((GPIO_TypeDef*)(GPIOA_BASE))
#define GPIOB ((GPIO_TypeDef*)(GPIOB_BASE))
#define GPIOC ((GPIO_TypeDef*)(GPIOC_BASE))

/**
 * @brief Frequency for GPIO pin, determines the transition slope.
 */
typedef enum {
    GPIO_SPEED_10MHZ = 1,
    GPIO_SPEED_2MHZ,
    GPIO_SPEED_50MHZ
} GPIO_speed;

/**
 * @brief Operating modes for GPIO. PP -> Pull Push, OD -> Open Drain.
 */
typedef enum {
    GPIO_MODE_INPUT_ANALOG,
    GPIO_MODE_INPUT_FLOATING,
    GPIO_MODE_INPUT_PULL_UP,
    GPIO_MODE_INPUT_PULL_DOWN,
    GPIO_MODE_OUTPUT_PP,
    GPIO_MODE_OUTPUT_OD,
    GPIO_MODE_AFIO_PP,
    GPIO_MODE_AFIO_OD
}GPIO_mode;

/**
 * @brief Parameters to initialize a GPIO pin.
 */
typedef struct
{
    uint32_t pin;
    GPIO_mode mode;
    GPIO_speed speed;
    GPIO_TypeDef* gpio_base;
} GPIO_Init_t;


void GPIO_init(GPIO_Init_t* init_handle);
uint32_t GPIO_read_pin(GPIO_TypeDef* gpio_base, uint8_t pin);
void GPIO_write_pin(GPIO_TypeDef* gpio_base, uint8_t pin, uint8_t value);

#endif