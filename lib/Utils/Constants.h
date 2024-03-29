#pragma once
#include <cstdint>

namespace spi {
constexpr uint8_t kMISO = 74;
constexpr uint8_t kMOSI = 75;
constexpr uint8_t kSCK = 76;
}  // namespace spi

namespace i2c {
constexpr uint8_t kSDA = 20;
constexpr uint8_t kSCL = 21;
}  // namespace i2c

namespace imu {
// Earth's magnetic field varies by location. Add or subtract
// a declination to get a more accurate heading. Calculate
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
constexpr float kDeclination = -11.23;  // Declination (degrees) in Barstow, CA. Last updated 2/16/2024.
}  // namespace imu

namespace battery {
constexpr float kResolution = 1023.0;
constexpr float kVoltage = 3.3;
constexpr float kThermistorResistor = 10000;  // ohms
constexpr float kThermFixedResistor = 10000;  // ohms
constexpr float kScaleFactor = 1000.0 * 5.7 / 10.0;
constexpr float kA = 10000.0;
constexpr float kB = 3950.0;
}  // namespace battery