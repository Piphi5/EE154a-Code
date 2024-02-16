#pragma once
#include <cmath>
#include <cstdint>

namespace util {
float GetBattTemp(uint16_t analogValue);
float GetBattCurrent(uint16_t analogValue1, uint16_t analogValue2);
float CalcCompassHeading(float magX, float magY, float magZ);
float CalcAccelFromG(float accel);
float RadToDeg(float radians);
float CalcRollDegrees(float accelY, float accelZ);
float CalcPitchDegrees(float accelX, float accelY, float accelZ);
float CalcHeadingDegrees(float mx, float my);

}  // namespace util