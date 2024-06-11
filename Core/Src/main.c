/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "car_wheels.h"
#include "ch34g.h"
#include "ir.h"
#include "oled.h"
#include "sr04.h"
#include "us025.h"
#include "utils.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t ModeSwitch = 0;
float CCM;

uint8_t p;
uint8_t data;
uint8_t Rx_Stat;

uint16_t frontOBS = 0;
uint16_t leftObs = 0;
uint16_t rightObs = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void USART_WheelsControl(UART_HandleTypeDef *huart) {
  HAL_UART_Receive_IT(huart, &p, 1);

  switch (Rx_Stat) {
  case 1:
    CAR_Forward();
    memset(&data, 0, 1);
    break;
  case 2:
    CAR_Backward();
    memset(&data, 0, 1);
    break;
  case 3:
    Car_Leftward();
    memset(&data, 0, 1);
    break;
  case 4:
    CAR_Rightward();
    memset(&data, 0, 1);
    break;
  case 0:
    Car_Stop();
    memset(&data, 0, 1);
    break;
  }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  CH34G_Init();
  oled_init();
  HAL_ADCEx_Calibration_Start(&hadc1);
  HAL_ADC_Start(&hadc1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    US025_Start();
    OLED_Disp_CarInfo(CCM, ModeSwitch);

    switch (ModeSwitch) {
    case 1:
      SR04_WheelsControl(CCM);
      break;
    case 2:
      USART_WheelsControl(&huart3);
      break;
    case 3:
      IR_Processing();
      break;
    case 4:
      CH34G_TurnAngle(50, 400);
      if (SR04_Dist(CCM) < 25)
        leftObs = 1;

      CH34G_TurnAngle(80, 400);
      if (SR04_Dist(CCM) < 25)
        frontOBS = 1;

      CH34G_TurnAngle(110, 400);
      if (SR04_Dist(CCM) < 25)
        rightObs = 1;

      SR04_LRControl(frontOBS, leftObs, rightObs);

      frontOBS = 0;
      leftObs = 0;
      rightObs = 0;
      CH34G_TurnAngle(80, 200);
      break;
    default:
      Car_Stop();
      break;
    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == KEY2_Pin) {
      ModeSwitch += 1;
      if (ModeSwitch > 4)
        ModeSwitch = 1;
  }

  if (GPIO_Pin == KEY1_Pin) {
    ModeSwitch = 0;
  }

  if (HAL_GPIO_ReadPin(SR04_ECHO_GPIO_Port, SR04_ECHO_Pin) == 1) {
    __HAL_TIM_SetCounter(&htim2, 0);
    HAL_TIM_Base_Start(&htim2);
  }

  if (HAL_GPIO_ReadPin(SR04_ECHO_GPIO_Port, SR04_ECHO_Pin) == 0) {
    CCM = __HAL_TIM_GetCounter(&htim2);
    HAL_TIM_Base_Stop(&htim2);
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart == &huart3) {
    data = p;
    switch (data) {
    case 'W':
      Rx_Stat = 1;
      break;
    case 'S':
      Rx_Stat = 2;
      break;
    case 'A':
      Rx_Stat = 3;
      break;
    case 'D':
      Rx_Stat = 4;
      break;
    case 'Q':
      Rx_Stat = 0;
      break;
    }
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
