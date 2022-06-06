#include "OdomRobot.h"

/*
A subclass of BaseBot that provides odometry functionality. Gives absolute positioning. tickOdom() must be called every frame in a seperate thread
*/

OdomRobot::OdomRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back): BaseRobot(distBetweenWheels, gyroPort), 
leftEncoder(left), rightEncoder(right), backEncoder(back),
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
  float deltaM = getMidEncoderAbsolute() - recordedM;
  float deltaL = getLeftEncoderAbsolute() - recordedL;
  float deltaTheta = bound180(gyroSensor.heading()- recordedTheta)*M_PI/180;
  
  // Split vector to X and Y 
  float distY = (deltaL+deltaR)/2;  
  float deltaX;
  float deltaY;
  float theta = gyroSensor.heading()*M_PI/180, rTheta = recordedTheta*M_PI/180;

  if(deltaTheta != 0){
    float radiusY = distY/deltaTheta;
    deltaX = radiusY * (cos(theta) - cos(rTheta));
    deltaY = radiusY * (sin(theta) - sin(rTheta));
    float radiusX = deltaM/deltaTheta;
    deltaX += radiusX * (sin(theta) - sin(rTheta));;
    deltaY += radiusX * (cos(theta) - cos(rTheta));
  } else {
    // prevent divison by 0, when robot has travelled perfectly straight
    deltaX = distY * (cos((gyroSensor.heading()*M_PI)/180));
    deltaY = distY * (sin((recordedTheta*M_PI)/180));
  }
  
  //Add X and Y distance to current values
  absoluteX -= deltaX;
  absoluteY += deltaY;
  recordedR = getRightEncoderAbsolute();
  recordedL = getLeftEncoderAbsolute();
  recordedTheta = gyroSensor.heading();
}
