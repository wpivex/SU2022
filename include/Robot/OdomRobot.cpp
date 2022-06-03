#include "OdomRobot.h"


OdomRobot::OdomRobot(int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back): gyroSensor(gyroPort), leftEncoder(left), rightEncoder(right), backEncoder(back),
ENCODER_DIAMETER(encoderDiameter) {

}

OdomRobot::getAngle() {
  return gyroSensor.heading();
}