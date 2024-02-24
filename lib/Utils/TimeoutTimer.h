#pragma once
#include <cstdint>

class TimeoutTimer {
   public:
    TimeoutTimer(uint32_t timeout = 5000);
    bool Wait(bool endCond, uint32_t currTime);
    void StartTimer(uint32_t time);
    bool TimedOut();

   private:
    const uint32_t kTimeout = 0;
    uint32_t mStartTime = 0;
    bool mStarted = false;
    bool mTimedOut = false;
};