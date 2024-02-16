#pragma once
#include <SparkFunLSM9DS1.h>

class IMU {
   public:
    IMU();
    void Setup();
    void UpdateLoop();
    float getPitch();
    float getRoll();
    float getHeading();
    float getPitchRate();
    float getRollRate();
    float getYawRate();
    float getXAccel();
    float getYAccel();
    float getZAccel();

   private:
    LSM9DS1 imu;
};