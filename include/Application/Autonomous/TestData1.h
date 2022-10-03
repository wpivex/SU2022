#pragma once

#include "Framework/PathFollowing/PathData.h"

class TestData1 : public PathData {

public:

    TestData1() {

        path = {
            {
                {1,2},
                {3,4}
            },
            {
                {5,6},
                {7,8}
            }
        };

    }

};