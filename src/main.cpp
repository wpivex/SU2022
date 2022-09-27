
#include "Robots/TestRobot.h"
#include "PathFollowing/TestController.h"
#include "constants.h"

#include <memory>

std::unique_ptr<GenericRobot> robot;


int runAutonomous() { robot->runAutonomous(); return 0;}
void autonomousTask() { vex::task auton(runAutonomous);}

int runDriver() { robot->runDriver(); return 0;}
void driverTask() { vex::task driver(runDriver); }


void setupProgram() {

    std::shared_ptr<ControllerInterface> controller(new TestController());
    robot = std::unique_ptr<GenericRobot>(new TestRobot(controller));

}

int main() {

    setupProgram();

    // Stop only the competition tasks between modes, ie do not stop odometry
    Competition.bStopTasksBetweenModes = true;

    Competition.autonomous(autonomousTask);
    Competition.drivercontrol(driverTask);

    robot->runPreAutonomous();

    while (true) {
        vex::wait(100, vex::msec);
    }
}

