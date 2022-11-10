#include "TestAuton.h"
#include "Application/AutonomousUtility/DriveFunctions.h"
#include "Algorithms/SingleBoundedPID.h"

void TestAuton::runPreAutonomous() {
    // TODO: write preautonomous code here
}

void TestAuton::runAutonomous() {
    // TODO: write autonomous code here
    //goTurnU(robot, 1, SingleBoundedPID(PIDParameters(1,1,1)));
}