#ifndef CORE_M3_H
#define CORE_M3_H

#include <stdint.h>

// Define modules.

typedef struct
{
    volatile uint32_t CTRL;  /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    volatile uint32_t LOAD;  /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
    volatile uint32_t VAL;   /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
    volatile uint32_t CALIB; /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

typedef struct
{
    volatile uint32_t ISER[8U]; /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
    uint32_t RESERVED0[24U];
    volatile uint32_t ICER[8U]; /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
    uint32_t RSERVED1[24U];
    volatile uint32_t ISPR[8U]; /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
    uint32_t RESERVED2[24U];
    volatile uint32_t ICPR[8U]; /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
    uint32_t RESERVED3[24U];
    volatile uint32_t IABR[8U]; /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
    uint32_t RESERVED4[56U];
    volatile uint8_t IP[240U]; /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
    uint32_t RESERVED5[644U];
    volatile uint32_t STIR; /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
} NVIC_Type;

#define SCS_BASE (0xE000E000UL)            /*!< System Control Space Base Address */
#define ITM_BASE (0xE0000000UL)            /*!< ITM Base Address */
#define DWT_BASE (0xE0001000UL)            /*!< DWT Base Address */
#define TPI_BASE (0xE0040000UL)            /*!< TPI Base Address */
#define CoreDebug_BASE (0xE000EDF0UL)      /*!< Core Debug Base Address */
#define SysTick_BASE (SCS_BASE + 0x0010UL) /*!< SysTick Base Address */
#define NVIC_BASE (SCS_BASE + 0x0100UL)    /*!< NVIC Base Address */
#define SCB_BASE (SCS_BASE + 0x0D00UL)     /*!< System Control Block Base Address */

#define SCnSCB ((SCnSCB_Type *)SCS_BASE)             /*!< System control Register not in SCB */
#define SCB ((SCB_Type *)SCB_BASE)                   /*!< SCB configuration struct */
#define SysTick ((SysTick_Type *)SysTick_BASE)       /*!< SysTick configuration struct */
#define NVIC ((NVIC_Type *)NVIC_BASE)                /*!< NVIC configuration struct */
#define ITM ((ITM_Type *)ITM_BASE)                   /*!< ITM configuration struct */
#define DWT ((DWT_Type *)DWT_BASE)                   /*!< DWT configuration struct */
#define TPI ((TPI_Type *)TPI_BASE)                   /*!< TPI configuration struct */
#define CoreDebug ((CoreDebug_Type *)CoreDebug_BASE) /*!< Core Debug configuration struct */

#endif