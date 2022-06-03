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

  int findClosestPoint(std::vector<Point> *points, float x, float y, int start, int end);
  bool runPurePursuit(std::vector<Point> *points);
  Point* loadPointsFromCSV(std::string filepath);

private:
  float MAX_TRANS_ACCEL;
  float MAX_ROT_ACCEL;
  int lookahead;

};