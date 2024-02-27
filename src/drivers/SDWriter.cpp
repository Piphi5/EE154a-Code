#include "SDWriter.h"

#include <SD.h>
#include <SPI.h>

#include "Constants.h"
#include "ResetUtil.h"
#include "StrUtil.h"

SDWriter::SDWriter(std::string prefix, std::string suffix, uint8_t chipSelect) : mPrefix(prefix), mSuffix(suffix), kChipSelectPin(chipSelect), mTimer(){};
#define FILE_APPEND (O_APPEND | O_WRITE)
bool SDWriter::Setup() {
    pinMode(kChipSelectPin, OUTPUT);
    digitalWrite(kChipSelectPin, LOW);
    // SPI.begin(spi::kSCK, spi::kMISO, spi::kMOSI, kChipSelectPin);
    // SPI.setDataMode(SPI_MODE0);
    // SPI.setClockDivider(SPI_CLOCK_DIV2);
    // SPI.begin();
    mTimer.StartTimer(millis());
    SPI.begin();
    while (mTimer.Wait(SD.begin(kChipSelectPin), millis())) {
        Serial.println("Card failed, or not present or system error. Will try to reset the pins in the meantime (0.5 seconds).");
        util::ResetSPIPins();
        delay(500);
    }
    digitalWrite(kChipSelectPin, HIGH);

    auto filename = util::GetRandomizedFilename(mPrefix, mSuffix);
    mFile = String{filename.c_str()};
    Serial.println(mFile);

    return !mTimer.TimedOut();
}

void SDWriter::ClearFile() {
    digitalWrite(kChipSelectPin, LOW);
    File SDout = SD.open(mFile, FILE_WRITE | O_TRUNC);
    SDout.close();
    digitalWrite(kChipSelectPin, HIGH);
}

void SDWriter::OverwriteFile(String txt) {
    digitalWrite(kChipSelectPin, LOW);
    File SDout = SD.open(mFile, FILE_WRITE);
    SDout.println(txt);
    SDout.close();
    digitalWrite(kChipSelectPin, HIGH);
}

void SDWriter::AppendFile(String txt) {
    File SDout = SD.open(mFile, FILE_WRITE);
    SDout.print(txt);
    SDout.close();
}

void SDWriter::WriteDataLine(unsigned long t, double xPos, double yPos, double externalPressure, double internalPressure, double altitude, double humidity, double internalTemp, double externalTemp, double yaw, double pitch, double roll, double yawRate, double pitchRate, double rollRate, double xAccel, double yAccel, double zAccel, std::string compassHeading, double battTemp, double battCurrent) {
    digitalWrite(kChipSelectPin, LOW);
    String compass = String{compassHeading.c_str()};
    File SDout = SD.open(mFile, FILE_WRITE);
    SDout.print(t);
    SDout.print(F(","));
    SDout.print(xPos);
    SDout.print(F(","));
    SDout.print(yPos);
    SDout.print(F(","));
    SDout.print(externalPressure);
    SDout.print(F(","));
    SDout.print(internalPressure);
    SDout.print(F(","));
    SDout.print(altitude);
    SDout.print(F(","));
    SDout.print(humidity);
    SDout.print(F(","));
    SDout.print(internalTemp);
    SDout.print(F(","));
    SDout.print(externalTemp);
    SDout.print(F(","));
    SDout.print(yaw);
    SDout.print(F(","));
    SDout.print(pitch);
    SDout.print(F(","));
    SDout.print(roll);
    SDout.print(F(","));
    SDout.print(yawRate);
    SDout.print(F(","));
    SDout.print(pitchRate);
    SDout.print(F(","));
    SDout.print(rollRate);
    SDout.print(F(","));
    SDout.print(xAccel);
    SDout.print(F(","));
    SDout.print(yAccel);
    SDout.print(F(","));
    SDout.print(zAccel);
    SDout.print(F(","));
    SDout.print(compass);
    SDout.print(F(","));
    SDout.print(battTemp);
    SDout.print(F(","));
    SDout.print(battCurrent);
    SDout.println();
    SDout.close();

    digitalWrite(kChipSelectPin, HIGH);
}

void SDWriter::WriteDataHeader() {
    OverwriteFile("Time (millis), Latitude, Longitude, External Pressure (pascals), Internal Pressure (pascals), Altitude (m), Humidity (percent), Internal Temperature (C), External Temperature (C), Yaw (deg), Pitch (deg), Roll (deg), Yaw Rate (deg/s), Pitch Rate (deg/s), Roll Rate (deg/s), X-axis Acceleration (g), Y-axis Acceleration (g), Z-axis Acceleration (g), Battery Temperature (C), Battery Current (mA)");
}
