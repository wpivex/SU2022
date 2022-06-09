#include "Team13.h"

Team13Robot::Team13Robot():
  left(PORT13, false), 
  right(PORT15, true),
  arm1(PORT5, false),
  arm2(PORT4, true),
  roller(PORT10, true) {

    left.setBrake(coast);
    right.setBrake(coast);
    arm1.setBrake(hold);
    arm2.setBrake(hold);
    roller.setBrake(hold);

}

void Team13Robot::teleop() {

  float drive = buttons.axis(BTN::LEFT_VERTICAL);
  float turn = buttons.axis(BTN::RIGHT_HORIZONTAL);
  float max = std::max(1.0, std::max(fabs(drive+turn), fabs(drive-turn)));
  setLeftVelocity(forward,100 * (drive+turn)/max);
  setRightVelocity(forward,100 * (drive-turn)/max);

  float arm = buttons.axis(BTN::RIGHT_VERTICAL) * 100;

  b.updateButtonState();
}

void Team13Robot::setLeftVelocity(directionType d, double percent) {
  if (percent < 0) {
    d = (d == forward) ? reverse : forward;
    percent = -percent;
  }
  left.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
}

void Team13Robot::setRightVelocity(directionType d, double percent) {
  if (percent < 0) {
    d = (d == forward) ? reverse : forward;
    percent = -percent;
  }
  right.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
}
