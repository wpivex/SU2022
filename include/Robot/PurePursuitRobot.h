#pragma once
#include "HoloRobot.cpp"
#include "Utility/Point.h"
#include "vex.h"
#include "constants.h"
#include "Utility/VisualField.cpp"
#include "Utility/PIDController.cpp"

class PurePursuitRobot : public HoloRobot {

public:
  PurePursuitRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back);

  std::vector<std::vector<float>> init();

  int findClosestPoint(float x, float y, int start, int end);
  bool runPurePursuit();
  Point* loadPointsFromCSV(std::string filepath);

  void drawTrajectory(VisualField *f);

private:
  std::vector<Point> points;
  float MAX_TRANS_ACCEL;
  float MAX_ROT_ACCEL;
  int lookahead;

};