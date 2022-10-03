#pragma once

#include "vex.h"
#include "Drive.h"
#include "Flywheel.h"
#include "Intake.h"
#include "Localization/Localizer.h"
#include "PathFollowing/PathFollower.h"
#include <memory>


class Robot {

public:
    // optional features of robot
    std::unique_ptr<Driveable> drive;
    std::unique_ptr<Localizable> localizer;
    std::unique_ptr<PathFollowable> pathFollower;
    std::unique_ptr<Intakeable> intake;
    std::unique_ptr<Flywheel> flywheel;

};
