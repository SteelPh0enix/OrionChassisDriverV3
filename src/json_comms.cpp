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

  jsonDoc.clear();
}

void addWheelFeedbackToJson(JsonObject& json, ChassisFeedback::WheelFeedback const& feedback, char const* keyName) {
  JsonObject wheelJson = json.createNestedObject(keyName);
  wheelJson[JsonKey::Feedback::Wheel::CurrentPower] = feedback.currentPower;
  wheelJson[JsonKey::Feedback::Wheel::CurrentDraw] = feedback.currentDraw;
  wheelJson[JsonKey::Feedback::Wheel::Direction] = static_cast<int>(feedback.direction);
  wheelJson[JsonKey::Feedback::Wheel::TargetPower] = feedback.targetPower;
}

void JSONComms::sendChassisFeedback(Stream& stream, ChassisFeedback const& feedback) {
  JsonObject json = jsonDoc.to<JsonObject>();

  // dummy fields, to be filled in future
  json[JsonKey::Feedback::ErrorCode] = 0;
  json[JsonKey::Feedback::ErrorDescription] = "";

  json[JsonKey::Feedback::Power] = feedback.power;
  json[JsonKey::Feedback::Rotation] = feedback.rotation;

  addWheelFeedbackToJson(json, feedback.leftFront, JsonKey::Feedback::LeftFrontWheelPWM);
  addWheelFeedbackToJson(json, feedback.rightFront, JsonKey::Feedback::RightFrontWheelPWM);
  addWheelFeedbackToJson(json, feedback.leftRear, JsonKey::Feedback::LeftRearWheelPWM);
  addWheelFeedbackToJson(json, feedback.rightRear, JsonKey::Feedback::RightRearWheelPWM);

  serializeJson(jsonDoc, stream);
  jsonDoc.clear();
}

void JSONComms::setXYDriveMessageCallback(XYDriveMessageCallbackT callback) {
  callbackXYDriveMessage = callback;
}
