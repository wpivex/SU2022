
#include "Autonomous/Auton.h"
#include "Driver/BasicDriver.h"
#include "Driver/DriverMixins.h"
#include "RobotCreator.h"
#include "constants.h"


Robot robot = getTestRobot();
Auton* auton = new Auton(robot);
Driver* driver = new TankDriver(robot);


int runAutonomous() { auton->runAutonomous(); return 0;}
void autonomousTask() { vex::task auton(runAutonomous);}

int runDriver() { driver->runDriver(); return 0;}
void driverTask() { vex::task driver(runDriver); }

int main() {

    // Stop only the competition tasks between modes, ie do not stop odometry
    Competition.bStopTasksBetweenModes = true;

    Competition.autonomous(autonomousTask);
    Competition.drivercontrol(driverTask);

    auton->runPreAutonomous();

    while (true) {
        vex::wait(100, vex::msec);
    }
}

