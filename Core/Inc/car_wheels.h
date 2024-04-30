#include "stm32f1xx_hal.h"

// 左轮
#define AIN1_H HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET)
#define AIN1_L HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET)

#define AIN2_H HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET)
#define AIN2_L HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET)

// 右轮
#define BIN1_H HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET)
#define BIN1_L HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET)

#define BIN2_H HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET)
#define BIN2_L HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET)

/* 小车前进 */
void CAR_Forward(void);

/* 小车后退 */
void CAR_Backward(void);

/* 小车左转 */
void Car_Leftward(void);

/* 小车右转 */
void CAR_Rightward(void);

/* 小车停止 */
void Car_Stop(void);

/* 控制小车速度 */
void Car_SpeedLevel(uint32_t width);