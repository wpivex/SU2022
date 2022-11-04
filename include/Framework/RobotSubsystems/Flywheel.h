#pragma once

class Flywheel {

public:
    virtual void setTargetFlywheelVelocity(float velocity) = 0;
    virtual void maintainVelocityTask() = 0;
    virtual void updatePIDConstants(float k_p = 0, float k_i = 0, float k_d = 0) = 0;
};