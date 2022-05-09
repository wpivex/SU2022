// CODE FOR 15" ROBOT
#include "Robot/r15/robot15.cpp"

Robot15 robot = Robot15();

int mainTeleop15() {

  while (true) {
    robot.teleop();
    wait(20, msec);
  }
  return 0;
}

int auton() {
  return 0;
}

void preAuton() {
  robot.calibrateGyroBlocking();
}

void autonomous15() { robot.setBrakeType(hold); task auto1(auton); }
//void autonomous15() { thread auto1(mainAuto); }

void userControl15(void) { robot.setBrakeType(coast); task controlLoop1(mainTeleop15); }
//void userControl15(void) { task controlLoop1(logDistance); }


int mainFunc() {
  
  preAuton();
  
  Competition.autonomous(autonomous15);
  Competition.drivercontrol(userControl15);

  while (true) {
    wait(20, msec);
  }

}
