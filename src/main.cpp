#include <cmath>

#include "ProjectConstants.h"
#include "drivers/AirQualitySensor.h"
#include "drivers/Battery.h"
// #include "drivers/Constants.h"
#include <watchdog.h>

#include "drivers/GPS.h"
#include "drivers/IMU.h"
#include "drivers/SDWriter.h"
#include "drivers/StatusManager.h"
#include "drivers/TempSensor.h"

IMU imuSensor;
SDWriter sdWriter{"data", ".txt", SDConstants::kSpiCSPin};
Battery batterySensor{BatteryConstants::kBatteryTempPin, BatteryConstants::kBatteryCurrentPin1, BatteryConstants::kBatteryCurrentPin2};
TempSensor bme680Internal{0x77};
TempSensor bme680External{0x76};
GPS gps;

StatusManager statman{LEDConstants::kSDCardLED, LEDConstants::kIMULED, LEDConstants::kTempLED, LEDConstants::kBatteryReaderLED, LEDConstants::kGPSLED, LEDConstants::kHearbeat};
#include <Arduino.h>

void watchdogSetup(void) {
    return;
}

void setup() {
    Serial.begin(9600);

    statman.Setup();

    Serial.println("Initializing GPS");
    if (gps.Setup()) {
        statman.GPSSuccess();
        Serial.println("Success!");
    }

    delay(50);
    Serial.println("Initializing imu");

    if (imuSensor.Setup()) {
        statman.IMUSuccess();
        Serial.println("Success!");
    }

    delay(50);

    Serial.println("Initializing SD card...");
    if (sdWriter.Setup()) {
        statman.SDSuccess();
        Serial.println("Success!");
    }

    delay(5);
    Serial.println("Initializing BME680s");
    if (bme680Internal.Setup() && bme680External.Setup()) {
        statman.TempSuccess();
    }

    Serial.println("Initializing battery stuff");
    batterySensor.Setup();
    statman.BatterySuccess(batterySensor.GetBattCurrent(), batterySensor.GetBattTemp());

    watchdogSetup();
    watchdogEnable(5000);  // Watchdog with 5s timeout

    sdWriter.ClearFile();
    sdWriter.OverwriteFile("");
}

void loop() {
    // Serial.println("LOOP");
    gps.Update();
    imuSensor.UpdateLoop();
    bme680Internal.Update();
    bme680External.Update();
    statman.ToggleHeartbeat();
    sdWriter.WriteDataLine(millis(), gps.GetLatitude(), gps.GetLongitude(), bme680External.GetPressure(), bme680Internal.GetPressure(), gps.GetAltitude(), bme680External.GetHumidity(), bme680Internal.GetTemperature(), bme680External.GetTemperature(), imuSensor.getHeading(), imuSensor.getPitch(), imuSensor.getRoll(), imuSensor.getYawRate(), imuSensor.getRollRate(), imuSensor.getPitchRate(), imuSensor.getXAccel(), imuSensor.getYAccel(), imuSensor.getZAccel(), imuSensor.getHeading(), batterySensor.GetBattTemp(), batterySensor.GetBattCurrent());
    watchdogReset();  // Pat the dog
}