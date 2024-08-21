#include "i2c.h"

/**
 * @brief Initialize I2C module.
 *
 * @param I2C_base Base address for I2C module.
 */
void I2C_init(I2C_TypeDef *I2C_base)
{
    I2C_pins_cfg((uint32_t)I2C_base);
    I2C_base->CR2 |= PCLK1;               // Set system FREQ = 8MHz
    I2C_base->CCR |= 5000 / TPCLK1;       // Set I2C frequency = 100 KHz
    I2C_base->TRISE |= 1000 / TPCLK1 + 1; // Set min TRISE = 1000 ns
    I2C_base->CR1 |= (1 << 0);            // Enable I2C
}

void I2C_pins_cfg(uint32_t I2C_base)
{
    GPIO_Init_t gpio_init_handle;
    RCC_PORTB_ENABLE();

    switch (I2C_base)
    {
    case I2C1_BASE:
        // PB6 (SCL1), PB7 (SDA1) AFIO open drain.
        gpio_init_handle.gpio_base = GPIOB;
        gpio_init_handle.mode = GPIO_MODE_AFIO_OD;
        gpio_init_handle.speed = GPIO_SPEED_10MHZ;
        gpio_init_handle.pin = 6;
        GPIO_init(&gpio_init_handle);

        gpio_init_handle.pin = 7;
        GPIO_init(&gpio_init_handle);
        break;

    case I2C2_BASE:
        // PB10 (SCL2), PB11 (SDA2) AFIO open drain.
        gpio_init_handle.gpio_base = GPIOB;
        gpio_init_handle.mode = GPIO_MODE_AFIO_OD;
        gpio_init_handle.speed = GPIO_SPEED_10MHZ;
        gpio_init_handle.pin = 10;
        GPIO_init(&gpio_init_handle);

        gpio_init_handle.pin = 11;
        GPIO_init(&gpio_init_handle);
        break;

    default:
        break;
    }
}

/**
 * @brief Send data to an I2C slave, and store it in a destination variable.
 *
 * @param I2C_base Base address for I2C module.
 * @param slave_address The address of the slave on I2C bus.
 * @param data_ptr Pointer to the data to be sent.
 * @param data_size Number of bytes to be sent.
 * @return The status of the transfer, indicates whether it succeeded or failed.
 */
I2C_status I2C_master_send(I2C_TypeDef *I2C_base, uint8_t slave_address, uint8_t *data_ptr, uint32_t data_size)
{

    I2C1->CR1 |= (1 << 8);                         // Send start condition.
    for (volatile uint32_t i = 0; i <= 10000; i++) // Wait while start bit not set.
    {
        if (I2C1->SR1 & (1 << 0))
        {
            break;
        }
        else if (i == 10000)
        {
            return I2C_STATUS_ERR; // After timeout, return error.
        }
    }

    I2C1->DR = (slave_address << 1); // Send slave address with Write bit.

    while (!(I2C1->SR1 & 1 << 1)) // Wait while address not sent.
    {
        if (I2C1->SR1 & 1 << 10) // In case of NACK condition.
        {
            return I2C_STATUS_NACK;
        }
    }

    if (I2C1->SR2)
        ; // Read SR2 to clear ADDR bit

    for (volatile uint8_t *i = data_ptr; i < data_ptr + data_size; i++)
    {
        while (!(I2C1->SR1 & (1 << 7)))
            ;                    // Wait while TX not empty.
        I2C1->DR = *i;           // Write byte to data register.
        if (I2C1->SR1 & 1 << 10) // In case of NACK condition.
        {
            return I2C_STATUS_NACK;
        }
    }

    // Send stop transmission.
    I2C1->CR1 |= 1 << 9;
    return I2C_STATUS_SUCCESS;
}

/**
 * @brief Receive data from an I2C slave, and store it in a destination variable.
 *
 * @param I2C_base Base address for I2C module.
 * @param slave_address The address of the slave on I2C bus.
 * @param dest Destination pointer to store data at.
 * @param data_size Number of bytes to be received. Will send a NACK to stop slave after these bytes are received.
 * @return The status of the transfer, indicates whether it succeeded or failed.
 */
I2C_status I2C_master_receive(I2C_TypeDef *I2C_base, uint8_t slave_address, uint8_t *dest, uint32_t data_size)
{

    I2C_base->CR1 |= 1 << 10; // Set ACK bit.

    I2C1->CR1 |= (1 << 8);                         // Send start condition.
    for (volatile uint32_t i = 0; i <= 10000; i++) // Wait while start bit not set.
    {
        if (I2C1->SR1 & (1 << 0)) // If start bit set then break.
        {
            break;
        }
        else if (i == 10000)
        {
            return I2C_STATUS_ERR; // After timeout, return error.
        }
    }

    I2C1->DR = (slave_address << 1) | 1; // Send slave address with read bit.

    while (!(I2C1->SR1 & 1 << 1)) // Wait while address not sent.
    {
        if (I2C1->SR1 & 1 << 10) // In case of NACK condition.
        {
            return I2C_STATUS_NACK;
        }
    }

    if (I2C1->SR2) // Read SR2 to clear ADDR bit
        ;

    // In case of sending 1 byte.

    if (data_size == 1)
    {
        I2C_base->CR1 &= ~(1 << 10); // Clear ACK bit (for transmission).
        I2C_base->CR1 |= (1 << 9);   // Send a stop bit.

        for (int j = 0; j <= 1000; j++)
        {
            if (I2C_base->SR1 & 1 << 6) // If RX not empty
            {
                *dest++ = (uint8_t)I2C_base->DR; // Read from DR.
                break;
            }
            else if (j == 1000)
            {
                return I2C_STATUS_TIMEOUT;
            }
        }

        return I2C_STATUS_SUCCESS;
    }

    for (volatile uint32_t i = 0; i < data_size; i++)
    {
        for (int j = 0; j <= 1000; j++)
        {
            if (I2C_base->SR1 & 1 << 6) // If RX not empty
            {
                *dest++ = (uint8_t)I2C_base->DR; // Read from DR.
                break;
            }
            else if (j == 1000)
            {
                return I2C_STATUS_TIMEOUT;
            }
        }

        if (i == data_size - 2) // At the second to last byte.
        {
            I2C_base->CR1 &= ~(1 << 10); // Clear ACK bit (for transmission).
            I2C_base->CR1 |= (1 << 9);   // Send a stop bit.
        }
    }

    return I2C_STATUS_SUCCESS;
}
