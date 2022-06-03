#pragma once
#include "OdomRobot.h"
#include "HoloRobot.h"
#include "Simulation.h"
#include "Point.h"
#include "vex.h"

class PeerPursuitRobot : public OdomRobot, HoloRobot {

public:
  PeerPursuitRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back);

  float evaluate(Simulation simulation, float error);
  int findClosestPoint(Point *points, float x, float y, int start, int end);
  bool runPeerPursuit(Point *points, float lookaheadOffset = 0, float kpOffset = 0, float kdOffset = 0);

};