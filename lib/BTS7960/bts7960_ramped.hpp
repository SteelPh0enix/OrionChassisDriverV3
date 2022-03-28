#pragma once
#include "bts7960.hpp"

class BTS7960Ramped : public BTS7960 {
 public:
  void setProcessingDelay(unsigned long delayMs);
  void setPowerRampingIntensity(unsigned pwmValuePerCycle);
  void setTargetPower(int targetPower);

  unsigned long processingDelay() const;
  unsigned powerRampingIntensity() const;
  int targetPower() const;
  bool isRamping() const;

  void process();

 private:
  void powerStep();

  int m_targetPower{};
  unsigned long m_lastRunTimestamp{};
  unsigned long m_processingDelay{};
  unsigned m_powerRampingIntensity{};
};