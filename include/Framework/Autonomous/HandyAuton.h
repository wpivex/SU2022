#pragma once

#include "Auton.h"
#include "Algorithms/EndablePID.h"


// A "handy" auton class injected with useful utility autonomous functions
class HandyAuton : public Auton {

    using Auton::Auton;

public:

    // Go forwards some distance while maintaining heading
    void goForwardU(float distance, float maintainedHeading, EndablePID&& pidSpeed, EndablePID&& pidAngle);

    // Turn to some given heading
    void goTurnU(float absoluteHeading, EndablePID&& pidAngle);

    // Go to some x/y position by driving forwards or backwards
    void goToX(float xcoord, float maintainedHeading, EndablePID&& pidSpeed);
    void goToY(float ycoord, float maintainedHeading, EndablePID&& pidSpeed);

    // go to (x,y)
    void goToPoint(float xcoord, float ycoord, EndablePID&& pidSpeed, EndablePID&& pidAngle);

};