#include "Clock.h"
#include <future>

std::chrono::system_clock::time_point Clock::now() const
{
    return std::chrono::system_clock::now();
}

void Clock::sleep_for(int time) const
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
