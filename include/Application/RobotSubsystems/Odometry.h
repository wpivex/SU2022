#pragma once

#include "Framework/RobotSubsystems/Localizer.h"
#include "vex.h"

typedef struct Encoder {
    vex::encoder enc;
    float x, y; // (x,y) in inches, relative to center of rotation (0,0)
    float diameter;

    Encoder(vex::triport::port port, float xOffset, float yOffset, float wheelDiameter):
        enc(port),
        x(xOffset),
        y(yOffset),
        diameter(wheelDiameter)
    {
        reset();
    }

    void reset() {
        enc.resetRotation();
    }

    // get distance travelled in inches
    float get() {
        return enc.rotation(vex::rev) * diameter * M_PI;
    }    

} Encoder;


class Odometry : public Localizable {

public:

    Odometry(int32_t gyroPort, Encoder leftEncoder, Encoder rightEncoder, Encoder backEncoder):
        gyroSensor(gyroPort),
        left(leftEncoder),
        right(rightEncoder),
        back(backEncoder)
    {}

    void calculatePosition();

    float getX() override {return currX;}
    float getY() override {return currY;}
    float getHeading() override {return currHeading;}

private:
    vex::inertial gyroSensor;
    Encoder left, right, back;

    float currX, currY, currHeading;
    float prevLeft, prevRight, prevBack, prevTheta;
    
    
};