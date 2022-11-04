#pragma once

class Localizable {

public:

    // Get current x and y position on the field in inches
    virtual float getX() = 0;
    virtual float getY() = 0;

    // Get the heading of the field relative to the field in radians
    virtual float getHeading() = 0;
    virtual void updatePositionTask() = 0;
};