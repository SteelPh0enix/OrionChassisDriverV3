#include "bts7960_ramped.hpp"
#include <Arduino.h>
#include "module.hpp"

void BTS7960Ramped::setProcessingDelay(unsigned long delayMs) {
  m_processingDelay = delayMs;
}

void BTS7960Ramped::setPowerRampingIntensity(unsigned pwmValuePerCycle) {
  m_powerRampingIntensity =
      pwmValuePerCycle % Module::PWMResolution<unsigned>();
}

void BTS7960Ramped::setTargetPower(int targetPower) {
  m_targetPower = constrain(targetPower, -Module::PWMResolution<int>(),
                            Module::PWMResolution<int>());
}

void BTS7960Ramped::process() {
  unsigned long const currentTime = millis();
  unsigned long const timeSinceLastRun = currentTime - m_lastRunTimestamp;
  if (timeSinceLastRun > processingDelay()) {
    powerStep();
    m_lastRunTimestamp = currentTime;
  }
}

unsigned long BTS7960Ramped::processingDelay() const {
  return m_processingDelay;
}

unsigned BTS7960Ramped::powerRampingIntensity() const {
  return m_powerRampingIntensity;
}

int BTS7960Ramped::targetPower() const {
  return m_targetPower;
}

bool BTS7960Ramped::isRamping() const {
  return targetPower() != power();
}

void BTS7960Ramped::powerStep() {
  int const powerDifference = targetPower() - power();
  unsigned const absolutePowerDifference = abs(powerDifference);

  if (absolutePowerDifference > 0) {
    int const direction = powerDifference >= 0 ? 1 : -1;
    int const currentPowerStep =
        min(absolutePowerDifference, powerRampingIntensity()) * direction;

    // Serial.print("Current power: ");
    // Serial.print(power());
    // Serial.print(", power step: ");
    // Serial.print(currentPowerStep);

    setPower(power() + currentPowerStep);

    // Serial.print(", new power: ");
    // Serial.println(power());
  }
}
