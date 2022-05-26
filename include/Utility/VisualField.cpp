#include "VisualField.h"

// Field is 12' x 12', so each tile is 24 inches with 6x6 tiles
// Screen render is 204x204 pixels
int VisualField::inchesToPixels(float inches) {
  return inches * (204.0 / 144.0);
}

int VisualField::getPixel(float inches) {
  return MARGIN + inchesToPixels(inches);
}

void VisualField::drawField() {

  //field from (20,20) to (224, 224)
  // draw 7 rows/cols of lines for 6 tiles
  // 34 pixels per tile
  Brain.Screen.setPenColor(white);
  for (int i = MARGIN; i <= MARGIN + 204; i += 34) {
    Brain.Screen.setPenWidth((i == 20 || i == MARGIN + 24) ? 2 : 1); 
    Brain.Screen.drawLine(MARGIN, i, MARGIN + 204, i); // draw row
    Brain.Screen.drawLine(i, MARGIN, i, MARGIN + 204); // draw col
  }
}