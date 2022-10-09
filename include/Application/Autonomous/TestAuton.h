#pragma once

#include "Framework/PathFollowing/PathFollower.h"
#include "Framework/Autonomous/Auton.h"

#include "TestData1.h"
#include "../Controllers/PurePursuit.h"

class TestAuton : public Auton {

public:

    TestAuton(Robot& robot):
        Auton(robot),
        p(robot, PurePursuit(), std::move(path))
    {

    }

    void runPreAutonomous() override;
    void runAutonomous() override;

private:

    PathFollower p;

};