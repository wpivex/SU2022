#include "DriveFunctions.h"

/*
These implementations assume the robot have localization capability and can make use of it, for simplicity's sake
*/

// Go forwards some distance while maintaining heading
void goForwardU(Robot& robot, float distance, float maintainedHeading, EndablePID& pidSpeed, EndablePID& pidAngle) {
    // TODO
}

// Turn to some given heading
void goTurnU(Robot& robot, float absoluteHeading, EndablePID& pidAngle) {
    // TODO
}

// Go to some x position by driving forwards or backwards
void goToX(Robot& robot, float xcoord, float maintainedHeading, EndablePID& pidSpeed) {
    // TODO
}

// Go to some y position by driving forwards or backwards
void goToY(Robot& robot, float ycoord, float maintainedHeading, EndablePID& pidSpeed) {
    // TODO
}

// go to (x,y)
void goToPoint(Robot& robot, float xcoord, float ycoord, EndablePID& pidSpeed, EndablePID& pidAngle) {
    // TODO
}