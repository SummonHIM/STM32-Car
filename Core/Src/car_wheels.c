#include "car_wheels.h"
#include "tim.h"

/* 小车前进 */
void CAR_Forward(void) {
  AIN1_H;
  BIN1_H;
  AIN2_L;
  BIN2_L;
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

/* 小车后退 */
void CAR_Backward(void) {
  AIN1_L;
  BIN1_L;
  AIN2_H;
  BIN2_H;
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

/* 小车左转 */
void Car_Leftward(void) {
  AIN1_L;
  BIN1_H;
  AIN2_H;
  BIN2_L;
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

/* 小车右转 */
void CAR_Rightward(void) {
  AIN1_H;
  BIN1_L;
  AIN2_L;
  BIN2_H;
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

/* 小车停止 */
void Car_Stop(void) {
  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}

/* 控制小车速度 */
void Car_SpeedLevel(uint32_t width) {
  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, width);
}