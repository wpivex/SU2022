#pragma once
#include "OdomRobot.h"
#include "HoloRobot.h"
#include "Utility/Point.h"
#include "vex.h"
#include "constants.h"

class PurePursuitRobot : public OdomRobot, HoloRobot {

public:
  PurePursuitRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back);

  float evaluate(float error);
  int findClosestPoint(Point *points, float x, float y, int start, int end);
  bool runPeerPursuit(Point *points, float lookaheadOffset = 0, float kpOffset = 0, float kdOffset = 0);

private:
  float MAX_TRANS_ACCEL;
  float MAX_ROT_ACCEL;

};