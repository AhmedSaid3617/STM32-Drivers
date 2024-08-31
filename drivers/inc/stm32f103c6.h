#ifndef STM32F103C6
#define STM32F103C6

#include <stdint.h>
#include "clocks.h"

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
#define USART3_BASE (APB1PERIPH_BASE + 0x00004800UL)
#define I2C1_BASE (APB1PERIPH_BASE + 0x00005400UL)
#define I2C2_BASE (APB1PERIPH_BASE + 0x00005800UL)
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

typedef enum
{
    /******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn = -14,   /*!< 2 Non Maskable Interrupt                             */
    HardFault_IRQn = -13,        /*!< 3 Cortex-M3 Hard Fault Interrupt                     */
    MemoryManagement_IRQn = -12, /*!< 4 Cortex-M3 Memory Management Interrupt              */
    BusFault_IRQn = -11,         /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
    UsageFault_IRQn = -10,       /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
    SVCall_IRQn = -5,            /*!< 11 Cortex-M3 SV Call Interrupt                       */
    DebugMonitor_IRQn = -4,      /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
    PendSV_IRQn = -2,            /*!< 14 Cortex-M3 Pend SV Interrupt                       */
    SysTick_IRQn = -1,           /*!< 15 Cortex-M3 System Tick Interrupt                   */

    /******  STM32 specific Interrupt Numbers *********************************************************/
    WWDG_IRQn = 0,             /*!< Window WatchDog Interrupt                            */
    PVD_IRQn = 1,              /*!< PVD through EXTI Line detection Interrupt            */
    TAMPER_IRQn = 2,           /*!< Tamper Interrupt                                     */
    RTC_IRQn = 3,              /*!< RTC global Interrupt                                 */
    FLASH_IRQn = 4,            /*!< FLASH global Interrupt                               */
    RCC_IRQn = 5,              /*!< RCC global Interrupt                                 */
    EXTI0_IRQn = 6,            /*!< EXTI Line0 Interrupt                                 */
    EXTI1_IRQn = 7,            /*!< EXTI Line1 Interrupt                                 */
    EXTI2_IRQn = 8,            /*!< EXTI Line2 Interrupt                                 */
    EXTI3_IRQn = 9,            /*!< EXTI Line3 Interrupt                                 */
    EXTI4_IRQn = 10,           /*!< EXTI Line4 Interrupt                                 */
    DMA1_Channel1_IRQn = 11,   /*!< DMA1 Channel 1 global Interrupt                      */
    DMA1_Channel2_IRQn = 12,   /*!< DMA1 Channel 2 global Interrupt                      */
    DMA1_Channel3_IRQn = 13,   /*!< DMA1 Channel 3 global Interrupt                      */
    DMA1_Channel4_IRQn = 14,   /*!< DMA1 Channel 4 global Interrupt                      */
    DMA1_Channel5_IRQn = 15,   /*!< DMA1 Channel 5 global Interrupt                      */
    DMA1_Channel6_IRQn = 16,   /*!< DMA1 Channel 6 global Interrupt                      */
    DMA1_Channel7_IRQn = 17,   /*!< DMA1 Channel 7 global Interrupt                      */
    ADC1_2_IRQn = 18,          /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn = 19,  /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn = 20, /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn = 21,        /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn = 22,        /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn = 23,         /*!< External Line[9:5] Interrupts                        */
    TIM1_BRK_IRQn = 24,        /*!< TIM1 Break Interrupt                                 */
    TIM1_UP_IRQn = 25,         /*!< TIM1 Update Interrupt                                */
    TIM1_TRG_COM_IRQn = 26,    /*!< TIM1 Trigger and Commutation Interrupt               */
    TIM1_CC_IRQn = 27,         /*!< TIM1 Capture Compare Interrupt                       */
    TIM2_IRQn = 28,            /*!< TIM2 global Interrupt                                */
    TIM3_IRQn = 29,            /*!< TIM3 global Interrupt                                */
    I2C1_EV_IRQn = 31,         /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn = 32,         /*!< I2C1 Error Interrupt                                 */
    SPI1_IRQn = 35,            /*!< SPI1 global Interrupt                                */
    USART1_IRQn = 37,          /*!< USART1 global Interrupt                              */
    USART2_IRQn = 38,          /*!< USART2 global Interrupt                              */
    EXTI15_10_IRQn = 40,       /*!< External Line[15:10] Interrupts                      */
    RTC_Alarm_IRQn = 41,       /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn = 42,       /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
} IRQn_Type;

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

typedef struct
{
    volatile uint32_t SR;   /*!< USART Status register,                   Address offset: 0x00 */
    volatile uint32_t DR;   /*!< USART Data register,                     Address offset: 0x04 */
    volatile uint32_t BRR;  /*!< USART Baud rate register,                Address offset: 0x08 */
    volatile uint32_t CR1;  /*!< USART Control register 1,                Address offset: 0x0C */
    volatile uint32_t CR2;  /*!< USART Control register 2,                Address offset: 0x10 */
    volatile uint32_t CR3;  /*!< USART Control register 3,                Address offset: 0x14 */
    volatile uint32_t GTPR; /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
} I2C_TypeDef;

typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMPR1;
    volatile uint32_t SMPR2;
    volatile uint32_t JOFR1;
    volatile uint32_t JOFR2;
    volatile uint32_t JOFR3;
    volatile uint32_t JOFR4;
    volatile uint32_t HTR;
    volatile uint32_t LTR;
    volatile uint32_t SQR1;
    volatile uint32_t SQR2;
    volatile uint32_t SQR3;
    volatile uint32_t JSQR;
    volatile uint32_t JDR1;
    volatile uint32_t JDR2;
    volatile uint32_t JDR3;
    volatile uint32_t JDR4;
    volatile uint32_t DR;
} ADC_TypeDef;

typedef struct
{
    volatile uint32_t CR1;   /*!< TIM control register 1,                      Address offset: 0x00 */
    volatile uint32_t CR2;   /*!< TIM control register 2,                      Address offset: 0x04 */
    volatile uint32_t SMCR;  /*!< TIM slave Mode Control register,             Address offset: 0x08 */
    volatile uint32_t DIER;  /*!< TIM DMA/interrupt enable register,           Address offset: 0x0C */
    volatile uint32_t SR;    /*!< TIM status register,                         Address offset: 0x10 */
    volatile uint32_t EGR;   /*!< TIM event generation register,               Address offset: 0x14 */
    volatile uint32_t CCMR1; /*!< TIM  capture/compare mode register 1,        Address offset: 0x18 */
    volatile uint32_t CCMR2; /*!< TIM  capture/compare mode register 2,        Address offset: 0x1C */
    volatile uint32_t CCER;  /*!< TIM capture/compare enable register,         Address offset: 0x20 */
    volatile uint32_t CNT;   /*!< TIM counter register,                        Address offset: 0x24 */
    volatile uint32_t PSC;   /*!< TIM prescaler register,                      Address offset: 0x28 */
    volatile uint32_t ARR;   /*!< TIM auto-reload register,                    Address offset: 0x2C */
    volatile uint32_t RCR;   /*!< TIM  repetition counter register,            Address offset: 0x30 */
    volatile uint32_t CCR1;  /*!< TIM capture/compare register 1,              Address offset: 0x34 */
    volatile uint32_t CCR2;  /*!< TIM capture/compare register 2,              Address offset: 0x38 */
    volatile uint32_t CCR3;  /*!< TIM capture/compare register 3,              Address offset: 0x3C */
    volatile uint32_t CCR4;  /*!< TIM capture/compare register 4,              Address offset: 0x40 */
    volatile uint32_t BDTR;  /*!< TIM break and dead-time register,            Address offset: 0x44 */
    volatile uint32_t DCR;   /*!< TIM DMA control register,                    Address offset: 0x48 */
    volatile uint32_t DMAR;  /*!< TIM DMA address for full transfer register,  Address offset: 0x4C */
    volatile uint32_t OR;    /*!< TIM option register,                         Address offset: 0x50 */
} TIM_TypeDef;

typedef struct
{
    volatile uint32_t CCR;
    volatile uint32_t CNDTR;
    volatile uint32_t CPAR;
    volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
    volatile uint32_t ISR;
    volatile uint32_t IFCR;
} DMA_TypeDef;

#endif