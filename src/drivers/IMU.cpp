#include "IMU.h"

#include <Wire.h>

#include "Math.h"

IMU::IMU() {}

void IMU::Setup() {
    Wire.begin();
    while (imu.begin(107U, 30U, Wire) == false)  // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
    {
        Serial.println("Failed to communicate with LSM9DS1.");
    }
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
float IMU::getXAccel() {
    return imu.ax;
}
float IMU::getYAccel() {
    return imu.ay;
}
float IMU::getZAccel() {
    return imu.az;
}

float IMU::getPitchRate() {
    return imu.gy;
}
float IMU::getRollRate() {
    return imu.gx;
}
float IMU::getYawRate() {
    return imu.gz;
}
