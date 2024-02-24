#pragma once
#include <Wire.h>
namespace util {
void ResetI2CPins(TwoWire& wire);

void ResetSPIPins();

}  // namespace util