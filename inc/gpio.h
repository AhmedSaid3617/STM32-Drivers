#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include "utils.h"

#define APB2PERIPH_BASE       (0x40010000UL)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x00000800UL)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x00000C00UL)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x00001000UL)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x00001400UL)

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

typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_t;

typedef struct 
{
    /* data */
} GPIO_init_t;

void GPIO_Init(GPIO_t* GPIO_BASE, int pin, GPIO_MODE mode, GPIO_PULL pull);
uint32_t GPIO_read_pin(GPIO_t* gpio_base, uint8_t pin);
void GPIO_write_pin(GPIO_t* gpio_base, uint8_t pin, uint8_t value);

#endif