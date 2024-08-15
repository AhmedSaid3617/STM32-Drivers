#ifndef UART_H
#define UART_H

#include "stm32f103c6.h"

#define USART2 ((USART_TypeDef*)(USART2_BASE))

typedef enum {
    UART_MODE_TX,
    UART_MODE_RX,
    UART_MODE_FULL_DUPLEX
} UART_mode;

typedef enum {
    UART_STATUS_SUCCESS,
    UART_STATUS_TX_FULL,
    UART_STATUS_RX_EMPTY,
} UART_status;

/**
 * @brief This struct contains the initialization parameters for UART module.
 */
typedef struct
{
    USART_TypeDef* USART_base;
    uint32_t baud_rate;
    UART_mode mode;
} UART_Init_t;

void UART_Init(UART_Init_t* init_handle);
UART_status UART_receive_byte(USART_TypeDef* uart_base, uint8_t* dest);
UART_status UART_send_byte(USART_TypeDef* uart_base, uint8_t byte);

#endif