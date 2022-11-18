#include "PathFollowingAuton.h"
#include "Application/AutonomousUtility/DriveFunctions.h"
#include "Algorithms/SingleBoundedPID.h"

void PathFollowingAuton::runPreAutonomous() {
    // TODO: write preautonomous code here
}

void PathFollowingAuton::runAutonomous() {
    // TODO: write autonomous code here
    //goTurnU(robot, 1, SingleBoundedPID(PIDParameters(1,1,1)));
}