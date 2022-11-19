#pragma once
#include <functional>
#include <vector>

typedef struct DataPoint {
    float rpm, volt;
} DataPoint;

/*
A controller class that attempts to maintain the velocity of motor(s) given a target.
TBH is good for slow response times like flywheels and are an alternative to PID.
*/

class TBH {

public:

    TBH(float gainConstant, float initialTargetRPM, std::vector<DataPoint> flywheelData);
    float getNextMotorVoltage(float currentVelocityRPM);
    void setTargetRPM(float targetVelocityRPM);
    float getTargetRPM() {return targetRPM;}
    float getTBH() {return tbh;}

    float voltToRpm(float volt);
    float rpmToVolt(float rpm);

private:

    std::vector<DataPoint> data;
    float gain;
    float targetRPM;
    float output = 0;
    float prevError = 0;
    float tbh;
    bool isFirstCrossover = true;

};