#pragma once

#include <TinyGPSPlus.h>

class GPS {
   public:
    GPS();
    bool Setup();
    void Update();
    float GetLatitude();
    float GetLongitude();
    float GetAltitude();

   private:
    TinyGPSPlus mGps;
};