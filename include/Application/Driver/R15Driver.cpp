#include "R15Driver.h"
#include "math.h"

const float INCREMENT = 100;

void R15Driver::handleSecondaryActions() {

    using namespace vex;

    if (buttons.pressed(BUTTON::UP)) {
        float target = fmin(4000, robot.flywheel->getVelocity() + INCREMENT);
        robot.flywheel->setVelocity(target);
    } else if (buttons.pressed(BUTTON::DOWN)) {
        float target = fmax(0, robot.flywheel->getVelocity() - INCREMENT);
        robot.flywheel->setVelocity(target);
    }

    if (buttons.pressing(BUTTON::R2)) {
        robot.intake->setVelocity(-1);
    } else if (buttons.pressing(BUTTON::R1)) {
        robot.intake->setVelocity(1);
    } else {
        robot.intake->stop();
    }

}
