#include "chassis.hpp"

void Chassis::initialize(unsigned long wheelsProcessingDelayMs, unsigned wheelsPowerChangePerCycle) {
  wheels.initialize(wheelsProcessingDelayMs, wheelsPowerChangePerCycle);
}

void Chassis::process() {
  wheels.process();
}

ChassisFeedback::WheelFeedback motorFeedback(BTS7960Ramped const& motor) {
  ChassisFeedback::WheelFeedback feedback{};

  feedback.currentPower = motor.power();
  feedback.targetPower = motor.targetPower();
  feedback.currentDraw = motor.current();

  switch (motor.direction()) {
    case BTS7960::Direction::None:
      feedback.direction = ChassisFeedback::WheelFeedback::Direction::None;
      break;
    case BTS7960::Direction::Forward:
      feedback.direction = ChassisFeedback::WheelFeedback::Direction::Forward;
      break;
    case BTS7960::Direction::Backward:
      feedback.direction = ChassisFeedback::WheelFeedback::Direction::Backward;
      break;
  }

  return feedback;
}

ChassisFeedback Chassis::feedback() const {
  ChassisFeedback feedback{};

  feedback.power = wheels.power();
  feedback.rotation = wheels.rotation();

  feedback.leftFront = motorFeedback(wheels.leftFrontWheel());
  feedback.rightFront = motorFeedback(wheels.rightFrontWheel());
  feedback.leftRear = motorFeedback(wheels.leftRearWheel());
  feedback.rightRear = motorFeedback(wheels.rightRearWheel());

  return feedback;
}

void Chassis::setRawMovement(int power, int rotation) {
  wheels.setPowerAndRotation(power, rotation);
}

