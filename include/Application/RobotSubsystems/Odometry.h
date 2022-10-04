#pragma once

#include "Framework/RobotSubsystems/Localizer.h"

typedef struct Encoder {
    float x, y; // (x,y) in inches, relative to center of rotation (0,0)
} Encoder;


class Odometry : public Localizable {

public:

    Odometry(Encoder leftEncoder, Encoder rightEncoder, Encoder backEncoder):
        left(leftEncoder),
        right(rightEncoder),
        back(backEncoder)
    {}

    void calculatePosition();

    float getX() override {return x;}
    float getY() override {return y;}
    float getHeading() override {return heading;}

private:
    Encoder left, right, back;
    float x, y, heading;
    
};