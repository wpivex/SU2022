#include "TestDriver.h"

void TestDriver::handleSecondaryActions() {
    // TODO: write driver code
    float targetVelocity = 100;

    if(buttons.pressed(BUTTON::Button::R2))
        targetVelocity+=10;
    if(buttons.pressed(BUTTON::Button::L2))
        targetVelocity-=10;

    bool changedPIDConstants = false;
    float kp = 0.5, ki = 0.1;

    if(buttons.pressed(BUTTON::Button::UP)){
        kp += 0.1;
        changedPIDConstants = true;
    }
    if(buttons.pressed(BUTTON::Button::DOWN)){
        kp -= 0.1;
        changedPIDConstants = true;
    }
    if(buttons.pressed(BUTTON::Button::RIGHT)){
        ki += 0.05;
        changedPIDConstants = true;
    }
    if(buttons.pressed(BUTTON::Button::LEFT)){
        ki -= 0.05;
        changedPIDConstants = true;
    }

    robot.flywheel->setTargetFlywheelVelocity(targetVelocity);
    if(changedPIDConstants){
        robot.flywheel->updatePIDConstants(kp,ki,kd);
        changedPIDConstants = false;
    }
    logController("Target Velocity: %f\nk_p: %f\nk_i: %f");
}
