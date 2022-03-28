#pragma once
#include <Arduino.h>
#include <stdint.h>

namespace Pinout {
using PinT = uint8_t;

namespace WheelLF {
constexpr PinT PWMB{3};
constexpr PinT PWMF{2};
constexpr PinT DirectionF{23};
constexpr PinT DirectionB{22};
constexpr PinT FeedbackF{A0};
constexpr PinT FeedbackB{A1};
}  // namespace WheelLF

namespace WheelRF {
constexpr PinT PWMF{7};
constexpr PinT PWMB{6};
constexpr PinT DirectionF{26};
constexpr PinT DirectionB{27};
constexpr PinT FeedbackF{A5};
constexpr PinT FeedbackB{A4};
}  // namespace WheelRF

namespace WheelLR {
constexpr PinT PWMB{5};
constexpr PinT PWMF{4};
constexpr PinT DirectionF{25};
constexpr PinT DirectionB{24};
constexpr PinT FeedbackF{A3};
constexpr PinT FeedbackB{A2};
}  // namespace WheelLB

namespace WheelRR {
constexpr PinT PWMF{9};
constexpr PinT PWMB{8};
constexpr PinT DirectionF{29};
constexpr PinT DirectionB{28};
constexpr PinT FeedbackF{A7};
constexpr PinT FeedbackB{A6};
}  // namespace WheelRB
}  // namespace Pinout