#pragma once

#include "vex.h"
#include "Localization/LocalizerInterface.h"
#include "Buttons.h"

class GenericRobot {

public:


    void init() {
        _leftMotors = initLeftMotors();
        _rightMotors = initRightMotors();
        _localizer = initLocalizer();
    }

    void setDriveVelocity(float leftPercent, float rightPercent);

    virtual void runPreAutonomous() {}
    virtual void runAutonomous() {}
    virtual void runDriver();

    virtual ~GenericRobot() {
        delete _localizer;
    }

protected:

    virtual vex::motor_group initLeftMotors() = 0;
    virtual vex::motor_group initRightMotors() = 0;
    virtual LocalizerInterface* initLocalizer() = 0;


    virtual void handleDrivetrain() {}
    virtual void handleSecondaryActions() {}

    vex::motor_group _leftMotors;
    vex::motor_group _rightMotors;
    LocalizerInterface* _localizer;

    Buttons buttons;

};