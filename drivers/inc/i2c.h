#ifndef I2C_H
#define I2C_H

#include "stm32f103c6.h"
#include "gpio.h"
#include "rcc.h"

// Defining modules.

#define I2C1 ((I2C_TypeDef*)(I2C1_BASE))
#define I2C2 ((I2C_TypeDef*)(I2C2_BASE))

typedef enum {
    I2C_MODE_MASTER,
    I2C_MODE_SLAVE
} I2C_mode;

/// @brief Status of I2C send and receive operations.
typedef enum {
    I2C_STATUS_SUCCESS, ///< Data transfer succeeded.
    I2C_STATUS_ERR, ///< A hardware-related error occurred.
    I2C_STATUS_NACK, ///< Received a not-acknowledged signal.
    I2C_STATUS_TIMEOUT ///< No data received in a long time.
} I2C_status;

typedef struct
{
    I2C_TypeDef* I2C_base;
    I2C_mode mode;
    uint32_t slave_address;
} I2C_init_t;

// Functions

void I2C_init(I2C_TypeDef* I2C_base);
void I2C_pins_cfg(uint32_t I2C_base);
I2C_status I2C_master_send(I2C_TypeDef *I2C_base, uint8_t slave_address, uint8_t *data_ptr, uint32_t data_size);
I2C_status I2C_master_receive(I2C_TypeDef *I2C_base, uint8_t slave_address, uint8_t *dest, uint32_t data_size);

#endif