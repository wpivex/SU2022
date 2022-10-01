#pragma once

#include "GenericRobot.h"
#include "PathFollowing/ControllerInterface.h"
#include <memory>


class PathFollower {

public:

    PathFollower(ControllerInterface& controller):
        _controller(controller)
    {
    }

    virtual void runUntilNode(int index) {
        // follow the path, using localizer and locomotion methods inherited from GenericRobot
        // TODO
    }

protected:

    ControllerInterface& _controller;


};