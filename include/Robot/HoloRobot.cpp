#include "HoloRobot.h"

/*
A subclass of BaseBot that provides an interface for holonomic drive. Features independent and concurrent control of translation and rotation.
This class contains calls to abstract motor spin methods. They must be implemented corresponding to the drivetrain of the robt. */
HoloRobot::HoloRobot(int32_t gyroPort, float encoderDiameter, float wheelDist, triport::port left, triport::port right, triport::port back): 
OdomRobot(gyroPort, encoderDiameter, wheelDist,
  left, right,  back) {
  
}

// From absolute field coordinates, get coordinates relative to robot (with respect to robot heading)
Point HoloRobot::fieldToRelCoords(float absX, int absY) {

  // Convert field coords to relative coords
    float dx = absX - getX();
    float dy = absY - getY();
    float translationAngle = M_PI/2 - atan2(dy, dx);
    float dAngle = translationAngle - getAngle(true);
    return Point(cos(dAngle), sin(dAngle));
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

  setDrivePower(leftFront, rightFront, leftBack, rightBack);
}

/*
move(...) is nonblocking, takes in absolute heading
absHeading, bounded [0,2pi), is strafe direction
translationSpeed bounded (0, 100], speed for translations
turnSpeed bounded [-100,100], where -100 means max counterclockwise, 0 is no spin, and 100 is max clockwise
Eample: move(0, 100, 100) would cause robot to continouously move forward and spin at the same time */
void HoloRobot::moveHeadingU(float absHeading, float translationSpeed, float turnSpeed, bool isFieldCentric) {
  //log("Heading: %f\nTranslation: %f", getAngle(), absHeading * 180 / M_PI);
  float relHeading = absHeading - (isFieldCentric ? getAngle(true) : 0);
  float x = cos(relHeading) * translationSpeed;
  float y = sin(relHeading) * translationSpeed;
  moveWithComponents(x, y, turnSpeed);
}

// https://www.desmos.com/calculator/7qnjjtyrx2
const float JOYSTICK_SNAP = 0.13;
float joystickFunction(float ang, int t) {
  
  const float p2 = M_PI/2;
  return (ang - JOYSTICK_SNAP - t * p2) * (p2 / (p2 - 2*JOYSTICK_SNAP)) + p2 * t;
}

// Maps full left joystick to translation and horizontal right joystick to rotation, calls moveU
// slightly inflexible implementation, but set to left joystick = translation, right joystick = rotation
void HoloRobot::holoDriveTeleop() {

  if (buttons.pressed(BTN::L1)) {
    isFieldCentric = !isFieldCentric;
    logController(isFieldCentric ? "Field Centric" : "Robot Centric");
  }

  float drive = buttons.axis(BTN::LEFT_VERTICAL) * 100;
  float strafe = buttons.axis(BTN::LEFT_HORIZONTAL) * 100;
  float translation = distanceFormula(drive, strafe);

  // Deadzone only applies if close to 0 on both axis
  if (distanceFormula(drive, strafe) < 5) {
    drive = 0;
    strafe = 0;
  }

  float KP = 2;
  float turnControl = buttons.axis(BTN::RIGHT_HORIZONTAL) * 100;
  if (fabs(turnControl) < 5) turnControl = 0;

  float turn;
  if (turnControl == 0) { // Hold theta if not rotating
    if (timer::system() - time < 1000) targetHeading = getAngle(); // grace period to shave off momentum before locking in heading
    else turn = getAngleDiff(targetHeading, getAngle()) * KP;
  } else {
    turn = turnControl;
    time = timer::system();
  }

  float ang = M_PI/2 - atan2(drive, strafe); // ang bounded [0, 2pi), 0 at north, positive clockwise
  if (ang < 0) ang += 2*M_PI;

  // "Snap" joystick to cardinal directions if close, and linearly interpolate otherwise for a mapping that is continuous
  float aang; // adjusted angle
  if (ang < JOYSTICK_SNAP) aang = 0;
  else if (ang < M_PI/2 - JOYSTICK_SNAP) aang = joystickFunction(ang, 0);
  else if (ang < M_PI/2 + JOYSTICK_SNAP) aang = M_PI/2;
  else if (ang < M_PI - JOYSTICK_SNAP) aang = joystickFunction(ang, 1);
  else if (ang < M_PI + JOYSTICK_SNAP) aang = M_PI;
  else if (ang < 3*M_PI/2 - JOYSTICK_SNAP) aang = joystickFunction(ang, 2);
  else if (ang < 3*M_PI/2 + JOYSTICK_SNAP) aang = 3*M_PI/2;
  else if (ang < 2*M_PI - JOYSTICK_SNAP) aang = joystickFunction(ang, 3);
  else aang = 0;
  log("Raw: %.1f\nAdjusted: %.1f", ang * 180 / M_PI, aang * 180 / M_PI);
  moveHeadingU(aang, translation, turn, isFieldCentric);
}

void HoloRobot::goToPoint(float x, float y, float theta) {

  PID pidX(1, 0, 0, 0.5, 1);
  PID pidY(1, 0, 0, 0.5, 1);
  PID pidT(1, 0, 0, 0.5, 1);

  while (!pidX.isCompleted() || !pidY.isCompleted() || !pidT.isCompleted()) {

    Point p = fieldToRelCoords(x, y);

    moveWithComponents(pidY.tick(p.y), pidX.tick(p.x), pidT.tick(theta - getAngle(true))); 

  }

  stopDrive();

}