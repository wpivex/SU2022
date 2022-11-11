#include "DifferentialDrive.h"
#include <iostream>

using namespace vex;

// Domain -1 to 1
void DifferentialDrive::setDriveVelocity(float left, float right) {
    std::cout << "diff" << std::endl;
    wait(0.1, vex::sec);
    leftMotors.spin(forward, left * 12, volt);
    rightMotors.spin(forward, right * 12, volt);
}

void DifferentialDrive::setBrakeType(brakeType type) {
    leftMotors.setStopping(type);
    rightMotors.setStopping(type);
}

void DifferentialDrive::resetPosition() {
    leftMotors.resetPosition();
    rightMotors.resetPosition();
}

// Position in rotations
float DifferentialDrive::getLeftPosition() {
    return leftMotors.position(rev);
}

float DifferentialDrive::getRightPosition() {
    return rightMotors.position(rev);
}