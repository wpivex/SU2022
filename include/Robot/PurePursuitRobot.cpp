#include "PurePursuitRobot.h"
#include "Utility/PIDController.h"

PurePursuitRobot::PurePursuitRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back): OdomRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back) {

}

float PurePursuitRobot::evaluate(float error) {
  return 0;
}

int PurePursuitRobot::findClosestPoint(Point *points, float x, float y, int start, int end) {
  return 0;
}

bool PurePursuitRobot::runPeerPursuit(Point *points, float lookaheadOffset, float kpOffset, float kdOffset) {
  PIDController pidX = PIDController(0, 0, 0);
  PIDController pidY = PIDController(0, 0, 0);
  PIDController pidRot = PIDController(0, 0, 0);
  PIDController pidFinal = PIDController(0, 0, 0); // for the last point
  
  float xvel = 0 // velocities in inches/second
  float yvel = 0
  float tvel = 0 // angular velocity
  int li = 0 // lookahead index
  int ci = 0 // closest index
  float x = 0;
  float y = 0;
  float theta = 0;

  float errorSum = 0

  int pointsLength = sizeof(points)/sizeof(points[0]);

  while(li != pointsLength - 1 || distanceBetweenPoints(points[pointsLength-1].x, points[pointsLength-1].y, x, y) > STOP_DISTANCE_THRESHOLD) {

    // Find closest waypoint within 5 points of the current waypoint
    ci = this.findClosestPoint(points, x, y, ci, ci + 30);
  
    // Update lookahead distance
    li = ci
    while(li < pointsLength - 1) {
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
    float dtheta = (points[li].theta - theta) % (2*PI)
    if dtheta > PI:
        dtheta -= 2*PI;
    targetTVel = pidRot.tick(dtheta)

    // Update velocities given target velocities, and constrain with acceleration limits
    xvel += clamp(targetXVel - xvel, -MAX_TRANS_ACCEL, MAX_TRANS_ACCEL);
    yvel += clamp(targetYVel - yvel, -MAX_TRANS_ACCEL, MAX_TRANS_ACCEL);
    tvel += clamp(targetTVel - tvel, -MAX_ROT_ACCEL, MAX_ROT_ACCEL);

    // set x, y, and theta velocities
    moveWithComponents(xvel, yvel, tvel);
  }

  return false;
}