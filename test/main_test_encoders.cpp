#include <Arduino.h>
#include <EnableInterrupt.h>
#include "pinout.hpp"
#include "settings.hpp"

static int counter = 0;
static char msgBuffer[1024];

void increaseCounter() {
  counter++;
}

void decreaseCounter() {
  counter--;
}

void setup() {
  enableInterrupt(Pinout::Encoders::Encoder1A, decreaseCounter, CHANGE);
  enableInterrupt(Pinout::Encoders::Encoder1B, increaseCounter, CHANGE);

  enableInterrupt(Pinout::Encoders::Encoder2A, increaseCounter, CHANGE);
  enableInterrupt(Pinout::Encoders::Encoder2B, decreaseCounter, CHANGE);

  enableInterrupt(Pinout::Encoders::Encoder3A, decreaseCounter, CHANGE);
  enableInterrupt(Pinout::Encoders::Encoder3B, increaseCounter, CHANGE);

  enableInterrupt(Pinout::Encoders::Encoder4A, increaseCounter, CHANGE);
  enableInterrupt(Pinout::Encoders::Encoder4B, decreaseCounter, CHANGE);

  Serial.begin(Settings::SerialBaudRate);
}

void loop() {
  snprintf(msgBuffer, 1024, "Counter equals %d\r\n", counter);
  Serial.write(msgBuffer);
  delay(200);
}