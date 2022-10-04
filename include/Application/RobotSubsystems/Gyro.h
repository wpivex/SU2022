#pragma once

#include "Framework/RobotSubsystems/Localizer.h"
#include "vex.h"

/*
Gyro sensor to give heading. No x and y data.
*/
class Gyro : public Localizable {

public:

    Gyro(int32_t port):
        gyro(port)
    {}

    void calculatePosition();

    // no x and y support
    float getX() override {return -1;}
    float getY() override {return -1;}

    // poll from gyro
    float getHeading() override {return gyro.heading();}

private:
    vex::inertial gyro;
};