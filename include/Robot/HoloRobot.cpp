#include "HoloRobot.h"

/*
A subclass of BaseBot that provides an interface for holonomic drive. Features independent and concurrent control of translation and rotation.
This class contains calls to abstract motor spin methods. They must be implemented corresponding to the drivetrain of the robt. */

/*
move(...) is nonblocking, and should be called each tick
relHeading, bounded [0,365), is strafe direction relative to robot heading
rotationAmt bounded [-1,1], where -1 means max counterclockwise, 0 is no spin, and 1 is max clockwise
speed bounded (0, 100], scales down the speed of all the motors but keeping ratio between motors
Example: move(0, 0.3) would cause the robot to spin in some circle with the robot's heading always tangent to the circle. */
void HoloRobot::move(float relHeading, float rotationAmt, float speed) {

  relHeading = fmod(360+relHeading, 360); // make sure it's bounded [0,360)
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

  float rotationWeight = fabs(rotationAmt); // how much weight rotation value has
  float translationWeight = 1 - rotationWeight; // how much weight translation value has

  // weighted average between translation and rotation
  float speedFL = (translationWeight * fl + rotationAmt * rotationWeight) * speed;
  float speedFR = (translationWeight * fr + rotationAmt * rotationWeight) * speed;
  float speedBL = (translationWeight * bl + rotationAmt * rotationWeight) * speed;
  float speedBR = (translationWeight * br + rotationAmt * rotationWeight) * speed;

  spinFL(speedFL);
  spinFR(speedFR);
  spinBL(speedBL);
  spinBR(speedBR);
}

/*
Wrapper for move(...), takes in absolute heading instead
moveU(...) is nonblocking, and should be called each tick
Eample: move(0, 0.3) would cause robot to continouously move forward and spin at the same time */
void HoloRobot::moveU(float absHeading, float rotationAmt, float speed) {
  float relHeading = fmod(360 + absHeading - getAngle(), 360);
  move(relHeading, rotationAmt, speed);
}

// Maps full left joystick to translation and horizontal right joystick to rotation, calls moveU
void HoloRobot::holoDriveTeleop() {

}