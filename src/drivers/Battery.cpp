#include "Battery.h"

#include <Arduino.h>

#include "Math.h"

Battery::Battery(uint8_t thermistor, uint8_t current1, uint8_t current2) : kThermistorPin(thermistor), kCurrentPin1(current1), kCurrentPin2(current2) {}

void Battery::Setup() {
    pinMode(kThermistorPin, INPUT);
    pinMode(kCurrentPin1, INPUT);
    pinMode(kCurrentPin2, INPUT);
}

float Battery::GetBattCurrent() {
    return util::GetBattCurrent(analogRead(kCurrentPin1), analogRead(kCurrentPin2));
}
float Battery::GetBattTemp() {
    return util::GetBattTemp(analogRead(kThermistorPin));
}

bool Battery::ValidMeasurements() {
    auto curr = GetBattCurrent();
    auto temp = GetBattTemp();
    return curr > 0 && curr < 500 && temp < 50.0;
}