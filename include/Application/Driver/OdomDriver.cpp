#include "OdomDriver.h"
#include "Utility/Logging.h"
#include "math.h"

void TestDriver::handleSecondaryActions() {
   
   float x = robot.localizer->getX();
   float y = robot.localizer->getY();
   float theta = robot.localizer->getHeading();

   field.drawField();
   
    float px = field.getX(x);
    float py = field.getY(y);
    Brain.Screen.drawCircle(px, py, 10);

    float length = 10;
    Brain.Screen.drawLine(px, py, px + length * cos(theta), py + length * sin(theta));

}
