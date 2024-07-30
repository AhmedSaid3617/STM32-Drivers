#ifndef STM32F103C6
#define STM32F103C6

#include <stdint.h>

#define FLASH_BASE 0x08000000UL      /*!< FLASH base address in the alias region */
#define FLASH_BANK1_END 0x08007FFFUL /*!< FLASH END address of bank1 */
#define SRAM_BASE 0x20000000UL       /*!< SRAM base address in the alias region */
#define PERIPH_BASE 0x40000000UL     /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE 0x22000000UL   /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE 0x42000000UL /*!< Peripheral base address in the bit-band region */

/*!< Peripheral memory map */
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE (PERIPH_BASE + 0x00020000UL)

#define TIM2_BASE (APB1PERIPH_BASE + 0x00000000UL)
#define TIM3_BASE (APB1PERIPH_BASE + 0x00000400UL)
#define RTC_BASE (APB1PERIPH_BASE + 0x00002800UL)
#define WWDG_BASE (APB1PERIPH_BASE + 0x00002C00UL)
#define IWDG_BASE (APB1PERIPH_BASE + 0x00003000UL)
#define USART2_BASE (APB1PERIPH_BASE + 0x00004400UL)
#define I2C1_BASE (APB1PERIPH_BASE + 0x00005400UL)
#define CAN1_BASE (APB1PERIPH_BASE + 0x00006400UL)
#define BKP_BASE (APB1PERIPH_BASE + 0x00006C00UL)
#define PWR_BASE (APB1PERIPH_BASE + 0x00007000UL)
#define AFIO_BASE (APB2PERIPH_BASE + 0x00000000UL)
#define EXTI_BASE (APB2PERIPH_BASE + 0x00000400UL)
#define GPIOA_BASE (APB2PERIPH_BASE + 0x00000800UL)
#define GPIOB_BASE (APB2PERIPH_BASE + 0x00000C00UL)
#define GPIOC_BASE (APB2PERIPH_BASE + 0x00001000UL)
#define GPIOD_BASE (APB2PERIPH_BASE + 0x00001400UL)
#define ADC1_BASE (APB2PERIPH_BASE + 0x00002400UL)
#define ADC2_BASE (APB2PERIPH_BASE + 0x00002800UL)
#define TIM1_BASE (APB2PERIPH_BASE + 0x00002C00UL)
#define SPI1_BASE (APB2PERIPH_BASE + 0x00003000UL)
#define USART1_BASE (APB2PERIPH_BASE + 0x00003800UL)

#define DMA1_BASE (AHBPERIPH_BASE + 0x00000000UL)
#define DMA1_Channel1_BASE (AHBPERIPH_BASE + 0x00000008UL)
#define DMA1_Channel2_BASE (AHBPERIPH_BASE + 0x0000001CUL)
#define DMA1_Channel3_BASE (AHBPERIPH_BASE + 0x00000030UL)
#define DMA1_Channel4_BASE (AHBPERIPH_BASE + 0x00000044UL)
#define DMA1_Channel5_BASE (AHBPERIPH_BASE + 0x00000058UL)
#define DMA1_Channel6_BASE (AHBPERIPH_BASE + 0x0000006CUL)
#define DMA1_Channel7_BASE (AHBPERIPH_BASE + 0x00000080UL)
#define RCC_BASE (AHBPERIPH_BASE + 0x00001000UL)
#define CRC_BASE (AHBPERIPH_BASE + 0x00003000UL)

#define FLASH_R_BASE (AHBPERIPH_BASE + 0x00002000UL) /*!< Flash registers base address */
#define FLASHSIZE_BASE 0x1FFFF7E0UL                  /*!< FLASH Size register base address */
#define UID_BASE 0x1FFFF7E8UL                        /*!< Unique device ID register base address */
#define OB_BASE 0x1FFFF800UL                         /*!< Flash Option Bytes base address */

#define DBGMCU_BASE 0xE0042000UL /*!< Debug MCU registers base address */

/* USB device FS */
#define USB_BASE (APB1PERIPH_BASE + 0x00005C00UL)    /*!< USB_IP Peripheral Registers base address */
#define USB_PMAADDR (APB1PERIPH_BASE + 0x00006000UL) /*!< USB_IP Packet Memory Area base address */

typedef struct
{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR[4];
    uint32_t RESERVED0;
    volatile uint32_t MAPR2;
} AFIO_TypeDef;

typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_TypeDef;

#endif