#include "uart.h"

/**
 * @brief Initialize a USART module for asynchronus serial communication.
 * @warning APB1 and APB2 must have the same clock frequnecy or else the baud rate will not be calculated correctly.
 * @param init_handle Parameters for initialization.
 * @attention Make sure to initialize the pins for TX/RX using GPIO_Init.
 */
void UART_Init(UART_Init_t *init_handle)
{
    double baud_divisor = (double)SYSCLK / (16 * init_handle->baud_rate);
    uint32_t baud_div_mantissa = (baud_divisor);
    uint32_t baud_div_fraction = 16 * (baud_divisor - baud_div_mantissa);
    init_handle->USART_base->CR1 |= 1 << 13;
    init_handle->USART_base->BRR |= baud_div_mantissa << 4;
    init_handle->USART_base->BRR |= baud_div_fraction;

    switch (init_handle->mode)
    {
    case UART_MODE_RX:
        init_handle->USART_base->CR1 |= (1 << 2); // Enable RX
        break;

    case UART_MODE_TX:
        init_handle->USART_base->CR1 |= (1 << 3); // Enable TX
        break;

    case UART_MODE_FULL_DUPLEX:
        init_handle->USART_base->CR1 |= (1 << 2); // Enable RX
        init_handle->USART_base->CR1 |= (1 << 3); // Enable TX
        break;
    }
}
