#include "StrUtil.h"

#include "Arduino.h"
using namespace util;

std::string util::GetRandomizedFilename(std::string prefix, std::string suffix) {
    randomSeed(analogRead(A0));
    return prefix + std::to_string(random(255)) + suffix;
}