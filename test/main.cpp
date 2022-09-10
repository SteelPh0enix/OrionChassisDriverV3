#include <Arduino.h>
#include "comms_manager.hpp"
#include "settings.hpp"
#include "wheels_manager.hpp"

WheelsManager wheelsManager;
CommsManager commsManager;

#define MESSAGE_BUFFER_SIZE 256
uint8_t messageBuffer[MESSAGE_BUFFER_SIZE]{};

bool ledState = false;

void blink() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void sendMessage(uint8_t const* messageBytes, uint16_t messageLength) {
  uint8_t sizeBuffer[2]{};
  sizeBuffer[0] = messageLength & 0xFF;
  sizeBuffer[1] = (messageLength >> 8) & 0xFF;
  Serial.write(sizeBuffer, 2);
  Serial.write(messageBytes, messageLength);
}

void handleHealthCheck(HealthCheck healthCheck) {
  Log log = Log_init_default;
  log.type = Log_Type_INFO;
  strcpy(reinterpret_cast<char*>(log.content), "hello world, this is an example message!");

  size_t const msgLen = CommsManager::createLogMessage(&log, messageBuffer, MESSAGE_BUFFER_SIZE);
  sendMessage(messageBuffer, msgLen);
}

ChassisFeedback_WheelFeedback fetchWheelFeedback(BTS7960Ramped const& wheel, char const* wheelID) {
  ChassisFeedback_WheelFeedback feedback = ChassisFeedback_WheelFeedback_init_zero;

  feedback.current_power = wheel.power();
  feedback.target_power = wheel.targetPower();
  feedback.current_draw = wheel.current();
  feedback.direction = static_cast<ChassisFeedback_WheelFeedback_Direction>(wheel.direction());
  strcpy(feedback.id, wheelID);

  return feedback;
}

ChassisFeedback fetchFeedback() {
  ChassisFeedback feedback = ChassisFeedback_init_zero;

  feedback.chassis_power = wheelsManager.power();
  feedback.chassis_rotation = wheelsManager.rotation();

  feedback.wheels[0] = fetchWheelFeedback(wheelsManager.leftFrontWheel(), "Left Front");
  feedback.wheels[1] = fetchWheelFeedback(wheelsManager.rightFrontWheel(), "Right Front");
  feedback.wheels[2] = fetchWheelFeedback(wheelsManager.leftRearWheel(), "Left Rear");
  feedback.wheels[3] = fetchWheelFeedback(wheelsManager.rightRearWheel(), "Right Rear");

  return feedback;
}

void handleChassisDirection(ChassisDirection direction) {
  wheelsManager.setPowerAndRotation(direction.power, direction.rotation);

  ChassisFeedback feedback = fetchFeedback();
  size_t const msgLen = commsManager.createChassisFeedbackMessage(&feedback, messageBuffer, MESSAGE_BUFFER_SIZE);
  sendMessage(messageBuffer, msgLen);
}

void setup() {
  Serial.begin(Settings::SerialBaudRate);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledState);

  commsManager.setHealthCheckHandler(handleHealthCheck);
  commsManager.setChassisDirectionHandler(handleChassisDirection);

  wheelsManager.initialize(Settings::ChassisProcessingDelay, Settings::WheelPowerChangePerCycle);
}

void loop() {
  if (Serial.available() >= 2) {
    blink();
    Serial.readBytes(messageBuffer, 2);
    size_t const messageLength = (messageBuffer[0] << 8) | messageBuffer[1];
    Serial.readBytes(messageBuffer, messageLength);
    commsManager.processMessage(messageBuffer, messageLength);
  }

  wheelsManager.process();
}