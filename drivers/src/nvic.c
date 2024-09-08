#include "nvic.h"

void _enable_irq(){
    __asm__("CPSIE i");
}

void _disable_irq(){
    __asm__("CPSID i");
}

extern inline void NVIC_enable_IRQ(IRQn_Type IRQn, uint8_t priority){
    NVIC->ISER[IRQn >> 5] |= 1 << (IRQn & 31UL);
    NVIC->IP[IRQn] = (uint8_t)((priority & 0xF) << 4);
}

extern inline void NVIC_disable_IRQ(IRQn_Type IRQn){
    NVIC->ICER[IRQn >> 5] |= 1 << (IRQn & 31UL);
}