#pragma once
#include "settings.hpp"
#include "module.hpp"

class XYDriveAlgorithm {
 public:
  struct Output {
    int left_speed;
    int right_speed;
  };

  static constexpr int SetPowerLimit = Settings::WheelPowerLimit;
  static constexpr int OutputPowerLimit = Module::PWMResolution<int>();

  // Assuming speed and rotation in ranges -1000 : 1000
  static Output translate(int speed, int rotation);
};