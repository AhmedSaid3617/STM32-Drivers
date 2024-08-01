#include "gpio.h"
#include "rcc.h"
#include "utils.h"
#include "stm32f103c6.h"
#include "afio.h"
#include "exti.h"
#include "nvic.h"

int main()
{
    // Set up clocks for peripherals.
    RCC_PORTA_ENABLE();
    RCC_PORTB_ENABLE();
    RCC_PORTC_ENABLE();
    RCC_AFIO_ENABLE();

    // Enable global interrupts.
    _enable_irq();

    // PA12 OUT
    GPIO_Init(GPIOA_BASE, 12, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);
    // PB0 OUT
    GPIO_Init(GPIOB_BASE, 1, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    // PC15 IN
    GPIO_Init(GPIOC_BASE, 15, GPIO_MODE_INPUT, GPIO_PULL_UP);
    // PA0 IN
    GPIO_Init(GPIOA, 0, GPIO_MODE_INPUT, GPIO_PULL_DOWN);

    // EXTI 15 setup
    EXTI_enable(EXTI_PORTC, 15, 0, 1);
    NVIC_enable_IRQ(EXTI15_10_IRQn, 1);

    // EXTI 0 setup
    EXTI_enable(EXTI_PORTA, 0, 1, 0);
    NVIC_enable_IRQ(EXTI0_IRQn, 10);

    while (1)
    {
        
    }
    return 0;
}

void EXTI0_IRQHandler()
{
    GPIO_write_pin(GPIOB_BASE, 1, 1);
    for (volatile int i = 0; i < 1000000; i++);
    GPIO_write_pin(GPIOB_BASE, 1, 0);
    EXTI_CLEAR_PENDING(0);
    NVIC_CLEAR_PENDING(EXTI0_IRQn);
}

void EXTI15_10_IRQHandler()
{
    GPIO_write_pin(GPIOA_BASE, 12, 1);
    for (volatile int i = 0; i < 1000000; i++);
    GPIO_write_pin(GPIOA_BASE, 12, 0);
    EXTI_CLEAR_PENDING(15);
    NVIC_CLEAR_PENDING(EXTI15_10_IRQn);
}