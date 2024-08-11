#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"


int main()
{
    RCC_USART2_ENABLE();

    USART2->CR1 |= (1<<13);
    USART2->BRR |= 52 << 4;
    USART2->BRR |= 1;
    USART2->CR1 |= (1<<3);

    // PA2 TX

    while (1)
    {
        USART2->DR = 'A';
        SysTick_delay_ms(500);
        
    }

    return 0;
}
