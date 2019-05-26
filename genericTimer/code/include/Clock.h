#pragma once
#include "IClock.h"
#include <chrono>

class Clock : public IClock
{
public:
    std::chrono::system_clock::time_point now() const override;
    void sleep_for(int time) const override;
    ~Clock() override = default;
};
