#pragma once

#include "Application/Controllers/Controller.h"
#include "PathData.h"
#include "../RobotSubsystems/Robot.h"

class PathFollower {
public:

    PathFollower(Robot& _robot, Controller&& _controller, const PathData& _data):
        robot(_robot),
        controller(_controller),
        data(_data)
    {}
    
    void runUntilNode(int index);

protected:

    Robot& robot;
    Controller& controller;
    const PathData& data;

};