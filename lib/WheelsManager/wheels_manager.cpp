#include "wheels_manager.hpp"
#include "pinout.hpp"

void WheelsManager::initialize() {
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
}

void WheelsManager::setSpeed(int speed) {}

void WheelsManager::setRotation(int rotation) {}

void WheelsManager::process() {}
