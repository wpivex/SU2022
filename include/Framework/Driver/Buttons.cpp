#include "Buttons.h"
#include <iostream>

Buttons::Buttons() {

  AXES[0] = Controller1->Axis1;
  AXES[1] = Controller1->Axis2;
  AXES[2] = Controller1->Axis3;
  AXES[3] = Controller1->Axis4;

}

// bound [-1, 1]
float Buttons::axis(AXIS::Axis a) {
  std::cout << "axisa" << &AXES[0] << " " << &(Controller1->Axis1) << std::endl;
  wait(1, vex::sec);
  float pos = AXES[a].position() / 100.0;
  if (fabs(pos) < 0.01) pos = 0;
  return pow(pos, 3);
}

bool Buttons::pressing(BUTTON::Button b) {
  if (b == BUTTON::NONE || b == BUTTON::INVALID) return false;
  return getObject(b)->pressing();
}
bool Buttons::pressing(int index) {
  if (index == BUTTON::NONE || index == BUTTON::INVALID) return false;
  return pressing(static_cast<BUTTON::Button>(index));
}
bool Buttons::pressed(BUTTON::Button b) {
  if (b == BUTTON::NONE || b == BUTTON::INVALID) return false;

  return pressing(b) && !prevButtonState[b];
  
}
bool Buttons::released(BUTTON::Button b) {
  if (b == BUTTON::NONE || b == BUTTON::INVALID) return false;
  return !pressing(b) && prevButtonState[b];
}

BUTTON::Button Buttons::get() {

  for (int i = 0; i < NUM_BUTTONS; i++) {
    BUTTON::Button b = static_cast<BUTTON::Button>(i);
    if (pressed(b)) {
      return b;
    }
  }
  return BUTTON::NONE;
}

// Run at every tick. Read all button inputs and update states
void Buttons::updateButtonState() {

  for (int i = 0; i < NUM_BUTTONS; i++) {
    prevButtonState[i] = pressing(i); 
  }
}

const vex::controller::button* Buttons::getObject(BUTTON::Button b) {
  switch (b) {
    case BUTTON::LEFT:
      return &Controller1->ButtonLeft;
    case BUTTON::RIGHT:
      return &Controller1->ButtonRight;
    case BUTTON::UP:
      return &Controller1->ButtonUp;
    case BUTTON::DOWN:
      return &Controller1->ButtonDown;
    case BUTTON::X:
      return &Controller1->ButtonX;
    case BUTTON::Y:
      return &Controller1->ButtonY;
    case BUTTON::A:
      return &Controller1->ButtonA;
    case BUTTON::B:
      return &Controller1->ButtonB;
    case BUTTON::L1:
      return &Controller1->ButtonL1;
    case BUTTON::R1:
      return &Controller1->ButtonR1;
    case BUTTON::L2:
      return &Controller1->ButtonL2;
    case BUTTON::R2:
      return &Controller1->ButtonR2;
    default:
      return nullptr;
  }
}