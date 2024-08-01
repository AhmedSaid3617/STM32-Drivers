#include "nvic.h"

void _enable_irq(){
    __asm__("CPSIE i");
}

void _disable_irq(){
    __asm__("CPSID i");
}

extern inline void NVIC_enable_IRQ(IRQn_Type IRQn, uint8_t priority){
    NVIC_ISER[IRQn >> 5] |= 1 << (IRQn & 31UL);
    NVIC_IPR[IRQn] = (uint8_t)((priority & 0xF) << 4);
}