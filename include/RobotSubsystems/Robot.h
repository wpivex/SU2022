#pragma once

#include "vex.h"
#include "Drive.h"
#include "Flywheel.h"
#include "Intake.h"
#include "Localization/Localizer.h"
#include "PathFollowing/PathFollower.h"


class Robot {

public:
    // optional features of robot
    Driveable* drive;
    Localizable* localizer;
    PathFollowable* pathFollower;
    Intakeable* intake;
    Flywheel* flywheel;

};
