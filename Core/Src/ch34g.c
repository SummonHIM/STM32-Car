#include "ch34g.h"
#include "tim.h"

/* 旋转舵机角度*/
void Car_CH34G_TurnAngle(uint32_t angle) {
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, angle);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_Delay(900);
  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

/* 初始化舵机 */
void Car_CH34G_Init() {
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_Delay(900);
  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);

  Car_CH34G_TurnAngle(25);
}