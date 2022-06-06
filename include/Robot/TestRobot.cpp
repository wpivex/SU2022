#include "TestRobot.h"

TestRobot::TestRobot(int32_t gyroPort, float encoderDiameter, triport::port left, triport::port right, triport::port back):
  HoloRobot(gyroPort, encoderDiameter, left, right, back),
  fl(PORT12, ratio18_1, false),
  fr(PORT1, ratio18_1, true),
  bl(PORT20, ratio18_1, false),
  br(PORT9, ratio18_1, true) {

  setBrakeType(coast);
}

void TestRobot::teleop() {
  holoDriveTeleop();
  buttons.updateButtonState();
}


void TestRobot::setDrivePower(float velFL, float velFR, float velBL, float velBR) {
  setMotorVelocity(fl, velFL);
  setMotorVelocity(fr, velFR);
  setMotorVelocity(bl, velBL);
  setMotorVelocity(br, velBR);
  /*log("LF: %.1f%.1f\nRF: %.1f%.1f\nLB: %.1f%.1f\nRB: %.1f%.1f", 
    velFL, fl.velocity(pct), 
    velFR, fr.velocity(pct),
    velBL, bl.velocity(pct),
    velBR, br.velocity(pct));*/
}
void TestRobot::stopDrive() { // stop all drive motors

  fl.stop();
  fr.stop();
  bl.stop();
  br.stop();

}

void TestRobot::setBrakeType(brakeType b) {
  fl.setBrake(b);
  fr.setBrake(b);
  bl.setBrake(b);
  br.setBrake(b);
}