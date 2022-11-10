#pragma once
#include <functional>


/*
A controller class that attempts to maintain the velocity of motor(s) given a target.
TBH is good for slow response times like flywheels and are an alternative to PID.
*/

class TBH {

public:

    TBH(float gainConstant, float initialTargetRPM, std::function<float(float)> rpmToVoltFunction);
    float getNextMotorVoltage(float currentVelocityRPM);
    void setTargetRPM(float targetVelocityRPM);
    float getTargetRPM() {return targetRPM;}
    float getTBH() {return tbh;}

private:

    std::function<float(float)> rpmToVolt;
    float gain;
    float targetRPM;
    float output = 0;
    float prevError = 0;
    float tbh;
    bool isFirstCrossover = true;

};