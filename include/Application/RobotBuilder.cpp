#include "RobotBuilder.h"

#include "RobotSubsystems/Odometry.h"
#include "RobotSubsystems/DifferentialDrive.h"
#include "RobotSubsystems/TBHFlywheel.h"
#include "constants.h"


Robot getTestRobot() {

    using namespace vex;

    Robot robot;
  
    robot.drive.reset(new DifferentialDrive(
        { // left motors
            {PORT11, true},
            {PORT12, false},
            {PORT14, true},
            {PORT15, false}
        },
        { // right motors
            {PORT17, false},
            {PORT18, false},
            {PORT19, true},
            {PORT20, true}
        }
    ));
    
    // Encoder leftEncoder = {Brain.ThreeWirePort.E, 0, 0, 1};
    // Encoder rightEncoder = {Brain.ThreeWirePort.C, 0, 0, 1};
    // Encoder backEncoder = {Brain.ThreeWirePort.A, 0, 0, 1};
    // robot.localizer.reset(new Odometry(vex::PORT7, leftEncoder, rightEncoder, backEncoder));
    

    vex::motor f1(vex::PORT1, false);
    vex::motor f2(vex::PORT2, true);
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
    robot.flywheel.reset(new TBHFlywheel(
        { {PORT1, false},{PORT2, true} }, 
        6, // flywheel to cart ratio
        0.0002, // tbh constant
        std::move(data),
        0)); // start speed
    
    return robot;
}