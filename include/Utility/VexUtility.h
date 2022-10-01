#include "vex.h"

// Velocity from -1 to 1
void setMotorVelocity(vex::motor m, vex::directionType d, double percent) {
    if (percent < 0) {
        d = (d == vex::forward) ? vex::reverse : vex::forward;
        percent = -percent;
    }

    percent = fmin(1, fmax(-1, percent)); // bound between -1 and 1

    m.spin(d, percent * 12.0, vex::voltageUnits::volt);
}