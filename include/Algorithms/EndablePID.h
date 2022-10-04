#pragma once

#include "SimplePID.h"

/*
An interface for a PID controller which has an end condition
*/
class EndablePID : public SimplePID {
    using SimplePID::SimplePID;

public:
    virtual bool isCompleted() = 0;
};