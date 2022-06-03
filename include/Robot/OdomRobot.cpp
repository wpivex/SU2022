#include "OdomRobot.h"


OdomRobot::OdomRobot(int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back): gyroSensor(gyroPort), leftEncoder(left), rightEncoder(right), backEncoder(back),
ENCODER_DIAMETER(encoderDiameter) {

}

float OdomRobot::getAngle() {
  return gyroSensor.heading();
}

void OdomRobot::setMotorVelocity(motor m, double percent) {

  directionType d = percent > 0 ? forward : reverse;
  percent = fabs(percent);
  percent = fmin(100, fmax(-100, percent)); // bound between -100 and 100

  m.spin(d, percent / 100.0 * 12.0, voltageUnits::volt);
}