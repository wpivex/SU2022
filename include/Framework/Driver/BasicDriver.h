#pragma once

#include "Buttons.h"
#include "../RobotSubsystems/Robot.h"

class BasicDriver {

public:

    BasicDriver(Robot& robotReference): robot(robotReference) {}

    virtual void runDriver();
    void callsFlywheelTask();
        
protected:
    virtual void handleDrivetrain() {}
    virtual void handleSecondaryActions() {}

    virtual void initDriver();
    

    Buttons buttons;
    Robot& robot;
};