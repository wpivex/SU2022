#pragma once
#include "FieldGraphics.h"
#include "vex.h"

// Field is 12' x 12', so each tile is 24 inches with 6x6 tiles
// Screen render is 204x204 pixels
int FieldGraphics::inchesToPixels(float inches) {
  return inches * (204.0 / 144.0);
}

// in this case, (0,0) in inches is the bottom left corner of hte field
int FieldGraphics::getX(float inches, bool isTileUnits) {
  if (isTileUnits) inches *= 24;
  return MARGIN + inchesToPixels(inches);
}

int FieldGraphics::getY(float inches, bool isTileUnits) {
  if (isTileUnits) inches *= 24;
  return MARGIN + inchesToPixels(inches);
}

void FieldGraphics::drawLine(float x1, float y1, float x2, float y2, bool isTileUnits) {
  Brain.Screen.drawLine(getX(x1, isTileUnits), getY(y1, isTileUnits), getX(x2, isTileUnits), getY(y2, isTileUnits));
}

void FieldGraphics::drawPoint(float x, float y, bool isTileUnits) {
  Brain.Screen.drawPixel(getX(x, isTileUnits), getY(y, isTileUnits));
}

vex::color vexblue(37, 75, 143);
vex::color vexred(204, 57, 58);
vex::color vexyellowline(225, 167, 102);

void FieldGraphics::drawField() {

  Brain.Screen.clearScreen();

  //field from (20,20) to (224, 224)
  // draw 7 rows/cols of lines for 6 tiles
  // 34 pixels per tile
  Brain.Screen.setPenColor(vex::white);
  for (int i = MARGIN; i <= MARGIN + 204; i += 34) {
    Brain.Screen.setPenWidth((i == 20 || i == MARGIN + 24) ? 2 : 1); 
    Brain.Screen.drawLine(MARGIN, i, MARGIN + 204, i); // draw row
    Brain.Screen.drawLine(i, MARGIN, i, MARGIN + 204); // draw col
  }

  // draw bumpers
  Brain.Screen.setPenWidth(4);
  Brain.Screen.setPenColor(vexblue);
  drawLine(1, 2, 2, 2, true);
  drawLine(2, 2, 2, 1, true);
  Brain.Screen.setPenColor(vexred);
  drawLine(4, 5, 4, 4, true);
  drawLine(4, 4, 5, 4, true);

  // draw mid line
  Brain.Screen.setPenColor(vexyellowline);
  Brain.Screen.setPenWidth(5);
  drawLine(0, 6, 6, 0, true);


}