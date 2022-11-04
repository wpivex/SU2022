#pragma once
#include "vex.h"

typedef struct PIDParameters {
  float P, I, D;
  float MIN, MAX;

  PIDParameters(float kp, float ki, float kd, float minMagnitude, float maxMagnitude):
    P(kp), I(ki), D(kd), MIN(minMagnitude), MAX(maxMagnitude) {}

  PIDParameters(float kp, float ki, float kd):
    PIDParameters(kp, ki, kd, 0, 1000000) {}

} PIDParameters;

/*
A PID controller with configurable parameters. Does not have termination logic
*/
class SimplePID {

public:

  SimplePID(PIDParameters params): K(params) {}
  float tick(float error);
  void setNewParam(float kp, float ki, float kd);
protected:
  virtual void handleEndCondition(float error) {}

private:

  float prevError = 0;
  float prevIntegral = 0;
  
  PIDParameters K;

};
