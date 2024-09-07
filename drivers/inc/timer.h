#ifndef TIMER_H
#define TIMER_H

#include "stm32f103c6.h"

#define TIM2 ((TIM_TypeDef*)(TIM2_BASE))

/**
 * @brief Initialization parameters for timers.
 * 
 */
typedef struct
{
    TIM_TypeDef* timer_base;    /* Base address for the timer.*/
    uint32_t prescaler;         /* Prescaler for the timer clock. Frequency = Fclk/(prescaler+1). */
    uint32_t period;            /* The period between timer resets. */
} timer_init_typedef;


void timer_init(timer_init_typedef* timer_init_handle);
void timer_reset(TIM_TypeDef* timer_base);

#endif