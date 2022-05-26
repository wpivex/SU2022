#include "Utility/VisualField.cpp"

void run() {

  VisualField f;
  f.drawField();

  while (true) {
    wait(20, vex::msec);
  }

}