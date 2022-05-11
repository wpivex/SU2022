#include "HoloRobot.h"

/*
A subclass of BaseBot that provides an interface for holonmic drive. Features independent and concurrent control of translation and rotation.
This class contains calls to abstract motor spin methods. They must be implemented corresponding to the drivetrain of the robt. */

/*
relHeading is strafe direction relative to robot heading
rotationAmt bounded [-1,1], where -1 means max counterclockwise, 0 is no spin, and 1 is max clockwise
speedScalar bounded (0, 1], scales down the speed of all the motors but keeping ratio between motors
Example: move(0, 0.3) would cause the robot to spin in some circle with the robot's heading always tangent to the circle. */
void HoloRobot::move(float relHeading, float rotationAmt, float speedScalar) {

}

// Wrapper for move(...), takes in absolute heading instead
// Eample: move(0, 0.3) would cause robot to continouously move forward and spin at the same time
void HoloRobot::moveU(float absHeading, float rotationAmt, float speedScalar) {

}

// Maps full left joystick to translation and horizontal right joystick to rotation, calls moveU
void HoloRobot::holoDriveTeleop() {

}