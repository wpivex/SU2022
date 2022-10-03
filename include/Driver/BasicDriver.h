#pragma once

#include "Driver.h"
#include "Buttons.h"

class BasicDriver : public Driver {

    using Driver::Driver;

public:

    virtual void runDriver();
        
protected:
    virtual void handleDrivetrain() {}
    virtual void handleSecondaryActions() {}

    Buttons buttons;
};