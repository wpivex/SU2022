#include "HoloRobot.cpp"

class TestRobot : public HoloRobot {

public:
  TestRobot(int32_t gyroPort, float encoderDiameter, triport::port left, triport::port right, triport::port back);

  motor fl, fr, bl, br;

  void setDrivePower(float velFL, float velFR, float velBL, float velBR);
  void stopDrive(); // stop all drive motors
  void setBrakeType(brakeType b);


};