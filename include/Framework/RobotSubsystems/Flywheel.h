#pragma once

class Flywheel {

public:
    virtual void setTargetFlywheelVelocity(float velocity) = 0;
    virtual void maintainVelocityTask() = 0;
};