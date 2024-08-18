#include "i2c.h"

void I2C_init(I2C_TypeDef *I2C_base)
{
    I2C_base->CR2 |= PCLK1;               // Set system FREQ = 8MHz
    I2C_base->CCR |= 5000 / TPCLK1;       // Set I2C frequency = 100 KHz
    I2C_base->TRISE |= 1000 / TPCLK1 + 1; // Set min TRISE = 1000 ns
    I2C_base->CR1 |= (1 << 0);            // Enable I2C
}

I2C_status I2C_master_send(I2C_TypeDef *I2C_base, uint8_t slave_address, uint8_t *data_ptr, uint32_t data_size)
{
    I2C1->CR1 |= (1 << 8); // Send start condition.
    for (volatile uint32_t i = 0; i <= 10000; i++)  // Wait while start bit not set.
    {
        if (I2C1->SR1 & (1 << 0))
        {
            break;
        }
        else if (i == 10000)
        {
            return I2C_STATUS_HARDWARE_ERR;         // After timeout, return error.
        }
                 
    }

    I2C1->DR = (slave_address << 1);  // Send slave address with Write bit.

    while (!(I2C1->SR1 & 1 << 1)); // Wait while address not sent.

    // TODO: Check this error, sends -1 if this line is removed.
    if (I2C1->SR2); // Read SR2 to clear ADDR bit

    for (volatile uint8_t * i = data_ptr; i < data_ptr + data_size; i++)
    {
        while (!(I2C1->SR1 & (1 << 7))); // Wait while TX not empty.
        I2C1->DR = *i;  // Write byte to data register.
    }

    // Send stop transmission.
    I2C1->CR1 |= 1 << 9;
    return I2C_STATUS_SUCCESS;
}
