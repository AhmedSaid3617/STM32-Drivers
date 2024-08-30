#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "nvic.h"
#include "timer.h"
#include "systick.h"

GPIO_Init_t gpio_init_handle;
UART_Init_t uart_init_handle;
timer_init_typedef timer_init_handle;
char string[14] = "H\n";

void SysClk_init();

int main()
{
    SysClk_init();
    RCC_PORTB_ENABLE();
    RCC_USART3_ENABLE();
    RCC_TIM2_ENABLE();

    _enable_irq();

    // PB10 (TX) AFIO Pull Push
    gpio_init_handle.gpio_base = GPIOB;
    gpio_init_handle.mode = GPIO_MODE_AFIO_PP;
    gpio_init_handle.pin = 10;
    GPIO_init(&gpio_init_handle);

    // Initialize USART3
    uart_init_handle.baud_rate = 9600;
    uart_init_handle.USART_base = USART3;
    uart_init_handle.mode = UART_MODE_TX;
    UART_Init(&uart_init_handle);

    NVIC_enable_IRQ(TIM2_IRQn, 2);

    timer_init_handle.timer_base = TIM2;
    timer_init_handle.prescaler = 7999; // Prescaler = 8000 (8Mhz/8000 = 1000 Hz).
    timer_init_handle.period = 499; // Reload value = 999 (1000 ticks).

    timer_init(&timer_init_handle);

    while (1)
    {
        int x = 10;
    }

    return 0;
}

void TIM2_IRQHandler(){
    TIM2->SR &= ~(1<<0); // Clear update interrupt flag.
    UART_printf(USART3, string);
    NVIC_CLEAR_PENDING(TIM2_IRQn);
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

void _putchar(char character)
{
    //UART_send_byte(USART3, character);
}