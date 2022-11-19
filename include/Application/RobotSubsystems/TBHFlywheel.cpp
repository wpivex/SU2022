#include "TBHFlywheel.h"

float voltToRpm(float volt, std::vector<DataPoint>& data) {
    
    int lowerBound = 0;
    while (lowerBound < data.size() - 2 && data[lowerBound+1].volt < volt) lowerBound++;
    
    float percent = (volt - data[lowerBound].volt) / (data[lowerBound+1].volt - data[lowerBound].volt);
    return data[lowerBound].rpm + (data[lowerBound+1].rpm - data[lowerBound].rpm) * percent;

}

float rpmToVolt(float rpm, std::vector<DataPoint>& data) {

    int lowerBound = 0;
    while (lowerBound < data.size() - 2 && data[lowerBound+1].rpm < rpm) lowerBound++;
    
    float percent = (rpm - data[lowerBound].rpm) / (data[lowerBound+1].rpm - data[lowerBound].rpm);
    return data[lowerBound].volt + (data[lowerBound+1].volt - data[lowerBound].volt) * percent;

}

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
            serial("stop");
        } else if (tbh.getTargetRPM() != 0) {
            float currentSpeed = motors.getVelocity(vex::rpm) * ratio;
            float motorInputVolts = tbh.getNextMotorVoltage(currentSpeed);
            motors.setVelocity(motorInputVolts / 12.0);
            serial(motorInputVolts);
        }

        vex::task::sleep(10);
    }
}