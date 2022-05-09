#include "OdomRobot.h"

OdomRobot::OdomRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter): BaseRobot(distBetweenWheels, gyroPort), 
leftEncoder(Brain.ThreeWirePort.A), rightEncoder(Brain.ThreeWirePort.B), backEncoder(Brain.ThreeWirePort.C),
ENCODER_DIAMETER(encoderDiameter) {

  // stuff

}

// return in inches
float OdomRobot::getLeftEncoderAbsolute() {
  return leftEncoder.rotation(deg) * M_PI * ENCODER_DIAMETER / 360.0 / 3.0;
}

// return in inches
float OdomRobot::getRightEncoderAbsolute() {
  return rightEncoder.rotation(deg) * M_PI * ENCODER_DIAMETER / 360.0 / 3.0;
}

void OdomRobot::resetEncoderDistance() {
  relativeL = leftEncoder.rotation(deg);
  relativeR = rightEncoder.rotation(deg);
}

float OdomRobot::getLeftEncoderDistance() {
  return leftEncoder.rotation(deg) - relativeL;
}

float OdomRobot::getRightEncoderDistance() {
  return rightEncoder.rotation(deg) - relativeR;
}

// Call every tick in a seperate thread to update absolute position
void OdomRobot::tickOdom() {

  float deltaR = getRightEncoderAbsolute() - recordedR;
  float deltaL = getLeftEncoderAbsolute() - recordedL;
  float deltaTheta = bound180(gyroSensor.heading()- recordedTheta)*M_PI/180;
  
  // Split vector to X and Y 
  float dist = (deltaL+deltaR)/2;
  float deltaX;
  float deltaY;
  if(deltaTheta != 0){
    float radius = dist/deltaTheta;
    deltaX = radius * (cos((gyroSensor.heading()*M_PI)/180) - cos(recordedTheta*M_PI/180));
    deltaY = radius * (sin((gyroSensor.heading()*M_PI)/180) - sin(recordedTheta*M_PI/180));
  } else {
    // prevent divison by 0, when robot has travelled perfectly straight
    deltaX = dist * (cos((gyroSensor.heading()*M_PI)/180));
    deltaY = dist * (sin((recordedTheta*M_PI)/180));
  }
  
  //Add X and Y distance to current values
  absoluteX -= deltaX;
  absoluteY += deltaY;
  recordedR = getRightEncoderAbsolute();
  recordedL = getLeftEncoderAbsolute();
  recordedTheta = gyroSensor.heading();
}
