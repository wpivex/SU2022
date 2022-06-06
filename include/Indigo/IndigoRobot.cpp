#include "IndigoRobot.h"

IndigoRobot::IndigoRobot():
  leftA(PORT1, true),
  leftB(PORT2, false),
  leftC(PORT3, true),
  rightA(PORT4, false),
  rightB(PORT5, true),
  rightC(PORT6, false),
  shooter(PORT7, true),
  intake(PORT8, true) {

    leftA.setBrake(coast);
    leftB.setBrake(coast);
    leftC.setBrake(coast);
    rightA.setBrake(coast);
    rightB.setBrake(coast);
    rightC.setBrake(coast);
    shooter.setBrake(coast);
    intake.setBrake(coast);

}

void IndigoRobot::teleop() {

  setLeftVelocity(forward,buttons.axis(BTN::LEFT_VERTICAL));
  setRightVelocity(forward,buttons.axis(BTN::RIGHT_VERTICAL));

  if (buttons.pressed(BTN::A)) {
    targetShooterVelocity = (targetShooterVelocity == 100) ? 0 : 100;
  }
  if (actualShooterVelocity < targetShooterVelocity) actualShooterVelocity += 4;
  else if (actualShooterVelocity > targetShooterVelocity) actualShooterVelocity -= 4;

  setMotorVelocity(shooter, actualShooterVelocity);

  if (buttons.pressed(BTN::R1)) setMotorVelocity(intake, 100);
  else if (buttons.pressed(BTN::R2)) setMotorVelocity(intake, -100);
  else setMotorVelocity(intake, 0);

  if (buttons.pressed(BTN::A)) {
    pistonOn = true;
    pistonTime = timer::system();
    piston.set(true);
  }
  if (pistonOn &&isTimeout(pistonTime, 0.1)) {
      pistonOn = false;
      piston.set(false);
  }
  b.updateButtonState();
}

void IndigoRobot::setLeftVelocity(directionType d, double percent) {
  if (percent < 0) {
    d = (d == forward) ? reverse : forward;
    percent = -percent;
  }
  leftA.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  leftB.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  leftC.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
}

void IndigoRobot::setRightVelocity(directionType d, double percent) {
  if (percent < 0) {
    d = (d == forward) ? reverse : forward;
    percent = -percent;
  }
  rightA.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  rightB.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
  rightC.spin(d, percent / 100.0 * MAX_VOLTS, voltageUnits::volt);
}