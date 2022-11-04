#pragma once

#include "constants.h"
#include "Framework/Driver/Buttons.h"

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
  Brain.Screen.setFont(vex::mono20);
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