#include "ir.h"

void IR_Processing() {
  if (GET_OUT_1 == 0 && GET_OUT_2 == 0 && GET_OUT_3 == 0 && GET_OUT_4 == 0) {
    CAR_Forward();
    HAL_Delay(10);
  }

  if (GET_OUT_1 == 1 && GET_OUT_2 == 0 && GET_OUT_3 == 0 && GET_OUT_4 == 0) {
    CAR_Rightward();
    HAL_Delay(250);
  }
  if (GET_OUT_1 == 0 && GET_OUT_2 == 1 && GET_OUT_3 == 0 && GET_OUT_4 == 0) {
    CAR_Rightward();
    HAL_Delay(150);
  }
  if (GET_OUT_1 == 1 && GET_OUT_2 == 1 && GET_OUT_3 == 0 && GET_OUT_4 == 0) {
    CAR_Rightward();
    HAL_Delay(300);
  }

  if (GET_OUT_1 == 0 && GET_OUT_2 == 0 && GET_OUT_3 == 1 && GET_OUT_4 == 0) {
    Car_Leftward();
    HAL_Delay(150);
  }
  if (GET_OUT_1 == 0 && GET_OUT_2 == 0 && GET_OUT_3 == 0 && GET_OUT_4 == 1) {
    Car_Leftward();
    HAL_Delay(250);
  }
  if (GET_OUT_1 == 0 && GET_OUT_2 == 0 && GET_OUT_3 == 1 && GET_OUT_4 == 1) {
    Car_Leftward();
    HAL_Delay(300);
  }
}