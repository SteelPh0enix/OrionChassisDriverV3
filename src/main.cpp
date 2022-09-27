#include <Arduino.h>
#include <ArduinoJson.h>
#include <settings.hpp>
#include "wheels_manager.hpp"

bool ledState = false;

WheelsManager wheelsManager;

void blink() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  wheelsManager.initialize(Settings::ChassisProcessingDelay, Settings::WheelPowerChangePerCycle);
}

void loop() {
  wheelsManager.process();
}