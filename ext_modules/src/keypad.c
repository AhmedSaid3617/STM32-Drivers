#include "keypad.h"
// TODO: Test the new gpio init function with keypad module.

/**
 * @brief Initialize keypad. GPIO port is defined in header file. Column pins must be connected to pins 0-4 of the GPIO port.
 */
void Keypad_init()
{
    GPIO_Init_t gpio_init_handle;

    // Port A0-4 input pulled down.
    gpio_init_handle.gpio_base = GPIOA;
    gpio_init_handle.mode = GPIO_MODE_INPUT_PULL_DOWN;
    for (int i = 0; i <= 4; i++)
    {
        gpio_init_handle.pin = i;
        GPIO_init(&gpio_init_handle);
    }

    // Port A5-8 output pp.
    gpio_init_handle.mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    for (int i = 5; i <= 8; i++)
    {
        gpio_init_handle.pin = i;
        GPIO_init(&gpio_init_handle);
    }
}

/**
 * @brief Read value from keypad.
 * @retval The key currently pressed from enum Keypad_key.
 */
Keypad_key Keypad_read()
{
    volatile uint16_t key = 0;

    for (int i = 0; i <= 3; i++)
    {
        GPIO_write_pin(COLUMN_PORT, i + 5, 1);
        if (ROW_PORT->IDR & 0b11111)
        {
            key = ROW_PORT->IDR & 0b11111;
            key |= (1 << i) << 5;
        }

        GPIO_write_pin(COLUMN_PORT, i + 5, 0);
    }

    return key;
}
