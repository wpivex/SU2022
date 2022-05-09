#pragma once
#include "TrapezoidController.h"

/*
A trapezoidal object allows you to approach the targetValue from any starting value.
The direction is dtermined by starting value (from first tick() call)
rampUp is determined by numRampUpFrames, which linearly interpolates from 0 to maxSpeed over the number of frames (so over time, not error)
Starting and ending speed are both defined as minSpeed by default. However, if startSpeed is defined, then that value will be used instead for start.
*/
Trapezoid::Trapezoid(float targetValue, float maxSpeedP, float minSpeedP, int numRampUpFrames, float slowDownValue, float endSlowValue, float startSpeedP) {

  curr = 0;
  target = targetValue;
  maxSpeed = maxSpeedP;
  minSpeed = minSpeedP;
  xn = numRampUpFrames;
  slowDown = slowDownValue;
  endSlow = endSlowValue;

  maxSpeed = fmax(minSpeed, maxSpeed);
  endSlow = fmin(targetValue, endSlowValue);
  slowDown = fmin(targetValue - endSlowValue, slowDown);
  if (startSpeedP == -1) startSpeed = minSpeedP;
  else startSpeed = startSpeedP;
  
}

float Trapezoid::tick(float currentValue) {

  curr = currentValue;

  if (firstFrame) {
    risingEdge = curr < target; // set trapezoidal direction. When crossed threshold from that direction, isCompleted
    firstFrame = false;
  }

  float delta;
  if(fabs(target - curr) < endSlow) delta = 0;
  else if (slowDown != 0 && fabs(target - curr) < slowDown+endSlow && slowDown > 0) delta = (fabs(target - curr) - endSlow) / slowDown;
  else delta = 1;
  float slowDownSpeed = minSpeed + (maxSpeed - minSpeed) * delta;
  float rampUpSpeed = startSpeed + (maxSpeed - startSpeed) * (xi+1.0) / (xn+1.0);

  float speed = fmin(slowDownSpeed, rampUpSpeed); // If there is both slowdown and rampUp, pick the smaller one

  if (xi < xn) xi++;
  return (risingEdge ? 1 : -1) * speed;
}

bool Trapezoid::isCompleted() {
  // logController("%f, %f", curr, target);
  if (firstFrame) return false;

  if (risingEdge) return curr >= target;
  else return curr <= target;
}