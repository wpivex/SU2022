#pragma once
#include "Framework/RobotSubsystems/Flywheel.h"
#include "Algorithms/TBH.h"
#include "Utility/MathUtility.h"
#include <vector>
#include "vex.h"
#include "Vex/MotorGroup.h"

typedef struct DataPoint {
    float rpm, volt;
} DataPoint;

float voltToRpm(float volt, std::vector<DataPoint>& data);
float rpmToVolt(float rpm, std::vector<DataPoint>& data);


class TBHFlywheel : public Flywheel {

public:

    TBHFlywheel(std::initializer_list<MotorData> flywheelMotors, float flywheelToCartRatio, float tbhConstant, std::vector<DataPoint> voltRpmData, float startSpeed = 0):
        motors(flywheelMotors),
        ratio(flywheelToCartRatio),
        tbh(tbhConstant, startSpeed, std::bind(rpmToVolt, std::placeholders::_1, voltRpmData))
    {}

    void setVelocity(float velocity) override;
    float getVelocity() override;
    void maintainVelocityTask() override;


private:
    TBH tbh;
    float ratio;
    MotorGroup motors;
    bool hasSetStopped = false;

};