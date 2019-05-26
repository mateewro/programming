#pragma once

#include <functional>
#include <thread>
#include <future>
#include <optional>
#include <memory>
#include "IClock.h"
#include "Clock.h"

using Time = unsigned int;

class Timer
{
public:
    Timer(const IClock& newClock);
    void setTimeoutInMs(std::function<void()> callback, Time time);
    void setIntervalInMs(std::function<void()> callback, Time time);
    Time getTimeToFireInMs();
    void abort();
    bool getException();
    ~Timer();
private:
    void start();
    bool checkIfTimerIsConfigured();
    std::chrono::system_clock::time_point m_timeToFireCallback;
    std::function<void()> m_callback;
    std::future<void> m_task;
    bool m_isTimeConfigured {false};
    std::optional<int> m_intervalTime;
    bool m_isTimerWorking{true};
    const IClock& m_clock;
};
