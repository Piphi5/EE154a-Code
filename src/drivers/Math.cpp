#include "Math.h"

#include <math.h>

#include "Constants.h"

using namespace util;

float util::GetBattTemp(uint16_t analogValue) {
    // TODO Labelson link the website for getting this
    return 1 / (battery::kA + battery::kB * log(analogValue / battery::kResolution)) + 25.0;  // normalized around 25 deg C
}

float util::GetBattCurrent(uint16_t analogValue1, uint16_t analogValue2) {
    return (battery::kVoltage * (analogValue1 - analogValue2) / battery::kResolution) * battery::kScaleFactor;
}

float util::CalcCompassHeading(float magX, float magY, float magZ) {
    // https://cdn-shop.adafruit.com/datasheets/AN203_Compass_Heading_Using_Magnetometers.pdf
    if (magY > 0) {
        return 90.0 - RadToDeg(atan2(magX, magY));

    } else if (magY < 0) {
        return 270 - RadToDeg(atan2(magX, magY));
    } else {
        if (magX < 0) {
            return 180.0;
        } else {
            return 0.0;
        }
    }
}
float util::CalcAccelFromG(float accel) {
    return accel * 9.807;
}
float util::RadToDeg(float radians) {
    return radians * 180.0 / M_PI;
}
float util::CalcRollDegrees(float accelY, float accelZ) {
    return RadToDeg(atan2(accelY, accelZ));
}
float util::CalcPitchDegrees(float accelX, float accelY, float accelZ) {
    return RadToDeg(atan2(-accelX, sqrt(accelY * accelY + accelZ * accelZ)));
}
float util::CalcHeadingDegrees(float mx, float my) {
    float heading = 0.0;
    if (my == 0)
        heading = (mx < 0) ? M_PI : 0;
    else
        heading = atan2(mx, my);

    heading -= imu::kDeclination * M_PI / 180;

    if (heading > M_PI)
        heading -= (2 * M_PI);
    else if (heading < -M_PI)
        heading += (2 * M_PI);

    return RadToDeg(heading);
}