#include "gpio.h"
#include "rcc.h"
#include "keypad.h"

int main()
{
    RCC_PORTA_ENABLE();
    RCC_PORTB_ENABLE();

    // PB1 OUT
    GPIO_Init(GPIOB, 1, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    // PA12 out
    GPIO_Init(GPIOA, 12, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    Keypad_init();

    while (1)
    {
        Keypad_key input_key = Keypad_read();
        if (input_key == KEYPAD_KEY_NONE)
        {
            GPIO_write_pin(GPIOB, 1, 1);
        }
        if (input_key == KEYPAD_KEY_LEFT)
        {
            GPIO_write_pin(GPIOA, 12, 1);
        }
    }

    return 0;
}
