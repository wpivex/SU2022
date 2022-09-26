#include "GenericRobot.h"

GenericRobot::GenericRobot() {

    _leftMotors = initLeftMotors();
    _rightMotors = initRightMotors();

}

// Set velocity of left and drive motors, from -100 to 100 percent
void GenericRobot::setVelocity(float leftPercent, float rightPercent) {
    // TODO
}