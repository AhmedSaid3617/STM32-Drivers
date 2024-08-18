#ifndef I2C_H
#define I2C_H

#include "stm32f103c6.h"

// Defining modules.

#define I2C1 ((I2C_TypeDef*)(I2C1_BASE))

typedef enum {
    I2C_MODE_MASTER,
    I2C_MODE_SLAVE
} I2C_mode;

typedef enum {
    I2C_STATUS_SUCCESS,
    I2C_STATUS_HARDWARE_ERR
} I2C_status;

typedef struct
{
    I2C_TypeDef* I2C_base;
    I2C_mode mode;
    uint32_t slave_address;
} I2C_init_t;

// Functions

void I2C_init(I2C_TypeDef* I2C_base);
I2C_status I2C_master_send(I2C_TypeDef *I2C_base, uint8_t slave_address, uint8_t *data_ptr, uint32_t data_size);

#endif