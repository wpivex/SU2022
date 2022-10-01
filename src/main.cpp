
#include "Robots/TestRobot.h"
#include "constants.h"


TestRobot robot;


int runAutonomous() { robot.runAutonomous(); return 0;}
void autonomousTask() { vex::task auton(runAutonomous);}

int runDriver() { robot.runDriver(); return 0;}
void driverTask() { vex::task driver(runDriver); }


void setupProgram() {

    


}

int main() {

    setupProgram();

    // Stop only the competition tasks between modes, ie do not stop odometry
    Competition.bStopTasksBetweenModes = true;

    Competition.autonomous(autonomousTask);
    Competition.drivercontrol(driverTask);

    robot.runPreAutonomous();

    while (true) {
        vex::wait(100, vex::msec);
    }
}

