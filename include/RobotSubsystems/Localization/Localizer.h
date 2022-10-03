#pragma once

class Localizable {

public:

    // Get current x and y position on the field in inches
    virtual float getFieldX() = 0;
    virtual float getFieldY() = 0;

    // Get the heading of the field relative to the field in radians
    virtual float getFieldHeading() = 0;

};