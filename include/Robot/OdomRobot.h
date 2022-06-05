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

  float getAngle(bool isRadians = false);
  float getX();
  float getY();
  
  void setMotorVelocity(motor m, double percent);
  void calibrateGyro();

  void goToPoint(float x, float y, float theta);
  void teleop() {};
  

};