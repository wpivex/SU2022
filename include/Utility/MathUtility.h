#include <math.h> 

typedef struct Point {
    float x,y;
} Point;

inline float clamp(float value, float min, float max) {
    return fmin(max, fmax(min, value));
}

inline int sign(double x) {
    if (x >= 0) return 1;
    return -1;
}

inline float hypotenuse(float side1, float side2) {
    return sqrt(side1*side1 + side2*side2);
}

inline float distancePoints(float x1, float y1, float x2, float y2) {
    return hypotenuse(y2-y1, x2-x1);
}

inline float distancePointLine(float pointX, float pointY, float lineX1, float lineY1, float lineX2, float lineY2) {
    float dist = distancePoints(lineX1, lineY1, lineX2, lineY2);
    return fabs((lineX2-lineX1) * (lineY1-pointY) - (lineX1-pointX) * (lineY2-lineY1)) / dist;
}

inline float isPointTouchingLineSegment(float pointX, float pointY, float lineX1, float lineY1, float lineX2, float lineY2, float tolerance) {
    if (lineX1 == lineX2 && lineY1 == lineY2) return false;

    if (distancePointLine(pointX, pointY, lineX1, lineY1, lineX2, lineY2) <= tolerance) {
        
        float lineDistance = distancePoints(lineX1, lineY1, lineX2, lineY2);
        if (distancePoints(pointX, pointY, lineX1, lineY1) < lineDistance && distancePoints(pointX, pointY, lineX2, lineY2) < lineDistance) {
            return true;
        }
    }
    return false;
}

inline Point getPointOnLineClosestToPoint(float pointX, float pointY, float lineX1, float lineY1, float lineX2, float lineY2) {
    float ax = pointX - lineX1;
    float ay = pointY - lineY1;
    float bx = lineX2 - lineX1;
    float by = lineY2 - lineY1;

    float scalar = (ax * bx + ay * by) / (bx * bx + by * by);
    
    return {lineX1 + scalar * bx, lineY1 + scalar * by};

}

// Bound angle to between -180 and 180
inline float bound180(float angle) {
  if (angle < -180) angle += 360;
  else if (angle > 180) angle -= 360;
  return angle;
}

// Find the closest angle between two universal angles
inline float getAngleDiff(float targetAngle, float currentAngle) {
  return bound180(targetAngle - currentAngle);
}
