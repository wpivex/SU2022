#pragma once

#include "vex.h"
#include <vector>
#include <memory>

typedef struct MotorData {
    int32_t port;
    bool reversed = false;
} MotorData;

class MotorGroup {

public:

    MotorGroup(std::initializer_list<MotorData> multipleMotors) {
        for (auto& i: multipleMotors) 
            motors.emplace_back(std::make_unique<vex::motor>(i.port, i.reversed));
    }

    MotorGroup(const MotorData& motor) {
        motors.emplace_back(std::make_unique<vex::motor>(motor.port, motor.reversed));
    }

    // from -1 to 1
    void setVelocity(float velocity);
    void stop(vex::brakeType brakeType);
    void setBrakeType(vex::brakeType brakeType);

    void resetPosition();

    float getPosition(vex::rotationUnits units);
    float getVelocity(vex::velocityUnits units);

private:
    std::vector<std::unique_ptr<vex::motor>> motors;
};