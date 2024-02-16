#pragma once

#include "Arduino.h"

class SDWriter {
   public:
    SDWriter(String filename, uint8_t chipSelect);
    void Setup();
    void OverwriteFile(String txt);
    void AppendFile(String txt);

    void WriteDataLine(unsigned long t, double xPos, double yPos, double externalPressure, double altitude, double humidity, double internalTemp, double externalTemp, double yaw, double pitch, double roll, double yawRate, double pitchRate, double rollRate, double xAccel, double yAccel, double zAccel, double compassHeading, double battTemp, double battCurrent);

   private:
    const String mFile;
    const uint8_t kChipSelectPin;
};