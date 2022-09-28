#pragma once
#include "wheels_manager.hpp"

struct ChassisFeedback {
  struct MotorFeedback {
    int currentPower;
    int targetPower;
    enum class Direction { None = 0, Forward = 1, Backward = -1 } direction;
    double currentDraw;
  } leftFront, rightFront, leftRear, rightRear;

  int power;
  int rotation;
};

class Chassis {
 public:
  void initialize(unsigned long wheelsProcessingDelayMs, unsigned wheelsPowerChangePerCycle);
  void process();

  ChassisFeedback feedback() const;
  void setRawMovement(int power, int rotation);

 private:
  WheelsManager wheels;
};