#include "GenericDriver.h"

class TankDriver : public GenericDriver {

protected:

    void handleDrivetrain() override {
        // TODO
        _robot->setVelocity(0,0);
    }
};

class ArcadeDriver : public GenericDriver {

protected:

    void handleDrivetrain() override {
        // TODO
        _robot->setVelocity(0,0);
    }
};