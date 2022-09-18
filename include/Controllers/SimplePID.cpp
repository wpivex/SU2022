#pragma once
#include "SimplePID.h"

/*
A PID controller with configurable parameters.
float kp: proportionality constant
float ki: integral constant
float kd: derivative constant
minimum: the clamped smallest MAGNITUDE of the tick() controller output. Meaning, we bound (-inf, -minumum] and [minimum, inf)
maximum: the clamped largest MAGNITUDE of the tick() controller output. Meaning, we bound [-maximum, maximum]
*/
SimplePID::SimplePID(float kp, float ki, float kd, float minimum, float maximum) {

  _KP = kp;
  _KI = ki;
  _KD = kd;
  _min = minimum;
  _max = maximum;
}

// Run one tick of PID given the error, and return the bounded controller output to be sent to motors
float SimplePID::tick(float error) {

  // calculate integral and derivative for current tick
  float integral = _prevIntegral + error * 0.02;
  float derivative = (error - _prevError) / 0.02;

  // Get output from summing P, I, and D terms
  float output = _KP * error + _KI * integral + _KD * derivative;

  // Store current state to be previous state of next tick
  _prevError = error;
  _prevIntegral = integral;

  // bound (-inf, -minumum] and [minimum, inf)
  if (output > 0) {
    output = fmax(_min, output);
  } else {
    output = fmin(-_min, output);
  }

  // bound [-maximum, maximum]
  output = clamp(output, -_max, _max);

  // does nothing in base class
  handleEndingCondition(error);

  return output;
}
