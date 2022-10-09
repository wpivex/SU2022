#pragma once

#include "Application/Controllers/Controller.h"
#include "../RobotSubsystems/Robot.h"

#include <vector>

typedef struct Waypoint {
    float x, y;
} Waypoint;


class PathFollower {
public:

    PathFollower(Robot& _robot, Controller&& _controller, std::vector<std::vector<Waypoint>>&& _path):
        robot(_robot),
        controller(_controller),
        path(std::move(_path))
    {}
    
    void runUntilNode(int index);

protected:

    Robot& robot;
    Controller& controller;
    std::vector<std::vector<Waypoint>> path;

};