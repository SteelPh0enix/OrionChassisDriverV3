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
  // Serial.print("Message length: ");
  // Serial.println(messageLength);
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