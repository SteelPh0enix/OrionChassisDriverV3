#include <Arduino.h>
#include "settings.hpp"
#include "wheels_manager.hpp"

WheelsManager wheelsManager;

constexpr size_t MessageBufferSize{10};
uint8_t messageBuffer[MessageBufferSize];

bool ledState = false;

void blink() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void setup() {
  Serial.begin(Settings::SerialBaudRate);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledState);
  wheelsManager.initialize(100, 5);
}

void loop() {
  if (Serial.available() >= 6) {
    Serial.readBytes(messageBuffer, 6);
    unsigned const header = (messageBuffer[1] << 8) | messageBuffer[0];

    if (header == 0x2137) {
      Serial.write(messageBuffer, 6);
      blink();

      int power =
          static_cast<int>((messageBuffer[3] << 8) | messageBuffer[2]) - 1000;
      int rotation =
          static_cast<int>((messageBuffer[5] << 8) | messageBuffer[4]) - 1000;

      wheelsManager.setPowerAndRotation(power, rotation);
    }
  }

  wheelsManager.process();
}