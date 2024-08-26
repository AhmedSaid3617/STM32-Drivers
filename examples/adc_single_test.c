#include "rcc.h"
#include "gpio.h"
#include "systick.h"
#include "uart.h"
#include "adc.h"
#include "printf.h"

float voltage;
GPIO_Init_t gpio_init_handle;
UART_Init_t uart_init_handle;
char string[100] = "hello";

int main()
{
    RCC_ADC1_ENABLE();
    RCC_PORTA_ENABLE();
    RCC_PORTB_ENABLE();
    RCC_USART3_ENABLE();

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

    // PA0 input analog.
    gpio_init_handle.gpio_base = GPIOA;
    gpio_init_handle.mode = GPIO_MODE_INPUT_ANALOG;
    gpio_init_handle.pin = 0;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    GPIO_init(&gpio_init_handle);

    ADC1->CR2 |= 1 << 0; // Start ADC (ADON = 1)

    for (int i = 0; i < 100; i++)
    {
        // Wait for 2 ADC cycles.
    }

    ADC1->CR2 |= 1 << 2; // Calibrate ADC

    for (int i = 0; i < 100; i++)
    {
        // Wait for some time.
    }

    // Choose channel 1 to be sampled.
    //ADC1->SQR3 |= 1;

    while (1)
    {
        ADC1->CR2 |= 1 << 0; // Start ADC (ADON = 1)

        while (!(ADC1->SR & 1<<1))  // Wait until EOC
        {

        }

        voltage = (ADC1->DR/4096.0)*3.3f;
       
        sprintf_(string, "Voltage: %.2f\n", voltage);
        UART_printf(USART3, string);
        SysTick_delay_ms(1000);
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