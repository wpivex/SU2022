// CODE FOR 18" ROBOT
#include "Robot/r18/robot18.cpp"

Robot18 robot = Robot18();

int mainTeleop18() {

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

void autonomous18() { robot.setBrakeType(hold); task auto1(auton); }
//void autonomous15() { thread auto1(mainAuto); }

void userControl18(void) { robot.setBrakeType(coast); task controlLoop1(mainTeleop18); }
//void userControl15(void) { task controlLoop1(logDistance); }


int mainFunc() {
  
  preAuton();
  
  Competition.autonomous(autonomous18);
  Competition.drivercontrol(userControl18);

  while (true) {
    wait(20, msec);
  }

}
