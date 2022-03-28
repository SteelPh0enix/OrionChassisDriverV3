#pragma once
#include "bts7960.hpp"

class WheelsManager {
 public:
    void initialize();
    void setSpeed(int speed);
    void setRotation(int rotation);
    void process();
 private:

   int m_speed{0};
   int m_rotation{0};

   BTS7960 m_leftFrontWheel{};
   BTS7960 m_leftRearWheel{};
   BTS7960 m_rightFrontWheel{};
   BTS7960 m_rightRearWheel{};
};