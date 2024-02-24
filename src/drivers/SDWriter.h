#pragma once

#include <string>

#include "Arduino.h"
#include "TimeoutTimer.h"

class SDWriter {
   public:
    SDWriter(std::string prefix, std::string suffix, uint8_t chipSelect);
    bool Setup();
    void OverwriteFile(String txt);
    void AppendFile(String txt);
    void ClearFile();

    void WriteDataLine(unsigned long t, double xPos, double yPos, double externalPressure, double internalPressure, double altitude, double humidity, double internalTemp, double externalTemp, double yaw, double pitch, double roll, double yawRate, double pitchRate, double rollRate, double xAccel, double yAccel, double zAccel, double compassHeading, double battTemp, double battCurrent);

   private:
    const std::string mPrefix;
    const std::string mSuffix;
    String mFile;
    const uint8_t kChipSelectPin;
    TimeoutTimer mTimer;
};