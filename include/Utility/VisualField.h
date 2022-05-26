#pragma once
#include "constants.h"

class VisualField {

public:
  void drawField();

private:
  const int MARGIN = 20;

  int inchesToPixels(float inches);
  int getPixel(float inches);

};