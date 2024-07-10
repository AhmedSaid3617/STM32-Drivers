#include "gpio.h"
#include "rcc.h"

GPIO_t* gpio_c = (GPIO_t*)GPIOC_BASE;

int main()
{
    RCC_PORTC_ENABLE();
    gpio_c->CRH |= (1<<20);
    gpio_c->ODR |= (1<<13);
    while (1)
    {
        gpio_c->BSRR |= (1<<13);
        for (volatile int i = 0; i < 100000; i++);

        gpio_c->BSRR &= ~(1<<29);
        for (volatile int i = 0; i < 100000; i++);
    }

    return 0;
}