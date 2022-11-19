#include "DifferentialDrive.h"
#include <iostream>
#include "Utility/Logging.h"

using namespace vex;

// Domain -1 to 1
void DifferentialDrive::setDriveVelocity(float left, float right) {
    leftMotors.setVelocity(left);
    rightMotors.setVelocity(right);
}

void DifferentialDrive::setBrakeType(brakeType type) {
    leftMotors.setBrakeType(type);
    rightMotors.setBrakeType(type);
}

void DifferentialDrive::resetPosition() {
    leftMotors.resetPosition();
    rightMotors.resetPosition();
}

// Position in rotations
float DifferentialDrive::getLeftPosition() {
    return leftMotors.getPosition(rev);
}

float DifferentialDrive::getRightPosition() {
    return rightMotors.getPosition(rev);
}