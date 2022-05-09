#pragma once
#include "vex.h"


class PID {

  public:

  PID(float kp, float ki, float kd, float TOLERANCE = -1, int REPEATED = -1, float minimum = 0, float maximum = -1);
  float tick(float error);
  bool isCompleted();

  private:

  float prevError = 0;
  float prevIntegral = 0;
  float K_p, K_i, K_d;
  
  float TOLERANCE_THRESHOLD;
  int REPEATED_THRESHOLD;
  int repeated = 0;
  float min = 0;
  float max = 0;

};