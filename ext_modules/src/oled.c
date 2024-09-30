#include "oled.h"

/**
 * @brief Initialize the OLED display.
 *
 * @param I2C_base I2C module connected to the OLED.
 * @param frame The frame_t object that will be written to the OLED display.
 */
void OLED_init(I2C_TypeDef *I2C_base, frame_t *frame)
{
    uint8_t commands[] = {0x00, 0xAE, 0xD5, 0xF0, 0xA8, 64 - 1, 0x8D, 0x14, 0xAF, 0xA4, 0x20, 0x00};
    uint8_t start[] = {0x00, 0x21, 0, 127, 0x22, 0, 7};

    // Initialize frame.
    frame->data_byte = 0x40;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            frame->pixels[i][j] = 0;
        }
    }

    I2C_master_send(I2C_base, 0x3C, &commands, 12);
    I2C_master_send(I2C_base, 0x3C, &start, 7);
}

/**
 * @brief Draw a rectangle with the specified dimensions onto a frame_t object.
 * 
 * @param frame The frame object to draw on. It should be sent to OLED display.
 */
void OLED_draw_rectangle(frame_t *frame, uint8_t x, uint8_t y, uint8_t length, uint8_t width)
{
    // Clear the frame.
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            frame->pixels[i][j] = 0;
        }
    }

    // First row.
    for (int j = x; j < x + width && j < 128; j++)
    {
        frame->pixels[y / 8][j] = 0xff << y % 8;

        if (length < 8)
        {
            frame->pixels[y / 8][j] &= 0xff >> (8 - y % 8 - length);
            return;
        }
    }

    int i = 1;
    length -= 8 - y % 8;

    // Middle rows.
    while (length >= 8)
    {
        for (int j = x; j < x + width && j < 128; j++)
        {
            frame->pixels[y/8 + i][j] = 0xff;
        }
        i++;
        length -= 8;
    }
    
    // Final Rows.
    for (int j = x; j < x + width && j < 128; j++)
    {
        frame->pixels[y / 8 + i][j] = 0xff >> 8 - length;
    }

}
