
#include "Framework/Autonomous/Auton.h"
#include "Framework/Driver/BasicDriver.h"

#include "Application/Autonomous/TestAuton.h"
#include "Application/Driver/TestDriver.h"
#include "Application/RobotBuilder.h"

#include "Application/RobotSubsystems/TBHFlywheel.h"

#include "constants.h"
#include <iostream>
#include <memory>


Robot robot = getTestRobot();
std::unique_ptr<Auton> auton = std::make_unique<TestAuton>(robot);
std::unique_ptr<BasicDriver> driver = std::make_unique<TankDriver>(robot);


int runAutonomous() { auton->runAutonomous(); return 0;}
void autonomousTask() { vex::task auton(runAutonomous);}

int runDriver() { driver->runDriver(); return 0;}
void driverTask() { vex::task driver(runDriver); }

int main() {

    std::cout << "start" << "\n";

    // Stop only the competition tasks between modes, ie do not stop odometry
    Competition.bStopTasksBetweenModes = true;

    Competition.autonomous(autonomousTask);
    Competition.drivercontrol(driverTask);

    //auton->runPreAutonomous();

    while (true) {
        vex::wait(100, vex::msec);
    }
}

