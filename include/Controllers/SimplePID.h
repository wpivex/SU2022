#pragma once
#include "vex.h"


class SimplePID {

public:

  SimplePID(float kp, float ki, float kd, float minimum = 0, float maximum = -1);

  float tick(float error);
  
  // SimplePID does not have end state checking, so we just always return alse
  virtual bool isCompleted() {return false; };

private:

  // Purpose of function is to run any code that is needed to calculate whether PID is done
  // No implementation in SimplePID, used for subclasses that make use of isCompleted()
  virtual void handleEndingCondition(float error);

  float _prevError, _prevIntegral;
  float _min, _max;
  float _KP, _KI, _KD;

};