#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"

UART_Init_t init_handle;

int main()
{
    RCC_USART2_ENABLE();
    RCC_PORTA_ENABLE();
    RCC_PORTC_ENABLE();

    // PC13 OUT
    GPIO_Init(GPIOC, 13, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    // PA8 OUT
    GPIO_Init(GPIOA, 8, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    // PA2 (TX) AFIO Pull Push
    GPIOA->CRL &= 0xF << (2 * 4);
    GPIOA->CRL |= 0x9 << (2 * 4);

    // PA3 (RX) GPIO Input floating
    GPIO_Init(GPIOA, 3, GPIO_MODE_INPUT, GPIO_PULL_FLOATING);

    init_handle.baud_rate = 19200;
    init_handle.USART_base = USART2_BASE;

    // USART2->CR1 |= (1 << 13);   // Enable UART
    /* USART2->BRR |= 52 << 4;     // Configure baud rate.
    USART2->BRR |= 1; */
    UART_Init(&init_handle);
    USART2->CR1 |= (1 << 2); // Enable RX

    while (1)
    {
        if (USART2->SR & (1 << 5))
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

void HardFault_Handler()
{
    while (1)
    {
        GPIO_write_pin(GPIOC, 13, 1);
        SysTick_delay_ms(1000);
        GPIO_write_pin(GPIOC, 13, 0);
        SysTick_delay_ms(1000);
    };
}
