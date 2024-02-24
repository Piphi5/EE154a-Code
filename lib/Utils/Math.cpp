#include "Math.h"

#include <math.h>

#include "Constants.h"
using namespace util;

float util::GetBattTemp(uint16_t analogValue) {
    // https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html to check math
    // TODO Labelson link the website for getting this
    // First need to solve for resistance of thermistor: https://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/
    // float R = 1.0 / (battery::kResolution / ((float)analogValue) - 1);
    float average = battery::kResolution / analogValue - 1;
    // average = battery::kThermistorResistor / average;
    // Serial.print("Thermistor resistance ");
    // Serial.println(average);

    float steinhart = average;
    // steinhart = average / battery::kThermistorResistor;  // (R/Ro)
    steinhart = log(steinhart);        // ln(R/Ro)
    steinhart /= battery::kB;          // 1/B * ln(R/Ro)
    steinhart += 1.0 / (25 + 273.15);  // + (1/To)
    steinhart = 1.0 / steinhart;       // Invert
    steinhart -= 273.15;               // convert absolute temp to C
    // Serial.println(R);

    return steinhart;
}

float util::GetBattCurrent(uint16_t analogValue1, uint16_t analogValue2) {
    return (battery::kVoltage * (analogValue1 - analogValue2) / battery::kResolution) * battery::kScaleFactor;
}

float util::ConvertIntToDec(int32_t num, int precision) {
    int scale = ((int)pow(10, precision));
    return num / scale + 1.0 / scale * (num % scale);
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
    return radians * 180.0 / util::pi;
}
float util::CalcRollDegrees(float accelY, float accelZ) {
    return RadToDeg(atan2(accelY, accelZ));
}
float util::CalcPitchDegrees(float accelX, float accelY, float accelZ) {
    return RadToDeg(atan2(-accelX, sqrt(accelY * accelY + accelZ * accelZ)));
}
float util::CalcHeadingDegrees(float mx, float my) {
    float heading = 0.0;
    if (my == 0) {
        if (mx < 0) {
            heading = util::pi;
        } else {
            heading = 0.0;
        }
    } else {
        heading = atan2(mx, my);
    }

    heading -= DegToRad(imu::kDeclination);

    if (heading > util::pi) {
        heading -= (2 * util::pi);
    } else if (heading < -util::pi) {
        heading += (2 * util::pi);
    }

    return RadToDeg(heading);
}

float util::DegToRad(float degrees) {
    return util::pi * degrees / 180.0;
}