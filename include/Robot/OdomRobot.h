#pragma once
#include "constants.h"

using namespace vex;

class OdomRobot {

public:
  OdomRobot(int32_t gyroPort, float encoderDiamter, triport::port left, triport::port right, triport::port back);

  const float ENCODER_DIAMETER;
  encoder leftEncoder;
  encoder rightEncoder;
  encoder backEncoder;

  inertial gyroSensor;

  float getAngle();
  void setMotorVelocity(motor m, double percent);

};