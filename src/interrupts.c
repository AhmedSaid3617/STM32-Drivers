#include "interrupts.h"

void _enable_irq(){
    __asm__("CPSIE i");
}

void _disable_irq(){
    __asm__("CPSID i");
}