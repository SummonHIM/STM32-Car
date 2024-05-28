#include <stdint.h>
#include "utils.h"

void Delay_MS(uint16_t time) {
  uint16_t i = 0;
  while (time--) {
    i = 12000; // 以ms为单位
    while (i--);
  }
}