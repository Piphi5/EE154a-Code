#pragma once
#include <cstdint>
class StatusManager {
   public:
    StatusManager(uint8_t sdPin, uint8_t imuPin, uint8_t tempPin, uint8_t batteryPin, uint8_t gpsPin, uint8_t heartbeatPin);
    void SetLEDOn();
    void SetLEDOff();
    void Setup();

    void SDSuccess();
    void IMUSuccess();
    void TempSuccess();
    void BatterySuccess(float battTemp, float battCurr);
    void GPSSuccess();
    void ToggleHeartbeat();

   private:
    const uint8_t kSDCardPin;
    const uint8_t kIMUPin;
    const uint8_t kTempPin;
    const uint8_t kBatteryPin;
    const uint8_t kGPSPin;
    const uint8_t kHearbeatPin;

    long mLastUpdate = 0;
    bool heartbeat = false;
};