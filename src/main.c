#include "gpio.h"
#include "rcc.h"

GPIO_t* gpio_c = (GPIO_t*)GPIOC_BASE;
GPIO_t* gpio_b = (GPIO_t*)GPIOB_BASE;
GPIO_t* gpio_a = (GPIO_t*)GPIOB_BASE;


int main()
{
    RCC_PORTC_ENABLE();
    gpio_c->CRH |= (1<<20);
    gpio_c->ODR |= (1<<13);

    RCC_PORTB_ENABLE();
    gpio_b->CRH &= ~(0xF);
    gpio_b->CRH |= (1<<0);
    gpio_b->ODR |= (1<<8);

    while (1)
    {
        gpio_c->ODR |= (1<<13);
        gpio_b->ODR &= ~(1<<8);
        for (volatile int i = 0; i < 1000000; i++);

        gpio_c->ODR &= ~(1<<13);
        gpio_b->ODR |= (1<<8);
        for (volatile int i = 0; i < 1000000; i++);
    } 
    return 0;
}