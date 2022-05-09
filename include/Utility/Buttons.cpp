#pragma once
#include "Buttons.h"

Buttons::Buttons() {

  AXES[0] = &Controller1->Axis1;
  AXES[1] = &Controller1->Axis2;
  AXES[2] = &Controller1->Axis3;
  AXES[3] = &Controller1->Axis4;

}

inline float Buttons::axis(BTN::Axis a) {
  float pos = AXES[a]->position();

  // deadzone
  if (fabs(pos) <= 5) {
    return 0;
  }
  // normalize between 1-100, and cube to give more sensitivity to small inputs
  return pow(pos / 100.0, 3);
}

inline bool Buttons::pressing(BTN::Button b) {
  if (b == BTN::NONE || b == BTN::INVALID) return false;
  return getObject(b)->pressing();
}
inline bool Buttons::pressing(int index) {
  if (index == BTN::NONE || index == BTN::INVALID) return false;
  return pressing(static_cast<BTN::Button>(index));
}
inline bool Buttons::pressed(BTN::Button b) {
  if (b == BTN::NONE || b == BTN::INVALID) return false;
  return pressing(b) && !prevButtonState[b];
}
inline bool Buttons::released(BTN::Button b) {
  if (b == BTN::NONE || b == BTN::INVALID) return false;
  return !pressing(b) && prevButtonState[b];
}

inline BTN::Button Buttons::get() {

  for (int i = 0; i < NUM_BUTTONS; i++) {
    BTN::Button b = static_cast<BTN::Button>(i);
    if (pressed(b)) {
      return b;
    }
  }
  return BTN::NONE;
}

// Run at every tick. Read all button inputs and update states
void Buttons::updateButtonState() {

  for (int i = 0; i < NUM_BUTTONS; i++) {
    prevButtonState[i] = pressing(i); 
  }
}

const vex::controller::button* Buttons::getObject(BTN::Button b) {
  switch (b) {
    case BTN::LEFT:
      return &Controller1->ButtonLeft;
    case BTN::RIGHT:
      return &Controller1->ButtonRight;
    case BTN::UP:
      return &Controller1->ButtonUp;
    case BTN::DOWN:
      return &Controller1->ButtonDown;
    case BTN::X:
      return &Controller1->ButtonX;
    case BTN::Y:
      return &Controller1->ButtonY;
    case BTN::A:
      return &Controller1->ButtonA;
    case BTN::B:
      return &Controller1->ButtonB;
    case BTN::L1:
      return &Controller1->ButtonL1;
    case BTN::R1:
      return &Controller1->ButtonR1;
    case BTN::L2:
      return &Controller1->ButtonL2;
    case BTN::R2:
      return &Controller1->ButtonR2;
    default:
      return nullptr;
  }
}