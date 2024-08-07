#include "keypad.h"

/**
 * @brief Initialize keypad. GPIO port is defined in header file. Column pins must be connected to pins 0-4 of the GPIO port.
 */
void Keypad_init()
{
    // Port A0-4 input pulled down.
    for (int i = 0; i <= 4; i++)
    {
        GPIO_Init(ROW_PORT, i, GPIO_MODE_INPUT, GPIO_PULL_DOWN);
    }

    // Port A5-8 output pp.
    for (int i = 5; i <= 8; i++)
    {
        GPIO_Init(COLUMN_PORT, i, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);
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
