#include "Utility/Buttons.cpp"
#include "constants.h"

using namespace vex;

class EricRobot{

public:

  motor leftA, leftB, leftC, leftD, rightA, rightB, rightC, rightD;
  motor shooter1, shooter2, intake1, intake2, intake3;

  EricRobot();

  Buttons b;
  void teleop();
  void setLeftVelocity(directionType d, double percent);
  void setRightVelocity(directionType d, double percent);
  void setIntakeVelocity(double percent);

private:
  int targetShooterVelocity = 0;
  int actualShooterVelocity = 0;

};