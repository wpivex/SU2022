#include "Framework/Driver/DriverMixins.h"

class TestDriver : public TankDriver {
    void handleSecondaryActions() override;
};