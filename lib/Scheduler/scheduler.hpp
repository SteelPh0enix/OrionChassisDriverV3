#pragma once

#include <Arduino.h>
#include <stddef.h>

class Scheduler {
 public:
  using FuncT = void (*)();
  static constexpr size_t MaxFunctionsScheduled{10};

  size_t currentlyScheduledFunctionsCount() const {
    return m_currentlyScheduledFunctionsCount;
  }

  bool addFunction(FuncT function, unsigned long delayMs) {
    if (currentlyScheduledFunctionsCount() < MaxFunctionsScheduled) {
      ScheduleInfo info{};
      info.function = function;
      info.delayMs = delayMs;
      m_scheduledFunctions[m_currentlyScheduledFunctionsCount] = info;
      m_currentlyScheduledFunctionsCount++;
      return true;
    }

    return false;
  }

  void clearFunctions() {
    memset(m_scheduledFunctions, 0x00, sizeof(m_scheduledFunctions));
    m_currentlyScheduledFunctionsCount = 0;
  }

  void process() {
    for (size_t i = 0; i < m_currentlyScheduledFunctionsCount; i++) {
      ScheduleInfo& funcInfo = m_scheduledFunctions[i];
      if (funcInfo.function != nullptr) {
        unsigned long const currentTime = millis();
        unsigned long const timeSinceLastRun =
            currentTime - funcInfo.lastRunTimestampMs;
        if (timeSinceLastRun > funcInfo.delayMs) {
          funcInfo.function();
          funcInfo.lastRunTimestampMs = currentTime;
        }
      }
    }
  }

 private:
  struct ScheduleInfo {
    FuncT function{nullptr};
    unsigned long delayMs{0};
    unsigned long lastRunTimestampMs{0};
  };

  ScheduleInfo m_scheduledFunctions[MaxFunctionsScheduled]{};
  size_t m_currentlyScheduledFunctionsCount{0};
};