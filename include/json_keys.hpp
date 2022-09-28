namespace JsonKey {
namespace Input {
constexpr char const* RoverSpeed = "X";
constexpr char const* RoverRotation = "Y";
}  // namespace Input

namespace Feedback {
constexpr char const* LeftFrontWheelPWM = "LF";
constexpr char const* RightFrontWheelPWM = "RF";
constexpr char const* LeftRearWheelPWM = "LB";
constexpr char const* RightRearWheelPWM = "RB";
constexpr char const* ErrorCode = "ErrorCode";
constexpr char const* ErrorDescription = "ErrorDescription";
constexpr char const* Power = "PWR";
constexpr char const* Rotation = "ROT";

namespace Wheel {
constexpr char const* CurrentPower = "CURRENT_PWR";
constexpr char const* TargetPower = "TARGET_PWR";
constexpr char const* Direction = "DIR";
constexpr char const* CurrentDraw = "CUR";
}  // namespace Wheel
}  // namespace Feedback
}  // namespace JsonKey