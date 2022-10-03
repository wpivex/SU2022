#pragma once
#include "vex.h"

class Driveable {

public:

    virtual void setDriveVelocity(float left, float right) = 0;
};

class DifferentialDrive : public Driveable {

public:
    DifferentialDrive(vex::motor_group leftMotors, vex::motor_group rightMotors):
        left(leftMotors),
        right(rightMotors)
    {}
    
    void setDriveVelocity(float left, float right) {}

    vex::motor_group left, right;
};