#include <Arduino.h>
#include "pinout.hpp"
#include "scheduler.hpp"
#include "settings.hpp"
#include "wheels_manager.hpp"

WheelsManager wheelsManager;

void setup() {
  Serial.begin(Settings::SerialBaudRate);
  wheelsManager.initialize(100, 5);
}

void loop() {
  wheelsManager.process();
}