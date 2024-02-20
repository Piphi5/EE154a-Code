#include <cmath>

#include "ProjectConstants.h"
#include "drivers/AirQualitySensor.h"
#include "drivers/Battery.h"
#include "drivers/Constants.h"
#include "drivers/IMU.h"
#include "drivers/SDWriter.h"
#include "drivers/TempSensor.h"

IMU imuSensor;
SDWriter sdWriter{SDConstants::kFilename, SDConstants::kSpiCSPin};
Battery batterySensor{BatteryConstants::kBatteryTempPin, BatteryConstants::kBatteryCurrentPin1, BatteryConstants::kBatteryCurrentPin2};
AirQualitySensor bme680{BME680Constants::kSpiCSPin};
TempSensor bme280{BME280Constants::kSpiCSPin};

void setup() {
    Serial.begin(9600);

    pinMode(SDConstants::kSpiCSPin, OUTPUT);
    pinMode(BME680Constants::kSpiCSPin, OUTPUT);
    pinMode(BME280Constants::kSpiCSPin, OUTPUT);

    digitalWrite(SDConstants::kSpiCSPin, HIGH);
    digitalWrite(BME680Constants::kSpiCSPin, HIGH);
    digitalWrite(BME280Constants::kSpiCSPin, HIGH);

    batterySensor.Setup();

    // Serial.println("Initializing imu");
    // imuSensor.Setup();
    Serial.println("Initializing SD card...");
    sdWriter.Setup();
    // Serial.println("Initializing BME680");
    // bme680.Setup();
    // Serial.println("Initializing BME280");
    // bme280.Setup();

    sdWriter.OverwriteFile("");
}

void loop() {
    imuSensor.UpdateLoop();
    bme680.Update();

    // TODO 0's are stuff we still need to implement (external temp sensor + GPS module)
    sdWriter.WriteDataLine(millis(), 0.0, 0.0, bme280.GetPressure(), bme680.GetPressure(), 0.0, bme680.GetHumidity(), bme680.GetTemperature(), bme280.GetTemperature(), imuSensor.getHeading(), imuSensor.getPitch(), imuSensor.getRoll(), imuSensor.getYawRate(), imuSensor.getRollRate(), imuSensor.getPitchRate(), imuSensor.getXAccel(), imuSensor.getYAccel(), imuSensor.getZAccel(), imuSensor.getHeading(), batterySensor.GetBattTemp(), batterySensor.GetBattCurrent());
}