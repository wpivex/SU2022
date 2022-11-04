#include "BasicDriver.h"
#include "vex.h"
#include "Utility/VexUtility.h"
#include <functional>
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

    auto flywheelTask = [&] { robot.flywheel->maintainVelocityTask(); };
    if (!robot.flywheel) launch_task(flywheelTask);

    auto odomTask = [&] { robot.localizer->updatePositionTask(); };
    if (!robot.localizer) launch_task(odomTask);

}