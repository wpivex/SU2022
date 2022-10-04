#pragma once
#include "Controller.h"

class PurePursuit : public Controller {

public:

    void initNewPath() override;
    bool followPath(Robot& _robot) override;

private:

    // TODO: internal state for pure pursuit
    
};
