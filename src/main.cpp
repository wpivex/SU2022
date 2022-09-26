#include "GenericAutonomous.h"
#include "GenericDriver.h"
#include "TestRobot.h"
#include "constants.h"

GenericRobot* robot = new TestRobot();

GenericAutonomous* auton = new GenericAutonomous(robot);
GenericDriver* driver = new GenericDriver(robot);

int runAutonomous() { auton->run(); }
void autonomousTask() { vex::task auton(runAutonomous); }

int runDriver() { driver->run(); }
void driverTask() { vex::task driver(runDriver); }


int main() {

    Competition.bStopAllTasksBetweenModes = true;

    Competition.autonomous(autonomousTask);
    Competition.drivercontrol(driverTask);

    auton->preAuton();

    while (true) {
        vex::wait(100, vex::msec);
    }
}
