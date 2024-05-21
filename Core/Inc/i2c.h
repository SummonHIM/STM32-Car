/**
 ******************************************************************************
 * @file    i2c.h
 * @brief   This file contains all the function prototypes for
 *          the i2c.c file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

#define OLED_SCL_PORT GPIOC
#define OLED_SDA_PORT GPIOC
#define OLED_PWR_PORT GPIOB
#define OLED_SCL_PIN GPIO_PIN_14 // PB6
#define OLED_SDA_PIN GPIO_PIN_15 // PB7
#define OLED_PWR_PIN GPIO_PIN_5

//
void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_wait_ack(void);
void i2c_send_ack(void);
void i2c_send_noack(void);
void i2c_send_byte(unsigned char cSendByte);
uint8_t i2c_receive_byte(void);

/* USER CODE END Includes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
