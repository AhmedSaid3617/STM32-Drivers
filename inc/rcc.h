#ifndef RCC_H
#define RCC_H

// Register addresses.

#define RCC_APB2ENR *((volatile uint32_t*)(0x40021000+0x18))

// Function-like macros.

#define RCC_PORTC_ENABLE() RCC_APB2ENR |= (1<<4)

#endif