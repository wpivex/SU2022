#pragma once

#include "BasicDriver.h"

class TankDriver : public BasicDriver {

    using BasicDriver::BasicDriver;

protected:

    void handleDrivetrain() override {

        robot.drive->setDriveVelocity(
            buttons.axis(CONTROLLER_ENUM::LEFT_VERTICAL),
            buttons.axis(CONTROLLER_ENUM::RIGHT_HORIZONTAL)
        );
    }
};

class ArcadeDriver : public BasicDriver {

    using BasicDriver::BasicDriver;

protected:

    void handleDrivetrain() override {
        
        float drive = buttons.axis(CONTROLLER_ENUM::LEFT_VERTICAL);
        float turn = buttons.axis(CONTROLLER_ENUM::RIGHT_HORIZONTAL);
        float max = std::max(1.0, std::max(fabs(drive+turn), fabs(drive-turn)));

        robot.drive->setDriveVelocity(
            buttons.axis( (drive + turn) / max ),
            buttons.axis( (drive - turn) / max )
        );
    }
};