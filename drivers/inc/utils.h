#ifndef UTILS_H
#define UTILS_H

// Set a bit in a variable or register.
#define SETBIT(data, bit) data |= (1<<bit);

// Reset a bit in a variable or register.
#define RESETBIT(data, bit) data &= ~(1<<bit);

#endif