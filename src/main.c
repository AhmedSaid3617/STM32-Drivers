#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"

int main()
{
    RCC_USART2_ENABLE();
    RCC_PORTA_ENABLE();

    // PA8 OUT
    GPIO_Init(GPIOA, 8, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    // PA2 (TX) AFIO Pull Push
    GPIOA->CRL &= 0xF << (2 * 4);
    GPIOA->CRL |= 0x9 << (2 * 4);

    // PA3 (RX) GPIO Input floating
    GPIO_Init(GPIOA, 3, GPIO_MODE_INPUT, GPIO_PULL_FLOATING);

    USART2->CR1 |= (1 << 13);
    USART2->BRR |= 52 << 4;
    USART2->BRR |= 1;
    USART2->CR1 |= (1 << 2);

    while (1)
    {
        if (USART2->SR & (1<<5))
        {
            if (USART2->DR == 'A')
            {
                GPIO_write_pin(GPIOA, 8, 1);
                SysTick_delay_ms(100);
                GPIO_write_pin(GPIOA, 8, 0);
            }
        }

    }

    return 0;
}
