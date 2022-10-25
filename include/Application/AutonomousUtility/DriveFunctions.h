#pragma once

#include "Algorithms/EndablePID.h"
#include "Framework/RobotSubsystems/Robot.h"

// Go forwards some distance while maintaining heading
void goForwardU(Robot& robot, float distance, float maintainedHeading, EndablePID&& pidSpeed, EndablePID&& pidAngle);

// Turn to some given heading
void goTurnU(Robot& robot, float absoluteHeading, EndablePID&& pidAngle);

// Go to some x position by driving forwards or backwards
void goToX(Robot& robot, float xcoord, float maintainedHeading, EndablePID&& pidSpeed);

// Go to some y position by driving forwards or backwards
void goToY(Robot& robot, float ycoord, float maintainedHeading, EndablePID&& pidSpeed);

// go to (x,y)
void goToPoint(Robot& robot, float xcoord, float ycoord, EndablePID&& pidSpeed, EndablePID&& pidAngle);