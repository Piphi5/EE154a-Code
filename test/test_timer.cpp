#include <gtest/gtest.h>

#include "TimeoutTimer.h"

TEST(TimerEndsOnExitCond, One) {
    uint32_t kMax = 5000;
    TimeoutTimer mTimer{kMax};
    ASSERT_EQ(true, mTimer.Wait(false, kMax + 100));  // timer hasn't started yet
    mTimer.StartTimer(0);
    ASSERT_EQ(true, mTimer.Wait(false, 10));
    ASSERT_EQ(true, mTimer.Wait(false, 20));
    ASSERT_EQ(true, mTimer.Wait(false, kMax - 1));
    ASSERT_EQ(false, mTimer.Wait(true, kMax - 1));
    ASSERT_EQ(false, mTimer.TimedOut());  // Did not time out
}

TEST(TimerEndsOnTimeout, One) {
    uint32_t kMax = 5000;
    TimeoutTimer mTimer{kMax};
    mTimer.StartTimer(0);
    ASSERT_EQ(true, mTimer.Wait(false, 0));
    ASSERT_EQ(true, mTimer.Wait(false, kMax - 1));
    ASSERT_EQ(false, mTimer.Wait(false, kMax));
    ASSERT_EQ(true, mTimer.TimedOut());  // Timed out
}
