#pragma once

#include "../RobotSubsystems/Robot.h"

class Auton {

public:

    Auton(Robot& _robot):
        robot(_robot)
    {}

    virtual void runPreAutonomous() {}
    virtual void runAutonomous() {}

protected:
    Robot& robot;
};