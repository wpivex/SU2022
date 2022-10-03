#include "RobotSubsystems/Drive.h"
#include "RobotSubsystems/Localization/Odometry.h"
#include "RobotCreator.h"
#include <memory>

Robot getTestRobot() {
    Robot robot;

    vex::motor m1(vex::PORT1);
    vex::motor m2(vex::PORT2);
    vex::motor_group left(m1);
    vex::motor_group right(m2);
    robot.drive.reset(new DifferentialDrive(left, right));

    Encoder e1 = {0,0,false};
    Encoder e2 = {0,0,false};
    Encoder e3 = {0,0,false};
    robot.localizer.reset(new Odometry(e1, e2, e3));

    return robot;
}