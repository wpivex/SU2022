#include "RobotBuilder.h"

#include "RobotSubsystems/Odometry.h"
#include "RobotSubsystems/DifferentialDrive.h"


Robot getTestRobot() {
    Robot robot;

    vex::motor m1(vex::PORT1);
    vex::motor m2(vex::PORT2);
    vex::motor_group leftMotors(m1);
    vex::motor_group rightMotors(m2);
    robot.drive.reset(new DifferentialDrive(leftMotors, rightMotors));

    Encoder leftEncoder = {0,0};
    Encoder rightEncoder = {0,0};
    Encoder backEncoder = {0,0};
    robot.localizer.reset(new Odometry(leftEncoder, rightEncoder, backEncoder));

    return robot;
}