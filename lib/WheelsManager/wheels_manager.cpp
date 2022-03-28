#include "wheels_manager.hpp"
#include "pinout.hpp"
#include "xy_drive_algorithm.hpp"

void WheelsManager::initialize(unsigned long processingDelayMs,
                               unsigned powerChangePerCycle) {
  m_leftFrontWheel.setPins(
      Pinout::WheelLF::PWMF, Pinout::WheelLF::PWMB, Pinout::WheelLF::DirectionF,
      Pinout::WheelLF::DirectionB, Pinout::WheelLF::FeedbackF,
      Pinout::WheelLF::FeedbackB);
  m_leftRearWheel.setPins(
      Pinout::WheelLR::PWMF, Pinout::WheelLR::PWMB, Pinout::WheelLR::DirectionF,
      Pinout::WheelLR::DirectionB, Pinout::WheelLR::FeedbackF,
      Pinout::WheelLR::FeedbackB);
  m_rightFrontWheel.setPins(
      Pinout::WheelRF::PWMF, Pinout::WheelRF::PWMB, Pinout::WheelRF::DirectionF,
      Pinout::WheelRF::DirectionB, Pinout::WheelRF::FeedbackF,
      Pinout::WheelRF::FeedbackB);
  m_rightRearWheel.setPins(
      Pinout::WheelRR::PWMF, Pinout::WheelRR::PWMB, Pinout::WheelRR::DirectionF,
      Pinout::WheelRR::DirectionB, Pinout::WheelRR::FeedbackF,
      Pinout::WheelRR::FeedbackB);

  // Initialize processing delay and ramping speed with default values
  setProcessingDelay(processingDelayMs);
  setRampingSpeed(powerChangePerCycle);
}

void WheelsManager::setPower(int power) {
  // m_power = constrain(power, -255, 255);
  m_power = power;
  recalculateWheelsPower();
}

void WheelsManager::setRotation(int rotation) {
  m_rotation = constrain(rotation, -255, 255);
  recalculateWheelsPower();
}

void WheelsManager::setProcessingDelay(unsigned long milliseconds) {
  m_leftFrontWheel.setProcessingDelay(milliseconds);
  m_leftRearWheel.setProcessingDelay(milliseconds);
  m_rightFrontWheel.setProcessingDelay(milliseconds);
  m_rightRearWheel.setProcessingDelay(milliseconds);
}

void WheelsManager::setRampingSpeed(unsigned powerChangePerCycle) {
  m_leftFrontWheel.setPowerRampingIntensity(powerChangePerCycle);
  m_leftRearWheel.setPowerRampingIntensity(powerChangePerCycle);
  m_rightFrontWheel.setPowerRampingIntensity(powerChangePerCycle);
  m_rightRearWheel.setPowerRampingIntensity(powerChangePerCycle);
}

int WheelsManager::power() const {
  return m_power;
}

int WheelsManager::rotation() const {
  return m_rotation;
}

unsigned long WheelsManager::processingDelay() const {
  return m_processingDelay;
}

unsigned WheelsManager::rampingSpeed() const {
  return m_powerChangePerCycle;
}

bool WheelsManager::isRamping() const {
  return m_leftFrontWheel.isRamping() || m_leftRearWheel.isRamping() ||
         m_rightFrontWheel.isRamping() || m_rightRearWheel.isRamping();
}

void WheelsManager::process() {
  m_leftFrontWheel.process();
  m_leftRearWheel.process();
  m_rightFrontWheel.process();
  m_rightRearWheel.process();
}

void WheelsManager::recalculateWheelsPower() {
  auto const wheelsTargetPower =
      XYDriveAlgorithm::translate(power(), rotation());
  
  Serial.print("Set power: ");
  Serial.print(power());
  Serial.print(", Left power target: ");
  Serial.print(wheelsTargetPower.left_speed);
  Serial.print(", Right power target: ");
  Serial.println(wheelsTargetPower.right_speed);

  Serial.println("Left front:");
  m_leftFrontWheel.setTargetPower(wheelsTargetPower.left_speed);
  Serial.println("Left rear:");
  m_leftRearWheel.setTargetPower(wheelsTargetPower.left_speed);
  Serial.println("Right front:");
  m_rightFrontWheel.setTargetPower(wheelsTargetPower.right_speed);
  Serial.println("Right rear:");
  m_rightRearWheel.setTargetPower(wheelsTargetPower.right_speed);
}