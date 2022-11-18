#pragma once

#include "BasicDriver.h"
#include <iostream>
#include "Utility/Logging.h"

class TankDriver : public BasicDriver {

    using BasicDriver::BasicDriver;

protected:

    void handleDrivetrain() override {
        
        float left = buttons.axis(AXIS::LEFT_VERTICAL);
        float right = buttons.axis(AXIS::RIGHT_VERTICAL);
        log("%f\n%f", left, right);
        robot.drive->setDriveVelocity(left, right);
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