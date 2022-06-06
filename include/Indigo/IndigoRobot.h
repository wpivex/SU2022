#include "Utility/Buttons.cpp"
#include "constants.h"

using namespace vex;

class IndigoRobot {

public:

  motor leftA, leftB, leftC, rightA, rightB, rightC;
  motor shooter, intake;

  digital_out piston = Brain.ThreeWirePort.A;

  IndigoRobot();

  Buttons b;
  void teleop();
  void setLeftVelocity(directionType d, double percent);
  void setRightVelocity(directionType d, double percent);

private:
  int targetShooterVelocity = 0;
  int actualShooterVelocity = 0;
  bool pistonOn = false;
  int pistonTime = -1;

};