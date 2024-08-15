#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"

UART_Init_t init_handle;

int main()
{
    uint8_t rec_char = 0;
    RCC_USART2_ENABLE();
    RCC_PORTA_ENABLE();

    // PA8 OUT
    GPIO_Init(GPIOA, 8, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);

    // PA2 (TX) AFIO Pull Push
    GPIOA->CRL &= 0xF << (2 * 4);
    GPIOA->CRL |= 0x9 << (2 * 4);

    // PA3 (RX) GPIO Input floating
    GPIO_Init(GPIOA, 3, GPIO_MODE_INPUT, GPIO_PULL_FLOATING);

    // Initialize USART2
    init_handle.baud_rate = 9600;
    init_handle.USART_base = USART2_BASE;
    init_handle.mode = UART_MODE_FULL_DUPLEX;
    UART_Init(&init_handle);

    while (1)
    {
        if (UART_receive_byte(USART2, &rec_char) == UART_STATUS_SUCCESS)
        {
            if (rec_char == 'B')
            {
                GPIO_write_pin(GPIOA, 8, 1);
                SysTick_delay_ms(3000);
                GPIO_write_pin(GPIOA, 8, 0);
                UART_send_byte(USART2, 'H');
            }   
        }
    }

    return 0;
}

void HardFault_Handler()
{
    RCC_PORTC_ENABLE();
    GPIO_Init(GPIOC, 13, GPIO_MODE_OUTPUT_PP, GPIO_PULL_FLOATING);
    while (1)
    {
        GPIO_write_pin(GPIOC, 13, 1);
        SysTick_delay_ms(1000);
        GPIO_write_pin(GPIOC, 13, 0);
        SysTick_delay_ms(1000);
    };
}
