#include "gpio.h"

/**
 * @brief Initialize a GPIO pin.
 * 
 * @param init_handle Parameters for initialization.
 */
void GPIO_init(GPIO_Init_t* init_handle){
    uint8_t control = 0;
    uint32_t odr_r = 0;
    if (init_handle->mode > GPIO_MODE_INPUT_PULL_DOWN)  // If mode is output.
    {
        control |= init_handle->speed;                  // Then set the speed.
        // If  speed wasn't set by user, then set it to 10MHZ.
        if (init_handle->speed == 0)
        {
            control |= GPIO_SPEED_10MHZ;
        }
        
    }

    switch (init_handle->mode)
    {
    case GPIO_MODE_INPUT_FLOATING:
        control |= 0b0100;
        break;
    
    case GPIO_MODE_INPUT_PULL_UP:
        control |= 0b1000;
        odr_r = init_handle->gpio_base->ODR | (1<<init_handle->pin);
        break;
    
    case GPIO_MODE_INPUT_PULL_DOWN:
        control |= 0b1000;
        odr_r = init_handle->gpio_base->ODR & ~(1<<init_handle->pin);
        break;
    
    case GPIO_MODE_OUTPUT_OD:
        control |= 0b0100;
        break;

    case GPIO_MODE_AFIO_PP:
        control |= 0b1000;
        break;
    
    case GPIO_MODE_AFIO_OD:
        control |= 0b1100;
        break;

    default:
        break;
    }
    
    if (init_handle->pin < 8)
    {
        init_handle->gpio_base->CRL &= ~(0xF << (init_handle->pin*4));
        init_handle->gpio_base->CRL |= (control << (init_handle->pin * 4));
    }
    else {
        init_handle->gpio_base->CRH &= ~(0xF << ((init_handle->pin-8) * 4));
        init_handle->gpio_base->CRH |= (control << ((init_handle->pin - 8) * 4));
    }
    init_handle->gpio_base->ODR = odr_r;

}

/**
 * @brief Read the boolean value from an input pin.
 * @return The value at the gpio port masked for this pin.
 */
uint32_t GPIO_read_pin(GPIO_TypeDef* gpio_base, uint8_t pin){
    return gpio_base->IDR & (1<<pin);
}

/**
 * @brief Write one or zero to a gpio pin configured to output.
 * @param value Value to be written to the pin, should be either 1 or 0.
 */
void GPIO_write_pin(GPIO_TypeDef* gpio_base, uint8_t pin, uint8_t value){
    if (value == 1)
    {
        SETBIT(gpio_base->ODR, pin);
    }
    else
    {
        RESETBIT(gpio_base->ODR, pin);
    }
}
