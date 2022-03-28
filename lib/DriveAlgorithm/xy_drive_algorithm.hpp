#pragma once

class XYDriveAlgorithm {
 public:
  struct Output {
    int left_speed;
    int right_speed;
  };

  // Assuming speed and rotation in ranges -255 : 255
  static Output translate(int speed, int rotation);
};