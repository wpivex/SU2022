// INCLUDE RIGHT VERSION OF ROBOT (15 OR 24)
// #include "main15.cpp"
//#include "Robot/TestRobot.cpp"
//#include "graphicsTest.cpp"
#include "Indigo/IndigoRobot.cpp"

using namespace vex;

//TestRobot r(PORT3, 1, 10, Brain.ThreeWirePort.A, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C);

/*int odom(){
  return r.odomTask();
}*/

int main() {
  //r.calibrateGyro();
  //task t(odom);
  IndigoRobot r;
  r.piston.set(true);
  while (true) {
    r.teleop();
    wait(20, msec);
  }

}
