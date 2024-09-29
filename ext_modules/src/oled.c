#include "oled.h"

void OLED_init(I2C_TypeDef* I2C_base){
    uint8_t commands[] = {0x00, 0xAE, 0xD5, 0xF0, 0xA8, 64 - 1, 0x8D, 0x14, 0xAF, 0xA4, 0x20, 0x00};
    uint8_t start[] = {0x00, 0x21, 0, 127, 0x22, 0, 7};

    I2C_master_send(I2C_base, 0x3C, &commands, 12);
    I2C_master_send(I2C_base, 0x3C, &start, 7);
}