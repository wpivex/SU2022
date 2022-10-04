#pragma once

#include "vex.h"

class Driveable {

public:

    virtual void setDriveVelocity(float left, float right) = 0;
    virtual void setBrakeType(vex::brakeType brakeType) = 0;
    virtual void resetPosition() = 0;
    virtual float getLeftPosition() = 0;
    virtual float getRightPosition() = 0;
    virtual float getPosition() {
        return (getLeftPosition() + getRightPosition()) / 2.0;
    }
};