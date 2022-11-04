#include "PIFlywheel.h"

PIDFlywheel::PIDFlywheel(vex::motor_group flywheelMotors, float k_p, float k_i, float k_d):
    pid(PIDParameters(k_p,k_i,k_d,0,12)),
    flywheel(flywheelMotors){
}

void PIDFlywheel::setTargetFlywheelVelocity(float velocity){
    targetVelocity = velocity;
}

void PIDFlywheel::updatePIDConstants(float k_p, float k_i, float k_d){
    pid.setNewParam(k_p,k_i,k_d);
}

void PIDFlywheel::maintainVelocityTask(){
    float velocity = flywheel.velocity(vex::rpm);
    float error = velocity - targetVelocity;
    float effort = pid.tick(error);
    flywheel.spin(vex::forward, effort, vex::volt);
}
