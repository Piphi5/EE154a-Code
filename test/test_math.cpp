#include <gtest/gtest.h>

#include "Constants.h"
#include "Math.h"

TEST(BatteryTempCalcTest, One) {
    // https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
    // analog_in = kResolution * R/(R0 + R)
    auto R1 = 20000.0;
    auto R2 = 10000.0;
    auto R3 = 858612.825;  // Corresponds to -50 C R = R0 *e^(kB(1/T-1/298.13))
    EXPECT_NEAR(10.0, util::GetBattTemp(battery::kResolution * (R1) / (battery::kThermFixedResistor + R1)), 1.0);
    EXPECT_NEAR(25.0, util::GetBattTemp(battery::kResolution * (R2) / (battery::kThermFixedResistor + R2)), 1.0);
    EXPECT_NEAR(-50.0, util::GetBattTemp(battery::kResolution * (R3) / (battery::kThermFixedResistor + R3)), 1.0);
}

TEST(BatteryCurrentCalcTest, One) {
    // TODO
}

TEST(ConvertIntToDec, One) {
    EXPECT_NEAR(-54.50, util::ConvertIntToDec(-5450, 2), 0.01);
    EXPECT_NEAR(35.30, util::ConvertIntToDec(3530, 2), 0.01);
}

TEST(RadToDegTest, One) {
    EXPECT_NEAR(90.0, util::RadToDeg(util::pi / 2.0), 0.0001);
    EXPECT_NEAR(-90.0, util::RadToDeg(-util::pi / 2.0), 0.0001);
}

TEST(DegToRadTest, One) {
    EXPECT_NEAR(util::pi / 2, util::DegToRad(90.0), 0.0001);
    EXPECT_NEAR(-util::pi / 2, util::DegToRad(-90.0), 0.0001);
}
