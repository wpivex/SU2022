#pragma once

// Implementation interface for path following controllers

class Controller {

public:

    // Attempt to follow the given waypoints. Nonblocking function
    virtual bool tickFollowPath(/* to be determined*/) = 0;
};

// Class headers for different controllers
class PurePursuit : public Controller { bool tickFollowPath() override; };
class Stanley : public Controller { bool tickFollowPath() override; };