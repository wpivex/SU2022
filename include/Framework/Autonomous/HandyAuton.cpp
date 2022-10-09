#include "HandyAuton.h"

// Go forwards some distance while maintaining heading
void HandyAuton::goForwardU(float distance, float maintainedHeading, EndablePID&& pidSpeed, EndablePID&& pidAngle) {
    // TODO
}

// Turn to some given heading
void HandyAuton::goTurnU(float absoluteHeading, EndablePID&& pidAngle) {
    // TODO
}

// Go to some x position by driving forwards or backwards
void HandyAuton::goToX(float xcoord, float maintainedHeading, EndablePID&& pidSpeed) {
    // TODO
}

// Go to some y position by driving forwards or backwards
void HandyAuton::goToY(float ycoord, float maintainedHeading, EndablePID&& pidSpeed) {
    // TODO
}

// go to (x,y)
void HandyAuton::goToPoint(float xcoord, float ycoord, EndablePID&& pidSpeed, EndablePID&& pidAngle) {
    // TODO
}