#include "IMU.h"

#include <Arduino.h>
#include <Wire.h>

#include "Math.h"
#include "ResetUtil.h"

IMU::IMU() : mTimer() {}

bool IMU::Setup() {
    Wire1.begin();
    mTimer.StartTimer(millis());
    while (mTimer.Wait(imu.begin(107U, 30U, Wire1), millis()))  // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
    {
        Serial.println("Failed to communicate with LSM9DS1. Attempting a reset of the I2c Bus. Waiting 0.5 seconds");
        util::ResetI2CPins(Wire1);
        delay(500);
    }
    return !mTimer.TimedOut();
}
void IMU::UpdateLoop() {
    if (imu.gyroAvailable()) {
        // To read from the gyroscope,  first call the
        // readGyro() function. When it exits, it'll update the
        // gx, gy, and gz variables with the most current data.
        imu.readGyro();
    }
    if (imu.accelAvailable()) {
        // To read from the accelerometer, first call the
        // readAccel() function. When it exits, it'll update the
        // ax, ay, and az variables with the most current data.
        imu.readAccel();
    }
    if (imu.magAvailable()) {
        // To read from the magnetometer, first call the
        // readMag() function. When it exits, it'll update the
        // mx, my, and mz variables with the most current data.
        imu.readMag();
    }
}

float IMU::getPitch() {
    return util::CalcPitchDegrees(imu.ax, imu.ay, imu.az);
}

float IMU::getRoll() {
    return util::CalcRollDegrees(imu.ay, imu.az);
}
float IMU::getHeading() {
    return util::CalcHeadingDegrees(imu.mx, imu.my);
}

std::string IMU::getCompassHeading() {
    auto heading = getHeading();
    return util::CalcCompassHeading(heading);
}
float IMU::getXAccel() {
    return imu.calcAccel(imu.ax);
}
float IMU::getYAccel() {
    return imu.calcAccel(imu.ay);
}
float IMU::getZAccel() {
    return imu.calcAccel(imu.az);
}

float IMU::getPitchRate() {
    return imu.calcGyro(imu.gy);
}
float IMU::getRollRate() {
    return imu.calcGyro(imu.gx);
}
float IMU::getYawRate() {
    return imu.calcGyro(imu.gz);
}
