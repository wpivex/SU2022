#include "TBH.h"
#include <Utility/MathUtility.h>



TBH::TBH(float gainConstant, float initialTargetRPM, std::vector<DataPoint> flywheelData):
    gain(gainConstant),
    data(flywheelData)
{
    setTargetRPM(initialTargetRPM);
}

// Given the current velocity, return a goal velocity based on tbh algorithm to minimize error
float TBH::getNextMotorVoltage(float currentVelocityRPM) {
    
    float error = targetRPM - currentVelocityRPM; // calculate the error;
    output += gain * error; // integrate the output

    output = clamp(output, 0, 12); // bound output to possible voltages
        
    if (sign(error) != sign(prevError)) { // if zero crossing,

        if (isFirstCrossover) { // First zero crossing after a new set velocity command
            // Set drive to the open loop approximation
            output = rpmToVolt(targetRPM);
        } else {
            output = 0.5 * (output + tbh); // Take Back Half
            isFirstCrossover = false;
        }

        tbh = output;// update Take Back Half variable
        prevError = error; // save the previous error
    }

    return output;

}

// Set the goal velocity in rpm
void TBH::setTargetRPM(float targetVelocityRPM) {
    targetRPM = targetVelocityRPM;
    isFirstCrossover = true;
}

float TBH::voltToRpm(float volt) {
    
    int lowerBound = 0;
    while (lowerBound < data.size() - 2 && data[lowerBound+1].volt < volt) lowerBound++;
    
    float percent = (volt - data[lowerBound].volt) / (data[lowerBound+1].volt - data[lowerBound].volt);
    return data[lowerBound].rpm + (data[lowerBound+1].rpm - data[lowerBound].rpm) * percent;

}

float TBH::rpmToVolt(float rpm) {

    int lowerBound = 0;
    while (lowerBound < data.size() - 2 && data[lowerBound+1].rpm < rpm) lowerBound++;
    
    float percent = (rpm - data[lowerBound].rpm) / (data[lowerBound+1].rpm - data[lowerBound].rpm);
    return data[lowerBound].volt + (data[lowerBound+1].volt - data[lowerBound].volt) * percent;

}