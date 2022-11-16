#include "RobotBuilder.h"

#include "RobotSubsystems/Odometry.h"
#include "RobotSubsystems/DifferentialDrive.h"
#include "RobotSubsystems/TBHFlywheel.h"
#include "constants.h"


Robot getTestRobot() {
    Robot robot;
    
    vex::motor m1(vex::PORT1);
    vex::motor m2(vex::PORT2);
    vex::motor_group leftMotors(m1);
    vex::motor_group rightMotors(m2);
    robot.drive.reset(new DifferentialDrive(leftMotors, rightMotors));
     
    //return robot;
    // Encoder leftEncoder = {Brain.ThreeWirePort.A, 0, 0, 1};
    // Encoder rightEncoder = {Brain.ThreeWirePort.B, 0, 0, 1};
    // Encoder backEncoder = {Brain.ThreeWirePort.C, 0, 0, 1};
    // robot.localizer.reset(new Odometry(vex::PORT1, leftEncoder, rightEncoder, backEncoder));
    
    vex::motor f1(vex::PORT4, false);
    vex::motor f2(vex::PORT5, true);
    vex::motor_group flywheel(f1,f2);
    std::vector<DataPoint> data = {
        {1615, 5},
        {1966, 6},
        {2306, 7},
        {2646, 8},
        {3054, 9},
        {3416, 10},
        {3751, 11},
        {4141, 12}
    };
    robot.flywheel.reset(new TBHFlywheel(flywheel, 6, 0.0002, std::move(data), 0));

    return robot;
}