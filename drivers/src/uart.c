#include "uart.h"

void UART_Init(UART_Init_t *init_handle)
{
    double baud_divisor = (double)SYSTEM_CLOCK/(16*init_handle->baud_rate);
    uint32_t baud_div_mantissa = (baud_divisor);
    uint32_t baud_div_fraction = 16 * (baud_divisor - baud_div_mantissa);
    init_handle->USART_base->CR1 |= 1 << 13;
    init_handle->USART_base->BRR |= baud_div_mantissa << 4;
    init_handle->USART_base->BRR |= baud_div_fraction;

}
