#pragma once
#include <cstdint>
class Battery {
   public:
    Battery(uint8_t thermistor, uint8_t current1, uint8_t current2);
    void Setup();
    float GetBattCurrent();
    float GetBattTemp();

   private:
    const uint8_t kThermistorPin;
    const uint8_t kCurrentPin1;
    const uint8_t kCurrentPin2;
};