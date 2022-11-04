#include <Arduino.h>
#include "pinout.hpp"
#include "scheduler.hpp"
#include "settings.hpp"
#include "wheels_manager.hpp"

WheelsManager wheelsManager;
Scheduler scheduler;

enum class TestDirection { None, Forward, Backward } testDirection;

void test_wheels_manager() {
  int targetPower = 0;
  int const maxTargetPower = 500;

  switch (testDirection) {
    case TestDirection::None:
      targetPower = maxTargetPower;
      testDirection = TestDirection::Forward;
      break;
    case TestDirection::Forward:
      if (!wheelsManager.isRamping()) {
        targetPower = -maxTargetPower;
        testDirection = TestDirection::Backward;
      }
      break;
    case TestDirection::Backward:
    if (!wheelsManager.isRamping()) {
      targetPower = maxTargetPower;
      testDirection = TestDirection::Forward;
    }
      break;
  }

  wheelsManager.setPower(targetPower);
}

void print_wheels_manager_info() {
  Serial.print("Target power: ");
  Serial.print(wheelsManager.power());
  Serial.print(", is ramping? ");
  Serial.println(wheelsManager.isRamping() ? "yes" : "no");
}

void setup() {
  Serial.begin(Settings::SerialBaudRate);
  wheelsManager.initialize(50, 5);

  scheduler.addFunction(test_wheels_manager, 8000);
  scheduler.addFunction(print_wheels_manager_info, 200);
}

void loop() {
  scheduler.process();
  wheelsManager.process();
}