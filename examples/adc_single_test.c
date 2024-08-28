#include "rcc.h"
#include "gpio.h"
#include "systick.h"
#include "uart.h"
#include "adc.h"
#include "printf.h"
#include "nvic.h"

float voltage;
GPIO_Init_t gpio_init_handle;
UART_Init_t uart_init_handle;
ADC_init_typedef adc_init_handle;
char string[100] = "hello";

int main()
{
    RCC_ADC1_ENABLE();
    RCC_PORTA_ENABLE();
    RCC_PORTB_ENABLE();
    RCC_USART3_ENABLE();

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

    adc_init_handle.ADC_base = ADC1;
    adc_init_handle.channel_num = 2;
    adc_init_handle.mode = ADC_MODE_CONT;
    ADC_init(&adc_init_handle);

    while (1)
    {

        voltage = (ADC_read_single(ADC1) / 4096.0) * 3.3f;

        sprintf_(string, "Voltage: %.4f\n", voltage);
        UART_printf(USART3, string);
        SysTick_delay_ms(200);
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

void _putchar(char character)
{
    UART_send_byte(USART3, character);
}