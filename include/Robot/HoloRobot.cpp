#include "HoloRobot.h"

/*
A subclass of BaseBot that provides an interface for holonomic drive. Features independent and concurrent control of translation and rotation.
This class contains calls to abstract motor spin methods. They must be implemented corresponding to the drivetrain of the robt. */

// move(...) is nonblocking, and should be called each tick
// drive, strafe, and turn have domain [-100, 100]
void HoloRobot::moveWithComponents(float drive, float strafe, float turn) {

  if (drive == 0 && strafe == 0 && turn == 0) {
    stopDrive();
    return;
  }

  float maxSpeed = fmax(100, distanceFormula(drive,strafe) + fabs(turn));

  float leftFront = drive + strafe + turn;
  float leftBack = drive - strafe + turn;
  float rightFront = drive - strafe - turn;
  float rightBack = drive + strafe - turn;
  float max = fmax(fmax(fabs(leftFront),fabs(leftBack)),fmax(fabs(rightFront),fabs(rightBack)));
  
  // normalize and rescale to maxSpeed
  float scalar = maxSpeed / max;
  setDrivePower(leftFront * scalar, leftBack * scalar, rightFront * scalar, rightBack * scalar);
}

/*
move(...) is nonblocking, takes in absolute heading
absHeading, bounded [0,365), is strafe direction
translationSpeed bounded (0, 100], speed for translations
turnSpeed bounded [-100,100], where -100 means max counterclockwise, 0 is no spin, and 100 is max clockwise
Eample: move(0, 100, 100) would cause robot to continouously move forward and spin at the same time */
void HoloRobot::moveHeadingU(float absHeading, float translationSpeed, float turnSpeed) {
  float relHeading = fmod(360 + absHeading - getAngle(), 360);
  float headingRadians = relHeading * M_PI / 180.0;
  float x = cos(headingRadians) * translationSpeed;
  float y = sin(headingRadians) * translationSpeed;
  moveWithComponents(x, y, turnSpeed);
}

// Maps full left joystick to translation and horizontal right joystick to rotation, calls moveU
// slightly inflexible implementation, but set to left joystick = translation, right joystick = rotation
void HoloRobot::holoDriveTeleop() {

  float drive = buttons.axis(BTN::LEFT_VERTICAL) * 100;
  float strafe = buttons.axis(BTN::LEFT_HORIZONTAL) * 100;
  float turn = buttons.axis(BTN::RIGHT_HORIZONTAL) * 100;

  moveWithComponents(drive, strafe, turn);
}