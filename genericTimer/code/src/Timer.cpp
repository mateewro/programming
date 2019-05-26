#include "Timer.h"
#include "Clock.h"
#include <chrono>
#include <future>
#include <ctime>

using namespace std;
using namespace std::chrono;

Timer::Timer(const IClock& newClock) :
            m_clock(newClock)
{}

void Timer::start()
{
    m_task = async([&]
    {
        while(m_isTimerWorking)
        {
        m_clock.sleep_for(1);
        if(m_timeToFireCallback < m_clock.now())
        {
            try
            {
                m_callback();
            }
            catch(...)
            {
                m_isTimerWorking = false;
                m_isTimeConfigured = false;
                std::exception_ptr e = std::current_exception();
                std::rethrow_exception(e);
            }
            if(m_intervalTime)
            {
                m_timeToFireCallback = m_timeToFireCallback + milliseconds(*m_intervalTime);
            }
            else
            {
                m_isTimeConfigured = false;
                return;
            }
        }
        }
    });
}

void Timer::setIntervalInMs(std::function<void()> callback, Time time)
{
    if (checkIfTimerIsConfigured())
    {
        return;
    }
    m_timeToFireCallback = m_clock.now() + milliseconds(time);
    m_callback = callback;
    m_intervalTime = time;
    start();
}

bool Timer::checkIfTimerIsConfigured()
{
    if (m_isTimeConfigured)
    {
        return true;
    }
    m_isTimeConfigured = true;
    return false;
}

void Timer::setTimeoutInMs(std::function<void()> callback, Time time)
{
    if (checkIfTimerIsConfigured())
    {
        return;
    }
    m_timeToFireCallback = m_clock.now() + milliseconds(time);
    m_callback = callback;
    start();
}

Timer::~Timer()
{
    if (m_isTimeConfigured)
    {
        m_task.wait();
    }
}

Time Timer::getTimeToFireInMs()
{
    if (!m_isTimeConfigured)
    {
        return 0;
    }
    return duration_cast<std::chrono::milliseconds>(m_timeToFireCallback - m_clock.now()).count();
}

void Timer::abort()
{
    m_isTimerWorking = false;
    m_isTimeConfigured = false;
}

bool Timer::getException()
{
    if (m_task.wait_for(0s) != future_status::ready)
    {
        return false;
    }
    try
    {
        m_task.get();
    }
    catch(...)
    {
        std::exception_ptr e = std::current_exception();
        std::rethrow_exception(e);
    }
    return true;
}
