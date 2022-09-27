#pragma once

#include "GenericRobot.h"
#include "PathFollowing/ControllerInterface.h"
#include <memory>


// mixin for GenericRobot
class PathFollowerMixin : public virtual GenericRobot {

public:

    PathFollowerMixin(std::shared_ptr<ControllerInterface> controller) {
        _controller = controller;
    }

    virtual void runUntilNode(int index) {
        // follow the path, using localizer and locomotion methods inherited from GenericRobot
        // TODO
    }

protected:

    std::shared_ptr<ControllerInterface> _controller;


};