#pragma once

#include <cstdint>
#include <string>

#include "Arduino.h"
namespace BatteryConstants {
constexpr uint8_t kBatteryTempPin = A8;
constexpr uint8_t kBatteryCurrentPin1 = A11;
constexpr uint8_t kBatteryCurrentPin2 = A10;
}  // namespace BatteryConstants

namespace IMUConstants {
}  // namespace IMUConstants

namespace LEDConstants {
constexpr uint8_t kBatteryReaderLED = 22;
constexpr uint8_t kSDCardLED = 23;
constexpr uint8_t kIMULED = 24;
constexpr uint8_t kTempLED = 25;
constexpr uint8_t kGPSLED = 26;
constexpr uint8_t kHearbeat = 27;
}  // namespace LEDConstants

namespace SDConstants {
const std::string kFilename = std::string("/tester") + std::to_string(random(300)) + std::string(".txt");
// const std::string kFilename = "/tester.txt";
constexpr uint8_t kSpiCSPin = 10;
}  // namespace SDConstants
