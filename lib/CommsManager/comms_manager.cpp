#include "comms_manager.hpp"
#include "pb_decode.h"
#include "pb_encode.h"

#include <Arduino.h>

CommsManager::ParsingResult CommsManager::processMessage(uint8_t const* buffer, size_t messageLength) {
  if (buffer == nullptr) {
    return ParsingResult::INVALID_BUFFER;
  }

  if (messageLength < 1) {
    return ParsingResult::BUFFER_TOO_SMALL;
  }

  MessageID const messageID = static_cast<MessageID>(buffer[0]);
  uint8_t const* messageData = messageLength > 1 ? &buffer[1] : nullptr;

  return parseMessageAndCallHandler(messageData, messageLength - 1, messageID);
}

void CommsManager::setHealthCheckHandler(HealthCheckHandler handler) {
  m_healthCheckHandler = handler;
}

bool CommsManager::createLogMessage(Log const& log, uint8_t* buffer, size_t bufferSize) {
  pb_ostream_t messageStream = pb_ostream_from_buffer(buffer, bufferSize);
  return pb_encode(&messageStream, Log_fields, &log);
}

CommsManager::ParsingResult CommsManager::parseMessageAndCallHandler(uint8_t const* messageData,
                                                                     size_t messageLength,
                                                                     MessageID messageID) {
  bool isParsedCorrectly = false;
  pb_istream_t messageStream = pb_istream_from_buffer(messageData, messageLength);

  switch (messageID) {
    case MessageID::HealthCheck: {
      HealthCheck message = HealthCheck_init_zero;
      isParsedCorrectly = pb_decode(&messageStream, HealthCheck_fields, &message);
      if (isParsedCorrectly) {
        m_healthCheckHandler(message);
      }
    }
    default:
      return ParsingResult::INVALID_ID;
  }

  if (isParsedCorrectly) {
    return ParsingResult::OK;
  }

  return ParsingResult::PARSING_ERROR;
}
