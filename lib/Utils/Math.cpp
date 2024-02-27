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
    average = battery::kThermFixedResistor / average;
    // average = battery::kThermistorResistor / average;
    // Serial.print("Thermistor resistance ");
    // Serial.println(average);

    float steinhart = average;
    steinhart = average / battery::kThermistorResistor;  // (R/Ro)
    steinhart = log(steinhart);                          // ln(R/Ro)
    steinhart /= battery::kB;                            // 1/B * ln(R/Ro)
    steinhart += 1.0 / (25 + 273.15);                    // + (1/To)
    steinhart = 1.0 / steinhart;                         // Invert
    steinhart -= 273.15;                                 // convert absolute temp to C
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

std::string util::CalcCompassHeading(float heading) {
    // https://digilent.com/blog/how-to-convert-magnetometer-data-into-compass-heading/
    if (heading > 337.25 || heading < 22.5) {
        return "North";
    } else if (heading >= 292.5 && heading <= 337.25) {
        return "North West";
    } else if (heading >= 247.5 && heading <= 292.5) {
        return "West";
    } else if (heading >= 202.5 && heading <= 247.5) {
        return "South West";
    } else if (heading >= 157.5 && heading <= 202.5) {
        return "South";
    } else if (heading >= 112.5 && heading <= 157.5) {
        return "South East";
    } else if (heading >= 67.5 && heading <= 112.5) {
        return "East";
    } else if (heading >= 0 && heading <= 67.15) {
        return "North East";
    } else {
        return "None";
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
    if (mx == 0) {
        if (my < 0) {
            heading = util::pi / 2.0;
        } else {
            heading = 0.0;
        }
    } else {
        heading = atan2(my, mx);
    }

    heading -= DegToRad(imu::kDeclination);

    if (heading > 2 * util::pi) {
        heading -= 2 * util::pi;
    } else if (heading < 0) {
        heading += 2 * util::pi;
    }

    return RadToDeg(heading);
}

float util::DegToRad(float degrees) {
    return util::pi * degrees / 180.0;
}