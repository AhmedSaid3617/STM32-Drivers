#include "gpio.h"
#include "rcc.h"
#include "utils.h"

GPIO_t *gpio_b = (GPIO_t *)GPIOB_BASE;

int main()
{
    RCC_PORTA_ENABLE();
    RCC_PORTC_ENABLE();

    // PA12 OUT
    GPIO_Init(GPIOA_BASE, 12, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    // PC15 IN
    GPIO_Init(GPIOC_BASE, 15, GPIO_MODE_INPUT, GPIO_PULL_UP);

    while (1)
    {

        if (GPIO_read_pin((GPIO_t*) GPIOC_BASE, 15))
        {
            GPIO_write_pin(GPIOA_BASE, 12, 1);
        }
        else {
            GPIO_write_pin(GPIOA_BASE, 12, 0);
        }
        
    }
    return 0;
}