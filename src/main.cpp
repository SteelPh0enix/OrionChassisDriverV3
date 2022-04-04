#include <Arduino.h>
#include "comms_manager.hpp"
#include "settings.hpp"
#include "wheels_manager.hpp"


WheelsManager wheelsManager;
CommsManager commsManager;

#define MESSAGE_BUFFER_SIZE 1024
uint8_t messageBuffer[MESSAGE_BUFFER_SIZE]{};

bool ledState = false;

void blink() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void handleHealthCheck(HealthCheck healthCheck) {}

void setup() {
  Serial.begin(Settings::SerialBaudRate);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledState);

  commsManager.setHealthCheckHandler(handleHealthCheck);

  wheelsManager.initialize(100, 5);
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