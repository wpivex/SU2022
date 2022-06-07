#include "Eric.h"

EricRobot::EricRobot():
  leftA(PORT5, false),
  leftB(PORT6, false),
  leftC(PORT7, false),
  leftD(PORT8, false),
  rightA(PORT1, true),
  rightB(PORT2, true),
  rightC(PORT3, true),
  rightD(PORT4, true),
  shooter1(PORT9, true),
  shooter2(PORT11, false),
  intake1(PORT12, true),
  intake2(PORT13, true),
  intake3(PORT14, true) {

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

}

void EricRobot::teleop() {

  float drive = buttons.axis(BTN::LEFT_VERTICAL);
    float turn = buttons.axis(BTN::RIGHT_HORIZONTAL);
    float max = std::max(1.0, std::max(fabs(drive+turn), fabs(drive-turn)));
    setLeftVelocity(forward,100 * (drive+turn)/max);
    setRightVelocity(forward,100 * (drive-turn)/max);

  if (buttons.pressed(BTN::B)) {
    targetShooterVelocity = (targetShooterVelocity == 100) ? 0 : 100;
  }
  if (actualShooterVelocity < targetShooterVelocity) actualShooterVelocity += 4;
  else if (actualShooterVelocity > targetShooterVelocity) actualShooterVelocity -= 4;

  setMotorVelocity(shooter1, actualShooterVelocity);
  setMotorVelocity(shooter2, actualShooterVelocity);

  if (buttons.pressed(BTN::X)) setIntakeVelocity(100);
  else setIntakeVelocity(0);

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