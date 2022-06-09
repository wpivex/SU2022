#include "Utility/Buttons.cpp"
#include "constants.h"

using namespace vex;

class Team13Robot {

public:

  motor left, right;
  motor arm1, arm2;
  motor roller;

  Team13Robot();

  Buttons b;
  void teleop();
  void setLeftVelocity(directionType d, double percent);
  void setRightVelocity(directionType d, double percent);

};