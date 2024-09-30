#ifndef OLED_H
#define OLED_H

#include "i2c.h"

typedef struct
{
    uint8_t data_byte;
    uint8_t pixels[8][128];
} frame_t;

void OLED_init(I2C_TypeDef* I2C_base, frame_t* frame);
void OLED_draw_rectangle(frame_t* frame, uint8_t x, uint8_t y, uint8_t length, uint8_t width);
#endif