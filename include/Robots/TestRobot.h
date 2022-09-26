#include "GenericRobot.h"

class TestRobot : public GenericRobot {

protected:

    vex::motor_group initLeftMotors() override {
        vex::motor a(vex::PORT1);
        return vex::motor_group(a);
    }

    vex::motor_group initRightMotors() override {
        vex::motor a(vex::PORT2);
        return vex::motor_group(a);
    }

};