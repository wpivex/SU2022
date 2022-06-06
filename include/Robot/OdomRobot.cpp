#include "OdomRobot.h"


OdomRobot::OdomRobot(int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back): gyroSensor(gyroPort), leftEncoder(left), rightEncoder(right), backEncoder(back),
ENCODER_DIAMETER(encoderDiameter) {

}

float OdomRobot::getAngle(bool isRadians) {
  float h = gyroSensor.heading();
  if (isRadians) h *= M_PI / 180;
  return h;
}

void OdomRobot::setMotorVelocity(motor m, double percent) {

  directionType d = percent > 0 ? forward : reverse;
  percent = fabs(percent);
  percent = fmin(100, fmax(-100, percent)); // bound between -100 and 100

  m.spin(d, percent / 100.0 * 12.0, voltageUnits::volt);
}

void OdomRobot::calibrateGyro() {
  gyroSensor.calibrate();

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
  wait(500, msec);
  gyroSensor.resetRotation();
  wait(500, msec);

  log("done calibration");
}