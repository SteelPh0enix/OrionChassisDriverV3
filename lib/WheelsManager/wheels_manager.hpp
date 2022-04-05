#pragma once
#include "bts7960_ramped.hpp"

class WheelsManager {
 public:
  void initialize(unsigned long processingDelayMs, unsigned powerChangePerCycle);

  // The internal algorithm will translate power and rotation (in range -255 to
  // 255) and rotation to wheel power
  void setPower(int power);
  void setRotation(int rotation);
  void setPowerAndRotation(int power, int rotation);

  // Processing delay tells how long is the delay between actual processing
  // calls.
  // Ramping speed tells how much the power is increased (in absolute units,
  // from 0 to 255) every processing call.
  // Longer processing delay and lower ramping speed = it'll take longer for
  // motor drivers to achieve requested power.
  // Adjust accordingly to prevent current spikes that could kill motor drivers
  // or MCU
  void setProcessingDelay(unsigned long milliseconds);
  void setRampingSpeed(unsigned powerChangePerCycle);

  int power() const;
  int rotation() const;
  unsigned long processingDelay() const;
  unsigned rampingSpeed() const;
  bool isRamping() const;

  BTS7960Ramped const& leftFrontWheel() const;
  BTS7960Ramped const& rightFrontWheel() const;
  BTS7960Ramped const& leftRearWheel() const;
  BTS7960Ramped const& rightRearWheel() const;

  // call this in `loop()` function, make sure it runs as often as possible to
  // prevent lags
  void process();

 private:
  int m_power{};
  int m_rotation{};
  unsigned long m_processingDelay{};
  unsigned m_powerChangePerCycle{};

  void recalculateWheelsPower();

  BTS7960Ramped m_leftFrontWheel{};
  BTS7960Ramped m_leftRearWheel{};
  BTS7960Ramped m_rightFrontWheel{};
  BTS7960Ramped m_rightRearWheel{};
};