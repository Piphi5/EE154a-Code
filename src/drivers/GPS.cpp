#include "GPS.h"

#include <Arduino.h>

GPS::GPS() {}

bool GPS::Setup() {
    Serial1.begin(9600);
    return true;
}
void GPS::Update() {
    while (Serial1.available() > 0) {
        mGps.encode(Serial1.read());
        // Serial.println("READING LINE");
    }
}
float GPS::GetLatitude() {
    return mGps.location.lat();
}
float GPS::GetLongitude() {
    return mGps.location.lng();
}
float GPS::GetAltitude() {
    return mGps.altitude.meters();
}