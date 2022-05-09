#pragma once
#include "BaseRobot.h"

BaseRobot::BaseRobot(float distBetweenWheels, int32_t gyroPort): DIST_BETWEEN_WHEELS(distBetweenWheels), gyroSensor(gyroPort) {
  
}

float BaseRobot::getAngle() {
  return gyroSensor.heading();
}

void BaseRobot::calibrateGyroBlocking() {

  wait(500, msec);
  gyroSensor.calibrate();

  int i = 0;
  while (gyroSensor.isCalibrating()) {
    wait(20, msec);
    i++;
  }
  gyroSensor.resetRotation();
  wait(1000, msec);
  
  log("done calibration");
}

// If the robot is known to have a given heading (i.e. from wall align) and the gyro heading is close enough to heading, recalibrate gyro heading
void BaseRobot::possiblyResetGyro(float targetAngle, float angleTolerance) {

  if (fabs(getAngleDiff(targetAngle, getAngle())) < angleTolerance) {
    logController("YES set heading\nfrom:%f\nto:%f", getAngle(), targetAngle);
    gyroSensor.setHeading(targetAngle, degrees);
  } else {
    logController("NO set heading\nfrom:%f\nto:%f", getAngle(), targetAngle);
  }
}

void BaseRobot::setMotorVelocity(motor m, directionType d, double percent) {
  if (percent < 0) {
    d = (d == forward) ? reverse : forward;
    percent = -percent;
  }

  percent = fmin(100, fmax(-100, percent)); // bound between -100 and 100

  m.spin(d, percent / 100.0 * 12.0, voltageUnits::volt);
}

void BaseRobot::goCurve(float distInches, float maxSpeed, float turnPercent, float rampUpFrames, float slowDownInches, float endSlowInches,
bool stopAfter, float slowMinSpeed) {
  float timeout = 5;

  Trapezoid trap(fabs(distInches), maxSpeed, slowMinSpeed, rampUpFrames, slowDownInches, endSlowInches);

  int startTime = vex::timer::system();
  resetEncoderDistance();
  directionType dir = distInches > 0 ? forward : reverse;

  while (!trap.isCompleted() && !isTimeout(startTime, timeout)) {
  
    float speed = trap.tick(fabs(getEncoderDistance()));

    // turnPercent bounded between -1 (counterclockwise point turn) and 1 (clockwise point turn)
    float lspeed, rspeed;
    if (turnPercent >= 0) {
      lspeed = 1;
      rspeed = 1 - 2*turnPercent;
    } else {
      rspeed = 1;
      lspeed = 1 + 2*turnPercent;
    }

    setLeftVelocity(dir, lspeed * speed);
    setRightVelocity(dir, rspeed * speed);

    wait(20, msec);
  }

  if (stopAfter) {
    stopLeft();
    stopRight();
  }
}

// Trapezoidal motion profiling
// Will use gyro sensor
// distAlongCirc is positive if forward, negative if reverse
// curveDirection is true for right, false for left
void BaseRobot::goRadiusCurve(float radius, float circProportion, bool curveDirection, float maxSpeed, int rampUpFrames, 
    float slowDownInches, bool stopAfter, float timeout) {

  float distAlongCircum = circProportion*M_PI*radius*2;
  float v_ratio = fabs((radius+DIST_BETWEEN_WHEELS)/(radius-DIST_BETWEEN_WHEELS));

  Trapezoid trap(distAlongCircum, maxSpeed, 20, rampUpFrames, slowDownInches);

  int startTime = vex::timer::system();
  resetEncoderDistance();

  // Repeat until either arrived at target or timed out
  while (!trap.isCompleted() && !isTimeout(startTime, timeout)) {

    float distSoFar = getEncoderDistance();

    float speed = trap.tick(distSoFar); 
    log("Current: %f\nTotal: %f", distSoFar, distAlongCircum);

    float lPower = speed / (curveDirection ? 1:v_ratio);
    float rPower =  speed / (curveDirection ? v_ratio:1);

    setLeftVelocity(forward, lPower);
    setRightVelocity(forward, rPower);

    wait(20, msec);
  }
  if(stopAfter){
    stopLeft();
    stopRight();
  }
}

void BaseRobot::goForwardTimed(float duration, float speed) {

  int startTime = vex::timer::system();

  while (!isTimeout(startTime, duration)) {
    setLeftVelocity(forward, speed);
    setRightVelocity(forward, speed);
    wait(20, msec);
  }
  stopLeft();
  stopRight();
}

// THIS FUNCTION DOES NOT STOP THE MOTORS; THEY WILL BE RUNNING AT FULL SPEED BACKWARDS AT THE END
// Make sure to handle this somehow, like adding a goForwardU backwards to decelerate to a stop
void BaseRobot::goFightBackwards(float currThresh) {

  VisualGraph g(-0.1, 2.9, 8, 50);

  setLeftVelocity(reverse, 100);
  setRightVelocity(reverse, 100);
  wait(500, msec);
  float curr = 3;
  bool display = true;
  while (curr > currThresh) {
    curr = getDriveCurrent();
    g.push(curr);
    if (display) g.display();
    display = !display;

    wait(20, msec);
  }
  g.push(curr,0);
  g.display();

}

// Go forward a number of inches, maintaining a specific heading
void BaseRobot::goForwardU_Abstract(float K_P, float distInches, float maxSpeed, float universalAngle, float rampUpFrames, float slowDownInches, 
float endSlowInches, bool stopAfter, float startSpeed, float stopSpeed, float timeout) {

  Trapezoid trap(distInches, maxSpeed, stopSpeed, rampUpFrames, slowDownInches, endSlowInches, startSpeed);
  PID turnPID(K_P, 0.00, 0);

  float correction = 0;
  float currDist;
  int startTime = vex::timer::system();
  
  resetEncoderDistance();

  //log("start forward %f %f %f", distInches, startX, startY);

  while (!trap.isCompleted() && !isTimeout(startTime, timeout)) {

    currDist = getEncoderDistance();
    
    float speed = trap.tick(currDist);
    float ang = getAngleDiff(universalAngle, getAngle());
    correction = (universalAngle == -1) ? 0 : turnPID.tick(ang);
 
    setLeftVelocity(forward, speed + correction);
    setRightVelocity(forward, speed - correction);

    //log("Dist: %f\nSpeed: %f", currDist, speed);

    wait(20, msec);
  }
  if (stopAfter) {
    stopLeft();
    stopRight();
  }
  //log("straight done");
}

// Turn to some universal angle based on starting point.
// If direction = 0, turn direction is determined by smallest angle to universal angle
// If direction = 1, force clockwise.  If direction = -1, force counterclockwise.
void BaseRobot::goTurnU_Abstract(float KP, float KI, float KD, float TOLERANCE, float REPEATED, float MINUMUM,
float universalAngleDegrees, int direction, bool stopAfter, float timeout, float maxSpeed) {

  PID anglePID(KP, KI, KD, TOLERANCE, REPEATED, MINUMUM, maxSpeed);

  float speed;

  log("initing");
  int startTime = vex::timer::system();
  log("about to loop");

  float relativeAngle = 0 - getAngleDiff(universalAngleDegrees, getAngle()); // negative = turn clockwise, positive = turn counterclockwise
  if (relativeAngle < 0 && direction == -1) relativeAngle += 360; // closest is to turn clockwise, but force turn counterclockwise
  else if (relativeAngle > 0 && direction == 1) relativeAngle -= 360; // closest is to turn counterclockwise, but force turn clockwise

  gyroSensor.setRotation(relativeAngle, deg); // set starting rotation, PID until gyroSensor rotation = 0

  while (!anglePID.isCompleted() && !isTimeout(startTime, timeout)) {
    
    speed = anglePID.tick(gyroSensor.rotation());

    //log("Turn \nTarget: %f \nCurrent: %f \nDiff: %f\nSpeed: %f \nGPS: %f", universalAngleDegrees, getAngle(), ang, speed, GPS11.heading());
    //log("heading: %f", GPS11.heading());
    // log("Heading: %f\nSpeed: %f", getAngle(), speed);

    setLeftVelocity(reverse, speed);
    setRightVelocity(forward, speed);

    wait(20, msec);
  }
  //log("wtf done");

  if (stopAfter) {
    stopLeft();
    stopRight();
  }  
}

// has NO motion profiling. Usually used in conjunction with other methods to add motion profiile
// If direction = 0, turn direction is determined by smallest angle to universal angle
// If direction = 1, force clockwise.  If direction = -1, force counterclockwise.
void BaseRobot::goTurnFastU(float universalAngleDegrees, int direction, float speed, bool stopAfter) {

  float relativeAngle = 0 - getAngleDiff(universalAngleDegrees, getAngle()); // negative = turn clockwise, positive = turn counterclockwise
  if (relativeAngle < 0 && direction == -1) relativeAngle += 360; // closest is to turn clockwise, but force turn counterclockwise
  else if (relativeAngle > 0 && direction == 1) relativeAngle -= 360; // closest is to turn counterclockwise, but force turn clockwise

  gyroSensor.setRotation(relativeAngle, deg); // set starting rotation, PID until gyroSensor rotation = 0
  setLeftVelocity(relativeAngle < 0 ? forward : reverse, speed);
  setRightVelocity(relativeAngle < 0 ? reverse : forward, speed);

  while (relativeAngle < 0 ? gyroSensor.rotation() < 0 : gyroSensor.rotation() > 0) {
    wait(20, msec);
  }
  if (stopAfter) {
    stopLeft();
    stopRight();
  }
    
}

// Go forward until the maximum distance is hit or the timeout is reached
// for indefinite timeout, set to -1
void BaseRobot::goVision_Abstract(float K_P, float MIN_SPEED, int32_t CAMERA_PORT, float distInches, float speed, Goal goal,
  float rampUpFrames, float slowDownInches, float endSlowInches, bool stopAfter, float timeout) {

  Trapezoid trapDist(distInches, speed, MIN_SPEED, rampUpFrames, slowDownInches, endSlowInches);
  PID pidTurn(K_P, 0, 0);

  vision camera(CAMERA_PORT, goal.bright, goal.sig);

  int startTime = vex::timer::system();
  resetEncoderDistance();

  // forward until the maximum distance is hit, the timeout is reached, or limitSwitch is turned on
  while (!trapDist.isCompleted() && !isTimeout(startTime, timeout)) {

    camera.takeSnapshot(goal.sig);
    
    float correction = camera.largestObject.exists ? pidTurn.tick((VISION_CENTER_X-camera.largestObject.centerX) / VISION_CENTER_X) : 0;
    float distDegrees = fmin(getLeftEncoderDistance(), getRightEncoderDistance()); // take smaller of two distances because arcs
    float speed = trapDist.tick(distDegrees);

    setLeftVelocity(forward, speed - correction);
    setRightVelocity(forward, speed + correction);

    wait(20, msec);
  }
  if (stopAfter) {
    stopLeft();
    stopRight();
  }
}

// Align to the goal of specified color with PID
void BaseRobot::goAlignVision_Abstract(float K_P, float K_I, float K_D, float TOLERANCE, float REPEATED, float MINIMUM, int32_t CAMERA_PORT, 
    Goal goal, float timeout, bool stopAfter) {

  vision camera(CAMERA_PORT, goal.bright, goal.sig);

  int startTime = vex::timer::system();
  float speed = 0;

  PID vTurnPID(K_P, K_I, K_D, TOLERANCE, REPEATED, MINIMUM);

  while (!vTurnPID.isCompleted() && !isTimeout(startTime, timeout)) {

    camera.takeSnapshot(goal.sig);

    if (camera.largestObject.exists) speed = vTurnPID.tick((VISION_CENTER_X-camera.largestObject.centerX) / VISION_CENTER_X);

    setLeftVelocity(reverse, speed);
    setRightVelocity(forward, speed);

    wait(20, msec);
  }

  if (stopAfter) {
    stopLeft();
    stopRight();
  }
}

void BaseRobot::basicDriveTeleop() {

  float drive = buttons.axis(BTN::LEFT_VERTICAL);
  float turn = buttons.axis(BTN::RIGHT_HORIZONTAL);
  float max = std::max(1.0, std::max(fabs(drive+turn), fabs(drive-turn)));
  setLeftVelocity(forward,100 * (drive+turn)/max);
  setRightVelocity(forward,100 * (drive-turn)/max);
  
}