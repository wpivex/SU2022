#pragma once
#include "Algorithms/FixedRingQueue.h"
#include <vector>
#include "vex.h"

using namespace vex;

class VisualGraph {

  public:
  VisualGraph(float minY, float maxY, int numMarkersY, int sizeRingQueue, int numFunctions = 1);
  void configureAutomaticDisplay(int interval = 1);
  void push(float dataPoint, int func = 0);
  void display();

  private:
  float minY, maxY;
  int numMarkersX, numMarkersY, numX;
  int displayInterval = -1;
  int xi = 0;
  std::vector<RingQueue*> data;
  int valueToY(float value);
  int offset;
  std::vector<color> lineColors;
  // void displayFunction(std::function<int()> func, vex::color col = black);

};