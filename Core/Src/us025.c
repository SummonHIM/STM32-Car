#include "main.h"

void US025_Start(void) {
    while (HAL_GPIO_ReadPin(SR04_ECHO_GPIO_Port, SR04_ECHO_Pin) == 1);
    HAL_GPIO_WritePin(SR04_TRIG_GPIO_Port, SR04_TRIG_Pin, GPIO_PIN_SET);
    HAL_Delay(15);
    HAL_GPIO_WritePin(SR04_TRIG_GPIO_Port, SR04_TRIG_Pin, GPIO_PIN_RESET);
}