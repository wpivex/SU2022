#include "SingleBoundedPID.h"

// When error crosses over the target threshold, then the PID controller is done
void SingleBoundedPID::handleEndCondition(float error) {

    if (isFirst) {
        goingUp = error < 0;
        isFirst = false;
    }

    done = goingUp ? error >= 0 : error <= 0;
}

bool SingleBoundedPID::isCompleted() {
    return done;
}