#ifndef __OLED_H
#define __OLED_H

#include "i2c.h"
#include "main.h"

#define Max_Column 128
#define Max_Row 32

#define OLED_CMD 0  // Ð´ÃüÁî
#define OLED_DATA 1 // Ð´Êý¾Ý

//
void oled_show_char(uint8_t x, uint8_t y, uint8_t chr);
void oled_show_string(uint8_t line, uint8_t *chr);
void oled_init(void);
void oled_clear(void);
void oled_show_CH_char(uint8_t x, uint8_t y, uint8_t chr);
//
typedef enum {
  OLED_DSP_LINE0 = 0,
  OLED_DSP_LINE1 = 2,
} OLED_DSP_LINE;

#endif
