#include "vex.h"

#include "Framework/RobotSubsystems/Drive.h"

class DifferentialDrive : public Driveable {

public:
    DifferentialDrive(vex::motor_group leftMotors, vex::motor_group rightMotors):
        leftMotors(leftMotors),
        rightMotors(rightMotors)
    {}
    
    void setDriveVelocity(float left, float right) override;
    void setBrakeType(vex::brakeType brakeType) override;
    void resetPosition() override;
    float getLeftPosition() override;
    float getRightPosition() override;

    vex::motor_group leftMotors, rightMotors;
};