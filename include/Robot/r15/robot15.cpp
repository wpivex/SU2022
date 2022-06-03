#include "robot15.h"
#include "Robot/PurePursuitRobot.h"

Robot15::Robot15() : BaseRobot(9.5, PORT16), leftMotorA(0), leftMotorB(0), leftMotorC(0), leftMotorD(0), rightMotorA(0), rightMotorB(0), 
  rightMotorC(0), rightMotorD(0) {

  leftMotorA = motor(PORT1, ratio6_1, true); 
  leftMotorB = motor(PORT2, ratio6_1, true);
  leftMotorC = motor(PORT12, ratio6_1, true);
  leftMotorD = motor(PORT10, ratio6_1, true);

  rightMotorA = motor(PORT4, ratio6_1, false);
  rightMotorB = motor(PORT18, ratio6_1, false);
  rightMotorC = motor(PORT20, ratio6_1, false);
  rightMotorD = motor(PORT21, ratio6_1, false);

  setControllerMapping();
}

void Robot15::setControllerMapping() {

}

float Robot15::distanceToDegrees(float distInches) {
  return distInches * (5/3.0) * 360 / 2 / M_PI / (3.25 / 2); // 4 in diameter wheels
}

float Robot15::degreesToDistance(float distDegrees) {
  return distDegrees * (3/5.0) / (360 / 2 / M_PI / (3.25 / 2)); // 4 in diameter wheels
}

// Run every tick
void Robot15::teleop() {
  
  basicDriveTeleop();

  buttons.updateButtonState();
}

// return in inches
float Robot15::getLeftEncoderDistance() {
  float sum = leftMotorA.rotation(deg) + leftMotorB.rotation(deg) + leftMotorC.rotation(deg) + leftMotorD.rotation(deg);
  return degreesToDistance(sum / 4.0);
}

// return in inches
float Robot15::getRightEncoderDistance() {
  float sum = rightMotorA.rotation(deg) + rightMotorB.rotation(deg) + rightMotorC.rotation(deg) + rightMotorD.rotation(deg);
  return degreesToDistance(sum / 4.0);
}

void Robot15::resetEncoderDistance() {
  leftMotorA.resetRotation();
  leftMotorB.resetRotation();
  leftMotorC.resetRotation();
  leftMotorD.resetRotation();
  rightMotorA.resetRotation();
  rightMotorB.resetRotation();
  rightMotorC.resetRotation();
  rightMotorD.resetRotation();
}

// Go forward a number of inches, maintaining a specific heading
// Calling general function with 15-specifc params
// minSpeed default is 18
void Robot15::goForwardU(float distInches, float maxSpeed, float universalAngle, bool stopAfter, float startSpeed, float stopSpeed, float timeout) {

  float rampUpFrames = (startSpeed == -1) ? 0 : maxSpeed * 0.075; // rampUp slope
  float slowDownInches = (stopSpeed == -1) ? 0 : (maxSpeed - stopSpeed) * 0.06; // slowDown slope
  float endSlowInches = (stopSpeed == -1) ? 0 : 4.5;

  BaseRobot::goForwardU_Abstract(1.0, distInches, maxSpeed, universalAngle, rampUpFrames, slowDownInches, endSlowInches, 
    stopAfter, startSpeed, stopSpeed, timeout);
}

// Turn to some universal angle based on starting point. Turn direction is determined by smallest angle to universal angle
// Calling general function with 15-specifc params
void Robot15::goTurnU(float universalAngleDegrees, int direction, bool stopAfter, float timeout, float maxSpeed) {
  BaseRobot::goTurnU_Abstract(2.5, 0, 0.1, 1.3, 3, 18, universalAngleDegrees, direction, stopAfter, timeout, maxSpeed);
}

void Robot15::setLeftVelocity(directionType d, double percent) {

  setMotorVelocity(leftMotorA, d, percent);
  setMotorVelocity(leftMotorB, d, percent);
  setMotorVelocity(leftMotorC, d, percent);
  setMotorVelocity(leftMotorD, d, percent);
}

void Robot15::setRightVelocity(directionType d, double percent) {
  
  setMotorVelocity(rightMotorA, d, percent);
  setMotorVelocity(rightMotorB, d, percent);
  setMotorVelocity(rightMotorC, d, percent);
  setMotorVelocity(rightMotorD, d, percent);
}

void Robot15::stopLeft() {
  leftMotorA.stop();
  leftMotorB.stop();
  leftMotorC.stop();
  leftMotorD.stop();
}

void Robot15::stopRight() {
  rightMotorA.stop();
  rightMotorB.stop();
  rightMotorC.stop();
  rightMotorD.stop();
}

void Robot15::setBrakeType(brakeType b) {
  leftMotorA.setBrake(b);
  leftMotorB.setBrake(b);
  leftMotorC.setBrake(b);
  leftMotorD.setBrake(b);
  rightMotorA.setBrake(b);
  rightMotorB.setBrake(b);
  rightMotorC.setBrake(b);
  rightMotorD.setBrake(b);
}

float Robot15::getDriveCurrent() {
  float currentSum = leftMotorA.current() + leftMotorB.current() + leftMotorC.current() + leftMotorD.current() + rightMotorA.current()
    + rightMotorB.current() + rightMotorC.current() + rightMotorD.current();
  return currentSum / 8;
}