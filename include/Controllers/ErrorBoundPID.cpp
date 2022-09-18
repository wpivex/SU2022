#pragma once
#include "ErrorBoundPID.h"
#include "constants.h"

/*
A PID controller with configurable parameters. isCompleted() returns whether PID has "settled" to a value, parametrized
by tolerance and repeated attributes
float kp: proportionality constant
float ki: integral constant
float kd: derivative constant
minimum: the clamped smallest MAGNITUDE of the tick() controller output. Meaning, we bound (-inf, -minumum] and [minimum, inf)
maximum: the clamped largest MAGNITUDE of the tick() controller output. Meaning, we bound [-maximum, maximum]
toleranceThreshold: the margin of error in which isCompleted() will return true
repeatedThreshold : the number of times the error must be within tolerance for isCompleted() to return true
*/
ErrorBoundPID::ErrorBoundPID(float kp, float ki, float kd, float minimum, float maximum, float toleranceThreshold, int repeatedThreshold)
: SimplePID(kp, ki, kd, minimum, maximum)
 {
  _toleranceThreshold = toleranceThreshold;
  _repeatedThreshold = repeatedThreshold;
  _numRepeated = 0;
}

void ErrorBoundPID::handleEndingCondition(float error) {
  if (fabs(error) < _toleranceThreshold) _numRepeated++;
  else _numRepeated = 0;
}

// Call to check whether PID has converged to a value. Useful with stuff like arm movement and aligns/turns
bool ErrorBoundPID::isCompleted() {

  return _numRepeated >= _repeatedThreshold;
;
}