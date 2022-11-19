#pragma once

#include "Framework/RobotSubsystems/Intake.h"
#include "Vex/MotorGroup.h"
#include "vex.h"

class Intake15 : public Intakeable {

public:

    Intake15(std::initializer_list<MotorData> intakeMotors, vex::triport::port pistonPort):
        motors(intakeMotors),
        indexer(pistonPort)
    {}

    void setVelocity(float velocity) override;
    void setIndexer(bool on) override;
    
private:
    MotorGroup motors;
    vex::digital_out indexer;

};