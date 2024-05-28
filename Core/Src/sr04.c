#include "car_wheels.h"
#include "ch34g.h"


float SR04_Dist(float CCM) { return ((CCM * 340) / 1000000.0) / 2 * 100.0; }

void SR04_WheelsControl(float CCM) {
  if (SR04_Dist(CCM) > 25) {
    CAR_Forward();
    HAL_Delay(200);
  } else if (SR04_Dist(CCM) < 20) {
    CAR_Backward();
    HAL_Delay(200);
  } else {
    Car_Stop();
    HAL_Delay(200);
  }
}

void SR04_FullWheelsControl(float CCM) {
  CH34G_TurnAngle(80, 900);

  if (SR04_Dist(CCM) > 25) {
    CAR_Forward();
    HAL_Delay(500);
  }

  if (SR04_Dist(CCM) < 25) {
    CH34G_TurnAngle(50, 900);

    if (SR04_Dist(CCM) > 25) {
      CAR_Rightward();
      HAL_Delay(700);
    } else {
      CH34G_TurnAngle(110, 900);
      if (SR04_Dist(CCM) > 25) {
        Car_Leftward();
        HAL_Delay(700);
      } else {
        CAR_Backward();
        HAL_Delay(700);
        CAR_Rightward();
        HAL_Delay(700);
      }
    }
  }
}