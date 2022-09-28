#pragma once
#include "messages.hpp"
#include "wheels_manager.hpp"

class Chassis {
 public:
  void initialize(unsigned long wheelsProcessingDelayMs, unsigned wheelsPowerChangePerCycle);
  void process();

  ChassisFeedback feedback() const;
  void setRawMovement(int power, int rotation);

 private:
  WheelsManager wheels;
};