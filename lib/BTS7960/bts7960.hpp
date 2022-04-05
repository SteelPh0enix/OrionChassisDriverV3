#pragma once
#include <stdint.h>
#include "module.hpp"

class BTS7960 : public Module {
 public:
  enum class Direction { None = 0, Forward = 1, Backward = 2 };

  BTS7960() = default;
  BTS7960(uint8_t pwmFPin,
          uint8_t pwmBPin,
          uint8_t directionFPin,
          uint8_t directionBPin,
          uint8_t feedbackFPin,
          uint8_t feedbackBPin);

  void setPins(uint8_t pwmFPin,
               uint8_t pwmBPin,
               uint8_t directionFPin,
               uint8_t directionBPin,
               uint8_t feedbackFPin,
               uint8_t feedbackBPin);

  void setPower(int power);
  void stop();
  void setCurrentSenseLoops(unsigned loops);

  int power() const;
  double current() const;
  Direction direction() const;
  unsigned currentSenseLoops() const;

 private:
  virtual bool internalInitialize();
  void setDirection(Direction direction);
  double calculateCurrent(double analogInput) const;

  uint8_t m_pwmFPin{};
  uint8_t m_pwmBPin{};
  uint8_t m_directionFPin{};
  uint8_t m_directionBPin{};
  uint8_t m_feedbackFPin{};
  uint8_t m_feedbackBPin{};

  int m_power{};
  Direction m_direction{Direction::None};
  unsigned m_currentSenseLoops{10};
};