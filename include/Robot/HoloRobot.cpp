#include "HoloRobot.h"

/*
A subclass of BaseBot that provides an interface for holonomic drive. Features independent and concurrent control of translation and rotation.
This class contains calls to abstract motor spin methods. They must be implemented corresponding to the drivetrain of the robt. */

/*
move(...) is nonblocking, and should be called each tick
relHeading, bounded [0,365), is strafe direction relative to robot heading
translationSpeed bounded (0, 100], speed for translation
rotationAmt bounded [-100,100], where -100 means max counterclockwise, 0 is no spin, and 100 is max clockwise
Example: move(0, 0.3) would cause the robot to spin in some circle with the robot's heading always tangent to the circle. */
void HoloRobot::move(float relHeading, float translationSpeed, float rotationSpeed) {

  float fl, fr, bl, br; // speeds (bounded [-1, 1]) of four motors
  
  // Calculate translation: refer to selfie https://discord.com/channels/863826887067435029/869718734409957387/973784859921240064
  if (relHeading < 90) fl = 1;
  else if (relHeading < 180) fl = (135.0 - relHeading) / 45.0; // linearly interpolate between 90 -> 1, 180 -> -1
  else if (relHeading < 270) fl = -1;
  else fl = (relHeading - 315.0) / 45.0; // linearly interpolate between 270 -> -1, 0 -> 1

  br = fl; // in translation, front left and back right motors spin the same speed

  if (relHeading < 90) fr = (45.0 - relHeading) / 45.0; // 0 -> 1, 90 -> -1
  else if (relHeading < 180) fr = -1;
  else if (relHeading < 270) fr = (relHeading - 225.0) / 45.0; // 180 -> -1, 270 -> 1
  else fr = 1;

  bl = fr; // in translation, front left and back right motors spin the same speed

  // bound speeds so that rotationSpeed + translationSpeed < 100
  float sumSpeed = fabs(rotationSpeed) + fabs(translationSpeed);
  if (sumSpeed > 100) {
    rotationSpeed = 100.0 * (rotationSpeed / sumSpeed);
    translationSpeed = 100.0 * (translationSpeed / sumSpeed);
  }

  // weighted average between translation and rotation
  float speedFL = (translationSpeed * fl + rotationSpeed);
  float speedFR = (translationSpeed * fr - rotationSpeed);
  float speedBL = (translationSpeed * bl + rotationSpeed);
  float speedBR = (translationSpeed * br - rotationSpeed);

  spinFL(speedFL);
  spinFR(speedFR);
  spinBL(speedBL);
  spinBR(speedBR);
}

/*
Wrapper for move(...), takes in absolute heading instead
moveU(...) is nonblocking, and should be called each tick
Eample: move(0, 0.3) would cause robot to continouously move forward and spin at the same time */
void HoloRobot::moveU(float absHeading, float translationSpeed, float rotationSpeed) {
  float relHeading = fmod(360 + absHeading - getAngle(), 360);
  move(relHeading, translationSpeed, rotationSpeed);
}

// Maps full left joystick to translation and horizontal right joystick to rotation, calls moveU
// slightly inflexible implementation, but set to left joystick = translation, right joystick = rotation
void HoloRobot::holoDriveTeleop() {

  float x = buttons.axis(BTN::LEFT_HORIZONTAL);
  float y = buttons.axis(BTN::LEFT_VERTICAL);
  float rot = buttons.axis(BTN::RIGHT_HORIZONTAL);

  // precondition: dist(x,y) <= 1
  float speed = fmin(100, distanceFormula(x, y) * 100.0);

  if (speed == 0) stopDrive();
  else {
    float angle = 90 - (atan2(y, x) * 180.0 / M_PI);
    angle = fmod(360, angle + 360); // bound 0-360
    moveU(angle, speed, rot * 100.0);
  }



}