#pragma once

#include "Buttons.h"
#include "../RobotSubsystems/Robot.h"

class BasicDriver {

public:

    virtual void runDriver();
        
protected:
    virtual void handleDrivetrain() {}
    virtual void handleSecondaryActions() {}

    virtual void initDriver() {}

    Buttons buttons;
    Robot& robot;
};