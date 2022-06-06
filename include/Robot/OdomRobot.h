#pragma once
#include "BaseRobot.cpp"

class OdomRobot : virtual public BaseRobot {

public:
  OdomRobot(float distBetweenWheels, int32_t gyroPort, float encoderDiamter, triport::port left, triport::port right, triport::port back);

  const float ENCODER_DIAMETER;
  encoder leftEncoder;
  encoder rightEncoder;
  encoder midEncoder;

  void tickOdom();

  float getLeftEncoderAbsolute();
  float getRightEncoderAbsolute();
  float getMidEncoderAbsolute();
  void resetEncoderDistance() override;
  float getLeftEncoderDistance() override;
  float getMidEncoderDistance() override;
  float getRightEncoderDistance() override;

private:

  float absoluteX = 0, absoluteY = 0;
  float recordedL = 0, recordedR = 0, recordedM = 0, recordedTheta = 0;
  float relativeL = 0, relativeR = 0;

};