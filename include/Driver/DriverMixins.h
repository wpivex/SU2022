#pragma once

#include "BasicDriver.h"

class TankDriver : public BasicDriver {

    using BasicDriver::BasicDriver;

protected:

    void handleDrivetrain() override {
        // TODO
        robot.drive->setDriveVelocity(0,0);
    }
};

class ArcadeDriver : public BasicDriver {

    using BasicDriver::BasicDriver;

protected:

    void handleDrivetrain() override {
        // TODO
        robot.drive->setDriveVelocity(0,0);
    }
};