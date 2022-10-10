#include <Arduino.h>
#include <ArduinoJson.h>
#include <json_comms.hpp>
#include <settings.hpp>
#include "chassis.hpp"
#include "scheduler.hpp"

bool ledState = false;

Chassis chassis;
JSONComms comms;
Scheduler feedbackScheduler;

void blink() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void handleDriveMessage(XYDriveMessage message) {
  chassis.setRawMovement(message.x, message.y);
  comms.sendChassisFeedback(Serial, chassis.feedback());
  blink();
}

void sendFeedback() {
  auto feedback = chassis.feedback();
  comms.sendChassisFeedback(Serial, feedback);
}

void setup() {
  Serial.begin(Settings::SerialBaudRate);
  pinMode(LED_BUILTIN, OUTPUT);
  feedbackScheduler.addFunction(sendFeedback, Settings::FeedbackDelayMs);

  comms.setXYDriveMessageCallback(handleDriveMessage);
  chassis.initialize(Settings::ChassisProcessingDelay, Settings::WheelPowerChangePerCycle);
}

void loop() {
  chassis.process();
  comms.tryReadingInput(Serial);
  // feedbackScheduler.process();
  // blink();
}