#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define APB2PERIPH_BASE       (0x40010000UL)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x00000800UL)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x00000C00UL)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x00001000UL)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x00001400UL)

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT_10MHZ,
    GPIO_MODE_OUTPUT_2MHZ,
    GPIO_MODE_OUTPUT_50MHZ
} GPIO_Mode;

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



#endif