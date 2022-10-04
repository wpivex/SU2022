#pragma once
#include "Controller.h"

class Stanley : public Controller {

public:

    void initNewPath() override;
    bool followPath(Robot& _robot) override;

private:

    // TODO: internal state for stanley
    
};
