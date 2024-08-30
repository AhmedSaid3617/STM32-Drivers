#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"

void SysClk_init();

UART_Init_t uart_init_handle;
GPIO_Init_t gpio_init_handle;

int main()
{
    SysClk_init();

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
    UART_TX_cfg(GPIOB, 10);

    // PB11 (RX) GPIO Input floating
    UART_RX_cfg(GPIOB, 11);

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

void SysClk_init(){
    RCC->CR |= 1<<16; // Turn HSE on.
    while (!(RCC->CR & 1<<17))
    {
        // While HSE not ready, wait.
    }
    
    RCC->CFGR |= 1; // Choose HSE as the source.
    RCC->CR &= ~(1<<0); // Turnoff HSI. (To reduce power consumption).
 
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
