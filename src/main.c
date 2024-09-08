#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"
#include "timer.h"
#include "nvic.h"
#include "exti.h"
#include "printf.h"

#define TRIGGER 9
#define ECHO 10

void SysClk_init();

UART_Init_t uart_init_handle;
GPIO_Init_t gpio_init_handle;
timer_init_typedef timer_init_handle;

uint32_t ticks = 0;
uint32_t echo_delay = 0;
float distance = 0.0;
uint8_t distance_str[25] = {};

uint8_t message[10];

int main()
{
    SysClk_init();

    RCC_USART3_ENABLE();
    RCC_PORTA_ENABLE();
    RCC_PORTB_ENABLE();
    RCC_TIM2_ENABLE();
    RCC_AFIO_ENABLE();

    SysTick_interrupt_init(1);

    // PA8 OUT
    gpio_init_handle.mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_handle.gpio_base = GPIOA;
    gpio_init_handle.pin = 8;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    GPIO_init(&gpio_init_handle);

    // PA9 OUT
    gpio_init_handle.pin = TRIGGER;
    GPIO_init(&gpio_init_handle);

    // PA10 IN pull down
    gpio_init_handle.pin = ECHO;
    gpio_init_handle.mode = GPIO_MODE_INPUT_PULL_DOWN;
    GPIO_init(&gpio_init_handle);

    // PB10 (TX) AFIO Pull Push
    UART_TX_cfg(GPIOB, 10);

    // PB11 (RX) GPIO Input floating
    UART_RX_cfg(GPIOB, 11);

    // Initialize USART3
    uart_init_handle.baud_rate = 9600;
    uart_init_handle.USART_base = USART3;
    uart_init_handle.direction = UART_DIR_FULL_DUPLEX;
    uart_init_handle.mode = UART_MODE_DMA;
    UART_Init(&uart_init_handle);

    timer_init_handle.timer_base = TIM2;
    timer_init_handle.prescaler = 3;
    timer_init_handle.period = 60000;
    timer_init(&timer_init_handle);
    timer_reset(TIM2);
    NVIC_enable_IRQ(TIM2_IRQn, 1);

    // Enable EXTI for PA10.
    EXTI_enable(EXTI_PORTA, ECHO, 1, 1);
    //NVIC_enable_IRQ(EXTI15_10_IRQn, 2);

    while (1)
    {
        distance = (echo_delay / 2) / 58.0;
        sprintf(distance_str, "D: %.2f\n", distance);
    }

    return 0;
}

void SysTick_Handler()
{
    if (ticks % 1000 == 0)
    {
        UART_printf(USART3, distance_str);
    }

    if (ticks % 250 == 0)
    {
        echo_delay = TIM2->CNT;
        // Arm EXTI
        NVIC_enable_IRQ(EXTI15_10_IRQn, 2);

        // Send pulse.
        GPIO_write_pin(GPIOA, TRIGGER, 0);
        for (int i = 0; i < 20; i++)
        {
        }
        GPIO_write_pin(GPIOA, TRIGGER, 1);
        for (int i = 0; i < 100; i++)
        {
        }
        GPIO_write_pin(GPIOA, TRIGGER, 0);
    }

    ticks++;
}

/* void TIM2_IRQHandler()
{
    // timer_reset(TIM2);

    GPIO_write_pin(GPIOA, 8, 1);

    for (int i = 0; i < 100000; i++)
    {
        
    }

    GPIO_write_pin(GPIOA, 8, 0);

    NVIC_CLEAR_PENDING(TIM2_IRQn);
    NVIC_disable_IRQ(EXTI15_10_IRQn);
} */

void EXTI15_10_IRQHandler()
{
    if (GPIO_read_pin(GPIOA, ECHO))
    {
        // At rising edge, start timer.
        TIM2->CR1 |= 1 << 0; // Counter enable.
    }

    else
    {
        // At falling edge, record time and stop timer.
        echo_delay = TIM2->CNT;
        timer_reset(TIM2);
        NVIC_disable_IRQ(EXTI15_10_IRQn);
    }

    EXTI_CLEAR_PENDING(10);
    NVIC_CLEAR_PENDING(EXTI15_10_IRQn); 
}

void SysClk_init()
{
    RCC->CR |= 1 << 16; // Turn HSE on.
    while (!(RCC->CR & 1 << 17))
    {
        // While HSE not ready, wait.
    }

    RCC->CFGR |= 1;       // Choose HSE as the source.
    RCC->CR &= ~(1 << 0); // Turnoff HSI. (To reduce power consumption).
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
