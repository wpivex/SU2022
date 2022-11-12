#include "BasicDriver.h"
#include "vex.h"
#include "Utility/VexUtility.h"
#include <functional>
#include <iostream>

BasicDriver::BasicDriver(Robot& robotReference): robot(robotReference) {

}

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

void BasicDriver::callsFlywheelTask() {
    robot.flywheel->maintainVelocityTask();
}

void BasicDriver::initDriver() {

    if (robot.flywheel) {
        auto flywheelTask = [&] { robot.flywheel->maintainVelocityTask(); };
        launch_task(flywheelTask);
    }
    std::cout << "a" << "\n";
    wait(0.1, vex::sec);

    if (robot.localizer) {
        auto odomTask = [&] { robot.localizer->updatePositionTask(); };
        launch_task(odomTask);
    }

}