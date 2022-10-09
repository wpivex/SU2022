#pragma once

#include "EndablePID.h"

/*
A PID controller which is bounded with a one-sided threshold. This means that when the threshold is crossed,
the controller terminates
*/
class DoubleBoundedPID : public EndablePID {

public:

    DoubleBoundedPID(PIDParameters params, float errorTolerance, int timesWithinTolerance):
        EndablePID(params),
        tolerance(errorTolerance),
        timesNeeded(timesWithinTolerance)
    {}
    bool isCompleted() override;

private:
    void handleEndCondition(float error) override;
    float tolerance;
    int timesNeeded;
    int times = 0;
};