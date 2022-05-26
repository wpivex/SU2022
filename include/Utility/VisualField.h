#pragma once
#include "constants.h"

class VisualField {

public:
  void drawField();

private:
  const int MARGIN = 20;

  int inchesToPixels(float inches);
  int getX(float inches, bool isTileUnits = false);
  int getY(float inches, bool isTileUnits = false);
  void drawLine(float x1, float y1, float x2, float y2, bool isTileUnits = false);

};