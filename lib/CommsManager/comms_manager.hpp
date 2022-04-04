#pragma once

#include "Chassis.pb.h"

/*
  EXPECTED MESSAGE FORMAT:
  | message data length (2B) | message ID (1B) | message data |
  message data length is little endian (LSB first), and does not include itself
  and message ID length
*/

class CommsManager {
 public:
  using HealthCheckHandler = void (*)(HealthCheck data);

  enum class ParsingResult { OK, INVALID_ID, PARSING_ERROR, BUFFER_TOO_SMALL, INVALID_BUFFER };

  ParsingResult processMessage(uint8_t const* buffer, size_t messageLength);

  void setHealthCheckHandler(HealthCheckHandler handler);

  static size_t createLogMessage(Log const* log, uint8_t* buffer, size_t bufferSize);

 private:
  enum class MessageID : uint8_t {
    Invalid = 0x00,
    HealthCheck = 0x01,
    Log = 0x20,
  };

  ParsingResult parseMessageAndCallHandler(uint8_t const* messageData, size_t messageLength, MessageID messageID);
  static size_t createMessage(pb_msgdesc_t const* descriptor,
                              MessageID messageID,
                              void const* messageData,
                              uint8_t* buffer,
                              size_t bufferLength);

  HealthCheckHandler m_healthCheckHandler{nullptr};
};