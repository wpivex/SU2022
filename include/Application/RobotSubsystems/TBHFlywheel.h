#pragma once
#include "Framework/RobotSubsystems/Flywheel.h"
#include "Algorithms/TBH.h"
#include "Utility/MathUtility.h"
#include <vector>
#include "vex.h"
#include "Vex/MotorGroup.h"
#include "Utility/VisualGraph.h"

class TBHFlywheel : public Flywheel {

public:

    TBHFlywheel(std::initializer_list<MotorData> flywheelMotors, float flywheelToCartRatio, float tbhConstant, std::vector<DataPoint> voltRpmData, float startSpeed = 0):
        motors(flywheelMotors),
        ratio(flywheelToCartRatio),
        tbh(tbhConstant, startSpeed, voltRpmData),
        g(0, 3600, 10, 400, 4)
    {}

    void setVelocity(float velocity) override;
    float getVelocity() override;
    void maintainVelocityTask() override;


private:
    TBH tbh;
    float ratio;
    MotorGroup motors;
    bool hasSetStopped = false;
    VisualGraph g;

};