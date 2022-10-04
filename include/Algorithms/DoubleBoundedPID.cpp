#include "DoubleBoundedPID.h"

// When error is within [-tolerance, tolerance] for 'timesNeeded' ticks, then the PID controller is done
void DoubleBoundedPID::handleEndCondition(float error) {

    if (fabs(error) < tolerance) times++;
    else times = 0;
}

bool DoubleBoundedPID::isCompleted() {
    return times >= timesNeeded;
}