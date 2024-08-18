#ifndef CLOCKS_H
#define CLOCKS_H

#define SYSCLK 8000000
#define SYSTICK_CLK (SYSCLK/8)

#define APB1_DIV 1
#define PCLK1 (SYSCLK/APB1_DIV)
#define TPCLK1 125

#define APB2_DIV 1
#define PCLK2 (SYSCLK/APB2_DIV)
#define TPCLK2 125

#endif
