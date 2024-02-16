#pragma once

#include <cstdint>

#include "Arduino.h"
namespace BatteryConstants {
constexpr uint8_t kBatteryTempPin = 34;
constexpr uint8_t kBatteryCurrentPin1 = 35;
constexpr uint8_t kBatteryCurrentPin2 = 34;
}  // namespace BatteryConstants

namespace IMUConstants {
}  // namespace IMUConstants

namespace SDConstants {
const String kFilename = "/tester.txt";
constexpr uint8_t kSpiCSPin = 5;
}  // namespace SDConstants

namespace BME680Constants {
constexpr uint8_t kSpiCSPin = 33;
}