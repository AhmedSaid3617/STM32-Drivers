#include "gpio.h"
#include "rcc.h"
#include "utils.h"
#include "systick.h"
#include "nvic.h"

uint8_t pin = 1;

int main()
{
    RCC_PORTA_ENABLE();

    GPIO_Init(GPIOA, 12, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);
    SysTick_interrupt_init(1000);
    while (1)
    {
        GPIO_write_pin(GPIOA, 12, pin);
    }
    return 0;
}

void SysTick_Handler()
{
    pin = !pin; 
}
