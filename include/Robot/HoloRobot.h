#pragma once
#include "OdomRobot.cpp"
#include "Utility/PIDController.cpp"
#include "Utility/Point.h"

class HoloRobot : public OdomRobot {

public:
  HoloRobot(int32_t gyroPort, float encoderDiameter, float wheelDist,
 triport::port left, triport::port right, triport::port back);

  Point fieldToRelCoords(float absX, int absY);

  void moveWithComponents(float drive, float strafe, float turn);
  void moveHeadingU(float absHeading, float translationSpeed, float turnSpeed, bool isFieldCentric = true);
  void holoDriveTeleop();
  void goToPoint(float x, float y, float theta);

  // Virtual methods that need to be implemented
  virtual void setDrivePower(float velFL, float velFR, float velBL, float velBR) = 0;
  virtual void stopDrive() = 0; // stop all drive motors

protected:
    float targetHeading = 0;
    int time = -1;
    bool isFieldCentric = true;

};