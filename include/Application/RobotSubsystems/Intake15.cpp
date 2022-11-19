#include "Intake15.h"

void Intake15::setVelocity(float velocity) {
    motors.setVelocity(velocity);
}

void Intake15::setIndexer(bool on) {
    indexer.set(on);
}