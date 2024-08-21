#include "rcc.h"
#include "gpio.h"
#include "systick.h"
#include "uart.h"

UART_Init_t uart_init_handle;
GPIO_Init_t gpio_init_handle;
uint8_t string[12] = "hello world";

int main()
{
    RCC_PORTB_ENABLE();
    RCC_USART3_ENABLE();

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
        SysTick_delay_ms(1000);
        UART_printf(USART3, string);
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