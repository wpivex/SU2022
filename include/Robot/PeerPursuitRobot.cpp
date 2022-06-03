#include "PeerPursuitRobot.h"

PeerPursuitRobot::PeerPursuitRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back): OdomRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiameter,
 triport::port left, triport::port right, triport::port back) {

}

float PeerPursuitRobot::evaluate(Simulation simulation, float error) {
  return 0;
}

int PeerPursuitRobot::findClosestPoint(Point *points, float x, float y, int start, int end) {
  return 0;
}

bool PeerPursuitRobot::runPeerPursuit(Point *points, float lookaheadOffset, float kpOffset, float kdOffset) {
  return false;
}