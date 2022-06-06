#pragma once
#include "constants.h"

using namespace vex;

class OdomRobot {

public:
  OdomRobot(int32_t gyroPort, float encoderDiamter, float distWheel, triport::port left, triport::port right, triport::port back);

  const float DIST_BETWEEN_WHEELS;
  //Diameter of encoder wheel
  const float ENCODER_DIAMETER;
  encoder leftEncoder;
  encoder rightEncoder;
  encoder midEncoder;

  inertial gyroSensor;

  float getAngle(bool isRadians = false);
  float getX();
  float getY();

  void goToPoint(float x, float y, float theta);
  void teleop() {};
  void calibrateGyro();

  int odomTask();
  
  void resetEncoderDistance();

private:

  float absoluteX = 0, absoluteY = 0;
  float recordedL = 0, recordedR = 0;
  float recordedM = 0, recordedTheta = 0;
  float relativeL = 0, relativeR = 0;
  
  
  void tickOdom(bool gyroTick);
  float getLeftEncoderDistance();
  float getMidEncoderDistance();
  float getRightEncoderDistance();
  float getAngleEncoder();
};