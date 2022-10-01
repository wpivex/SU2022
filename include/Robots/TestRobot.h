#pragma once

#include "GenericRobot.h"
#include "DriverMixins.h"
#include "Localization/TestLocalizer.h"

class TestRobot : public GenericRobot, TankDriverMixin {

public:

    TestRobot() {

    }

    vex::motor_group initLeftMotors() {
        vex::motor m1(vex::PORT1);
        return vex::motor_group(m1);

    }
    vex::motor_group initRightMotors() {
        vex::motor m2(vex::PORT1);
        return vex::motor_group(m2);

    }
    LocalizerInterface* initLocalizer() {
        return new TestLocalizer();
    }

};