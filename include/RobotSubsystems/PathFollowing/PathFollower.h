#pragma once

class PathFollowable {
    virtual void runUntilNode(int index) = 0;
};

class PathFollower : public PathFollowable {
    void setController() {}
    void runUntilNode(int index) {}
};