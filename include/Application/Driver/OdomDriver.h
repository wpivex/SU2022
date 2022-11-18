#include "Framework/Driver/DriverMixins.h"
#include "Utility/FieldGraphics.h"

class OdomDriver : public TankDriver {

    using TankDriver::TankDriver;

public:
    void handleSecondaryActions() override;

private:

    FieldGraphics field;
    
};