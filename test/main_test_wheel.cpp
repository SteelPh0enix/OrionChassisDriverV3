#include <Arduino.h>
#include "pinout.hpp"
#include "scheduler.hpp"
#include "settings.hpp"
#include "wheels_manager.hpp"

BTS7960Ramped wheel;
Scheduler scheduler;

enum class TestDirection { None, Forward, Backward } testDirection;

void test_wheels_manager() {
  int targetPower = 0;
  int const maxTargetPower = 100;

  switch (testDirection) {
    case TestDirection::None:
      targetPower = maxTargetPower;
      testDirection = TestDirection::Forward;
      break;
    case TestDirection::Forward:
      if (!wheel.isRamping()) {
        targetPower = -maxTargetPower;
        testDirection = TestDirection::Backward;
      }
      break;
    case TestDirection::Backward:
      if (!wheel.isRamping()) {
        targetPower = maxTargetPower;
        testDirection = TestDirection::Forward;
      }
      break;
  }

  wheel.setTargetPower(targetPower);
}

void print_wheels_manager_info() {
  Serial.print("Target power: ");
  Serial.print(wheel.targetPower());
  Serial.print(", is ramping? ");
  Serial.println(wheel.isRamping() ? "yes" : "no");
}

void setup() {
  Serial.begin(Settings::SerialBaudRate);

  // wheel.setPins(Pinout::WheelLF::PWMF, Pinout::WheelLF::PWMB,
  //               Pinout::WheelLF::DirectionF, Pinout::WheelLF::DirectionB,
  //               Pinout::WheelLF::FeedbackF, Pinout::WheelLF::FeedbackB);

  // wheel.setPins(Pinout::WheelLR::PWMF, Pinout::WheelLR::PWMB,
  // Pinout::WheelLR::DirectionF, Pinout::WheelLR::DirectionB,
  // Pinout::WheelLR::FeedbackF, Pinout::WheelLR::FeedbackB);

  // wheel.setPins(Pinout::WheelRF::PWMF, Pinout::WheelRF::PWMB,
  // Pinout::WheelRF::DirectionF, Pinout::WheelRF::DirectionB,
  // Pinout::WheelRF::FeedbackF, Pinout::WheelRF::FeedbackB);

  wheel.setPins(Pinout::WheelRR::PWMF, Pinout::WheelRR::PWMB,
                Pinout::WheelRR::DirectionF, Pinout::WheelRR::DirectionB,
                Pinout::WheelRR::FeedbackF, Pinout::WheelRR::FeedbackB);

  wheel.setPowerRampingIntensity(5);
  wheel.setProcessingDelay(200);

  scheduler.addFunction(test_wheels_manager, 10000);
  scheduler.addFunction(print_wheels_manager_info, 200);
}

void loop() {
  scheduler.process();
  wheel.process();
}