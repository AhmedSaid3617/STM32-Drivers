#ifndef UART_H
#define UART_H

#include "stm32f103c6.h"

#define USART2 ((USART_TypeDef*)(USART2_BASE))

typedef enum {
    UART_MODE_TX,
    UART_MODE_RX,
    UART_MODE_FULL_DUPLEX
} UART_Mode;

typedef struct
{
    USART_TypeDef* USART_base;
    uint32_t baud_rate;
    UART_Mode tx_mode;
} UART_Init_t;

void UART_Init(UART_Init_t* init_handle);

#endif