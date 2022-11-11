#pragma once

#include "BasicDriver.h"
#include <iostream>

class TankDriver : public BasicDriver {

    using BasicDriver::BasicDriver;

protected:

    void handleDrivetrain() override {
        std::cout << "f" << std::endl;
        wait(0.1, vex::sec);
        buttons.axis(AXIS::LEFT_VERTICAL);
        std::cout << "tank" << std::endl;
        wait(0.1, vex::sec);
        robot.drive->setDriveVelocity(
            buttons.axis(AXIS::LEFT_VERTICAL),
            buttons.axis(AXIS::RIGHT_HORIZONTAL)
        );
    }
};

class ArcadeDriver : public BasicDriver {

    using BasicDriver::BasicDriver;

protected:

    void handleDrivetrain() override {
        
        float drive = buttons.axis(AXIS::LEFT_VERTICAL);
        float turn = buttons.axis(AXIS::RIGHT_HORIZONTAL);
        float max = std::max(1.0, std::max(fabs(drive+turn), fabs(drive-turn)));

        robot.drive->setDriveVelocity( (drive + turn) / max, (drive - turn) / max ); 
    }
};