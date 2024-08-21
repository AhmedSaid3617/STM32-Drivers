#include "rcc.h"
#include "gpio.h"
#include "i2c.h"
#include "systick.h"

GPIO_Init_t gpio_init_handle;

uint8_t received[7] = {};

void blink_led();

int main()
{
    RCC_I2C1_ENABLE();
    RCC_PORTB_ENABLE();

    // PB12 OUT PP
    gpio_init_handle.gpio_base = GPIOB;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    gpio_init_handle.pin = 12;
    gpio_init_handle.mode = GPIO_MODE_OUTPUT_PP;
    GPIO_init(&gpio_init_handle);

    I2C_init(I2C1);

    while (1)
    {
        SysTick_delay_ms(1000);

        if (I2C_master_receive(I2C1, 8, &received, 1) == I2C_STATUS_ERR)
        {
            blink_led();
        }

        if (received[0] == 'A')
        {
            received[0] = 'X';
            GPIO_write_pin(GPIOB, 12, 1);
            SysTick_delay_ms(500);
            GPIO_write_pin(GPIOB, 12, 0);
        }

    }

    return 0;
}

void blink_led()
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