#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"
#include "i2c.h"

void SysClk_init();

UART_Init_t uart_init_handle;
GPIO_Init_t gpio_init_handle;
I2C_init_t i2c_init_handle;
uint8_t data_byte = 0x40;
uint8_t data[1025] = {};
uint8_t ticks = 0;

int main()
{
    SysClk_init();
    RCC_I2C1_ENABLE();
    RCC_USART3_ENABLE();
    RCC_PORTA_ENABLE();
    RCC_PORTB_ENABLE();

    // Initialize I2C1 module.
    i2c_init_handle.I2C_base = I2C1;
    i2c_init_handle.mode = I2C_MODE_MASTER;
    I2C_init(I2C1);

    // Initialize USART3
    uart_init_handle.USART_base = USART3;
    uart_init_handle.baud_rate = 9600;
    uart_init_handle.direction = UART_DIR_TX;
    uart_init_handle.mode = UART_MODE_POLLING;
    UART_Init(&uart_init_handle);

    // PA8 Out
    gpio_init_handle.gpio_base = GPIOA;
    gpio_init_handle.mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_handle.pin = 8;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    GPIO_init(&gpio_init_handle);

    // PB10 (TX) AFIO Pull Push
    UART_TX_cfg(GPIOB, 10);

    uint8_t commands[] = {0x00, 0xAE, 0xD5, 0xF0, 0xA8, 64 - 1, 0x8D, 0x14, 0xAF, 0xA4, 0x20, 0x00};
    uint8_t start[] = {0x00, 0x21, 0, 127, 0x22, 0, 7};

    I2C_master_send(I2C1, 0x3C, &commands, 12);
    I2C_master_send(I2C1, 0x3C, &start, 7);
    I2C_master_send(I2C1, 0x3C, &data_byte, 1025);

    while (1)
    {
        for (int i = 0; i < 1024; i++)
        {
            if (ticks % 2 == 0)
            {
                data[i] = 0xAA;
            }
            else
            {
                data[i] = 0x55;
            }
        }

        I2C_master_send(I2C1, 0x3C, &start, 7);
        I2C_master_send(I2C1, 0x3C, &data_byte, 1025);
        /* GPIO_write_pin(GPIOA, 8, 1);
        SysTick_delay_ms(500);
        GPIO_write_pin(GPIOA, 8, 0);
        SysTick_delay_ms(500); */
        SysTick_delay_ms(1000);
        ticks++;
    }

    return 0;
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
