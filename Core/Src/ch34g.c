#include "ch34g.h"
#include "tim.h"
#include "utils.h"


/* 旋转舵机角度*/
void CH34G_TurnAngle(uint32_t angle, uint32_t delay) {
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, angle);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_Delay(delay);
  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

/* 初始化舵机 */
void CH34G_Init() {
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_Delay(500);
  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);

  CH34G_TurnAngle(80, 500);
}