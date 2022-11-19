#pragma once

class Flywheel {

public:
    virtual void setVelocity(float velocity) = 0;
    virtual float getVelocity() = 0;
    virtual void maintainVelocityTask() = 0;
};