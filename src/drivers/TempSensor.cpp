#include "TempSensor.h"

#include "Constants.h"

TempSensor::TempSensor(uint8_t CS_pin) : kCSPort(CS_pin){};
void TempSensor::Setup() {
    pinMode(kCSPort, OUTPUT);
    digitalWrite(kCSPort, LOW);
    SPI.begin(spi::kSCK, spi::kMISO, spi::kMOSI, kCSPort);
    while (!mBME280.beginSPI(kCSPort))  // Start using hardware SPI protocol
    {
        Serial.println("-  Unable to find BME280. Waiting 3 seconds.");
        delay(3000);
    }  // of loop until device is located
}
void TempSensor::Update() {
}
float TempSensor::GetTemperature() {
    return mBME280.readTempC();
}
float TempSensor::GetHumidity() {
    return mBME280.readFloatHumidity();
}
float TempSensor::GetPressure() {
    return mBME280.readFloatPressure();
}