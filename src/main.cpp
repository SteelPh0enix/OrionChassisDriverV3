#include <Arduino.h>
#include <ArduinoJson.h>
#include <settings.hpp>
#include "chassis.hpp"

bool ledState = false;

Chassis chassis;

void blink() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void setup() {
  Serial.begin(Settings::SerialBaudRate);
  pinMode(LED_BUILTIN, OUTPUT);

  chassis.initialize(Settings::ChassisProcessingDelay, Settings::WheelPowerChangePerCycle);
}

void loop() {
  chassis.process();
}