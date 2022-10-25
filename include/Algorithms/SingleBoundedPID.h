#pragma once

#include "EndablePID.h"

/*
A PID controller which is bounded with a one-sided threshold. This means that when the threshold is crossed,
the controller terminates
*/
class SingleBoundedPID : public EndablePID {

public:

    SingleBoundedPID(PIDParameters params):
        EndablePID(params)
    {}
    bool isCompleted() override;

private:
    void handleEndCondition(float error) override;
    bool goingUp;
    bool isFirst = true;
    bool done = false;
};