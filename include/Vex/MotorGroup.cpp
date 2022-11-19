#include "MotorGroup.h"

// from -1 to 1
void MotorGroup::setVelocity(float velocity) {
    using namespace vex;
    for (auto& motor : motors) {
        motor->spin(forward, velocity * 12, volt);
    }
}
void MotorGroup::stop(vex::brakeType type) {
    using namespace vex;
    for (auto& motor : motors) {
        motor->stop(type);
    }
}

void MotorGroup::setBrakeType(vex::brakeType type) {
    using namespace vex;
    for (auto& motor : motors) {
        motor->setBrake(type);
    }
}

void MotorGroup::resetPosition() {
    using namespace vex;
    for (auto& motor : motors) {
        motor->resetPosition();
    }
}

float MotorGroup::getPosition(vex::rotationUnits units) {

    if (motors.size() == 0) return 0;

    float sum = 0;
    for (auto& motor : motors) {
        sum += motor->position(units);
    }
    return sum / motors.size();
}

float MotorGroup::getVelocity(vex::velocityUnits units) {
    
    if (motors.size() == 0) return 0;

    float sum = 0;
    for (auto& motor : motors) {
        sum += motor->velocity(units);
    }
    return sum / motors.size();
}
