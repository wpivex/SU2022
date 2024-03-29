#pragma once
#include "vex.h"

static vex::controller C1 (vex::controllerType::primary);
static vex::controller* Controller1 = &C1;

const static int NUM_BUTTONS = 12;
namespace BUTTON {
  enum Button {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, X = 4, Y = 5, A = 6, B = 7, L1 = 8, L2 = 9, R1 = 10, R2 = 11, NONE = 12, INVALID = 13};
}

namespace AXIS {
  enum Axis {RIGHT_HORIZONTAL = 0 , RIGHT_VERTICAL = 1, LEFT_VERTICAL = 2, LEFT_HORIZONTAL = 3};
}

class Buttons {

  public:

    void updateButtonState();

    bool pressing(BUTTON::Button b);
    bool pressing(int index);
    bool pressed(BUTTON::Button b);
    bool released(BUTTON::Button b);
    BUTTON::Button get();
    float axis(AXIS::Axis a);

  private:
    const vex::controller::button* getObject(BUTTON::Button b);
    bool prevButtonState[NUM_BUTTONS] = {false}; // initalize all values to false

};