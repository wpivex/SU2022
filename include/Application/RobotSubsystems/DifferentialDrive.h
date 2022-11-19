#include "vex.h"
#include "Vex/MotorGroup.h"

#include "Framework/RobotSubsystems/Drive.h"

class DifferentialDrive : public Driveable {

public:
    
    DifferentialDrive(std::initializer_list<MotorData> left, std::initializer_list<MotorData> right):
        leftMotors(left),
        rightMotors(right)
    {}
    
    void setDriveVelocity(float left, float right) override;
    void setBrakeType(vex::brakeType brakeType) override;
    void resetPosition() override;
    float getLeftPosition() override;
    float getRightPosition() override;

    MotorGroup leftMotors, rightMotors;
};