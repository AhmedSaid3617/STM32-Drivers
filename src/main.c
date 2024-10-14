#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"
#include "i2c.h"

#include "FreeRTOS.h"
#include "task.h"

void SysClk_init();
void GreenTask(void *argument);
void RedTask(void *argument);

GPIO_Init_t gpio_init_handle;

int main()
{
    SysClk_init();
    RCC_PORTB_ENABLE();

    // PB1 Out
    gpio_init_handle.gpio_base = GPIOB;
    gpio_init_handle.mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_handle.pin = 1;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    GPIO_init(&gpio_init_handle);

    // PB12 Out
    gpio_init_handle.pin = 12;
    GPIO_init(&gpio_init_handle);

    xTaskCreate(RedTask, "Red Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(GreenTask, "Green Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    while (1)
    {
    }

    return 0;
}

void GreenTask(void *argument)
{
    while (1)
    {
        GPIO_write_pin(GPIOB, 12, 1);

        for (int i = 0; i < 250000; i++)
        {
            /* code */
        }

        GPIO_write_pin(GPIOB, 12, 0);

        for (int i = 0; i < 250000; i++)
        {
            /* code */
        }
    }
}

void RedTask(void *argument)
{
    while (1)
    {
        GPIO_write_pin(GPIOB, 1, 1);

        for (int i = 0; i < 100000; i++)
        {
            /* code */
        }

        GPIO_write_pin(GPIOB, 1, 0);

        for (int i = 0; i < 100000; i++)
        {
            /* code */
        }
    }
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

/* void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    HardFault_Handler();
}
 */