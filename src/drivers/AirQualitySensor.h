#pragma once
#include <cmath>

#include "Zanshin_BME680.h"
class AirQualitySensor {
   public:
    AirQualitySensor(uint8_t spiCSPin);
    void Setup();
    void Update();
    float GetTemperature();
    float GetHumidity();
    float GetPressure();
    float GetGas();

   private:
    int32_t temperature = 2500;
    int32_t humidity = 90000;
    int32_t pressure = 90000;
    int32_t gas = 10;
    uint8_t kSPICSPin;
    BME680_Class mBME680;
};