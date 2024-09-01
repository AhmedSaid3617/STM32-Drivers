#include "systick.h"
#include "nvic.h"

/**
 * @brief Busy wait for ms milliseconds.
 * @param ms Time to wait in milliseconds.
 */
void SysTick_delay_ms(int ms)
{

    int cycles = 0;
    RESETBIT(SysTick->CTRL, 0);
    SysTick->LOAD = SYSTICK_CLK / 1000 - 1;
    SETBIT(SysTick->CTRL, 0);

    while (cycles < ms)
    {
        if (SysTick->CTRL & 1 << 16) // If COUNTFLAG
        {
            cycles += 1;
        }
    }
}

void SysTick_interrupt_init(int ms)
{
    NVIC_enable_IRQ(SysTick_IRQn, 1);
    SysTick->LOAD = (SYSTICK_CLK/1000) * ms - 1;
    SETBIT(SysTick->CTRL, 1);
    SETBIT(SysTick->CTRL, 0);
    
}
