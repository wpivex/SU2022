#include "vex.h"
#include "Utility/TrapezoidController.cpp"
#include "Utility/PIDController.cpp"
#include "Utility/VisualGraph.cpp"
#include "Utility/Buttons.cpp"

using namespace vex;

class BaseRobot {

public:

  BaseRobot(float distBetweenWheels, int32_t gyroPort);

  const float DIST_BETWEEN_WHEELS;

  inertial gyroSensor;

  // Teleop
  virtual void teleop() = 0;
  void basicDriveTeleop();

  // Encoders
  virtual void resetEncoderDistance() = 0;
  virtual float getLeftEncoderDistance() = 0;
  virtual float getRightEncoderDistance() = 0;
  float getEncoderDistance() {return (getLeftEncoderDistance() + getRightEncoderDistance()) / 2;}
  virtual float distanceToDegrees(float distInches) = 0;
  virtual float degreesToDistance(float distDegrees) = 0;

  // Angles/Gyro
  float getAngle();
  void calibrateGyroBlocking();
  void possiblyResetGyro(float targetAngle, float angleTolerance = 10);

  // Basic Motor Control
  void setMotorVelocity(motor m, directionType d, double percent);
  virtual void setLeftVelocity(directionType d, double percent) = 0;
  virtual void setRightVelocity(directionType d, double percent) = 0;
  virtual void stopLeft() = 0;
  virtual void stopRight() = 0;
  void stopDrive() {stopLeft(); stopRight(); }
  virtual void setBrakeType(brakeType b) = 0;
  virtual float getDriveCurrent() = 0;

  // Drive Straight & Variations
  void goForwardTimed(float duration, float speed);
  void goFightBackwards(float currThresh);

  // Curving Functions
  void goCurve(float distInches, float maxSpeed, float turnPercent, float rampUpFrames, float slowDownInches, float endSlowInches = 0,
    bool stopAfter = true, float slowMinSpeed = 12);
  void goRadiusCurve(float radius, float circProportion, bool curveDirection, float maxSpeed, int rampUpFrames, 
    float slowDownInches, bool stopAfter = true, float timeout = 5);
    void goTurnFastU(float universalAngleDegrees, int direction, float speed, bool stopAfter = false);


protected:

  void goForwardU_Abstract(float K_P, float distInches, float maxSpeed, float universalAngle, float rampUpFrames, float slowDownInches,
      float endSlowInches, bool stopAfter, float startSpeed, float stopSpeed, float timeout = 10);
  void goTurnU_Abstract(float KP, float KI, float KD, float TOLERANCE, float REPEATED, float MINUMUM,
      float universalAngleDegrees, int direction = 0, bool stopAfter = true, float timeout = 5, float maxSpeed = 75);

  // Vision
  void goVision_Abstract(float K_P, float MIN_SPEED, int32_t CAMERA_PORT, float distInches, float speed, Goal goal,
    float rampUpFrames, float slowDownInches, float endSlowInches = 0, bool stopAfter = true, float timeout = 5);
  void goAlignVision_Abstract(float K_P, float K_I, float K_D, float TOLERANCE, float REPEATED, float MINIMUM, int32_t CAMERA_PORT, 
    Goal goal, float timeout = 5, bool stopAfter = true);
  
};