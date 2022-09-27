#pragma once

// Implementation interface for path following controllers

class ControllerInterface {

public:

    // Attempt to follow the given waypoints. Nonblocking function
    virtual bool tickFollowPath(/* to be determined*/) = 0;
};