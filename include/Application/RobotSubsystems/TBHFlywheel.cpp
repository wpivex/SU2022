#include "TBHFlywheel.h"



void TBHFlywheel::setVelocity(float velocity) {
    tbh.setTargetRPM(velocity);
    if (velocity == 0) hasSetStopped = false;
}

float TBHFlywheel::getVelocity() {
    return tbh.getTargetRPM();
}


void TBHFlywheel::maintainVelocityTask() {

    using namespace std;
    
    while (true) {

        if (tbh.getTargetRPM() == 0 && !hasSetStopped) {
            motors.stop(vex::brake);
            hasSetStopped = true;
        } else if (tbh.getTargetRPM() != 0) {
            float currentSpeed = motors.getVelocity(vex::rpm) * ratio;
            float motorInputVolts = tbh.getNextMotorVoltage(currentSpeed);
            motors.setVelocity(motorInputVolts / 12.0);
            
            g.push(currentSpeed, 0);
            g.push(tbh.getTargetRPM(), 1);
            g.push(tbh.voltToRpm(motorInputVolts), 2);
            g.push(tbh.voltToRpm(tbh.getTBH()), 3);

            g.display();

        }

        vex::task::sleep(10);
    }
}