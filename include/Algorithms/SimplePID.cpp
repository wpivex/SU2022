#include "SimplePID.h"

float SimplePID::tick(float error) {

  handleEndCondition(error);

  float integral = prevIntegral + error * 0.02;
  float derivative = (error - prevError) / 0.02;

  float output = K.P * error + K.I * integral + K.D * derivative;
  prevError = error;
  prevIntegral = integral;

  // Set mininum output value
  if (output > 0) {
    output = fmax(K.MIN, output);
  } else {
    output = fmin(-K.MIN, output);
  }
  output = fmax(-K.MAX, fmin(K.MAX, output));

  return output;
}