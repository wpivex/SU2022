
#include "Autonomous/Auton.h"
#include "Driver/BasicDriver.h"
#include "Driver/DriverMixins.h"
#include "RobotCreator.h"
#include "constants.h"
#include "Utility/Memory.h"


Robot robot = getTestRobot();
std::unique_ptr<Auton> auton = make_unique<Auton>(robot);
std::unique_ptr<Driver> driver = make_unique<TankDriver>(robot);


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

