// INCLUDE RIGHT VERSION OF ROBOT (15 OR 24)
// #include "main15.cpp"
//#include "Robot/TestRobot.cpp"
#include "Eric/Eric.cpp"
//#include "graphicsTest.cpp"
//#include "Team13/Team13.cpp"

using namespace vex;

//TestRobot r(PORT3, 1, 10, Brain.ThreeWirePort.A, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C);

/*int odom(){
  return r.odomTask();
}*/

int main() {
  //r.calibrateGyro();
  //task t(odom);

  //encoder e(Brain.ThreeWirePort.A);



  //Team13Robot r;
  //r.piston.set(true);
  EricRobot r;
  while (true) {
    r.teleop();
    //log("%f", e.rotation(deg));
    
    wait(20, msec);
    
  }

}
