#ifndef UART_H
#define UART_H

#include "stm32f103c6.h"
#include "systick.h"
#include "gpio.h"

#define USART1 ((USART_TypeDef*)(USART1_BASE))
#define USART2 ((USART_TypeDef*)(USART2_BASE))
#define USART3 ((USART_TypeDef*)(USART3_BASE))

typedef enum {
    UART_MODE_POLLING,
    UART_MODE_INTERRUPT,
    UART_MODE_DMA
} UART_mode;

typedef enum {
    UART_DIR_TX,           /* UART TX only is on. */
    UART_DIR_RX,           /* UART RX only is on. */
    UART_DIR_FULL_DUPLEX   /* Both UART TX and RX are on. */
} UART_direction;

typedef enum {
    UART_STATUS_SUCCESS,    /* UART send or receive operation succeeded. */
    UART_STATUS_TX_FULL,    /* Another transmit operation is underway. */
    UART_STATUS_RX_EMPTY,   /* Nothing to receive. */
} UART_status;

/**
 * @brief Initialization parameters for UART module.
 */
typedef struct
{
    USART_TypeDef* USART_base;
    uint32_t baud_rate;
    UART_mode mode;
    UART_direction direction;
} UART_Init_t;

void UART_Init(UART_Init_t* init_handle);
void UART_TX_cfg(GPIO_TypeDef* gpio_base, uint8_t pin);
void UART_RX_cfg(GPIO_TypeDef* gpio_base, uint8_t pin);
UART_status UART_receive_byte(USART_TypeDef* uart_base, uint8_t* dest);
UART_status UART_send_byte(USART_TypeDef* uart_base, uint8_t byte);
UART_status UART_printf(USART_TypeDef *uart_base, uint8_t* data);

#endif