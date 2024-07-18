#include "gpio.h"
#include "rcc.h"

GPIO_t* gpio_c = (GPIO_t*)GPIOC_BASE;
GPIO_t* gpio_b = (GPIO_t*)GPIOB_BASE;
GPIO_t* gpio_a = (GPIO_t*)GPIOB_BASE;


int main()
{
    RCC_PORTC_ENABLE();
    gpio_c->CRH &= ~(0xF<<20);
    gpio_c->CRH |= (1<<20);

    RCC_PORTB_ENABLE();

    // PB8 OUT
    gpio_b->CRH &= ~(0xF);
    gpio_b->CRH |= (1<<0);

    //PB10 IN
    gpio_b->CRH &= ~(0xF<<8);
    gpio_b->CRH |= (0x8<<8);


    while (1)
    {

        if (gpio_b->IDR & (1<<10))
        {
            gpio_b->ODR |= (1<<8);
        }
        else
        {
            gpio_b->ODR &= ~(1<<8);
            
        }
    } 
    return 0;
}