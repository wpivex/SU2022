#include "TBHFlywheel.h"
#include <iostream>

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

void TBHFlywheel::setTargetFlywheelVelocity(float velocity) {
    tbh.setTargetRPM(velocity);
}


void TBHFlywheel::maintainVelocityTask() {
    
    while (true) {
        double currentSpeed = motors.velocity(vex::rpm) * ratio;
        float motorInputVolts = tbh.getNextMotorVoltage(currentSpeed);
        motors.spin(vex::forward, motorInputVolts, vex::volt);
        std::cout << "maintain velocity" << motorInputVolts << std::endl;
        vex::task::sleep(10);
    }

}