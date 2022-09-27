#pragma once

#include "DriverMixins.h"
#include "PathFollowerMixin.h"
#include "PathFollowing/ControllerInterface.h"
#include "Localization/TestLocalizer.h"

class TestRobot : public TankDriverMixin, public PathFollowerMixin {

public:

    TestRobot(std::shared_ptr<ControllerInterface> controller):
        PathFollowerMixin(controller)
    {

    }

    // Define the parameters of TestRobot through implementing setup functions
    std::shared_ptr<LocalizerInterface> setupLocalizer() override {
        return std::shared_ptr<LocalizerInterface>(new TestLocalizer());
    }
    vex::motor_group setupLeftMotors() override {
        vex::motor m1(vex::PORT1);
        return vex::motor_group(m1);
    };
    vex::motor_group setupRightMotors() override {
        vex::motor m1(vex::PORT1);
        return vex::motor_group(m1);
    }




};