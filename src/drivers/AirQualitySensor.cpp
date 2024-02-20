#include "AirQualitySensor.h"

#include <Arduino.h>

#include "Constants.h"
AirQualitySensor::AirQualitySensor(uint8_t spiCSPin) : kSPICSPin(spiCSPin) {}
void AirQualitySensor::Setup() {
    pinMode(kSPICSPin, OUTPUT);
    digitalWrite(kSPICSPin, LOW);
    SPI.begin(spi::kSCK, spi::kMISO, spi::kMOSI, kSPICSPin);
    while (!mBME680.begin(kSPICSPin))  // Start using hardware SPI protocol
    {
        Serial.println("-  Unable to find BME680. Waiting 3 seconds.");
        delay(3000);
    }  // of loop until device is located
    Serial.println("- Setting 16x oversampling for all sensors");
    mBME680.setOversampling(TemperatureSensor, Oversample16);
    mBME680.setOversampling(HumiditySensor, Oversample16);
    mBME680.setOversampling(PressureSensor, Oversample16);
    mBME680.setIIRFilter(IIR16);
    digitalWrite(kSPICSPin, HIGH);
}
void AirQualitySensor::Update() {
    mBME680.getSensorData(temperature, humidity, pressure, gas);
}
float AirQualitySensor::GetTemperature() {
    return temperature;
    // return temperature / 100 + 0.01 * (temperature % 100);
}
float AirQualitySensor::GetHumidity() {
    return humidity;
    // return humidity / 1000 + 0.001 * (humidity % 1000);
}
float AirQualitySensor::GetPressure() {
    return pressure;
    // return pressure / 100 + 0.01 * (pressure % 100);
}
float AirQualitySensor::GetGas() {
    return gas / 100 + 0.01 * (gas % 100);
}
