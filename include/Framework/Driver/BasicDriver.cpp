#include "BasicDriver.h"

void BasicDriver::runDriver() {
    // Initialize driver class
    initDriver();

    while (true) {
        // Handle drivetrain locomotion from joysticks (tank, arcade, etc.)
        handleDrivetrain();

        // Handle other things like intaking, shooting, etc.
        handleSecondaryActions();
        
        // Update button state machine for rising and falling edges
        buttons.updateButtonState();

        // Enforce minimum polling cycle rate
        vex::wait(20, vex::msec);
    }
}

void BasicDriver::initDriver(){
    vex::task updaters = vex::task(runTasks);
}

void runTasks(){
    robot.flywheel->maintainVelocityTask();
    robot.localizer->updatePositionTask();
}