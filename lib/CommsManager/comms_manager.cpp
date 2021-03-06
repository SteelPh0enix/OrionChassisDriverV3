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

void CommsManager::setChassisDirectionHandler(ChassisDirectionHandler handler) {
  m_chassisDirectionHandler = handler;
}

size_t CommsManager::createLogMessage(Log const* log, uint8_t* buffer, size_t bufferSize) {
  return createMessage(Log_fields, MessageID::Log, static_cast<void const*>(log), buffer, bufferSize);
}

size_t CommsManager::createChassisFeedbackMessage(ChassisFeedback const* feedback, uint8_t* buffer, size_t bufferSize) {
  return createMessage(ChassisFeedback_fields, MessageID::ChassisFeedback, static_cast<void const*>(feedback), buffer,
                       bufferSize);
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
        if (m_healthCheckHandler != nullptr) {
          m_healthCheckHandler(message);
        }
      }
    }
    case MessageID::ChassisDirection: {
      ChassisDirection message = ChassisDirection_init_zero;
      isParsedCorrectly = pb_decode(&messageStream, ChassisDirection_fields, &message);
      if (isParsedCorrectly) {
        if (m_chassisDirectionHandler != nullptr) {
          m_chassisDirectionHandler(message);
        }
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

size_t CommsManager::createMessage(pb_msgdesc_t const* messageDescriptor,
                                   MessageID messageID,
                                   void const* messageData,
                                   uint8_t* buffer,
                                   size_t bufferLength) {
  buffer[0] = static_cast<uint8_t>(messageID);
  pb_ostream_t messageStream = pb_ostream_from_buffer(buffer + 1, bufferLength - 1);
  pb_encode(&messageStream, messageDescriptor, messageData);
  return messageStream.bytes_written + 1;
}
