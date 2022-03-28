#include <Arduino.h>
#include "settings.hpp"
#include "pinout.hpp"
#include "scheduler.hpp"
#include "wheels_manager.hpp"

WheelsManager wheelsManager;

void setup() {
  Serial.begin(Settings::SerialBaudRate);
  wheelsManager.initialize();
}

void loop() {
  wheelsManager.process();
}