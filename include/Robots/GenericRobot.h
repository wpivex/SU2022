#pragma once

#include "vex.h"
#include "Localization/LocalizerInterface.h"
#include "Buttons.h"
#include <memory>

class GenericRobot {

public:

    GenericRobot() {
        _localizer = setupLocalizer();
        _leftMotors = setupLeftMotors();
        _rightMotors = setupRightMotors();
    }

    // Functions that must be implemented by leaf concrete class to define robot parameters
    virtual std::shared_ptr<LocalizerInterface> setupLocalizer() = 0;
    virtual vex::motor_group setupLeftMotors() = 0;
    virtual vex::motor_group setupRightMotors() = 0;

    void setVelocity(float leftPercent, float rightPercent);
    
    // Runs this during driver period. Functions calls handleDrivetrain() and handleSecondrayActions()
    void runDriver() {};

    // Functions to be implemented that handle controller input for one tick in driver control
    virtual void handleDrivetrain() {};
    virtual void handleSecondaryActions() {};

    // Functions to be implemented that handle autonomous logic
    virtual void runPreAutonomous() {};
    virtual void runAutonomous() {};



protected:

    vex::motor_group _leftMotors;
    vex::motor_group _rightMotors;

    std::shared_ptr<LocalizerInterface> _localizer;

    Buttons buttons;

};