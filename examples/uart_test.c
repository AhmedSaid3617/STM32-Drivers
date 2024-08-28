#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"

UART_Init_t uart_init_handle;
GPIO_Init_t gpio_init_handle;

int main()
{
    uint8_t rec_char = 0;
    RCC_USART3_ENABLE();
    RCC_PORTA_ENABLE();
    RCC_PORTB_ENABLE();

    // PA8 OUT
    gpio_init_handle.mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_handle.gpio_base = GPIOA;
    gpio_init_handle.pin = 8;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    GPIO_init(&gpio_init_handle);

    // PB10 (TX) AFIO Pull Push
    gpio_init_handle.gpio_base = GPIOB;
    gpio_init_handle.mode = GPIO_MODE_AFIO_PP;
    gpio_init_handle.pin = 10;
    GPIO_init(&gpio_init_handle);

    // PB11 (RX) GPIO Input floating
    gpio_init_handle.mode = GPIO_MODE_INPUT_FLOATING;
    gpio_init_handle.pin = 11;
    GPIO_init(&gpio_init_handle);

    // Initialize USART3
    uart_init_handle.baud_rate = 9600;
    uart_init_handle.USART_base = USART3;
    uart_init_handle.mode = UART_MODE_FULL_DUPLEX;
    UART_Init(&uart_init_handle);

    while (1)
    {
        if (UART_receive_byte(USART3, &rec_char) == UART_STATUS_SUCCESS)
        {
            if (rec_char == 'B')
            {
                GPIO_write_pin(GPIOA, 8, 1);
                SysTick_delay_ms(3000);
                GPIO_write_pin(GPIOA, 8, 0);
                UART_send_byte(USART3, 'H');
            }
        }
    }

    return 0;
}

void HardFault_Handler()
{
    RCC_PORTC_ENABLE();
    GPIO_Init_t gpio_init_handle;
    gpio_init_handle.gpio_base = GPIOC;
    gpio_init_handle.mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_handle.pin = 13;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    GPIO_init(&gpio_init_handle);
    while (1)
    {
        GPIO_write_pin(GPIOC, 13, 1);
        SysTick_delay_ms(1000);
        GPIO_write_pin(GPIOC, 13, 0);
        SysTick_delay_ms(1000);
    };
}
