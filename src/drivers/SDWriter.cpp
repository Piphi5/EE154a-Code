#include "SDWriter.h"

#include <SD.h>
#include <SPI.h>

#include "Constants.h"

SDWriter::SDWriter(String filename, uint8_t chipSelect) : mFile(filename), kChipSelectPin(chipSelect){};

void SDWriter::Setup() {
    pinMode(kChipSelectPin, OUTPUT);

    digitalWrite(kChipSelectPin, LOW);
    SPI.begin(spi::kSCK, spi::kMISO, spi::kMOSI, kChipSelectPin);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV2);

    if (!SD.begin(kChipSelectPin)) {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        return;
    }
    digitalWrite(kChipSelectPin, HIGH);
}

void SDWriter::OverwriteFile(String txt) {
    File SDout = SD.open(mFile, FILE_WRITE);
    SDout.println(txt);
    SDout.close();
}

void SDWriter::AppendFile(String txt) {
    File SDout = SD.open(mFile, FILE_APPEND);
    SDout.print(txt);
    SDout.close();
}

void SDWriter::WriteDataLine(unsigned long t, double xPos, double yPos, double externalPressure, double altitude, double humidity, double internalTemp, double externalTemp, double yaw, double pitch, double roll, double yawRate, double pitchRate, double rollRate, double xAccel, double yAccel, double zAccel, double compassHeading, double battTemp, double battCurrent) {
    File SDout = SD.open(mFile, FILE_APPEND);
    SDout.print(t);
    SDout.print(",");
    SDout.print(xPos);
    SDout.print(",");
    SDout.print(yPos);
    SDout.print(",");
    SDout.print(externalPressure);
    SDout.print(",");
    SDout.print(altitude);
    SDout.print(",");
    SDout.print(humidity);
    SDout.print(",");
    SDout.print(internalTemp);
    SDout.print(",");
    SDout.print(externalTemp);
    SDout.print(",");
    SDout.print(yaw);
    SDout.print(",");
    SDout.print(pitch);
    SDout.print(",");
    SDout.print(roll);
    SDout.print(",");
    SDout.print(yawRate);
    SDout.print(",");
    SDout.print(pitchRate);
    SDout.print(",");
    SDout.print(rollRate);
    SDout.print(",");
    SDout.print(xAccel);
    SDout.print(",");
    SDout.print(yAccel);
    SDout.print(",");
    SDout.print(zAccel);
    SDout.print(",");
    SDout.print(compassHeading);
    SDout.print(",");
    SDout.print(battTemp);
    SDout.print(",");
    SDout.print(battCurrent);
    SDout.println();
    SDout.close();
}
