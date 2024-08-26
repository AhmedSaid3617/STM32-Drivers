#ifndef ADC_H
#define ADC_H

#include "stm32f103c6.h"
#include "gpio.h"

// Defining modules.

#define ADC1 ((ADC_TypeDef*)(ADC1_BASE))

// Enums

typedef enum {
    ADC_MODE_SINGLE,
    ADC_MODE_CONT
} ADC_mode;

// Typedefs

typedef struct 
{
    ADC_TypeDef* ADC_base;
    ADC_mode mode;
    uint8_t channel_num;
} ADC_init_typedef;


// Functions

void ADC_init(ADC_init_typedef* init_handle);
void ADC_pin_cfg(ADC_init_typedef* adc_init_handle);
uint32_t ADC_read_single(ADC_TypeDef* adc_base);

#endif