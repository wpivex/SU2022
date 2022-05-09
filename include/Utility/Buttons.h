#pragma once
#include "vex.h"

vex::controller C1 (vex::controllerType::primary);
vex::controller* Controller1 = &C1;

const static int NUM_BUTTONS = 12;
namespace BTN {
  enum Button {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, X = 4, Y = 5, A = 6, B = 7, L1 = 8, L2 = 9, R1 = 10, R2 = 11, NONE = 12, INVALID = 13};
  enum Axis {RIGHT_HORIZONTAL = 0 , RIGHT_VERTICAL = 1, LEFT_VERTICAL = 2, LEFT_HORIZONTAL = 3};
}

class Buttons {

  public:

    Buttons();
    void updateButtonState();

    bool pressing(BTN::Button b);
    bool pressing(int index);
    bool pressed(BTN::Button b);
    bool released(BTN::Button b);
    BTN::Button get();
    float axis(BTN::Axis a);

  private:
    const vex::controller::button* getObject(BTN::Button b);
    const vex::controller::axis *AXES[5];
    bool prevButtonState[NUM_BUTTONS] = {false}; // initalize all values to false

};