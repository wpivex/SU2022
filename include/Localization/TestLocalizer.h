#pragma once

#include "LocalizerInterface.h"

class TestLocalizer : public LocalizerInterface {
    float getFieldX() override {}
    float getFieldY() override {}
    float getFieldHeading() override {}
};