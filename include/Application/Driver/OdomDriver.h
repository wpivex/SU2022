#include "Framework/Driver/DriverMixins.h"
#include "Utility/FieldGraphics.h"

class TestDriver : public TankDriver {

public:
    void handleSecondaryActions() override;

private:

    FieldGraphics field;
    
};