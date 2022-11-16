#include "vex.h"

#include "Framework/RobotSubsystems/Drive.h"

class DifferentialDrive : public Driveable {

public:
    DifferentialDrive(vex::motor_group leftMotorGroup, vex::motor_group rightMotorGroup):
        leftMotors(leftMotorGroup),
        rightMotors(rightMotorGroup)
    {}
    
    void setDriveVelocity(float left, float right) override;
    void setBrakeType(vex::brakeType brakeType) override;
    void resetPosition() override;
    float getLeftPosition() override;
    float getRightPosition() override;

    vex::motor_group leftMotors, rightMotors;
};