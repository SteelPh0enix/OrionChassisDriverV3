#include <Arduino.h>
#include <ArduinoJson.h>
#include <json_comms.hpp>
#include <settings.hpp>
#include "chassis.hpp"

bool ledState = false;

Chassis chassis;
JSONComms comms;

void blink() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void handleDriveMessage(XYDriveMessage message) {
  chassis.setRawMovement(message.x, message.y);
}

void setup() {
  Serial.begin(Settings::SerialBaudRate);
  pinMode(LED_BUILTIN, OUTPUT);

  comms.setXYDriveMessageCallback(handleDriveMessage);

  chassis.initialize(Settings::ChassisProcessingDelay, Settings::WheelPowerChangePerCycle);
}

void loop() {
  chassis.process();
  comms.tryReadingInput(Serial);
  blink();
}