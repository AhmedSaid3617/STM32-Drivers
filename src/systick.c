#include "systick.h"

/**
 * @brief Busy wait for ms milliseconds.
 * @param ms Time to wait in milliseconds.
 */
void SysTick_delay_ms(int ms){

    int cycles = 0;
    RESETBIT(SysTick->CTRL, 0);
    SysTick->LOAD = SYSTEM_CLOCK/1000;
    SETBIT(SysTick->CTRL, 0);

    while (cycles < ms)
    {
        if (SysTick->CTRL & 1<<16) // If COUNTFLAG
        {
            cycles += 1;
        }
        
    }
    
}
