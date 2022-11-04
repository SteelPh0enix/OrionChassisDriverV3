#pragma once

namespace Settings {
constexpr unsigned long SerialBaudRate{250000};

// This limit sets the range of speed/rotation input for Chassis.
// This value comes via UART and is further processed to PWM value.
constexpr int WheelPowerLimit = 1000;

// Configures the delay between chassis power change.
// Increase to have faster power change, also increasing the peak current draw.
constexpr unsigned long ChassisProcessingDelay = 30;

// Configures how much the power changes in each chassis processing cycle.
// This is a PWM value, so should be in range (0, 256)
// Increase to have faster power change, also increasing the peak current draw
constexpr unsigned WheelPowerChangePerCycle = 15;

// Configures the time between feedback updates.
constexpr unsigned long FeedbackDelayMs = 500;
}  // namespace Settings

