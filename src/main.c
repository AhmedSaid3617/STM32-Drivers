#include "rcc.h"
#include "gpio.h"
#include "i2c.h"
#include "systick.h"

GPIO_Init_t gpio_init_handle;

char arr[12] = "Hello world";

void HardFault_Handler();

int main()
{
    RCC_I2C1_ENABLE();
    RCC_PORTB_ENABLE();

    // PB6 (SCL), PB7 SDA AFIO open drain.
    gpio_init_handle.gpio_base = GPIOB;
    gpio_init_handle.mode = GPIO_MODE_AFIO_OD;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    gpio_init_handle.pin = 6;
    GPIO_init(&gpio_init_handle);

    gpio_init_handle.pin = 7;
    GPIO_init(&gpio_init_handle);

    I2C_init(I2C1);

    while (1)
    {

        if (I2C_master_send(I2C1, 8, arr, 20) == I2C_STATUS_NACK)
        {
            HardFault_Handler();
        }

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
