#pragma once
#include "PIDController.h"
#include "constants.h"

/*
A PID controller with configurable parameters. An optional isCompleted() returns whether PID has "settled" to a value, set with a tolerance
and the number of times in a row needed to be in that tolerance.
You may set a minimum and maximum output
*/
PID::PID(float kp, float ki, float kd, float TOLERANCE, int REPEATED, float minimum, float maximum) {

  TOLERANCE_THRESHOLD = TOLERANCE; // the error threshold to be considered "done"
  REPEATED_THRESHOLD = REPEATED; // the number of times the threshold must be reached in a row to be considered "done"
  repeated = 0;

  K_p = kp;
  K_i = ki;
  K_d = kd;
  min = minimum;
  max = maximum;
}

float PID::tick(float error) {
  float integral = prevIntegral + error * 0.02;
  float derivative = (error - prevError) / 0.02;

  float output = K_p * error + K_i * integral + K_d * derivative;
  prevError = error;
  prevIntegral = integral;

  if (fabs(error) < TOLERANCE_THRESHOLD) repeated++;
  else repeated = 0;

  // Set mininum output value
  if (output > 0) {
    output = fmax(min, output);
  } else {
    output = fmin(-min, output);
  }
  if (max != -1) output = fmax(-max, fmin(max, output));

  //logController("Error: %f \n Output: %f \n P: %f \n D: %f", error, output, (K_p * error), (K_d * derivative));
  return output;
}

// Call to check whether PID has converged to a value. Useful with stuff like arm movement and aligns/turns but not with stuff like driving straight
bool PID::isCompleted() {
  //logController("asdf %d %d", repeated, REPEATED_THRESHOLD);
  return repeated >= REPEATED_THRESHOLD;
}