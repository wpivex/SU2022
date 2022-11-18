#pragma once

#include "Framework/PathFollowing/PathFollower.h"
#include "Framework/Autonomous/Auton.h"

#include "../Controllers/PurePursuit.h"

class PathFollowingAuton : public Auton {

public:

    PathFollowingAuton(Robot& robot):
        Auton(robot),
        p(robot, PurePursuit(), std::vector<std::vector<Waypoint>>() )
    {

    }

    void runPreAutonomous() override;
    void runAutonomous() override;

private:

    PathFollower p;

};