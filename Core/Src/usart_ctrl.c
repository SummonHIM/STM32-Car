#include "usart_ctrl.h"
#include "usart.h"
#include <string.h>


uint8_t p;
uint8_t data;
uint8_t Rx_Stat;

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

void Car_WheelsControl(UART_HandleTypeDef *huart) {
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