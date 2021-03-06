#pragma once
#include <Arduino.h>
#include <stdint.h>

namespace Pinout {
using PinT = uint8_t;

namespace WheelRF {  // OK
constexpr PinT PWMB{2};
constexpr PinT PWMF{3};
constexpr PinT DirectionF{22};
constexpr PinT DirectionB{23};
constexpr PinT FeedbackF{A1};
constexpr PinT FeedbackB{A0};
}  // namespace WheelRF

namespace WheelRR {  // OK
constexpr PinT PWMF{7};
constexpr PinT PWMB{6};
constexpr PinT DirectionF{26};
constexpr PinT DirectionB{27};
constexpr PinT FeedbackF{A5};
constexpr PinT FeedbackB{A4};
}  // namespace WheelRR

namespace WheelLF {  // OK
constexpr PinT PWMB{5};
constexpr PinT PWMF{4};
constexpr PinT DirectionF{25};
constexpr PinT DirectionB{24};
constexpr PinT FeedbackF{A3};
constexpr PinT FeedbackB{A2};
}  // namespace WheelLF

namespace WheelLR {  // OK
constexpr PinT PWMF{8};
constexpr PinT PWMB{9};
constexpr PinT DirectionF{28};
constexpr PinT DirectionB{29};
constexpr PinT FeedbackF{A6};
constexpr PinT FeedbackB{A7};
}  // namespace WheelLR

namespace Encoders {
constexpr PinT Encoder1A{A8};
constexpr PinT Encoder1B{A9};
constexpr PinT Encoder2A{A10};
constexpr PinT Encoder2B{A11};
constexpr PinT Encoder3A{A12};
constexpr PinT Encoder3B{A13};
constexpr PinT Encoder4A{A14};
constexpr PinT Encoder4B{A15};
}  // namespace Encoders
}  // namespace Pinout