#include "Buttons.h"
#include "GenericRobot.h"

class GenericAutonomous {

public:

    GenericAutonomous(GenericRobot* robot) : _robot(robot) {}

    virtual void preAuton() {};
    virtual void run() {};

protected:

    GenericRobot* _robot;

};