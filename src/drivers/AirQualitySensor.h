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
    int32_t temperature;
    int32_t humidity;
    int32_t pressure;
    int32_t gas;
    uint8_t kSPICSPin;
    BME680_Class mBME680;
};