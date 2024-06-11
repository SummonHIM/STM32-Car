#include "car_wheels.h"
#include "ch34g.h"
#include "utils.h"
#include "sr04.h"


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

void SR04_LRControl(uint16_t frontOBS, uint16_t leftObs, uint16_t rightObs) {
  if (frontOBS == 1 && leftObs == 1 && rightObs == 1) {
    CAR_Rightward();
    HAL_Delay(1000);
  } else if (frontOBS == 1 && leftObs == 0 && rightObs == 0) {
    CAR_Rightward();
    HAL_Delay(200);
  } else if (frontOBS == 1 && leftObs == 1 && rightObs == 0) {
    CAR_Rightward();
    HAL_Delay(400);
  } else if (frontOBS == 0 && leftObs == 1 && rightObs == 1) {
    Car_Leftward();
    HAL_Delay(200);
  } else if (frontOBS == 0 && leftObs == 0 && rightObs == 1) {
    Car_Leftward();
    HAL_Delay(400);
  } else {
    CAR_Forward();
    HAL_Delay(500);
  }
  return;
}