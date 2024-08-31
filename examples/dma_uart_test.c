#include "rcc.h"
#include "uart.h"
#include "systick.h"
#include "gpio.h"
#include "dma.h"

void SysClk_init();

UART_Init_t uart_init_handle;
GPIO_Init_t gpio_init_handle;
DMA_init_typedef dma_init_handle;

uint8_t message[10];

int main()
{
    SysClk_init();
    
    RCC_USART3_ENABLE();
    RCC_PORTA_ENABLE();
    RCC_PORTB_ENABLE();
    RCC_DMA1_ENABLE();

    // PA8 OUT
    gpio_init_handle.mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_handle.gpio_base = GPIOA;
    gpio_init_handle.pin = 8;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    GPIO_init(&gpio_init_handle);

    // PB10 (TX) AFIO Pull Push
    UART_TX_cfg(GPIOB, 10);

    // PB11 (RX) GPIO Input floating
    UART_RX_cfg(GPIOB, 11);

    // Initialize USART3
    uart_init_handle.baud_rate = 9600;
    uart_init_handle.USART_base = USART3;
    uart_init_handle.direction = UART_DIR_FULL_DUPLEX;
    uart_init_handle.mode = UART_MODE_DMA;
    UART_Init(&uart_init_handle);

    // Initialize DMA
    dma_init_handle.dma_channel = DMA1_Channel3; // Set to channel 3.
    dma_init_handle.peripheral_register = USART3_BASE + 0x4; // Put USART3_DR as the peripheral address.
    dma_init_handle.memory_address = &message; // Put the address of message variable as the memory address.
    dma_init_handle.data_count = 9; // Transfer 9 bytes.
    dma_init_handle.priority = DMA_PRI_MEDIUM; // Set priority to medium.
    dma_init_handle.mem_inc = 1; // Memory increment.
    DMA_channel_init(&dma_init_handle);

    while (1)
    {
        UART_printf(USART3, message);
        SysTick_delay_ms(1000);
        DMA1_Channel3->CCR &= ~(1 << 0); // Disable channel.
        DMA1_Channel3->CNDTR = 9;        // Transfer 9 bytes.
        DMA1_Channel3->CCR |= 1;         // Enable channel.
    }

    return 0;
}

void SysClk_init()
{
    RCC->CR |= 1 << 16; // Turn HSE on.
    while (!(RCC->CR & 1 << 17))
    {
        // While HSE not ready, wait.
    }

    RCC->CFGR |= 1;       // Choose HSE as the source.
    RCC->CR &= ~(1 << 0); // Turnoff HSI. (To reduce power consumption).
}

void HardFault_Handler()
{
    RCC_PORTC_ENABLE();
    GPIO_Init_t gpio_init_handle;
    gpio_init_handle.gpio_base = GPIOC;
    gpio_init_handle.mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_handle.pin = 13;
    gpio_init_handle.speed = GPIO_SPEED_10MHZ;
    GPIO_init(&gpio_init_handle);

    while (1)
    {
        GPIO_write_pin(GPIOC, 13, 1);
        SysTick_delay_ms(1000);
        GPIO_write_pin(GPIOC, 13, 0);
        SysTick_delay_ms(1000);
    };
}
