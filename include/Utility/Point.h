#pragma once

class Point {

public:
  Point(float _x, float _y, float _theta) {x = _x, y = _y, theta = _theta;};
  Point(float _x, float _y) {Point(_x, _y, 0);};
  float x;
  float y;
  float theta;
};