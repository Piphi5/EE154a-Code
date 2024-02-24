#pragma once
#include <cmath>
#include <cstdint>

namespace util {
constexpr float pi = 3.14159265;
float GetBattTemp(uint16_t analogValue);
float GetBattCurrent(uint16_t analogValue1, uint16_t analogValue2);
float CalcCompassHeading(float magX, float magY, float magZ);
float CalcAccelFromG(float accel);
float ConvertIntToDec(int32_t num, int precision);
float RadToDeg(float radians);
float DegToRad(float degrees);
float CalcRollDegrees(float accelY, float accelZ);
float CalcPitchDegrees(float accelX, float accelY, float accelZ);
float CalcHeadingDegrees(float mx, float my);

}  // namespace util