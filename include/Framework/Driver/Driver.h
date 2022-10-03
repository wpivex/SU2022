#pragma once

#include "../RobotSubsystems/Robot.h"

class Driver {

public:

    Driver(Robot& _robot):
        robot(_robot)
    {}

    virtual void runDriver() = 0;

protected:
    Robot& robot;

};