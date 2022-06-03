// INCLUDE RIGHT VERSION OF ROBOT (15 OR 24)
// #include "main15.cpp"
#include "Robot/TestRobot.cpp"
//#include "graphicsTest.cpp"

using namespace vex;

int main() {

  TestRobot r(PORT3, 1, Brain.ThreeWirePort.A, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C);
  r.calibrateGyro();
  
  while (true) {
    r.holoDriveTeleop();
    wait(20, msec);
  }

}
