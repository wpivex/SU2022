#pragma once
#include "BaseRobot.cpp"

class HoloRobot : virtual public BaseRobot {

public:
  HoloRobot(float distBetweenWheels, int32_t gyroPort);
  void moveWithComponents(float drive, float strafe, float turn);
  void moveHeadingU(float absHeading, float translationSpeed, float turnSpeed);
  void holoDriveTeleop();

  // Virtual methods that need to be implemented
  virtual void setDrivePower(float velFL, float velFR, float velBL, float velBR) = 0;
  virtual void stopDrive() = 0; // stop all drive motors


};