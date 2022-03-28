#include "bts7960.hpp"
#include <Arduino.h>

BTS7960::BTS7960(uint8_t pwmFPin,
                 uint8_t pwmBPin,
                 uint8_t directionFPin,
                 uint8_t directionBPin,
                 uint8_t feedbackFPin,
                 uint8_t feedbackBPin) {
  setPins(pwmFPin, pwmBPin, directionFPin, directionBPin, feedbackFPin,
          feedbackBPin);
}
void BTS7960::setPins(uint8_t pwmFPin,
                      uint8_t pwmBPin,
                      uint8_t directionFPin,
                      uint8_t directionBPin,
                      uint8_t feedbackFPin,
                      uint8_t feedbackBPin) {
  m_directionFPin = directionFPin;
  m_directionBPin = directionBPin;
  m_pwmFPin = pwmFPin;
  m_pwmBPin = pwmBPin;
  m_feedbackFPin = feedbackFPin;
  m_feedbackBPin = feedbackBPin;
  pinsHasBeenSet();
}

bool BTS7960::internalInitialize() {
  pinMode(m_feedbackFPin, INPUT);
  pinMode(m_feedbackBPin, INPUT);
  pinMode(m_pwmFPin, OUTPUT);
  pinMode(m_pwmBPin, OUTPUT);
  pinMode(m_directionFPin, OUTPUT);
  pinMode(m_directionBPin, OUTPUT);
  return true;
}

void BTS7960::setDirection(BTS7960::Direction direction) {
  // TODO: Find out why direction settings is not working properly
  // (when setting pins to F LOW, B HIGH or F HIGH B LOW, nothing happens)
  switch (direction) {
    case Direction::None:
      digitalWrite(m_directionFPin, LOW);
      digitalWrite(m_directionBPin, LOW);
      break;
    case Direction::Forward:
      digitalWrite(m_directionFPin, HIGH);
      digitalWrite(m_directionBPin, HIGH);
      break;
    case Direction::Backward:
      digitalWrite(m_directionFPin, HIGH);
      digitalWrite(m_directionBPin, HIGH);
      break;
  }

  m_direction = direction;
}

void BTS7960::stop() {
  setPower(0);
}

void BTS7960::setPower(int power) {
  power = constrain(power, -PWMResolution(), PWMResolution());
  if (power > 0) {
    setDirection(Direction::Forward);
    analogWrite(m_pwmFPin, power);
    analogWrite(m_pwmBPin, 0);
  } else if (power == 0) {
    setDirection(Direction::None);
    analogWrite(m_pwmFPin, 0);
    analogWrite(m_pwmBPin, 0);
  } else {
    setDirection(Direction::Backward);
    analogWrite(m_pwmFPin, 0);
    analogWrite(m_pwmBPin, power * -1);
  }

  m_power = power;
}

int BTS7960::power() const {
  return m_power;
}

BTS7960::Direction BTS7960::direction() const {
  return m_direction;
}

double BTS7960::current() const {
  uint8_t sensorPin{};
  unsigned successfulReads{0};
  double reading{0};

  switch (m_direction) {
    case Direction::None:
      return 0;
    case Direction::Forward:
      sensorPin = m_feedbackFPin;
    case Direction::Backward:
      sensorPin = m_feedbackBPin;
  }

  for (unsigned i = 0; i < m_currentSenseLoops; i++) {
    double tempReading = static_cast<double>(analogRead(sensorPin));
    if (tempReading > 0) {
      reading += tempReading;
      successfulReads++;
    }
  }

  if (successfulReads > 0) {
    return calculateCurrent(reading / successfulReads);
  } else {
    return 0.;
  }
}

double BTS7960::calculateCurrent(double input) const {
  return (VoltsPerADCUnit<double>() * input) * 8.5;
}