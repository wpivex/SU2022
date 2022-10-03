#pragma once

#include "Framework/RobotSubsystems/Localizer.h"

typedef struct Encoder {
    float x, y; bool isHorizontal; // (x,y) in inches, relative to center of rotation (0,0)
} Encoder;

class Odometry : public Localizable {

public:

    Odometry(Encoder encoder1, Encoder encoder2, Encoder encoder3):
        ec1(encoder1),
        ec2(encoder2),
        ec3(encoder3)
    {}

    float getFieldX() {return 0;}
    float getFieldY() {return 0;}
    float getFieldHeading() {return 0;}

    Encoder ec1, ec2, ec3;
};