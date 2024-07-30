#include "gpio.h"
#include "rcc.h"
#include "utils.h"
#include "stm32f103c6.h"
#include "afio.h"
#include "exti.h"
#include "interrupts.h"

int main()
{
    RCC_PORTA_ENABLE();
    RCC_PORTB_ENABLE();
    RCC_PORTC_ENABLE();
    RCC_AFIO_ENABLE();

    // PA12 OUT
    GPIO_Init(GPIOA_BASE, 12, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);
    // PB0 OUT
    GPIO_Init(GPIOB_BASE, 1, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    // PC15 IN
    GPIO_Init(GPIOC_BASE, 15, GPIO_MODE_INPUT, GPIO_PULL_UP);

    // EXTI setup
    _enable_irq();
    AFIO->EXTICR[3] |= (0b0010 << 12);
    EXTI->IMR |= 1 << 15;
    EXTI->FTSR |= 1 << 15;
    NVIC_ISER[1] |= 1 << 8;

    while (1)
    {
        GPIO_write_pin(GPIOB_BASE, 1, 1);
        for (int i = 0; i < 100000; i++)
            ;
        GPIO_write_pin(GPIOB_BASE, 1, 0);
        for (int i = 0; i < 100000; i++)
            ;
    }
    return 0;
}

void EXTI15_10_IRQHandler()
{
    GPIO_write_pin(GPIOA_BASE, 12, 1);
    for (int i = 0; i < 1000000; i++)
        ;
    GPIO_write_pin(GPIOA_BASE, 12, 0);
    EXTI->PR |= 1<<15;
    NVIC_ICPR[1] = 1 << 8;
}