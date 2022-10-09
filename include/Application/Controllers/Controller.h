#pragma once

#include "Framework/RobotSubsystems/Robot.h"

// Implementation interface for path following controllers

class Controller {

public:

    // Attempt to follow the given waypoints. Nonblocking function
    virtual void initNewPath() = 0;
    virtual bool followPath(Robot& _robot) = 0;
    
    void setNewPath(std::vector<Waypoint>* currentPath) {
        path = currentPath;
        initNewPath();
    }

protected:
    std::vector<Waypoint>* path;
};