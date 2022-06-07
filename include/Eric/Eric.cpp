#include "Eric.h"

EricRobot::EricRobot():
  leftA(PORT1, false),
  leftB(PORT2, false),
  leftC(PORT3, false),
  leftD(PORT4, false),
  rightA(PORT5, true),
  rightB(PORT6, true),
  rightC(PORT7, true),
  rightD(PORT8, true),
  shooter1(PORT9, true),
  shooter2(PORT10, true),
  intake1(PORT12, true),
  intake2(PORT13, true),
  intake3(PORT14, true),
  spinner(PORT19, ratio6_1, true) {

    leftA.setBrake(coast);
    leftB.setBrake(coast);
    leftC.setBrake(coast);
    leftD.setBrake(coast);
    rightA.setBrake(coast);
    rightB.setBrake(coast);
    rightC.setBrake(coast);
    rightD.setBrake(coast);
    shooter1.setBrake(coast);
    shooter2.setBrake(coast);
    intake1.setBrake(coast);
    intake2.setBrake(coast);
    intake3.setBrake(coast);
    spinner.setBrake(hold);

}

void EricRobot::teleop() {

  float drive = buttons.axis(BTN::LEFT_VERTICAL);
  float turn = buttons.axis(BTN::RIGHT_HORIZONTAL);
  float max = std::max(1.0, std::max(fabs(drive+turn), fabs(drive-turn)));
    setLeftVelocity(forward,100 * (drive+turn)/max);
    setRightVelocity(forward,100 * (drive-turn)/max);
  log("%f\n%f", 100 * (drive+turn)/max, 100 * (drive-turn)/max);
  if (buttons.pressed(BTN::B)) {
    targetShooterVelocity = (targetShooterVelocity == 100) ? 0 : 100;
  }
  if (actualShooterVelocity < targetShooterVelocity) actualShooterVelocity += 4;
  else if (actualShooterVelocity > targetShooterVelocity) actualShooterVelocity -= 4;

  setMotorVelocity(shooter1, actualShooterVelocity);
  setMotorVelocity(shooter2, actualShooterVelocity);

  if (buttons.pressed(BTN::X)) intakeOn = !intakeOn;
  if (intakeOn) setIntakeVelocity(100);
  else setIntakeVelocity(0);

  if (buttons.pressed(BTN::R2)) {
    spinnerTarget = 55;
    spinnerTime = timer::system();
  }
  if (spinnerTarget > 0 && isTimeout(spinnerTime, 0.2) && !buttons.pressing(BTN::R2)) {
    spinnerTarget = 10;
  }
  float error = spinnerTarget - spinner.position(deg);
  if (fabs(error) < 5) error = 0;
  float speed = error * 1;
  setMotorVelocity(spinner, fmax(-100, fmin(100, speed)));

  b.updateButtonState();
}

void EricRobot::setLeftVelocity(directionType d, double percent) {
  if (percent < 0) {
    d = (d == forward) ? reverse : forward;
    percent = -percent;
  }
  leftA.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  leftB.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  leftC.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  leftD.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
}

void EricRobot::setRightVelocity(directionType d, double percent) {
  if (percent < 0) {
    d = (d == forward) ? reverse : forward;
    percent = -percent;
  }
  rightA.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  rightB.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  rightC.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  rightD.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
}

void EricRobot::setIntakeVelocity(double percent) {
  setMotorVelocity(intake1, percent);
  setMotorVelocity(intake2, percent);
  setMotorVelocity(intake3, percent);
}