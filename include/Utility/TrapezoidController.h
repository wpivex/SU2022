#pragma once
#include "vex.h"
#include "constants.h"

class Trapezoid {

  public:
  Trapezoid(float targetValue, float maxSpeedP, float minSpeedP, int numRampUpFrames, float slowDownValue, float endSlowValue = 0, float startSpeedP = -1);
  float tick(float currentValue);
  bool isCompleted();
  
  private:
  bool risingEdge;
  bool firstFrame = true;
  int xi = 0;
  int xn;
  float curr, target, maxSpeed, minSpeed, startSpeed, rampUp, slowDown, endSlow;

};