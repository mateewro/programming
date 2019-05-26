#include "IClock.h"
#include <gmock/gmock.h>
#include <chrono>

struct ClockMock : public IClock
{
    MOCK_CONST_METHOD0(now, std::chrono::system_clock::time_point());
    MOCK_CONST_METHOD1(sleep_for, void(int time));
};
