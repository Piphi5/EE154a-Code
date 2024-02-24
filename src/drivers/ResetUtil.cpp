#include "ResetUtil.h"

#include "Arduino.h"
#include "Constants.h"
#include "SPI.h"

using namespace util;
void util::ResetI2CPins(TwoWire& wire) {
    wire.end();
    pinMode(i2c::kSDA, OUTPUT);
    pinMode(i2c::kSCL, OUTPUT);
    digitalWrite(i2c::kSDA, LOW);
    digitalWrite(i2c::kSCL, LOW);
    pinMode(i2c::kSDA, INPUT);
    pinMode(i2c::kSCL, INPUT);
    wire.begin();
}

void util::ResetSPIPins() {
    SPI.end();
    pinMode(spi::kMISO, OUTPUT);
    pinMode(spi::kMOSI, OUTPUT);
    pinMode(spi::kSCK, OUTPUT);
    digitalWrite(spi::kMISO, LOW);
    digitalWrite(spi::kMOSI, LOW);
    digitalWrite(spi::kSCK, LOW);
    pinMode(spi::kMISO, INPUT);
    pinMode(spi::kMOSI, INPUT);
    pinMode(spi::kSCK, INPUT);
    SPI.begin();
}