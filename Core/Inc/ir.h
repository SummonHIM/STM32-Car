#include "car_wheels.h"
#include "main.h"

#define GET_OUT_1 HAL_GPIO_ReadPin(OUT_1_GPIO_Port, OUT_1_Pin)
#define GET_OUT_2 HAL_GPIO_ReadPin(OUT_2_GPIO_Port, OUT_2_Pin)
#define GET_OUT_3 HAL_GPIO_ReadPin(OUT_3_GPIO_Port, OUT_3_Pin)
#define GET_OUT_4 HAL_GPIO_ReadPin(OUT_4_GPIO_Port, OUT_4_Pin)

void IR_Processing();