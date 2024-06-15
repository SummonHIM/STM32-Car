#include "sr04.h"
#include "car_wheels.h"
#include "ch34g.h"
#include "utils.h"

float SR04_Dist(float CCM) { return ((CCM * 340) / 1000000.0) / 2 * 100.0; }

void SR04_WheelsControl(float CCM) {
  if (SR04_Dist(CCM) > 25) {
    CAR_Forward();
    HAL_Delay(200);
  } else if (SR04_Dist(CCM) < 20) {
    CAR_Backward();
    HAL_Delay(400);
  } else {
    Car_Stop();
    HAL_Delay(200);
  }
}
