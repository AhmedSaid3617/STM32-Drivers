#ifndef CLOCKS_H
#define CLOCKS_H

#define SYSCLK 8000000
#define SYSTICK_CLK (SYSCLK/8)

#define APB1_DIV 1
#define APB1_CLK (SYSCLK/APB1_DIV)

#define APB2_DIV 1
#define APB2_CLK (SYSCLK/APB2_DIV)

#endif
