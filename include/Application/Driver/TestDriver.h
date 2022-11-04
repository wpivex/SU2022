#include "Framework/Driver/DriverMixins.h"

class TestDriver : public TankDriver {

public:
    void handleSecondaryActions() override;

private:
    float targetVelocity = 100;
    
};