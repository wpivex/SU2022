#include "RobotBuilder.h"

#include "RobotSubsystems/Odometry.h"
#include "RobotSubsystems/DifferentialDrive.h"

#include "constants.h"


Robot getTestRobot() {
    Robot robot;

    vex::motor m1(vex::PORT1);
    vex::motor m2(vex::PORT2);
    vex::motor_group leftMotors(m1);
    vex::motor_group rightMotors(m2);
    robot.drive.reset(new DifferentialDrive(leftMotors, rightMotors));

    Encoder leftEncoder = {Brain.ThreeWirePort.A, 0, 0, 1};
    Encoder rightEncoder = {Brain.ThreeWirePort.B, 0, 0, 1};
    Encoder backEncoder = {Brain.ThreeWirePort.C, 0, 0, 1};
    robot.localizer.reset(new Odometry(vex::PORT1, leftEncoder, rightEncoder, backEncoder));

    return robot;
}