#include "Odometry.h"
#include "Utility/MathUtility.h"

// Calculate the position of the robot for one tick based on encoders
// update x, y, heading
void Odometry::calculatePosition() {

    float polledRight = right.get();
    float polledBack = back.get();
    float polledLeft = left.get();
    float polledTheta = gyroSensor.heading();
    
    float deltaR = polledRight - prevRight;
    float deltaB = polledBack - prevBack;
    float deltaL = polledLeft - prevLeft;
    float deltaTheta = bound180(polledTheta - prevTheta) * M_PI/180;
    
    // Split vector to X and Y 
    float distY = (deltaL + deltaR) / 2;  
    float deltaX;
    float deltaY;
    float theta = polledTheta * M_PI/180;
    float rTheta = prevTheta * M_PI/180;

    if(deltaTheta != 0){
        float radiusY = distY/deltaTheta;
        deltaX = radiusY * (cos(theta) - cos(rTheta));
        deltaY = radiusY * (sin(theta) - sin(rTheta));
        float radiusX = deltaB / deltaTheta;
        deltaX += radiusX * (sin(theta) - sin(rTheta));;
        deltaY += radiusX * (cos(theta) - cos(rTheta));
    } else {
        // prevent divison by 0, when robot has travelled perfectly straight
        deltaX = distY * (cos( (polledTheta*M_PI) / 180 ));
        deltaY = distY * (sin( (prevTheta*M_PI) / 180 ));
    }
    
    //Add X and Y distance to current values
    currX -= deltaX;
    currY += deltaY;

    prevRight = polledRight;
    prevLeft = polledLeft;
    prevTheta = polledTheta;

}