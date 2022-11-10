#include "TBH.h"
#include <Utility/MathUtility.h>



TBH::TBH(float gainConstant, float initialTargetRPM, std::function<float(float)> rpmToVoltFunction):
    rpmToVolt(rpmToVoltFunction),
    gain(gainConstant)
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