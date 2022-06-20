#include <Arduino.h>
#include "pinout.hpp"
#include "settings.hpp"

void setup() {
  Serial.begin(Settings::SerialBaudRate);
}

void loop() {}