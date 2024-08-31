#include "uart.h"

/**
 * @brief Initialize a USART module for asynchronus serial communication.
 * @warning APB1 and APB2 must have the same clock frequnecy or else the baud rate will not be calculated correctly.
 * @param init_handle Parameters for initialization.
 * @attention Make sure to initialize the pins for TX/RX using UART_TX_cfg/UART_RX_cfg.
 */
void UART_Init(UART_Init_t *init_handle)
{
    double baud_divisor = (double)SYSCLK / (16 * init_handle->baud_rate);
    uint32_t baud_div_mantissa = (baud_divisor);
    uint32_t baud_div_fraction = 16 * (baud_divisor - baud_div_mantissa);
    init_handle->USART_base->CR1 |= 1 << 13;
    init_handle->USART_base->BRR |= baud_div_mantissa << 4;
    init_handle->USART_base->BRR |= baud_div_fraction;

    switch (init_handle->direction)
    {
    case UART_DIR_RX:
        init_handle->USART_base->CR1 |= (1 << 2); // Enable RX
        if (init_handle->mode == UART_MODE_DMA)
        {
            init_handle->USART_base->CR3 |= 1 << 6; // Enable DMA receiver.
        }
        
        break;

    case UART_DIR_TX:
        init_handle->USART_base->CR1 |= (1 << 3); // Enable TX
        if (init_handle->mode == UART_MODE_DMA)
        {
            init_handle->USART_base->CR3 |= 1 << 7; // Enable DMA transmitter.
        }
        break;

    case UART_DIR_FULL_DUPLEX:
        init_handle->USART_base->CR1 |= (1 << 2); // Enable RX
        init_handle->USART_base->CR1 |= (1 << 3); // Enable TX
        if (init_handle->mode == UART_MODE_DMA)
        {
            init_handle->USART_base->CR3 |= 1 << 6; // Enable DMA receiver.
            init_handle->USART_base->CR3 |= 1 << 7; // Enable DMA transmitter.
        }
        break;
    }
}

/**
 * @brief Configure pin for TX.
 * 
 * @param gpio_base Base address for the port containing the pin. 
 * @param pin Pin number.
 */
void UART_TX_cfg(GPIO_TypeDef* gpio_base, uint8_t pin){
    GPIO_Init_t gpio_init_handle;
    gpio_init_handle.gpio_base = gpio_base;
    gpio_init_handle.mode = GPIO_MODE_AFIO_PP;
    gpio_init_handle.pin = pin;
    GPIO_init(&gpio_init_handle);
}

/**
 * @brief Configure pin for RX.
 * 
 * @param gpio_base Base address for the port containing the pin. 
 * @param pin Pin number.
 */
void UART_RX_cfg(GPIO_TypeDef* gpio_base, uint8_t pin){
    GPIO_Init_t gpio_init_handle;
    gpio_init_handle.gpio_base = gpio_base;
    gpio_init_handle.mode = GPIO_MODE_INPUT_FLOATING;
    gpio_init_handle.pin = pin;
    GPIO_init(&gpio_init_handle);
}

/**
 * @brief Receive one byte from a USART module.
 * 
 * @param uart_base Base address for the USART module.
 * @param dest Pointer to the variable in which to store the received byte.
 * @return Returns a status, either UART_STATUS_SUCCESS if recieved successfully, or UART_STATUS_RX_EMPTY if there's nothing to receive.
 */
UART_status UART_receive_byte(USART_TypeDef *uart_base, uint8_t *dest)
{
    if (uart_base->SR & (1 << 5)) // If RX not empty.
    {
        *dest = uart_base->DR & 0xFF;
        return UART_STATUS_SUCCESS;
    }
    return UART_STATUS_RX_EMPTY;
}

/**
 * @brief Send one byte over a USART module.
 * @param uart_base Base address for the USART module.
 * @param dest The required byte to send.
 * @return Returns a status, either UART_STATUS_SUCCESS if recieved successfully, or UART_STATUS_TX_FULL if some other value is being transmitted.
 */
UART_status UART_send_byte(USART_TypeDef *uart_base, uint8_t byte)
{
    for (int i = 0; i < 1000; i++)
    {
        if (uart_base->SR & (1 << 7))
        {
            uart_base->DR = byte;
            return UART_STATUS_SUCCESS;
        }
    }

    return UART_STATUS_TX_FULL;
}

// TODO: insert comment.
/**
 * @brief 
 * 
 * @param uart_base 
 * @param data 
 * @return UART_status 
 */
UART_status UART_printf(USART_TypeDef *uart_base, uint8_t *data)
{
    while (*data != 0)
    {
        UART_send_byte(uart_base, *(data++));
    }

    return UART_STATUS_SUCCESS;
}