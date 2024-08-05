#include "gpio.h"
#include "rcc.h"
#include "utils.h"
#include "systick.h"

int main()
{
    uint8_t pin = 1;
    RCC_PORTA_ENABLE();

    GPIO_Init(GPIOA, 12, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    while (1)
    {
        GPIO_write_pin(GPIOA, 12, pin);
        SysTick_delay_ms(1000);
        pin = !pin;

    }
    return 0;
}
