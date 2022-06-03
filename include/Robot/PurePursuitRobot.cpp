#include "PurePursuitRobot.h"


PurePursuitRobot::PurePursuitRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back): OdomRobot(distBetweenWheels, gyroPort, encoderDiameter,
  left, right,  back), HoloRobot(0,0) {

}

int PurePursuitRobot::findClosestPoint(float x, float y, int start, int end) {
  start = fmax(start, 0);
  end = fmin(end, points.size() - 1);

  int minIndex = start;
  float minDist = distanceBetweenPoints(x, y, points[start].x, points[start].y);
  start += 1;
  // while start < end:
  //     dist = Utility.distance(x, y, points[start].x, points[start].y)
  //     if dist < minDist:
  //         minIndex = start
  //         minDist = dist
  //     start += 1

  return minIndex;
}

void PurePursuitRobot::drawTrajectory(VisualField f) {

  for (Point p : points) {
    f.drawPoint(f.getX(p.x), f.getY(p.y));
  }  

}
/*
bool PurePursuitRobot::runPurePursuit() {
  PID pidX = PID(0, 0, 0);
  PID pidY = PID(0, 0, 0);
  PID pidRot = PID(0, 0, 0);
  PID pidFinal = PID(0, 0, 0); // for the last point
  
  float xvel = 0; // velocities in inches/second
  float yvel = 0;
  float tvel = 0; // angular velocity
  int li = 0; // lookahead index
  int ci = 0; // closest index
  float x = 0;
  float y = 0;
  float theta = 0;

  float errorSum = 0;

  while(li != points.size - 1 || distanceBetweenPoints(points[points.size-1].x, points[points.size-1].y, x, y) > STOP_DISTANCE_THRESHOLD) {

    // Find closest waypoint within 5 points of the current waypoint
    ci = this.findClosestPoint(points, x, y, ci, ci + 30);
  
    // Update lookahead distance
    li = ci
    while(li < points.size - 1 && distanceBetweenPoints(points[li].x, points[li].y, points[ci].x, points[ci].y) < lookahead) {
      li += 1;
    }

    // Calculate target velocities
    float targetXVel = pidX.tick(points[li].x - x);
    float targetYVel = pidY.tick(points[li].y - y);

    // Constrain maximum robot speed
    float mag = hypo(targetXVel, targetYVel);
    float scalar = Math.min(1, MAX_SPEED / mag);
    targetXVel *= scalar;
    targetYVel *= scalar;
      
    // Calculate heading delta (turn the fastest way)
    float dtheta = (points[li].theta - theta) % (2*PI);
    if(dtheta > PI) {
      dtheta -= 2*PI;
    }
    targetTVel = pidRot.tick(dtheta);

    // set x, y, and theta velocities
    moveWithComponents(xvel, yvel, tvel);
  }

  return false;
}

std::vector<Point> loadPointsFromCSV(std::string filepath) {
  int byteLen = Brain.SDcard.size(filename.c_str()) + 10; // just in case this is off for some reason
  unsigned char* c = new unsigned char[byteLen];
  Brain.SDcard.loadfile(filename.c_str(), c, byteLen);

  int lineCount = 0;
  for(int i=0; i<byteLen; i++) { if(i != byteLen - 1 && c[i] == 13 && c[i+1] == 10) { lineCount++; } }
  std::vector<Point> points;
  points.reserve(lineCount-3);
  for(int i = 0; i < lineCount - 3; ++i) { points.push_back(Point()); }

  // TODO: read in lookahead, p, and d
  std::string s = "";
  int currInd = 0;
  for(int i=0; i<byteLen; i++) {
    s += c[i];
    if(i != byteLen - 1 && c[i] == 13 && c[i+1] == 10) {
      int commaIndex1 = s.find(",");
      int commaIndex2 = s.find(commaIndex1+1, s.end(), ",");
      points[currInd].x = atof(s.substr(0, commaIndex1).c_str());
      points[currInd].y = atof(s.substr(commaIndex1 + 1, commaIndex2 - commaIndex1 + 1).c_str());
      points[currInd].theta = atof(s.substr(commaIndex2 + 1, s.length() - commaIndex2 + 1).c_str());
      currInd++;
      s = "";
    }
  }
  return points;
}*/