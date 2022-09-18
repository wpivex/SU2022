#pragma once
#include "vex.h"
#include "SimplePID.h"


class ErrorBoundPID {

public:

  ErrorBoundPID(float kp, float ki, float kd, float minimum = 0, float maximum = 100, float toleranceThreshold, int repeatedThreshold = 1);

  float tick(float error);
  
  bool isCompleted();

private:

  void handleEndingCondition(float error);

  float _toleranceThreshold;
  int _repeatedThreshold, _numRepeated;
  float _prevError, _prevIntegral;
  float _min, _max;
  float _KP, _KI, _KD;

};