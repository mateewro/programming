#pragma once

#include <chrono>

class IClock
{
public:
    virtual std::chrono::system_clock::time_point now() const = 0;
    virtual void sleep_for(int time) const = 0;
    virtual ~IClock() = default;
};
