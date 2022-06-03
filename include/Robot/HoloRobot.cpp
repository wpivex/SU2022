#include "HoloRobot.h"

/*
A subclass of BaseBot that provides an interface for holonomic drive. Features independent and concurrent control of translation and rotation.
This class contains calls to abstract motor spin methods. They must be implemented corresponding to the drivetrain of the robt. */
HoloRobot::HoloRobot(int32_t gyroPort, float encoderDiameter, triport::port left, triport::port right, triport::port back): 
OdomRobot(gyroPort, encoderDiameter,
  left, right,  back) {
  
}

// move(...) is nonblocking, and should be called each tick
// drive, strafe, and turn have domain [-100, 100]
void HoloRobot::moveWithComponents(float drive, float strafe, float turn) {

  if (drive == 0 && strafe == 0 && turn == 0) {
    stopDrive();
    return;
  }

  float maxSpeed = fmin(100, distanceFormula(drive,strafe) + fabs(turn));

  float leftFront = drive + strafe + turn;
  float leftBack = drive - strafe + turn;
  float rightFront = drive - strafe - turn;
  float rightBack = drive + strafe - turn;
  float max = fmax(fmax(fabs(leftFront),fabs(leftBack)),fmax(fabs(rightFront),fabs(rightBack)));
  
  // normalize and rescale to maxSpeed
  float scalar = maxSpeed / max;
  leftFront *= scalar;
  rightFront *= scalar;
  leftBack *= scalar;
  rightBack *= scalar;

  //log("LF: %f\nRF: %f\nLB: %f\nRB: %f", leftFront, rightFront, leftBack, rightBack);

  setDrivePower(leftFront * scalar, rightFront * scalar, leftBack * scalar, rightBack * scalar);
}

/*
move(...) is nonblocking, takes in absolute heading
absHeading, bounded [0,365), is strafe direction
translationSpeed bounded (0, 100], speed for translations
turnSpeed bounded [-100,100], where -100 means max counterclockwise, 0 is no spin, and 100 is max clockwise
Eample: move(0, 100, 100) would cause robot to continouously move forward and spin at the same time */
void HoloRobot::moveHeadingU(float absHeading, float translationSpeed, float turnSpeed) {
  log("Heading: %f\nTranslation: %f", getAngle(), absHeading * 180 / M_PI);
  float headingRad = getAngle() * M_PI / 180;
  float relHeading = absHeading - headingRad;
  float x = cos(relHeading) * translationSpeed;
  float y = sin(relHeading) * translationSpeed;
  moveWithComponents(x, y, turnSpeed);
}

// Maps full left joystick to translation and horizontal right joystick to rotation, calls moveU
// slightly inflexible implementation, but set to left joystick = translation, right joystick = rotation
void HoloRobot::holoDriveTeleop() {

  float drive = buttons.axis(BTN::LEFT_VERTICAL);
  float strafe = buttons.axis(BTN::LEFT_HORIZONTAL);
  float translation = distanceFormula(drive, strafe) * 100;
  drive *= 100;
  strafe *= 100;

  // Deadzone only applies if close to 0 on both axis
  if (distanceFormula(drive, strafe) < 5) {
    drive = 0;
    strafe = 0;
  }
  float turn = pow(buttons.axis(BTN::RIGHT_HORIZONTAL), 3) * 100;

  moveHeadingU(M_PI/2 - atan2(drive, strafe), translation, turn);
}