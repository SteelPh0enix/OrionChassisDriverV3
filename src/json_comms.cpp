#include <json_comms.hpp>
#include <json_keys.hpp>

bool jsonContainsXYDriveMessage(JsonObject const& json) {
  return (json.containsKey(JsonKey::Input::RoverRotation) && json.containsKey(JsonKey::Input::RoverSpeed));
}

bool validateJsonXYDriveMessage(JsonObject const& json) {
  return (json[JsonKey::Input::RoverRotation].is<int>() && json[JsonKey::Input::RoverSpeed].is<int>());
}

XYDriveMessage getXYDriveMessageFromDoc(JsonObject const& json) {
  XYDriveMessage msg;

  msg.x = json[JsonKey::Input::RoverSpeed].as<int>();
  msg.y = json[JsonKey::Input::RoverRotation].as<int>();

  return msg;
}

void JSONComms::tryReadingInput(Stream& stream) {
  DeserializationError result = deserializeJson(jsonDoc, stream);

  if (!result) {
    return;
  }

  JsonObject json = jsonDoc.as<JsonObject>();

  if (jsonContainsXYDriveMessage(json)) {
    if (validateJsonXYDriveMessage(json)) {
      XYDriveMessage msg = getXYDriveMessageFromDoc(json);
      if (callbackXYDriveMessage != nullptr) {
        callbackXYDriveMessage(msg);
      }
    }
  }
}

void JSONComms::sendChassisFeedback(ChassisFeedback const& feedback) {}

void JSONComms::setXYDriveMessageCallback(XYDriveMessageCallbackT callback) {}
