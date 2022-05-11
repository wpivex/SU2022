#pragma once
#include "BaseRobot.cpp"

class HoloRobot : public BaseRobot {

public:

  void move(float relHeading, float rotationAmt, float speedScalar = 1);
  void moveU(float absHeading, float rotationAmt, float speedScalar = 1);
  void holoDriveTeleop();

  // Virtual methods that need to be implemented
  virtual void spinFL(float percent) = 0; // front left
  virtual void spinFR(float percent) = 0; // front right
  virtual void spinBL(float percent) = 0; // back left
  virtual void spinBR(float percent) = 0; // back right
  virtual void stopDrive() = 0; // stop all drive motors


};