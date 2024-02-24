#include "TempSensor.h"

#include <Arduino.h>

#include "Constants.h"
#include "Math.h"
#include "ResetUtil.h"

TempSensor::TempSensor(uint8_t addr) : kAddr(addr), mTimer() {
}
bool TempSensor::Setup() {
    // SPI.begin(spi::kSCK, spi::kMISO, spi::kMOSI, kCSPort);
    pinMode(i2c::kSDA, INPUT);
    pinMode(i2c::kSCL, INPUT);
    mTimer.StartTimer(millis());
    Wire.begin();
    while (mTimer.Wait(mBME680.begin(I2C_STANDARD_MODE, kAddr), millis()))  // Start using hardware SPI protocol
    {
        util::ResetI2CPins(Wire);
        Serial.println("-  Unable to find BME680. Attempting reset. Waiting 0.5 seconds.");
        delay(500);
    }  // of loop until device is located
    mBME680.setOversampling(TemperatureSensor, Oversample16);
    mBME680.setOversampling(HumiditySensor, Oversample16);
    mBME680.setOversampling(PressureSensor, Oversample16);
    mBME680.setIIRFilter(IIR16);

    return !mTimer.TimedOut();
}
void TempSensor::Update() {
    mBME680.getSensorData(temperature, humidity, pressure, gas);
}
float TempSensor::GetTemperature() {
    return util::ConvertIntToDec(temperature, 2);
}
float TempSensor::GetHumidity() {
    return util::ConvertIntToDec(humidity, 3);
}
float TempSensor::GetPressure() {
    return pressure;  //  util::ConvertIntToDec(pressure, 2);
}