#include "Buttons.h"
#include "GenericRobot.h"

class GenericDriver {

public:

    GenericDriver(GenericRobot* robot) :
    _robot(robot)
    {}

    void run() {

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

protected:

    Buttons buttons;
    GenericRobot* _robot;

    virtual void handleDrivetrain() {};
    virtual void handleSecondaryActions() {};

};