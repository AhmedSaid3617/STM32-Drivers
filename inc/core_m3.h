#ifndef CORE_M3_H
#define CORE_M3_H

#include <stdint.h>

#define CORE_PERIPH_BASE 0xE0000000
#define NVIC_BASE (CORE_PERIPH_BASE + 0xE100)

#define NVIC_ISER   ((volatile uint32_t*)(NVIC_BASE + 0x00))
#define NVIC_ICER   ((volatile uint32_t*)(NVIC_BASE + 0x80))
#define NVIC_ISPR   ((volatile uint32_t*)(NVIC_BASE + 0x100))
#define NVIC_ICPR   ((volatile uint32_t*)(NVIC_BASE + 0x180))
#define NVIC_IABR   ((volatile uint32_t*)(NVIC_BASE + 0x200))
#define NVIC_IPR    ((volatile uint32_t*)(NVIC_BASE + 0x100))
#define NVIC_STIR   ((volatile uint32_t*)(NVIC_BASE + 0XE00))
#endif