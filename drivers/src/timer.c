#include "timer.h"

/**
 * @brief Initialize the timer for counting mode.
 * @attention Global interrupts must be enabled for this particular Timer module using NVIC_enable_IRQ()
 * 
 * @param timer_init_handle Initialization parameters.
 */
void timer_init(timer_init_typedef* timer_init_handle){
    timer_init_handle->timer_base->PSC = timer_init_handle->prescaler; // Set prescaler.
    timer_init_handle->timer_base->ARR = timer_init_handle->period; // Set reset value.
    timer_init_handle->timer_base->DIER |= 1<<0; // Update interrupt enable.

    timer_init_handle->timer_base->CR1 |= 1<<0; // Counter enable.
}
 