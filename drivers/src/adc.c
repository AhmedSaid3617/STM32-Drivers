#include "adc.h"

void ADC_init(ADC_init_typedef *init_handle)
{

    ADC_pin_cfg(init_handle); // Configure pin to analog input.

    init_handle->ADC_base->CR2 |= 1 << 0; // Start ADC (ADON = 1)

    for (int i = 0; i < 100; i++)
    {
        // Wait for 2 ADC cycles.
    }

    init_handle->ADC_base->CR2 |= 1 << 2; // Calibrate ADC

    for (int i = 0; i < 100; i++)
    {
        // Wait for some time.
        // TODO: figure out this time.
    }

    // Set channel to rank zero.
    init_handle->ADC_base->SQR3 |= init_handle->channel_num;

    if (init_handle->mode == ADC_MODE_CONT)
    {
        init_handle->ADC_base->CR2 |= 1 << 1; // Set CONT bit for continuous conversion.
        init_handle->ADC_base->CR2 |= 1 << 0; // Start ADC (ADON = 1).
    }
}

void ADC_pin_cfg(ADC_init_typedef *adc_init_handle)
{
    GPIO_Init_t gpio_init_handle;

    // Pin input analog.
    gpio_init_handle.gpio_base = GPIOA;
    gpio_init_handle.mode = GPIO_MODE_INPUT_ANALOG;
    gpio_init_handle.pin = adc_init_handle->channel_num;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    GPIO_init(&gpio_init_handle);
}

uint32_t ADC_read_single(ADC_TypeDef* adc_base)
{
    if (!(adc_base->CR2 & (1 << 1))) // If not continuous.
    {
        adc_base->CR2 |= 1 << 0; // Start ADC (ADON = 1)

        while (!(adc_base->SR & 1 << 1)) // Wait until EOC
        {
        }
    }
    return adc_base->DR;
}
