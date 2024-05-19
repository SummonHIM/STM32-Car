/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_PC13_Pin GPIO_PIN_13
#define LED_PC13_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOA
#define KEY1_EXTI_IRQn EXTI9_5_IRQn
#define BIN2_Pin GPIO_PIN_0
#define BIN2_GPIO_Port GPIOB
#define BIN1_Pin GPIO_PIN_1
#define BIN1_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_12
#define AIN2_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_13
#define AIN1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_12
#define KEY2_GPIO_Port GPIOA
#define KEY2_EXTI_IRQn EXTI15_10_IRQn
#define OUT_4_Pin GPIO_PIN_15
#define OUT_4_GPIO_Port GPIOA
#define OUT_3_Pin GPIO_PIN_3
#define OUT_3_GPIO_Port GPIOB
#define OUT_2_Pin GPIO_PIN_4
#define OUT_2_GPIO_Port GPIOB
#define OUT_1_Pin GPIO_PIN_5
#define OUT_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
