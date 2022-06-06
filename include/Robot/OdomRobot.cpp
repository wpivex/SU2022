#include "OdomRobot.h"


OdomRobot::OdomRobot(int32_t gyroPort, float encoderDiameter, float distWheel,
 triport::port left, triport::port right, triport::port mid): gyroSensor(gyroPort), leftEncoder(left), rightEncoder(right), midEncoder(mid),
ENCODER_DIAMETER(encoderDiameter), DIST_BETWEEN_WHEELS(distWheel) {

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
  
  wait(500, msec);
  gyroSensor.resetRotation();
  wait(500, msec);

  log("done calibration");
}

float OdomRobot::getMidEncoderDistance() {
  //Returns in inches
  return (midEncoder.rotation(deg) - relativeL)*(M_PI/180)*(ENCODER_DIAMETER/2);
}

float OdomRobot::getLeftEncoderDistance() {
  //Returns in inches
  return (leftEncoder.rotation(deg) - relativeL)*(M_PI/180)*(ENCODER_DIAMETER/2);
}

float OdomRobot::getRightEncoderDistance() {
  // Returns in inches
  return (rightEncoder.rotation(deg) - relativeR)*(M_PI/180)*(ENCODER_DIAMETER/2);
}

float OdomRobot::getAngleEncoder(){
  int encDiff = getLeftEncoderDistance()-getRightEncoderDistance();
  return 2*encDiff/DIST_BETWEEN_WHEELS;
}

int OdomRobot::odomTask(){
  int ct = 0;
  const int gyroHz = 50;
  const int hz = 500;
  while(true){
    tickOdom(ct==0);
    ct = (ct+1)%(hz/gyroHz);
    wait(1000/hz,msec);
  }
  return 0;
}

// Call every tick in a seperate thread to update absolute position
void OdomRobot::tickOdom(bool gyroTick) {

  float deltaR = getRightEncoderDistance() - recordedR;
  float deltaM = getMidEncoderDistance() - recordedM;
  float deltaL = getLeftEncoderDistance() - recordedL;
  float theta;
  if(gyroTick)
    theta = gyroSensor.heading()*M_PI/180;
  else theta = getAngleEncoder();
  
  // Split vector to X and Y 
  float distY = (deltaL+deltaR)/2;  
  float deltaX;
  float deltaY;
  float deltaTheta = theta-recordedTheta;
  if(deltaTheta != 0){
    float radiusY = distY/deltaTheta;
    deltaX = radiusY * (cos(theta) - cos(recordedTheta));
    deltaY = radiusY * (sin(theta) - sin(recordedTheta));
    float radiusX = deltaM/deltaTheta;
    deltaX += radiusX * (sin(theta) - sin(recordedTheta));
    deltaY += radiusX * (cos(theta) - cos(recordedTheta));
  } else {
    // prevent divison by 0, when robot has travelled perfectly straight
    deltaX = distY * cos(theta) + deltaM * sin(theta);
    deltaY = distY * sin(theta) + deltaM * cos(theta); 
  }
  recordedTheta = theta;
}