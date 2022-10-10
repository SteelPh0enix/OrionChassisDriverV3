#pragma once
#include <Arduino.h>
#include <stdint.h>

namespace Pinout {
using PinT = uint8_t;

namespace WheelLF {  // OK
constexpr PinT PWMB{3};
constexpr PinT PWMF{2};
constexpr PinT DirectionF{23};
constexpr PinT DirectionB{22};
constexpr PinT FeedbackF{A1};
constexpr PinT FeedbackB{A0};
}  // namespace WheelRF

namespace WheelRF {  // OK
constexpr PinT PWMF{7};
constexpr PinT PWMB{6};
constexpr PinT DirectionF{27};
constexpr PinT DirectionB{26};
constexpr PinT FeedbackF{A5};
constexpr PinT FeedbackB{A4};
}  // namespace WheelRR

namespace WheelLR {  // OK
constexpr PinT PWMB{5};
constexpr PinT PWMF{4};
constexpr PinT DirectionF{25};
constexpr PinT DirectionB{24};
constexpr PinT FeedbackF{A3};
constexpr PinT FeedbackB{A2};
}  // namespace WheelLF

namespace WheelRR {  // OK
constexpr PinT PWMF{9};
constexpr PinT PWMB{8};
constexpr PinT DirectionF{29};
constexpr PinT DirectionB{28};
constexpr PinT FeedbackF{A7};
constexpr PinT FeedbackB{A6};
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