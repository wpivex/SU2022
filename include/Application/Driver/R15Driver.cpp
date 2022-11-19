#include "R15Driver.h"
#include "math.h"

const float INCREMENT = 100;

void R15Driver::handleSecondaryActions() {

    using namespace vex;

    // update flywheel speed with L1 and L2
    if (buttons.pressed(BUTTON::L1)) {
        float target = fmin(4000, robot.flywheel->getVelocity() + INCREMENT);
        robot.flywheel->setVelocity(target);
    } else if (buttons.pressed(BUTTON::L2)) {
        float target = fmax(0, robot.flywheel->getVelocity() - INCREMENT);
        robot.flywheel->setVelocity(target);
    }

    // Indexer is set to R2 state. R2: Intake forward with 0.25s delay, R1: intake reverse
    if (buttons.pressed(BUTTON::R2)) {
        robot.intake->setIndexer(true);
        indexerOn = true;
        indexerTimer = timer::system();
    } else if (buttons.released(BUTTON::R2)) {
        robot.intake->setIndexer(false);
        indexerOn = false;
    }

    // Actually set the intake velocity
    if (indexerOn && timer::system() - 250 > indexerTimer) {
        robot.intake->setVelocity(-1);
    } else if (buttons.pressing(BUTTON::R1)) {
        robot.intake->setVelocity(1);
    } else {
        robot.intake->stop();
    }
}
