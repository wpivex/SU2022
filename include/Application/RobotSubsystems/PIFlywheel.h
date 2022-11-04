#pragma once
#include "Framework/RobotSubsystems/Flywheel.h"
#include "Algorithms/SimplePID.h"
#include "vex.h"

class PIDFlywheel : public Flywheel {
    public:
        PIDFlywheel(vex::motor_group flywheelMotors, float k_p = 0, float k_i = 0, float k_d = 0);
        void setTargetFlywheelVelocity(float velocity = 0);
        void updatePIDConstants(float k_p = 0, float k_i = 0, float k_d = 0);
        void maintainVelocityTask();
    private:
        vex::motor_group flywheel;
        float targetVelocity;
        SimplePID pid;
};