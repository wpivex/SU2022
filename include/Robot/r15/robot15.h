#pragma once
#include "vex.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>     /* atof */
#include <math.h>       /* sin */
#include <stdio.h>      /* printf, fgets */
#include <unistd.h>
#include <algorithm>

#include "Utility/VisualGraph.cpp"
#include "Robot/PurePursuitRobot.cpp"
#include "constants.h"

using namespace vex;

class Robot15 : public PurePursuitRobot {
  public:

    // four drivebase motors will not be accessible for a while
    Robot15();
    motor leftMotorA;
    motor leftMotorB;
    motor leftMotorC;
    motor leftMotorD;
    motor rightMotorA;
    motor rightMotorB;
    motor rightMotorC;
    motor rightMotorD;


    void setControllerMapping();


    // Teleop methods
    void userControl( void );
    void teleop( void ) override;

    // Calling parent drive functions with params
    void goForwardU(float distInches, float maxSpeed, float universalAngle, bool stopAfter = true, float startSpeed = 18, float stopSpeed = 18, float timeout = 4);
    void goTurnU(float universalAngleDegrees, int direction = 0, bool stopAfter = true, float timeout = 5, float maxSpeed = 75);

    // Implementing abstract functions
    float distanceToDegrees(float distInches) override;
    float degreesToDistance(float distInches) override;
    float getLeftEncoderDistance() override;
    float getRightEncoderDistance() override;
    void resetEncoderDistance() override;
    void setLeftVelocity(directionType d, double percent) override;
    void setRightVelocity(directionType d, double percent) override;
    void stopLeft() override;
    void stopRight() override;
    void setBrakeType(brakeType b) override;
    float getDriveCurrent() override;

    void setDrivePower(float velFL, float velFR, float velBL, float velBR) override;
    void stopDrive() override; // stop all drive motors

  private:
    int intakeState;
    bool targetIsIntake = false;
    bool backIsDown = false;
};