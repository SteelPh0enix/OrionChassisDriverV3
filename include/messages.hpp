#pragma once

struct XYDriveMessage {
  int x;
  int y;
};

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