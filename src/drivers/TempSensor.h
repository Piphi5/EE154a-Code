#pragma once
#include <cmath>

#include "SparkFunBME280.h"

class TempSensor {
   public:
    TempSensor(uint8_t CS_pin);
    void Setup();
    void Update();
    float GetTemperature();
    float GetHumidity();
    float GetPressure();

   private:
    BME280 mBME280;
    const uint8_t kCSPort;
};