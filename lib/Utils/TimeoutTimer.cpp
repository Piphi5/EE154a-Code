#include "TimeoutTimer.h"

TimeoutTimer::TimeoutTimer(uint32_t timeout) : kTimeout{timeout} {
}

void TimeoutTimer::StartTimer(uint32_t time) {
    mStartTime = time;
    mStarted = true;
}

bool TimeoutTimer::Wait(bool endCond, uint32_t currTime) {
    if (!mStarted) {
        return true;
    }
    auto dt = currTime - mStartTime;
    if (dt >= kTimeout && !endCond) {
        mTimedOut = true;
    }
    return !endCond && dt < kTimeout;
}

bool TimeoutTimer::TimedOut() {
    return mTimedOut;
}