#include "vex.h"

class GenericRobot {

public:

    GenericRobot();

    void setVelocity(float leftPercent, float rightPercent);

protected:

    virtual vex::motor_group initLeftMotors() = 0;
    virtual vex::motor_group initRightMotors() = 0;

    vex::motor_group _leftMotors;
    vex::motor_group _rightMotors;

};