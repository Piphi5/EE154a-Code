#include "StatusManager.h"

#include "Arduino.h"
StatusManager::StatusManager(uint8_t sdPin, uint8_t imuPin, uint8_t tempPin, uint8_t batteryPin, uint8_t gpsPin, uint8_t heartbeatPin) : kSDCardPin(sdPin), kIMUPin(imuPin), kTempPin(tempPin), kBatteryPin(batteryPin), kGPSPin(gpsPin), kHearbeatPin(heartbeatPin) {}
void StatusManager::Setup() {
    pinMode(kSDCardPin, OUTPUT);
    pinMode(kIMUPin, OUTPUT);
    pinMode(kTempPin, OUTPUT);
    pinMode(kBatteryPin, OUTPUT);
    pinMode(kGPSPin, OUTPUT);
    pinMode(kHearbeatPin, OUTPUT);

    digitalWrite(kSDCardPin, LOW);
    digitalWrite(kIMUPin, LOW);
    digitalWrite(kTempPin, LOW);
    digitalWrite(kBatteryPin, LOW);
    digitalWrite(kGPSPin, LOW);
    digitalWrite(kHearbeatPin, LOW);
}

void StatusManager::SDSuccess() {
    digitalWrite(kSDCardPin, HIGH);
}
void StatusManager::IMUSuccess() {
    digitalWrite(kIMUPin, HIGH);
}
void StatusManager::TempSuccess() {
    digitalWrite(kTempPin, HIGH);
}

void StatusManager::BatterySuccess() {
    digitalWrite(kBatteryPin, HIGH);
}
void StatusManager::GPSSuccess() {
    digitalWrite(kGPSPin, HIGH);
}

void StatusManager::ToggleHeartbeat() {
    auto now = millis();
    if (now - mLastUpdate > 500) {
        if (heartbeat) {
            digitalWrite(kHearbeatPin, HIGH);
        } else {
            digitalWrite(kHearbeatPin, LOW);
        }
        heartbeat = !heartbeat;
        mLastUpdate = millis();
    }
}