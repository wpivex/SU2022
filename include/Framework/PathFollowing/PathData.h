#pragma once

#include <vector>

typedef struct Waypoint {
    float x, y;
} Waypoint;


class PathData {

public:

    std::vector<Waypoint>& get(int index) { return path.at(index); }
    int size() { return path.size(); }

protected:

    std::vector<std::vector<Waypoint>> path;

};