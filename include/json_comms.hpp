#pragma once
#include <ArduinoJson.h>
#include <messages.hpp>

class JSONComms {
 public:
  static constexpr size_t JsonBufferSize = 1024;
  using XYDriveMessageCallbackT = void (*)(XYDriveMessage);

  void tryReadingInput(Stream& stream);
  void sendChassisFeedback(Stream& stream, ChassisFeedback const& feedback);

  void setXYDriveMessageCallback(XYDriveMessageCallbackT callback);

 private:
  XYDriveMessageCallbackT callbackXYDriveMessage = nullptr;
  StaticJsonDocument<JsonBufferSize> jsonDoc;
};