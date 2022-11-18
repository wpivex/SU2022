

#pragma once
#include "../constants.h"

class FieldGraphics {

public:
  void drawField();
  
  int getX(float inches, bool isTileUnits = false);
  int getY(float inches, bool isTileUnits = false);

private:

    int inchesToPixels(float inches);

    void drawLine(float x1, float y1, float x2, float y2, bool isTileUnits = false);
    void drawPoint(float x, float y, bool isTileUnits = false);

  const int MARGIN = 20;


};