//#include "Utility/VisualField.cpp"
#include "Robot/r15/Robot15.cpp"

void run() {

  VisualField f;
  Robot15 r;
  f.drawField();
  r.drawTrajectory(&f);

  while (true) {
    wait(20, vex::msec);
  }

}