#pragma once
#include <string>
#include <queue>
#include "Utility/Buttons.cpp"
#include <cmath>

vex::brain Brain;
vex::competition Competition;
Buttons buttons;


namespace CURRENT {
  const static float OFF = 0.0;
  const static float LOW = 0.1;
  const static float MID = 1.0;
  const static float HIGH = 10.0;
}


const float MAX_VOLTS = 12.0; // maximum volts for vex motors

static const int SCREEN_WIDTH = 480; // Brain screen width
static const int SCREEN_HEIGHT = 240; // Brain screen height

// Given a motor object and a percent from -100 to 100, convert to raw voltage and set motor velocity
static inline void setMotorVelocity(vex::motor m, double percent) {

  vex::directionType d = percent > 0 ? vex::forward : vex::reverse;
  percent = fabs(percent);
  percent = fmin(100, fmax(-100, percent)); // bound between -100 and 100

  m.spin(d, percent / 100.0 * 12.0, vex::voltageUnits::volt);
}

// Bound angle to between -180 and 180
static inline float bound180(float angle) {
  if (angle < -180) angle += 360;
  else if (angle > 180) angle -= 360;
  return angle;
}

// Find the closest angle between two universal angles
static inline float getAngleDiff(float targetAngle, float currentAngle) {
  return bound180(targetAngle - currentAngle);
}

// Given a starting time, return whether timeout (in seconds) has been reached
static inline bool isTimeout(int startTime, float timeout) {
  return timeout != -1 && vex::timer::system() >= startTime + timeout*1000;
}

// log output to controller
template <class ... Args>
static inline void logController(const char *f, Args ... args) {

  Controller1->Screen.clearScreen();
  int row = 1;

  char buffer[200];
  sprintf(buffer, f, args...);

  char* pch = strtok (buffer,"\n");
  while (pch != NULL)
  {
    Controller1->Screen.setCursor(row, 1);
    Controller1->Screen.print(pch);
    pch = strtok (NULL, "\n");
    row++;
  }
}


// log output to brain display the way you would with printf
template <class ... Args>
static inline void log(const char *f, Args ... args) {

  Brain.Screen.clearScreen();
  Brain.Screen.setFont(vex::mono30);
  int row = 1;

  char buffer[200];
  sprintf(buffer, f, args...);

  char* pch = strtok (buffer,"\n");
  while (pch != NULL)
  {
    Brain.Screen.setCursor(row, 1);
    Brain.Screen.print(pch);
    pch = strtok (NULL, "\n");
    row++;
  }
}

// Return the distance between (x1, y1) and (x2, y2)
static inline float distance(float x1, float y1, float x2, float y2) {
  return sqrt( (pow((x1-x2), 2))+(pow((y1-y2), 2)) );
}

// Return the hypotonuse of a right triangle given two sides
static inline float distance(float dx, float dy) {
  return sqrt(dx*dx + dy*dy);
}

// Clamp value between [mn, mx]
static inline float clamp(float value, float mn, float mx) {
  return fmax(mn, fmin(mx, value));
}