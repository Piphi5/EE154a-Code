#pragma once
#include <cmath>

#include "TimeoutTimer.h"
#include "Zanshin_BME680.h"

class TempSensor {
   public:
    TempSensor(uint8_t addr);
    bool Setup();
    void Update();
    float GetTemperature();
    float GetHumidity();
    float GetPressure();

   private:
    BME680_Class mBME680;
    int32_t temperature = 2500;
    int32_t humidity = 90000;
    int32_t pressure = 90000;
    int32_t gas = 10;
    const uint8_t kAddr;
    TimeoutTimer mTimer;
};