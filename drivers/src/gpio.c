#include "gpio.h"

/**
 * @brief Initialize a GPIO pin to the specified mode.
 * @param gpio_base Address to the base of the GPIO port.
 * @param pin Pin number to be initialized.
 * @param mode In/Out, Pull Push/Open Drain.
 * @param pull Input pin pull-down/pull-up/floating.
 */
void GPIO_Init(GPIO_TypeDef* gpio_base, int pin, GPIO_MODE mode, GPIO_PULL pull){
    uint8_t control_data = 0;
    uint16_t odr_r = 0;
    switch (mode)
    {
    case GPIO_MODE_ANALOG:
        control_data = 0;
        break;
    
    case GPIO_MODE_INPUT:
        if (pull == GPIO_PULL_DOWN)
        {
            control_data = 0b1000ul;
            odr_r = gpio_base->ODR & ~(1<<pin);     // Set odr_r to the ODR with this bit reset.
        }
        else if (pull == GPIO_PULL_UP)
        {
            control_data = 0b1000ul;
            odr_r = gpio_base->ODR | (1<<pin);     // Set odr_r to the ODR with this bit set.
        }
        else{
            control_data = 0b0100ul;
        }
        break;

    case GPIO_MODE_OUTPUT_OD:
        control_data = 0b0101;

    case GPIO_MODE_OUTPUT_PP:
        control_data = 0b0001;
    default:
        break;
    }

    if (pin < 8)
    {
        gpio_base->CRL &= ~(0xF << (pin*4));
        gpio_base->CRL |= (control_data << (pin * 4));
    }
    else {
        gpio_base->CRH &= ~(0xF << ((pin-8) * 4));
        gpio_base->CRH |= (control_data << ((pin - 8) * 4));
    }
    gpio_base->ODR = odr_r;
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
