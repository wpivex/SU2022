#include "BasicDriver.h"

void BasicDriver::runDriver() {
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