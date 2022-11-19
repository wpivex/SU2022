#include "Framework/Driver/DriverMixins.h"
#include "Utility/FieldGraphics.h"

class R15Driver : public TankDriver {

    using TankDriver::TankDriver;

public:
    void handleSecondaryActions() override;

private:

    bool indexerOn = false;
    int indexerTimer;
    
};