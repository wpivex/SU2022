#pragma once

#include "GenericRobot.h"

class TankDriverMixin : public virtual GenericRobot {

protected:

    void handleDrivetrain() override {
        // TODO
        setDriveVelocity(0,0);
    }
};

class ArcadeDriverMixin : public virtual GenericRobot {

protected:

    void handleDrivetrain() override {
        // TODO
        setDriveVelocity(0,0);
    }
};